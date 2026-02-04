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
#define PATH "d/Terel/common/town/mansion/graveyard/"

object monster;

reset_room()
{
    if (monster) return;

    monster = clone_object(MANSION + "mon/grave_digger");
    monster -> move(TO);
}
void
create_room()
{
set_short("graveyard outside the mansion");
    set_long(BS(
        "You are standing in a graveyard next to the mansion chapel, " +
        "you feel uneased when you go through the graveyard. You think " +
        "you saw something just disappear outside your sight, but maybe " +
        "you just imagined it. There is a tombstone here with some " +
        "flowers standing in front of it. \n"
        ));


    add_item(({"tombstone"}), BS(
        "It's an ordinary tombstone with an engraving but you can't make out " +
        "what it says due to the moss and dirt on it. \n"
        ));

    add_item(({"flower", "flowers"}), BS(
        "Some old fading flowers that stand in front of the grave. " +
        "It's strange that they are here, the whole graveyard looks like it " +
        "hasn't been visited for many years. \n"
        ));

   add_item(({"engraving"}), BS(
       "The engraving is covered by too much dirt for you too read it. \n"
        ));

    add_prop(ROOM_I_INSIDE, 0);

 add_exit(MANSION + "graveyard/grv4.c", "north", 0);
 add_exit(MANSION + "graveyard/grv2.c", "south", 0);
add_exit(MANSION + "graveyard/grvpath1.c", "east", 0);
reset_room();
}
