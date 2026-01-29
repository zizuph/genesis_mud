/*
 * Daenbraigh pub
 * TAPAKAH, 09/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h";
#include "../../village/village.h";

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/pub";
inherit DAENBRAIGH_BASE;

string menu_list();

void
create_khalakhor_room()
{
  ::create_khalakhor_room();
  
  set_short(VILLAGE_NAME + " pub");
  set_long("The pub is one of the first buildings erected in the village. "+
	   "A dirty-looking wooden menu is leaning against a wall.\n");

  add_item(({"shelves","shelf","bottles"}),
	   "The shelves are very dusty and barely filled with bottles.\n");
  add_item(({"tables","table","chair"}),
	   "The tables and the chairs are old and rickety");
  add_item(({"menu"}),
	   &menu_list());
  add_prop(ROOM_I_INSIDE,1);
  add_exit("ns_2","east");

  add_drink(
	    ({"ale","frosty ale"}),
	    ({"ale"}),
	    "frosty",
	    250,
	    10,
	    25,
	    "glass of frosty ale",
	    "glasses of frosty ale",
	    "The glass contains half a pint of ale and has frost all over it.\n",
	    "",
	    );
  add_drink(
	    ({"port","smuggled port"}),
	    ({"port"}),
	    "smuggled",
	    160,
	    30,
	    75,
	    "dented goblet of port",
	    "dented goblets of port",
	    "The badly dented goblet with a measure of port in it " +
	    "probably was smuggled or salvaged from a shipwreck like its contents.\n",
	    "",
	    );
  add_drink(
	    ({"wine","juniper wine"}),
	    ({"wine"}),
	    "juniper",
	    90,
	    60,
	    250,
	    "shot of juniper wine",
	    "shots of juniper wine",
	    "A small vial of glass containing a shot of juniper wine. It smells"+
	    " horribly.\n",
	    "",
	    );
  add_drink(
	    ({"whisky","malt whisky"}),
	    ({"whisky"}),
	    "malt",
	    40,
	    100,
	    400,
	    "tumbler with a tip of malt whisky",
	    "tumblers with a tip of malt whisky",
	    "A pint tumbler with a drop of malt whisky. You wonder why they "+
	    "serve it that way.\n",
	    "",
	    );
  add_food(
	   ({"stew","cat stew"}),
	   ({"stew"}),
	   "cat",
	   60,
	   60,
	   "bowl of cat stew",
	   "bowls of cat stew",
	   "A bowl with pieces of a miserable cat who happened to wander too "+
	   "close to the pub",
	   "",
	   );
  add_food(
	   ({"cutlet","dog cutlet"}),
	   ({"cutlet"}),
	   "dog",
	   120,
	   120,
	   "plate with dog cutlet",
	   "plates with dog cutlet",
	   "A battered plate with a cutlet made from a dog.",
	   "",
	   );
  add_food(
	   ({"pie","meat pie"}),
	   ({"pie"}),
	   "meat",
	   360,
	   360,
	   "large round pie",
	   "large round pie",
	   "A large pie stuffed with any kind of meat the cook could find",
	   "",
	   );
  add_npc(V_BARMAN);
  add_npc(V_COURIER);
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
    write(sprintf("%|76s\n\n", "Goblynn Pryde Pub Menu"));
}

int *
query_local_coords()
{
  return ({-6,-2});
}
