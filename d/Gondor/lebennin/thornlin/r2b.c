#pragma strict_types

#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include <language.h>
#include <macros.h>

#include "locals.h"

public int     go_northeast();

static object  Guard,
*Peasant = allocate(2);

public void
create_area_room()
{
    set_areatype(4);
    set_areadesc("well travelled");
    set_whereis("in");
    set_treetype("beech");
    set_area("Thornlin");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");

    set_extraline("The main road turns from south to east here. Off the road, "
      + "to the north, there are some "+treetype+" trees. A trail "
      + "is disappearing into the grove.");

    add_item("grove","The grove consists of some tall "+treetype+" trees.\n");
    add_item(({treetype+" trees",treetype+" tree","trees","tree"}),
      "The "+treetype+" trees are tall and proud.\n");
    add_item(({"trail","trails"}), "The trail can only just be seen " +
      "disappearing into the grove leading northeast. It " +
      "does not seem to be used that often, but is not abandoned either.\n");
    add_item(({"square","town square"}),"It seems to be the center of "
      +cityname+" and looks rather busy.\n");
    add_item(({"road","main road"}),"The road looks "+areadesc+" and "+
      "runs east trough the village and south into the square.\n"); 

    add_exit(THORN_DIR + "t1",  "northeast", go_northeast, 2, 1);
    add_exit(THORN_DIR + "r3",  "east",      0,            2, 0);
    add_exit(THORN_DIR + "r2d", "south",     0,            2, 0);

    reset_room();
}

public int
go_northeast() 
{
    write("You follow the trail in to the forest.\n");
    say(QCTNAME(TP)+" follows the trail northeast.\n",TP);
    return 0;
}

public void
reset_room()
{
    clone_npcs(Peasant, NPC_DIR + "peasants", -1.0, ({ CITY_PATH }) );
    (Peasant - ({ 0 }))->set_random_move(5);

    Guard = clone_npc(Guard, NPC_DIR + "militia");
    Guard->set_long(BS("It is a militia man, he looks like he "+
	"is working like any other farmer, though he will "+
	"probably be ready to fight when summoned upon.\n"));
    Guard->set_random_move(1);
    Guard->MILITIA_2ND_PATH;
}
