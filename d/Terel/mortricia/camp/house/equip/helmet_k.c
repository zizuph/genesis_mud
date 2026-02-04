#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("crown");
    set_short("golden crown");
    set_long("A golden crown. Suitable for kings and alike.\n");
    set_adj("golden");

    set_default_armour(25, A_HEAD, 0, 0);
    set_am(({ 1, 1, -2}));
}
