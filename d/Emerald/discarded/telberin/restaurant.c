/*
 * The Waterfront Restaurant in Telberin
 * Coded by Finwe
 * February 1997
 * This uses the 'common room' code by Xarguul
 */
 
inherit "/std/room"; 
inherit "/d/Emerald/lib/room_tell"; 
inherit "/d/Emerald/telberin/common_room"; 
#include "/d/Emerald/defs.h" 
#include "default.h"
 
 
void create_room()
{
   ::create_room();
    add_prop(ROOM_I_INSIDE, 1);
    set_short("Waterfront Restaurant");
    set_long("   You have entered the Waterfront Restaurant. " +
        "It is one of the finest restaurants in Emerald.  " +
        "Large windows at the far end offer a panoramic view of " +
        "the lake. A subdued atmosphere fills the room as elves " +
        "quietly eat here and discuss business. You see tables " +
        "spread around here with candles on them. A menu and a " +
        "wine list are on the wall for you to read.\n\n");
 
    add_item("scrollwork",
        "The scrollwork is beautifully carved on the tables and " +
        "chairs.\n");
    add_item(({"interior", "walls"}),
        "The walls are paneled with dark mahogany. They are " +
        "polished to a deep luster and glow in the light.\n");
    add_item("view",
        "The view is specatular. You see the lake below you " +
        "with waves across the surface. Boats can be seen " +
        "floating on the lake.\n");
    add_item(({"window", "windows"}),
        "The windows are fill the south end of the restaurant. " +
        "They beckon to the elves to come out and experience " +
        "the beauty of the lake.\n");
    add_item(({"down", "ground", "floor"}),
        "You see the floor is covered with a lush carpet. " +
        "The carpet is a dark chocolate color. It fills the room.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling is painted a subdued color.\n");
    add_item(({"color", "colors", "colour", "colours"}),
        "The colors are quiet and subdued.\n");
    add_item(({"customers", "elves"}),
        "The elves that sit in the restaurant are quietly " +
        "enjoying themselves. Many of them come here for the " +
        "quiet atmosphere, good food, and private tables.\n");
    add_item(({"list", "wine list"}), "It has words on it. "+
		"perhaps you should read it.\n");

    add_cmd_item(({"sign", "menu", "wine list", "list"}), 
         "list", "@@list_sign@@");

    set_alarm(1.0,0.0,"reset_room");
 
    add_exit(AVENUE_DIR + "ave21", "out");
}
 
void
reset_room()
{
}
string
list_sign()
{
    return "Perhaps you should read it.\n";
}
