inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("mirage2");
   set_long("A mirage.\n");
   add_prop(OBJ_I_INVIS,100);
   set_no_show();
   set_alarm(15.0,0.0,"msg1");
}
msg1()
{
   TP->catch_msg("The sky suddenly darkens, and small frogs and toads "+
      "begin raining down upon you.\n");
   set_alarm(15.0,0.0,"msg2");
   return 1;
}
msg2()
{
   TP->catch_msg("The desolate landscape before you suddenly becomes an "+
      "immense lake...you fall inside!\n"+
      "Water begins to fill your lungs!!\n"+
      "You are dying!!!\n");
   set_alarm(15.0,0.0,"msg3");
   return 1;
}
msg3()
{
   TP->catch_msg("A man swathed from head to toe in white robes appears "+
      "before you...then walks straight through you and vanishes!\n");
   set_alarm(15.0,0.0,"msg4");
   return 1;
}
msg4()
{
   TP->catch_msg("The sun seems to slowly darken...then fade from sight.\n");
   return 1;
}
