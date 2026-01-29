/*
 * Base file for Bree Perfumes
 * Not sure who coded this, but converted over
 * -- Finwe October 2005
 *
 * Palmer Aug-1-2006
 *    Remove Kalad stank.
 */

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Shire/sys/defs.h"

#define PERFUME_CHARGES     5
#define LIVE_I_DIRTY     "_live_i_dirty"

int charges;			    // Number of charges.
string perfume_name;		// Name of perfume.
string perfume_name_oth;    // Name given to others.
string perfume_file;		// File of perfume effect.

void set_charges(int ch)
{
    charges = ch;
}

varargs void 
set_perfume_name(string name, string oth_name = 0) 
{
    perfume_name = name;
    if (stringp(oth_name))
        perfume_name_oth = oth_name;
    else
        perfume_name_oth = "expensive-smelling perfume";
}

void set_perfume_file(string file)
{
    perfume_file = file;
}

nomask void
create_object()
{
    FIXEUID;
    this_object()->create_perfume();
    if (!charges)
        charges = PERFUME_CHARGES;
}

void
init()
{
    ::init();
    add_action("do_dabble","dabble");    
}

int
do_dabble(string str)
{
    mixed what;
    int i;
    object *stinks = deep_inventory(TP);
    
    // Get rid of Kalad stank:
    for (i = 0; i < sizeof(stinks); i++)
        if (stinks[i]->id("dirty"))
            stinks[i]->remove_object();
    TP->add_prop(LIVE_I_DIRTY, 0);

    if (!strlen(str) ||
	!parse_command(str, all_inventory(TP), "[the] %i [on] [me]", what))
	return notify_fail("Dabble what?\n" +
			   "Perhaps: dabble <type of cologne>?\n");
    
    what = NORMAL_ACCESS(what, 0, 0);
    
    if (sizeof(what) > 1)
	return notify_fail("Dabble all that at once!?!\n");
    if (sizeof(what) == 0)
	return notify_fail("Eh.. What'erm, hmm.?? What'ya say?\n");
    
    return what[0]->dabble_me(str);
}

int
dabble_me(string str)
{
    object perfume;

    if (charges <= 0)
	return notify_fail("Alas! The bottle seems to be empty.\n");

    write("You liberally dabble on your " + perfume_name + ".\n");
    say(QCTNAME(TP)+ " dabbles on some " + perfume_name_oth + ".\n");

    perfume = clone_object(perfume_file);
    perfume->move(TP);

    charges --;
    return 1;
}
