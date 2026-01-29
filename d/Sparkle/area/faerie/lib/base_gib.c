/*
 * Base file for gibberer caves
 * By Finwe, August 2004
 * Removed darkness from rooms for morts
 * - Finwe, April 15, 2013
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit S_LIB_CLOCK;
inherit COMMON_BASE;

#define MAX_NPCS 3

static object *g_npcs = allocate(MAX_NPCS);

void add_npcs();
void create_gib_room() {}

int room_num;

void reset_room();

public void
create_room()
{
    reset_room();
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("In the lair of the gibberers");
    set_long("You are in a small, dark, narrow passage below ground. The " +
        "characteristic acrid stench of gibberers is everywhere.\n");

    create_gib_room();

    add_prop(ROOM_I_INSIDE, 1);
//    add_prop(ROOM_I_LIGHT, 0); // dark

    add_item(({"wall", "walls", "ceiling", "floor", "passage"}),
        "The passage is dug out of the moist, black earth. It bends " +
        "around huge rocks that project out into the passage. Smaller " +
        "stones and bones can be seen in the earth.\n");
    add_item(({"stone", "stones", "rock", "rocks"}),
        "The stones are rounded pieces of grey or grey-pink granite. Some " +
        "are very large and protude partially from the walls. Others " +
        "are small and loose, and lay scattered on the ground.\n");
    add_item(({"bone", "bones", "skeleton"}),
        "The bones comes from something vaguely, but not very, humanoid. " +
        "They seem to be very old and have teethmarks on them.\n");
    add_item(({"smell", "stench", "air"}),
        "It is not very pleasent, an smells like rotting flesh, or " +
        "dirty animals.\n");
    add_item(({"teeth marks", "marks"}),
        "These are from animals that have gnawed on the bones scattered " +
        "around here. Some even look fresh.\n");
    add_item(({"earth", "dirt", "black earth", "moist earth", "ground"}),
        "The earth is dark, almost black and compacted. It feels moist " +
        "and smells like like rotting flesh.\n");


}

void
reset_room()
{
    add_npcs();
}


void
add_npcs()
{
    int index, npc_count = random(MAX_NPCS);
    string which_npcs = "gibberer";

    setuid();
    seteuid(getuid());

    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(g_npcs[index]))
        {
            g_npcs[index] = clone_object(NPC_DIR + which_npcs);
            g_npcs[index]->move(TO);
        }
    }

}
