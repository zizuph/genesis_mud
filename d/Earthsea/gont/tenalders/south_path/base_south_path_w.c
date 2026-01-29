/*
 * 
 * 
*  coded by Amelia 6/1/97
 */

inherit "/d/Earthsea/std/room";
#pragma no_clone
#pragma strict_types

#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include "/sys/macros.h"
inherit BASE_HERB_ROOM;
#include GARDEN_HERB_FILE


string long_desc();
void create_farm_path();

void
reset_room()
{
    ::reset_room();
}

void
create_earthsea_room()
{


    ::create_herb_room();
    set_short("Road through farmland");

    set_long(BS("@@long_desc", 70));
    set_tell_time(120);



    add_item((({"farmland", "pastures", "rolling hillside",
	  "hillside"})),
      "There are farm cottages dotting the hillside with green "+
      "pasture and cultivated fields lying between them. Although "+
      "all should seem like a lovely view, you notice that something "+
      "is quite wrong... You see flame and plumes of smoke "+
      "rising from some of them.\n");
    add_item((({"Gont City", "City", "white towers", "towers"})),
      "The white towers of Gont still glisten in the sun, with "+
      "boats going to and fro in the harbour. Away to the "+
      "southeast off the beach, however, you also make out "+
      "three black longships, with the red mark of Karego At on "+
      "their sails.\n");
    add_item((({"forest", "ancient pine trees", "pine trees", 
	  "trees"})),
      "The pine forest climbs the flank of the mountain.\n");
    add_item((({"south", "sea", "beach", "white sandy beach",
	  "sandy beach"})),
      "From this vantage point you view at a distance the vast "+
      "sea and the white beach far below.\n");


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);

    set_up_herbs(TO->select_herb_files(GARDEN_HERBS),
      GARDEN_LOCATIONS, 3);
    reset_room();

    create_farm_path();

}


void
create_farm_path()
{}

string
long_desc()
{
    return "Away down the mountain to the south "+
    "you see in the distance the vast "+
    "expanse of winedark sea, where the waves crash onto a sandy "+
    "white beach. To the southwest you see green farmland and "+
    "pastures on the rolling hillside. ";

}
