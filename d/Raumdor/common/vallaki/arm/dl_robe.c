inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_armour()
{
    ::create_armour();
    set_name("robe");
    set_short("black-red robe of Drakmere");
    set_adj("black-red");
    add_adj("drakmere");
    set_long("This is the holy robe of Drakmere, worn only by the lord "+
        "himself. It is made of the finest silk and satin you have ever seen. "+
        "It has many intricate decorations. The insigina of Drakmere is etched "+
        "on the back, with a small golden cross etched in the center.\n");
    set_ac(15);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 450);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 700);
}
