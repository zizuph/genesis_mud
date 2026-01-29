/* -*- Mode: C -*-
 *
 * npc/g11-imp
 *
 * By Skippern 20(c)02
 *
 * This is the impish gardener of a magician.
 */
inherit "/std/monster";
//inherit "/std/act/domove";

#include "../defs.h"
#include <macros.h>

void
create_monster()
{
    set_name("crow");
    set_short("black crow");
    set_long("This small bird seems totally sentient and seems familiar around here.\n");

    set_random_move(55);
    set_restrain_path(DOL_HILLS + "g-11/");
    set_monster_home(DOL_HILLS + "g-11/garden1");

	set_act_time(15);
	add_act("ponder");
	add_act("bounce");
	add_act("wink");
	add_act("pace");
	add_act("jump");
	add_act("mumble");
	
	set_chat_time(90);
	add_chat("Really need to weed out here");
	add_chat("Nice living in the city, isn't it?");
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr, o;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);

    o = clone_object(DOL_NPC + "g11-golem");
    command("emote shrieks out a summoning.");
    o->move(environment(this_object()));
    say(QCTNAME(o) + " steps out of the ground.\n", o);
    o->command("assist crow");
}

