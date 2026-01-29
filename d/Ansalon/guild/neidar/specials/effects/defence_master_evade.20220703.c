/*
* Neidar Defence Master
*
* Neidar gain a 40% combat aid evade bonus for a limited
* time (30 seconds).  5 minute cooldown.
*
* Louie Oct 2008
*
*/

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Genesis/specials/defs.h"
#include "../../guild.h"

inherit EVADE_OBJ_BASE;

#include DEBUGGER_TELL

public object find_shield(object player);
public object find_weapon(object player);

/*
* Function     : create_effect
* Description  : The create function called for objects that inherit this
* Arguments    : none
* Returns      : nothing
*/
public void
create_effect()
{
    set_name("_neidar_defence_master_object_");
    add_name( ({"neidar_defence_master_object" }) );
    set_short("hidden neidar defence master evade object");
    set_long("The object that grants evade to "
        + "Neidars.  This should not be visible by players.\n");

    setuid();
    seteuid(getuid());

    set_evade_stats( TS_CON );
    set_evade_skills( SS_DEFENCE );

    set_evade_combat_aid(DEFENCE_MASTER_AID);
}

/*
 * Function:    is_neidar_defence_master_object
 * Description: Allows filters to identify this particular object easily
 */
public int
is_neidar_defence_master_object()
{
    return 1;
}

/*
* Function     : remove_neidar_shield_object
* Description  : Destructor function.
* Arguments    : none
* Returns      : nothing
*/
public void
remove_neidar_defence_master_object()
{
    remove_object();
}

