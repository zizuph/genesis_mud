/* /d/Terel/mountains/ghastly_keep/obj/icy_brew.c
 *
 * A potion for throwing.
 *
 *
 * Brew of Soothe Mind
 * Attack delay.
 *
  *  Created by Znagsnuf.
 *
 *
 *  Relase date:
 *
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  27/04-17                   Changing name to icy_potion             Znagsnuf
 *  12/06-17                   Bugfix with add_attack_delay            Znagsnuf
 *  25/12-19                   Bugfix with attacking in safe rooms        Arman
 *  01/06-21                   Added a quick and dirty delay solution    Carnak
 *  07/08-21                   Only add commands to environment       Cotillion
 */
// Added to handle the global PVP disable function.
#include "/d/Genesis/specials/defs.h"

inherit "/cmd/std/command_driver";
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include "defs.h";
#include "../npc_stats.h";

static int throw_alarm;

int do_throw(string target);

#define propel1 ({ "deliver", "fling", "flip",\
                   "heave", "hurl", "send",\
                   "thrust", "toss", "drive"})

#define force1 ({"effort", "strength", "violence", "speed",\
                   "tension", "steam", "momentum"})

void
create_object()
{
    add_name(({"_gkeep_icy_potion"}));
    set_name("brew");
    set_short("icy glass brew");
    set_adj(({"icy", "glass", "brew"}));
    set_long("The liquid in this brew had once run so freely, then as the "
            + "failing light of dusk, but now here trapped in this icy form, "
            + "beautiful under the glare from any source of light, but "
            + "as solid as a frozen block of ice. Your hand recoils "
            + "as soon as you make contact with the brew, not mere "
            + "ice, but unnaturally cold.\n");
    
    add_prop(OBJ_I_VOLUME, 10);   
    add_prop(OBJ_I_WEIGHT, 10);   
    add_prop(OBJ_I_VALUE, 100);

    add_cmd_item(({"brew","potion"}), "open", "The " +TO->short()+ " is sealed "
                  + "closed, making it impossible to open.\n");
    add_cmd_item(({"brew","potion"}), "smell", "You put the " +TO->short()+ " "
                  + "close to your nose, and take a solid sniff. The stench "
                  + "is overwhelming.\n");
    add_cmd_item(({"brew","potion"}), "touch", "You place your "
                  + "hand on the " +TO->short()+ " and recoil as soon as you "
                  + "make contact with the glass.\n");

    add_prop(MAGIC_AM_MAGIC, ({ "enchantment", 20 }));
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "This " +TO->short()+ " is enchanted with cold magic.\n", 10,
        "The Brew of Soothe Mind shatters on contact when thrown "
        + "at a target, making the target freeze into solid ice.\n", 25 }));

    add_prop(OBJ_S_WIZINFO, "A potion that shatters on contact with an "
                           + "enemy, freezing them into ice, for a short "
                           + "period of time.\n");
}             


int 
delay_throw(string target)
{
    object *enemies, enemy;
    
    if (PVP_ABILITY_DISABLED)
    {
        notify_fail("Divine intervention prevents you from performing "
        + "this action.\n");
        return 0;
    }
    
    notify_fail("You are already preparing to throw the icy glass brew.\n");
    if (get_alarm(throw_alarm))
        return 0;
    
    // When in combat 'throw' is enough.
    notify_fail(CAP(query_verb()) + " the " + TO->short() + " at whom?\n");
    if(!target)
    {
        if(objectp(TP->query_attack()))
            enemy = TP->query_attack();
        else 
            return 0;
    }
    else
    { 
        enemies = parse_this(target,
        "[icy] [glass] 'brew' / 'potion' [at] [towards] %l");
        
        if(!sizeof(enemies))
            return 0;
        
        enemy = enemies[0];
    }

    // Prevent attacking. 
    notify_fail("You sense a divine presence protecting the intended "
               + "victim.\n");
    if (enemy->query_prop(OBJ_M_NO_ATTACK))
        return 0;

    notify_fail("You don't dare to throw the " + TO->short() + " at your "
               + "target.\n");
    if(!F_DARE_ATTACK(TP,enemy))
        return 0;

    notify_fail("In this state, you cannot throw the " + TO->short() + ".\n");
    if (TP->query_prop(LIVE_I_ATTACK_DELAY) || 
        TP->query_prop(LIVE_I_STUNNED))
        return 0;

    notify_fail("You sense a divine presence protecting the intended "
               + "victim.\n");
    if (ENV(enemy) && (enemy->query_prop(ROOM_I_NO_ATTACK)))
        return 0;

    notify_fail("You sense you are unable to do hostile actions here.\n");
    if (ENV(enemy)->query_prop(ROOM_I_NO_ATTACK))
        return 0;

    notify_fail("The intended target is already freezing cold, it would have "
               + "no effect.\n");
    if (present("_gkeep_throw_cooldown_ice", enemy))
        return 0;
    
    TP->catch_msg("You prepare to throw the icy glass brew at " + QTNAME(enemy)
    + ".\n");
    enemy->catch_msg(QCTNAME(TP) + " prepares to throw an icy glass brew at "
    + "you.\n");
    say(QCTNAME(TP) + " prepares to throw an icy glass brew at " + QTNAME(enemy)
    + ".\n", ({ TP, enemy }));
    
    throw_alarm = set_alarm(3.0, 0.0, &do_throw(target));
    return 1;
}

/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
void
init() 
{
    ::init();

    /* Only add commands when carried */
    if (this_player() != environment())
        return;

    add_action(delay_throw, "throw");
    add_action(delay_throw, "toss");
    add_action(delay_throw, "lob");
    add_action(delay_throw, "hurdle");
    add_action(delay_throw, "heave");
}

