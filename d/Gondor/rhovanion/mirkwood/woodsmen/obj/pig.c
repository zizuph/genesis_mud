#include <stdproperties.h>

inherit "/std/food";

void
create_food() 
{
    set_name(({ "pig", "roast pig", "roast" }));
    set_pname(({ "pigs", "roast pigs", "roasts" }));
    set_short("roast pig");
    set_pshort("roast pigs");
    set_long("This is a suculent roast pig, undoubtedly " +
        "caught by the woodsmen of Mirkwood forest who " +
        "hunt wild boar. This serving should satisfy " +
        "even the hungriest person.\n");
    set_amount(575);
    add_prop(OBJ_I_WEIGHT,750);
    add_prop(OBJ_I_VOLUME,900);
    add_prop(OBJ_I_VALUE, 500);
}