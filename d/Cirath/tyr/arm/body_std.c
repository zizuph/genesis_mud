/* body_std: Studded leather armor */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("vest");
    set_short("studded leather vest");
    set_long("Made of hardened leather with pieces of stone and chitin "+
             "sewn in for good measure, studded leather is a good "+
             "compromise between cost and protection.\n");
    set_adj("studded");
    add_adj("leather");

    set_ac(25);
    set_am(({ 0, -2, 2}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 5625);
    add_prop(OBJ_I_VOLUME, 2812);
}
