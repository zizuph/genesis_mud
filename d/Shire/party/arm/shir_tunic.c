inherit "/std/armour";

#include <wa_types.h>
#include "/d/Shire/common/defs.h"

void
create_armour()
{
    set_name("tunic");
    set_short("well-kept yellow tunic");
    set_long("A well-kept tunic of yellow colour.  "+
      "This tunic looks like it would keep you warm and protect you "+
      "well from the elements.\n");
    add_adj(({"yellow","well_kept"}));

    set_at(A_BODY);
    set_ac(8);

    add_prop(OBJ_I_WEIGHT,600);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE, 100);
}
