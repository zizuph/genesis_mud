inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    string *arr;
    int n;

    set_name("cloak");

    arr = ({"tattered",10, "smelly",12, "patched",12, "stitched",13,
            "grey",16, "thick",17, "oversized",18, "coarse",17,
            "padded",19, "plated",19, "chain",19, "billowey",19});

    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n])) set_adj(arr[n]);
    set_long("This "+short()+ "looks like it belonged to a pirate.\n");
    set_ac(arr[n+1]);
    set_am( ({-2, 1, 1}) );
    set_at(A_ROBE);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
