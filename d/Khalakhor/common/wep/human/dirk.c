/*
 * dirk.c
 *
 * A simple dirk for common-place use across the domain.
 *
 * Khail - March 29/97
 * 
 * Modification Log:                         Date:
 * Added set_short and pshort. --  Tomas     June 08/00
 */
#pragma strict_types

#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define BASE_HIT  14
#define BASE_PEN  13

inherit "/d/Khalakhor/std/weapon";

/* Global Vars */
int quality;
string hilt,
      *hilts = ({"oak",
                 "horn",
                 "bone"});

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
 * Function name: set_hilt
 * Description  : Sets the material the hilt is dominantly constructed
 *                from. Specifically the actual handgrip. Must be one
 *                of the types listed in the hilts array.
 * Arguments    : str - The type of hilt to set. I.e. 'bone' for a
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
 * Function name: setup_dirk
 * Description  : Turns this knife into a dirk. Certain
 *                variables are randomly selected, but can
 *                be manually overriden with the appropriate
 *                set functions.
 * Arguments    : n/a
 * Returns      : n/a
 */
public nomask void
setup_dirk()
{
    string temp_long;
    int myhit,
        mypen;

    temp_long = "This long knife is known as a dirk. A quite " +
        "popular weapon, it has a wide double-edged blade and " +
        "a straight tang construction.";

  /* If no hilt specified, always choose random hilt. */
    if (!hilt)
        hilt = hilts[random(sizeof(hilts))];

    set_adj(hilt + "-handled");
    set_short(hilt + "-handled dirk");
    set_pshort(hilt + "-handled dirks");

    temp_long += " A brass bolster functions as a spacer between " + 
        "the blade and " + LANG_ADDART(hilt) + " handle, which is " +
        "held in place by a simple brass nut.\n";

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

    set_hit(myhit);
    set_pen(mypen);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(myhit, mypen));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}    

/*
 * Function name: create_khalakhor_weapon
 * Description  : Turns this object into a weapon.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_weapon()
{
    set_name("dirk");
    set_pname("dirks");
    add_name("knife");
    set_wt(W_KNIFE);
    set_hands(W_ANYH);
    set_dt(W_SLASH | W_IMPALE);

    setup_dirk();
}

/*
 * Function name: stat_object (MASK)
 * Description  : Generates output for the 'stat' command. Masked
 *                to provide addition information on quality, 
 *                and hilt.
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
    ret += "Hilt: " + hilt + "\n";

    return ret;
}

/*
 * Function name: query_recover (MASK)
 * Description  : Adds the quality and hilt 
 *                vars to the usual recover string.
 * Arguments    : n/a
 * Returns      : A string used as the full recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" +  quality + "@" +  hilt + "@" +
        query_wep_recover();
}

/*
 * Function name: init_recover (MASK)
 * Description  : Called with the argument to the recovery string
 *                when this object is cloned as a recovering item.
 *                Used to reset variables so the dirk is the same
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

    sscanf(arg, "%d@%s@%s", quality, hilt, extra);
    init_wep_recover(extra);
}
