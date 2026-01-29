inherit "std/object";

#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

int questnr;
/* Prototypes */

/*
 * Function name: create_object
 * Description:   The standard create
 */
void
create_object()
{
    set_name("locket");
    set_adj("shiny");
    add_name("_orc_locket_");
     set_short("orc locket");
     set_long("This locket is shiny and clean, you could hardly expect "+
     "it to have come from an orc. It positively sparkles in "+
     "the light. The picture drawn on the front shows a beautiful human "+
     "woman, backlit by a rising moon.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_M_NO_BUY,"The locket is not for sale.");

}

