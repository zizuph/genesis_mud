/*
 * /d/Gondor/morgul/cellar/pass_1e1.c
 * A passage on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 30-jul-1994
 *
 *    Modification log:
 * 
 *           2006.08.27, removed BSN, obsolete. Toby
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("dark narrow passage");
    set_extra_long("To the west, the passage ends in front of a large "
      + "steel gate, while to the east, it continues in darkness.");

    add_c_passage("east");
    add_ceiling();
    add_floor();
    add_walls();

    add_exit(CELLAR_DIR + "pass_1e2",   "east",  0, 1);

    clone_object(CELLAR_DIR + "doors/cellar_out")->move(TO);
    add_item(({"emblem", "etching", }), 
        "The emblem etched onto the steel gate is the emblem of "
      + "the Lord of the Nazgul and the King of Minas Morgul: A Moon "
      + "as symbol of the conquered Minas Ithil, disfigured by a "
      + "death's head.");

    add_prop(ROOM_I_NO_CLEANUP, 1); // To prevent gate from relocking
}

