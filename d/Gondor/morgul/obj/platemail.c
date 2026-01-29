/*
 * Last Modification: Olorin, July 1994
 *                    Olorin, 1-dec-1995: magic resistance fixed.
 *                    Olorin, 9-sep-1996: /lib/keep
 *                    Stern, 21-apr-2000: reduce chance of recovery (glow)
 *                    Chmee,  16.07.2002: some debugging and code
 *                        modernization
 *                    Toby, 13.02.2007  : Fixed weight to comply with rules
 *                                        and meddled with set_am as should
 *                                        be on all armours.
 *                    Toby, 15.06.2008  : New values for set_am
 *                                        old value ({ -1, 5, 2 }) != 0
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
    add_name( "_ithil_armour" );
    set_adj( ({ "plate", "black", "steel", "morgul", "high" }) );
    set_short( "black platemail" );
    set_pshort( "black platemails" );
    set_long(
        "A black platemail forged from high steel in the pits below "
      + "Barad-dur for the officers of the Morgul army. There is a "
      + "faint and unusual glimmer radiating from the armour. The "
      + "breastplate shows a picture of the Moon disfigured with a "
      + "ghastly face of death.\n" );
    set_default_armour( 50, A_BODY, ({ -3, 2, 1 }), this_object() );
    add_prop( OBJ_I_VALUE,F_VALUE_ARMOUR( 50 )+ random( 1000 )+ 500 );
    add_prop( OBJ_M_NO_BUY, 1 );
    add_prop( OBJ_I_WEIGHT, 8800 + random(200) );
    add_prop( OBJ_I_VOLUME, query_prop( OBJ_I_WEIGHT )/ 6 );
    add_prop( GONDOR_M_MORGUL_NO_SELL, 1 );
    add_prop( OBJ_S_WIZINFO, wizinfo );
    add_prop( OBJ_I_IS_MAGIC_ARMOUR, 1 );
    add_prop( MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );
    add_prop( MAGIC_AM_ID_INFO,
    ({
        "The black platemail seems to be magically strengthened. ", 1,
        "Some of this strength is put into the black metal itself " +
        "which is hammered really thin to reduce some weight, yet " +
        "being as strong as a regularly made platemail. ", 10,
        "Though it is enhanced the piercing blows will still penetrate " +
        "but the slashing and bludgeoning hits that would land on this " +
        "great armour would have a harder time penetrating through onto " +
        "the wearer. ", 30,
        "It is magically enhanced to protect the wearer against magical spells. ", 40,
        "More specifically the black platemail protects against the " +
        "dreaded death spells rumoured to be frequent in Mordor! ", 65,
        "\n", 1
    }) );
    add_prop( MAGIC_I_RES_DEATH, 100 );
    add_prop( MAGIC_I_RES_DEATH, ({ 33, 0 }) );
                                /*Let us reduce the number of glowing
                                 *platemails a bit.                       */
    if (random( 1 ))
    {
        set_may_not_recover();
    }
}

string wizinfo()
{
    return "A platemail forged in Sauron's stronghold. \n"+
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

mixed query_magic_protection( string prop, object for_what =
    previous_object() )
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

