/* 	this is an object of the 2nd floor of the crystalline palace

    coder(s):   Glykron

    history:     1. 5.93    created                         Glykron

    purpose:    to allow the guild quest to be solved
    objects:    none

    quests:     given to guildmaster to solve the guild quest
    special:    cannot be picked up without code

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

string
my_long()
{
    return "This is a perfectly spherical crystalline orb.\n" +
	(query_prop(OBJ_M_NO_GET) ?
	    "It is sitting on a little wooden table.\n" :
	    "");
}

void
create_object()
{
    if (!IS_CLONE)
	return;

    set_name( ({ "orb", "Calia_orb" }) );
    set_long("@@my_long");
    set_adj("crystalline");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET, "The orb will not move.\n");
}