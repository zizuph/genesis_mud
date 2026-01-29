/*
 * File name: city_guard.c
 * Palanthas city guard base file.
 * 
 * 9.11.2003
 * Blizzard
 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <options.h>
#include "/d/Krynn/solamn/palan/local.h"

inherit  M_FILE
inherit  "/d/Krynn/std/equip";
inherit  "/d/Krynn/open/auto_teaming";

/* Unfefine this if we do not want city guards to attack Dragonarmy members */
#define  ATTACK_DRAGONARMY            1
#undef   ATTACK_DRAGONARMY
#define  PALANTHAS_WARNED    "_i_have_been_warned_in_palanthas"
#define  PALANTHAS_ATTACKED  "_i_have_attacked_palanthas"

#define  KRWEP               "/d/Krynn/common/weapons/"

string   *adjective1 = ({ "muscular", "proud", "alert", "solemn",
                          "stern", "young", "stoic", "moustachioed" });
string   *adjective2 = ({ "blond-haired", "brown-haired", "dark-haired",
                          "blue-eyed", "green-eyed", "black-haired",
                          "dark-eyed" });

int calm_alarm;                          
string   adj1, adj2;
int      already_fighting, time_follow;
object   guard;


public void
check_visitor(object who)
{
    object *weapons;

    /* Let the leader do the talking */
    if (!objectp(who) || query_leader() || query_attack())
        return;

    if (who->query_npc())
        return;
    
    weapons = who->query_weapon(-1);
    
    if (environment(who) != environment())
        return;
 
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, who))
        return;

    if (!sizeof(weapons) )
        return;
           
    if (!who->query_prop(PALANTHAS_WARNED) )
    {
        command("say to " + OB_NAME(who) + 
            " You are not supposed to wield any weapons " +
            "inside Palanthas! Unwield them at once, I warn you!");
        who->add_prop(PALANTHAS_WARNED, time());
        
        set_alarm(30.0 * rnd(), 0.0, &check_visitor(who));
        return 0;
    }
    
    if (time() > (who->query_prop(PALANTHAS_WARNED) + 30) )
    {
        action_attack(who);
        set_follow(who);
        time_follow = time();
        return;
    }
    
    if (time() > (who->query_prop(PALANTHAS_WARNED) + 15))
    {
        command("shout You are testing my patience! Unwield your " +
            "weapons!");
        set_alarm(16.0, 0.0, &check_visitor(who));
        return;
    }
    
    set_alarm(15.0, 0.0, &check_visitor(who));
}

public int
check_aggressive()
{
    if ( !CAN_SEE(TO, TP) && !CAN_SEE_IN_ROOM(TP) )
        return 0;

#ifdef ATTACK_DRAGONARMY
    if ( TP->query_dragonarmy_occ_member() ||
        TP->query_guild_member("Priests of Takhisis") )
        return 1;
    else
#endif
        if ( TP->query_prop(PALANTHAS_ATTACKED) )
            return 1;
    
    return 0;
}

public void
create_palanthas_guard()
{

}

public string
long_description()
{
    return "This is one of the city guards of Palanthas. He seems to be " +
        "taking his job seriously and being on constant alert for " +
        "dragonarmy soldiers, he is very suspicious of outsiders.\n";
}

public void
create_krynn_monster()
{
    int stat_num;
    
    set_name("guard");
    add_name("_palanthas_guard_");
    set_race_name("human");
    set_gender(0);
    
    set_adj( ({ ONE_OF(adjective1), ONE_OF(adjective2) }) );

    set_long(long_description());
    
    for (stat_num = 0; stat_num < 6; stat_num++)
        set_base_stat(stat_num, 130 + random(40));

    set_skill(SS_2H_COMBAT,    60 + random(20));
    set_skill(SS_DEFENCE,      70 + random(20));
    set_skill(SS_PARRY,        70 + random(20));
    set_skill(SS_WEP_SWORD,    81 + random(20));
    set_skill(SS_WEP_POLEARM,  81 + random(20));
    set_skill(SS_WEP_MISSILE,  81 + random(20));
    set_skill(SS_AWARENESS,    50 + random(20));
    set_skill(SS_BLIND_COMBAT, 40 + random(30));
 
    set_act_time(15);
    add_act("emote stops and looks around the area.");
    add_act("emote eyes you up and down suspiciously, but says nothing.");
    
    set_cact_time(5);
    add_cact("say Surrender!");
    add_cact("emote parries your blow and rushes with a counterattack.");
    add_cact("emote looks around nervously.");
    add_cact("shout To Arms! Palanthas is under attack!");
    add_cact("say You have no chance to leave the city in one piece!");
    
    add_prop(CONT_I_HEIGHT, 170 + random(30));
    add_prop(CONT_I_WEIGHT, 45000 + random(10000));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);

    set_alignment(500);

    /* Guards will patrol the city */
    set_random_move(5);
    set_restrain_path(ROOM);

    set_pick_up_team("_palanthas_guard_");
    set_max_team_size_auto_join(3);
    
    switch ( random(4) )
    {
    case 0:
        equip(({ OBJ + "uniform.c", KRWEP + "steel_longsword", 
                 OBJ + "sol_boots" }));
    break;
    case 1:
        equip(({ OBJ + "uniform.c", KRWEP + "steel_broadsword",
                 OBJ + "sol_boots" }));
    break;
    case 2:
        equip(({ OBJ + "uniform.c", KRWEP + "steel_halberd",
                 OBJ + "sol_boots" }));
    break;
    case 3:
        equip(({ OBJ + "uniform.c", KRWEP + "steel_mace",
                 OBJ + "sol_boots" }));
    break;
    }
        
    create_palanthas_guard();
    
}

