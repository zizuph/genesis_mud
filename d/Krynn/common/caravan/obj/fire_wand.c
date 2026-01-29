/*
 *      /w/vencar/caravan/obj/fire_wand.c
 *
 *      A wand that fire with fireballs.
 *      Created by Vencar 09/09/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      09/2003
 *
 * Based on Ansalon fermammon wand.
 */

inherit "/std/object";
inherit "/lib/holdable_item";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../wagon/wagon.h"
#include "fire.h"

int charge = 3;

string
short_descr()
{
    if(charge > 0)
    {
    return "red steel-tipped wand";
    }
    else
    return "dull steel-tipped wand";
}

/*
 * Function name:  try_all_fireball
 * Description:    Tries to hit everyone except the caster
 *                 with a fireball, which sets them on fire.
 *
 *                 Damage is the instant damage taken,
 *                 level is which level the fire starts on (1-5)
 *                 strength is how much firedamage the fire should
 *                 do every firetime * the level (strenght * level)
 *                 firetime is the time for the fire to burn.
 *
 * Returns:        nothing
*/


void
try_all_fireball(object player, int damage, int level,int strength,
                 float firetime)
{
    int rnddam, rndfire, dam;
    object fireobj;

    if (!living(player) || (TP == player))
        return;

    /* takes damage */
    dam = (OBJ + "burning_damage")->hurt_player(player, damage);

    rnddam = random(dam);
    rndfire = random(damage - 50);

    /* if damaged sustained more than the players fire resistancy
       he might go on fire. */
    if (dam <= player->query_magic_res(MAGIC_I_RES_FIRE) )
        return;


    if ( dam > 0 && ( rnddam > rndfire ) && !player->query_burning_shadow())
    /* this person goes on fire! */
    {
        setuid();
        seteuid(getuid());

        fireobj=clone_object(OBJ + "burning_object");
        fireobj->move(player,1);
        fireobj->start(player, level, strength, firetime);
    }
}

int
try_point_failure()
{
    int tmp, tmp2, fail, dam;
    object fireobj;

    tmp =  TP->query_stat(SS_INT) / 15;
    tmp += TP->query_stat(SS_WIS) / 10;
    tmp += TP->query_skill(SS_SPELLCRAFT);
    tmp += TP->query_skill(SS_FORM_CONJURATION);
    tmp += TP->query_skill(SS_ELEMENT_FIRE);

    switch (tmp)
    {
        case 0..50:
        {
            fail = 90;
            break;
        }
        case 51..100:
        {
            fail = 50;
            break;
        }
        case 101..150:
        {
            fail = 20;
            break;
        }
        case 151..500:
        {
            fail = 8;
            break;
        }
    }

    tmp2 = random(100);

    /* critical fail */
    if (tmp2 < (fail / 2))
    {

        DEBUG_MSG ("in critical fail");
        tell_object( TP, "As the wand explodes, you are engulfed in a " +
                             "huge ball of fire!\n");
        tell_room(E(TP), "The wand that " + QCTNAME(TP) + " is " +
                             "holding, explodes and engulfs " +
                              QCTNAME(TP) + " in a huge ball of fire!\n", TP);

        /* takes damage */
        dam = (OBJ + "burning_damage")->hurt_player(TP, FIREWAND_FAIL_DAMAGE);

        /* if damaged sustained more than the players fire resistancy
           he will go on fire. */
        if (dam > TP->query_magic_res(MAGIC_I_RES_FIRE) )
        {
            DEBUG_MSG ("give player fireobject");
            fireobj=clone_object(OBJ + "burning_object");
            fireobj->move(TP,1);
            fireobj->start(TP, FIREWAND_FAIL_LVL_START,
                           FIREWAND_FAIL_DOT_DAMAGE , FIRE_DEFAULT_DOT_TIME);
        }
        remove_object();
        return 0;

    }
    /*normal fail */
    if (tmp2 < fail)
        return 0;

    /* success */
    return 1;
}


