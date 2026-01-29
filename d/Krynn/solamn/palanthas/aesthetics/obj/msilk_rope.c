/*
 * Silk rope sold at general eq store in Aesthetics
 * quarter of Palanthas.  A grapple can attach to it.
 * Holdable item that adds climb skill.
 *
 * Mortis 05.2006
 *
 */

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";

#include "../../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

int have_grapple = 0;
string recover_string = "no";
object holder;

void
create_object()
{
    set_name("rope");
    add_name("_20_meter_rope");
    set_adj("silk");
	add_adj("long");
	set_short("@@my_short");
    set_long("@@my_long");

    add_prop(OBJ_S_WIZINFO, "Adds three points of climb skill when held "
	+ "and three more with a grapple.\n");

    set_slots(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE,  576);

    set_keep(1);
    seteuid(getuid());
}

public int
rope_has_grapple()
{
   return have_grapple;
}

string
my_short()
{
	if (have_grapple == 1)
		return "long silk rope with grapple";
	
	return "long silk rope";
}

string
my_long()
{
	if (have_grapple == 1)
		return "This is a twenty meter length of slender, ultra-strong, grey "
		+ "silk rope with a grapple fastened to one end.  It is light and "
		+ "would be very helpful in climbing when held.\n";

	return "This is a twenty meter length of slender, ultra-strong, grey "
	+ "silk rope.  It is light and would be helpful in climbing when "
	+ "held.\n";
}

int
add_grapple()
{
	have_grapple = 1;
	recover_string = "yes";

	ITEM("grapple", "A small, iron grapple with four backward curving hooks "
	+ "has been secured to the end of the long silk rope.  You can "
	+ "<unfasten> it.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,   720);

	return 1;
}

int
remove_grapple()
{
	have_grapple = 0;
	recover_string = "no";

	remove_item("grapple");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE,  576);

	return 1;
}

void
recover_grapple(string arg)
{
	if (arg == "yes")
		add_grapple();
}

void
init()
{
	ADA("unfasten");
}

int
unfasten(string str)
{
	NF("What?\n");
	if (have_grapple == 0)
		return 0;

	NF("Unfasten?  Unfasten grapple from rope?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[iron] [my] [the] [a] 'grapple' [from] [long] [silk] [rope]"))
		return 0;

	NF("You must release the rope before you can unfasten its grapple.\n");
	if (TO->query_held())
		return 0;

	remove_grapple();
	clone_object(MONKS + "obj/mgrapple")->move(TP);
	write("You unfasten your grapple from your rope.\n");
	say(QCTNAME(TP) + " unfastens a grapple from " + HIS(TP) + " rope.\n");
	return 1;
}

public mixed
hold()
{
	if (have_grapple == 0)
	{
	    TP->set_skill_extra(SS_CLIMB, TP->query_skill_extra(SS_CLIMB) + 3);
		write("You feel better equipped for climbing now.\n");
	}

	else
	{
	    TP->set_skill_extra(SS_CLIMB, TP->query_skill_extra(SS_CLIMB) + 6);
		write("You feel much better equipped for climbing now.\n");
	}

    holder = TP;

    return 0;
}

public mixed
release()
{
	if (have_grapple == 0)
	    holder->set_skill_extra(SS_CLIMB, TP->query_skill_extra(SS_CLIMB) - 3);
	else
	    holder->set_skill_extra(SS_CLIMB, TP->query_skill_extra(SS_CLIMB) - 6);

    holder = 0;
	write("You no longer feel especially prepared for climbing now.\n");
    return 0;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    /* This needs to be called from leave_env() so that items are
     * released when they are dropped.
     */
    holdable_item_leave_env(env, to);
}


/*
 * Function name: appraise_object
 * Description:   This is called when someone appraises this item.
 *                We want to mask it to add a message telling the
 *                appraiser that the item can be held.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    write(holdable_item_usage_desc());
}

string
query_recover()
{
	return MASTER + ":" + recover_string;
}

void
init_recover(string arg)
{
    ::init_keep_recover(arg);
	recover_grapple(arg);
}
