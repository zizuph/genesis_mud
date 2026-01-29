// Created by Ibun, summer 2007
// Together with the thief_gloves the cloak forms a set.

/*
 * Revisions:
 * 	Lucius, Jun 2017: Cleaned up duplicated code and
 * 	                  extra_skill handling.
 */
#pragma strict_types

#include "/d/Avenir/common/common.h"
inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>     /* Where the properties are defined. */
#include <wa_types.h>          /* Where weapon and armour defs are. */
#include <ss_types.h>          /* Where the skill defines are.      */
#include <formulas.h>          /* Where the formulas for value, */
#include <terrain.h>

#define EXTRA_HIDE	10
#define EXTRA_SNEAK	10

/* WHO, SKILL, AMOUNT */
#define INC_SK_EXTRA(x, y, z) (x)->set_skill_extra(y, \
    (x)->query_skill_extra(y) + z)
#define DEC_SK_EXTRA(x, y, z) (x)->set_skill_extra(y, \
    (x)->query_skill_extra(y) - z)

#define DBG(msg) if (wearer->query_wiz_level()) \
    wearer->catch_tell("Wizinfo: "+ msg +"\n");


int extra_hide, extra_sneak, last_hide;


void
create_armour()
{
    set_name("cloak");
    add_name("_ave_shadow_cloak");
    set_adj("gray");
    add_adj(({"dull","shadow"}));
    set_short("dull gray cloak");
    set_long("The cloak is dull gray without any " +
        "other significant features other than a cross branded " +
        "on its back.\n");
    set_at(A_ROBE);
    set_ac(3);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE) );
    set_af(this_object());
    set_keep(1);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20) + 100);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This cloak is enchanted. ", 10,
        "It has the virtues of affecting the wearers "+
        "stealth under special conditions. ", 50,
        "Together with a spider knife it might raise stealth and " +
        "might allow the wearer to hide in the shadows.\n", 90})),
    add_prop(OBJ_S_WIZINFO,
        "The cloak completes a set with a spider knife " +
        "for thieves.\n");
}

void
init()
{
    ::init();
    add_action("hide_in_shadows", "hide");
}

mixed
wear(object ob)
{
    int extra;
    object gloves = wearer->query_armour(A_HANDS);

    DBG("WEARER == " + wearer->query_name());

    if (!extra_hide)
    {
	extra = wearer->query_skill_extra(SS_HIDE);
	INC_SK_EXTRA(wearer, SS_HIDE, EXTRA_HIDE);
        extra_hide = wearer->query_skill_extra(SS_HIDE) - extra;
	DBG("Added extra hide skill: "+  extra_hide);
    }

    // Gloves are worn, add the extra skills for complete set
    if (gloves && gloves->id("_ave_thief_gloves"))
    {
	if (!extra_sneak)
	{
	    DBG("GLOVES FOUND: Adding extra sneak skill.");
	    extra = wearer->query_skill_extra(SS_SNEAK);
	    INC_SK_EXTRA(wearer, SS_SNEAK, EXTRA_SNEAK);
	    extra_sneak = wearer->query_skill_extra(SS_HIDE) - extra;
	    DBG("Added extra sneak skill: "+  extra_sneak);
	}

	// Adds extra knife skill
        gloves->add_extra_skills();
    }
    return 0;
}

mixed
remove(object ob)
{
    object gloves = wearer->query_armour(A_HANDS);

    DBG("WEARER == " + wearer->query_name());

    if (extra_hide)
    {
	DBG("Removing extra hide skill.");
	DEC_SK_EXTRA(wearer, SS_HIDE, extra_hide);
        extra_hide = 0;
    }

    if (extra_sneak)
    {
	DBG("Removing extra sneak skill.");
	DEC_SK_EXTRA(wearer, SS_SNEAK, extra_sneak);
	extra_sneak = 0;
    }

    // Removes extra knife skill
    if (gloves && gloves->id("_ave_thief_gloves"))
        gloves->remove_extra_skills();

    return 0;
}

int
remove_extra_skills()  // Called if the player remove the gloves
{
    if (!extra_sneak)
	return 0;

    DBG("GLOVES REMOVED: Removing extra sneak skill.");
    DEC_SK_EXTRA(wearer, SS_SNEAK, extra_sneak);
    extra_sneak = 0;
    return 1;
}

int
add_extra_skills()   // Called if the player wear the gloves
{
    int extra;

    if (extra_sneak)
	return 0;

    DBG("GLOVES WORN: Adding extra sneak skill.");
    extra = wearer->query_skill_extra(SS_SNEAK);
    INC_SK_EXTRA(wearer, SS_SNEAK, EXTRA_SNEAK);
    extra_sneak = wearer->query_skill_extra(SS_HIDE) - extra;
    return 1;
}

void
do_hide()
{
    // BOOST!
    INC_SK_EXTRA(TP, SS_HIDE, 100);
    DBG("Hiding with " + TP->query_skill(SS_HIDE) + " value.\n");

    if (TP->command("$hide"))
	write("You sneak further into the shadows.\n");

    last_hide = time();
    DEC_SK_EXTRA(TP, SS_HIDE, 100);
}

/*
    Various checks before the player can perform
    a hide in the shadows.
*/

int
hide_in_shadows(string str)
{
    if (!query_worn())
	return 0;

    if (!strlen(str))
	return 0;

    if ((str != "in shadows") && (str != "in the shadows"))
	return notify_fail("Hide in the shadows?\n");

    if (!CAN_SEE_IN_ROOM(TP))
    {
        // If he can not see in the room, he can not hide
        write("You can not see well enough to hide.\n");
        return 1;
    }

    if (TP->query_attack())
    {
        write("You are in the middle of combat!\n");
        return 1;
    }

    if (sizeof(FILTER_IS_SEEN(TP,
		FILTER_OTHER_LIVE(all_inventory(ENV(TP))))))
    {
        write("You can not do that while others can see you.\n");
        return 1;
    }

    object gloves = TP->query_armour(A_HANDS);

    // Both items worn forming a complete set
    if (!gloves->id("_ave_thief_gloves"))
    {
        // Gloves must be worn
	write("You lack the ability to do that.\n");
        return 1;
    }

    if ((time() - last_hide) <= 180)
    {
        if (TP->query_wiz_level())
	{
            write("Wizinfo: Your wizard status allows you to hide " +
                "sooner than normal.\n");
	}
        else
	{
	    // 3 mins between each hide
	    write("You can not do this so soon after last attempt.\n");
	    return 1;
	}
    }

    // Check the light level in this room
    if (ENV(TP)->light() >= 2)
    {
	// Not enough shadows, light level 2+
	write("There is too much light in here.\n");
	return 1;
    }

#if 0
    // Shadows allows hide
    if (ENV(TP)->terrain_includes_all(TERRAIN_SHADOWS))
	do_hide();
    else
	write("There are not enough shadows here to do that.\n");
#endif

    do_hide();
    return 1;
}
