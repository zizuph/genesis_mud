/*
 *  Added fishing properties allowing fishing - Arman 2021
 */

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;
#include "river_drink.h"
#include "/d/Krynn/common/herbsearch.h"

#define H1 "/d/Krynn/common/herbs/bur_reed"
#define LIVE_I_CAN_FISH      "_live_i_can_fish"

void
reset_flotsam_room()
{
   set_searched(random(2));
}

create_flotsam_room()
{
    set_short("By the bank of a merrily running river");
    set_long("@@long_descr");

    add_item(({"forest","evergreen forest","ancient forest",
	"great oaks","oaks","ancient oaks","thick underbrush","underbrush",
	"shadows","trees"}),
      "The river here divides the ancient evergreen forest only " +
      "barely in two, with the canopies of the ancient oaks " +
      "entangling like estranged lovers.\n");
    add_item(({"river","merrily running river"}),
      "Before you a river runs merrily away through the " +
      "forest to your southeast.\n");
    add_item(({"river bank","bank"}),
      "You stand on the edge of a river bank.\n");
    add_item(({"bridge","wooden bridge"}),
      "To your north a bridge spans over the flowing river. " +
      "The river bank runs under it into the darkness created " +
      "by its shadow in that direction.\n");
    add_item(({"trail","small trail"}),
      "To your northeast a trail curves around the side of the bank " +
      "and up to the foot of the bridge.\n");

    add_exit(FROOM + "under_bridge","north",0);
    add_exit(FROOM + "bridge","northeast","@@up_trail");
    add_exit(FROOM + "trailb","southeast",0);

    add_prop(LIVE_I_CAN_FISH, "freshwater");

    set_tell_time(120);
    add_tell("The river babbles past you noisily " +
      "as it flows through the forest to your southeast.\n");
    add_tell("The ancient oaks beside the river groan " +
      "as a strong wind blows " +
      "through them.\n");

    add_cmd_item(({"river","water","from river","water from river"}),
      "drink","@@drink_water");

   seteuid(getuid(TO));
   set_search_places(({"forest","underbrush","herbs"}));
   add_prop(OBJ_I_SEARCH_TIME,3);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_herb_file(H1);

    reset_flotsam_room();
}

int
up_trail()
{
    write("You climb up the edge of the bank and onto " +
      "the bridge...\n");
    return 0;
}

string
long_descr()
{
    return "You stand on the bank of a river that flows " +
    "through a vast evergreen forest." +
    " To your north stands a bridge that spans over " +
    "the river. The river bank runs underneath it into " +
    "the darkness created by its shadow. A small trail " +
    "leads up the bank to the bridge to your northeast." +
    "\n";
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
	start_room_tells();
}
