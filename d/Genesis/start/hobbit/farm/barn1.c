/*
 *  The barn on the yard of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

void add_stuff();
void reset_room()
{
   add_stuff();
}
object stool;
create_room() 
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Barn");
   set_long(
      "You have entered a big barn. All kinds of sounds are coming from "
    + "all directions. The sounds of chickens is coming from the east, "
    + "west you hear pigs and piglets squealing, while south the "
    + "moohs of cows can be heard. North you can leave this barn.\n");

   add_exit(STAND_DIR + "yard7","north");
   add_exit(STAND_DIR + "barn2","east");
   add_exit(STAND_DIR + "barn3","south");
   add_exit(STAND_DIR + "barn4","west");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   reset_room();
}

void
add_stuff()
{
   if(!present("stool"))
   {
    stool = clone_object("/d/Shire/common/obj/stool");
   stool->move(this_object());
   }

}