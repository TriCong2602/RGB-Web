<?php
// Connect to database
$server = "localhost";
$user = "cas"; 
$pass = "123456";
$dbname = "ledControl";

$conn = mysqli_connect($server,$user,$pass,$dbname);

// Check connection
if($conn === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}


?>