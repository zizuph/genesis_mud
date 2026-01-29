/*
 * Moderated the resistance provided.
 *
 * Arman - 01/03/2019
 */

#include "defs.h"

inherit BASE_ARMOUR;
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#include "recover"

mapping resistance = ([]);
object wearer;


CONSTRUCT_ARMOUR 
{
    set_name( ({"armour", "fullplate", "platemail", "plate"}) );
    set_short("black fullplate");
    set_adj( ({ "black" , "magical", "full", "alloy" }) );
    set_long("@@my_long@@");
    set_ac( 27 );
    set_at( A_BODY | A_ARMS | A_LEGS );
    set_am( ({ 0, 0, 0}) );
    set_af( this_object() );

    add_prop(OBJ_I_WEIGHT, 25000); /* 25 kg and black alloy! */
    add_prop(OBJ_I_VALUE,  4*12*12); /* 4 gold */
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
	({
	   "This seems like a mighty black fullplate.\n", 1,
	   "This armour resists fire, cold, magic, death and light spells.\n",20,
	   "In addition yields healing spells triggered by arcane magic.\n",50,
	   "The magic is evil though, it drains power from the "+
	   "wearer's experience.\n",90
	}) );

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    resistance = ([ MAGIC_I_RES_FIRE : 19,
		    MAGIC_I_RES_COLD : 35,
		    MAGIC_I_RES_MAGIC : 5,
		    MAGIC_I_RES_DEATH : 15,
		    MAGIC_I_RES_LIGHT : 24 ]);
    set_keep();
}


wear(object to)
{
    wearer = TP;
    wearer->add_magic_effect(TO);
}

remove(object to)
{
    wearer->remove_magic_effect(TO);
    wearer = 0;
}

int
query_magic_protection(mixed prop, object for_who)
{
    if (for_who == TO)
	return ::query_magic_protection(prop, for_who);
    else 
	return resistance[prop];
}


my_long()
{
    return
	"This is a black alloy metal fullplate, made by dwarves, but made "+
	"for bigger people. It covers the whole body, but still is very light. "+
	"The black metal shines in the light, twinkling and polished as it is.\n";
}
