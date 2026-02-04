/* /d/Terel/mountains/ghastly_keep/obj/hatred_brew.c
 *
 * A potion for throwing.
 *
 * Brew of Hatred.
 * Does damage on inpact.
 *
 *  Relase date:
 *
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  27/04-17                   Changing name to brew_of_hatred         Znagsnuf
 *  25/12-19                   Bugfix with attacking in safe rooms        Arman
 *
 */


inherit "/cmd/std/command_driver";
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include "defs.h";
#include "../npc_stats.h";

int do_throw(string target);

#define propel1 ({ "deliver", "fling", "flip",\
                   "heave", "hurl", "send",\
                   "thrust", "toss", "drive"})

#define force1 ({"effort", "strength", "violence", "speed",\
                   "tension", "steam", "momentum"})

void
create_object()
{
    add_name(({"_brew_of_hatred"}));
    set_name("brew");
    set_short("red witch brew");
    set_adj(({"red", "witch", "brew"}));
    set_long("This strange red witch brew is kept in a sealed "
            + "container, but still the stench is overwhelming.\n");
    
    add_prop(OBJ_I_VOLUME, 10);   
    add_prop(OBJ_I_WEIGHT, 10);   
    add_prop(OBJ_I_VALUE, 100);

    add_cmd_item(({"brew","potion"}), "open", "The " +TO->short()+ " sealed "
                  + "closed, making it impossible to open.\n");
    add_cmd_item(({"brew","potion"}), "smell", "You put the " +TO->short()+ " "
                  + "close to your nose, and take a solid sniff. The stench "
                  + "is overwhelming.\n");

    add_prop(MAGIC_AM_MAGIC, ({ "enchantment", 20 }));
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "This " +TO->short()+ " is enchanted with fire magic.\n", 10,
        "The Brew of Hatred explodes on contact when thrown "
        + "at a target.\n", 25 }));

    add_prop(OBJ_S_WIZINFO, "A potion made for throwing, this deadly brew "
                           + "explodes on contact.\n");
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

    add_action(do_throw, "throw");
    add_action(do_throw, "toss");
    add_action(do_throw, "lob");
    add_action(do_throw, "hurdle");
    add_action(do_throw, "heave");
}

/*
 * Function name: do_throw())
 * Description  : Throws a brew towards a target.
 */
int 
do_throw(string target)
{
    object enemy, potion, leftover, *enemies;
    object cooldown;

    mixed *hitresult;

    int hurt;

    string how, ohow, hdesc;
    string target_loc, force, propel;
    string l_file;

    force = one_of_list(force1);
    propel = one_of_list(propel1);

    // When in combat 'throw' is enough.
    notify_fail(CAP(query_verb()) + " the " +TO->short()+ " at whom?\n");
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
            "[red] [witch] 'brew' / 'potion' [at] %l");
        if(!sizeof(enemies))
            return 0;
        enemy = enemies[0];
    }

    // Prevent attacking. 
    notify_fail("You sense a divine presence protecting the intended "
                + "victim.\n");
    if (enemy->query_prop(OBJ_M_NO_ATTACK))
        return 0;

    notify_fail("You don't dare to throw the " + TO->short()+ " at your "
               + "target.\n");
    if(!F_DARE_ATTACK(TP,enemy))
        return 0;

    notify_fail("In this state, you cannot throw the " + TO->short()+ ".\n");
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

    notify_fail("Your intended target is already drenched with oozing liquid "
               + "this won't have any effect.\n");
    if (present("_gkeep_throw_cooldown", enemy))
        return 0;

    /* Start combat */
    TP->attack_object(enemy);

    /* Just in case */
    TP->reveal_me(0);

    // How much dmg.
    hurt = min(700, enemy->query_max_hp() * 70 / 100);
    hurt -= hurt * enemy->query_magic_res(MAGIC_I_RES_FIRE) / 100;

    // The special.
    hitresult = enemy->hit_me(hurt, MAGIC_DT, TP, -1);

    setuid();
    seteuid(getuid());

    cooldown = clone_object(GTHROW_CDWN);
    cooldown->set_duration(GBREW);
    cooldown->set_target(enemy);

    if (cooldown->move(enemy))
        cooldown->move(enemy, 1);

    setuid();
    seteuid(getuid());

    // Add timestamp, avg, name, and dmg.
    l_file = ctime(time()) + " " + CAP(TP->query_real_name())+
    " (" + TP->query_average_stat()+ ") threw a '" + TO->short()+ "' "
      + "at " + CAP(enemy->query_name());
    
    l_file += " (" + CAP(enemy->query_average_stat())+ ") ";
    l_file += "\nHitresult:" +hitresult[0]+ " Damage:" +hurt+ " ";
    l_file += "\n";

    // Write a log file.
    write_file(BREW_THROW, l_file);

    //string hitloc desc - descr. of the location that was hit.
    hdesc = hitresult[1];

    how = " but miss";
    ohow = " but misses";

    if (hitresult[0] >= 0)

    {
        how = " it fiercely explodes across ";
        ohow = " it fiercely explodes across ";
    }

    if (hitresult[0] > 10)
    {
        how = " it brutally explodes across ";
        ohow = " it brutally explodes across ";
    }

    if (hitresult[0] > 20)
    {
        how = " it violently explodes across ";
        ohow = " it violently explodes across ";
    }

    if (hitresult[0] == -1)
    {
        TP->catch_msg("You " +propel+ " a " + TO->short() + " towards " 
            + QTNAME(enemy) + " with " +force+ "," +how+ ".\n");

        enemy->catch_msg(QCTNAME(TP) + " " +propel+ "s a " + TO->short() + " "
            + "towards you," +ohow+ ".\n");

        say(QCTNAME(TP) + " " +propel+ "s a " + TO->short() + " at " 
          + QTNAME(enemy) + " with " +force+ "," +ohow+ ".\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        TP->catch_msg("You " +propel+ " a " + TO->short() + " towards " 
            + QTNAME(enemy) + " with " +force+ "," +
            how + enemy->query_possessive() + " " + hdesc + ".\n");

        enemy->catch_msg(QCTNAME(TP)
            + " " +propel+ "s a " + TO->short() + " at you with " +force+ "," +
            ohow + "your " + hdesc + ".\n");

        say(QCTNAME(TP) + " " +propel+ "s a " + TO->short() + " at "
          + QTNAME(enemy) + " with " +force+ "," + ohow 
          + enemy->query_possessive() + " " + hdesc + "."
          + "\n", ({enemy,TP}));
       
        if(enemy->query_hp() <= 0)
        {
            if (!enemy->query_prop(LIVE_I_NO_CORPSE) &&
                !enemy->query_prop(LIVE_I_NO_BODY))
            {
                setuid(); 
                seteuid(getuid(TO));

                tell_room(ENV(TP),"The impact from the " + TO->short() + " "
                    + "completely obliterates " + QTNAME(enemy) + "!\n");

                enemy->add_prop(LIVE_I_NO_CORPSE, 1);
                enemy->do_die(TP);

                // The potion shatters on impact.
                remove_object();  
                return 1;
            }

            if(enemy->query_hp() <= 0)
                enemy->do_die(TP);
            
        }
            // The potion shatters on impact.
            remove_object(); 
            return 1;
    }
    // The potion shatters on impact.
    remove_object();       
    return 1;
}