int
try_recharge_failure()
{
    int tmp, tmp2, fail, dam;
    object fireobj;

    tmp =  TP->query_stat(SS_INT) / 15;
    tmp += TP->query_stat(SS_WIS) / 10;
    tmp += TP->query_skill(SS_SPELLCRAFT);
    tmp += TP->query_skill(SS_FORM_CONJURATION);
    tmp += TP->query_skill(SS_ELEMENT_FIRE);

    switch (tmp)
    {
        case 0..100:
        {
            fail = 90;
            break;
        }
        case 101..150:
        {
            fail = 40;
            break;
        }
        case 151..500:
        {
            fail = 20;
            break;
        }
    }

    tmp2 = random(100);

    /* critical fail */
    if (tmp2 < (fail / 2))
    {

        DEBUG_MSG ("in critical fail");
        tell_object( TP, "As the wand explodes, you are engulfed in a " +
                             "huge ball of fire!\n");
        tell_room(E(TP), "The wand that " + QCTNAME(TP) + " is " +
                             "holding, explodes and engulfs " +
                              QCTNAME(TP) + " in a huge ball of fire!\n", TP);

        /* takes damage */
        dam = (OBJ + "burning_damage")->hurt_player(TP,
               FIREWAND_RECHARGE_DAMAGE);

        /* if damaged sustained more than the players fire resistancy
           he will go on fire. */
        if (dam > TP->query_magic_res(MAGIC_I_RES_FIRE) )
        {
            fireobj=clone_object(OBJ + "burning_object");
            fireobj->move(TP,1);
            fireobj->start(TP, FIREWAND_RECHARGE_START,
                           FIREWAND_RECHARGE_DOT_DAMAGE ,
                           FIRE_DEFAULT_DOT_TIME);
        }
        remove_object();
        return 0;

    }
    /*normal fail */
    if (tmp2 < fail)
        tell_object( TP, "The recharging fails.\n");
        return 0;

    /* success */
    return 1;
}


int
point_wand()
{
    mixed obj;
    int dam, rnddam, rndfire, ir;


    if(!TO->query_held())
    {
        write("You have to be holding the wand to point it.\n");
        return 1;
    }


    if(charge == 0)
    {
        write("You point the wand around, but nothing happens.\n");
        say(QCTNAME(TP) + " points the dull wand around and " +
          "makes some silly gestures. Not surprisingly, nothing " +
          "happens.\n");
        return 1;
    }
    else
    {
        write("You point the wand, and with a roaring blast a fireball " +
          "shoots from the tip of the wand!\n");
        say(QCTNAME(TP) + " points the red wand and with a roaring blast " +
          "a fireball shoots from the tip of the wand!\n");

        charge -= 1;

        if (!try_point_failure())
            return 1;

        obj = all_inventory(E(TP));

        map(obj, &try_all_fireball(,FIREWAND_DAMAGE
           ,FIREWAND_LVL_START,FIREWAND_DOT_DAMAGE,FIRE_DEFAULT_DOT_TIME));

        return 1;
    }
}

string
read_writing()
{
    return "This is a wand of fireballs. Point it, " +
    "and a fireball will be shot in that general direction. " +
    "Warning! Use it with caution, as the fireball will " +
    "be quite damaging, and may harm someone unintentionally.\n";
}

int
recharge()
{
    if(!TO->query_held())
    {
    write("You can only recharge it if you are holding it.\n");
    return 0;
    }

    if(TP->query_skill(SS_SPELLCRAFT) < 75)
    {
    write("You do not have the magical skill or knowledge " +
      "to be able to recharge this wand.\n");
    return 0;
    }
    if(charge > 0)
    {
    write("You raise the wand above your head and chant the " +
      "word 'Inferno''!\nNothing seems " +
      "to happen.\n");
    say(QCTNAME(TP) + " raises a wand above " + POSSESSIVE(TP) +
      " head and begins " +
      "chanting the spidery words of magic.\n");
    return 0;
    }
    else
    {
    write("You raise the wand above your head and chant " +
      "the word 'Inferno'!\nThe wand pulses " +
      "briefly with a red light as you feel your own energies " +
      "being drawn into the wand.\nYou feel quite drained.\n");

    say(QCTNAME(TP) + " raises a wand above " + POSSESSIVE(TP) +
      " head and begins chanting the spidery words of magic.\n" +
      "The wand pulses briefly with a red light.\n");

    TP->add_mana(-random(150) - 300);

    if (!try_recharge_failure())
        return 1;

    charge += 1;
    return 1;
    }
}

void
set_charge(int number)
{
    charge = number;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

void
create_object()
{
    set_name("wand");
    set_short("@@short_descr");
    add_name("@@short_descr");
    set_long("This " + "@@short_descr@@" + " is made of " +
      "some rare sort of red wood. the steely tip is covered " +
      "slightly with soot.\n");

    add_prop(OBJ_I_WEIGHT,30);
    add_prop(OBJ_I_VOLUME,30);
    add_prop(OBJ_I_VALUE, 7500);
    add_prop(MAGIC_AM_MAGIC,({25,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This is a wand of firebals. Its  " +
    "type generally has a few charges, and can be hard to " +
    "use correctly if one is not skilled in magic. " +
    "It may be recharged, but recharging of such powerful magic " +
    "may be hazardeous for the unskilled.\n",10}));

    set_slots(W_ANYH);

    add_cmd_item("wand","point",point_wand);
    add_cmd_item("Inferno","chant",recharge);
}

