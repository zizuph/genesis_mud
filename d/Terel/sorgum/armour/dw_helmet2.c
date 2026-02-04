/*
 * Tomb dweller helmet: medium model
 *
 * based on code from the legion of darkness
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name("helmet");
     set_short("steel helmet");
     set_long("Its a shiny steel helmet used by tomb dwellers.\n");
     set_adj("steel");

     set_default_armour(30, A_HEAD, 0, 0);
}
     