public int
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
        return 1;
}


public void
calm_me()
{
    if (!query_attack)
        already_fighting = 0;
    else
        calm_alarm = set_alarm(10.0, 0.0, &calm_me());
}

public void
hook_attacked(object enemy)
{
    if ( !enemy->query_prop(PALANTHAS_ATTACKED) )
        enemy->add_prop(PALANTHAS_ATTACKED, 1);
    
    if ( already_fighting == 1 )
        return;
    
    switch ( random(3) )
    {
    case 0:
        command("say That was a mistake! You are going to pay for it!");
    break;
    case 1:
        command("shout To arms! The city is under attack!");
    break;
    case 2:
        command("emote draws his weapon and enters the battle.");
    break;
    default:
        command("emote Attacking the city guard? Ha!");
    break;
    }
    
    already_fighting = 1;
    calm_alarm = set_alarm(8.0, 0.0, calm_me);
    
}

public void
hook_attack(object enemy)
{
    if ( already_fighting == 1 )
        return;
    
    switch ( random(3) )
    {
    case 0:
        command("say Hey! That's the criminal we were looking for!");
        break;
    case 1:
        command("say Now you are going to pay for your crimes!");
        break;
    case 2:
        command("emote quickly enters the battle.");
        break;
    default:
        command("say You are not welcome to Palanthas!");
        break;    
    }
    
    already_fighting = 1;
    calm_alarm = set_alarm(8.0, 0.0, calm_me);
}

/* Function name:   special_attack
 * Description  :   The city guard's special attack.
 * Arguments    :   enemy    - the one we are fighting now
 * Returns      :   0        - if we want the round to continue
 *                  1        - if we are done with this round
 */
public int
special_attack(object enemy)
{
    object weapon, *wps, me = TO;
    int    dt, pen;
    mixed  hitresult;
    string *hit_locs, place, how;
    
    wps = query_weapon(-1);
    
    if ( random(5) )
        return 0;
        
    if ( !sizeof(wps) )
        return 0;    

    weapon = wps[0];
        
    if ( !enemy )
        return 0;
    
    if ( !objectp(weapon) )
        return 0;
        
    dt = weapon->query_dt();
                
    hitresult = enemy->hit_me(400, dt, me, -1);
    
    switch ( hitresult[0] )
    {
    case 0:
        how = "barely missing";
    break;
    case 1..4:
        how = "barely hurting";
    break;
    case 5..10:
        how = "opening a small wound on";
    break;
    case 11..16:
        how = "opening a mediocre wound on";
    break;
    case 17..27:
        how = "opening a gash on";
    break;
    case 30..50:
        how = "leaving a ugly wound on";
    break;
    default:
        how = "tearing a vicious wound on";
    break;
    }

    hit_locs = ({ "left leg", "right leg", "left arm", "right arm",
        "head", "body" });

    place = ONE_OF(hit_locs);
    
    enemy->catch_msg(QCTNAME(TO) + " parries your blow and then moves " +
        "with a quick counterattack, " + how + " your " + place +
        " with his " + weapon->query_short() + ".\n");
    tell_watcher(QCTNAME(TO) + " parries " + QTNAME(enemy) + 
        "'s attack and then moves with a quick counterattack, " +
        how + " " + HIS(enemy) + " " + place + " with the " +
        weapon->query_short() + ".\n", enemy);

    return 1;
}

public void
init_living()
{
    ::init_living();
    init_team_pickup();
    set_alarm(2.0, 0.0, &check_visitor(this_player()));
}

mixed
oke_to_move(string exit)
{
    if (query_leader())
        return 0;

    if (query_follow()) 
    {
        /* We stop hunting after 10 min or so */
        if (time() - time_follow > 600)
            stop_follow();
        else
            return 0;
    }
    return ::oke_to_move(exit);
}
