inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
object ob1;
/* Moisture messages here due to proximity to the Bay of Kabal */
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Black stone, as stygion as the nether reaches of the lower planes, "+
      "fills your entire field of vision, encompassing you in its embrace "+
      "of coldness, of lifelessness. The presence of thousands of tons of "+
      "rock over you nearly leaves you weakened and completely vulnerable. "+
      "The passage you have been travelling in curves from the northwest "+
      "to the south.\n"+
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
   add_exit(CPASS(uc/u46),"northwest",0,2,1);
   add_exit(CPASS(uc/u48),"south",0,2,1);
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
