#include "defs.h"
inherit BASE_ARMOUR;

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#include "recover"

mapping resistance;

CONSTRUCT_ARMOUR
{
    set_name( ({"armour", "fullplate", "platemail", "plate"}) );
    set_short("dwarven fullplate");
    set_adj( ({ "mitrhil", "dwarven", "shining" , "magical", "full" }) );
    set_long("@@my_long@@");
    set_ac(28);
    set_at( A_BODY | A_ARMS | A_LEGS );
    set_am( ({ 2, -1, 1}) );
    set_af( this_object() );

    add_prop(OBJ_I_WEIGHT, 12000); /* 12 kg and mithril! */
    add_prop(OBJ_I_VALUE,  10000); /* Expensive? Yes!	*/
    add_prop(OBJ_I_VOLUME,  5000);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment", 40, "spell-resistance"}));
    add_prop(MAGIC_AM_ID_INFO,
	({
	    "This seems like a mighty dwarven mithril full plate!\n", 1,
	    "It has been enchanted and is of mithril.\n", 20,
	    "It also protects against fire, cold, magic, death and light spells.\n", 40
	}) );
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_I_LIGHT, 1);

    resistance = ([ MAGIC_I_RES_FIRE : 40,
		    MAGIC_I_RES_COLD : 20,
		    MAGIC_I_RES_MAGIC : 15,
		    MAGIC_I_RES_DEATH : 15 ]);
}

/*
int *
query_slots()
{
    return ({ A_L_ARM, A_R_ARM, A_BODY, A_LEGS });
}
*/

int
query_magic_protection(mixed prop, object for_who)
{
    if (for_who == TO)
	return ::query_magic_protection(prop, for_who);
    else 
	return resistance[prop];
}

wear(object to)
{
    object tp=environment(to);
    tp->add_magic_effect(to);
}

remove(object to)
{
    object tp=query_worn();
    tp->remove_magic_effect(to);
}

string
wear_how(int loc)
{
    string pos;


    if(!query_worn() || query_worn()==this_player())
	pos = "your";
    else
	pos = query_worn()->query_possessive();

    if(loc==A_BODY)
	return " over "+pos+" body";
    else
	return ::wear_how(loc);
}

my_long()
{
    return
	"This seems to be a mighty good platemail made of mithril! "+
	"It is increadibly light when you think of it's large size, "+
	"so you bet this is one of the finest dwarven item ever made.\n";
}


/*
wear()
{
 
 
}
 
remove()
{
 
 
 
}
*/
