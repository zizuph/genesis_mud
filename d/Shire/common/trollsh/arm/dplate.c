/*
 * Armour for champion Trolls
 * Finwe, November 2004
 */
inherit "/lib/keep";
inherit "/std/armour";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

mapping resistance = ([]);
object wearer;

nomask void create_armour()
{
    set_name( ({"armour", "platemail", "plate"}) );
    set_short("dull steel platemail");
    set_adj( ({ "dull" , "steel"}) );
    set_long("@@my_long@@");
    set_ac( 47 );
    set_at( A_BODY | A_ARMS);
    set_am( ({ 3, 3, 3}) );
    set_af( this_object() );

    add_prop(OBJ_I_WEIGHT, 30000); /* 25 kg and steel*/
    add_prop(OBJ_I_VALUE,  2700); 
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(MAGIC_AM_MAGIC, ({ 55, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
	({
	   "This " + short() + " looks like it will protect your body. \n", 1,
	   "It's an ancient armour and enhanced to protect you against " +
            "dark magics. \n",20,
	   "It protects you against elemental magics that can destroy you.\n",50
	}) );

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    resistance = ([ MAGIC_I_RES_FIRE : 35,
		    MAGIC_I_RES_COLD : 40,
		    MAGIC_I_RES_MAGIC : 30,
		    MAGIC_I_RES_DEATH : 20,
		    MAGIC_I_RES_LIGHT : 29 ]);
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
	"This is a " + short() + ". It was forged by the men of Numenor and brought to Middle-earth by the Dunedain. It is made of steel and protects the body and arms. The armour looks like it was polished at one time, now it's dull with scratches and knicks in the surface.\n";
}
