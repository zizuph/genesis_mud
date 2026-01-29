inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("tell2");
   set_long("A tell.\n");
   add_prop(OBJ_I_INVIS,100);
   set_no_show();
   set_alarm(5.0,0.0,"msg1");
}
msg1()
{
   TP->catch_msg("The uneven sound of dripping water echoes weirdly in the passage.\n");
   set_alarm(30.0,0.0,"msg2");
   return 1;
}
msg2()
{
   TP->catch_msg("The moisture laden air seems to make breathing difficult.\n");
   set_alarm(30.0,0.0,"msg3");
   return 1;
}
msg3()
{
   TP->catch_msg("An indistinguishable sound echoes in the distance.\n");
   set_alarm(30.0,0.0,"msg4");
   return 1;
}
msg4()
{
   TP->catch_msg("A sound akin to splashing water can faintly be heard.\n");
   set_alarm(30.0,0.0,"msg5");
   return 1;
}
msg5()
{
   TP->catch_msg("A smell, like that of fish scales, reaches your nose.\n");
   return 1;
}
