/****************************************/
/*    Oak Room of Icewall Castle        */
/*       Coded by Stevenson             */
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit ICEINROOM;

static int open = 0;
string oaklong, button;
object tongs, fireplace, ember;

reset_icewall_room() {
   if (!tongs) {
      tongs = clone_object(ICE_CAST_O+"tongs");
      tongs->move(TO);
   }
   if (!fireplace) {
      fireplace = clone_object(ICE_CAST_O+"fireplace");
      fireplace->move(TO);
      ember = clone_object(ICE_CAST_O+"ember");
      ember->move(fireplace);
   }
   if (open) {
      tell_room(TO,"There is a soft whirring noise in the room.\n");
      remove_exit("east");
      open = 0;
   }
}

init() {
   ADD("press_button","press");
   ADD("press_button","push");
   ::init();
}

create_icewall_room()
{
   set_short("Oak Room");
   set_long(
      "This is the room where the owner obviously comes to relax. "
      + "The furniture in the room is made of solid oak with red "
      + "lining. There is a huge log fireplace on the east "
      + "wall that roars and gives off a brilliant heat. Just "
      + "above the fireplace is a mantlepiece covered with "
      + "intricately carved figurines. "
      + "The curtains on each of "
      + "the windows are drawn shut and no daylight appears to come "
      + "into the room. "
      + "\n");
   
   add_item("figurines","They are skillfully crafted carvings of "
      + "the kinds of animals you would find in Icewall.\n");
   add_item(({"fire","logs","log"}),
      "A roaring, hot fire provides the only light in the room.\n"
      + "");
   add_item("furniture",
      "Each piece of furniture is made of solid oak with red, "
      + "velvet lining.\n");
   add_item("curtains",
      "The curtains are made of red velvet and stop daylight coming "
      + "into the room.\n");
   add_item("mantlepiece","The mantle of the fireplace is made of polished "
      + "oak that seems to glow with an inner light. A knothole in the "
      + "wood does look kind of funny, though.\n");
   add_item(({"knothole","button"}),"The knothole is actually a small button.\n");
   
   add_exit(ICE_CAST1_R + "north_hall.c", "south");

   reset_icewall_room();
}

press_button(str)
{
   NF("What?\n");
   if (str != "button" && str != "knothole") return 0;
   
   if (!open)
      {
      write("You press the button and part of the wall starts to move "
         + "revealing a secret passage to the east.\n");
      say("Suddenly, you see a portion of the east wall slide away.\n");
      add_exit(ICE_CAST1_R+"secret1","east");
      open = 1;
      return 1;
   }
   write("Nothing happens.\n");
   return 1;
}
