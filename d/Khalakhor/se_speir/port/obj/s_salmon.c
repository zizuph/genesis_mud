#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("salmon");
    add_name("fish");
    set_adj("smoked");
    set_short("smoked salmon");
    set_long("The smoked salmon is a favorite. Carefully cut fillets " +
        "of tasty salmon hung to dry in a smokehouse over slowly " +
        "burning peat gives it a wonderful smokey flavour.\n");
    set_amount(220);
    mod_value(30);
    set_cooked();
}
