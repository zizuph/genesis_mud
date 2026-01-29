inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("dagger");
    set_short("bone dagger");
    set_long ("An interesting looking dagger, it is long and "
	+"thin, with no sharpened edge that you can see.  It "
	+"ends in a very sharp point that looks like it was "
	+"meant to pierce flesh.\n");
    set_adj  ("bone");

    set_hit(18);
    set_pen(25);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 338);
    add_prop(OBJ_I_VOLUME, 65);
}


