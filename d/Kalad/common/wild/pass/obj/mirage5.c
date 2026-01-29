inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("mirage5");
   set_long("A mirage.\n");
   add_prop(OBJ_I_INVIS,100);
   set_no_show();
   set_alarm(15.0,0.0,"msg1");
}
msg1()
{
   TP->catch_msg("A horrible spherical-shaped beast with many long, snake-like "+
      "stalkes sprouting from it comes into view. With even greater horror "+
      "you note the eyes at the end of each stalk and the great eye at its "+
      "very center.\n"+
      "You try to move but find that you cannot...\n"+
      "You realize it has teeth also...very sharp teeth.\n"+
      "All becomes black as it approaches you.\n");
   set_alarm(15.0,0.0,"msg2");
   return 1;
}
msg2()
{
   TP->catch_msg("A rotting corpse arrives before you.\n"+
      "The corpse approaches and with great horror you realize it has your "+
      "face!\n"+
      "The image fades from your mind.\n");
   set_alarm(15.0,0.0,"msg3");
   return 1;
}
msg3()
{
   TP->catch_msg("The air before you wavers and shifts...\n");
   set_alarm(15.0,0.0,"msg4");
   return 1;
}
msg4()
{
   TP->catch_msg("Rain begins falling down upon you...but instead of "+
      "cooling you, it acts like acid...and slowly begins dissolving the "+
      "flesh from your bones. You watch in fascination as all the flesh "+
      "from your body dissolves, leaving nothing but a bone-white skeleton...\n");
   return 1;
}
