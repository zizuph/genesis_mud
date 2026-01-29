
#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/money.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

object money;
int wiped_before;

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Buckleberry's stables");
   set_long("You are inside Buckleberry's stables. This is where "
    + "Buckleberry takes care of his beloved ponies. The stables "
    + "have lots of straw lying on the floor.\n");

   add_exit(STAND_DIR + "bw_road6", "north", 0);

   add_item("floor", "The floor is covered with straw. Actually, you cannot quite see the "
    + "floor. Maybe you can see it if you wipe some of the straw off it.\n");

   add_item("straw",
      "The strong odor of the straw penetrates the whole stable. "
    + "It is strewn all across the floor, to make life more comfortable "
    + "for the ponies.\n");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   wiped_before = 0;
}

reset_room() {
   wiped_before = 0;
}

init() {
   ::init();
   add_action("do_wipe","wipe",0);
}

do_wipe(str) {
   if(str == "straw" || str == "straw away")
   {
      if(wiped_before)
         write("You wipe the straw away, but find nothing.\n");
      else
      {
         write("You wipe the straw away, and find some lost money!\n");
         money = MONEY_MAKE_GC(5+random(5));
         if(money)
            money->move(this_object());
         wiped_before = 1;
      }
      say(QCTNAME(this_player()) + " wipes some straw away.\n");
      return 1;
   }
}