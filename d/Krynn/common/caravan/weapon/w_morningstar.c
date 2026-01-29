/*
 *  Filename:       w_morningstar.c
 *  Description:    A lance for knights riding the caravan
 *
 *
 *  Copyright (c) Nov. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Commerce part taken from other place done by Boron.

 *  Change log:
 */

inherit "/std/weapon";
inherit "/d/Genesis/lib/commodity";
#include "/sys/macros.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../local.h"
#define SS_WOLF_RIDING 135001


#define  TO_HIT              42
#define  TO_PEN              44
#define  TO_HIT_GAUNTLET     48
#define  TO_PEN_GAUNTLET     45
#define  FATIGUE_PENALTY      8
#define  STUN_TIME           10
#define  PARRY_PENALTY        5
#define  SECONDS_BETWEEN_SWINGS 3

int momentum; //momentum can run from 1 to 5
int mounted = 0;
string steed;
int lastswing;




/*
 * Function name: swing
 * Description:   Enables the momentum gaining if one is not mounted,
 *                adds fatigue to the one trying to swing - and momentum.
 *                Momentum is used in the did_hit function, to grant a
 *                chance to do extra damage or even break a shield/helmet
 *                on the opponent.
 *
 * Arguments:     string str - expected to be 'morningstar' for it to swing,
 * Return value:  1 if succesful swinging, 0 if not.
 */

public int
swing(string str)
{
    if (time() - SECONDS_BETWEEN_SWINGS < lastswing)
    {
        write("You swing the morningstar around without gaining any more momentum.\n");
        return 1;
    }

    lastswing = time();
    if (str == "morningstar" && wielded)
    {
        wielder->add_fatigue(-(FATIGUE_PENALTY * (momentum + 1)));
        /* did we run out of fatigue? then we stop swinging it around and
           drops the momentum */
        if (wielder->query_fatigue() <= 10)
        {
            write("You swing the morningstar around, but the strain is too " +
                  "hard, and you give up.\n");
            say(QCTNAME(TP) + " swings the " + short() + " around shortly " +
                "and stops.\n", TP);
            momentum = 0;
            return 1;
        }

        switch (momentum)
        {
            case 0:
            {
                write("You start swinging the ball and chain of the " + short() +
                " around slowly gaining momemtum.\n");
                say(QCTNAME(TP) + " starts swinging the ball and chain of the " +
                short() + " around, slowly gaining momentum.\n", TP);
                momentum = 1;
                return 1;
            }
            case 1:
            {
                write("You continue spinning the swinging ball around " +
                      "gaining more momentum.\n");
                say(QCTNAME(TP) + " continues spinning the swinging ball " +
                      " around, gaining momentum.\n", TP);
                momentum = 2;
                return 1;
            }
            case 2:
            {
                write("With some effort you swing the ball and chain of the " +
                short() + " above your head, gaining momentum.\n");
                say(QCTNAME(TP) + " swings the ball and chain of the " +
                short() + " above the head, gaining a powerful " +
                "momentum.\n", TP);
                momentum = 3;
                return 1;
            }
            case 3:
            {
                write("In a quick pace, you start getting a certain rythm " +
                      "into the spin of the " + short() + " gaining an " +
                      "incredible momentum.\n");
                say(QCTNAME(TP) + " starts speeding up the pace of the " +
                        "swinging " + short() + ", gaining an incredible " +
                        "momentum.\n",TP);
                momentum = 4;
                return 1;
            }
            case 4:
            {
                write("With a mad glint in your eyes, you gather the last " +
                      "strength in you, and push the spinning " + short() +
                      " into a furious whirling metal ball of destruction " +
                      "above your head .\n");
                say(QCTNAME(TP) + " seems to concentrate deeply gathering " +
                        "all " + HIS(wielder) + " strength making the " +
                        short() + " into a furious ball of whirling metal " +
                        "death above " + HIS(wielder) +
                        "'s head.\n" ,TP);
                return 1;
            }
            case 5:
            {
                write("You don't have the strength to swing it any faster.\n");
                momentum = 5;
                return 1;
            }
        }
    }
    else
        return 0;

}


