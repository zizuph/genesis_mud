inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("mirage3");
   set_long("A mirage.\n");
   add_prop(OBJ_I_INVIS,100);
   set_no_show();
   set_alarm(15.0,0.0,"msg1");
}
msg1()
{
   TP->catch_msg("Small rivulets of blood pour from your eyes.\n");
   set_alarm(15.0,0.0,"msg2");
   return 1;
}
msg2()
{
   TP->catch_msg("An angry swarm of giant vultures appears in the "+
      "distant horizon...\n"+
      "They rapidly fly in your direction, screeching angrily!\n"+
      "Soon they are upon you, ripping and tearing the flesh from your bones!\n"+
      "All turns black as you die...\n");
   set_alarm(15.0,0.0,"msg3");
   return 1;
}
msg3()
{
   TP->catch_msg("A disembodied head floats past you.\n");
   set_alarm(15.0,0.0,"msg4");
   return 1;
}
msg4()
{
   TP->catch_msg("The sun slowly transforms into a huge red eye, which then blinks and becomes the sun again.\n");
   return 1;
}
