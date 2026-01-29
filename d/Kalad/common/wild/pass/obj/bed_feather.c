inherit "/std/object.c";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   ::create_object();
   set_name("sacredfeatherofnathla");
   add_name("feather");
   add_name("sacred feather of nathla");
   add_name("sacred feather");
   add_name("feather of nathla");
   set_short("sacred feather of Nathla");
   set_pshort("sacred feathers of Nathla");
   set_long("An incredibly long and thin feather, whose myriad colors "+
      "swirl incandescently in even the slightest of lights. It seems to "+
      "radiate an inner light.\n");
   add_prop(OBJ_M_NO_SELL,"This feather is sacred, it cannot be sold!\n");
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_VOLUME,250);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_LIGHT,1);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }) );
}
void
init()
{
   ::init();
   AA(wave,wave);
}
int
wave(string str)
{
   if(!str || str != "feather")
      {
      NF("You can't wave a '" + str + "'.\n");
      return 0;
   }
   write("You wave the feather ever so slightly.\n");
   say(QCTNAME(TP) + " waves the feather ever so slightly.\n");
   set_alarm(3.0,0.0,"effect");
   return 1;
}
void
effect()
{
    object dao;
 
   write("An incredibly strong gust of wind rushes forth from the feather.\n");
   say("An incredible strong gust of wind rushes forth from the feather.\n");
    dao = present("dao", environment(environment(TO)));
   if (dao)
   {
       dao->banished();
   }
   return;
}
