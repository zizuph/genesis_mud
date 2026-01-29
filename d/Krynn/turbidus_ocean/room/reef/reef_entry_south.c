#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <macros.h>
#include "../../local.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "intertide", }) );

void
reset_sea_room()
{
    set_searched(0);

    return;
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
 
    add_item(({"deep water bay","deep bay","bay","bay of branchala",
        "inlet","water","deep water inlet"}),
        "To your south is the Bay of Branchala, a deep water inlet of " +
        "the Turbidus Ocean. It is protected from wild weather by the " +
        "great reef you now find yourself in.\n");
    add_item(({"turbidus ocean","ocean","sea"}),
        "Around you is the Turbidus Ocean - a massive body of water " +
        "that stretches from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"reef","great reef","coral","maze"}),
        "To your north is a great reef, a maze of coral that would take a " +
        "skilled sailor to navigate. You have no doubt the reef holds " +
        "the wrecks of many unfortunate or foolish captains who were not up to " +
        "the task.\n");
    add_item(({"wrecks","ships"}),
        "You see no wrecks from here, but assume the great reef would hold " +
        "many sunken ships of the unfortunate or foolish captains.\n");

    add_row_exit(ROOM + "4q", "south", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(61);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("You don't have the skill to navigate " +
        "into the coral maze without sinking your ship!\n");
    set_sailing_difficulty_message("The reef is challenging to navigate, " +
        "but your sailing skills are up to the challenge!\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

string
short_descr()
{
    return "maze of coral in a great reef";
}
 
string
long_descr()
{
    return "You find yourself in a maze of coral, part of a great reef off " +
        "the Bay of Branchala in the Turbidus Ocean. "+
        query_sailing_difficulty_desc()+ "\n";
}