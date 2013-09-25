<script language='javascript'>
  window.setTimeout('window.location.reload()',1000);
</script>

<?php
$connect = mysql_connect("localhost", "root", "비밀번호")
   or die("Connect Fail: " . mysql_error());
echo "Connect Success!";
mysql_select_db("rpidb") or die("Select DB Fail!");

$query = "select * from envdata order by time desc limit 10";
$result = mysql_query($query) or die("Query Fail: " . mysql_error());

echo "<table>\n";

echo "<tr><td>Time</td><td>TEM</td><td>HUM</td><td>ILL</td><td>MIC</td><td>FLA</td><td>ACX</td><td>ACY</td><td>ACZ</td><td>GAS</td><td>DIS</td><td>MOT</td></tr>";

while ($line = mysql_fetch_array($result, MYSQL_ASSOC)) {
   echo "\t<tr>\n";
   foreach ($line as $col_value) {
       echo "\t\t<td>$col_value</td>\n";
   }
   echo "\t</tr>\n";
}

echo "</table>\n";

mysql_free_result($result);

mysql_close($connect);
?>