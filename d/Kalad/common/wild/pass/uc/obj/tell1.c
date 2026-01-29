inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("tell1");
   set_long("A tell.\n");
   add_prop(OBJ_I_INVIS,100);
   set_no_show();
   set_alarm(5.0,0.0,"msg1");
}
msg1()
{
   TP->catch_msg("A putrid odor penetrates your nasal cavity.\n");
   set_alarm(30.0,0.0,"msg2");
   return 1;
}
msg2()
{
   TP->catch_msg("Something rotten reaches your nose.\n");
   set_alarm(30.0,0.0,"msg3");
   return 1;
}
msg3()
{
   TP->catch_msg("A smell akin to that of a wet dog reaches your nose.\n");
   set_alarm(30.0,0.0,"msg4");
   return 1;
}
msg4()
{
   TP->catch_msg("A horrible odor reaches your nostrils, nearly causing you to hurl the contents "+
      "of your stomach.\n");
   set_alarm(30.0,0.0,"msg5");
   return 1;
}
msg5()
{
   TP->catch_msg("You are nearly overcome by the terrible smell here, luckily you "+
      "manage to keep yourself from fainting.\n");
   return 1;
}
