/*
 *	/d/Genesis/start/human/obj/pool.c
 *
 *	A pool of water.
 *
 *	Styles  Nov 2008.
 *
 * 
 * 
 * 
 * 
 * 
 * 
 */
#pragma strict_types

inherit "/std/container.c";


#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <subloc.h>
#include <ss_types.h>


// Constructor.
public void
create_container()
{
    set_name("unconfigured pool");

    set_long("This is a big pool.\n");
    add_prop(CONT_I_IN,				1);
    add_prop(CONT_I_RIGID,			1);
    add_prop(CONT_I_TRANSP,			1);
    add_prop(CONT_I_WEIGHT,			2000000);
    add_prop(CONT_I_VOLUME,			2000000);
    add_prop(CONT_I_MAX_WEIGHT,		3000000);
    add_prop(CONT_I_MAX_VOLUME,		3000000);
    add_prop(OBJ_I_VALUE,			0);
	add_prop(OBJ_M_NO_GET, "You really can not get the pool.\n");
	add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);


}


// Keep the player out of the pool
public int
prevent_enter(object obj)
{
    if (IS_PLAYER_OBJECT(obj))
    {
        write("You really shouldn't soil the water.\n");
        return 1;
    }
    return 0;
}



public void
enter_inv(object ob, object from)
{
	::enter_inv(ob, from);

	if (ob->query_prop(OBJ_I_HAS_FIRE))
	{
		ob->extinguish_me();
	}
}





/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (this_object()->query_prop(CONT_I_ATTACH))
    {
        if (sizeof(obarr) > 0)
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
				(sizeof(obarr) > 1 ? " are" : " is") + 
				" on the " +
				this_object()->short() + ".\n");
        else
            for_obj->catch_tell("There is nothing on the " + 
				this_object()->short() + ".\n");
    }
    else if (sizeof(obarr) > 0)
        for_obj->catch_tell("The " + this_object()->short() +
			" also contains " +  COMPOSITE_DEAD(obarr) + ".\n");

    else
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " contains nothing but water.\n");
}