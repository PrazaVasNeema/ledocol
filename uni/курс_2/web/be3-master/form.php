<!DOCTYPE html>
<html lang="ru">

  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Задание 3</title>
    <link rel="stylesheet" href="style.css">
    <script src="script.js"></script>
  </head>
  <body>
      <header>
        <p class="header-text">my form</p>
      </header>
      <main>
        <div>
                <form action="" method="POST">
                <label>
                  Имя<br />
                  <input name="fio"
                    value="Иван"/>
                </label><br />
        
                <label>
                  E-mail:<br />
                  <input name="email"
                    value="email@example.com"
                    type="email" />
                </label><br />
        
                <label>
                  Дата рождения:<br />
                  <input name="birthday"
                    value="2000-01-01"
                    type="date" />
                </label><br />
        
                Пол:<br />
                <label><input type="radio" checked="checked"
                  name="gender" value="Male" />
                  мужской
                </label>
                <label><input type="radio"
                  name="gender" value="Female" />
                  женский
                </label>
                <label><input type="radio"
                  name="gender" value="Other" />
                  другое
                </label>
                <br />
        
                Количество конечностей:<br />
                <label><input type="radio"
                  name="limbs" value="0" />
                  0
                </label>
                <label><input type="radio"
                  name="limbs" value="1" />
                  1
                </label>
                <label><input type="radio"
                  name="limbs" value="2" />
                  2
                </label>
                <label><input type="radio"
                  name="limbs" value="3" />
                  3
                </label>
                <label><input type="radio" checked="checked"
                  name="limbs" value="4" />
                  4
                </label>
                <label><input type="radio"
                  name="limbs" value="5+" />
                  5+
                </label>
                <br />
        
                <label>
                  Сверхспособности:
                  <br />
                  <select name="ability[]"
                    multiple="multiple">
                    <option value="0">Летать</option>
                    <option value="1" selected="selected">Читать</option>
                    <option value="2" selected="selected">Писать</option>
                  </select>
                </label><br />
        
                <label>
                  Биография:<br />
                  <textarea name="biography">...</textarea>
                </label><br />
        
                <br />
                <label><input type="checkbox"
                  name="contract" />
                  С контрактом ознакомлен
                </label><br />
                
                <input id="submit" type="submit" value="ok" />
              </form>
          </div>
      </main>
      
  </body>

</html>