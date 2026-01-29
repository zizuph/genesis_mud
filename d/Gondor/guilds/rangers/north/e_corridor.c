/*
 *  /d/Gondor/guilds/rangers/north/e_corridor.c
 *
 *  A hallway in the North Hideout.
 *
 *  Coded by Elessar
 *    Modified by Alto, 15 July 2001, changed to fit revised themes
 *    Updated by Tigerlily, March, 2004
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

public string long_desc();

string
long_desc()
{

    return "You are standing in an eastern corridor of the underground "
        + "hideout. An impressive tapestry hangs on the west wall. Set "
        + "into the west wall is an iron torch stand from which a warm "
        + "flickering light plays off the walls, floor and ceiling. "
        + "The corridor leads north toward a brightly lit room and "
        + "opens onto a great hall through an arched opening to the " 
        + "south. To the east you see what appears to be a " 
        + "post-office.\n";
}

public void
create_gondor()
{
    set_short("an eastern corridor");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "corridor", "eastern corridor"}), &long_desc());
    add_item(({"tapestry", "west wall"}), "The tapestry depicts one of the "
        + "great legends of the First Age. You see the huge hound Huan, who "
        + "once was Orome's hunting dog. He is fighting Sauron, who is "
        + "in the shape of a great werewolf. Huan won the fight and forced "
        + "Sauron to relinquish the mastery of Tol-in-Gaurhoth, a fortress "
        + "built by Finrod, Son of Finarfin, on Tol Sirion.\n");
    add_item(({"opening", "arched opening"}), "The arched opening leads "
        + "to a great hall in the south.\n");
    add_item(({"walls"}), "There are two primary walls in the room, the west "
        + "wall and the east wall.\n");
    add_item(({"west wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The west wall is adorned with an "
        + "impressive tapestry, as well as an iron torch stand.\n");
    add_item(({"east wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The east wall is notable only for the "
        + "doorway leading into the post-office.\n");
    add_item(({"torch", "torch stand", "stand"}), "A torch is contained "
        + "within the iron torch stand and casts a flickering light "
        + "upon the corridor.\n");

    add_exit(RANGERS_NOR_DIR + "song_room", "north");
    add_exit(RANGERS_NOR_DIR + "post", "east");
    add_exit(RANGERS_NOR_DIR + "great_hall", "south");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

}
