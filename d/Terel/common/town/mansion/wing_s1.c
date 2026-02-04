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

object b_cat, b_dog;

void
reset_room()
{
    if (!b_cat) {
        b_cat = clone_object(MORTRICIADIR + "creatures/cat");
        b_cat -> move(TO);
    }
    if (!b_dog) {
        b_dog = clone_object(MORTRICIADIR + "creatures/dog");
        b_dog -> move(TO);
    }
}

void
create_room()
{
    set_short("south wing corridor");
    set_long(BS(
        "You are standing in a corridor in the " +
        "south wing " +
        "of the old mansion. " +
        "This wing is in very poor condition, and what is left of the " +
        "walls and ceiling doesn't provide much protection against the " +
        "icy wind. " +
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

    add_exit(MANSION + "wing_w1", "northwest", 0);
    add_exit(MANSION + "wing_s2", "east", 0);
    
    reset_room();
}
