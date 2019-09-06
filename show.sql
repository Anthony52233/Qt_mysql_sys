#建立触发器，保证租借数量不大于总量。触发器实现断言功能
use czs;
drop trigger camera_total_gt_rent;
delimiter $$
create trigger camera_total_gt_rent 
after update
on cameras for each row
begin
	DECLARE msg VARCHAR(200);
	if new.rent_num > new.total_num
    then
		set msg = concat("库存不足：已租赁数量，总量", old.rent_num, new.total_num);
        signal sqlstate 'HY000' set message_text = msg;
	end if;
end;
$$
delimiter ;

select * from cameras;
update cameras set rent_num = 1 where camera_no = "Canon5D3";


#触发器
#当生成新的订单，更改cameras表中的rent_num数量。
drop trigger update_camera_rent_num;
delimiter $$
create trigger update_camera_rent_num
after insert
on indents for each row
begin
	update cameras set rent_num = new.rent_num+cameras.rent_num where camera_no = new.camera_no;
end;
$$
delimiter ;

select * from cameras where camera_no = "leica0";
select * from indents;
insert into indents(order_no, user_name, rent_num, camera_no) values("111", "1", "1", "leica0");




select * from indents;
select * from cameras;
delete from indents where order_no = "111";

update cameras set rent_num = 0 where camera_no = "1";



#创建我的订单视图
drop view my_indent;
create view my_indent(order_no, user_name, camera_no, rent_num, price, start_time, rent_time, rent_days, rent_charge, extra_charge, finall_charge)
as select order_no, user_name, indents.camera_no, indents.rent_num, price, start_time, rent_time, (rent_time-start_time)/(24*60*60), indents.rent_num*(rent_time-start_time)/(24*60*60)*price, extra_charge, indents.rent_num*(rent_time-start_time)/(24*60*60)*price + extra_charge
from indents, cameras
where indents.camera_no = cameras.camera_no;

select * from browse;
select * from manage;
select * from update_user;


#定义视图
create index customs_balance_index on customs(balance);
create index cameras_price_index on cameras(price);







insert into cameras values("Canon5D4", "Canon", 10, 0, 50);
insert into cameras values("Canon5D3", "Canon", 10, 0, 45);
insert into cameras values("Canon6D2", "Canon", 10, 0, 70);
insert into cameras values("Canon6D", "Canon", 10, 0, 100);
insert into cameras values("GoPro7", "Canon", 10, 0, 40);
update cameras set name = "GoPro" where camera_no = "GoPro7";
insert into cameras values("SonyA7R2", "Sony", 10, 0, 40);
insert into cameras values("SonyA7R3", "Sony", 10, 0, 40);
insert into cameras values("SonyA7S2", "Sony", 10, 0, 30);
insert into cameras values("SonyA7", "Sony", 10, 0, 60);
insert into cameras values("SonyA9", "Sony", 10, 0, 90);
delete from cameras where camera_no = "2";
select * from browse;
delete from browse where time = 1567598864;
update customs set user_name = "Mike" where user_name = "cuntom10";
update admins set admin_name = "czs" where admin_name = "4";

use czs;
show create table update_user;