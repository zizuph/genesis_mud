/*
    A mansion wing room. Mortricia 920906.
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

object monster;

reset_room(arg){
  if(!monster){
    monster=clone_object(MANSION + "mon/hunchback");
    monster->move(this_object());
}
}

void
create_room()
{
    set_short("west wing corridor");
    set_long(BS(
        "You are standing in a corridor in the " +
        "west wing " +
        "of the old mansion. " +
        "The wooden floor creaks under your weight, and the walls " +
        "are draped with dust. Cobwebs are everywhere.\n"
        ));

    add_item(({"floor"}), BS(
        "The floor is made of wooden boards which have shrunk in this " +
        "dry climate, hence leaving quite large gaps between the boards.\n"
        ));

    add_item(({"wall", "walls"}), BS(
        "The dusty wooden walls have not been touched by human hands " +
        "for many years.\n"
        ));

   add_item(({"web", "webs", "cobwebs", "cobweb"}), BS(
        "From the size of the cobwebs you realise that the creatures " +
        "who made them must be quite big.\n"
        ));

    add_prop(ROOM_I_INSIDE, 1);
   add_exit(MANSION + "tapestry_room", "north", 0);
   add_exit(MANSION + "rooms/stateroom", "east", 0);
    add_exit(TOWNDIR + "mansion/wing_n1", "northeast", 0);
    add_exit(TOWNDIR + "mansion/wing_w4", "south", 0);
  reset_room();
}
