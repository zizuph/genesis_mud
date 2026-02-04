/*
A graveyard for the legion Redhawk 921103
 */
inherit "/std/room";
#define PATH "d/Terel/common/town/mansion/graveyard/"
object monster;
reset_room(){
if(present("ghost"))return;
monster=clone_object(PATH + "ghost1.c");
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
        "you feel uneased when you goes through the graveyard.You think " +
        "you saw something just disappear outside your sights,but maybe " +
        "you just imagining things. There is a tombstone here with some " +
        "flowers standing in front of it. \n"
        ));


    add_item(({"tombstone"}), BS(
        "Its an ordinary tombstone with an engraving on it. \n"
        ));

    add_item(({"flower", "flowers"}), BS(
        "Its some old fading flowers that stands in front of the grave. " +
        "Its strange that they are here the whole graveyard looks like it " +
        "hasnt been visited for many years. \n"
        ));

   add_item(({"engraving"}), BS(
       "HERE LIES SIR DANIEL DOUGAN, MISSED BY HIS BROTHER. \n"
        ));

    add_prop(ROOM_I_INSIDE, 0);

 add_exit(MANSION + "graveyard/grv3.c", "north", 0);
 add_exit(MANSION + "graveyard/grv1.c", "south", 0);
 add_exit(MANSION + "graveyard/grvw2.c", "west", 0);
add_exit(MANSION + "graveyard/grve2.c", "east", 0);
reset_room();
}
