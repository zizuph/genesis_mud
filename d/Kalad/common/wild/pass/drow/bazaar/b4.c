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
      "You are presently in the southern side of the bazaar, located in the "+
      "center of the city of Undraeth. Here, and nowhere else in this twisted "+
      "city of drow, a merchant or trader may come and trade in goods "+
      "with relative safety, for this place is a common trading place for "+
      "various races within the Dark Dominion. Many colorful tents lie "+
      "scattered all around you, while the remainder of the bazaar lies just "+
      "to the northwest, north and northeast.\n"+
      "A tent lies before you, its flap invitingly open.\n");
   add_item(({"tent"}),
      "A dark blue canvas tent, its flap is open.\n");
   add_item(({"flap"}),
      "It has been pulled back, inviting you to enter the tent.\n");
   add_item(({"bazaar"}),
      "A bustling area of trade and commerce within Undraeth.\n");
   add_item(({"city","undraeth"}),
      "A teeming city of thousands of drow, where love and war are commonplace "+
      "events, all done for the glory of Lolth, the Spider Queen.\n");
   add_item(({"colorful tents","tents","colorful tent"}),
      "Of all sizes, descriptions and colors, they fill the entirety of the "+
      "bazaar.\n");
   add_exit(CPASS(drow/bazaar/b1),"northwest");
   add_exit(CPASS(drow/bazaar/b5),"north");
   add_exit(CPASS(drow/bazaar/b3),"northeast");
   set_noshow_obvious(1);
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
   if(!str || str !="tent")
      {
      NF("Enter what? The tent maybe?\n");
      return 0;
   }
   write("You duck your head and enter the tent.\n");
   set_alarm(1.0,0.0,"do_enter");
   return 1;
}
void
do_enter()
{
   TP->move_living("into the tent","/d/Kalad/common/wild/pass/drow/bazaar/weapon_tent");
   return;
}
