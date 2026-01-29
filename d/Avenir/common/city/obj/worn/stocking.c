// -*-C++-*-
// file name:   /d/Avenir/common/city/obj/stocking.c
// creator(s):  Lilith June 2002
// purpose:    Excellent armour for dej minha and
//             those lucky enough to defeat her.
//             Good coverage everywhere EXCEPT torso.
/*
 * Revisions:
 * 	Lilith, May 2004: Took TORSO off the set_at list. I don't know who
 * 			  added it there, but if I find TORSO in this file
 * 			  again, I am going to break someone's fingers.
 * 	Lilith, May 2004: Forgot to set_af() so the wear() check was not occuring
 * 	Ibun,   Feb 2007: Lowered the AC which is FAR to high
 * 	Ibun,   Feb 2007: Raise weight and AC to 'better' values
 * 	Lucius, Nov 2007: Reverted recent changes. Added ac modifiers.
 * 	Lucius, Mar 2010: Cleanups, Variables variables recover state.
 * 	Lilith, Mar 2014: Updated intox check.
 * 	Lucius, Aug 2017: Removed enemy check.
 *  Lilith, Sep 2021: Updated intox check to 50% of max intox.
 */
#pragma strict_types

inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Avenir/include/deities.h"
#include "/d/Avenir/include/relation.h"

private static int alarm,
		   a_ac = (46 + random(5)),
		   a_wt = (500 + random(501));

public void
remove_object(void)
{
    if (alarm)
	remove_alarm(alarm);

    ::remove_object();
}

public mixed
wear(object ob)
{
    int tox_max;
	/* I'm an infidel/enemy of Sybarus, I can't wear them */
    if (IS_INFIDEL(wearer))
    {
        return "You just can't seem to fit yourself into the "+
               short() +".\n";
    }

    /* Does player have more than 50% alcohol level? If so, don't wield */  
    tox_max = wearer->intoxicated_max() / 2;	
    if (wearer->query_intoxicated() > (tox_max) && (!wearer->query_prop(I_DRANK_WITH_SYBARUN_GOD)))
        return "You're too drunk to slip into something "+
            "as limp and complicated as this "+ short() +".\n";

    return 0;
}

private void
drunk_remove(void)
{
    alarm = 0;

    if (!worn)
	return;

    if (objectp(wear_func))
	wear_func->remove(this_object());

    tell_object(wearer, "Your skin is too sweaty from your "+
	"drinking to keep the "+ short() +" in place.\n");
    tell_room(environment(wearer), "The " + QSHORT(this_object()) +
	" worn by " + QTNAME(wearer) + " suddenly slips loose.\n",
	wearer);

    do_remove_item();
    remove_adj("worn");
    add_adj("unworn");
    worn = 0;
}

public varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    int result = ::got_hit(hid, ph, att, dt, dam);

    if (!alarm && (wearer->query_intoxicated() > (wearer->intoxicated_max() / 2)))
	alarm = set_alarm(itof(2 + random(3)), 0.0, drunk_remove);

    return result;
}

public void
create_armour(void)
{
    set_name("stocking");
    add_name(({"body stocking", "body-stocking"}));
    set_short("webcloth body-stocking");
    set_pshort("webcloth body-stockings");
    set_adj(({"sheer","body", "webcloth"}));
    set_long("This is a sheer body-stocking made of webcloth. "+
        "It covers the body from neck to ankle, leaving the "+
        "chest bare. It has the texture of finest spun silk, "+
        "and feels wonderful to the touch.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 400);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, a_wt);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "life" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"A suit of silken webcloth strong as steel.\n"+
          "A special gift from the Webbers and Weavers\n"+
          "to those who guard the life of the Hegemon.", 30}));
    add_prop(OBJ_S_WIZINFO, "This bodysuit is made of webcloth, "+
        "a substance valued for its strength and lightness. It "+
        "cannot be worn by enemies of Sybarus, and drunks don't "+
        "benefit from wearing it, either. It gives max ac of 50 "+
        "to most areas of the body.\n");

    set_default_armour(a_ac,
    // Everything but torso, which is exposed for showing tattoo
	A_LEGS | A_ANKLES | A_SHOULDERS | A_ARMS | A_BACK | A_NECK | A_MAGIC,
    // Impale, Slash, Bludgeon
	({ 1, 2, -3 }),
	this_object());
}

public string
query_recover(void)
{
    return MASTER + ":" +
	query_keep_recover() + query_arm_recover() +
	"#!"+ a_ac +"!"+ a_wt +"!#";
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
    init_keep_recover(arg);

    sscanf(arg, "%s#!%d!%d!#", arg, a_ac, a_wt);
    add_prop(OBJ_I_WEIGHT, a_wt);
    set_ac(a_ac);
}
