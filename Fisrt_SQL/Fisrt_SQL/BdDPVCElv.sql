/* 
personnel
*/
CREATE TABLE `personnel` (
  `id_Personnel` smallint(2) unsigned NOT NULL auto_increment,
  `login` varchar(25) NOT NULL,
  `password` varchar(25) NOT NULL,
  `qualite` enum('OPERATEUR','PREPARATEUR') NOT NULL,
  PRIMARY KEY  USING BTREE (`id_Personnel`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

/* 
formule
*/
CREATE TABLE `formule` (
  `id_Formule` tinyint(1) unsigned NOT NULL auto_increment,
  `type` varchar(10) NOT NULL,
  `pvcBase` double(5,2) NOT NULL,
  `plastifiant` decimal(5,2) NOT NULL,
  `lubrifiant` decimal(5,2) NOT NULL,
  `dureeMalaxage` smallint(2) NOT NULL,
  `dureeRefroidissement` smallint(2) NOT NULL,
  PRIMARY KEY  (`id_Formule`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

/* 
ordrefabrication
*/
CREATE TABLE `ordrefabrication` (
  `id_OrdreFabrication` smallint(2) unsigned NOT NULL auto_increment,
  `reference` varchar(15) NOT NULL,
  `id_Formule` tinyint(1) unsigned NOT NULL,
  `quantite` decimal(5,2) NOT NULL,
  `etat` enum('X','E','T') NOT NULL,
  `heurefin` datetime default NULL,
  `id_Personnel` smallint(2) unsigned NOT NULL,
  PRIMARY KEY  USING BTREE (`id_OrdreFabrication`,`id_Formule`,`id_Personnel`),
  KEY `id_Formule` (`id_Formule`),
  KEY `id_Personnel` (`id_Personnel`),
  CONSTRAINT `id_Personnel` FOREIGN KEY (`id_Personnel`) REFERENCES `personnel` (`id_Personnel`),
  CONSTRAINT `id_Formule` FOREIGN KEY (`id_Formule`) REFERENCES `formule` (`id_Formule`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

