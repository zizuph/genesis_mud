/* 
 * This is a base for a kender walking around and borrowing 
 * things from people. It's a pretty nice kender, but ken
 *
 * Created by Aridor 05/19/94 
 *
 * Updated by Cotillion 2003-03
 */
#include "/d/Krynn/common/defs.h"

inherit M_FILE

#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <language.h>

#define KENDER_STOLEN_ITEM  "krynn_kender_stole_this"

/* This is an odd array used in lots of inheriting files,
 * it has to remain
 */
object *my_stuff;


void
create_kender() { }

void
create_krynn_monster()
{
    set_name("kender");
    set_gender(random(1));
    set_race_name("kender");

    set_alignment(0);
    set_knight_prestige(0);
    
    set_random_move(2, 1);
    set_act_time(1 + random(2));

    add_act("@@do_drop@@");
    add_act("@@steal_something@@");
    add_act("@@steal_something@@");
    add_act("@@steal_something@@");
    add_act("@@steal_something@@");
    add_act("@@steal_something@@");
    add_act("get all from corpse");

    set_pick_up(1);
    create_kender();
}

void
flee(object enemy)
{
    string *exit;
    if (!objectp(enemy) || environment(enemy) != environment())
        return;

    if (!CAN_SEE(TO, enemy))
        return;
    
    switch (random(2))
    {
    case 0:
        command("peer " + OB_NAME(enemy));
        break;
    case 1:
        command("say to " + OB_NAME(enemy) + 
            " I didn't do anything!");
        break;
    }
    
    exit = environment()->query_exit_cmds();
    if (sizeof(exit))
    {
        command(exit[random(sizeof(exit))]);
    }
}

public varargs void
emote_hook(string emote, object actor, string adverb, object *oblist, 
    int cmd_attr, int target = 1) 
{
    if (!target)
        return;
    
    switch (emote) 
    {
    case "slap":
    case "kick":
    case "knee":
        set_alarm(rnd(), 0.0, &flee(actor));
        break;
    }
}


string
steal_something()
{
    object *ob;
    object who, what;
    
    if (!environment(this_object()))
        return "";
    
    if (!CAN_SEE_IN_ROOM(this_player()))
        return "";
    
    ob = all_inventory(E(TO));
    ob = FILTER_PLAYERS(ob);
    ob = FILTER_CAN_SEE(ob, TO);
    ob -= filter(ob, &->query_wiz_level());
    
    if (!sizeof(ob))
	return "";
    
    who = ob[random(sizeof(ob))];
    
    ob = all_inventory(who);
    ob = FILTER_CAN_SEE(ob, TO);

    if (!sizeof(ob))
        return "";

    what = ob[random(sizeof(ob))];
    
    if (what->query_no_show_composite() || what->query_prop(OBJ_M_NO_STEAL) ||
        what->query_prop(OBJ_M_NO_DROP) || what->query_prop(OBJ_M_NO_GIVE) ||
        what->query_worn() || what->query_wielded() || what->query_held())
	return "";
        
    if (what->query_value() < (who->query_average_stat() - 20) && random(2))
    {
	if (who->query_skill(SS_AWARENESS) > random(50) + 50)
	    who->catch_msg("You catch " + QTNAME(TO) + 
                " rifling through your private belongings.\n");
	else
	    what->move(TO);
    }
    else
    {
	switch(random(3)) 
	{
	case 0:  
	    command("say Where did this come from?");
	    if (random(2))
		break;
	case 1:  
	    command("say Is that yours?");
	    if (random(2))
		break;
	case 2:  
	    command("say I must have found it somewhere.");
	    if (random(2))
		break;
	case 3:
	    command("say You must have lost it. What would have happened " +
                "if I hadn't found it?");
	}
	tell_room(QCTNAME(TO) + " gives " + LANG_ASHORT(what) + " to " + 
            QTNAME(who) + ".\n", who);
	who->catch_msg(QCTNAME(TO) + " gives you " + LANG_ASHORT(what) + 
            ".\n");
    }
    return "";
}

/*
 * This function was badly broken.
 * I'll assume it was meant to drop a thing which was not 
 * one of the things the kender booted with.
 */
string
do_drop()
{
    object *ob;

    ob = all_inventory(TO);
    ob = FILTER_CAN_SEE(ob, TO);
    ob = filter(ob, &->query_prop(KENDER_STOLEN_ITEM));

    if (sizeof(ob))
    {
        command("drop " + OB_NAME(ob[random(sizeof(ob))]));
    }
    return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    /* If it come from somewhere but the void, it's something 
     * we might drop. */
    if (objectp(from))
    {
        ob->add_prop(KENDER_STOLEN_ITEM, 1);
    }
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (ob->query_prop(KENDER_STOLEN_ITEM))
    {
        ob->remove_prop(KENDER_STOLEN_ITEM);
    }
}
