inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("mirage4");
   set_long("A mirage.\n");
   add_prop(OBJ_I_INVIS,100);
   set_no_show();
   set_alarm(15.0,0.0,"msg1");
}
msg1()
{
   TP->catch_msg("The wasteland before you blurs...\n"+
      "A city more majestic than any you've ever beheld lies before you, "+
      "wide avenues and grand marble buildings...\n"+
      "The city fades and is replaced with the wasteland.\n");
   set_alarm(15.0,0.0,"msg2");
   return 1;
}
msg2()
{
   TP->catch_msg("A dark cloud momentarily hangs over you...\n"+
      "You seem to hear voices from within calling out your name...\n"+
      "The cloud soon vanishes.\n");
   set_alarm(15.0,0.0,"msg3");
   return 1;
}
msg3()
{
   TP->catch_msg("A pool of water appears comes into view...\n"+
      "But disappears as soon as you take a step towards it.\n");
   set_alarm(15.0,0.0,"msg4");
   return 1;
}
msg4()
{
   TP->catch_msg("The heat of the sun suddenly increases tenfold!\n"+
      "Your skin begins to sizzle and crack!!\n"+
      "You collapse onto the ground, cringing in terrible agony!!!\n");
   return 1;
}
