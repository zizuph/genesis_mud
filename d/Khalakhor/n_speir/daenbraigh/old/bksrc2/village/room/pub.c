/*
 * Daenbraigh pub
 * TAPAKAH, 09/2005
 */

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/pub";

#include <stdproperties.h>
#include "../../nspeir.h";
#include "../../village/village.h";

object barman;
void
create_khalakhor_room()
{
  set_short(VILLAGENAME + " pub");
  set_long(BS("The pub is one of the first buildings erected in the village.\n"));

  add_item(({"shelves","shelf","bottles"}),
	   "The shelves are very dusty and barely filled with bottles.\n");
  add_item(({"tables","table","chair"}),
	   "The tables and the chairs are old and rickety");
  add_item(({"menu"}),
	   &menu_list);
  add_prop(ROOM_I_INSIDE,1);
  add_prop(GV_OUTSIDE, 0);
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
	    90,
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
	    160,
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
  
  reset_room();
}
void
reset_room() {

  ::reset_room();

  if(! barman) {
    barman = clone_object(BARMAN);
    barman->move(TO);
  }
}
string
menu_list()
{
    read_menu("menu");
    return "";
} 
     
