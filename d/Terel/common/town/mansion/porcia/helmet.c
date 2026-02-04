#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_terel_armour(){
set_name("helmet");
set_adj("silver");
set_short("shiny silver helmet");
set_long("This helmet is made of finely polished silver.\n");
set_ac(20);
set_at(A_HEAD);
set_am(({0, 0, 0}));
}
