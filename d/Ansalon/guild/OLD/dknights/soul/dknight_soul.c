/*
 * File Name        : dknight_soul.c
 * By               : Elmore.
 * Date             : April 2001.
 * 
 */ 

#pragma strict_types
#pragma save_binary
#pragma no_clone

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include "/d/Ansalon/common/defs.h"

private int order_members(object a, object b);

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
int 
query_cmd_soul() 
{ 
    return 1; 
}

/*
 * Function name: query_cmdlist
 * Description:   Get the commands available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
query_cmdlist()
{
    return ([
            /* Command name : Function name */
              "dkeyes"       : "dkeyes",
              "reap"         : "reap",
              "assault"      : "dassault",
              "help"         : "help",
              "ddesintegrate": "ddesintegrate",
              "dlist"        : "dlist"
           ]);
}

int
dkeyes(string str)
{
    write("You orange-red eyes flares up in anger.\n");
    return 1;
}


int
dassault(string str)
{
    object ob, *obj, *oblist;
    string how;

    /* What are we attacking anyway? */
    if (strlen(str))
    {
	if (!sizeof(obj = parse_this(str, "[the] %l")))
	{
	    notify_fail("Choose thing is not alive!\n");
	    return 0;
	}

	ob = obj[0];
    }
    /* if the player doesn't specify a target, we assume the player's
     * current enemy.
     */
    else if (!(ob = TP->query_attack()))
    {
	notify_fail("But you aren't in combat with anyone!\n");
	return 0;
    }

    /* Does attacker have the skill? */
    if (!(TP->query_skill(SS_GUILD_SPECIAL_DASSAULT)))
    {
	write("You should learn how to assault first.\n");
	return 1;
    }

    /* Is the attacker already busy? */
    if(TP->query_reap() || TP->query_dassault())
    {
	write("Patience is a virtue! You are not ready to assault again.\n");
	return 1;
    }

    /* Are we even allowed to attack it?  Use can_attack_with_occ_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = TP->can_attack_with_dassault_special(ob, "dassault")))
    {
	write(how);
	return 1;
    }

    /* The shadow takes care of the rest */
    TP->dassault(ob);

    return 1;
}


int
reap(string str)
{
    object ob, *obj, *oblist;
    string how;

    /* What are we attacking anyway? */
    if (strlen(str))
    {
	if (!sizeof(obj = parse_this(str, "[the] %l")))
	{
	    notify_fail("Choose thing does not have any lifeforce for you to reap.\n");
	    return 0;
	}

	ob = obj[0];
    }
    /* if the player doesn't specify a target, we assume the player's
     * current enemy.
     */
    else if (!(ob = TP->query_attack()))
    {
	notify_fail("But you aren't in combat with anyone!\n");
	return 0;
    }

    /* Does attacker have the skill? */
    if (!(TP->query_skill(SS_GUILD_SPECIAL_REAP)))
    {
	write("You should learn how to reap first.\n");
	return 1;
    }

    if(TP->query_alignment() > -500)
    {
	write("You begin to feel sorry for your victim, and thus decide "+
              "to abandon your reap.\n");
	return 1;
    }

    /* Is the attacker already busy? */
    if(TP->query_reap() || TP->query_dassault())
    {
	write("Patience is a virtue! You are not ready to reap again.\n");
	return 1;
    }

    /* Are we even allowed to attack it?  Use can_attack_with_occ_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = TP->can_attack_with_reap_special(ob, "reap")))
    {
	write(how);
	return 1;
    }

    /* The shadow takes care of the rest */
    TP->reap(ob);

    return 1;
}

int
help(string str)
{
    if (str == "sash")
    {
        write("The crystal ring of Lord Soth can do this:\n" +
        "--------------------------------------------------------------------------------\n" +
        "- blist            - Get a list of the death knights currently haunting Genesis \n");
        write("--------------------------------------------------------------------------------\n" +
        "You can also wear and remove the ring.\n");
        return 1;
    }
    return 0;
}


