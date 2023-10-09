-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3307
-- Generation Time: Oct 09, 2023 at 10:23 PM
-- Server version: 10.4.22-MariaDB
-- PHP Version: 8.1.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `citeuniv`
--

-- --------------------------------------------------------

--
-- Table structure for table `batiment`
--

CREATE TABLE `batiment` (
  `REFBAT` char(11) NOT NULL,
  `LOCATION` int(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `batiment`
--

INSERT INTO `batiment` (`REFBAT`, `LOCATION`) VALUES
('Batiment 01', 7),
('Batiment 02', 3),
('Batiment 03', 4);

-- --------------------------------------------------------

--
-- Table structure for table `calendrier`
--

CREATE TABLE `calendrier` (
  `DATEDEBUTLOCATION` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `calendrier`
--

INSERT INTO `calendrier` (`DATEDEBUTLOCATION`) VALUES
('2014-09-13'),
('2016-09-02'),
('2023-05-17'),
('2023-09-05');

-- --------------------------------------------------------

--
-- Table structure for table `chambre`
--

CREATE TABLE `chambre` (
  `REFBAT` char(11) NOT NULL,
  `NUMCHAMBRE` char(3) NOT NULL,
  `CATEGORIE` varchar(32) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `chambre`
--

INSERT INTO `chambre` (`REFBAT`, `NUMCHAMBRE`, `CATEGORIE`) VALUES
('Batiment 01', '001', '1 Pièce'),
('Batiment 01', '002', '2 Pièces'),
('Batiment 02', '001', '1 Pièce'),
('Batiment 02', '004', '2 pieces');

-- --------------------------------------------------------

--
-- Table structure for table `etudiant`
--

CREATE TABLE `etudiant` (
  `NUMET` char(5) NOT NULL,
  `NOMET` varchar(50) DEFAULT NULL,
  `PRENOMET` varchar(50) DEFAULT NULL,
  `NUMTEL` char(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `etudiant`
--

INSERT INTO `etudiant` (`NUMET`, `NOMET`, `PRENOMET`, `NUMTEL`) VALUES
('E0000', 'RAKOTOMALALA', 'Johns', '0349895234'),
('E0001', 'ANDRIAMANANTENA', 'Joseph', '0385372098'),
('E0003', 'RASOAMALALA', 'Vignette', '0336595202'),
('E0004', 'Julo', 'Lezy', '0342327089');

-- --------------------------------------------------------

--
-- Table structure for table `historique_location`
--

CREATE TABLE `historique_location` (
  `id` int(11) NOT NULL,
  `etudiant_id` char(5) NOT NULL,
  `chambre_id` char(3) NOT NULL,
  `refbat` char(11) NOT NULL,
  `date_debut` date NOT NULL,
  `date_fin` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `louer`
--

CREATE TABLE `louer` (
  `NUMET` char(5) NOT NULL,
  `REFBAT` char(11) NOT NULL,
  `NUMCHAMBRE` char(3) NOT NULL,
  `DATEDEBUTLOCATION` date NOT NULL,
  `DATEFINLOCATION` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `louer`
--

INSERT INTO `louer` (`NUMET`, `REFBAT`, `NUMCHAMBRE`, `DATEDEBUTLOCATION`, `DATEFINLOCATION`) VALUES
('E0001', 'Batiment 02', '001', '2016-09-02', '2023-09-06'),
('E0003', 'Batiment 01', '002', '2023-09-05', '2023-09-04');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `batiment`
--
ALTER TABLE `batiment`
  ADD PRIMARY KEY (`REFBAT`);

--
-- Indexes for table `calendrier`
--
ALTER TABLE `calendrier`
  ADD PRIMARY KEY (`DATEDEBUTLOCATION`);

--
-- Indexes for table `chambre`
--
ALTER TABLE `chambre`
  ADD PRIMARY KEY (`REFBAT`,`NUMCHAMBRE`);

--
-- Indexes for table `etudiant`
--
ALTER TABLE `etudiant`
  ADD PRIMARY KEY (`NUMET`);

--
-- Indexes for table `historique_location`
--
ALTER TABLE `historique_location`
  ADD PRIMARY KEY (`id`),
  ADD KEY `etudiant_id` (`etudiant_id`),
  ADD KEY `refbat` (`refbat`,`chambre_id`);

--
-- Indexes for table `louer`
--
ALTER TABLE `louer`
  ADD PRIMARY KEY (`NUMET`,`REFBAT`,`NUMCHAMBRE`,`DATEDEBUTLOCATION`),
  ADD KEY `FK_LOUER_CHAMBRE` (`REFBAT`,`NUMCHAMBRE`),
  ADD KEY `FK_LOUER_CALENDRIER` (`DATEDEBUTLOCATION`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `historique_location`
--
ALTER TABLE `historique_location`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `chambre`
--
ALTER TABLE `chambre`
  ADD CONSTRAINT `FK_CHAMBRE_BATIMENT` FOREIGN KEY (`REFBAT`) REFERENCES `batiment` (`REFBAT`);

--
-- Constraints for table `historique_location`
--
ALTER TABLE `historique_location`
  ADD CONSTRAINT `historique_location_ibfk_1` FOREIGN KEY (`etudiant_id`) REFERENCES `etudiant` (`NUMET`),
  ADD CONSTRAINT `historique_location_ibfk_2` FOREIGN KEY (`refbat`,`chambre_id`) REFERENCES `chambre` (`REFBAT`, `NUMCHAMBRE`);

--
-- Constraints for table `louer`
--
ALTER TABLE `louer`
  ADD CONSTRAINT `FK_LOUER_CALENDRIER` FOREIGN KEY (`DATEDEBUTLOCATION`) REFERENCES `calendrier` (`DATEDEBUTLOCATION`),
  ADD CONSTRAINT `FK_LOUER_CHAMBRE` FOREIGN KEY (`REFBAT`,`NUMCHAMBRE`) REFERENCES `chambre` (`REFBAT`, `NUMCHAMBRE`),
  ADD CONSTRAINT `FK_LOUER_ETUDIANT` FOREIGN KEY (`NUMET`) REFERENCES `etudiant` (`NUMET`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
