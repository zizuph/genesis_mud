/*
 * /d/Gondor/morgul/cellar/pass_2e2.c
 *
 * Olorin, 18-Oct-1995
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void    reset_room();

object  snake;

void
create_morgul_cellar_room()
{
    set_level(2);
    set_room_type("dark passage");
    set_extra_long("The dark tunnel runs north, while a flight of "
      + "stairs is leading up to the south.");

    add_walls();
    add_floor();
    add_ceiling();
    add_c_passage("north");
    add_up_archway();

    add_exit(CELLAR_DIR + "pass_2e3", "north", "@@check_exit", 1);
    add_exit(CELLAR_DIR + "pass_1e5", "up",    "@@check_exit", 2);

    // delay cloning the first snake
    set_alarm(120.0 + 240.0 * rnd(), 0.0, reset_room);
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

