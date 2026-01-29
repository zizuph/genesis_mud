/* head_chn: Bug shell headware */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("helmet");
    set_short("glossy chitin helmet");
    set_long("You do of course realise that wearing this might make "+
             "somebody mistake you for an ugly Thri-Kreen?\n");
    set_adj("chitin");
    add_adj("glossy");

    set_ac(30);
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 18000);
    add_prop(OBJ_I_VOLUME, 900);
}
