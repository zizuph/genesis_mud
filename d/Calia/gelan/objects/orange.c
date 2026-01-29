/* A large orange for the grocery shop in Gelan 
 */

#include "/d/Calia/glykron/palace/specials/orange_task.h"
inherit "/d/Calia/std/fruit";

void
create_fruit()
{
   set_name("orange");
   add_name(ORANGE_NAME);
   set_short("big orange");
   set_adj("big");
   set_long("A big juicy orange.\n");
   set_fruit_amount(2);
   set_mana_add(0);
   set_hp_add(10);
   set_fatigue_add(4);
}

