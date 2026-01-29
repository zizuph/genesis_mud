/* a pouch-belt
 * created by Lilith August 1996
 *
 * revisions: 07/08/98 - Lilith - updated to new wearable pack.
 * Mercade, 21 May 2004; removed decay routines.
 *
 * * Lucius Mar 2009: Re-written for new custom packs & sacks by Havec.
 */
#pragma strict_types

#include "havec.h"
inherit HAVEC_BASE;

public void
create_tailored(void)
{
    ::create_tailored();

    set_name(({"belt", "pouch-belt"}));
    set_short("belt of pouches");
    set_pshort("belts of pouches");
    set_long("A sturdy "+ fabric +" belt upon which voluminous pouches "+
        "are strung. The pouches are made of supple, waterproof "+
        "leather and look like they can hold quite a bit. There is "+
        "a small tag sewn to the belt.\n");

    set_slots(A_WAIST);
    set_looseness(8);
    set_layers(2);

    add_prop(CONT_I_WEIGHT, 300);        /* 0.3 kg */
    add_prop(CONT_I_VOLUME, 1500);       /* 1.5 L  */
    add_prop(CONT_I_MAX_WEIGHT, 60000);  /* 60.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 60000);  /* 60.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 110); // reduces weight by 10%
}