/*
* Function     : attack_blocked
* Description  : Function to display messages that the attack was
*                blocked.
* Arguments    : player    - player who is being attacked
*                attacker  - the person doing the attacking
*                attack_id - attack id location
* Returns      : nothing
*/
public void
attack_blocked(object player, object attacker, int attack_id)
{
    object* exclude_list;
    string player_descr, attacker_descr, watcher_descr;

    exclude_list = ({ player, attacker });

    object player_shield = find_shield(player);
    object player_weapon = find_weapon(player);
    object player_helmet = player->query_armour(TS_HEAD);
    object attacker_weapon = find_weapon(attacker);

    string* valid_player_desc = ({"Too late to avoid, you prepare yourself " +
        "for an incoming blow from "+QTNAME(attacker)+"." +
        " Taking the attacks full brunt with your " +
        "chest, you look at "+HIM(attacker) +
        " unwaveringly.\n",
        QCTNAME(attacker) + " lands a blow on your body " +
        "but you shrug off the attack as a giant " +
        "would shrug off a mosquito.\n",
        "With your feet dug firmly into the ground, you "+
        "do not yield an inch in response to "+QTNAME(attacker) +
        "'s devastating blow."});

    string* valid_attacker_desc = ({"You strike "+QTNAME(player)+" with full " +
        "force straight in the chest, but "+HE(player)+
        " looks at you unwaveringly.\n",
        "You land a blow on "+QTNAME(player)+"'s body, "+
        "but "+HE(player)+" shrugs off the attack.\n",
        "You deliver "+QTNAME(player)+" a devastating " +
    "blow, but "+HE(player)+" doesn't yield an inch.\n"});

    string* valid_watcher_desc = ({QCTNAME(attacker)+" strikes "+QTNAME(player)+
        " with full force straight in the chest, but "+
        QTNAME(player)+" looks at "+QTNAME(attacker)+" unwaveringly.\n",
        QCTNAME(attacker) + " lands a blow on "+QTNAME(player)+
        "'s body "+HE(player)+" shrugs it off like a giant "+
        "would shrug off a mosquito.\n",
        QCTNAME(attacker)+" delivers "+QTNAME(player)+
        " a devastating blow, but "+HE(player)+
    " didn't yield an inch.\n"});

    if(player_helmet && attacker_weapon)
    {
        string player_desc = "You react too slowly and "+QTNAME(attacker)+" hits you " +
        "in the head with "+HIS(attacker)+" "+attacker_weapon->short()+
        ", but your "+player_helmet->short()+" deflects the attack.\n";
        valid_player_desc = valid_player_desc + ({player_desc});

        string attacker_desc = QCTNAME(player)+" reacts too slowly, and you hit "+
        HIM(player)+" in the head with your "+attacker_weapon->short()+
        ", but "+HIS(player)+" "+player_helmet->short()+" deflects the attack.\n";
        valid_attacker_desc = valid_attacker_desc + ({attacker_desc});

        string watcher_desc = QCTNAME(player)+" reacts too slowly, and "+QTNAME(attacker) +
        " hits "+HIM(player)+" in the head with "+HIS(attacker)+" "+attacker_weapon->short()+
        ", but "+QTNAME(player)+"'s "+player_helmet->short()+" deflects the attack.\n";
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc});
    }

    if(player_weapon)
    {
        string player_desc = QCTNAME(attacker) + " tries to land a blow to " +
        "your body, but you manage to swipe it away with "+
        "your "+player_weapon->short()+" effortlessly.\n";
        valid_player_desc = valid_player_desc + ({player_desc});

        string attacker_desc = "You try to land a blow on "+QTNAME(player)+
        "'s body, but "+HE(player)+" manages to swip it away with "+
        HIS(player)+" "+player_weapon->short()+" effortlessly.\n";
        valid_attacker_desc = valid_attacker_desc + ({attacker_desc});

        string watcher_desc = QCTNAME(attacker) + " tries to land a blow to "+
        QTNAME(player)+"'s body, but "+QTNAME(player)+" manages to "+
        "swipe it away with "+HIS(player)+" "+player_weapon->short()+
        " effortlessly.\n";
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc});
    }

    if(player_shield)
    {
        string player_desc1 = "Roaring into the heavens, you cover yourself with your "+
        player_shield->short() + " deflecting " + QTNAME(attacker) +
        "'s oncoming assault.\n";
        string player_desc2 = "Putting your weight behind your "+player_shield->short() +
        ", you push "+QTNAME(attacker)+" back, forcing him to abandon " +
        HIS(attacker)+" attack.\n";
        string player_desc3 = "You drop to one knee while raising your "+player_shield->short() +
        " in order to block a powerful swing from "+QTNAME(attacker)+".\n";

        valid_player_desc = valid_player_desc + ({player_desc1});
        valid_player_desc = valid_player_desc + ({player_desc2});
        valid_player_desc = valid_player_desc + ({player_desc3});

        string attacker_desc1 = "Roaring into the heavens, "+QTNAME(player)+" covers "+
        HIM(player)+"self with "+HIS(player)+" "+player_shield->short()+
        " deflecting your oncoming assault.\n";
        string attacker_desc2 = "Putting "+HIS(player)+" weight behind "+HIS(player)+
        " "+player_shield->short()+ " "+HE(player)+" pushes you back, forcing you to "+
        "abandon your attack.\n";
        string attacker_desc3 = QCTNAME(player)+" drops to one knee while raising "+HIS(player)+
        " "+player_shield->short()+" in order to block your powerful swing.\n";

        valid_attacker_desc = valid_attacker_desc + ({attacker_desc1});
        valid_attacker_desc = valid_attacker_desc + ({attacker_desc2});
        valid_attacker_desc = valid_attacker_desc + ({attacker_desc3});

        string watcher_desc1 = "Roaring into the heavens, "+QTNAME(player)+" covers "+HIM(player) +
        "self with "+HIS(player)+" "+player_shield->short()+" deflecting "+ QTNAME(attacker)+
        "'s oncoming assault.\n";
        string watcher_desc2 = "Putting "+HIS(player)+" weight behind "+HIS(player)+
        " "+player_shield->short()+", "+QTNAME(player)+" pushes "+QTNAME(attacker)+
        " back, forcing "+HIM(attacker)+" to abandon "+HIS(attacker)+" attack.\n";
        string watcher_desc3 = QCTNAME(player)+" drops to one knee while raising "+HIS(player)+
        " "+player_shield->short()+" in order to block a powerful swing from "+
        QTNAME(attacker)+".\n";

        valid_watcher_desc = valid_watcher_desc + ({watcher_desc1});
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc2});
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc3});
    }
    else
    {
        string player_desc = "Absendmindedly you raise your arm as if to "+
        "block "+QTNAME(attacker)+"'s attack with a shield, "+
        "but it bounces off your rock hard forearm regardlessly.\n";
        valid_player_desc = valid_player_desc + ({player_desc});

        string attacker_desc = "Absendmindedly "+QTNAME(player)+" raises "+HIS(player)+
        " arm as if to block your attack with a shield, "+
        "but it bounces off "+HIS(player)+" rock hard forearm regardlessly.\n";
        valid_attacker_desc = valid_attacker_desc + ({attacker_desc});

        string watcher_desc = "Absendmindedly "+QTNAME(player)+" raises "+HIS(player) +
        "arm as if to block "+QTNAME(attacker)+"'s attack with a shield, "+
        "but it bounces off "+HIS(player)+" rock hard forearm regardlessly.\n";
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc});
    }

    if(player_shield && attacker_weapon)
    {
        string player_desc = "Sparks fly as you block "+QTNAME(attacker)+"'s " +
        attacker_weapon->short() + " with your "+player_shield->short()+".\n";

        valid_player_desc = valid_player_desc + ({player_desc});

        string attacker_desc = "Sparks fly as "+QTNAME(player)+" blocks "+
        "your "+attacker_weapon->short()+" with "+HIS(player)+" "+player_shield->short()+".\n";

        valid_attacker_desc = valid_attacker_desc + ({attacker_desc});

        string watcher_desc = "Sparks fly as "+QTNAME(player)+" blocks "+
        QTNAME(attacker)+"'s "+attacker_weapon->short()+" with "+HIS(player)+
        " "+player_shield->short()+".\n";
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc});
    }

    if(player_weapon && attacker_weapon)
    {
        string player_desc = "Anticipating " + QTNAME(attacker)+"'s move, you hit " +
        HIS(attacker) + " "+attacker_weapon->short()+ " forcefully, "+
        "knocking back " + HIS(attacker)+" attack.\n";
        valid_player_desc = valid_player_desc + ({player_desc});

        string attacker_desc = "Anticipating your move, "+QTNAME(player)+" hits "+
        "your "+attacker_weapon->short()+" forcefully, knocking back your attack.\n";
        valid_attacker_desc = valid_attacker_desc + ({attacker_desc});

        string watcher_desc = "Anticipating "+QTNAME(attacker)+"'s move, "+
        QTNAME(player)+" hits "+QTNAME(attacker)+"'s "+attacker_weapon->short() +
        " forcefully, knocking back "+HIS(attacker)+" attack.\n";
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc});
    }

    if(attacker_weapon)
    {
        string player_desc1 = QCTNAME(attacker)+"'s "+attacker_weapon->short() + " launches " +
        "straight at you, but only manages to get entangled in your beard.\n";
        string player_desc2 = "Using your size to your advantage, you drop to your knees " +
        "ducking under "+QTNAME(attacker)+"'s "+attacker_weapon->short() +
        ", which sweeps harmlessly over your head.\n";

        valid_player_desc = valid_player_desc + ({player_desc1});
        valid_player_desc = valid_player_desc + ({player_desc2});

        string attacker_desc1 = "Your "+attacker_weapon->short()+" launches "+
        "straight at "+QTNAME(player)+", but only manages to get " +
        "entangled in "+HIS(player)+" beard.\n";

        string attacker_desc2 = "Using "+HIS(player)+" size to "+HIS(player)+
        " advantage, "+QTNAME(player)+" drops to "+HIS(player)+" knees "+
        "ducking under your "+attacker_weapon->short()+", which sweeps harmlessly over "+
        HIS(player)+" head.\n";

        valid_attacker_desc = valid_attacker_desc + ({attacker_desc1});
        valid_attacker_desc = valid_attacker_desc + ({attacker_desc2});

        string watcher_desc1 = QCTNAME(attacker)+"'s "+attacker_weapon->short()+" launches "+
        "straight at "+QTNAME(player)+", but only manages to get entangled in "+HIS(player)+
        " beard.\n";
        string watcher_desc2 = "Using "+HIS(player)+" size to "+HIS(player)+
        " advantage, "+QTNAME(player)+" drops to "+HIS(player)+" knees "+
        "ducking under "+QTNAME(attacker)+"'s "+attacker_weapon->short()+
        ", which sweeps harmlessly over "+HIS(player)+" head.\n";
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc1});
        valid_watcher_desc = valid_watcher_desc + ({watcher_desc2});
    }

    int index = random(sizeof(valid_player_desc));

    player_descr = valid_player_desc[index];
    attacker_descr = valid_attacker_desc[index];
    watcher_descr = valid_watcher_desc[index];
    player->catch_msg(player_descr + "\n");
    attacker->catch_msg(attacker_descr + "\n");
    player->tell_watcher(watcher_descr, attacker, exclude_list);
}

/*
* Description  : Finds a shield (random if there's 2).
* Arguments    : A player
* Returns      : The first shield we find (doesn't matter which).
*/
public object
find_shield(object player)
{
    object shd1 = player->query_armour(TS_RWEAPON),
    shd2 = player->query_armour(TS_LWEAPON);

    mixed *shields = ({});

    if (shd1 && shd1->query_at(A_SHIELD))
    {
        shields += ({shd1});
    }

    if (shd2 && shd2->query_at(A_SHIELD))
    {
        shields += ({shd2});
    }

    int size_of_shields = sizeof(shields);

    if (size_of_shields)
    {
        return shields[random(size_of_shields)];
    }
    return 0;
}

/*
* Description : Find a weapon (random if there's 2).
* Arguments   : A player.
* Returns     : A wielded weapon, 0 if none is wielded.
*/
public object
find_weapon(object player)
{
    object* wielded_weapons = player->query_weapon(-1);
    int num_of_weapons = sizeof(wielded_weapons);

    if(num_of_weapons > 0)
    {
        return wielded_weapons[random(num_of_weapons)];
    }
    
    return 0;
}
