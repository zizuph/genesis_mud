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

void
create_room()
{
    set_short("east wing corridor");
    set_long(BS(
        "You are standing in a corridor in the " +
        "east wing " +
        "of the old mansion. " +
        "This corridor used to be very elegant, but nowadays it is only " +
        "the remnants of a red carpet that show signs of a forgotten glory. " +
        "The wooden floor creaks under your weight, and the walls " +
        "are draped with dust. Cobwebs are everywhere.\n"
        ));

    add_item(({"carpet"}), BS(
        "It is a red carpet made out of fine wool. Once it was beatiful " +
        "but now not much is left of it.\n"
        ));

    add_item(({"floor"}), BS(
        "The floor is made of wooden boards which have shrunk in this " +
        "dry climate, hence leaving quite large gaps between the boards. " +
        "An old carpet lies on the floor.\n"
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

    add_exit(MANSION + "wing_e4", "north", 0);
    add_exit(MANSION + "wing_e2", "south", 0);
    add_exit(MANSION + "porcia/entrance", "west", 0);
}
