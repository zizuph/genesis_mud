inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("pudding");
    set_adj("gnomish");
    set_long("No wonder gnomes are so short.  This stuff tastes awful." +
	"  Filling, but\nonly an inventor could ignore taste like this.\n");
    set_short("bowl of pudding");
    set_pshort("bowls of pudding");
    set_amount(65);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 300);
}

