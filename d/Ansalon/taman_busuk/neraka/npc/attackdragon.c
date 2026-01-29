/* Carridin, 27 Nov 97
   A dragon that buggers about in the skies above Neraka
	based on youngblue.c
*/

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"


inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";

object *gHunted = ({ });
int gHaveSetTrigger = 0;

void
create_dragon_npc()
{
    set_age("adult");
    set_colour("red");
    set_gender(0);
    set_long("You see before you a great winged beast. " +
        "His scales ripples as he moves with a serpentlike grace, " +
		"and his awesome claws scratch the ground as he moves.\n");

    add_prop(CONT_I_WEIGHT, 1300000);
    add_prop(CONT_I_VOLUME, 1200000);

    set_aggressive("@@check_for_attack@@");
    ::create_dragon_npc();
}

int
check_for_attack()
{
    return TP->query_prop(NERAKA_I_ATTACKED_TEMPLE) || ATTACKERS_ADMIN->query_know_person(0, TP);
}

void
init_living()
{
    init_attack();
    ::init_living();
}

int
test_friend(object who)
{
    if (::test_friend(who))
        return 1;
/* Navarre added Dragonarmy here, if priests are friends, then so
 * are dragonarmies. */
    if (who->query_guild_name_occ() == "Priests of Takhisis" ||
        who->query_guild_name_occ() == "Dragonarmy")
        return 1;

    if (who->id("zombie") || who->id("_templeguard_"))
        return 1;

    return 0;
}

int
test_breath_friend(object who)
{
    int j;
    object *enemy_team;
    object t;

    if (::test_friend(who))
        return 1;

    t = query_attack();
    enemy_team = ({ });

    /* is there a better way to do this? */
    while(objectp(t))
    {
    	enemy_team |= ({ t }) + t->query_team_others();
    	t = t->query_leader();
    }
    
    if (member_array(who, enemy_team) >= 0)
        return 0;
    else
        return 1;
}

int
special_attack(object enemy)
{
    int attacktype;
    mixed* hitresult;
    object me, *ob, *ob2;
    int i;

    me = this_object();

/* disabled 981116 by Ashlar because it seems to be buggy.
Though it's beyond me how this simple code could bug out
	if (query_hp() * 10 < query_max_hp())
	{
    	say(QCTNAME(TO) + " leaps up into the skies, escaping the battle.\n");
    	remove_object();
	}
        */


    if (forced_attacktype == 0)   /* no forced special attack this turn */
        attacktype = random(5);
    else
        attacktype = forced_attacktype;

    if (attacktype == 1)
    {
        if (forced_attacktype == 0)
        {
            /* Dragon inhales air, forced next attack to be cloud breath */

            tell_room(E(TO), QCTNAME(TO)+" rises to "+POSSESSIVE(TO)+" full "+
              "height, and you hear a sharp intake of breath as "+PRONOUN(TO)+
              " rears back "+POSSESSIVE(TO)+" head...\n", TO);
            forced_attacktype = 1;
            return 1;
        }

        tell_room(E(TO), "As "+QTNAME(TO)+"'s head descends, "+breath_weapon,
          TO);

        ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
        ob2 = ob + ({ });

        /* Remove friends from breath victims */

        for (i = 0; i < sizeof(ob2); i++)
        {
            if(test_breath_friend(ob2[i]))
                ob -= ({ ob2[i] });
        }

        for (i = 0; i < sizeof(ob); i++)
        {
            penet -= penet * ob[i]->query_magic_res(res_prop) /100;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

            how_str = how[0];
            if (hitresult[0] > 0)
                how_str = how[1];
            if (hitresult[0] > 10)
                how_str = how[2];
            if (hitresult[0] > 20)
                how_str = how[3];
            if (hitresult[0] > 40)
                how_str = how[4];
            if (hitresult[0] > 60)
                how_str = how[5];

            ob[i]->catch_msg("You are "+how_str+" by the dragon breath!\n");
            tell_watcher(QCTNAME(ob[i]) + " is "+how_str+" by the dragon "+
              "breath!\n", ob[i]);

            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        forced_attacktype = 0;
        return 1;
    }

    return 0;
}

int
set_hunting(object ob)
{
    if(!ob)
        return 0;

    if (!gHaveSetTrigger)
        trig_new("%s 'leaves' / 'sneaks' / 'panics' [and] [flees] [limping] %w",
        "react_leave");
    gHaveSetTrigger = 1;
    if (member_array(ob, gHunted) == -1)
    {
        gHunted += ({ ob });
    }
    gHunted -= ({ 0 });
    return 1;
}

int set_hunting_name(string name) { return set_hunting(find_player(name)); }

void
do_follow_player(object ob, string cmd)
{
    object room;
    
    if (!objectp(ob))
        return;
    
    room = environment(ob);
    if (!objectp(room))
        return;
    
    if (room->query_prop(ROOM_I_INSIDE))
         return;
    
    this_object()->command(cmd);
}

void
react_leave(string name, string dir)
{
    object tone;
    tone = find_player(lower_case(name));
    if(!tone)
    {
        return;
    }
    if(member_array(tone,gHunted) != -1)
    {
        dir = extract(dir,0,-3);
        set_alarm(0.0, 0.0, &do_follow_player(tone, dir));
        return;
    }
}

int
second_life(object killer)
{
    setuid();
    seteuid(getuid());
    A_KILL_LOG("pot/npckills","Bastard attack dragon",killer);
    return 0;
}

mixed query_age()
{ 
	if (calling_object() == this_object())
		return ::query_age();
	else
		return 0; 
}
