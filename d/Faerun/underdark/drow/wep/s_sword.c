/*
 *  faerun/underdark/upper/menzo/melee/wep/s_sword.c
 *
 *  This is sword for melee students
 *
 *  Created by Midnight, 16-4-2004
 */

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Faerun/defs.h"

#define HOW ({ "vigorously", "viciously", "dangerously", \
               "fiercely", "wickedly", "deftly",  \
               "brutally", "savagely", "sadistically", \
               "painfully", "violently" })


inherit FAERUN_WEP_BASE;

#define HIT 25
#define PEN 30

void
create_faerun_weapon()
{
    set_name("sword");
    add_name("longsword");
    add_adj("adamantine");
    add_adj("dark");
    set_long("The long dark blade of this simple, yet beautiful, sword " +
              "has been matted to an almost velvet-like finish, unable to " +
              "reflect any light. This way it can find it's way through " +
              "the ribcage of any victim, unseen. The hilt is made of dark " +
              "wood, with black leather wrapping.\n");

 
    set_short("dark adamantine longsword");
    
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
        "The blade has been macigally enchanted with " +
        "magical oils, so the blade will not become so damaged.\n", 70 }));
    add_prop(OBJ_S_WIZINFO, "A student of Melee-magthere wields this sword. " +
        "It does not dull.\n");

    set_default_weapon(HIT + random(5), PEN + random(5), W_KNIFE, W_SLASH | W_IMPALE,
        W_ANYH, this_object());
    
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 2000);



}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
    int dt, int phit, int dam)
{
    object me, *us;
    string desc;

    if(random(8))
    {
        return 0;
    }

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    me = environment(this_object());
    desc = HOW[random(11)];
    

    us = ({ me, enemy });

    switch(phurt)
    {
        case -1:
        case -2:
            enemy->catch_msg(QCTNAME(me) + " nearly hits you " +
                "with a striking blow of the " + query_short() + 
                ", but you manage to sidestep the " +
                "attack in the last second.\n");
            me->catch_msg(QCTNAME(me)  + " nearly hits " + QTNAME(enemy) +
                " with a striking blow of the " + query_short() + ", but " + 
                QTNAME(enemy) + " manages " +
                "to sidestep the attack in the last second.\n");
            me->tell_watcher(QCTNAME(me) + " nearly hits " + QTNAME(enemy) +
                " with a striking blow of the " + query_short() + ", but " + 
                QTNAME(enemy) + " manages " +
                "to sidestep the attack in the last second.\n", enemy, us);
        break;

       
        case 0..1:
            enemy->catch_msg(QCTNAME(me) + " easily deflects your " +
                "attack, and " + desc + " pierces your " + hdesc + 
                " with the long blade of the " + query_short() + ".\n");
            me->catch_msg("You easily deflect the attack of "  +
                QTNAME(enemy) + " and " + desc + " pierces the " + hdesc + 
                " of " + QTNAME(enemy) + " with " +
                "the long blade of the " +  query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " easily deflects the attack of "  +
                QTNAME(enemy) + " and " + desc + " pierces the " + hdesc + 
                " of " + QTNAME(enemy) + " with " +
                "the long blade of the " +  query_short() + ".\n", 
                enemy, us);
        break;

        case 2..3:
            enemy->catch_msg(QCTNAME(me) + " quickly spin around and with " + 
                "the momentum of the spin you deliver a " + desc + " cut to the " +
                hdesc + " with the sharp blade of the " + query_short() +
                ".\n");
            me->catch_msg("You quickly spin around and with " + 
                "the momentum of the spin you deliver a " + desc + " cut to the " +
                hdesc + " of " + QTNAME(enemy) + " with the sharp blade of your " +
                query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " quickly spins around and with " +
                "the momentum of the spin " + QTNAME(me) + " delivers a " + desc +
                " cut to the " + hdesc + " of " + QTNAME(enemy) + ".\n",
                enemy, us);
            
        break;

        case 7..10:
            enemy->catch_msg(QCTNAME(me) + " slashes you " + desc + " and cuts " +
                "a piece of blooded flesh from your " + hdesc + " with the sharp " +
                "blade of the " + query_short() + ".\n " +
                "You scream in pain!\n");
            me->catch_msg("You slash " + QTNAME(enemy) + " " + desc + " and cut " +
                "a piece of blooded flesh from the " + hdesc + " of " + QTNAME(enemy) +
                " with the sharp blade of the " + query_short() + ".\n " +
                QCTNAME(enemy) + " screams in pain!\n");
            me->tell_watcher(QCTNAME(me) + " slashes " + QTNAME(enemy) + " " + desc + 
                "and cuts a piece of blooded flesh from the " + hdesc + " of " + 
                QTNAME(enemy) + " with the sharp blade of the " + 
                query_short() + ".\n " +
                QCTNAME(enemy) + " screams in pain!\n", enemy, us);
        break;

        case 16..20:
            enemy->catch_msg(QCTNAME(me) + " impales you " + desc +
                " with the slim blade of the " + query_short() + "!\n " +
                QCTNAME(me) + " twists the " + query_short() + " " +
                desc + " in the wound, letting " +
                "the blade tear bloody chunks from your gaping wound!\n");
            me->catch_msg("You impale " + QTNAME(enemy) + " " + desc +
                "with the slim blade of the " + query_short() + "!\n " +
                "You twists the " + query_short() + " " +
                desc + " in the wound, letting  " +
                "the blade tear bloody chunks from " +
                enemy->query_possesive() + " gaping wound!\n");
            me->tell_watcher(QCTNAME(me) + " impales " + QTNAME(enemy) +
                 " " + desc + " with the slim blade of the " + query_short() 
                 + "!\n " +
                "You twists the " + query_short() + " " +
                desc + " in the wound, letting " +
                "the blade tear bloody chunks from " +
                enemy->query_possesive() + " gaping wound!\n", enemy, us);
        break;

        default:
            enemy->catch_msg(QCTNAME(me) + " impales you " + desc +
                " with the black blade of the " + query_short() + "!\n " +
                QCTNAME(me) + " twists the " + query_short() + " " +
                desc + " in the wound, letting " +
                "the blade tear bloody chunks from your gaping wound!\n");
            me->catch_msg("You impale " + QTNAME(enemy) + " " + desc +
                "with the black blade of the " + query_short() + "!\n " +
                "You twists the " + query_short() + " " +
                desc + " in the wound, letting  " +
                "the blade tear bloody chunks from " +
                enemy->query_possesive() + " gaping wound!\n");
            me->tell_watcher(QCTNAME(me) + " impales " + QTNAME(enemy) +
                 " " + desc + " with the black blade of the " + query_short() 
                 + "!\n " +
                "You twists the " + query_short() + " " +
                desc + " in the wound, letting " +
                "the blade tear bloody chunks from " +
                enemy->query_possesive() + " gaping wound!\n", enemy, us);
        break;
    }


    return 1;
}