/*
 * targe.c
 *
 * This is a simple base-targe for their domain-wide use in Khalakhor.
 * Originally, targes were heavy, circular shields favoured by Highland
 * Scots, but they'll probably see use in lowland regions of the
 * domain as well. Most targes bore various patterns of brass domes
 * called bosses, the central one usually with a spike through the
 * center. The actual number of bosses and designs are largely
 * irrelevant, but a few rare targes bore heraldic devices of the
 * owner. This might perhaps be replicated for clan thanes.
 *
 * This file allows for random appearance (facing cloth colour,
 * number of bosses, extra designs, and slight variation in AC).
 * Should a specific targe be wished, this can be done after the
 * base targe is cloned, by setting the desired variables and
 * calling the setup targe function again.
 *
 * Khail - March 29/97
 * 
 * Changes:
 * 2020-05-05, Cotillion
 * - Fixed issue with recovery
 * 
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

#define BASE_AC 10

inherit "/std/armour";

/* GLOBAL VARS */
int boss_num,
quality;
string colour,
pattern;
string *targe_colours = ({"red",
  "blue",
  "black",
  "white",
  "green",
  "purple"});
string *pattern_names = ({"cross",
  "celtic",
  "circles"});

/*
 * Function name: set_boss
 * Description  : Sets the boss_num var to the argument passed,
 *                which represents the additional number of satellite
 *                bosses of the targe around the central one.
 * Arguments    : i - Integer representing the number of extra
 *                    bosses, from 2 to 6.
 * Returns      : 0 - boss_num not set.
 *                1 - boss_num set.
 */
public int
set_boss(int i)
{
    if (i < 2 || i > 6)
        return 0;
    boss_num = i;
    return 1;
}

/*
 * Function name: set_colour
 * Description  : Sets the colour of the cloth covering the front
 *                of the targe.
 * Arguments    : str - String argument which is the colour of
 *                      the targe. Must be part of the targe_colours
 *                      array.
 * Returns      : 0 - Colour not set.
 *                1 - Colour set.
 */
public int
set_colour(string str)
{
    if (member_array(str, targe_colours) < 0)
        return 0;
    colour = str;
    return 1;
}

/*
 * Function name: set_pattern
 * Description  : Sets the extra patterns on the targe.
 * Arguments    : str - A single word describing which pattern
 *                      to use. I.e. 'cross' adds a celtic cross
 *                      to the targe, 'circles' adds patterns of
 *                      nailheads around the bosses. See the 
 *                      pattern switch in setup_targe for a full
 *                      list.
 * Returns      : 0 - Pattern not set
 *                1 - Pattern set.
 */
public int
set_pattern(string str)
{
    if (member_array(str, pattern_names) < 0)
        return 0;
    pattern = str;
    return 1;
}

/*
 * Function name: set_quality
 * Description  : Sets the quality of the targe as a percentage
 *                which will effect the AC. Valid range from 
 *                75%-125%.
 * Arguments    : i - Integer representing quality percent.
 * Returns      : 0 - Quality not set.
 *                1 - Quality set.
 */
public int
set_quality(int i)
{
    if (i < 75 || i > 125)
        return 0;
    quality = i;
    return 1;
}

/*
 * Function name: setup_targe
 * Description  : Generates variables to make 'random' targes,
 *                if not already set. This can only be overriden
 *                by another object resetting one of the variables.
 *                the randomness is largely in appearance only,
 *                though the AC will vary slightly as well.
 * Arguments    : n/a
 * Returns      : n/a
 */
