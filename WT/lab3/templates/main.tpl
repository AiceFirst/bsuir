<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html lang="ru" xml:lang="ru" xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <meta http-equiv="content-type" content="text/html;charset=windows-1251" />
   <title>Основы создания сайтов</title>
   <META content="{HEADER_DESCRIPTION}" name="description">
   <META content="{HEADER_KEYWORDS}" name="keywords">
   <link href="css/basic.css" rel="stylesheet" type="text/css" media="all" />

 </head>

<body>
<table width="100%" border="0" bgcolor="#a8ddff" class="globaltable" cellspacing="0" cellpadding="0">
 {LOGO}
 <tr>
  <td align="left" valign="top" width="16%" class="menutd" rowspan="2">
	<center>
<br>
   Сейчас: {TODAY_D}.{TODAY_M}.{TODAY_Y} {NOW_H}:{NOW_M}:{NOW_S}

</center>
   {MAIN_MENU}

  <form action="#" method="post">
  <table border="0" width="100%" align="center">
   <tr bgcolor="#0400b0" height="1">

    <td colspan="2"></td>
   </tr>
   <tr height="5">
    <td colspan="2"></td>
   </tr>
   <tr>
    <td align="right" valign="middle"><b>Логин:</b>&nbsp;</td>
    <td align="left"><input type="text" size="10" name="ulogin" class="formf1" /></td>

   </tr>
   <tr>
    <td align="right" valign="middle"><b>Пароль:</b>&nbsp;</td>
    <td align="left"><input type="password" size="10" name="upassword" class="formf1" /></td>
   </tr>
   <tr>
    <td>&nbsp;</td>
    <td align="left"><input type="submit" name="go" value="Войти" class="formf1" /></td>

   </tr>
  </table>
  </form>

  </td>


  <td width="80%" >
   <!-- inner table for main only -->
    <table border="0" width="100%" cellspacing="5" cellpadding="5">

     <tr>
      <td id="textt" bgcolor="{main_color}">
       {text}

      </td>
      <td width="30%">
       {news}

      </td>
     </tr>
    </table>
  </td>
 </tr>

 <tr>
  <td align="center" width="80%" bgcolor="{copyright_color}"  class="bottomline">
   &copy; 2007-2008, Название фирмы.<br />

   Тел. 111-22-33, адрес: ул. Имени-кого-то, дом.999
  </td>
 </tr>


 <tr>
  <td align="center" valign="top" bgcolor="#cdebff" width="100%" colspan="2">
   <img src="images/1.bmp"> <img src="images/2.gif"> <img src="images/3.bmp">
  </td>

 </tr>
</table>

</body>
</html>

