// Some boring ashes
//        -Ilyian May 1995

inherit "/std/object";

#include "/d/Avenir/common/common.h"
#include "/sys/stdproperties.h"

void remove_ashes();

create_object()
{
    set_name(({"ashes", "pile" }));
    set_pname(({"piles"}));
    set_short("small pile of grey ashes");
    set_pshort("small piles of grey ashes");
    set_adj(({"grey","small"}));
    set_long(
          "This is a small pile of greyish ashes, which are still somewhat "+
          "warm. It seems something was burnt here recently.\n");

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VALUE, 1);

    set_alarm(900.0, 0.0, remove_ashes);
}

void remove_ashes()
{
   tell_room(ENV(TO),"The pile of grey ashes blows away, scattering "
                    +"itself upon the air.\n");
   remove_object();
}

