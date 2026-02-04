/*
  A room. Mortricia 920927
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

object tecla;

void
reset_room()
{
    object crystal;

    if (!tecla) {
        tecla = clone_object(CAMP_DIR + "tecla");
        tecla -> move(TO);
    }
    if (!present("crystal")) {
        crystal = clone_object(CAMP_DIR + "crystal");
        crystal -> move(TO);
    }
    return;
}

void
create_room()
{
    set_short("Fortune teller's carriage");
    set_long(BSN(
        "You are inside a strange carriage, and you feel a bit " +
	"uneasy. It's somewhat dusky in here. The walls are " +
	"covered with symbols. A table and two chairs have been " +
	"placed in the corner."
    ));
    
    add_item("symbols", BSN(
	"They are old Tarot symbols: Love, Death etc."
    ));
    add_item(({"Love", "love"}), BSN(
	"It's a couple of lovers."
    ));
    add_item(({"Death", "death"}), BSN(
	"It's a fully armoured skeleton on a white horse."
    ));
    add_item("table", BSN(
	"The spherical crystal stands on the table."
    ));
    add_item(({"chairs", "chair"}), BSN(
	"One chair is empty, the other one is occupied by " +
	"the old fortune teller."
    ));
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CAMP_DIR + "camp_12", "south", 0);

    reset_room();
}
