/*
 * Last Modification: Modified from the morgul platemail, Alto, August 2002
 *                    Olorin, July 1994
 *                    Olorin, 1-dec-1995: magic resistance fixed.
 *                    Olorin, 9-sep-1996: /lib/keep
 *                    Stern, 21-apr-2000: reduce chance of recovery (glow)
 *                    Chmee,  16.07.2002: some debugging and code
 *                        modernization
 *                    Toby,  04-Oct-2007: Fixed random(1) -> random(2)
 */
#pragma strict_types
inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

string wizinfo();

void create_armour() 
{
    set_name( "platemail" );
    add_name( "mail" );
    set_adj( ({ "camouflaged", "steel" }) );
    set_short( "camouflaged platemail" );
    set_pshort( "camouflaged platemails" );
    set_long("This steel platemail resembles those crafted in the smithies "
      + "of Gondor, although there seems to be an almost elvish feeling to it "
      + "when worn. It has been painted in such a way to make it less obvious "
      + "in a forest setting.\n");
    set_default_armour( 50, A_BODY, ({ 0, 0, 0 }), this_object() );
    add_prop( OBJ_I_VALUE,F_VALUE_ARMOUR( 50 ) + random( 1000 )+ 500 );
    add_prop( OBJ_M_NO_BUY, 1 );
    add_prop( OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR( 50, A_BODY )+
        random( 2000 )- 1000 );
    add_prop( OBJ_I_VOLUME, query_prop( OBJ_I_WEIGHT )/ 6 );
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop( OBJ_S_WIZINFO, wizinfo );
    add_prop( OBJ_I_IS_MAGIC_ARMOUR, 1 );
    add_prop( MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );
    add_prop( MAGIC_AM_ID_INFO,
    ({
        "The camouflaged platemail seems to be magically strengthened.", 1,
        "The camouflaged platemail seems to be magically enhanced to protect "+
            "against magic spells. ", 25,
        "The camouflaged platemail protects against death spells. ", 50
    }) );
    add_prop( MAGIC_I_RES_DEATH, 100 );
    add_prop( MAGIC_I_RES_DEATH, ({ 33, 0 }) );
}

string wizinfo()
{
    return "A platemail forged of old in Gondor, when men and elves allied.\n"+
        "Magically strengthened against death spells. \n" +
        "MAGIC_AM_MAGIC    : " + query_prop(MAGIC_AM_MAGIC)[0] + "%, "
                               + query_prop(MAGIC_AM_MAGIC)[1] + "\n" +
        "MAGIC_I_RES_DEATH : 33%, additive.\n";
}

public mixed wear( object obj )
{
 object tp = environment( this_object() );

    if ((tp != this_player()) || (obj != this_object()))
    {
        return -1;
    }
    if (living( tp ))
    {
        tp->add_magic_effect( this_object() );
    }
    return 0;
}

public mixed remove( object obj )
{
 object tp = query_worn();

    if ((tp != this_player()) || (obj != this_object()))
    {
        return -1;
    }
    if (living(tp))
    {
        tp->remove_magic_effect( this_object() );
    }
    return 0;
}

mixed query_magic_protection( string prop, object for_what = previous_object() )
{
 object tp = query_worn();

    if (for_what == tp)
    {
        switch (prop)
        {
        case MAGIC_I_RES_DEATH:
            return ({ 33, 1 });
        }
    }
    return ::query_magic_protection( prop, for_what );
}

