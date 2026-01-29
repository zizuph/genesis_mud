/* This module allows objects to be throwable. Mucalytic 21-11-95
 *                             Modification by Mucalytic 09-01-96
 *                      Second Modification by Mucalytic 16-01-95 */

/* -------------------------------------------------------------------------- *
 * IDEAS:                                                                     *
 * -------------------------------------------------------------------------- *
 * Should be able to find the hitlocs of the target and say that objects hits *
 * the target there.                                                          *
 * -------------------------------------------------------------------------- *
 * USE OF THIS MODULE:                                                        *
 * -------------------------------------------------------------------------- *
 * You should #include this module and in your init() function, do:           *
 *                                                                            *
 *     init_throwing();                                                       *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/cmdparse.h"
#include "/sys/language.h"
#include "../master_defs.h"
#include "/sys/stdproperties.h"

#define HARDNESS ({ "very softly", "quite softly", "softly", "", \
                    "quite hard", "hard", "very hard", "very hard indeed", \
                    "incredibly hard", "unbelievably hard" })

void init_throwing()
{
    add_action("throw_object", "throw");
}

int throw_object(string str)
{
    string what, who;
    object enemy, *obj_array;
    int obweight, capacity, ad, as, td, hs, pca, pct, pcw, pcs, dam;

    if(!strlen(str))
    {
        notify_fail("Throw what?\n");
        return 0;
    }

    if(sscanf(str, "%s at %s", what, who) == 2)
    {
        if(member_array(TO, FIND_STR_IN_OBJECT(what, TP)) == -1)
            return 0;

        if(E(TO) != TP)
        {
            notify_fail("You have to pick the "+what+" up before you can "+
                "throw it.\n");
            return 0;
        }

        obj_array = FIND_STR_IN_OBJECT(who, E(TP));

        if(!sizeof(obj_array))
        {
            notify_fail(C(who)+" is not present for you to throw the "+
                what+" at.\n");
            return 0;
        }

        if(sizeof(obj_array) > 1)
        {
            write("Please be more precise. There are "+
                LANG_WNUM(sizeof(obj_array))+" objects that fit that "+
                "description.\n");
            return 1;
        }

        enemy = obj_array[0];

        if(enemy == TP)
        {
            notify_fail("You cannot throw the "+what+" at yourself!\n");
            return 0;
        }

        if(!enemy->query_prop(LIVE_I_IS) && !enemy->query_npc())
        {
            notify_fail("You should save your weapons instead of "+
                "wasting them by throwing them at a worthless "+
                enemy->query_name()+".\n");
            return 0;
        }

        if(enemy->query_prop(OBJ_M_NO_ATTACK) ||
         E(enemy)->query_prop(ROOM_M_NO_ATTACK))
        {
            notify_fail("A divine force stops you from attacking "+
                QTNAME(enemy)+".\n"); // Use the property's string.
            return 0;
        }

     /* ad  = The attacker's current DEX score.
      * as  = The attacker's current STR score.
      * td  = The target's current DEX score.
      *
      * hs  = Hit strength of attacker (1 - 10)
      *
      * pca = The percentage chance of the attacker hitting the target.
      * pct = The percentage chance of the target dodging the thrown object.
      *
      * pcw = The percentage chance due to handicap by weight of the 
      *       attacker's ability to throw the object.
      * pcs = The general percentage chance due to the strength of the 
      *       attacker.
      *
      * dam = The damage (in HP) inflicted upon the target.
      */

        as = (TP->query_stat(SS_STR) > 100 ? 100 : TP->query_stat(SS_STR));

        obweight = query_prop(CONT_I_WEIGHT);
        capacity = TP->query_prop(CONT_I_MAX_WEIGHT);

        pcw = 100 - (100 * obweight) / capacity;
        pcs = random(50) + ((10 * as) - 100) / 18;

        if(pcs > pcw)
        {
            write("You try to throw the "+query_name()+" but it is far too "+
                "heavy for you and lands on the "+
                (E(TP)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground")+" "+
                "with a thud.\n");
            tell_room(E(TP), QCTNAME(TP)+" tries to throw "+
                LANG_ADDART(query_name())+" but it is far too heavy for "+
                OBJECTIVE(TP)+" and lands on the "+
                (E(TP)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground")+" "+
                "with a thud.\n", TP);

            TP->add_fatigue(-(5 + random(6)));
            TO->move(E(TP));
            return 1;
        }

        ad = (TP->query_stat(SS_DEX) > 100 ? 100 : TP->query_stat(SS_DEX));
        td = (enemy->query_stat(SS_DEX) > 100 ? 100 : enemy->query_stat(SS_DEX));

        pca = ((ad - 10) / 9) + random((((ad - td + 90) * 100) / 225) + 10);
        pct = ((td - 10) / 9) + random((((td - ad + 90) * 100) / 225) + 10);

        if(pca < pct)
        {
            TP->catch_msg("You throw the "+what+" at "+QCTNAME(enemy)+", "+
                "but "+PRONOUN(enemy)+" dodges just in time.\n");

            tell_room(E(TP), QCTNAME(TP)+" throws "+LANG_ADDART(what)+" "+
                "at "+QTNAME(enemy)+", but "+PRONOUN(enemy)+" dodges "+
                "just in time.\n", ({ TP, enemy }));

            enemy->catch_msg(QCTNAME(TP)+" throws "+LANG_ADDART(what)+" "+
                "at you, but you dodge just in time and it misses.\n");

            TP->add_fatigue(-(1 + random(5)));
            TO->move(E(TP));
            return 1;
        }

        hs  = (as / 5 > 20 ? 20 : as / 5);
        dam = (hs * obweight > 150 ? 150 : hs * obweight);

        TP->catch_msg("You throw the "+what+" at "+QCTNAME(enemy)+". It "+
            "flies through the air and hits "+OBJECTIVE(enemy)+" "+
            HARDNESS[(hs / 2) - 1]+".\n");

        tell_room(E(TP), QCTNAME(TP)+" throws "+LANG_ADDART(what)+" at "+
            QTNAME(enemy)+". It flies through the air and hits "+
            OBJECTIVE(enemy)+" "+HARDNESS[(hs / 2) - 1]+".\n", ({ TP, enemy }));

        enemy->catch_msg(QCTNAME(TP)+" throws "+LANG_ADDART(what)+" at "+
            "you. It flies through the air and hits you "+
            HARDNESS[(hs / 2) - 1]+".\n");

        enemy->heal_hp(-dam);

        if(enemy->query_hp() <= 0)
            enemy->do_die(TP);
        else
        {
            if(!objectp(enemy->query_attack()))
                enemy->attack_object(TP);

            if(enemy->query_attack() != TP)
            {
                TP->catch_msg(QTNAME(enemy)+" turns to attack you!\n");
                enemy->catch_msg("You turn to attack "+QTNAME(TP)+".\n");
                tell_room(E(enemy), QCTNAME(enemy)+" turns to attack "+
                    QTNAME(TP)+".\n", ({ enemy, TP }));

                enemy->attack_object(TP);
            }
        }

        TP->add_fatigue(-(1 + random(5)));
        TO->move(E(TP));
        return 1;
    }
    write("Syntax: 'throw [what] at [whom]'.\n");
    return 1;
}
