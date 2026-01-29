/* A crucible, for the Akram's Dagger Quest */
#pragma save_binary
#pragma strict_types

inherit "/std/container";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

public string Name = "";

public void
create_container(void)
{
    set_short("crucible");
    set_name("crucible");
    add_name("_union_crucible");
    set_adj(({"union", "porcelain", "ceramic", "greyish-white"}));
    set_long("This is a crucible made of a high-quality "+
	"ceramic that will withstand extreme heat. It "+
	"is greyish-white in colour.\n");

    add_item(({ "base", "bottom", "mark", "marking" }),
	"It is marked with a dark blue flame rising from "+
	"a black sphere.\n");    

    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME,  300);
    add_prop(CONT_I_MAX_WEIGHT,  10000);
    add_prop(CONT_I_MAX_VOLUME,  10000);
}

/*
 * Function name: test_it
 * Description  : Test for presence of all desired objects.
 * Returns      : 1-All five objects are present.
 *                0-Missing objects still.	 
 */
public int
test_it(void)
{
    return (sizeof(all_inventory()) == 5);
}

/*
 * Function name:  name_it
 * Description  :  put the player name on the crucible
 * Arguments    :  string arg -- whatever npc gives
 * Returns      :  1 on success, 0 on failure
 */
public int
name_it(string arg)
{
    if (!strlen(arg))
	return 0;

    Name = arg; 
    add_name(arg);     
    return 1;
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
    int reject;

    //Not a valid crucible component.
    if (!entering->id("_crucible_component"))
    {
	write("The "+ entering->short() +" does not belong in "+
	    "the "+ short() +".\n");
	return 1;
    }

    // Dont want more than one.
    if (entering->id("charcoal") && present("charcoal"))
	reject++;
    else if (entering->id("sphere") && present("dust"))
	reject++;
    else if (entering->id("dust") && present("dust"))
	reject++;
    else if (entering->id("strangleweed") && present("strangleweed"))
	reject++;
    else if (entering->id("glass") && present("glass"))
	reject++;
    else if (entering->id("ukku") && present("ukku"))
	reject++;

    if (!reject)
	return 0;

    write("There is "+ entering->short() +" in the "+
	short() +" already.\n");

    return 1;
}
