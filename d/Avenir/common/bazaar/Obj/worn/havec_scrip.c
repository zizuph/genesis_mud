/* a scrip
 *   worn over the shoulder
 * created by Lilith Oct 1996
 * Lilith Aug 1997: added magical components prop
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

    set_name("scrip");
    set_short(desc +" "+ fabric +" scrip");
    set_pshort(desc +" "+ fabric +" scrips");

    set_long("This scrip is made to be comfortable when carried for " +
        "long distances. It is favored by pilgrims and explorers "+
        "alike because its strap is worn on one shoulder so that "+
        "it crosses the chest, causing the scrip itself to be carried "+
        "at waist-height and easily accessible. There is a small tag "+
        "sewn to the strap.\n");

    if (random(3))
	set_slots(A_L_SHOULDER | A_R_HIP);
    else
	set_slots(A_R_SHOULDER | A_L_HIP);

    set_looseness(15);
    set_layers(2);

    add_prop(CONT_I_WEIGHT, 500);        /* 0.5 kg */
    add_prop(CONT_I_VOLUME, 500);        /* 0.5 L  */
    add_prop(CONT_I_MAX_WEIGHT, 80000);  /* 80.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 80000);  /* 80.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 115); // reduces weight by 15%
}
