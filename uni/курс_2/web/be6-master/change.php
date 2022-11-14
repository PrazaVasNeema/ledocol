<?php
header('Content-Type: text/html; charset=UTF-8');
$user = 'u20945';
$pass = '1388111';
  $db = new PDO('mysql:host=localhost;dbname=u20945', $user, $pass, array(PDO::ATTR_PERSISTENT => true));

session_start();
$id = $_POST['change'];
$stmt = $db->prepare("SELECT login_id FROM login_data WHERE user_id = '$id'");
$stmt->execute();
$row = $stmt->fetch();
if($row==false){
    header('Location:admin.php');
    exit();
}
$user_login=$row['login_id'];

$_SESSION['login'] = $user_login;
$_SESSION['uid'] = $id;

setcookie('admin','1');
header('Location: index.php');
