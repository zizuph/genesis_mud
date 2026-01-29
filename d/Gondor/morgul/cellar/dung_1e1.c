/*
 * /d/Gondor/morgul/cellar/dung_1e1.c
 * A dungeon on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 30-jul-1994
 * Tigerlily--removed exit to torture until quest is
 *   completed--March 2, 2004
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
    set_room_type("gloomy dungeon");
    set_extra_long("There is an archway to the northwest " +
        "beyond which a dark tunnel is visible.");

    add_walls();
    add_floor();
    add_archway("northwest");
    add_ceiling();
/*
    add_item( ({ "stairs", "steps" }), 
        ("The black stone steps lead down and show signs of " +
        "centuries of usage.\n"));
*/

    add_exit(CELLAR_DIR + "pass_1e3", "northwest", 0, 1);
/*
    add_exit(CELLAR_DIR + "torture", "down", 0, 1);
*/
}

