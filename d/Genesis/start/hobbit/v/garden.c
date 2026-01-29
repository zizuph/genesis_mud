/*
 *  Garden 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

public void
create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Garden");
   set_long("You have entered a garden with beautiful flowers, big trees "
    + "and nice smelling shrubberies. This garden is maintained by "
    + "the citizens of Hobbiton, so they can proudly walk around "
    + "and relax in it. To the east is Hill lane, and to the "
    + "north is the shore of the river Bywater.\n");

   add_item(({"flower","flowers"}), 
      "There are many different colours of flowers here. Almost too many "
    + "to count. Most of the flowers have a pleasant smell, filling the "
    + "air with a refreshing odour.\n");

   add_item(({"tree","trees"}), 
      "The big trees seem to be some kind of oak trees. They have thick "
    + "trunks and must have been standing here for decades. The trees "
    + "cast a nice, cool shade when the sun is at its highest.\n");

   add_item(({"shrubbery","shrubberies"}), 
      "The shrubberies are surrounded by white, small wooden hedges. "
    + "Each shrubbery has its own colour of flowers, together they "
    + "form colourful patches in the green grass of the garden.\n");

   add_exit(STAND_DIR + "river1","north",0);
   add_exit(STAND_DIR + "h_lane1","east",0);

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}