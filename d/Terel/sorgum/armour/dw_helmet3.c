/*
 * Tomb dweller helmet: good model
 *
 * based on code from the legion of darkness
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name("helmet");
     set_short("alloy helmet");
     set_long("Its a metal alloy helmet worn by tomb dwellers.\n");
     set_adj("alloy");

     set_default_armour(35, A_HEAD, 0, 0);
}
     
     
