-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.6.21 - MySQL Community Server (GPL)
-- Server OS:                    Win32
-- HeidiSQL Version:             9.1.0.4867
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Dumping database structure for helbreath
DROP DATABASE IF EXISTS `helbreath`;
CREATE DATABASE IF NOT EXISTS `helbreath` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `helbreath`;


-- Dumping structure for table helbreath.account_database
DROP TABLE IF EXISTS `account_database`;
CREATE TABLE IF NOT EXISTS `account_database` (
  `name` varchar(10) NOT NULL DEFAULT '',
  `password` varchar(10) NOT NULL DEFAULT '1',
  `WorldName` varchar(10) NOT NULL DEFAULT 'WS1',
  `AccountID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `LoginIpAddress` varchar(20) NOT NULL DEFAULT '',
  `IsGMAccount` smallint(1) NOT NULL DEFAULT '0',
  `cash` int(10) unsigned NOT NULL DEFAULT '0',
  `ValidDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `LoginDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `BlockDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Email` varchar(50) NOT NULL DEFAULT '',
  `Quiz` varchar(45) NOT NULL DEFAULT '',
  `Answer` varchar(20) NOT NULL DEFAULT '',
  `FirstName` varchar(20) NOT NULL DEFAULT '',
  `LastName` varchar(20) NOT NULL DEFAULT '',
  `Address` varchar(50) NOT NULL DEFAULT '',
  `City` varchar(20) NOT NULL DEFAULT '',
  `State` varchar(30) NOT NULL DEFAULT '',
  `ZipCode` varchar(10) NOT NULL DEFAULT '',
  `Country` varchar(20) NOT NULL DEFAULT '',
  PRIMARY KEY (`name`),
  UNIQUE KEY `AccountID` (`AccountID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 PACK_KEYS=0;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.bank_item
DROP TABLE IF EXISTS `bank_item`;
CREATE TABLE IF NOT EXISTS `bank_item` (
  `CharID` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemName` varchar(20) NOT NULL DEFAULT '',
  `ItemID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `Count` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemType` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `ID1` smallint(8) NOT NULL DEFAULT '0',
  `ID2` smallint(8) NOT NULL DEFAULT '0',
  `ID3` smallint(8) NOT NULL DEFAULT '0',
  `Color` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect1` int(11) DEFAULT '0',
  `Effect2` int(11) DEFAULT '0',
  `Effect3` int(11) DEFAULT '0',
  `LifeSpan` int(11) unsigned NOT NULL DEFAULT '0',
  `Attribute` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ItemID`),
  UNIQUE KEY `ItemID` (`ItemID`),
  KEY `Index` (`CharID`),
  KEY `ItemName` (`ItemName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 PACK_KEYS=0;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.cash_transactions
DROP TABLE IF EXISTS `cash_transactions`;
CREATE TABLE IF NOT EXISTS `cash_transactions` (
  `account_name` varchar(10) NOT NULL,
  `service` varchar(50) NOT NULL,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.char_database
DROP TABLE IF EXISTS `char_database`;
CREATE TABLE IF NOT EXISTS `char_database` (
  `account_name` varchar(10) NOT NULL DEFAULT '',
  `char_name` varchar(10) NOT NULL DEFAULT '',
  `CharID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `ID1` mediumint(9) NOT NULL DEFAULT '0',
  `ID2` mediumint(9) NOT NULL DEFAULT '0',
  `ID3` mediumint(9) NOT NULL DEFAULT '0',
  `Level` smallint(4) unsigned NOT NULL DEFAULT '1',
  `Strenght` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Vitality` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Dexterity` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Intelligence` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Magic` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Agility` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Luck` smallint(5) unsigned NOT NULL DEFAULT '10',
  `Exp` int(11) unsigned NOT NULL DEFAULT '0',
  `Gender` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `Skin` smallint(6) unsigned NOT NULL DEFAULT '0',
  `HairStyle` smallint(6) unsigned NOT NULL DEFAULT '0',
  `HairColor` smallint(6) unsigned NOT NULL DEFAULT '0',
  `Underwear` smallint(6) unsigned NOT NULL DEFAULT '0',
  `ApprColor` int(11) unsigned NOT NULL DEFAULT '0',
  `Appr1` mediumint(6) NOT NULL DEFAULT '0',
  `Appr2` mediumint(6) NOT NULL DEFAULT '0',
  `Appr3` mediumint(6) NOT NULL DEFAULT '0',
  `Appr4` mediumint(6) NOT NULL DEFAULT '0',
  `Nation` varchar(10) NOT NULL DEFAULT 'Traveler',
  `MapLoc` varchar(10) NOT NULL DEFAULT 'default',
  `LocX` mediumint(4) NOT NULL DEFAULT '-1',
  `LocY` mediumint(4) NOT NULL DEFAULT '-1',
  `Contribution` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftSpecTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LockMapName` varchar(10) NOT NULL DEFAULT 'NONE',
  `LockMapTime` int(11) unsigned NOT NULL DEFAULT '0',
  `BlockDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `GuildName` varchar(20) NOT NULL DEFAULT 'NONE',
  `GuildID` int(11) NOT NULL DEFAULT '-1',
  `GuildRank` tinyint(4) NOT NULL DEFAULT '-1',
  `FightNum` tinyint(4) NOT NULL DEFAULT '0',
  `FightDate` int(10) unsigned NOT NULL DEFAULT '0',
  `FightTicket` tinyint(4) NOT NULL DEFAULT '0',
  `QuestNum` smallint(5) unsigned NOT NULL DEFAULT '0',
  `QuestID` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestCount` smallint(5) unsigned NOT NULL DEFAULT '0',
  `QuestRewType` smallint(6) NOT NULL DEFAULT '0',
  `QuestRewAmmount` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestCompleted` tinyint(1) NOT NULL DEFAULT '0',
  `EventID` int(11) unsigned NOT NULL DEFAULT '0',
  `WarCon` int(11) unsigned NOT NULL DEFAULT '0',
  `CruJob` smallint(2) unsigned NOT NULL DEFAULT '0',
  `CruID` int(11) unsigned NOT NULL DEFAULT '0',
  `CruConstructPoint` int(11) unsigned NOT NULL DEFAULT '0',
  `Popularity` int(11) NOT NULL DEFAULT '0',
  `HP` int(11) unsigned NOT NULL DEFAULT '0',
  `MP` int(11) unsigned NOT NULL DEFAULT '0',
  `SP` int(11) unsigned NOT NULL DEFAULT '0',
  `EK` int(11) unsigned NOT NULL DEFAULT '0',
  `PK` int(11) unsigned NOT NULL DEFAULT '0',
  `RewardGold` int(11) unsigned NOT NULL DEFAULT '0',
  `DownSkillID` tinyint(4) NOT NULL DEFAULT '-1',
  `Hunger` tinyint(4) unsigned NOT NULL DEFAULT '100',
  `LeftSAC` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `LeftShutupTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftPopTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftForceRecallTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftFirmStaminarTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftDeadPenaltyTime` int(11) unsigned NOT NULL DEFAULT '0',
  `PartyID` int(11) unsigned NOT NULL DEFAULT '0',
  `GizonItemUpgradeLeft` int(11) unsigned NOT NULL DEFAULT '0',
  `elo` int(11) unsigned NOT NULL DEFAULT '1000',
  `BankModified` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `AdminLevel` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `MagicMastery` varchar(100) NOT NULL DEFAULT '0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000',
  `Profile` varchar(255) NOT NULL DEFAULT '__________',
  PRIMARY KEY (`char_name`),
  UNIQUE KEY `CharID` (`CharID`),
  KEY `account_name` (`account_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 PACK_KEYS=0;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.guild
DROP TABLE IF EXISTS `guild`;
CREATE TABLE IF NOT EXISTS `guild` (
  `GuildName` varchar(20) NOT NULL DEFAULT '',
  `GuildID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `MasterName` varchar(10) NOT NULL DEFAULT '',
  `Nation` varchar(10) NOT NULL DEFAULT '',
  `NumberOfMembers` smallint(5) unsigned NOT NULL DEFAULT '0',
  `CreateDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Captains` smallint(5) unsigned NOT NULL DEFAULT '0',
  `HuntMasters` smallint(5) unsigned NOT NULL DEFAULT '0',
  `RaidMasters` smallint(5) unsigned NOT NULL DEFAULT '0',
  `WHLevel` smallint(5) unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `GuildID` (`GuildID`),
  KEY `GuildName` (`GuildName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.guild_item
DROP TABLE IF EXISTS `guild_item`;
CREATE TABLE IF NOT EXISTS `guild_item` (
  `GuildID` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemName` varchar(20) NOT NULL DEFAULT '',
  `ItemID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `Count` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemType` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `ID1` smallint(8) NOT NULL DEFAULT '0',
  `ID2` smallint(8) NOT NULL DEFAULT '0',
  `ID3` smallint(8) NOT NULL DEFAULT '0',
  `Color` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect1` int(11) DEFAULT '0',
  `Effect2` int(11) DEFAULT '0',
  `Effect3` int(11) DEFAULT '0',
  `LifeSpan` int(11) unsigned NOT NULL DEFAULT '0',
  `Attribute` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ItemID`),
  UNIQUE KEY `ItemID` (`ItemID`),
  KEY `Index` (`GuildID`),
  KEY `ItemName` (`ItemName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 PACK_KEYS=0;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.guild_member
DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE IF NOT EXISTS `guild_member` (
  `GuildName` varchar(20) NOT NULL DEFAULT '',
  `MemberName` varchar(10) NOT NULL DEFAULT '',
  `JoinDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  KEY `GuildName` (`GuildName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.ipblocked
DROP TABLE IF EXISTS `ipblocked`;
CREATE TABLE IF NOT EXISTS `ipblocked` (
  `ipaddress` varchar(20) NOT NULL DEFAULT '',
  `comment` mediumtext,
  PRIMARY KEY (`ipaddress`),
  UNIQUE KEY `ipaddress` (`ipaddress`),
  KEY `ipaddress_2` (`ipaddress`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.item
DROP TABLE IF EXISTS `item`;
CREATE TABLE IF NOT EXISTS `item` (
  `CharID` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemName` varchar(21) DEFAULT NULL,
  `ItemID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `Count` int(11) unsigned NOT NULL DEFAULT '1',
  `ItemType` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `ID1` smallint(8) NOT NULL DEFAULT '0',
  `ID2` smallint(8) NOT NULL DEFAULT '0',
  `ID3` smallint(8) NOT NULL DEFAULT '0',
  `Color` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect1` int(11) DEFAULT '0',
  `Effect2` int(11) DEFAULT '0',
  `Effect3` int(11) DEFAULT '0',
  `LifeSpan` int(11) unsigned NOT NULL DEFAULT '0',
  `Attribute` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemEquip` tinyint(1) NOT NULL DEFAULT '0',
  `ItemPosX` int(11) NOT NULL DEFAULT '40',
  `ItemPosY` int(11) NOT NULL DEFAULT '30',
  PRIMARY KEY (`ItemID`),
  UNIQUE KEY `ItemID` (`ItemID`),
  KEY `Index` (`CharID`),
  KEY `ItemName` (`ItemName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 PACK_KEYS=0;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.paypal_cart_info
DROP TABLE IF EXISTS `paypal_cart_info`;
CREATE TABLE IF NOT EXISTS `paypal_cart_info` (
  `txnid` varchar(30) NOT NULL DEFAULT '',
  `itemname` varchar(255) NOT NULL DEFAULT '',
  `itemnumber` varchar(50) DEFAULT NULL,
  `os0` varchar(20) DEFAULT NULL,
  `on0` varchar(50) DEFAULT NULL,
  `os1` varchar(20) DEFAULT NULL,
  `on1` varchar(50) DEFAULT NULL,
  `quantity` char(3) NOT NULL DEFAULT '',
  `invoice` varchar(255) NOT NULL DEFAULT '',
  `custom` varchar(255) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.paypal_payment_info
DROP TABLE IF EXISTS `paypal_payment_info`;
CREATE TABLE IF NOT EXISTS `paypal_payment_info` (
  `firstname` varchar(100) NOT NULL DEFAULT '',
  `lastname` varchar(100) NOT NULL DEFAULT '',
  `buyer_email` varchar(100) NOT NULL DEFAULT '',
  `memo` varchar(255) DEFAULT NULL,
  `itemname` varchar(255) DEFAULT NULL,
  `itemnumber` varchar(50) DEFAULT NULL,
  `os0` varchar(20) DEFAULT NULL,
  `on0` varchar(50) DEFAULT NULL,
  `os1` varchar(20) DEFAULT NULL,
  `on1` varchar(50) DEFAULT NULL,
  `quantity` char(3) DEFAULT NULL,
  `paymentdate` varchar(50) NOT NULL DEFAULT '',
  `paymenttype` varchar(10) NOT NULL DEFAULT '',
  `txnid` varchar(30) NOT NULL DEFAULT '',
  `mc_gross` varchar(6) NOT NULL DEFAULT '',
  `mc_fee` varchar(5) NOT NULL DEFAULT '',
  `paymentstatus` varchar(15) NOT NULL DEFAULT '',
  `pendingreason` varchar(10) DEFAULT NULL,
  `txntype` varchar(10) NOT NULL DEFAULT '',
  `tax` varchar(10) DEFAULT NULL,
  `mc_currency` varchar(5) NOT NULL DEFAULT '',
  `reasoncode` varchar(20) NOT NULL DEFAULT '',
  `custom` varchar(255) NOT NULL DEFAULT '',
  `street` varchar(100) NOT NULL,
  `city` varchar(50) NOT NULL,
  `zipcode` varchar(11) NOT NULL,
  `state` char(15) NOT NULL,
  `country` varchar(20) NOT NULL DEFAULT '',
  `datecreation` date NOT NULL DEFAULT '0000-00-00'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.paypal_subscription_info
DROP TABLE IF EXISTS `paypal_subscription_info`;
CREATE TABLE IF NOT EXISTS `paypal_subscription_info` (
  `subscr_id` varchar(255) NOT NULL DEFAULT '',
  `sub_event` varchar(50) NOT NULL DEFAULT '',
  `subscr_date` varchar(255) NOT NULL DEFAULT '',
  `subscr_effective` varchar(255) NOT NULL DEFAULT '',
  `period1` varchar(255) NOT NULL DEFAULT '',
  `period2` varchar(255) NOT NULL DEFAULT '',
  `period3` varchar(255) NOT NULL DEFAULT '',
  `amount1` varchar(255) NOT NULL DEFAULT '',
  `amount2` varchar(255) NOT NULL DEFAULT '',
  `amount3` varchar(255) NOT NULL DEFAULT '',
  `mc_amount1` varchar(255) NOT NULL DEFAULT '',
  `mc_amount2` varchar(255) NOT NULL DEFAULT '',
  `mc_amount3` varchar(255) NOT NULL DEFAULT '',
  `recurring` varchar(255) NOT NULL DEFAULT '',
  `reattempt` varchar(255) NOT NULL DEFAULT '',
  `retry_at` varchar(255) NOT NULL DEFAULT '',
  `recur_times` varchar(255) NOT NULL DEFAULT '',
  `username` varchar(255) NOT NULL DEFAULT '',
  `password` varchar(255) DEFAULT NULL,
  `payment_txn_id` varchar(50) NOT NULL DEFAULT '',
  `subscriber_emailaddress` varchar(255) NOT NULL DEFAULT '',
  `datecreation` date NOT NULL DEFAULT '0000-00-00'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table helbreath.skill
DROP TABLE IF EXISTS `skill`;
CREATE TABLE IF NOT EXISTS `skill` (
  `CharID` int(11) unsigned NOT NULL DEFAULT '0',
  `SkillID` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `SkillMastery` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `SkillSSN` int(10) unsigned NOT NULL DEFAULT '0',
  KEY `Index` (`CharID`),
  KEY `SkillID` (`SkillID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
