<?php
$id = $_POST['delete'];
$user = 'u20945';
$pass = '1388111';
  $db = new PDO('mysql:host=localhost;dbname=u20945', $user, $pass, array(PDO::ATTR_PERSISTENT => true));
$req = "DELETE FROM link WHERE userr_id='$id'";
$res = $db->prepare($req);
$res->execute();
$req = "DELETE FROM login_data WHERE user_id='$id'";
$res = $db->prepare($req);
$res->execute();
$req = "DELETE FROM user WHERE user_id='$id'";
$res = $db->prepare($req);
$res->execute();
header('Location:admin.php');
