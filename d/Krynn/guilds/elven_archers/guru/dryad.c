// 2021-04-24 : Dryad evade lowered from 33% to 25%
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "../guild.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit "/std/monster";

void remove_me(object me);

object  gArcher;
string *gSublocs = ({});

public void
set_archer(object archer)
{
    gArcher = archer;
}

public void
forceful_ejection()
{
    object *eject = ({});
    
    if (objectp(gArcher))
    {
        eject = filter(all_inventory(environment(this_object())), interactive);
        eject -= ({ gArcher });
        
        if (!sizeof(eject))
            return;
        
        eject->move((BISLAND + "tower01"), 1);
        eject->catch_msg("An unknown force pushes you up the stairs.\n");
    }
}

void
create_monster()
{
    set_race_name("dryad");
    set_name("dryad");
    add_name("_dryad");
    set_long("A corrupted dryad, grown to absorb and cleanse the corruption "
    + "in the reflection pool.\n");

    set_stats(({ 100, 100, 100, 100, 100, 100 }));

    set_skill(SS_DEFENCE, 75);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);
    
    set_skill(SS_WEP_MISSILE, 90);

    set_alignment(0);
    set_all_hitloc_unarmed(40);
    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    set_aggressive(1);

    add_notify_meet_interactive(forceful_ejection);
    
    set_alarm(1800.0, 0.0, &remove_me(this_object()));
}

void
remove_me(object me)
{
    if (!me)
        return;
  
    object* players = FILTER_PLAYERS(all_inventory(environment(me)));
    if (sizeof(players))
        set_alarm(1800.0, 0.0, &remove_me(me));
    else
        me->remove_object();
}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    clone_object(DRYAD_BOW)->move(this_object(), 1);
    command("wield all");
}

void
print_msg(object me)
{
    tell_room(environment(me), QCTNAME(me) + " seems to have recovered.\n");
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(0.0, 0.0, &print_msg(this_object()));
    set_hp(query_max_hp());
}

int
special_attack(object enemy)
{
    if (!(GUILD_GURU + "quickshot")->query_ability_active(this_object()))
        (GUILD_GURU + "quickshot")->do_ability("");
}

/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 *                  If fail, the cause must produce explanatory text himself.
 * Arguments:       attacker: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
public int
query_not_attack_me(object attacker, int aid)
{
    object  player;
    int     rnd_msg;
    string  avoiding,
           *player_msg,
           *target_msg,
           *others_msg;
    
    if (!random(4))
        return 0;
        
    player = this_object();
    
    avoiding = one_of_list(({
        "evading", "dodging", "avoiding"
    }));
    
    player_msg = ({
        "You leap back to distance yourself from "
        + attacker->query_the_name(player) + ", " + avoiding
        + " an attack in the process.\n",
        "You sidestep in an attempt to distance yourself from "
        + attacker->query_the_name(player) + " successfully " + avoiding
        + " an incoming attack.\n",
        "You retreat a few steps to increase the distance between yourself and "
        + attacker->query_the_name(player) + ".\n"
    });
    
    target_msg = ({
        player->query_The_name(attacker) + " suddenly leaps back, distancing "
        + player->query_objective() + "self from you, just narrowly " + avoiding
        + " your attack in the process.\n",
        player->query_The_name(attacker) + " sidesteps your attack and "
        + "attempt to increase the distance between "
        + player->query_objective() + "self and you.\n",
        player->query_The_name(attacker) + " retreats a few steps in order to "
        + "distance " + player->query_objective() + "self from you.\n"
    });
    
    others_msg = ({
        QCTNAME(player) + " leaps back in an attempt to distance " 
        + player->query_objective() + "self from " + QTNAME(attacker) + ", "
        + "narrowly " + avoiding + " " + QTPNAME(attacker) + " attack.\n",
        QCTNAME(player) + " sidesteps " + QTPNAME(attacker) + " attack and "
        + "increases the distance between them.\n",
        QCTNAME(player) + " retreats a few steps away from " + QTNAME(attacker)
        + " increasing the distance between them.\n"
    });

    rnd_msg = random(sizeof(player_msg));
    
    player->catch_msg(player_msg[rnd_msg]
    + (aid == -1 ? "Your maneuvering had a monumental effect on "
    + attacker->query_the_possessive_name(player)
    + " offensive strategy.\n" : ""));
    
    attacker->catch_msg(target_msg[rnd_msg]
    + (aid == -1 ? player->query_The_possessive_name(attacker)
    + " maneuvering had a monumental effect on your offensive "
    + "strategy.\n" : ""));
    
    player->tell_watcher(others_msg[rnd_msg], ({ attacker }));
    return 1;
}

public string *
query_sublocs()
{
    if (objectp(gArcher))
        return gArcher->query_sublocs();
    
    return ::query_sublocs();
}

varargs public mixed 
show_cont_subloc(string sloc, object for_obj)
{
    if (!objectp(gArcher))
        return ::show_cont_subloc(sloc, for_obj);
 
    string  desc = "";
    
    if (!sizeof(gSublocs))
    {
        gSublocs = query_sublocs();
        gSublocs -= ({"_subloc_misc_extra", "worn_a", "held", "wielded"});
    }
    
    if (IN_ARRAY(sloc, gSublocs))
    {
        foreach(string sub: gSublocs)
        {
            desc += gArcher->show_cont_subloc(sub, this_object());
        }
    }

    if (!stringp(::show_cont_subloc(sloc, for_obj)))
        return desc;
    
    return desc + ::show_cont_subloc(sloc, for_obj);
}

/*
 * Function name: query_height_desc
 * Description  : Find out the height description of the living.
 * Returns      : string - the height description.
 */
public string
query_height_desc()
{
    if (objectp(gArcher))
        return gArcher->query_height_desc();
    
    return ::query_height_desc();
}

/*
 * Function name: query_width_desc
 * Description  : Find out the width description of the living.
 * Returns      : string - the width description.
 */
public string
query_width_desc()
{
    if (objectp(gArcher))
        return gArcher->query_width_desc();
    
    return ::query_width_desc();
}


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    object seed = present("_archer_guru_quest_seed_");
    
    if (objectp(seed))
        seed->move(environment(this_object()), 1);
    
    all_inventory(this_object())->remove_object();
    
    tell_room(environment(this_object()), 
        QCTNAME(this_object()) + " withers and dies, leaving behind a silvery "
        + "willow-wood sprout.\n", this_object());
}