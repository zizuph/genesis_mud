/* A haunted room. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"

void
reset_room()
{
    object box;

    if (!present("box", TO)) {
        box = clone_object(HAUN_DIR + "box");
        box -> set_adj("black");
        box -> set_short("black box");
        box -> move(TO);
    }
}

void
create_room()
{
    set_short("Haunted House");
    set_long(BSN(
        "It's rather dark in here, since not much light " +
        "penetrates the canvas."
    ));
    add_item(({"canvas"}), BSN(
        "The canvas reflects the light in many colours. " +
        "Drawings of ghostly creatures have been made on it " +
        "as well. You have never before seen such creatures."
    ));
    add_item(({"exit", "exits"}), BSN(
        "Which exit do you mean? The western or the eastern?"
    ));
    add_item(({"eastern exit"}), BSN(
        "You see some faint day-light through the eastern exit."
    ));
    add_item(({"western exit"}), BSN(
        "The western exit is simply an opening in the canvas. " +
        "You can't see (or even imagine) what is behind it."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HAUN_DIR + "house_1", "east", 0);
    add_exit(HAUN_DIR + "house_3", "west", "@@go_west");

    reset_room();
}

go_west()
{
    write("Ooops! You slip and slide down...\n");
    return 0;
}
