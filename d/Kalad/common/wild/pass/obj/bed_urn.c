inherit "/std/container";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_container()
{
   set_name("urn of rata");
   add_name("urn");
   set_short("urn of Rata");
   set_pshort("urns of Rata");
   set_long("An ancient-looking urn fashioned from bronze. Intricate "+
      "images depict a man bearing the urn against a being of fiery origin. "+
      "The outcome of the confrontation is unknown to you, for the last "+
      "image has faded with age.\n");
   add_prop(CONT_I_WEIGHT,5000);
   add_prop(CONT_I_MAX_WEIGHT,15000);
   add_prop(CONT_I_VOLUME,5000);
   add_prop(CONT_I_MAX_VOLUME,15000);
   add_prop(OBJ_M_NO_SELL,"The value of the urn goes far beyond anything the "+
      "shopkeeper could ever give you.\n");
   add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }) );
   add_prop(CONT_M_NO_REM,1);
   make_water();
}

make_water()
{
   
   object water;
   int n;
   
   seteuid(getuid(TO));
   for (n=0;n < 1;n++)
   {
      water = clone_object("/d/Kalad/common/wild/pass/obj/water");
      water -> move(TO);
   }
   
}
void
init()
{
   ::init();
   AA(pour,pour);
}
int
pour(string str)
{
   if(!str || str != "water")
      {
      NF("Pour what?\n");
      return 0;
   }
   write("You pour out some of the water from the urn.\n");
   say(QCTNAME(TP) + " pours out some of the water from the urn.\n");
   set_alarm(2.0,0.0,"water_effect");
   return 1;
}
water_effect()
{
    object efreeti;
 
   write("The water touches the ground and instantly becomes a huge "+
      "wave that crashes into everything before you!\n");
   say("The water touches the ground and instantly becomes a huge wave "+
      "that crashes into everything, including you!\n");
    efreeti = present("efreeti", environment(environment(TO)));
    if (efreeti)
    {
        efreeti->banished();
    }
   return;
}
