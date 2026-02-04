/*
  A carriage room. Mortricia 920927
 */
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

object key, head;

void
reset_room()
{
    if (!head) {
        head = clone_object(CAMP_DIR + "manager");
        head -> move(TO);
	key -> move(head);
    }
}

void
create_room()
{
    object door;

    set_short("The Head of Gypsies' carriage");
    set_long(BSN(
        "You are inside the carriage that belongs to the head of " +
	"the gypsies."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CAMP_DIR + "camp_08", "east", 0);

    door = clone_object(CAMP_DIR + "m_door1");
    door -> move(TO);

    key = clone_object(CAMP_DIR + "m_key");
    door -> set_key(key -> query_key());

    reset_room();
}
