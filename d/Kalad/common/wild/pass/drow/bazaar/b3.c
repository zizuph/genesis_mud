inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the bazaar, Undraeth");
   set_long("The bazaar of Undraeth.\n"+
      "This is the eastern edge of the bazaar in the very heart of the drow city of "+
      "Undraeth where merchants and traders from all over the Dark Dominion "+
      "may trade in relative safety. A myriad amount of colorful tents, "+
      "a few outlined in faerie fire lie all around you. The remainder of "+
      "the bazaar is to the northwest, west and southwest. In the east, a "+
      "dark and narrow street cleaves its way among the stalagmite buildings "+
      "of the city.\n"+
      "A tent lies before you, its flap open.\n");
   add_item(({"bazaar"}),
      "A bustling place filled with many drow, as well as a few non-drow.\n");
   add_item(({"drow city","city","undraeth"}),
      "The foreboding structures of stalagmites that serve as homes for the "+
      "drow rise menacingly around the edges of the bazaar, as if disapproving "+
      "of all within it.\n");
   add_item(({"colorful tents","tents","colorful tent"}),
      "Tents of all shapes, sizes and colors of the spectrum.\n");
   add_item(({"faerie fire","fire"}),
      "It glows in a soft, gentle fashion.\n");
   add_item(({"stalagmite buildings","buildings","building","stalagmites","stalagmite"}),
      "The dark, foreboding structures loom over the bazaar like a vulture "+
      "upon a hapless victim.\n");
   add_item(({"dark street","narrow street","street"}),
      "A thin line of darkness amidst the greater darkness of the city.\n");
   add_item(({"tent"}),
      "A grey leather tent, its top writhed with red faerie fire, making it "+
      "glow an eerie red.\n");
   add_item(({"flap"}),
      "It lies open, signalling an invitation to enter.\n");
   add_exit(CPASS(drow/bazaar/b5),"west");
   add_exit(CPASS(drow/bazaar/b2),"northwest");
   add_exit(CPASS(drow/d36),"east");
   add_exit(CPASS(drow/bazaar/b4),"southwest");
   set_noshow_obvious(1);
}
block()
{
   write("You try to go east, but are soon stopped by a large contingent "+
      "of drow soldiers. After a few tense moments, they allow you to return "+
      "back to the bazaar...unharmed.\n");
   say(QCTNAME(TP) + " tries to go east, but is soon stopped by a large "+
      "contingent of drow soldiers. After a few tense moments, they "+
      "allow " + TP->query_objective() + " to return back to the bazaar...unharmed.\n");
   return 1;
}
void
init()
{
   ::init();
   AA(enter,enter);
}
int
enter(string str)
{
   if(!str || str != "tent")
      {
      NF("Enter what? The tent perhaps?\n");
      return 0;
   }
   write("You duck your head and enter the tent.\n");
   set_alarm(1.0,0.0,"do_enter");
   return 1;
}
void
do_enter()
{
   TP->move_living("into the tent","/d/Kalad/common/wild/pass/drow/bazaar/armour_tent");
   return;
}
