<?php
// 實際上，.php 的檔案內容，其實也是網頁的程式碼。
// 在 PHP 程式語言的語法當中，所有變數名稱，皆是錢字符號開頭的。

// $servername = 'localhost';
// $username = 'jack';
// $password = 'good1234';
// $dbname = 'button_on_off';

$servername = 'localhost';
$username = 'admin';
$password = '1234';
$dbname = 'button_on_off';

$conn = mysqli_connect($servername, $username, $password, $dbname);
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>新增一筆資料錄，到特定資料庫中的特定資料表裡面。</title>
    <style>
      table
      {
        font-family: arial, sans-serif;
        border-collapse: collapse;
        width: 100%;
      }

      td, th
      {
        border: 1px solid #dddddd;
        text-align: left;
        padding: 8px;
      }

      tr:nth-child(even)
      {
        background-color: #dddddd;
      }
    </style>
  </head>
  <body>
    <?php
      // 此條件敘述是用來判斷該連線是不是失敗了？！
      if (! $conn) 
      {
         // 在 PHP 程式語言當中，是透過英文句點的符號，將兩個字串，加以銜接起來。
        die('連線失敗: ' . mysqli_connect_error());
      }
      else
      {
        echo "連線成功( ^_^/ )<p></p>\n";
      }

      // http://localhost/database_related/examples/basic17.php?radius_text=16&height_text=18
      //使用上面網址測試
      // $current_radius = $_REQUEST['radius_text'];
      // $current_height = $_REQUEST['height_text'];
      // $current_result = $_REQUEST['message_box02'];

      // date_default_timezone_set("Asia/Taipei");
      // $date_string = date("Y-m-d H:i:s");

      $current_result = $_REQUEST['current_state'];
      $device = $_REQUEST['device_name'];

      // $sql = 'SELECT id, radius, height, result FROM cylinder WHERE id = 2;';
      // $sql = 'SELECT id, radius, height, result FROM cylinder;';
      // $sql = "SELECT id, radius, height, result FROM cylinder WHERE radius = '$current_radius' AND height = '$current_height';";
      
      date_default_timezone_set("Asia/Taipei");
      $date_string = date("Y-m-d H:i:s");

      $sql = "INSERT INTO switch (current_state, device_name, upload_time) VALUES ('$current_result', '$device', '$date_string');";//改

      /*函數執行某個針對數據庫的查詢
      (
      必需。规定要使用的 MySQL 连接,
      必需，规定查询字符串,
      可选。一个常量。可以是下列值中的任意一个： 
      1.MYSQLI_USE_RESULT（如果需要检索大量数据，请使用这个
      2.MYSQLI_STORE_RESULT（默认）
      )*/
      $output = mysqli_query($conn, $sql);

      //函數返回結果集中的行數。
      if ($output)
      {
        echo '成功新增了此筆資料錄！';
      }
      else
      {
        echo '無法新增此筆資料錄...。';
      }

      mysqli_close($conn);
    ?>
  </body>
</html>