inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Cirath/defs.h"

void create_armour()
{
    set_name("pants");
    set_short("pair of heavy canvas pants");
    set_long("These pants are long and loose fitting, made of very " +
             "thick canvas. Along the waist is canvas cord strung through " +
             "loops used to hold them on the wearer.\n");
    set_adj("heavy");
    set_adj("canvas");
    set_ac(5);
    set_at(A_LEGS);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 1100);
}
