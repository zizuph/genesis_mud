/* A coal sack, for the Akram's Dagger Quest */
/*
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 */
#pragma strict_types

inherit "/std/container";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>

public void
create_container()
{
    set_short("coal sack");
    set_name("sack");
    add_name(({"_smith_coal_sack"}));
    set_adj(({"coal", "sail-cloth"}));
    set_long("This is a sack made of once-white sail-cloth. It is is now "+
      "smudged with dark streaks from coal.\n");

    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 300);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
}

/*
 * Function name: test_it
 * Description  : Test for presence of all desired objects.
 * Returns      : 1-All objects are present.
 *                0-Missing objects still.	 
 */
public int
test_it()
{
    return (sizeof(all_inventory()) >= 7);
}

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object entering)
{
    //Not a valid object.
    if (!entering->id("_avenir_coal"))
    {
	write("The " + entering->short()+ " does not belong in "+
	    "the "+ short() +".\n");
	return 1;
    }

    if (sizeof(all_inventory(this_object())) > 6)
    {   //I'm full, lets let player know.
	write("The "+ short() +" is full.\n");
	return 1;
    }
    return 0;
}