public nomask void
setup_targe()
{
    int mod_ac;
    string temp_long;

    /* No colour set, generate one randomly. */
    if (!colour)
    {
        /* 90% of all targes are red. */
        if (random(10))
            colour = "red";
        else
            colour = targe_colours[random(sizeof(targe_colours))];
    }

    /* If no number of bosses is set, generate randomly. */
    if (!boss_num)
    {
        switch (random(100))
        {
        case 0..30:
            boss_num = 0;
            break;
        case 31..60:
            boss_num = 2;
            break;
        case 61..80:
            boss_num = 3;
            break;
        case 81..90:
            boss_num = 4;
            break;
        case 91..96:
            boss_num = 5;
            break;
        default:
            boss_num = 6;
        }
    }

    /* If no pattern set, randomly select one. */
    if (!pattern)
    {
        /* Only 20% of targes have extra patterns. */
        if (!random(5))
            pattern = pattern_names[random(sizeof(pattern_names))];
        else
            pattern = "";
    }

    /* If no quality set, randomly select one. */
    if (!quality)
    {
        /* 50% of targes are 'average' quality. */
        if (!random(2))
            quality = 100;
        else
            quality = random(51) + 75;
    }

    /* Now set the ac based off of quality and # of bosses. */
    mod_ac = ftoi(itof(BASE_AC + boss_num) * itof(quality) / 100.0);
    set_ac(mod_ac);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(mod_ac));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(mod_ac, A_SHIELD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);     

    temp_long = "The targe is a type of shield favoured by the " +
    "Highlanders, though used frequently by others. It is " +
    "circular in shape, and a little wider than your forearm " +
    "is long. Made from heavy straps of oak as thick as " +
    "your thumb, the front is faced with a heavy " + colour + 
    " fabric. Atop the fabric, a large brass dome, known " +
    "as a boss, holds a long spike in the center of the targe.";
    if (boss_num)
        temp_long += " Spaced evenly around the central boss, " +
        LANG_WNUM(boss_num) + " more smaller bosses provide " +
        "a bit more resistance to attack.";
    if (pattern)
    {
        switch (pattern)
        {
        case "cross":
            temp_long += " Engraved deeply into the center " +
            "boss is a large cross with a circle connecting " +
            "the four arms.";
            break;
        case "celtic":
            temp_long += " The fabric of the targe is covered " +
            "with intricate, interweaving lines, which seem " +
            "to have no beginning or end.";
            break;
        default:
            temp_long += " A series of circles formed by bright " +
            "brass nailheads adorn the front of the targe.";
        }
    }

    temp_long += " The back of the targe is covered in soft, if " +
    "worn-looking, deerskin. A thick leather strap and an " +
    "iron grip provides a means of wearing the shield.";

    set_long(temp_long + "\n");
}

/*
 * Function name: create_armour
 * Description  : Turns this object into armour.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_armour()
{
    set_name("targe");
    add_name("shield");
    set_short("heavy round targe");
    set_pshort("heavy round targes");
    set_adj("heavy");
    add_adj("round");
    setup_targe();

    set_at(A_SHIELD);
    set_af(TO);
}

/*
 * Function name: stat_object (MASK)
 * Description  : Generates output for the 'stat' command. Masked
 *                to provide addition information on quality, 
 *                colour, boss_num and pattern name.
 * Arguments    : n/a
 * Returns      : A formatted string usually output with the stat
 *                command.
 */
public string
stat_object()
{
    string ret;

    ret = ::stat_object();

    ret += "Colour: " + colour + "\n";
    ret += "Pattern: " + pattern + "\n";
    ret += "Bosses: " + boss_num + "\n";
    ret += "Quality: " + quality + "\n";

    return ret;
}

/*
 * Function name: query_recover (MASK)
 * Description  : Adds the colour, quality, pattern and bosses 
 *                vars to the usual recover string.
 * Arguments    : n/a
 * Returns      : A string used as the full recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + boss_num + "@" + quality + "@" +
    colour + "@" + pattern + "@" + query_arm_recover();
}

/*
 * Function name: init_recover (MASK)
 * Description  : Called with the argument to the recovery string
 *                when this object is cloned as a recovering item.
 *                Used to reset variables so the shield is the same
 *                one it was before recovery.
 * Arguments    : arg - A string containing the recovery string
 *                      arguments (i.e. the string which follows
 *                      the : generated in query_recover()).
 * Returns      : n/a
 */
public void
init_recover(string arg)
{
    string extra;

    sscanf(arg, "%d@%d@%s@%s@%s", boss_num, quality, colour, 
      pattern, extra);
    init_arm_recover(extra);
}

/*
 * Function name: wear (MASK)
 * Description  : This function might be called when someone tries to wear
 *                this armour. Used simply to add new wear message.
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    write("You slip your arm through the " + short() + "'s " +
      "leather strap, and take a firm grip on the iron " +
      "handle.\n");
    say(QCTNAME(TP) + " slips " + HIS + " arm through " + HIS + 
      " " + short() + "'s leather strap, and takes a firm grip " +
      "on it's iron handle.\n");
    return 1;
}

/*
 * Function name: remove (MASK)
 * Description  : This function might be called when someone tries to remove
 *                 this armour. Used here to add new remove message.
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
mixed
remove(object obj)
{
    if (wearer->query_hp() <=0)
    {
        return 1;
    }

    wearer->catch_tell("You release your grip on the " + short() +
      "'s iron handle, and slip your arm out of it's leather " +
      "strap.\n");
    if (this_player() == wearer)
    {
        tell_room(environment(wearer), QCTNAME(wearer) + 
          " releases " + HIS_HER(wearer) + " grip on " +
          HIS_HER(wearer) + " " + short() + "'s iron handle, " +
          "and slips " + HIS_HER(wearer) + " arm out of " +
          "its leather strap.\n", ({wearer}));
    }
    return 1;
}
