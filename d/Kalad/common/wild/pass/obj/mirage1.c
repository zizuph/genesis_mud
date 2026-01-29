inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("mirage1");
   set_long("A mirage.\n");
   add_prop(OBJ_I_INVIS,100);
   set_no_show();
   set_alarm(15.0,0.0,"msg1");
}
msg1()
{
   TP->catch_msg("A small red worm crawls its way out of your nose...\n");
   set_alarm(15.0,0.0,"msg2");
   return 1;
}
msg2()
{
   TP->catch_msg("The world around you begins to spin around and around...\n");
   set_alarm(15.0,0.0,"msg3");
   return 1;
}
msg3()
{
   TP->catch_msg("A haunting apparition of a small child appears before "+
      "you...then vanishes from sight.\n");
   set_alarm(15.0,0.0,"msg4");
   return 1;
}
msg4()
{
   TP->catch_msg("Small furry spiders begin crawling all over you!\n");
   return 1;
}
