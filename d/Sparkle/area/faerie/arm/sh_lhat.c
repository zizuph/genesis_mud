/*
 * Black leather hat
 * -- Finwe, April 2005
 * tip hat to all
 * flip hat onto head
 *
 * Modification log:
 *   Gorboth (April 2011) - changed value (endless money bug otherwise)
 */

#pragma save_binary;

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

#include "defs.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_object()
{
    setuid(); seteuid(getuid());

    set_name("hat");
    add_name("cowhide hat");

    set_short("cowhide hat");
    set_long("This "+short()+" is made of soft leather with a wide " +
        "brim. The leather is fine grained and supple to the " +
        "touch. The wide brim extends about a hand's width and is " +
        "circular. There is a crease down the center of the hat, " +
        "with two dents at the front.\n");
    set_slots(A_HEAD);
    set_layers(0);
    set_looseness(5);

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 5);
}


public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}

void
init()
{  
   ::init();
   add_action("tip_hat","tip");
}



/*
 * tip_hat - tip hat at someone in greeting
 */
int
tip_hat(string str)
{
    object *oblist;

    notify_fail("You must wear the " + short() + " first.\n");
    if(!query_worn())
        return 0;

    // no string supplied
    if(!strlen(str) || str=="hat all" || str=="hat to all" || str=="hat")
    {
	write("You tip your hat to everyone present.\n");
	all(" tips " + HIS_HER(TP) + " "+short()+" to everone present, " +
        "including you.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist)|| str=="hat")
    {
	write("Tip hat to who?\n");
	return 1;
    }

    actor("You tip your "+short()+" to",oblist,".");
    target(" tips " + HIS_HER(TP) + " "+short()+" to you.", oblist);
    all2act(" tips " + HIS_HER(TP) + " "+short()+" to", oblist,".");
    return 1;
 
}
