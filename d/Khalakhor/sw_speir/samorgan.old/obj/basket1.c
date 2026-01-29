/**********************************************************************
 * - basket1.c                                                      - *
 * -                                                                - *
 * - Created by Damaris@Genesis 04/2006                             - *
 **********************************************************************/

inherit "/std/receptacle";
inherit "/lib/keep";
#include <stdproperties.h>

void
create_receptacle()
{
	set_name("basket");
	add_adj(({"wicker"}));
	set_short("wicker basket");
	set_long("This basket is made from wicker reeds that have been "+
	"woven using a special technique known as a five by five, which "+
	"is simply five wicker reeds placed tightly together crossing "+
	"five reeds. The weave adds a distinctive touch to form a sturdy "+
	"and yet a quite decorative basket. It has a sturdy lid that "+
	"displays the crest of a boar's head. ");
	add_item(({"crest", "boar crest", "boar's head", "lid", "basket lid"}),
	"The lid has a crest displayed that is made from darkened "+
	"wicker reeds woven in the shape of a boar's head.\n");
	
	set_keep(1);
	add_prop(CONT_I_RIGID, 1);
	add_prop(CONT_I_WEIGHT, 1000);
	add_prop(CONT_I_MAX_WEIGHT, 25000);
	add_prop(CONT_I_VOLUME, 1000);
	add_prop(CONT_I_MAX_VOLUME, 11000);
	add_prop(OBJ_I_VALUE, 450);
}
