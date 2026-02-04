/*
A graveyard for the legion Redhawk 921103
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()
#define PATH           MANSION + "graveyard/"

object monster;
reset_room(){
if (monster) return;
monster=clone_object(PATH + "ghost1");
monster->move(this_object());
}

void
create_room()
{
set_short("graveyard outside the mansion");
    set_long(BS(
        "You are standing on a path that leads east on this graveyard, " +
        "you feel that the temperature seems to fall the closer you get " +
        "to the east. \n"
        ));

    add_prop(ROOM_I_INSIDE, 0);

add_exit(PATH + "grv3", "west", 0);
add_exit(PATH + "grvpath2", "east", 0);
add_exit(PATH + "g1", "north", 0);
reset_room();
}
