/*
 * /d/Gondor/common/wep/hurin_sword.c
 *
 * Longsword of Hurin, Wielded by Steward of Gondor
 *
 * Alto 23 April 2001
 *
 * Elements of code structure were borrowed from Gwyneth
 *
 * Modification log:
 * Rohim 2002-11-09      Modified did_hit to handle parries as dodges.
 * Cotillion - 2020-09-29
 * - Fixed type confusion
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";


#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include <options.h>



#define HIT 40
#define PEN 40
#define MIN_BLOODED 20

/* Global Variables */
mapping blooded = ([]);


public void
create_weapon()
{
    set_name(({"longsword", "sword", "weapon"}));
    set_pname("longswords");
    add_pname("swords");
    set_short("ancient golden-hilted longsword");
    set_pshort("ancient golden-hilted longsword");
    set_long("This sword was wielded by Hurin of Emyn Arnen, and has "
        + "ever since been carried by the Stewards of Gondor. It has a "
        + "long slender blade with deeply traced hilts. Legend says "
        + "that while the ruling Steward yet wields it, the city can "
        + "never fall to its enemies.\n");
    add_item(({"blade", "slender blade", "long blade"}), "Forged of the "
        + "finest steel in the smithies of lost Numenor, the blade shines "
        + "in even the faintest light. Not a scratch can be seen along its "
        + "long even surface.\n");
    add_item(({"hilts", "patterns", "tracings"}), "The hilts of the "
        + "ancient golden-hilted "
        + "longsword are traced with numerous looping and swirling patterns. "
        + "In five places, however, the tracings are worn away from long "
        + "use.\n");
    add_item(({"five places", "places"}), "These appear to be the places "
        + "on the hilts where a hand would wrap around them for the best "
        + "grip.\n");

    set_adj("ancient");
    add_adj("golden-hilted");
    add_adj("long");

	   set_hit(HIT);
   	set_pen(PEN);
   	set_wt(W_SWORD);
   	set_dt(W_SLASH);
   	set_hands(W_BOTH);
   	set_wf(TO);


    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,1200);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(20,22)+random(400)-100);
}


/*
 * Function     : wield
 * Description  : Wield a weapon
 * Arguments    : Object what - The weapon to wield
 * Returns      : string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
public mixed
wield(object what)
{
    int level;

    /* Do some stat/wield checks here. Only those that it
       has tasted enough blood of may wield it. */

    if (!TP->query_npc() && !TP->query_wiz_level())
    {
        level = atoi(blooded[TP->query_real_name()]);
        if (level < MIN_BLOODED)
        {
            say(QCTNAME(TP) + " seems startled as " + TP->query_pronoun()
                + " tries to wrap " + TP->query_possessive() + "hands "
                + "around the hilts of the " + short() + ".\n");
            return("You feel the spirit of Hurin of Emyn Arnen in your "
                + "mind. He does not find you worthy enough to wield his "
                + "sword.\n");
        }
    }


    /* Wield description. */
    wielded = 1;

    say(QCTNAME(TP) + " seems pleased as " + TP->query_pronoun()
        + " wields the " + short() + ".\n");
    write("As you carefully wrap your hands around the hilt of the "
        + short() + ", you feel the spirit of Hurin of Emyn Arnen in your "
        + "mind. He will tolerate your touch upon his blade .. for now.\n");
    return 1;
}

/*
 * Function    : unwield
 * Description : Unwield a weapon
 * Arguments   : object what - the weapon to unwield
 */