public void
create_weapon()
{
    set_name("morningstar");
    add_name(({"weapon","club"}));
    set_pname("morningstars");
    add_pname("weapons");
    set_adj(({"steel", "spiked"}));
    set_short("steel spiked morningstar");
    set_pshort("steel spiked morningstars");
    set_long("This morningstar consists of a wooden handle attached to " +
      "a chain with a steel spiked ball the size of a mans head. The sheer " +
      "weight of the spiked steel ball gives it the ability to crush through " +
      "shields and other heavy armours, if one can get the momentum behind " +
      "it that is. The handle has a reinforced grip, that makes it " +
      "attachable with a special steel gauntlet used for jousting contests.\n");
    set_default_weapon(TO_HIT,TO_PEN, W_CLUB, W_BLUDGEON, W_RIGHT);

    set_commodity_name ("w_morningstar"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_WEAPON(TO_HIT,TO_PEN), 0);

    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(TO_HIT,TO_PEN));
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }) );
    add_prop(OBJ_S_WIZINFO, "This morningstar is more effective on " +
        "a mounted warrior and that is why such will receive additional " +
        "bonuses depending on some mounted skills.\nFurthermore one " +
        "can 'swing' the morningstar to gain momentum which will give it " +
        "the ability to break armours on the cost of fatigue if not " +
        "mounted.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "The morningstar has been created for jousting contests and blessed " +
        "to do more damage than normal, especially mounted.\n", 10,
        "One can swing the morningstar around to further increase the " +
        "momentum of the star when it strikes.\n" , 20,
        "With the momentum increased, it may break armours when it strikes." +
        "giving the victim a heavier blow.\n " , 65 }) );

    set_wf(TO);

}

int
wield_check(object ob)
{

    momentum = 0; //no momentum gained.
    if ( query_wielded()->query_npc() )
    {
        set_hit(TO_HIT_GAUNTLET);
        set_pen(TO_PEN_GAUNTLET);
        query_wielded()->update_weapon(TO);

        return 1;
    }
}

mixed
wield(object ob)
{
    if ( !interactive(TP) )
    {
        set_alarm(1.0, 0.0, &wield_check(TO));
        return 1;
    }
}

int
unwield(object what)
{
    momentum = 0; //remove momentum gained.
    steed = 0;
    mounted = 0;

    set_hit(TO_HIT);
    set_pen(TO_PEN);
    query_wielded()->update_weapon(TO);

    return 0;
}
/*
 * Function name: special_hit
 * Description:   Checks if the swinging is enabled, and if it is
 *                hitting an arm, then it will have a chance of
 *                breaking the shield.
 *                The more momentum, the bigger chance of success.
 *
 *                hdesc: The hitlocation description.
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 */
int
special_hit(string hdesc, int dam, int phit)
{
    int bonus = 0;
    if ( wielder->query_steed())
        bonus = 3;

    if (random(7) < (momentum + bonus))
    {
        return 1;
    }
    return 0;
}




