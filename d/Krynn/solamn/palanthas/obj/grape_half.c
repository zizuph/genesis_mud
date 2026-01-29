/* 
 * Palanthas food by Mortis 09.2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "../local.h";

public void
create_food()
{
    set_amount(30);
    set_name("half");
    set_pname("halves");
	set_adj("grapefruit");
    set_short("grapefruit half");
    set_pshort("grapefruit halves");
    set_long("A large, orange-yellow half of a grapefruit freshly cut "
	+ "and served in white paper wrapped around its bottom forming a "
	+ "bowl to keep grapefruit juices from spilling over and dripping "
	+ "onto your fingers.\n");
}

public void
special_effect(int numofdrinks)
{
    write("You scrunch your face as you take your first bite of the sour, "
	+ "though mildly sweet grapefuit.\n");
	tell_room(E(TP), QCTNAME(TP)+ "'s eyes and face scrunches up as "
	+ PRONOUN(TP) + " takes " + HIS(TP) + " first bite of a grapefruit "
	    + "half.\n", ({TO, TP}));

}
