inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <formulas.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_weapon()
{
   set_name("pin");
   set_pname(({"pins","rolling pins"}));
   set_short("rolling pin");
   set_pshort("rolling pins");
   set_adj("rolling");
   set_long("A common rolling pin scaled down to size for a hobbit.\n");
    set_default_weapon( 
       8,
       5,
       W_CLUB,
       W_BLUDGEON,
       W_NONE,                 
       0);           
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 30);
   add_prop(OBJ_I_VALUE, 10);
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