public int
mounted_fightmessage(int phurt ,string tmp, object enemy)
{
    string wound_adj;

    switch (phurt)
    {
    case -2..-1:
        return 0;
    case 0..4:
        wielder->catch_msg("You barely hit the " + tmp + " of " +
             QTNAME(enemy) + " with the swing of your " + short() + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " barely hits your " + tmp +
            " with the swing of " + POSSESSIVE(wielder) + " " + short() + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " barely hits the " + tmp +
            " of " + QTNAME(enemy) + " with the swing of " + POSSESSIVE(wielder) +
            " " + short() + ".\n", enemy);
    break;
    case 5..19:
        wound_adj = ({ "light", "minor", "mediocre"  })[random(3)];

        wielder->catch_msg("While riding by " + QTNAME(enemy) +
            " you hit a " + wound_adj + " blow in the " +
            tmp + " of " + HIM(enemy) + ".\n");
        enemy->catch_msg("As " + QCTNAME(wielder) + " rides by you, " +
            HIS(wielder) + " " + short() + " hits with a " + wound_adj  +
            " blow in your " + tmp + ".\n");
        wielder->tell_watcher("As " + QCTNAME(wielder) + " rides by " +
            QTNAME(enemy) + ", " + HE(wielder) + " hitting a " + wound_adj +
            " blow in " + HIS(enemy) + " " + tmp +  ".\n" ,enemy);
    break;
    case 20..30:
        wound_adj = ({ "shallow", "painful", "big",
            "bleeding" })[random(4)];

        wielder->catch_msg("You spin around the " + steed +
            " and hits " + QTNAME(enemy) + " with a heavy blow of the " +
            "spiked ball, leaving a " + wound_adj + " wound.\n");
        enemy->catch_msg(QCTNAME(wielder) + " spins the " + steed +
            " around and hits you with a heavy blow of the spiked " +
            "ball, leaving a " + wound_adj + " wound.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " spins the " +
            steed + " around and hits "+  QTNAME(enemy) +
            " with a heavy blow of the spiked ball, leaving a " +
            wound_adj + " wound.\n",  enemy);
    break;
    case 31..55:
        wielder->catch_msg("You spur your " + steed + " forward " +
            "into a charge, and hits " + QTNAME(enemy) +
            " with your " + short() + ", with a heavy blow to " + HIS(enemy) +
            " " + tmp + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " spurs the " + steed +
            " forward and hits you with " + HIS(wielder) + " " + short() +
            ", beating your " + tmp + " deeply.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " spurs the " +
            steed + " forward and hits " + QTNAME(enemy)
            + " with " + HIS(wielder) + " " + short() + ", beating " +
            HIS(enemy) + " " + tmp + " deeply.\n",enemy);
    break;
    case 56..68:
        wound_adj = ({ "bleeding", "serious", "deep",
            "badly looking" })[random(4)];

        wielder->catch_msg("Digging the heels into the sides of the " +
            steed + ", you rush forward with your " + short() +
            " swinging around, making a " + wound_adj + " wound into the " +
            tmp + " of " + QTNAME(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " digs " +
            HIS(wielder) + " heels into the sides of the " + steed +
            " swinging the " + short() + " around, causing a " + wound_adj +
            " wound into the " + tmp + " of you.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " digs " +
            HIS(wielder) + " heels into the sides of the " + steed +
            " swinging the " + short() + " around, causing a " + wound_adj +
            " wound into the " + tmp + " of " + QCNAME(enemy) +".\n", enemy );
    break;
    case 69..88:
        wielder->catch_msg("Charging directly at " + QTNAME(enemy) +
            " you smash the " + short() + " deep into " + HIS(enemy) +
            " " + tmp  + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " charges directly at you " +
            "smashing " + HIS(wielder) + " " +short() +
            " deep into your " + tmp + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " charges directly at " +
            QTNAME(enemy) + " smashing " + HIS(wielder) + " " + short() +
            " deep into " + QTNAME(enemy) + "'s " + tmp + ".\n", enemy );

    break;
    default:
        wielder->catch_msg("Charging directly at " + QTNAME(enemy) +
            " you smashing the " + short() + " deep into " + HIS(enemy) +
            " " + tmp  + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " charges directly at you " +
            "smashing " + HIS(wielder) + " " +short() +
            " deep into your " + tmp + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " charges directly at " +
            QTNAME(enemy) + " smashing " + HIS(wielder) + " " + short() +
            " deep into " + QTNAME(enemy) + "'s " + tmp + ".\n" , enemy);

    break;

    }
    return 1;
}



public int
testing(object enemy)
{
    mounted_fightmessage(-2,"body", enemy);
    mounted_fightmessage(3,"body", enemy);
    mounted_fightmessage(8,"body", enemy);
    mounted_fightmessage(25,"body", enemy);
    mounted_fightmessage(45,"body", enemy);
    mounted_fightmessage(60,"body", enemy);
    mounted_fightmessage(72,"body", enemy);
    mounted_fightmessage(98,"body", enemy);
    return 0;
}



/*
 * Function name: did_hit
 * Description:   Masks the did_hit function to give better
 *                combatmessages while mounted, and to test
 *                if there's a change in the mounted situation
 *                And finally to give a chance of breaking armours
 *                if the morningstar has gained momentum to use.
 *
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 *                hid:   The hitlocation id
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over */


public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int r;
    string tmp;

    testing (enemy);
    return 1;

    r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (special_hit(hdesc, dam, phit));
        return 1;

    if ( wielder->query_steed())
    {

        /* Switch to high power */
        if (!mounted)
        {
            mounted = 1;
            steed = wielder->query_steed()->steed_short();

        }

        tmp = hdesc;
        if (tmp == 0)
            tmp = "body";
        mounted_fightmessage(phurt , tmp, enemy);

    }
    else
    {
 //       DEBUG_MSG ("I AM NOT MOUNTED");
        /* Switch to low power */
        if (mounted)
        {
            mounted = 0;
        }

    }





    return r;
}


public void
init()
{
    ::init();

    add_action (swing, "swing");


}
