/**********************************************************************
 * - rack_room.c                                                    - *
 *
 * - A room that holds racks for Gladiators to hold thier equipment - *
 * - Also contains a "board" that only the High Overseer can post   - *
 * - rack policy on.                                                - *
 *
 * - Created by Damaris@Genesis 09/2005                             - *
 * - April 2013 (Serpine) - Merged with chest room
 *********************************************************************
 */
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"
#include <macros.h>

public void
create_room()
{
    object rack1;
    object rack2;
    object rack3;
    object rack4;

    object board;
        
    set_short("Equipment hall");
    set_long("The light from dim torches cast a warm glow all " +
        "around the chamber. It is far from being barren here, as " +
        "various means of storage take up a significant portion of " +
        "the space. Alongside the axe rack is a sign that the High " +
        "Overseer has attached to the wall, "+
        "outlining the rules and regulations for use of the "+
        "gear by other gladiators.\n" +
        "Storage options here include a solid wooden axe rack, an " +
        "armour closet, a weapons pile, and a huge stone supply chest.\n");

    add_item(({"room", "area", "rack room", "equipment hall", "hall"}),
        query_long);
    add_item(({"walls", "wall", "storage", "means", "means of storage"}),
        "Their are various places to store equipment and arms here.\n");
    add_item(({"floor", "ground", "corner"}),
        "The floor is made of some kind of rock mixture. A weapon " +
        "pile takes up a large portion of one corner.\n");
    add_item(({"rock mixture", "mixture", "rock"}),
        "The rock mixture looks like it is small rocks mixed with some "+
        "mud that has hardened with straw and other substances.\n");
    add_item(({"torch", "torches", "dim torch", "dim torches"}),
        "The torches add dim light and are firmly attached to the " +
        "walls.\n");

    rack1 = clone_object(GLAD_OBJ+"racks/axe_rack");
    rack1->move(TO); 

    rack2 = clone_object(GLAD_OBJ+"racks/armour_rack");
    rack2->move(TO); 

    rack3 = clone_object(GLAD_OBJ+"racks/weapon_rack");
    rack3->move(TO); 

    rack4 = clone_object(GLAD_OBJ+"racks/supply_rack");
    rack4->move(TO); 

    board = clone_object(GLAD_OBJ+"rack_board");
    board->move(TO);        

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("gldboard", "east");
}
