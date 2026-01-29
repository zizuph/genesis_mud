inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("beer");
    add_name("glass");
    set_adj("gnomish");
    set_short("glass of gnomish beer");
    set_pshort("glasses of gnomish beer");
    set_long("A glass of gnomish brew. Apparently the product of" +
	     " some invention, because their dwarvish cousins make a" +
	     " much better beer...\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
