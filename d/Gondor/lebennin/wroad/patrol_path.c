/*
 *  /d/Gondor/lebennin/wroad/patrol_path.c
 *
 *  Basefile for corsair patrol path rooms
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit LEBENNIN_STD_DIR + "base";

#define PATROL_PATH ["cp6", "cp7", "cp8", "cp9", "cp11", "cp12", "cp13", "cp14"]

static int moving = 0;
void move_patrol(object o);

public void
enter_inv(object o, object from)
{
    ::enter_inv(o, from);

    if (!moving && o->query_prop(LEBENNIN_CORSAIR_PATROL)) {
        mixed exits = from->query_exit();
        for (int i; i < sizeof(exits) / 3; i++) {
           tell_room(environment(this_player()), exits[i + 3]);
        }
        //moving = set_alarm(20.0 + rnd() * 40.0, 0.0, &move_patrol(o));
    }
}

void
move_patrol(object o)
{
    moving = 0;
    o->command("north");
}


/*
 * Function name:        set_items_patrol
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_patrol(); 
 *                       Use for the rooms the corsair patrol roams
 */
void
set_items_patrol()
{
    add_item(({"river"}),
        "To the west you can see the river Gilraith flowing down to the sea.\n");
}
