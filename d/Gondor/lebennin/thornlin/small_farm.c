#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");

#include <macros.h>
#include <stdproperties.h>
#include "locals.h"

int
add_stuff()
{
    object hammer;
    if (!present("_hidden_hammer",TO))
    {
	hammer = clone_object(OBJ_DIR + "hammer");
	hammer->add_name("_hidden_hammer");
	hammer->add_prop(OBJ_I_HIDE, 15 + random(11));
	hammer->move(TO);
    }
}

void
create_room()
{
    set_short("a small farm house");
    set_long(BSN("This is a small farm house with only a single "
	+ "room. In western end of the room there is a small table "
	+ "and a cupboard. In the middle of the room lie several "
	+ "mattresses where folks can sleep. The eastern part of "
	+ "the room looks more like a stable for animals, "
	+ "possibly pigs. In the northeast corner is a door."));

    INSIDE;  /* This room is a inside room */

    add_item("table","It is a wooden table where folks can eat.\n");
    add_item("door","The door is leading out.\n");
    add_item(({"mattress", "mattresses", }), "They look unmade.\n");
    add_item("cupboard","It is a normal cupboard.\n");

    add_exit(THORN_DIR + "r2c","northeast","@@enter_garden",1);

    add_stuff();
}

int
enter_garden()
{
    write("You walk through the doorway and out into the light.\n");
    return 0;
}

void
reset_room()
{
    add_stuff();
}
