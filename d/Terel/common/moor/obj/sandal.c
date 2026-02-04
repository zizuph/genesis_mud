#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name(({"sandal", "sandle"}));
     set_short("old sandal");
     set_long("An old leather sandal with broken leather straps\n");
     set_adj(({"old"}));

     set_default_armour(5, A_R_FOOT, 0, 0);
}
