/*********************************************************************
 * - scarf.c                                                       - *
 * - A white scarf for the shops in the                            - *
 * - Gentleman's club                                              - *
 * - Created by Damaris 10/2001                                    - *
 *********************************************************************/
#pragma strict_types

inherit "/std/armour";

#include "/d/Raumdor/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

void create_armour()
{
    set_short("long elegant scarf");
    set_pshort("long elegant scarves");
    set_name("scarf");
    set_adj(({"long", "elegant", "white"}));
    set_long("This is a fine gentleman's scarf. It is made from the "+
    "finest silk available in Raumdor. It has been specially woven by "+
    "special weavers just for the fine gentlemen of the Gentleman's "+
    "club. It's fine threads have carefully been dyed a soft creamy "+
    "white. It is silky smooth, full in length.\n");
    set_ac(8 + random(5));
    set_at(A_NECK);
    set_am( ({-1,3,-2 }) );

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()) + 100);
}

public string
query_recover()
{
return MASTER;
}
int
wear()
{

    {
    write("You put your " + short() + " around your neck and adjust " +
          "it charmingly.\n");

    say(QCTNAME(TP) + " puts "+ HIS(TP) +" " + short() + " around "+
        HIS(TP) +" neck and adjusts it charmingly.\n");
    }

    return 1;
}

int
remove()
{
    {
    write("You remove your " + short() + " and flash a charming smile.\n");

    say(QCTNAME(TP) + " removes "+ HIS(TP) +" " + short() + " and flashes " +
        "a charming smile.\n");
   }
    return 1;
}
int
adjust_scarf(string str)
{
     if((str == "scarf") || (str == "elegant scarf") || (str == " long scarf") || (str == "white scarf"))
    {
        if (!query_worn())
            return notify_fail("Try wearing it first.\n");

	write("You charmingly adjust your " + short() +
	" so it fits more smoothly around your neck.\n");

	say(QCTNAME(TP)+" charmingly adjusts "+ HIS(TP) +" " + short() + " "+
	"so it fits more smoothly around "+ HIS(TP) +" neck.\n");

	return 1;
    }
    return notify_fail("Adjust what?\n");
}

int
toss_gc(string str)
{
   if((str == "scarf") || (str == "elegant scarf") || (str == " white scarf") ||       (str == "long scarf"))
    {
	write("You gallantly toss your " + short() +" over your shoulder.\n");
	say(QCTNAME(TP)+" gallantly tosses " + HIS(TP) + " " +short() +
	    " over " + HIS(TP) + " shoulder.\n");
	return 1;
    }

    return notify_fail("Toss what?\n");
}

void
init()
{
    ::init();

    add_action(adjust_scarf, "adjust");
    add_action(toss_gc, "toss");

}
