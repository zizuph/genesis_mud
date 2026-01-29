/* A golden crown. ~mucalytic/hills/armour/gold_crown */

inherit "/std/armour";

#include "../defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_armour()
{
    set_name("crown");
    set_pname("crowns");
    set_adj("gold");
    set_long("A jewelled golden crown. It looks very expensive indeed.\n");

    set_ac(3);

    set_at(A_HEAD);

    set_likely_cond(1);
    set_likely_break(3);

    add_prop(OBJ_I_VALUE, 1500);

    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 3750);
}
