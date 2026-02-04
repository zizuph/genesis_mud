/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

create_armour(){
set_name("robe");
set_adj("holy");
add_adj("white");
add_name("holy_cantor_robe");

set_long("It is a brilliant white robe, it emanates holiness.\n");

set_ac(30);
set_at(A_ROBE);
add_prop(MAGIC_AM_MAGIC, ({ "enchantments", 30 }));

}
