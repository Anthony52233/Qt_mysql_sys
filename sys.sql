-- MySQL dump 10.13  Distrib 5.7.27, for Linux (x86_64)
--
-- Host: localhost    Database: czs
-- ------------------------------------------------------
-- Server version	5.7.27-0ubuntu0.19.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `admins`
--

DROP TABLE IF EXISTS `admins`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admins` (
  `admin_name` varchar(45) NOT NULL,
  `admin_password` varchar(45) NOT NULL,
  PRIMARY KEY (`admin_name`),
  UNIQUE KEY `admin_name_UNIQUE` (`admin_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admins`
--

LOCK TABLES `admins` WRITE;
/*!40000 ALTER TABLE `admins` DISABLE KEYS */;
INSERT INTO `admins` VALUES ('1','1'),('Adi','111'),('admin_1','111'),('admin_2','111'),('czs','111');
/*!40000 ALTER TABLE `admins` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `browse`
--

DROP TABLE IF EXISTS `browse`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `browse` (
  `user_name` varchar(45) DEFAULT NULL,
  `camera_no` varchar(45) DEFAULT NULL,
  `time` int(11) NOT NULL,
  PRIMARY KEY (`time`),
  UNIQUE KEY `time_UNIQUE` (`time`),
  KEY `fk_browse_1_idx` (`camera_no`),
  KEY `fk_browse_2` (`user_name`),
  CONSTRAINT `fk_browse_1` FOREIGN KEY (`camera_no`) REFERENCES `cameras` (`camera_no`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_browse_2` FOREIGN KEY (`user_name`) REFERENCES `customs` (`user_name`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `browse`
--

LOCK TABLES `browse` WRITE;
/*!40000 ALTER TABLE `browse` DISABLE KEYS */;
INSERT INTO `browse` VALUES ('1','Canon5D4',1567654944),('1','SonyA7S2',1567655249),('1','SonyA7S2',1567661437),('1','Canon5D3',1567661463),('1','leica0',1567661630),('czs','Canon5D4',1567662586),('czs','leica1',1567662612),('Tom','leica2',1567662703),('Tom','leica1',1567662712),('Tom','leica4',1567662723),('Tom','leica4',1567662752),('Tom','leica4',1567662773),('1','leica1',1567667273),('Tom','Canon6D',1567667633),('Tom','Canon6D',1567667661),('Tom','Sony10',1567668109),('Lily','Sony10',1567668476),('1','SonyA7S2',1567670364);
/*!40000 ALTER TABLE `browse` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cameras`
--

DROP TABLE IF EXISTS `cameras`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cameras` (
  `camera_no` varchar(45) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  `total_num` int(11) DEFAULT NULL,
  `rent_num` int(11) DEFAULT NULL,
  `price` int(11) DEFAULT NULL,
  PRIMARY KEY (`camera_no`),
  UNIQUE KEY `carid_UNIQUE` (`camera_no`),
  KEY `cameras_price_index` (`price`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cameras`
--

LOCK TABLES `cameras` WRITE;
/*!40000 ALTER TABLE `cameras` DISABLE KEYS */;
INSERT INTO `cameras` VALUES ('Canon5D3','Canon',10,1,45),('Canon5D4','Canon',10,5,50),('Canon6D','Canon',10,2,100),('Canon6D2','Canon',10,0,70),('GoPro7','GoPro',10,0,40),('leica0','leica',10,3,32),('leica1','leica',10,6,32),('leica2','leica',10,2,32),('leica3','leica',10,0,32),('leica4','leica',10,5,32),('leica5','leica',10,0,32),('leica6','leica',10,0,32),('leica7','leica',10,0,32),('leica8','leica',10,0,32),('leica9','leica',10,0,32),('Sony10','Sony is good!',10,4,100),('SonyA7','Sony',10,0,60),('SonyA7R2','Sony',10,0,40),('SonyA7R3','Sony',10,0,40),('SonyA7S2','Sony',10,6,30),('SonyA9','Sony',10,0,90);
/*!40000 ALTER TABLE `cameras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customs`
--

DROP TABLE IF EXISTS `customs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `customs` (
  `user_name` varchar(45) NOT NULL,
  `user_password` varchar(45) NOT NULL,
  `balance` float DEFAULT NULL,
  `sex` varchar(45) DEFAULT NULL,
  `phone` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`user_name`),
  UNIQUE KEY `user_name_UNIQUE` (`user_name`),
  KEY `customs_balance_index` (`balance`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customs`
--

LOCK TABLES `customs` WRITE;
/*!40000 ALTER TABLE `customs` DISABLE KEYS */;
INSERT INTO `customs` VALUES ('1','1',1832.38,'',''),('czs','111',652.071,'man','13460699149'),('Lily','111',2000,'woman','120'),('Mike','111',2000,'man','13460699149'),('Tom','111',2000,'woman','');
/*!40000 ALTER TABLE `customs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `indents`
--

DROP TABLE IF EXISTS `indents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `indents` (
  `order_no` varchar(45) NOT NULL,
  `user_name` varchar(45) NOT NULL,
  `rent_num` int(11) DEFAULT NULL,
  `camera_no` varchar(45) NOT NULL,
  `start_time` int(11) DEFAULT NULL,
  `rent_time` int(11) DEFAULT NULL,
  `extra_charge` int(11) DEFAULT NULL,
  PRIMARY KEY (`order_no`),
  UNIQUE KEY `id_UNIQUE` (`order_no`),
  KEY `fk_indent_1` (`user_name`),
  KEY `fk_indent_2` (`camera_no`),
  CONSTRAINT `fk_indent_1` FOREIGN KEY (`user_name`) REFERENCES `customs` (`user_name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_indent_2` FOREIGN KEY (`camera_no`) REFERENCES `cameras` (`camera_no`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `indents`
--

LOCK TABLES `indents` WRITE;
/*!40000 ALTER TABLE `indents` DISABLE KEYS */;
INSERT INTO `indents` VALUES ('1567661437','1',2,'SonyA7S2',1567661444,1567785600,0),('1567661630','1',2,'leica0',1567661636,1567872000,0),('1567662612','czs',1,'leica1',1567662617,1567785600,50),('1567662703','Tom',1,'leica2',1567662707,1567785600,0),('1567662712','Tom',1,'leica1',1567662717,1567785600,0),('1567662723','Tom',1,'leica4',1567662729,1567785600,0),('1567662752','Tom',1,'leica4',1567662754,1567699200,0),('1567662773','Tom',1,'leica4',1567662775,1567699200,0),('1567668476','Lily',2,'Sony10',1567668484,1567785600,50);
/*!40000 ALTER TABLE `indents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `init`
--

DROP TABLE IF EXISTS `init`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `init` (
  `id` char(20) DEFAULT NULL,
  `salary` char(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `init`
--

LOCK TABLES `init` WRITE;
/*!40000 ALTER TABLE `init` DISABLE KEYS */;
INSERT INTO `init` VALUES ('1','2'),('3','4'),('5','6'),('5','7');
/*!40000 ALTER TABLE `init` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `manage`
--

DROP TABLE IF EXISTS `manage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `manage` (
  `admin_name` varchar(45) DEFAULT NULL,
  `camera_no` varchar(45) DEFAULT NULL,
  `time` int(11) NOT NULL,
  `operate` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`time`),
  UNIQUE KEY `time_UNIQUE` (`time`),
  KEY `fk_manage_1` (`admin_name`),
  CONSTRAINT `fk_manage_1` FOREIGN KEY (`admin_name`) REFERENCES `admins` (`admin_name`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `manage`
--

LOCK TABLES `manage` WRITE;
/*!40000 ALTER TABLE `manage` DISABLE KEYS */;
INSERT INTO `manage` VALUES ('1','6',1567599577,'add'),('1','6',1567600158,'del'),('1','6',1567600291,'del'),('1','Sony1',1567600428,'edit'),('1','Sony0',1567654089,'del'),('1','Sony1',1567654090,'del'),('1','Sony10',1567654091,'del'),('1','Sony10',1567654092,'del'),('1','Sony11',1567654095,'del'),('1','Sony13',1567654096,'del'),('1','Sony16',1567654097,'del'),('1','Sony2',1567654098,'del'),('1','Sony22',1567654099,'del'),('1','Sony26',1567654100,'del'),('1','Sony31',1567654101,'del'),('1','Sony36',1567654102,'del'),('1','Sony40',1567654103,'del'),('1','Sony47',1567654104,'del'),('1','Sony52',1567654105,'del'),('1','Sony59',1567654106,'del'),('1','Sony64',1567654107,'del'),('1','Sony7',1567654108,'del'),('1','Sony75',1567654109,'del'),('1','Sony81',1567654110,'del'),('1','Sony88',1567654111,'del'),('1','Sony90',1567654112,'del'),('1','Sony95',1567654113,'del'),('1','Sony97',1567654114,'del'),('1','Sy001',1567654118,'del');
/*!40000 ALTER TABLE `manage` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `my_indent`
--

DROP TABLE IF EXISTS `my_indent`;
/*!50001 DROP VIEW IF EXISTS `my_indent`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `my_indent` AS SELECT 
 1 AS `order_no`,
 1 AS `user_name`,
 1 AS `camera_no`,
 1 AS `rent_num`,
 1 AS `price`,
 1 AS `start_time`,
 1 AS `rent_time`,
 1 AS `rent_days`,
 1 AS `rent_charge`,
 1 AS `extra_charge`,
 1 AS `final_charge`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `update_user`
--

DROP TABLE IF EXISTS `update_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `update_user` (
  `admin_name` varchar(45) DEFAULT NULL,
  `custom_name` varchar(45) DEFAULT NULL,
  `time` int(11) NOT NULL,
  `operate` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`time`),
  KEY `fk_update_1` (`admin_name`),
  CONSTRAINT `fk_update_1` FOREIGN KEY (`admin_name`) REFERENCES `admins` (`admin_name`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `update_user`
--

LOCK TABLES `update_user` WRITE;
/*!40000 ALTER TABLE `update_user` DISABLE KEYS */;
INSERT INTO `update_user` VALUES ('1','cuntom10',1567600890,'edit'),('1','5',1567600981,'del'),('1','4',1567600987,'del'),('1','4',1567601006,'del'),('1','czs',1567654358,'edit'),('1','1',1567655057,'edit'),('1','Lily',1567662664,'edit'),('1','Mike',1567662677,'edit'),('1','Tom',1567662685,'edit'),('1','czs',1567667375,'edit'),('1','Lily',1567667380,'edit'),('1','Mike',1567667385,'edit'),('1','Tom',1567667391,'edit'),('czs','Lily',1567668338,'edit'),('1','1',1567670298,'edit');
/*!40000 ALTER TABLE `update_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Final view structure for view `my_indent`
--

/*!50001 DROP VIEW IF EXISTS `my_indent`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`%` SQL SECURITY DEFINER */
/*!50001 VIEW `my_indent` AS select `indents`.`order_no` AS `order_no`,`indents`.`user_name` AS `user_name`,`indents`.`camera_no` AS `camera_no`,`indents`.`rent_num` AS `rent_num`,`cameras`.`price` AS `price`,`indents`.`start_time` AS `start_time`,`indents`.`rent_time` AS `rent_time`,((`indents`.`rent_time` - `indents`.`start_time`) / ((24 * 60) * 60)) AS `rent_days`,(((`indents`.`rent_num` * (`indents`.`rent_time` - `indents`.`start_time`)) / ((24 * 60) * 60)) * `cameras`.`price`) AS `rent_charge`,`indents`.`extra_charge` AS `extra_charge`,((((`indents`.`rent_num` * (`indents`.`rent_time` - `indents`.`start_time`)) / ((24 * 60) * 60)) * `cameras`.`price`) + `indents`.`extra_charge`) AS `final_charge` from (`indents` join `cameras`) where (`indents`.`camera_no` = `cameras`.`camera_no`) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-11-17 21:54:05