/*
 * Function name: do_throw())
 * Description  : Throws a brew towards a target.
 */
int 
do_throw(string target)
{
    remove_alarm(throw_alarm);
    
    if (PVP_ABILITY_DISABLED)
    {
        notify_fail("Divine intervention prevents you from performing "
        + "this action.\n");
        return 0;
    }
    
    object enemy, potion, *enemies;
    object cooldown, stun;

    int hitresult;

    int stun_duration, target_res, full_stun;

    string how, ohow, hdesc;
    string target_loc, force, propel;
    string l_file;

    force = one_of_list(force1);
    propel = one_of_list(propel1);

    // When in combat 'throw' is enough.
    notify_fail(CAP(query_verb()) + " the " + TO->short() + " at whom?\n");
    if(!target)
    {
        if(objectp(TP->query_attack()))
            enemy = TP->query_attack();
        else 
        return 0;
    }
    else
    { 
        enemies = parse_this(target,
        "[icy] [glass] 'brew' / 'potion' [at] [towards] %l");
        if(!sizeof(enemies))
            return 0;
        enemy = enemies[0];
    }

    // Prevent attacking. 
    notify_fail("You sense a divine presence protecting the intended "
               + "victim.\n");
    if (enemy->query_prop(OBJ_M_NO_ATTACK))
        return 0;

    notify_fail("You don't dare to throw the " + TO->short() + " at your "
               + "target.\n");
    if(!F_DARE_ATTACK(TP,enemy))
        return 0;

    notify_fail("In this state, you cannot throw the " + TO->short() + ".\n");
    if (TP->query_prop(LIVE_I_ATTACK_DELAY) || 
        TP->query_prop(LIVE_I_STUNNED))
        return 0;

    notify_fail("You sense a divine presence protecting the intended "
               + "victim.\n");
    if (ENV(enemy) && (enemy->query_prop(ROOM_I_NO_ATTACK)))
        return 0;

    notify_fail("You sense you are unable to do hostile actions here.\n");
    if (ENV(enemy)->query_prop(ROOM_I_NO_ATTACK))
        return 0;

    notify_fail("The intended target is already freezing cold, it would have "
               + "no effect.\n");
    if (present("_gkeep_throw_cooldown_ice", enemy))
        return 0;

    /* Start combat */
    TP->attack_object(enemy);

    /* Just in case */
    TP->reveal_me(0);

    target_res = (enemy->query_magic_res(MAGIC_I_RES_COLD) / 100);

    stun_duration = random(20);
    stun_duration -= stun_duration * target_res;

    if(stun_duration < 5)
        stun_duration = 5;

    full_stun = (stun_duration / 2);

    enemy->add_attack_delay(stun_duration, 1);

    // Add timestamp, avg, name, and dmg.
    l_file = ctime(time()) + " " + CAP(TP->query_real_name()) +
    " (" + TP->query_average_stat() + ") threw a '" + TO->short() + "' "
      + "at " + CAP(enemy->query_name());
    
    l_file += " (" + CAP(enemy->query_average_stat()) + ") ";
    l_file += "\nAttack delay: " +stun_duration+ "sec. "
            + "\tStun: " +full_stun+ "sec.";
    l_file += "\n";

    // Write a log file.
    write_file(BREW_THROW2, l_file);

    how = " but miss";
    ohow = " but misses";

    if (stun_duration >= 0)

    {
        how = " it smashes on impact";
        ohow = " it smashes on impact";
    }

    if (stun_duration > 10)
    {
        how = " it explodes on impact";
        ohow = " it explodes on impact";
    }

    if (stun_duration > 20)
    {
        how = " it shatters on impact";
        ohow = " it shatters on impact";
    }

    if (stun_duration == -1)
    {
        TP->catch_msg("You " +propel+ " an " + TO->short() + " towards " 
            + QTNAME(enemy) + " with " +force+ "," +how+ ".\n");

        enemy->catch_msg(QCTNAME(TP) + " " +propel+ "s an " + TO->short()+ " "
            + "towards you," +ohow+ ".\n");

        say(QCTNAME(TP) + " " +propel+ "s an " + TO->short()+ " at " 
            + QTNAME(enemy)+ " with " +force+ "," +ohow+ ".\n", enemy);

        remove_object(); 
        return 1;
    }

    if (stun_duration >= 0)
    {
        TP->catch_msg("You " +propel+ " an " + TO->short()+ " towards "
            + QTNAME(enemy) + " with " +force+ "," + how + ".\n");

        enemy->catch_msg(QCTNAME(TP)
            + " " +propel+ "s an " + TO->short()+ " at you with " +force+ "," +
            ohow + ".\n");

        say(QCTNAME(TP) + " " +propel+ "s an " + TO->short() + " at "
         + QTNAME(enemy) + " with " +force+ "," + ohow + ".\n", ({enemy,TP}));
       

        setuid();
        seteuid(getuid());

        // Moving the cooldown object to the target.
        cooldown = clone_object(GTHROW_CDWN2);
        cooldown-> set_duration(GBREW);
        cooldown-> set_target(enemy);

        if (cooldown->move(enemy))
            cooldown->move(enemy, 1);

        setuid();
        seteuid(getuid());

        // Moving the stun object to the target.
        stun = clone_object(GTHROW_STUN);
        stun-> set_remove_time(full_stun);
        stun-> set_target(enemy);

        if (stun->move(enemy))
            stun->move(enemy, 1);

        // The potion shatters on impact.
        remove_object(); 
        return 1;
    }
    // The potion shatters on impact.
    remove_object();     
    //TO->remove_object();   
    return 1;
}
