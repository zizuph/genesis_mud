inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_armour()
{
    ::create_armour();
    set_name("cape");
    set_short("flowing blood red cape");
    set_adj("blood red");
    add_adj("flowing");
    set_long("This cape is made of fine heavy silk, it's deep crimson red "+
    "is rich and full of color..\n");
    set_ac(8);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 450);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 700);
}
