
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("hat");
    set_short("leather hat");
    set_long("This is a fine leather hat. From the smell of it, it "+
             "probably belonged to a fisherman some time.\n");
    set_adj("cloth");
    set_ac(13);
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 700);
}
