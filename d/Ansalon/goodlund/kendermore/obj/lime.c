inherit "/std/food";
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

#define adjecs query_adjs()


#define ONE_OF(x)     ((x)[random(sizeof(x))])

string *adjs=({"juicy", "large", "green", "small"});

void
create_food()
{
    set_name("lime");
    set_pname("limes");
    add_name("fruit");
    add_pname("fruits");
    set_adj(ONE_OF(adjs));
    add_adj("green");
    set_long("This is a fine example of a lime fruit.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}
