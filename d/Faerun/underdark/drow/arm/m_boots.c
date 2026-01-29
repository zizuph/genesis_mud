/*
 *  faerun/underdark/upper/menzo/sorcere/arm/m_boots.c
 *
 *  Sorcere master boots in Underdark
 *
 *  Created by Midnight, 21-2-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

#define AC 15

void create_faerun_armour()
{

    set_name("boots");
    set_adj( "decorated" );
    set_adj( "snake-skin" );
    set_short("pair of decorated snake-skin boots");
    set_pshort("pairs of decorated snake-skin boots");
    set_long("This pair of boots are made of glistening dark snakeskin, " +
             "and they feel cold to the touch and the material " +
             "moves lightly under the stroke of your hand, just " +
             "a living snake. The material is much like leather, " +
             "very supple and formfitting. A thin silvery chain " +
             "with small rubies twists around the snakeskin.\n");

    
    set_ac(AC + random(5));
    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT, 2800);
}