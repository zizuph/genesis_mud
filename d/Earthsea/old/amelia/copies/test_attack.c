
/* 
    This is an outline for a damage special attack. 

    Coded by Maniac. 
 */

#pragma save_binary

inherit "/cmd/std/command_driver"; 
inherit "/d/Calia/open/attack_desc"; 

#include <wa_types.h> 
#include <stdproperties.h> 
#include <macros.h> 
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h> 

#define KB_I_ATTACK_STAGE 1 
#define KB_PRE_PREPARE 0
#define KB_PREPARE 1 
#define KB_READY 2
#define KB_POST_HIT 3

#define KB_PREP_TIME 2
#define KB_EXEC_TIME 8

string
get_soul_id()
{
    return "Knight test attack";
}

int
query_cmd_soul()
{
    return 1;
}


mapping
query_cmdlist()
{
    return ([ "kb" : "kb" ]); 
}


/* 
 * query_main_weapon returns the main weapon or the weapon 
 * which is specified by the player in the string p.
 */ 
object
query_main_weapon(object living, string p)
{
    object weapon_left, weapon_right, weapon_both;
    int wl_pen, wr_pen;

    weapon_left = living->query_weapon(W_LEFT);
    weapon_right = living->query_weapon(W_RIGHT);
    weapon_both = living->query_weapon(W_BOTH);

    if (objectp(weapon_both))
        return weapon_both;

    if ((p == "right") && (objectp(weapon_right)))
        return weapon_right;

    if ((p == "left") && (objectp(weapon_left)))
        return weapon_left;

    if (objectp(weapon_right))
        return weapon_right;

    return weapon_left;
}


/* Return kb state of the player */
int
kb_state(object tp)
{
    return (tp->query_prop(KB_I_ATTACK_STAGE));
}


/* Change swarm state, updates the swarm state for a player */
void
change_kb_state(object tp, int state)
{
    tp->add_prop(KB_I_ATTACK_STAGE, state);
}

void
ready_to_kb_now(object tp)
{
    change_kb_state(tp, KB_PRE_PREPARE);
    tp->catch_msg("You feel ready to kb again.\n");
}


/* Carry out swarm after preparation */
void
kb_enemy(object me, object enemy, string str)
{
    if (!objectp(me))
        return;

    if (!objectp(enemy)) {
        me->catch_msg("You can no longer see the enemy you were " +
                      "preparing to kb.\n");
        change_kb_state(me, KB_PRE_PREPARE);
        return;
    }

    if (!present(enemy, environment(me))) {
        me->catch_msg("You can no longer see the enemy you were " +
                          "preparing to kb.\n");
        change_kb_state(me, KB_PRE_PREPARE);
        return;
    }

    change_kb_state(me, KB_READY);
    me->command("kb " + str);
}



int
filter_attack_team(object player, object enemy)
{
    return (player->query_attack() == enemy); 
}


/*
 * Function name: kb
 * Description:   executes the kb command
 * Arguments:     str - predicate ("left" / "right" (hand)) 
 * Returns:       success
 */
int
kb(string str)
{
    object tp, *enemies, enemy, weapon;
    string enemy_name, *message, enemy_race, weapon_desc,  
           *hit_descr; 
    int x, *ids, dt, *poss_hit_types, p, d, ss, sfor,  
       sagainst, ht;
    mixed hit, *loc, nam;

    tp = this_player(); 

    ss = kb_state(tp); 

    /* wizards and npcs don't get a preparation time, saves cpu */
    if ((tp->query_wiz_level() || tp->query_npc()) && (ss == KB_PRE_PREPARE))
        ss = KB_READY;

    if (!strlen(str)) 
        str = "any"; 

    if ((str != "left") && (str != "right") && (str != "any")) {  
        notify_fail("Kb with what hand? [left/right]\n");
        return 0;
    }

    if (!(enemy = tp->query_attack()))
    {
        write("You are not fighting anyone.\n");
        if (ss == KB_READY)
            change_kb_state(tp, KB_PRE_PREPARE);
        return 1;
    }

    weapon = query_main_weapon(tp, str);
    weapon_desc = weapon->short();
    dt = weapon->query_dt();

    if (tp->query_prop(LIVE_I_ATTACK_DELAY)) { 
        notify_fail("You are currently stunned so you can't kb!\n"); 
        return 0;
    } 
    else if ((nam = enemy->query_prop(OBJ_M_NO_ATTACK)) ||
        (nam = environment(enemy)->query_prop(ROOM_M_NO_ATTACK)) )  
        if (stringp(nam)) {
            notify_fail(nam);
            return 0;
        }
        else {
            notify_fail("A magical force prevents you from using kb " +
                        "on that opponent.\n");
            return 0;
        }
    else if (!objectp(weapon)) {
        notify_fail("You cannot kb your enemy without a weapon!\n");
        return 0;
    }
    else if (ss == KB_PREPARE) {
        notify_fail("You are currently preparing to kb.\n");
        return 0;
    }
    else if (ss == KB_POST_HIT) {
        notify_fail("You have only just used kb.\n");
        return 0;
    }
    else if (ss == KB_PRE_PREPARE) {
        change_kb_state(tp, KB_PREPARE);
        tp->catch_msg("You prepare to kb " + QTNAME(enemy)+".\n");
        set_alarm(itof(KB_PREP_TIME), 0.0, 
                    &kb_enemy(tp, enemy, str));
    }
    else if (ss == KB_READY)
    {
        change_kb_state(tp, KB_POST_HIT);
        if ((tp->query_wiz_level()) || (tp->query_npc()))
            set_alarm(itof(KB_EXEC_TIME+KB_PREP_TIME), 0.0, 
                                  &ready_to_kb_now(tp));
        else 
            set_alarm(itof(KB_EXEC_TIME), 0.0, 
                                  &ready_to_kb_now(tp));


        /* work out the possible hit types of the weapon */ 
        poss_hit_types = ({ });
        if (dt & W_SLASH)
           poss_hit_types += ({ W_SLASH });
        if (dt & W_IMPALE)
           poss_hit_types += ({ W_IMPALE });
        if (dt & W_BLUDGEON)
           poss_hit_types += ({ W_BLUDGEON });
        if (!sizeof(poss_hit_types)) 
           poss_hit_types = ({ W_BLUDGEON });

        ht = poss_hit_types[random(sizeof(poss_hit_types))]; 

        /* weapon pen */ 
        p = weapon->query_pen(); 

        /* multiplier for weapon pen */ 
        d = 100; 

        /* chance for hitting */ 
        sfor = tp->query_stat(SS_DEX); 

        /* chance against hitting */ 
        sagainst = enemy->query_stat(SS_DEX) / 2; 

        if (random(sfor) > random(sagainst))  
            hit = enemy->hit_me(F_PENMOD(p, 100), 
                                weapon->query_dt(), tp, -1);
        else { 
            hit = enemy->hit_me(0, weapon->query_dt(), tp, -1);
            hit[0] = -1;  /* miss */ 
        } 

        hit_descr = attack_desc_template_one(tp, enemy, ht,  
                                 hit[0], hit[1], weapon_desc);   
        tp->catch_msg(hit_descr[0]); 
        enemy->catch_msg(hit_descr[1]); 
        enemy->tell_watcher(hit_descr[2], tp); 
        if (enemy->query_hp() < 1)
            enemy->do_die(tp);
    }

    if (kb_state(tp) == KB_READY)
        change_kb_state(tp, KB_PRE_PREPARE);

    return 1;
}

