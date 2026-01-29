/*
 * Plain platemail
 * Last Modification: Palmer 9 - Dec - 2006
 *
 *
 */

#pragma strict_types
inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"


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
      + "Barad-dur for the officers of the Morgul army. You can see a "
      + "strange magical glimmer radiating from the armour. The "
      + "breastplate shows a picture of the Moon disfigured with a "
      + "ghastly face of death.\n" );
    set_default_armour( 30, A_BODY, ({ 0, 0, 0 }), this_object() );
    add_prop( OBJ_I_VALUE,F_VALUE_ARMOUR(30)+ random(100) );
    add_prop( OBJ_M_NO_BUY, 1 );
    add_prop( OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(30, A_BODY )+
        random( 2000 )- 1000 );
    add_prop( OBJ_I_VOLUME, query_prop( OBJ_I_WEIGHT )/ 6 );
    add_prop( GONDOR_M_MORGUL_NO_SELL, 1 );
}


