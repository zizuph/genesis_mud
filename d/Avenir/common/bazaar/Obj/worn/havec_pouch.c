/* a pouch
 * worn around the neck
 * created by Lilith Oct 1996
 * updated: Lilith Aug 1997: added CONT_I_HOLDS_COMPONENTS prop.
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

    set_name("pouch");
    set_short(desc +" "+ fabric +" pouch");
    set_pshort(desc +" "+ fabric +" pouches");

    set_long("A pouch made of "+ fabric +" material. It bears the stamp "+
        "of Havec Sackmaker of Sybarus, and is designed to be "+
        "worn around the neck.\n");

    set_slots(A_NECK);
    set_looseness(20);
    set_layers(1);

    add_prop(CONT_I_WEIGHT, 250);         /* 0.25 kg */
    add_prop(CONT_I_VOLUME, 500);         /* 0.5 L  */
    add_prop(CONT_I_MAX_WEIGHT, 10000);   /* 10.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 10000);   /* 10.0 L */
    add_prop(CONT_I_REDUCE_WEIGHT, 110);  // reduces weight by 10%
}
