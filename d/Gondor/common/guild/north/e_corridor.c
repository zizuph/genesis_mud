#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/common/guild/north/northern_hq.h"

create_room()
{
    set_short("The eastern corridor");
    set_long(BS("You're in the eastern corridor. On the west wall hangs an "+
    "impressive tapestry. Burning torches are set in torch brackets at "+
    "regular intervals. To the south is an arched opening. North and "+
    "east are other exits.\n"));

    add_item("tapestry",BS("It shows one of the great legends from the First "+
    "Age. You see the huge hound Huan, who once was Orome's "+
    "hunting dog. He's fighting Sauron, who is in the shape of a great "+
    "werewolf. Huan won the fight and forced Sauron to relinquish the "+
    "mastery of Tol-in-Gaurhoth, a fortress built by Finrod, Son of "+
    "Finarfin, on Tol Sirion.\n"));
    add_item("opening","The opening leads into the great hall.\n");
    TORCHES;
    SCONCES;
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR+"song_room","north",0);
    add_exit(RANGER_NORTH_DIR+"post","east",0);
    add_exit(RANGER_NORTH_DIR+"great_hall","south",0);
}