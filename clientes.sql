CREATE DATABASE  IF NOT EXISTS `clientes` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `clientes`;
-- MySQL dump 10.13  Distrib 8.0.22, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: clientes
-- ------------------------------------------------------
-- Server version	8.0.25-0ubuntu0.20.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `cliente`
--

DROP TABLE IF EXISTS `cliente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cliente` (
  `idcliente` int NOT NULL AUTO_INCREMENT,
  `nombre` varchar(45) NOT NULL,
  `cedula` int NOT NULL,
  `telefono` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idcliente`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cliente`
--

LOCK TABLES `cliente` WRITE;
/*!40000 ALTER TABLE `cliente` DISABLE KEYS */;
INSERT INTO `cliente` VALUES (4,'oliver',26269828,'04249516684');
/*!40000 ALTER TABLE `cliente` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `compras`
--

DROP TABLE IF EXISTS `compras`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `compras` (
  `fecha` datetime DEFAULT NULL,
  `codbarra` int NOT NULL,
  `idproductos` int DEFAULT NULL,
  `nombre` varchar(45) DEFAULT NULL,
  `precio_compra` int NOT NULL,
  `idProveedores` int DEFAULT NULL,
  PRIMARY KEY (`codbarra`),
  KEY `idproductos_idx` (`idproductos`),
  KEY `idProveedores_idx` (`idProveedores`),
  CONSTRAINT `idproductos` FOREIGN KEY (`idproductos`) REFERENCES `productos` (`idproductos`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `idProveedores` FOREIGN KEY (`idProveedores`) REFERENCES `proveedores` (`idproveedores`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `compras`
--

LOCK TABLES `compras` WRITE;
/*!40000 ALTER TABLE `compras` DISABLE KEYS */;
INSERT INTO `compras` VALUES ('2021-07-27 19:49:47',1111,23,'GUANTES H',500,5),('2021-07-27 19:49:48',1532,27,'SOLUCION',1520,5),('2021-07-27 19:49:46',2513,21,'TAPABOCAS',1500,5),('2021-07-27 19:49:47',3422,24,'MASCARILLA',1000,5),('2021-07-27 19:49:46',4144,22,'OXIGENO 9%',1200,5),('2021-07-27 19:49:48',5656,26,'GAZA BLANCA',900,5),('2021-07-27 19:49:48',7555,25,'INYECTADORA',850,5);
/*!40000 ALTER TABLE `compras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `historial_compra`
--

DROP TABLE IF EXISTS `historial_compra`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `historial_compra` (
  `fecha` datetime DEFAULT NULL,
  `codbarra` int NOT NULL,
  `idproductos` int DEFAULT NULL,
  `nombre` varchar(45) DEFAULT NULL,
  `precio_compra` int DEFAULT NULL,
  `idProveedores` int DEFAULT NULL,
  PRIMARY KEY (`codbarra`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `historial_compra`
--

LOCK TABLES `historial_compra` WRITE;
/*!40000 ALTER TABLE `historial_compra` DISABLE KEYS */;
INSERT INTO `historial_compra` VALUES ('2021-07-27 19:49:47',1111,23,'GUANTES H',500,5),('2021-07-27 19:49:48',1532,27,'SOLUCION',1520,5),('2021-07-27 19:49:46',2513,21,'TAPABOCAS',1500,5),('2021-07-27 19:49:47',3422,24,'MASCARILLA',1000,5),('2021-07-27 19:49:46',4144,22,'OXIGENO 9%',1200,5),('2021-07-27 19:49:48',5656,26,'GAZA BLANCA',900,5),('2021-07-27 19:49:48',7555,25,'INYECTADORA',850,5);
/*!40000 ALTER TABLE `historial_compra` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `productos`
--

DROP TABLE IF EXISTS `productos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `productos` (
  `idproductos` int NOT NULL AUTO_INCREMENT,
  `nombre` varchar(45) NOT NULL,
  `precio` int NOT NULL,
  `descripcion` varchar(200) NOT NULL,
  `cantidad` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idproductos`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `productos`
--

LOCK TABLES `productos` WRITE;
/*!40000 ALTER TABLE `productos` DISABLE KEYS */;
INSERT INTO `productos` VALUES (21,'TAPABOCAS',1000,'SON PARA TAPAR LA BOCA','1'),(22,'OXIGENO',1500,'SIN EL NO PUEDES RESPIRAR','1'),(23,'GUANTES',1200,'SON PARA USARLOS','1'),(24,'MASCARILLA',500,'CUBRE LA CARA','1'),(25,'INYECTADORA',600,'PARA INYECTAR','1'),(26,'GAZA',200,'PARA CUBRIR HERIDAS','1'),(27,'SOLUCION',800,'SOLUCION AL 9%','1');
/*!40000 ALTER TABLE `productos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proveedores`
--

DROP TABLE IF EXISTS `proveedores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `proveedores` (
  `idproveedores` int NOT NULL AUTO_INCREMENT,
  `nombre` varchar(45) NOT NULL,
  `descripcion` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idproveedores`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proveedores`
--

LOCK TABLES `proveedores` WRITE;
/*!40000 ALTER TABLE `proveedores` DISABLE KEYS */;
INSERT INTO `proveedores` VALUES (5,'oliver','LG shop'),(6,'alfonzo','Factor Tecnology');
/*!40000 ALTER TABLE `proveedores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ventas`
--

DROP TABLE IF EXISTS `ventas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ventas` (
  `cedula` int NOT NULL,
  `nombrepro` varchar(45) NOT NULL,
  `fecha` varchar(45) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ventas`
--

LOCK TABLES `ventas` WRITE;
/*!40000 ALTER TABLE `ventas` DISABLE KEYS */;
INSERT INTO `ventas` VALUES (26269828,'oliverf','2021-07-27 18:12:37'),(26269828,'oliverdd','2021-07-27 18:55:25'),(26269828,'olivers','2021-07-27 18:55:47'),(26269828,'oliverdd','2021-07-27 19:06:57'),(26269828,'olivers','2021-07-27 19:07:10'),(26269828,'olivers','2021-07-27 19:20:13'),(26269828,'oliverg','2021-07-27 19:24:03'),(26269828,'oliverf','2021-07-27 19:25:48'),(26269828,'oliverdddd','2021-07-27 19:26:42');
/*!40000 ALTER TABLE `ventas` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-07-27 20:17:47
