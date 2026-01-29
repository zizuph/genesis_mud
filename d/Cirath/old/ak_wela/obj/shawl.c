/* head_chn: Bug shell headware */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("shawl");
    set_short("cloth shawl");
    set_long("This cloth shawl can be tied around the head to keep "+
             "the hair from falling into your eyes. It doesn't look "+
             "it offers much protection though.\n");
    set_adj("cloth");
    set_ac(10);
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 700);
}