public mixed
unwield(object what)
{
    set_this_player(wielder);

    /* Unwield description. */
    if (wielder)
    {
        say(QCTNAME(this_player()) + " unwields the " + short() + " and " +
            "shudders involuntarily.\n", ({wielder}));
        write("You release the " + short() + " and shudder " +
            "involuntarily as the spirit of Hurin of Emyn Arnen " +
            "releases your mind.\n");
    }

    return 1;
}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();
    string wmess = "", emess = "", omess = "", ename, sword = short();

    switch(phurt)
    {
    case -1:
    case -2:
        if (!wielder->query_npc() &&
          !wielder->query_option(OPT_GAG_MISSES))
        {
            wmess = ("The " + sword + " cuts cleanly through nothing "
                + "but air as " + enemy->query_the_name(wielder)
                + " dances out of range.\n");
        }

        if (interactive(enemy) &&
          !enemy->query_option(OPT_GAG_MISSES))
        {

            emess = (wielder->query_The_possessive_name(enemy) + " "
                + sword + " cuts cleanly through the air as you dance "
                + "out of range.\n");
        }

        wielder->tell_watcher_miss(QCTPNAME(wielder) + " " + sword
            + " cuts cleanly through nothing but air as " + QTNAME(enemy)
            + " dances out of range.\n", enemy, enemy);
            break;

    case 0:
        if (!wielder->query_npc() &&
          !wielder->query_option(OPT_GAG_MISSES))
        {
            wmess = ("Your " + sword + " almost touches "
                + enemy->query_the_name(wielder) + " on "
                + enemy->query_possessive() + " " + hdesc + ".\n");
        }

        if (interactive(enemy) &&
          !enemy->query_option(OPT_GAG_MISSES))
        {
            emess = (wielder->query_The_possessive_name(enemy) + " "
                + sword + " almost touches you on your " + hdesc + ".\n");
        }

        wielder->tell_watcher_miss(QCTPNAME(wielder) + " " + sword
            + " almost touches " + QTNAME(enemy)
            + " on " + enemy->query_possessive() + " " + hdesc +
            ".\n", enemy, enemy);
            break;

    case 1..5:
        wmess = ("The spirit of Hurin seems unimpressed as the tip of "
            + "the " + sword + " makes a clean scratch on the " + hdesc
            + " of " + enemy->query_the_name(wielder) + ".\n");
        emess = (wielder->query_The_possessive_name(enemy) + " "
            + sword + " makes a clean scratch on your " + hdesc + ".\n");
        omess = (QCTPNAME(wielder) + " " + sword
            + " makes a clean scratch on the " + hdesc + " of "
            + QTNAME(enemy) + ".\n");
        break;

    case 6..10:
        wmess = ("Your " + sword + " slices a smooth cut into the " + hdesc
            + " of " + enemy->query_the_name(wielder) + ".\n");
        emess = (wielder->query_The_possessive_name(enemy) + " "
            + sword + " slices a smooth cut into your " + hdesc + ".\n");
        omess = (QCTPNAME(wielder) + " " + sword
            + " slices a smooth cut into the " + hdesc + " of "
            + QTNAME(enemy) + ".\n");
        break;

    case 11..20:
        wmess = ("The spirit of Hurin seems mildly amused as you slip the "
            + sword + " through the defences of "
            + enemy->query_the_name(wielder) + " and penetrate "
            + enemy->query_possessive() + hdesc + ".\n");
        emess = (wielder->query_the_name(enemy) + " manages to slip the "
            + sword + " through your defences and penetrates your "
            + hdesc + ".\n");
        omess = (QCTNAME(wielder) + " manages to slip the " + sword
            + " through the defences of " + QTNAME(enemy) + " and penetrates "
            + enemy->query_possessive() + " " + hdesc + ".\n");
        break;

    case 21..40:
        wmess = ("The spirit of Hurin seems slightly impressed when your "
            + sword + " slices painfully through the " + hdesc + " of "
            + enemy->query_the_name(wielder) + ".\n");
        emess = (wielder->query_The_possessive_name(enemy) + " "
            + sword + " slices painfully through your " + hdesc + ".\n");
        omess = (QCTPNAME(wielder) + " " + sword
            + " slices painfully through the " + hdesc + " of "
            + QTNAME(enemy) + ".\n");
        break;

    case 41..60:
        wmess = ("The spirit of Hurin approves as your "
            + sword + " passes cleanly through the " + hdesc + " of "
            + enemy->query_the_name(wielder) + ".\n\n"
            + "The " + sword + " hums softly as you withdraw it from "
            + enemy->query_possessive() + " " + hdesc + "!\n\n");
        emess = (wielder->query_The_possessive_name(enemy) + " "
            + sword + " passes cleanly through your " + hdesc + ".\n\n"
            + "The " + sword + " hums softly as it is withdrawn from your "
            + hdesc + "!\n\n");
        omess = (QCTPNAME(wielder) + " " + sword
            + " passes cleanly through the " + hdesc + " of "
            + QTNAME(enemy) + ".\n\n"
            + "The " + sword + " hums softly as it is withdrawn from "
            + enemy->query_possessive() + " " + hdesc + "!\n\n");
        break;

    case 61..90:
        wmess = ("The spirit of Hurin seems very impressed when your "
            + sword + " slices almost completely through the " + hdesc
            + " of "
            + enemy->query_the_name(wielder) + ".\n\n"
            + "The " + sword + " sings as it continues to cut through "
            + enemy->query_possessive() + " " + hdesc + "!\n\n");
        emess = (wielder->query_The_possessive_name(enemy) + " "
            + sword + " slices almost completely through your " + hdesc
            + ".\n\n"
            + "The " + sword + " sings as it continues to cut through your "
            + hdesc + "!\n\n");
        omess = (QCTPNAME(wielder) + " " + sword
            + " slices almost completely through the " + hdesc + " of "
            + QTNAME(enemy) + ".\n\n"
            + "The " + sword + " sings as it continues to cut through "
            + enemy->query_possessive() + " " + hdesc + "!\n\n");
        break;

    default:
        wmess = ("The spirit of Hurin fades in satisfaction as your "
            + sword + " destroys the " + hdesc + " of "
            + enemy->query_the_name(wielder) + ".\n\n"
            + "The " + sword + " thrums and shrieks as obliterates "
            + enemy->query_possessive() + " " + hdesc + "!\n\n");
        emess = (wielder->query_The_possessive_name(enemy) + " "
            + sword + " destroys your " + hdesc + ".\n\n"
            + "The " + sword + " thrums and shrieks as it obliterates your "
            + hdesc + "!\n\n");
        omess = (QCTPNAME(wielder) + " " + sword
            + " destroys the " + hdesc + " of "
            + QTNAME(enemy) + ".\n\n"
            + "The " + sword + " thrums and shrieks as it obliterates "
            + enemy->query_possessive() + " " + hdesc + "!\n\n");
        break;

    }

    wielder->catch_tell(wmess);
    enemy->catch_tell(emess);
    wielder->tell_watcher(omess, enemy, enemy);

    hits++;

    if (F_WEAPON_CONDITION_DULL(hits, wep_pen, likely_dull))
    {
        hits = 0;
        set_dull(query_dull() + 1);
    }

    ename = enemy->query_real_name();

    if (member_array(ename, m_indexes(blooded)) != -1)
    {
        blooded[ename] = (atoi(blooded[ename]) + phurt) + "";
    }
    else
    {
        blooded += ([ ename : phurt + "" ]);
    }
    return 1;
}

public mapping
query_blooded()
{
    return blooded;
}

public string
blooded_string()
{
    string indexes, values;

    indexes = implode(m_indexes(blooded), ",");
    values = implode(m_values(blooded), ",");

    return (indexes + "&" + values);
}

public void
set_blooded(string str)
{
    string *result = explode(str, "&");
    string *indexes = explode(result[0], ",");
    string *values = explode(result[1], ",");

    blooded = mkmapping(indexes, values);
    return;
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover() +
        "&&" + blooded_string();
}

public void
init_recover(string str)
{
    string *temp = explode(str, "&&");

    set_blooded(temp[1]);
    init_wep_recover(temp[0]);
    init_keep_recover(temp[0]);
}
