/*
 *  faerun/underdark/upper/menzo/sorcere/wep/roncone.c
 *
 *  This is roncone for wizard masters
 *
 *  Created by Midnight, 25-2-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;


/*#define WHERE ({"left cheek", "right cheek", "left shoulder",  \
                "right shoulder", "face", "left leg", "right leg", \
                "back", "chin", "head", "chest", \
                "left arm", "right arm" })*/
#define HOW ({ "vigorously", "viciously", "dangerously", \
               "fiercely", "wickedly", "deftly",  \
               "brutally", "savagely", "sadistically", \
               "painfully", "violently" })

#define HIT 40
#define PEN 45
void 
create_faerun_weapon()
{
    set_name("roncone");
    add_name("polearm");
    add_adj("ancient");
    add_adj("slim-bladed");
    set_short("ancient slim-bladed roncone");
    set_long("This is a long sleek roncone. The shaft is made of duskwood, " +
        "which has been polished and oiled to a silvery finish. It feels " +
        "as hard as iron and the shaft is slightly twirled along its length " +
        "to secure a solid grip for the wielder. At the end of the shaft " +
        "is a sharp point which gracefully curves into a slim blade. " +
        "The slim blade has a few sharp pointy teeths, which point out " +
        "from the blade about a finger's length. A solid metal hook has " +
        "been placed at the back of the blade for extra advantage in battle.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
        "The blade has been macigally enchanted with " +
        "magical oils, so the blade will not become so damaged.\n", 70 }));
    add_prop(OBJ_S_WIZINFO, "A master of the Sorcere wields this roncone. " +
        "It does not dull.\n");

    set_default_weapon(HIT, PEN, W_POLEARM, W_BLUDGEON | W_SLASH | W_IMPALE,
        W_BOTH, this_object());
    
    add_prop(OBJ_I_WEIGHT, 4600);

}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
    int dt, int phit, int dam)
{
    object me, *us;
    string loc, desc;

    if(random(8))
    {
        return 0;
    }

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    me = environment(this_object());
    desc = HOW[random(11)];
    /*loc = WHERE[random(13)]; */

    if(random(20) > 15)
    {
        tell_room(environment(me), "The blade of the ancient roncone " +
          "pulses fiercely with a bright blue glow.\n", ({}));
    }

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
                "attack with the " + query_short() + " and " + desc +
                " hit your " + hdesc + " with the slender shaft of the " + 
                query_short() + ".\n");
            me->catch_msg("You easily deflect the attack of "  +
                QTNAME(enemy) + " with the " + query_short() + " and " + 
                desc + " hit the " + hdesc + " of " + QTNAME(enemy) + " with " +
                "the slender shaft of the " +  query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " easily deflects the attack of "  +
                QTNAME(enemy) + " with the " + query_short() + " and " + 
                desc + " hit the " + hdesc + " of " + QTNAME(enemy) + " with " +
                "the slender shaft of the " +  query_short() + ".\n", 
                enemy, us);
        break;

        case 2..3:
            enemy->catch_msg(QCTNAME(me) + " " + desc + " hook-cuts your " +
                hdesc + " with the sharp hook of the " + query_short() +
                ".\n");
            me->catch_msg("You " + desc + " hook-cuts " + QTNAME(enemy) +
                "'s " + hdesc + " with the sharp hook of your " +
                query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " " + desc +
                " hook-cuts the " + hdesc + " of " + QTNAME(enemy) + ".\n",
                enemy, us);
            
        break;

        case 7..10:
            enemy->catch_msg(QCTNAME(me) + " hits you " + desc + " and tears " +
                "a piece of blooded flesh from your " + hdesc + " with the sharp " +
                "hook of the " + query_short() + ".\n " +
                "You scream in pain!\n");
            me->catch_msg("You hit " + QTNAME(enemy) + " " + desc + " and tear " +
                "a piece of blooded flesh from the " + hdesc + " of " + QTNAME(enemy) +
                " with the sharp hook of the " + query_short() + ".\n " +
                QCTNAME(enemy) + " screams in pain!\n");
            me->tell_watcher(QCTNAME(me) + "hits " + QTNAME(enemy) + " " + desc + 
                "and tears a piece of blooded flesh from the " + hdesc + " of " + 
                QTNAME(enemy) + " with the sharp hook of the " + 
                query_short() + ".\n " +
                QCTNAME(enemy) + " screams in pain!\n", enemy, us);
        break;

        case 16..20:
            enemy->catch_msg(QCTNAME(me) + " impales you " + desc +
                " with the slim blade of the " + query_short() + "!\n " +
                QCTNAME(me) + " twists the " + query_short() + " " +
                desc + " in the wound, letting the jagged teeth of " +
                "the blade tear bloody chunks from your gaping wound!\n");
            me->catch_msg("You impale " + QTNAME(enemy) + " " + desc +
                "with the slim blade of the " + query_short() + "!\n " +
                "You twists the " + query_short() + " " +
                desc + " in the wound, letting the jagged teeth of " +
                "the blade tear bloody chunks from " +
                enemy->query_possesive() + " gaping wound!\n");
            me->tell_watcher(QCTNAME(me) + " impales " + QTNAME(enemy) +
                 " " + desc + " with the slim blade of the " + query_short() 
                 + "!\n " +
                "You twists the " + query_short() + " " +
                desc + " in the wound, letting the jagged teeth of " +
                "the blade tear bloody chunks from " +
                enemy->query_possesive() + " gaping wound!\n", enemy, us);
        break;

        default:
            enemy->catch_msg(QCTNAME(me) + " quickly steps forward and " +
                "pierces you " + desc + " with the sharp tip of the " + 
                  query_short() + ".\n");
            me->catch_msg("You quickly step forward and " +
                "pierce " + QTNAME(enemy) + " " + desc + " with the " + 
                "sharp tip of the " + query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " quickly steps forward and " +
                "pierces "  + QTNAME(enemy) + " " + desc + " with the " + 
                "sharp tip of the " +query_short() + ".\n", enemy, us);
        break;
    }


    return 1;
}