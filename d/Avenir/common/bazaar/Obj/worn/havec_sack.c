/* a VERY LARGE bag
 * created by Lilith Oct 1996
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

    set_name(({"sack"}));
    set_short(desc +" "+ fabric +" sack");
    set_pshort(desc +" "+ fabric +" sacks");

    set_long("This is a rather unusual sack. Rather voluminous, it is "+
        "made of from a "+ fabric +" material that was crafted to be "+
	"extra strong and resistant to tearing. It is triple stitched "+
	"to a rawhide strap and is slung around the body and back, "+
	"wrapping around half your body. There is a tag of some sort "+
        "sewn onto the sack.\n");

    /* Not meant to be worn. */
    set_slots(A_TORSO | A_BACK);
    set_looseness(5);
    set_layers(5);

    add_prop(CONT_I_WEIGHT, 200);        /* 0.2 kg */
    add_prop(CONT_I_VOLUME, 2000);        /* 2.0 L  */
    add_prop(CONT_I_MAX_WEIGHT, 190000);  /* 190.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 190000);  /* 190.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 175);  /* reduces weight by 75% */
}
