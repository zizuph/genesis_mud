inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* Moisture messages here due to proximity to the Bay of Kabal */
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Black stone as lightless as the depths of the netherworld surrounds "+
      "you from every conceivable direction, trapping you in its cold and "+
      "unyielding embrace, like some musty, forgotten tomb. The sheer "+
      "immensity of rock that lies overhead seems to withdraw the very life "+
      "from you, leaving you a weak and debilitated shell. Here, the passage "+
      "bends ever so slightly, heading to the north and southeast.\n"+
      "The air here seems to be saturated with moisture.\n");
   add_item(({"passage"}),
      "A cramped tunnel far beneath the surface of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u45),"north",0,2,1);
   add_exit(CPASS(uc/u47),"southeast",0,2,1);
}
void
init()
{
   ::init();
   clone_object(CPASS(uc/obj/tell2))->move(TP,1);
}
leave_inv(ob, to)
{
   object msg;
   ::leave_inv(ob);
   msg = present("tell2",ob);
   if (msg) msg -> remove_object();
}
