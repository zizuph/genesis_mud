/*
 * Rack room base room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L1_BASE_ROOM;

string get_rack_loc();
string get_add_room_long();
/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Rack room");
    set_long("You are in a small room with the only exit. " +
             "There is a large rack in " + get_rack_loc() +
             " part of room. " + get_add_room_long());

    add_npc(NPCS_DIR + "goblin1_1", 2, &->arm_me());

} /* create_room */


string
get_rack_loc()
{
    return "wrong";
}

string
get_add_room_long()
{
    return "\n";
}