/*
 * Hammerhands pub
 * TAPAKAH, 10/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/pub";
inherit HH_GUILDROOM;

string menu_list();

void
create_khalakhor_room()
{
  ::create_khalakhor_room();
  
  set_short("Hammerhands pub");
  set_long("Obviously, one of the most popular room in the building.\n");

  add_item(({"kegs","barrels"}),
	   "The shelves are very dusty and barely filled with bottles.\n");
  add_item(({"tables","table","chair","chairs"}),
	   "The tables and the chairs carry the crossed-clubs insignia");
  add_item(({"menu"}),
	   &menu_list());
  add_prop(ROOM_I_INSIDE,1);
  add_prop(HH_INSIDE,1);
  add_exit("join","north",&check_enter(HH_ACCESS_ALL));
  add_exit("train","east",&check_enter(HH_ACCESS_MEMBER));
  add_drink(
	    ({"ale","dark ale"}),
	    ({"ale"}),
	    "dark",
	    250,
	    10,
	    25,
	    "glass of dark ale",
	    "glasses of dark ale",
	    "The glass contains half a pint of a nearly black ale.\n",
	    "",
	    );
  add_drink(
	    ({"beer","sugar beer"}),
	    ({"beer"}),
	    "sugar",
	    160,
	    30,
	    75,
	    "mug of beer",
	    "mugs of beer",
	    "The mug is full of sweetly smelling beer.\n",
	    "",
	    );
  add_drink(
	    ({"wine","old wine"}),
	    ({"wine"}),
	    "old",
	    90,
	    90,
	    250,
	    "small glass of old wine",
	    "small glasses of old wine",
	    "A small glass of a very old, best quality wine.\n",
	    "",
	    );
  add_drink(
	    ({"whisky","malt whisky"}),
	    ({"whisky"}),
	    "malt",
	    40,
	    160,
	    400,
	    "tumbler with a tip of malt whisky",
	    "tumblers with a tip of malt whisky",
	    "A pint tumbler with a drop of malt whisky. You wonder why they "+
	    "serve it that way.\n",
	    "",
	    );
  reset_room();
}
void
reset_room() {

  ::reset_room();

}
string
menu_list()
{
    read_menu("menu");
    return "";
} 
string
init()
{
  ::init_pub();
  ::init();
}

void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "Hammer It Pub Menu"));
}
