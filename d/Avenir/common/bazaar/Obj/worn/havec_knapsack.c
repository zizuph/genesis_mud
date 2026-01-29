/* a scrip
 *   worn over the shoulder
 * created by Lilith Oct 1996
 * Lilith Aug 1997: added magical components prop
 *
 * revisions: 07/08/98 - Lilith - updated to new wearable pack.
 * Mercade, 21 May 2004; removed decay routines.
 * Lucius May 2007 - Fixed pshort description & removed redundant bits.
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

    set_name("knapsack");
    set_short(desc +" "+ fabric +" knapsack");
    set_pshort(desc +" "+ fabric +" knapsacks");

    set_long("This knapsack is made to be comfortable when carried for " +
        "long distances. It is favored by those who carry heavy loads "+
        "for long distances because it is worn across the back and "+
        "held in place by two study straps over each shoulder. "+
        "There is a small tag sewn into one of the straps.\n");

    set_slots(A_BACK);
    set_looseness(15);
    set_layers(2);

    add_prop(CONT_I_WEIGHT, 500);         /* 0.5 kg */
    add_prop(CONT_I_VOLUME, 500);         /* 0.5 L  */
    add_prop(CONT_I_MAX_WEIGHT, 100000);  /* 100.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 100000);  /* 100.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 150);  // reduces weight by 25%
}

