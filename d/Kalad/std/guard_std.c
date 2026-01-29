inherit "/d/Kalad/std/monster"; 
#include "/d/Kalad/defs.h"
/* This is so that any guards on the list recognize eachother and help  */
/* eachother when being attacked, regardless if they are teamed or not. */
/* Sarr */

string *list_friends();

void
create_monster()
{
    ::create_monster();
    trig_new("%w 'attacks' %s", "react_attack");
}


void
kill_undead(object ob)
{
    command("kill "+lower_case(ob->query_name()));
}




int
react_attack(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(2.0,0.0,"return_attack",who);
	return 1;
    }
}

do_die(object who)
{
    object room;
    who->add_prop(IS_ENEMY_OF_DRAKMERE,who->query_prop(IS_ENEMY_OF_DRAKMERE)+1);
    if(who->query_prop(IS_ENEMY_OF_DRAKMERE) > 5 && 
      who->query_average_stat() > 130)
    {
	call_other("/d/Kalad/common/raum/drakmere/holy_room","??");
	room = find_object("/d/Kalad/common/raum/drakmere/holy_room");
	room->summon_gilbert(who);
    }
    ::do_die(who);
}


void
return_attack(string who)
{
    object obj;
    object victim;
    if(obj = present(who, environment()))
    {
	victim = obj->query_attack();
	if(victim == TO) /* This is me who hes attacking!! */
	    return;
	if(victim->query_prop(LIVE_I_UNDEAD)) /* Guards won't help undead */
	    return;
	if(victim->query_npc()) /* Ignore Player Fights */
	{
	    command("kill " + (obj->query_real_name()));
	}
    }
}


void
attacked_by(object enemy)
{
    int i,a;
    object *people;
    string *target;
    string *friends = list_friends();
    people = FILTER_LIVE(all_inventory(E(TO)));
    people -= ({TO});
    ::attacked_by(enemy);
    for(i=0;i<sizeof(people);i++)
    {
	for(a=0;a<sizeof(friends);a++)
	{
	    target = explode(file_name(people[i]),"#");
	    if(target[0] == friends[a])
		set_alarm(2.0,0.0,"call_friends",people[i],enemy);
	}
    }
}

void
call_friends(object friend, object enemy)
{
    friend->aid_guard(enemy);
    friend->special_attack(enemy);
}

string
*list_friends()
{
    return 
    /*RAUMDOR GUARDS LIST, they help eachother out*/
    ({"/d/Kalad/common/raum/drakmere/npc/dguard",
      "/d/Kalad/common/raum/drakmere/npc/dguard_s",
      "/d/Kalad/common/raum/drakmere/npc/eg_guard",
      "/d/Kalad/common/raum/drakmere/npc/eg_guard_s",
      "/d/Kalad/common/raum/drakmere/npc/drakmere",
      "/d/Kalad/common/raum/drakmere/npc/dguard_cap", 
      "/d/Kalad/common/raum/drakmere/npc/dguard_chief"});
    /* Add any guards you want to help eachother to the list */
}


void aid_guard(object ob) /* You can redefine this in your guard if you like */ 
{
    if(ob->query_attack() && present(ob,E(TO)))
    {
	command("kill " + lower_case(ob->query_real_name()));
    }
}

void
init_living()
{
    object who;
    ::init_living();
    if(TP->query_prop(LIVE_I_UNDEAD))
    {
	set_alarm(0.5,0.0,"kill_undead",TP);
    }
    if(TP->query_prop(IS_ENEMY_OF_DRAKMERE))
    {
	command("kill "+lower_case(TP->query_name()));
	return;
    }
    if(TP->query_attack())
    {
	who = TP->query_attack();
	if(!who->query_prop(LIVE_I_UNDEAD))
	    if(who->query_npc())
		set_alarm(2.0,0.0,"aid_guard",TP);
    }
}


