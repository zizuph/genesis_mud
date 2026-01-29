inherit "std/object";

#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"


/*
 * Function name: create_object
 * Description:   The standard create
 */
void
create_object()
{
    set_name("paper");
    set_adj("ragged");
    add_name("_ragged_paper_");
     set_short("ragged paper");
    set_long("This is a ragged old piece of paper, looking as if it were "+
    "once marked on, but is definitely no longer readable. "+
    "You should probably throw it away.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_M_NO_SELL,1);

}
