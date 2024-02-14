-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Jan 24, 2024 at 05:30 PM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `hotel`
--

-- --------------------------------------------------------

--
-- Table structure for table `booking`
--

CREATE TABLE `booking` (
  `reservationId` int(11) NOT NULL,
  `rId` int(11) NOT NULL,
  `quantity` int(11) NOT NULL,
  `checkInDate` date NOT NULL,
  `checkOutDate` date NOT NULL,
  `user` int(11) NOT NULL,
  `price` decimal(7,2) NOT NULL,
  `roomNum` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `booking`
--

INSERT INTO `booking` (`reservationId`, `rId`, `quantity`, `checkInDate`, `checkOutDate`, `user`, `price`, `roomNum`) VALUES
(1, 3, 1, '2024-01-04', '2024-01-05', 2, '102.10', 'Q124'),
(2, 6, 1, '2024-10-12', '2024-10-23', 2, '3850.00', 'Q132'),
(3, 4, 1, '2024-01-11', '2024-01-13', 2, '300.00', 'Q125'),
(4, 1, 1, '2024-10-22', '2024-10-24', 2, '179.98', 'A101');

-- --------------------------------------------------------

--
-- Table structure for table `feedback`
--

CREATE TABLE `feedback` (
  `feedBackId` int(100) NOT NULL,
  `user` int(11) NOT NULL,
  `messages` varchar(255) NOT NULL,
  `date` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `feedback`
--

INSERT INTO `feedback` (`feedBackId`, `user`, `messages`, `date`) VALUES
(1, 2, 'Very Good', '2024-01-07 18:36:08');

-- --------------------------------------------------------

--
-- Table structure for table `reservation`
--

CREATE TABLE `reservation` (
  `reservationId` int(100) NOT NULL,
  `user` int(11) NOT NULL,
  `dateTime` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `reservation`
--

INSERT INTO `reservation` (`reservationId`, `user`, `dateTime`) VALUES
(1, 2, '2024-01-08 12:43:57'),
(2, 2, '2024-01-09 02:02:34'),
(3, 2, '2024-01-11 07:09:49'),
(4, 2, '2024-01-13 13:01:22');

-- --------------------------------------------------------

--
-- Table structure for table `room`
--

CREATE TABLE `room` (
  `roomId` int(11) NOT NULL,
  `roomNum` varchar(120) DEFAULT NULL,
  `rType` int(11) NOT NULL,
  `price` decimal(7,2) NOT NULL,
  `description` varchar(100) NOT NULL,
  `availability` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `room`
--

INSERT INTO `room` (`roomId`, `roomNum`, `rType`, `price`, `description`, `availability`) VALUES
(1, 'A101', 1, '89.99', 'Beach View, Aircond', 'Occupied'),
(2, 'Q123', 2, '90.99', 'Tower View, Aircond', 'YES'),
(3, 'Q124', 2, '102.10', 'Beach View, Private Pool, No Aircond', 'Occupied'),
(4, 'Q125', 2, '150.00', 'Aircond with Beach View and Pool', 'Occupied'),
(5, 'Q126', 2, '200.00', 'Aircond with beach view and indoor pool', 'YES'),
(6, 'Q132', 2, '350.00', 'Aircond, Tower View', 'Occupied'),
(7, 'S101', 3, '50.99', 'Aircond with normal view', 'YES'),
(8, 'M201', 1, '99.99', 'with pool', 'YES'),
(9, 'S201', 3, '89.90', 'With Aircond and Beach View', 'YES');

-- --------------------------------------------------------

--
-- Table structure for table `roomtypes`
--

CREATE TABLE `roomtypes` (
  `roomTypeId` int(11) NOT NULL COMMENT 'this is the unique identifier of the room',
  `type` varchar(255) NOT NULL,
  `capacity` int(100) NOT NULL,
  `description` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `roomtypes`
--

INSERT INTO `roomtypes` (`roomTypeId`, `type`, `capacity`, `description`) VALUES
(1, 'Master Room', 1, 'King Bed'),
(2, 'Queen Room', 2, 'Queen Bed'),
(3, 'Single Room', 2, 'Single Bed');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `userId` int(11) NOT NULL,
  `username` varchar(50) NOT NULL,
  `password` varchar(25) NOT NULL,
  `numIc` int(14) NOT NULL,
  `phoneNum` int(14) NOT NULL,
  `email` varchar(25) NOT NULL,
  `name` varchar(50) NOT NULL,
  `address` varchar(100) NOT NULL,
  `userType` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`userId`, `username`, `password`, `numIc`, `phoneNum`, `email`, `name`, `address`, `userType`) VALUES
(1, 'admin', 'sni1\\W', 0, 0, '', 'Admin', '', 'admin'),
(2, 'wana', 'sni1\\W', 2147483647, 133773474, 'wanahnaf07@gmail.com', 'Wan Ahnaf', 'Malacca', 'user'),
(3, 'ahnaf', 'sni1\\W', 2147483647, 133773474, 'wanahnaf@gmail.com', 'Wan Ahnaf', 'Durian Tunggal', 'user');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `booking`
--
ALTER TABLE `booking`
  ADD PRIMARY KEY (`reservationId`,`rId`,`user`) USING BTREE,
  ADD KEY `roomID` (`rId`,`user`) USING BTREE;

--
-- Indexes for table `feedback`
--
ALTER TABLE `feedback`
  ADD PRIMARY KEY (`feedBackId`,`user`) USING BTREE,
  ADD KEY `user` (`user`);

--
-- Indexes for table `reservation`
--
ALTER TABLE `reservation`
  ADD PRIMARY KEY (`reservationId`);

--
-- Indexes for table `room`
--
ALTER TABLE `room`
  ADD PRIMARY KEY (`roomId`) USING BTREE,
  ADD KEY `rType` (`rType`);

--
-- Indexes for table `roomtypes`
--
ALTER TABLE `roomtypes`
  ADD PRIMARY KEY (`roomTypeId`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`userId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `feedback`
--
ALTER TABLE `feedback`
  MODIFY `feedBackId` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `reservation`
--
ALTER TABLE `reservation`
  MODIFY `reservationId` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `room`
--
ALTER TABLE `room`
  MODIFY `roomId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `roomtypes`
--
ALTER TABLE `roomtypes`
  MODIFY `roomTypeId` int(11) NOT NULL AUTO_INCREMENT COMMENT 'this is the unique identifier of the room', AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `userId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
