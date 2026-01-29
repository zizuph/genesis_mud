/*
 * /d/Gondor/morgul/cellar/pass_1e4.c
 * A passage on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 30-jul-1994
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void    reset_room();

object  snake;

void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("dark tunnel");
    set_extra_long("The tunnel comes to a narrow bend here. It continues "
      + "south and northeast. In the west wall, a dark archway is "
      + "leading down into a dungeon.");

    add_walls();
    add_floor();
    add_c_passages("south", "northeast");
    add_ceiling();
    add_down_archway();

    add_exit(CELLAR_DIR + "pass_1e5", "northeast", 0, 1);
    add_exit(CELLAR_DIR + "pass_1e3", "south",     0, 1);
    add_exit(CELLAR_DIR + "dung_2e1", "down",  "@@no_sneak", 1);

    reset_room();
}

void
reset_room()
{
    if (objectp(snake))
        return;

    snake = clone_object(NPC_DIR + "snake");
    snake->set_restrain_path(CELLAR_DIR);
    snake->set_random_move(4);
    snake->set_whimpy(80);
    snake->move_living("down", TO);
}

