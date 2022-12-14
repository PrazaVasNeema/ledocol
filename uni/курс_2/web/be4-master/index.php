<?php
// Отправляем браузеру правильную кодировку,
// файл index.php должен быть в кодировке UTF-8 без BOM.

header('Content-Type: text/html; charset=UTF-8');

// В суперглобальном массиве $_SERVER PHP сохраняет некторые заголовки запроса HTTP
// и другие сведения о клиненте и сервере, например метод текущего запроса $_SERVER['REQUEST_METHOD'].
if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    // Массив для временного хранения сообщений пользователю.
    $messages = array();
    $messages[8] = '';
    // В суперглобальном массиве $_COOKIE PHP хранит все имена и значения куки текущего запроса.
    // Выдаем сообщение об успешном сохранении.
    if (!empty($_COOKIE['save'])) {
      // Удаляем куку, указывая время устаревания в прошлом.
      setcookie('save', '', 100000);
      // Если есть параметр save, то выводим сообщение пользователю.
      $messages[8] = '<div style="text-align: center; margin: 4px;">Спасибо, результаты сохранены.</div>';
    }
  
    // Складываем признак ошибок в массив.
    $errors = array();
    $errors['fio'] = !empty($_COOKIE['fio_error']);
    $errors['email'] = !empty($_COOKIE['email_error']);
    $errors['birthday'] = !empty($_COOKIE['birthday_error']);
    $errors['gender'] = !empty($_COOKIE['gender_error']);
    $errors['limbs'] = !empty($_COOKIE['limbs_error']);
    $errors['biography'] = !empty($_COOKIE['biography_error']);

    $errors['ability'] = !empty($_COOKIE['ability_error']);
    $errors['contract'] = !empty($_COOKIE['contract_error']);

    // TODO: аналогично все поля.
  
    // Выдаем сообщения об ошибках.
    if ($errors['fio']) {
      // Удаляем куку, указывая время устаревания в прошлом.
      setcookie('fio_error', '', 100000);
      // Выводим сообщение.
      $messages[0] = '<div class="error_text">Поле с именем не должно быть пустым.</div>';
    }
    if ($errors['email']) {
        // Удаляем куку, указывая время устаревания в прошлом.
        setcookie('email_error', '', 100000);
        // Выводим сообщение.
        $messages[1] = '<div class="error_text">Заполните почту в формате email@example.com.</div>';
    }
    if ($errors['birthday']) {
        // Удаляем куку, указывая время устаревания в прошлом.
        setcookie('birthday_error', '', 100000);
        // Выводим сообщение.
        $messages[2] = '<div class="error_text">Выберите дату.</div>';
    }
    if ($errors['gender']) {
      // Удаляем куку, указывая время устаревания в прошлом.
      setcookie('gender_error', '', 100000);
      // Выводим сообщение.
      $messages[3] = '<div class="error_text">Выберите свой гендер.</div>';
  }
  if ($errors['limbs']) {
    // Удаляем куку, указывая время устаревания в прошлом.
    setcookie('limbs_error', '', 100000);
    // Выводим сообщение.
    $messages[4] = '<div class="error_text">Выберите количество конечностей.</div>';
  }
    if ($errors['biography']) {
      // Удаляем куку, указывая время устаревания в прошлом.
      setcookie('biography_error', '', 100000);
      // Выводим сообщение.
      $messages[6] = '<div class="error_text">Поле с биографией не должно быть пустым.</div>';
    }
    if ($errors['ability']) {
      // Удаляем куку, указывая время устаревания в прошлом.
      setcookie('ability_error', '', 100000);
      // Выводим сообщение.
      $messages[5] = '<div class="error_text">Должна быть выбрана хотя бы одна способность.</div>';
    }
    if ($errors['contract']) {
      // Удаляем куку, указывая время устаревания в прошлом.
      setcookie('contract_error', '', 100000);
      // Выводим сообщение.
      $messages[7] = '<div class="error_text">Вы должны согласиться с условиями , прежде чем продолжить.</div>';
    }
  

    // TODO: тут выдать сообщения об ошибках в других полях.
    // Складываем предыдущие значения полей в массив, если есть.
    $values = array();
    $values['fio'] = empty($_COOKIE['fio_value']) ? '' : $_COOKIE['fio_value'];
    $values['email'] = empty($_COOKIE['email_value']) ? '' : $_COOKIE['email_value'];
    $values['birthday'] = empty($_COOKIE['birthday_value']) ? '' : $_COOKIE['birthday_value'];
    $values['gender'] = empty($_COOKIE['gender_value']) ? '' : $_COOKIE['gender_value'];
    $values['limbs'] = empty($_COOKIE['limbs_value']) ? '' : $_COOKIE['limbs_value'];
    $values['biography'] = empty($_COOKIE['biography_value']) ? '' : $_COOKIE['biography_value'];

    $ability = array();
    $ability = empty($_COOKIE['ability_values']) ? array() : unserialize($_COOKIE['ability_values'], ["allowed_classes" => false]);
    // TODO: аналогично все поля.
    // Включаем содержимое файла form.php.
    // В нем будут доступны переменные $messages, $errors и $values для вывода 
    // сообщений, полей с ранее заполненными данными и признаками ошибок.
    include('form.php');
  }

