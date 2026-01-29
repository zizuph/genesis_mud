/*
 * /d/Gondor/anorien/nimrais/trolls/armscave.c
 *
 * Coder: Unknown
 *
 * Modification log:
 *
 * Gwyneth, 10/02/02: Cleaned up and modernized the code. Changed inheritance.
 */
#pragma strict_types
inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

object gHammer, gMail, gLamp;

void reset_room();

void
create_gondor()
{
    set_short("The arms storage cave in the hill-troll lair");
    set_long("This must be the cave where the hill-trolls store their " +
        "weapons and armours. You see broken clubs and torn capes " +
        "littered about the floor. Not much usable for anyone else but " +
        "the strong trolls. A foul smell reaches you from the cave to " +
        "the southeast.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(NIMRAIS_DIR + "trolls/livcave", "southeast");

    add_item("clubs", "You see the pieces of broken stone clubs on the "+
        "floor. They are of course unusable and thus worthless.\n");
    add_item("capes", "You find several torn and worn out capes on the " +
        "floor. You instantly discard them as useless as well as " +
        "worthless.\n");

    reset_room();
}

void
reset_room()
{
    ::reset_room();

    if (!present(gHammer, this_object()))
    {
        gHammer = clone_object(WEP_DIR + "trollhammer");
        gHammer->move(this_object());
    }

    if (!present(gMail, this_object()))
    {
        gMail = clone_object(ARM_DIR + "mmail");
        gMail->move(this_object());
    }

    if (!present(gLamp, this_object()))
    {
        gLamp = clone_object(OBJ_DIR + "oil_lamp");
        gLamp->set_time_left(100 + random(100));
        gLamp->move(TO);
    }
}
