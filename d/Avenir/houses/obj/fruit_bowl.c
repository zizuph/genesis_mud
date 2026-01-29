/*
 * Fruit bowl for Avenir houses.
 *
 * Lilith, Feb 2022
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/container";

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

public void reset_container();

public void
create_container()
{
    string what = one_of_list(({"glass", "clay", "stone", "wood"}));

    set_name("bowl");
	set_adj(what);
	add_adj("fruit");
    set_short(what +" bowl@@full_str@@");
    set_long("It is a "+ what +" bowl.\n");

    add_prop(OBJ_I_VOLUME, 260);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VALUE, 26);

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 600);
    add_prop(CONT_I_MAX_WEIGHT, 200);
	
	seteuid(getuid());
	reset_container();
}

public string
full_str(void)
{
 
    if (!sizeof(all_inventory(TO)))
	return "";
    else 
	return " holding fruit";
}

public void
reset_container(void)
{
    int size;
    object obj;

    string fruit = one_of_list(({"pear","peach","cherry","blackberry","raspberry"}));

	size = 5 +random(10);
	while(size--)
	{
	    if (!catch(obj = clone_object(ZIGG + "food/"+fruit)))
	    {
            obj->move(this_object(), 1);
	    }
	}
}


public int
prevent_enter(object ob)
{
	
    if (ob->id("fruit"))
	{
	   return 0;
	}
    else 
    write("The "+ ob->short() +" does not belong in the "+ short() +".\n");
    return 1;
}

