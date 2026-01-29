/*
 * HOBJ + pantry1.c
 *
 * Varian - Feb 2020
 *
 */

#pragma strict_types
#pragma save_binary 

inherit "/std/receptacle";

#include <stdproperties.h>
#include <files.h>
#include "../defs.h"

private void
fill_pantry()
{
	seteuid(getuid());

    clone_object(ZIGG+"food/pear")->move(this_object(), 1);
    clone_object(ZIGG+"food/peach")->move(this_object(), 1);
    clone_object(ZIGG+"food/punch")->move(this_object(), 1);
    clone_object(ZIGG+"food/punch_cup")->move(this_object(), 1);
    clone_object(ZIGG+"food/punch_cup")->move(this_object(), 1);
    clone_object(BAZAAR+"Obj/food/crusty_bread")->move(this_object(), 1);
	
}
	
public void
create_receptacle()
{
    set_adj("corner");
    set_name("pantry");
    set_long("This pantry occupies the southwest corner of " +
        "the kitchen. It is a good place to store food and "+
        "drink.\n");

    add_prop(CONT_I_VOLUME, 81000);
    add_prop(CONT_I_WEIGHT, 4535);
    add_prop(CONT_I_MAX_VOLUME, 120000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_M_NO_GET, 1);

    set_no_show_composite(1);
	
    fill_pantry();
}