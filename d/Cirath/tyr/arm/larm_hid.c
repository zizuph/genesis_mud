/* larm_hid: A hide sleeve for the left arm. */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("sleeve");
    set_short("hide sleeve");
    set_long("A single sleeve made of two cylinders of hide, linked at "+
             "elbow with some more flexible leather.\n");
    set_adj("hide");

    set_ac(20);
    set_am(({ -4, 1, 2}));
    set_at(A_L_ARM);

    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 900);
}
