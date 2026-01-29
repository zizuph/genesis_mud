/*
 * draconian_mask.c
 *
 * Created by Milan.
 *
 * This is guard draconian. It has changed acts and also it
 * is not followed by team members (others should stay on guard even
 * if this one runs in panic)
 * This file should be included after something like:
 *
 * inherit "/d/Krynn/std/aurak";
 */


/* Altered June 7th 2006 by Navarre
 * Draconians now assist eachother, but I kept them not in team
 * as to not ruin what Milan had intended with them. One scared 
 * out with fear, wont bring a team with him.
 */


#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

int is_fight_helper = 0;
int num_of_helpers = 0;
int hunt_alarm = 0;
int attacker_alarm = 0;

void
set_fight_helper()
{
    is_fight_helper = 1;
}

int
check_for_attack()
{
    return ATTACKERS_ADMIN->query_auto_attack(this_object(),this_player());
}

void
set_draconian_acts()
{
    set_aggressive(check_for_attack);
    set_cact_time(random(3) + 5);
    add_cact("emote snarls: You really think you can defeat me?");
    add_cact("emote grunts: Ahhh, now I can test my battle skill.");
    add_cact("emote snarls: I didn't even feel that!");
    add_cact("emote snarls: Is that all you can do?");
    add_cact("emote whispers: Don't take it personally but I'll kill you.");
    add_cact("grin");
}

varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    return ::move_living(how, to_dest, 1, 1);
}

void
remove_prop(string prop)
{
    if(prop != LIVE_O_ENEMY_CLING)
	::remove_prop(prop);
}

void
do_hunt_enemy(object who, string cmd)
{
    if (!stringp(cmd) || !objectp(who))
	return;
    command(cmd);
    hit_me(0, 0, who, 0);
    who->hit_me(0, 0, this_object(), 0);
    hunt_alarm = 0;
}

object
query_hunt_enemy()
{
    object who = previous_object(-1)->qme();
    string com, cmd = who->query_prop(LIVE_S_LAST_MOVE);
    string rest;

    if(hunt_alarm || !who->check_seen(TO))
	return 0;

    if (com = environment()->query_dircmd())
    {
        cmd += " " + com;
    }
    if(hunt_alarm)
    {
        remove_alarm(hunt_alarm);
    }
    hunt_alarm = set_alarm(0.0, 0.0, &do_hunt_enemy(who, cmd));
    return 0;
}

void
set_hunt_enemy(int i)
{
    if(i)
	add_prop(LIVE_O_ENEMY_CLING, query_hunt_enemy);
    else
	::remove_prop(LIVE_O_ENEMY_CLING);
}

void
do_die( object killer )
{
    // ATTACKERS_ADMIN->add_reputation(killer,CRIME_MURDER);
    environment()->draconian_guard_died();
    ::do_die(killer);
}

void print_attack_msg(object drac, object attacker)
{
    if(attacker && drac)
    {
        drac->attack_object(attacker);
        attacker->catch_msg(QCTNAME(drac)+" attacks you!\n");
        tell_room(environment(attacker), QCTNAME(drac)+" attacks "+QTNAME(attacker)+"!\n", attacker);
    }
}


void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    // ATTACKERS_ADMIN->add_reputation(attacker,CRIME_ATTACK);
    object* room_items = all_inventory(environment(attacker));
    string* names = ({});
    for(int i = 0; i<sizeof(room_items); i++)
    {
      if(living(room_items[i]) && !interactive(room_items[i]))
      {
        names = room_items[i]->query_names();
        for(int j = 0; j<sizeof(names); j++)
        {
          if(names[j]=="draconian")
          {
              if(attacker_alarm)
              {
                  remove_alarm(attacker_alarm);
              }
              attacker_alarm = set_alarm(0.0, 0.0, &print_attack_msg(room_items[i], attacker));
            break;
          }
        }   
      }
    }
}

public int
special_attack(object victim)
{
    object drac;

    if(!random(100) && !is_fight_helper && num_of_helpers < 4)
    {
	num_of_helpers++;
	switch(random(11))
	{
	case 0:
	    drac = clone_object(DRAGONARMY_NPC+"aurak");
	    break;
	case 1:
	case 2:
	    drac = clone_object(DRAGONARMY_NPC+"sivak");
	    break;
	case 3:
	case 4:
	    drac = clone_object(DRAGONARMY_NPC+"bozak");
	    break;
	case 5:
	case 6:
	case 7:
	    drac = clone_object(DRAGONARMY_NPC+"kapak");
	    break;
	default:
	    drac = clone_object(DRAGONARMY_NPC+"baaz");
	}
	drac->set_fight_helper();
	drac->set_color(query_color());
	drac->arm_draconian();
	drac->set_hunt_enemy(1);
	drac->move_living("M", environment(), 1, 1);
	tell_room(E(TO), QCNAME(drac)+" rushes in attracted by the noise.\n");
	drac->command("kill " + OB_NAME(victim));
    }

    return ::special_attack(victim);
}

int
query_not_accept_member(object ob)
{
    if(ob->query_color() == query_color())
	return 0;
    return 1;
}

