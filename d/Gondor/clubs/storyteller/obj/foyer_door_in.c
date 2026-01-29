/*
 * /d/Gondor/clubs/storytellers/obj/foyer_door_in.c
 */
inherit "/std/door";
#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>

void
create_door()
{
    set_door_id("foyer_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(PELAR_DIR + "streets/beacon02");
    set_door_desc("The large door is made of polished wood, and leads "
      + "out into the street. There is a peep hole, through which you "
      + "can peek.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key(KEY_ID);
}

public int
peep_hole(string str)
{
    object *inv;
    string text;

    if (str != "through peep hole" && str != "through peephole")
	return 0;

    inv = FILTER_LIVE(all_inventory(find_object(other_room)));

    if (!sizeof(inv))
	text = "but see no one there";
       else
	text = "and see "+COMPOSITE_LIVE(inv)+" there";

    write("You "+query_verb()+" through the peep hole, "+text+".\n");
    say(QCTNAME(this_player())+" "+query_verb()+"s through the peep hole.\n");
    return 1;
}


void init()
{
    ::init();

    add_action(peep_hole, "peek");
    add_action(peep_hole, "look");
}
