<?php
$to = $_GET['to'];
$subject = "prova invio email";
$message = $_GET['msg'];
$headers = "From: hatyyys@hhhfffyyw.it/r/n";
mail ($to, $subject, $message, $headers);
?>
