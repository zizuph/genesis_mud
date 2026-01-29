#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

void
do_desiccate(object ob)
{
    string sh = "@@short:" + file_name(ob) + "@@";
    object env, *players, *can_see_actor, *can_see_corpse;

    env = ((environment(ob) == this_player()) ? 
        environment(this_player()) : environment(ob));
    players = FILTER_PLAYERS(all_inventory(env));
    can_see_actor = can_see_corpse = FILTER_CAN_SEE_IN_ROOM(players);
    can_see_actor = FILTER_CAN_SEE(can_see_actor - ({ this_player() }), this_player());
    can_see_corpse = FILTER_CAN_SEE(can_see_corpse, ob);

    this_player()->add_thirst_random();
    
    this_player()->catch_msg("You place your hands on the " + sh + 
        " and focus your power.\n");
    can_see_actor->catch_msg(QCTNAME(this_player()) + " places " + 
        this_player()->query_possessive() + " hands on " + sh + ".\n");

    map(all_inventory(ob), &->move(environment(ob)));

    can_see_corpse->catch_msg("The " + sh + 
        " decays into a desiccated pile of dust.\n");

    ob->remove_object();
}

int
desiccate(string str)
{
    mixed *obs;
    object *corpses;

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
         notify_fail("You can't see anything, though!\n");
         return 0;
    }

    if (!strlen(str) ||
        !parse_command(str, all_inventory(environment(this_player())) +
        all_inventory(this_player()), "[the] %i", obs) ||
        !sizeof(obs = NORMAL_ACCESS(obs - ({ this_player() }), 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    corpses = filter(obs, 
        &operator(==)(CORPSE_OBJECT) @ &function_exists("create_container"));

    if (!sizeof(corpses))
    {
        write("You cannot desiccate " + ((sizeof(obs) > 1) ? "those" :
        "that") + ".\n");
      	return 1;
    }

    map(corpses, do_desiccate);

    return 1;
}