// Иначе, если запрос был методом POST, т.е. нужно проверить данные и сохранить их в XML-файл.

// Иначе, если запрос был методом POST, т.е. нужно проверить данные и сохранить их в XML-файл.
else {
    // Проверяем ошибки.
    $errors = FALSE;
    if (empty($_POST['fio'])) {
      // Выдаем куку на день с флажком об ошибке в поле fio.
      setcookie('fio_error', '1', time() + 24 * 60 * 60);
      $errors = TRUE;
    }
    else {
      // Сохраняем ранее введенное в форму значение на месяц.
      setcookie('fio_value', $_POST['fio'], time() + 30 * 24 * 60 * 60);
    }
    if (!preg_match('/^[a-zA-Z0-9]+@[a-zA-Z0-9]+\.[a-zA-Z0-9]+$/', $_POST['email'])) {
        setcookie('email_error', '1', time() + 24 * 60 * 60);
        $errors = TRUE;
      }
    else{
        setcookie('email_value', $_POST['email'], time() + 30 * 24 * 60 * 60);
    }
    if (empty($_POST['birthday'])) {
        // Выдаем куку на день с флажком об ошибке в поле birthday.
        setcookie('birthday_error', '1', time() + 24 * 60 * 60);
        $errors = TRUE;
      }
      else {
        // Сохраняем ранее введенное в форму значение на месяц.
        setcookie('birthday_value', $_POST['birthday'], time() + 30 * 24 * 60 * 60);
      }
    if (!isset($_POST['gender'])) {
      // Выдаем куку на день с флажком об ошибке в поле fio.
      setcookie('gender_error', '1', time() + 24 * 60 * 60);
      $errors = TRUE;
    }
    else {
      // Сохраняем ранее введенное в форму значение на месяц.
      setcookie('gender_value', $_POST['gender'], time() + 30 * 24 * 60 * 60);
    }
    if (!isset($_POST['limbs'])) {
      // Выдаем куку на день с флажком об ошибке в поле fio.
      setcookie('limbs_error', '1', time() + 24 * 60 * 60);
      $errors = TRUE;
    }
    else {
      // Сохраняем ранее введенное в форму значение на месяц.
      setcookie('limbs_value', $_POST['limbs'], time() + 30 * 24 * 60 * 60);
    }
    if (empty($_POST['biography'])) {
      // Выдаем куку на день с флажком об ошибке в поле fio.
      setcookie('biography_error', '1', time() + 24 * 60 * 60);
      $errors = TRUE;
    }
    else {
      // Сохраняем ранее введенное в форму значение на месяц.
      setcookie('biography_value', $_POST['biography'], time() + 30 * 24 * 60 * 60);
    }

    if (!isset($_POST['ability'])) {
      // Выдаем куку на день с флажком об ошибке в поле fio.
      setcookie('ability_error', '1', time() + 24 * 60 * 60);
      $errors = TRUE;
    }
    else {
      
      setcookie('ability_values', serialize($_POST['ability']), time() + 30 * 24 * 60 * 60);
    }
    if (!isset($_POST['contract'])) {
      setcookie('contract_error', '1', time() + 24 * 60 * 60);
      $errors = TRUE;
    }

  // *************
  // TODO: тут необходимо проверить правильность заполнения всех остальных полей.
  // Сохранить в Cookie признаки ошибок и значения полей.
  // *************




// *************
// Тут необходимо проверить правильность заполнения всех остальных полей.
// *************

if ($errors) {
    // При наличии ошибок перезагружаем страницу и завершаем работу скрипта.
    header('Location: index.php');
    exit();
  }
  else {
    // Удаляем Cookies с признаками ошибок.
    setcookie('fio_error', '', 100000);
    setcookie('email_error', '', 100000);
    setcookie('birthday_error', '', 100000);
    setcookie('gender_error', '', 100000);
    setcookie('limbs_error', '', 100000);
    setcookie('ability_error', '', 100000);
    setcookie('biography_error', '', 100000);
    setcookie('contract_error', '', 100000);
    // TODO: тут необходимо удалить остальные Cookies.
  }

// Сохранение в базу данных.
// Сохранение в XML-документ.

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
 

// Делаем перенаправление.
// Если запись не сохраняется, но ошибок не видно, то можно закомментировать эту строку чтобы увидеть ошибку.
// Если ошибок при этом не видно, то необходимо настроить параметр display_errors для PHP.

// Сохраняем куку с признаком успешного сохранения.
setcookie('save', '1');

header('Location: ?save=1');
}