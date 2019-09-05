select * from customs;
select * from cameras;
select * from rent;
use czs;
insert into customs(user_name, password) values("1", "1");
insert into customs(user_name, password) values("2", "2");
insert into customs(user_name, password) values("3", "3");

#alter table customs modify	password varchar(45) not null comment "111";

delete from customs where user_name = "6";

insert into cars(id) value("1");
insert into cars(id) value("2");
insert into cars(id) value("3");

insert into rent(id, customs_user_name, car_id) value("Aug2601", "1", "1");
insert into rent(id, customs_user_name, car_id) value("Aug2602", "2", "1");
insert into rent(id, customs_user_name, car_id) value("Aug2603", "2", "2");
insert into rent(id, customs_user_name, car_id) value("Aug2604", "2", "5");

#alter table rent add constraint fk_column_id foreign key(customs_user_name) references customs(user_name);
alter table rent add  foreign key(car_id) references cars(id);
alter table rent add  foreign key(customs_user_name) references customs(user_name);

#为cameras添加断言。
#create assertion camera_total_gt_rent check 
#(not exits (
#	select * from cameras 
#    where rent_num > total_num));

delimiter $$
create trigger camera_total_gt_rent 
after update on cameras
for each row
begin
DECLARE msg VARCHAR(200);
if(new.rent_num > new.total_num)
then update cameras set new.rent_num = old.rent_num;
	set msg = concat("库存不足：已租赁数量，总量", old.rent_num, new.total_num);
	signal sqlstate 'HY000' set message_text = msg;
end if;
end;
$$
delimiter ;

create trigger camera_total_gt_rent_1
before update on cameras
for each row
where(new.rent_num > old.total_num)
begin
#if(new.rent_num > old.total_num)
#then set .rent_num = @old_rent;
#end if;
#set @new_total = old.rent_num;
#update cameras set new.rent_num = old.rent_num where new.rent_num > new.total_num
end;

show create table indent;


use czs;
show create table update_user;





#建立触发器，保证租借数量不大于总量。触发器实现断言功能
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

update cameras set rent_num = 11 where camera_no = "1";

select * from cameras;

#当生成新的订单，更改cameras表中的rent_num数量。
delimiter $$
create trigger update_camera_rent_num
after insert
on indents for each row
begin
	update cameras set rent_num = new.rent_num+cameras.rent_num where camera_no = new.camera_no;
end;
$$
delimiter ;

drop trigger update_camera_rent_num;
insert into indents(order_no, user_name, rent_num, camera_no) values("111", "1", "1", "1");
select * from indents;
select * from cameras;
delete from indents where order_no = "111";

update cameras set rent_num = 0 where camera_no = "1";




drop trigger camera_total_gt_rent;
show variables like '%table_names';
show triggers;

select * from cameras;
select * from admin;

insert into cameras(cameras_no, name, total_num, rent_num, price) values("Sy001", "Sony", 10, 9, 100); 

update cameras set rent_num = 11 where camera_no = "Sy001";

insert into admin(admin_name, admin_password) values("admin001", "111");
insert into admin(admin_name, admin_password) values("admin002", "111");
delete from admin where admin_name = "admin002";

#创建函数往admin表中快速插入测试数据。
DELIMITER $$
 
USE `czs`$$
 
DROP PROCEDURE IF EXISTS `insert_admin_table`$$
 
CREATE DEFINER=`root`@`localhost` PROCEDURE `insert_admin_table`(IN item INTEGER)
BEGIN
DECLARE counter INT;
SET counter = 0;
WHILE counter < item DO
INSERT INTO admin VALUES(concat("admin", counter), "111");
SET counter = counter + 1;
END WHILE;
END$$
 
DELIMITER ;

call `insert_admin_table`(10)

DELIMITER $$
 
USE `czs`$$
 
DROP PROCEDURE IF EXISTS `insert_camera_table`$$
 
CREATE DEFINER=`root`@`localhost` PROCEDURE `insert_camera_table`(IN item INTEGER)
BEGIN
DECLARE counter INT;
SET counter = 0;
WHILE counter < item DO
INSERT INTO cameras VALUES(concat("leica",counter), "leica", "10", "0", "32");
SET counter = counter + 1;
END WHILE;
END$$
 
DELIMITER ;

call `insert_camera_table`(10);
select * from cameras;

DELIMITER $$
 
USE `czs`$$
 
DROP PROCEDURE IF EXISTS `insert_custom_table`$$
 
CREATE DEFINER=`root`@`localhost` PROCEDURE `insert_custom_table`(IN item INTEGER)
BEGIN
DECLARE counter INT;
SET counter = 0;
WHILE counter < item DO
INSERT INTO customs VALUES(concat("cuntom",counter), "111", 1000, "man", "13460699149");
SET counter = counter + 1;
END WHILE;
END$$
 
DELIMITER ;

call `insert_custom_table`(100);
select * from customs;

alter table customs add constraint sex_check check(sex in("man","woman"));
update customs set sex = "1" where user_name = "1";

#定义一个视图，用于客户浏览相机信息
use czs;
select * from indents;
insert into indent values("1567229141", "1", 0, "Sony12", "1567229142", "1567180800", 0);
select * from indent where user_name = "1";
select price from cameras where camera_no = "Sony12";
select price from cameras where camera_no = "Sony1";

#创建我的订单视图
drop view my_indent;
create view my_indent(order_no, user_name, camera_no, rent_num, price, start_time, rent_time, rent_days, rent_charge, extra_charge, finall_charge)
as select order_no, user_name, indents.camera_no, indents.rent_num, price, start_time, rent_time, (rent_time-start_time)/(24*60*60), indents.rent_num*(rent_time-start_time)/(24*60*60)*price, extra_charge, indents.rent_num*(rent_time-start_time)/(24*60*60)*price + extra_charge
from indents, cameras
where indents.camera_no = cameras.camera_no;

select * from my_indent;
delete from indents where user_name = "2";
select * from customs;
select * from admins;
select * from cameras;
select * from indents;
update customs set balance=1000 where user_name = '3';
insert into customs values("4", "4", 4, "woman", "120");
delete from customs where user_name = `cuntom10`;
select rent_num, total_num from cameras where camera_no = "Sony14";
SET SQL_SAFE_UPDATES = 0;#关闭安全模式
update cameras set rent_num = 0;
update cameras set rent_num = 3 where camera_no = "Sony0";

update my_indent set user_name = "1", camera_no = "Sony0", rent_num = 3, price = 100, start_time = "1567427208", rent_time = "1567440000", rent_days =0.1481 ,rent_charge = 44.4167, extra_charge = 10, final_charge = 44.4167 where order_no = "1567427206";
select * from indent order by extra_charge;
select * from indent;
select * from cameras;
select * from browse;
select * from manage;
insert into manage values("1", "6", "1567599577", "add");
insert into manage values("1", "6", "1567600158", "del");
select * from update_user;

#定义视图
create index customs_balance_index on customs(balance);
create index cameras_price_index on cameras(price);