private int
filter_dknights(object who)
{
    string coven;

    if (!who->query_guild_member(GUILD_NAME))
        return 0;

    if (who == TP)
        return 1;

    /* Wizards see everyone */
    if (TP->query_wiz_level())
        return 1;

#ifndef DA_TESTING
    /* Wizards are not shown to mortals */
    if (who->query_wiz_level())
        return 0;

    /* Wizards jr are not shown to mortals */
    if (extract(who->query_real_name(), -2) == "jr")
        return 0;
#endif DA_TESTING

    return 1;
}

mixed
make_list(object *members)
{
    string name, title, str1, str2, list = "";
    int i, size, cnt = 0;

    size = sizeof(members);
    i = -1;
    while (++i < size)
    {    
        str1 = SECURITY->query_wiz_pretitle(members[i]);
        str2 = "";

        if (strlen(name = members[i]->query_name()))
        {
            str1 += (strlen(str1) ? " " + name : name);
        }
        else
        {
            continue;
        }

        if (strlen(title = members[i]->query_guild_title_occ()))
        {
            str1 += (strlen(str1) ? " the " + title : capitalize(title));
        }

        if (TP->query_wiz_level())
        {
            str2 = "(" + (members[i]->query_wiz_level() ? "wiz" :
              members[i]->query_average_stat()) + ")";
        }

        cnt++;
        list += sprintf("- %=-68s %-5s\n", str1, str2);
    }
    
    return ({ list, cnt });
}

int
dlist()
{
    mixed tmp;
    string list;
    int cnt;
    object *members;

    write("These Death Knights currently haunt the Realm:\n");
    write("----------------------------------------------\n");
    members = sort_array(filter(users(), filter_dknights), order_members);

    tmp = make_list(members);
    list = tmp[0];
    cnt = tmp[1];

#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    /* If there is a room where statues of linkdead people can be found,
     * we add that to the list.
     */
    members = filter((all_inventory(find_object(OWN_STATUE)) - members), 
        &not() @ &->query_npc());
    members = sort_array(filter(members, filter_dknights), order_members);
    tmp = make_list(members);
    if (cnt = tmp[1])
    {
        list += "\nCurrently guarding Dargaard Keep " + (cnt > 1 ? "are:\n" : "is:\n");
        list += tmp[0];
    }
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD



    if (query_verb()[0..0] == "m")
    {
        setuid();
        seteuid(getuid());
        TP->more(list);
    }
    else
    {
        write(list);
    }

    return 1;
}

private int
order_members(object a, object b)
{
    int ai, bi;
    

    ai = a->query_guild_level_occ();
    bi = b->query_guild_level_icc();

    if (ai < bi)
        return 1;
    if (ai > bi)
        return -1;

    ai = a->query_guild_level_occ();
    bi = b->query_guild_level_occ();

    return ((ai < bi) ? 1 : (ai == bi ? 0 : -1));  
}


//------------------------------- E M O T E S -------------------------------\\

int 
ddesintegrate(string str) 
{ 
    object *ob;
    object obj;

    if(!strlen(str))
    {
       notify_fail("Desintegrate what?\n"); 
       return 0;
    }

    ob = parse_this(str, "%i");

    if(!sizeof(ob))
    {
       notify_fail("Desintegrate what ?\n"); 
       return 0;
    }

    obj = ob[0];

    if (environment(obj) != TP)
    { 
        notify_fail("You are not carrying that item.\n"); 
        return 0; 
    }


    actor("You stare at your", ob," and begin to concentrate."); 
    all2act(" stares at "+ HIS(TP)+ "",ob," and begins to concentrate."); 

    set_alarm(1.5,0.0, &actor("The",ob," is engulfed in bright blue flames.")); 
    set_alarm(1.5,0.0, &all2act("'s eyes flares up as the",ob," is engulfed "+ 
             "in bright blue flames.")); 

    set_alarm(2.5,0.0, &actor("The",ob," turns to into a fine dust and "+ 
              "blows away in the wind.")); 
    set_alarm(2.5,0.0, &all2act(" drops the",ob," on the ground as it turns into "+ 
              "a fine dust and blows away in the wind.")); 

    set_alarm(2.6,0.0, &obj->remove_object());

    return 1; 

} 
