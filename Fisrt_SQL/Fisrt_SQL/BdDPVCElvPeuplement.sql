
/* 
peuplement formule
*/

INSERT INTO `formule` VALUES ('1','RIGIDE','80.00','10.00','10.00','30','20');
INSERT INTO `formule` VALUES ('2','SOUPLE','70.00','20.00','10.00','35','10');

/* 
peuplement personnel
*/

INSERT INTO `personnel` VALUES ('1','op1','123abc','OPERATEUR');
INSERT INTO `personnel` VALUES ('2','op2','456abc','OPERATEUR');
INSERT INTO `personnel` VALUES ('3','prepa2','prepa2','PREPARATEUR');
INSERT INTO `personnel` VALUES ('4','prepa1','prepa1','PREPARATEUR');

/* 
peuplement ordrefabrication
ATTENTION : changer les valeurs des clefs secondaires
			(Formule et Personnel)
*/

INSERT INTO `ordrefabrication` VALUES (NULL,'Ref_OF_1','1','2.50','T','2007-09-24 23:47:29','4');
INSERT INTO `ordrefabrication` VALUES (NULL,'Ref_OF_2','2','3.00','E','2007-09-24 23:21:22','4');
INSERT INTO `ordrefabrication` VALUES (NULL,'Ref_OF_3','1','3.00','X','2007-09-24 23:21:22','3');
