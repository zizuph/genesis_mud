/*
 * claymore.c
 *
 * A simple claymore for use spread out over the entire domain.
 * Claymore are large swords, sometimes standing the height of
 * a man from blade tip to pommel. Claymores are truely named
 * as Claidheamh mor (gaelic for 'sword great'), and are referenced
 * by this name in some places of the domain, so is included as
 * a name. There are some discrepancies in the spelling of the
 * word 'claidheamh' (great or big), this one I picked as it was
 * this way in 2 out of 3 dictionaries I found.
 *
 * Khail - March 29/97
 */
#pragma strict_types

#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define BASE_HIT  30
#define BASE_PEN  38

inherit "/d/Khalakhor/std/weapon";

/* Global Vars */
int quality;
string pattern,
quillion,
hilt;

string *pattern_names = ({"celtic",
  "stained"});
string *quillions = ({"brass",
  "iron",
  "steel"});
string *hilts = ({"wire",
  "leather",
  "oak",
  "pine"});

/*
 * Function name: set_quality
 * Description  : Sets the quality of the weapon from between
 *                75 to 125% of the base hit/pens.
 * Arguments    : i - Integer from 75 to 125.
 * Returns      : 0 - Quality not set.
 *                1 - Quality set.
 */
public nomask int
set_quality(int i)
{
    if (i < 75 || i > 125)
        return 0;
    quality = i;
    return 1;
}

/*
 * Function name: set_quillions
 * Description  : Sets the material the claymore's quillions (cross 
 *                piece) and pommel are made from. Must be one of the
 *                types available in the quillions array.
 * Arguments    : str - Type of quillion as a string. i.e. 'brass'.
 * Returns      : 0 - Quillions not set.
 *                1 - Quillions set.
 */
public nomask int
set_quillions(string str)
{
    if (member_array(str, quillions) < 0)
        return 0;
    quillion = str;
    return 1;
}

/*
 * Function name: set_hilt
 * Description  : Sets the material the hilt is dominantly constructed
 *                from. Specifically the actual handgrip. Must be one
 *                of the types listed in the hilts array.
 * Arguments    : str - The type of hilt to set. I.e. 'wire' for a
 *                      wire-wrapped grip.
 * Returns      : 0 - Hilt not set.
 *                1 - Hilt set.
 */
public nomask int
set_hilt(string str)
{
    if (member_array(str, hilts) < 0)
        return 0;
    hilt = str;
    return 1;
}

/*
 * Function name: set_pattern
 * Description  : Sets a special pattern for the blade of the sword.
 *                Must be in the pattern_names array.
 * Arguments    : str - The pattern for the blade. I.e. 'stained' for
 *                      a blade that is stained black.
 * Returns      : 0 - Pattern not set.
 *                1 - Pattern set.
 */
public nomask int
set_pattern(string str)
{
    if (member_array(str, pattern_names) < 0)
        return 0;
    pattern = str;
    return 1;
}

/*
 * Function name: setup_claymore
 * Description  : Turns this sword into a claymore. Certain
 *                variables are randomly selected, but can
 *                be manually overriden with the appropriate
 *                set functions.
 * Arguments    : n/a
 * Returns      : n/a
 */
public nomask void
setup_claymore()
{
    string temp_long;
    int myhit,
    mypen;

    temp_long = "This massive sword, known as a claidheamh mor, or " +
    "claymore, truely lives up to its name meaning great " +
    "sword. From tip to pommel, it's almost as tall as a " +
    "fully-grown male human.";

    /* If no quillion set, 50% chance for a random quillion. */
    if (!quillion)
    {
        if (!random(2))
            quillion = quillions[random(sizeof(quillions))];
        else
            quillion = "";
    }

    temp_long += " Its " + (strlen(quillion) ? quillion + " " : "") +
    "quillions are swept " +
    "fowards at a sharp angle towards the blade";

    /* If no pattern is set, 25% chance of random pattern. */
    if (!pattern)
    {
        if (!random(4))
            pattern = pattern_names[random(sizeof(pattern_names))];
        else
            pattern = "";
    }

    if (!strlen(pattern))
        temp_long += ".";
    else
    {
        switch (pattern)
        {
        case "celtic":
            temp_long += ", which is covered in intricate " +
            "designs of seemingly continuous lines " +
            "weaving sharply in and out of one another.";
            break;
        default:
            temp_long += ", which has been stained a deep " +
            "black, somehow.";
        }
    }

    /* If no hilt specified, always choose random hilt. */
    if (!hilt)
        hilt = hilts[random(sizeof(hilts))];

    temp_long += " Between the " + 
    (strlen(quillion) ? quillion + " " : "") + "quillions and " +
    "pommel, " + LANG_ADDART(hilt) + " grip as long as most " +
    "knives provides a means of two-handed wielding.\n";

    set_long(temp_long);

    /* If no quality is set, randomly pick a non-standard */
    /* quality 20% of the time. */
    if (!quality)
    {
        if (!random(5))
            quality = random(51) + 75;
        else
            quality = 100;
    }

    myhit = ftoi(itof(BASE_HIT * quality) / 100.0);
    mypen = ftoi(itof(BASE_PEN * quality) / 100.0);

    set_hit((myhit > 40 ? 40 : myhit));
    set_pen((mypen > 40 ? 40 : mypen));

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(myhit, mypen));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}    

void create_claymore() {}

/*
 * Function name: create_khalakhor_weapon
 * Description  : Turns this object into a weapon.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_weapon()
{
    set_name("claymore");
    add_name("sword");
    add_name("claidheamh mor");
    set_adj("massive");
    add_adj("two-handed");
    set_short("massive two-handed claymore");
    set_pshort("massive two-handed claymores");
    set_wt(W_SWORD);
    set_hands(W_BOTH);
    set_dt(W_SLASH);

    create_claymore();
    setup_claymore();
}

/*
 * Function name: stat_object (MASK)
 * Description  : Generates output for the 'stat' command. Masked
 *                to provide addition information on quality, 
 *                quillion, hilt and pattern name.
 * Arguments    : n/a
 * Returns      : A formatted string usually output with the stat
 *                command.
 */
public string
stat_object()
{
    string ret;

    ret = ::stat_object();

    ret += "Quality: " + quality + "\n";
    ret += "Pattern: " + pattern + "\n";
    ret += "Hilt: " + hilt + "\n";
    ret += "Quillion: " + quillion + "\n";

    return ret;
}

/*
 * Function name: query_recover (MASK)
 * Description  : Adds the quillion, quality, pattern and hilt 
 *                vars to the usual recover string.
 * Arguments    : n/a
 * Returns      : A string used as the full recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + quillion + "@" + quality + "@" +
    hilt + "@" + pattern + "@" + query_wep_recover();
}

/*
 * Function name: init_recover (MASK)
 * Description  : Called with the argument to the recovery string
 *                when this object is cloned as a recovering item.
 *                Used to reset variables so the claymore is the same
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

    sscanf(arg, "%s@%d@%s@%s@%s", quillion, quality, hilt, 
      pattern, extra);
    init_wep_recover(extra);
}
