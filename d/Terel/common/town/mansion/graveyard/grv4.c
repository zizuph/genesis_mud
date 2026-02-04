/*
A graveyard for the legion Redhawk 921103
 */
inherit "/std/room";
#define PATH "d/Terel/common/town/mansion/graveyard/"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

object monster;
reset_room(){
    if (present("ghost")) return;
    monster = clone_object(PATH + "ghost1");
    monster -> move_living("X", TO);
}

void
create_room()
{
set_short("graveyard outside the mansion");
    set_long(BS(
        "You are standing in a graveyard next to the mansion chapel, " +
        "you feel uneasy when you go through the graveyard. You think " +
        "you saw something just disappear outside your sight, but maybe " +
        "you're just imagining things. There is a tombstone here with some " +
        "flowers standing in front of it. \n"
        ));


    add_item(({"tombstone"}), BS(
        "It's an ordinary tombstone with an engraving that you can't make out " +
        "what it says due to much moss and dirt on it. \n"
        ));

    add_item(({"flower", "flowers"}), BS(
        "Its some old fading flowers that stands in front of the grave. " +
        "Its strange that they are here the whole graveyard looks like it " +
        "hasnt been visited for many years. \n"
        ));

   add_item(({"engraving"}), BS(
       "The engraving is covered with too much dirt for you too read it. \n"
        ));

    add_prop(ROOM_I_INSIDE, 0);

 add_exit(MANSION + "chapel/chapel.c", "west", 0);
 add_exit(MANSION + "graveyard/grv3.c", "south", 0);
    reset_room();
}
