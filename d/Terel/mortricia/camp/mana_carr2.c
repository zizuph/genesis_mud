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

void
reset_room()
{
}

void
create_room()
{
    object door;

    set_short("Small room");
    set_long(BSN(
	"A small room in the carriage."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    door = clone_object(CAMP_DIR + "m_door2");
    door -> move(TO);

    reset_room();
}
