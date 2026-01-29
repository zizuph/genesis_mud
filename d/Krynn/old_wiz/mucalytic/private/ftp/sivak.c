#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/draconian.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

inherit DRACONIAN;

int alarm;
string *save;

/*
 * Function name: set_sivak_skills
 * Description:   Calc and set the stats and skills for the draconian.
 */
nomask static void
set_sivak_skills()
{
    int i, level;

    for (i = 0; i < 6; i++) /* 70 - 126 */
        set_base_stat(i, (random(6) + 4) * 10 + 30 + random(7));

    level = query_draconian_level();

    set_skill(SS_2H_COMBAT,   80 + random(21));
    set_skill(SS_DEFENCE,     level * 6 + random(20) + 20);
    set_skill(SS_PARRY,       level * 6 + random(8) + 20);
    set_skill(SS_WEP_SWORD,   level * 6 + random(8) + 20);
    set_skill(SS_WEP_KNIFE,   level * 6 + random(8) + 20);
    set_skill(SS_WEP_CLUB,    level * 6 + random(8) + 20);
    set_skill(SS_WEP_POLEARM, level * 6 + random(8) + 20);
    set_skill(SS_WEP_JAVELIN, level * 6 + random(8) + 20);
    set_skill(SS_WEP_AXE,     level * 6 + random(8) + 20);
    set_skill(SS_AWARENESS,   level * 5);

    set_draconian_alignment();
}

/*
 * Function name: create_sivak
 * Description:
 */
public void
create_sivak()
{
}

/*
 * Function name: create_draconian
 * Description:
 */
nomask public void
create_draconian()
{
    int i;

    set_sivak_skills();
    set_draconian_type(SIVAK);

    create_sivak();

    if (!query_long())
        set_default_long();

    set_name("sivak");

    add_prop(OBJ_I_RES_FIRE, 100);
    add_prop(OBJ_I_RES_ACID, 80);    

    add_act("emote flaps its wings, making some dust swirl around.");
}

/*
 * Function name: special_draconian_attack
 * Description:   Called from the draconian special_attack
 *                routine. By redefining this, draconians can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 */
public int
special_draconian_attack(object victim)
{
    object *wep;
    mixed tmp;
    
    tell_room(E(TO), QCTNAME(TO) + " starts to flap its wings and stirs" +
	      " the dust around you.\n");
    victim->catch_msg("Before you are able to react the " + QTNAME(TO) +
		      " is behind you and stabs you in the back.\n");
    tell_room(E(TO), "Before " + QTNAME(victim) + " is able to react " +
	      "the " + QTNAME(TO) + " has flown past " +
	      victim->query_objective() + " and hits " + 
	      victim->query_objective() + " in the back.\n", victim);

    victim->hit_me(random(15) + 15, W_IMPALE, TO, -1);

/*    wep = query_weapon(-1);

    if (pointerp(wep))
      tmp = victim->hit_me(wep[0]->query_pen(), wep[0]->query_dt(), TO, -1);
*/
    
    return 1;
}

/*
 * Function name: second_life
 * Description:
 * Arguments:     killer - 
 * Returns:
 */
public int
second_life(object killer)
{
    object corpse, *team;

    if (living(killer))
    {
	team = killer->query_team_others();
	tell_room(E(TO),"The draconian bursts into flames!\n");
  
	corpse = clone_object(FLAMES);
	corpse->set_my_victims(({ killer }) + team);
	corpse->move(E(TO));
    }
}

/*
 * Function name: notify_you_killed_me
 * Description:   This function is called by the victim to the killer (this
 *                object) during the death sequence. It will pass on infor-
 *                mation to the transformation function.
 * Arguments:     obj (The object killed by this object.)
 * Returns:       Does not return a value.
 */

void notify_you_killed_me(object obj)
{
    mixed *data = ({ });

    if(LIVING(obj))
    {
        data += ({ RNAME(obj) });
        data += ({ RACEN(obj) });
        data += ({ obj->query_adj(1), 0 });

        if(!pointerp(get_alarm(alarm)))
            alarm = set_alarm(itof(2 + random(4)), 0.0, "transform", data);
    }
}

/*
 * Function name: transform
 * Description:   This is the function that transforms the Sivak to make it
 *                appear like the last person it killed.
 * Arguments:     name  : This is the name of the victim.
 *                race  : The race of the victim.
 *                adj   : The adjectives of the victim.
 *                index : Which part of the transformation sequence.
 * Returns:       Does not return a value.
 */

void transform(string name, string race, string *adj, int index)
{
    switch(index)
    {
        case 0:
        {
            save = ({ RNAME(TO), RACEN(TO), TO->query_adj(1) });
    
            tell_room(E(TO), QCTNAME(TO)+" seems to shimmer magically.\n", TO);
        }
        case 1:
        {
            tell_room(E(TO), QCTNAME(TO)+" screams, "+POSSESSIVE(TO)+
                "voice the embodiment of pure evil.\n", TO);
            break;
        }
        case 2:
        {
            tell_room(E(TO), QCTNAME(TO)+" begins to undergo an amazing "+
                "transformation.\n", TO);
            break;
        }
        case 3:
        {
            tell_room(E(TO), "The wings on "+LANG_POSS(QTNAME(TO))+" back "+
                "shrink into "+POSSESSIVE(TO)+" back and disappear.\n", TO);
            break;
        }
        case 4:
        {
            tell_room(E(TO), LANG_POSS(QTNAME(TO))+" fangs draw back into "+
                POSSESSIVE(TO)+" mouth and "+POSSESSIVE(TO)+" claws become "+
                "smaller and more rounded.\n", TP);
            break;
        }
        case 5:
        {
            tell_room(E(TO), LANG_POSS(QTNAME(TO))+" reptilian scales "+
                "seem to soften and slowly form into "+race+" skin.\n", TO);
            break;
        }
        case 6:
        {
            tell_room(E(TO), "With a final bloodcurdling scream, "+
                QTNAME(TO)+" shrinks dramatically in size and suddenly "+
                "appears much different.\n", TO);

            set_race_name(race); set_name(name); set_adj(adj);
            break;
        }
    }

    index ++;

    if(index < 7)
        alarm = set_alarm(1.0, 0.0, "transform", ({ name, race, adj, index }));
}
