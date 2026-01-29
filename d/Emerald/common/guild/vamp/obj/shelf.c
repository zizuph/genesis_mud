/*
 * /d/Emerald/mist_tower/obj/shelf.c
 *
 * A shelf used in a storage facility in the Vampire Guild.
 *
 * Copyright (c) ?? 1998 ?? by Shiva
 *
 * Revision history:
 *     10-3-00: (Gorboth) - Altered naming functions to allow for
 *                          more intuitive interaction with the shelves
 *                          and the room that clones them for mortals
 */
inherit "/std/container";

#include <stdproperties.h>
#include <files.h>
#include <language.h>

static string position;

void
create_container()
{
    set_name("shelf");
    remove_pname("shelves");
//  add_adj("set of");
//  set_short("set of shelves");
//  set_pshort("sets of shelves");

    set_long("A set of sturdy, wooden shelves, which is fastened " +
        "securely to the wall.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_WEIGHT, 300000);
    add_prop(CONT_I_VOLUME, 120000);
    add_prop(CONT_I_HEIGHT, 220);
    add_prop(CONT_I_MAX_WEIGHT, 1400000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}

void
set_position(string which)
{
    position = which;
    add_adj(which);
}

public mixed
unique_item(object ob)
{
    if (ob->query_prop(HEAP_I_IS))
    {
        // Deal with heaps all together
	return -1;
    }

    return ob->short();
}

void
show_objects(object for_obj, object *obarr)
{
    mixed *sorted;
    int i, j, num;
    string desc;

    sorted = unique_array(obarr, unique_item);

    for (i = 0; i < sizeof(sorted); i++)
    {
        // heaps are handled separately
	if (sorted[i][0]->query_prop(HEAP_I_IS))
	{
	    for (j = 0; j < sizeof(sorted[i]); j++)
	    {
		num = sorted[i][j]->num_heap();
		desc = ((num == 1) ? sorted[i][j]->singular_short() :
                                     sorted[i][j]->plural_short());
		for_obj->catch_tell(sprintf("%3d %s\n", num, desc));
	    }

	    continue;
	}

        num = sizeof(sorted[i]);

        if (num > 1)
	{
            desc = sorted[i][0]->plural_short();

            if (!strlen(desc))
	    {
                desc = LANG_PSENT(sorted[i][0]->short());
	    }
	}
        else
	{
            desc = sorted[i][0]->short();
	}

        /* Should do some extra checks for heaps */
        for_obj->catch_tell(sprintf("%3d %s\n", num, desc));
    }

    write("\n");
}

void
describe_contents(object for_obj, object *obarr)
{
    object *armours, *weapons, *other;


    if (!sizeof(obarr))
    {
        for_obj->catch_tell("There is nothing on the shelves.\n");
        return;
    }

    for_obj->catch_tell("========================================" +
                        "=======================================\n");

    /* Would be nice to be able to use unique_array() here */
    weapons = filter(obarr, 
        &operator(==)(WEAPON_OBJECT) @ &function_exists("create_object"));

    if (sizeof(weapons))
    {
        show_objects(for_obj, weapons);
        obarr -= weapons;
    }

    armours = filter(obarr,
        &operator(==)(ARMOUR_OBJECT) @ &function_exists("create_object"));

    if (sizeof(armours))
    {
        show_objects(for_obj, armours);
    }

    other = obarr - armours;

    if (sizeof(other))
    {
        show_objects(for_obj, other);
    }
}

#if SORT_CONTENTS
int
sort_contents_by_short(object a, object b)
{
    string ashort = a->short();
    string bshort = b->short();

    return ((ashort < bshort) ? -1 : ((ashort == bshort) ? 0 : 1));
}
#endif SORT_CONTENTS

int
list_shelf_contents()
{
    object *obs;
    int i;

    write(capitalize(position) + " shelf\n" +
         "==============\n");

    obs = all_inventory(this_object());

    if (!sizeof(obs))
    {
        write("\nEmpty\n\n");
        return 1;
    }

    write("* Recoverable\n+ Non-empty container\n\n");

#if SORT_CONTENTS
    obs = sort_array(obs, sort_contents_by_short);
#endif SORT_CONTENTS

    for (i = 0; i < sizeof(obs); i++)
    {
        write(sprintf("%1s %1s %s\n", 
            ((obs[i]->check_recoverable() && !obs[i]->may_not_recover()) ? "*" : ""),
            ((obs[i]->query_prop(CONT_I_IN) && sizeof(all_inventory(obs[i]))) ? "+" : ""),
            obs[i]->short()));
    }

    write("\n");
    
    return 1;
}
