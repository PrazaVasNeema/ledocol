<?php
// Отправляем браузеру правильную кодировку,
// файл index.php должен быть в кодировке UTF-8 без BOM.

header('Content-Type: text/html; charset=UTF-8');

// В суперглобальном массиве $_SERVER PHP сохраняет некторые заголовки запроса HTTP
// и другие сведения о клиненте и сервере, например метод текущего запроса $_SERVER['REQUEST_METHOD'].
if ($_SERVER['REQUEST_METHOD'] == 'GET') {
  // В суперглобальном массиве $_GET PHP хранит все параметры, переданные в текущем запросе через URL.
  if (!empty($_GET['save'])) {
    // Если есть параметр save, то выводим сообщение пользователю.
    $txt="Спасибо, результаты сохранены.";
    print"<div>" . $txt . "<div>";
  }
  // Включаем содержимое файла form.php.
  include('form.php');
  // Завершаем работу скрипта.
  exit();
}
// Иначе, если запрос был методом POST, т.е. нужно проверить данные и сохранить их в XML-файл.

// Проверяем ошибки.
$errors = FALSE;
if (empty($_POST['fio'])) {
  print('Заполните имя.<br/>');
  $errors = TRUE;
}

if (!preg_match('/^[a-zA-Z0-9]+@[a-zA-Z0-9]+\.[a-zA-Z0-9]+$/', $_POST['email'])) {
  print('Заполните почту.<br/>');
  $errors = TRUE;
}

if (empty($_POST['biography'])) {
  print('Заполните биографию.<br/>');
  $errors = TRUE;
}
if (!isset($_POST['contract'])) {
  print('Ознакомьтесь с контрактом.<br/>');
  $errors = TRUE;
}
if (!isset($_POST['gender'])) {
  print('Выберете гендер.<br/>');
  $errors = TRUE;
}
if (!isset($_POST['limbs'])) {
  print('Выберете количество конечностей.<br/>');
  $errors = TRUE;
}
if (!isset($_POST['ability'])) {
  print('Выберете хотя бы одну способность.<br/>');
  $errors = TRUE;
}

// *************
// Тут необходимо проверить правильность заполнения всех остальных полей.
// *************

if ($errors) {
  // При наличии ошибок завершаем работу скрипта.
  exit();
}

// Сохранение в базу данных.

$user = 'u20945';
$pass = '1388111';
$db = new PDO('mysql:host=localhost;dbname=u20945', $user, $pass, array(PDO::ATTR_PERSISTENT => true));


// Подготовленный запрос. Не именованные метки.
try {
  $stmt = $db->prepare("INSERT INTO user SET fio = ?, user_email = ?, user_birthday = ?, user_gender = ? , user_limb_count = ?, user_biography = ?");
  $stmt -> execute([$_POST['fio'],$_POST['email'],$_POST['birthday'],$_POST['gender'],$_POST['limbs'],$_POST['biography']]);

  $stmt2 = $db->prepare("INSERT INTO link SET userr_id= ?, abil_id = ?");
  $id = $db->lastInsertId();
  foreach ($_POST['ability'] as $s)
    $stmt2 -> execute([$id, $s]);
}
catch(PDOException $e){
  print('Error : ' . $e->getMessage());
  exit();
}

//  stmt - это "дескриптор состояния".

//  Именованные метки.
//$stmt = $db->prepare("INSERT INTO test (label,color) VALUES (:label,:color)");
//$stmt -> execute(array('label'=>'perfect', 'color'=>'green'));

//Еще вариант
/*$stmt = $db->prepare("INSERT INTO users (firstname, lastname, email) VALUES (:firstname, :lastname, :email)");
$stmt->bindParam(':firstname', $firstname);
$stmt->bindParam(':lastname', $lastname);
$stmt->bindParam(':email', $email);
$firstname = "John";
$lastname = "Smith";
$email = "john@test.com";
$stmt->execute();
*/

// Делаем перенаправление.
// Если запись не сохраняется, но ошибок не видно, то можно закомментировать эту строку чтобы увидеть ошибку.
// Если ошибок при этом не видно, то необходимо настроить параметр display_errors для PHP.
header('Location: ?save=1');
