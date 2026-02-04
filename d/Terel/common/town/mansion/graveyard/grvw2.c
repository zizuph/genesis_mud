/*
A graveyard for the legion Redhawk 921103
 */
inherit "/std/room";
#define PATH "d/Terel/common/town/mansion/graveyard/"
object monster;
reset_room(){
if(present("ghost"))return;
monster=clone_object(PATH + "ghost1");
monster->move(this_object());
}
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

void
create_room()
{
set_short("graveyard outside the mansion");
    set_long(BS(
        "You are standing in a graveyard next to the mansion chapel, " +
        "you feel uneased when you go through the graveyard.  You think " +
        "you saw something just disappear outside your sights, but maybe " +
        "you're just imagining things. There is a tombstone here that is " +
        "moss covered. \n"
        ));


    add_item(({"tombstone"}), BS(
        "Its an ordinary tombstone with an engraving on it. \n"
        ));

    add_item(({"moss", "moss"}), BS(
        "Its ordinary green moss that grows in moisture. \n"
        ));

   add_item(({"engraving"}), BS(
       "UNKNOWN. \n"
        ));

    add_cmd_item("engraving", "read", "UNKNOWN\n");

    add_prop(ROOM_I_INSIDE, 1);

 add_exit(MANSION + "graveyard/grv2.c", "east", 0);
}
