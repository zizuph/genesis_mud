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
    set_short("north wing corridor");
    set_long(BS(
        "You are standing in a corridor in the " +
        "north wing " +
        "of the old mansion. " +
        "The wooden floor creaks under your weight, and the walls " +
        "are draped with dust. Cobwebs are everywhere. A fine wooden " +
	"door, now cracked and broken, hangs loosely from one hinge " +
	"in the south wall.\n"
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

    add_item(({"door"}), BS(
	"This large wooden door might once have been formidable, but " +
	"now you may simply step around it to enter the dim room to the " +
	"the south.\n"
	));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(MANSION + "wing_n2", "west", 0);
    add_exit(MANSION + "wing_n4", "east", 0);
    add_exit(MANSION + "lib/entrance","south",0);
}
