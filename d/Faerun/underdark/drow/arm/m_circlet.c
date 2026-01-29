/*
 *  faerun/underdark/upper/menzo/sorcere/arm/m_circlet.c
 *
 *  Mithril circlet in Underdark
 *
 *  Created by Midnight, 25-2-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

#define AC 15

inherit FAERUN_ARM_BASE;

void create_faerun_armour()
{
    set_name("circlet");
    set_adj( "braided" );
    set_adj( "mithril" );
    set_adj( "decorated" );
    set_long("This exquisite circlet is made out of several " +
             "interwoven thick mithril threads. Small decorative " +
             "mithril spiders are attached around the circlet. " +
             "Very thin threads of mithril has been spun into " +
             "a spiderweb, which hangs from the sides of the circlet " +
             "and down around the back. A large ruby shaped like a " +
             "flame is set in the front of the circlet\n");
    set_short("decorated braided mithril circlet");

    set_ac(AC + random(5));
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 2850);
}