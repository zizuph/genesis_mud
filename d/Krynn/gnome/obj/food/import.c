inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(110);
    set_alco_amount(33);
    set_name("beer");
    add_name("glass");
    set_adj("imported");
    set_adj("Hobbiton");
    set_short("glass of imported Hobbiton beer");
    set_pshort("glasses of imported Hobbiton beer");
    set_long("A glass of Hobbiton beer, imported to this world at" +
	" great expense.  Hobbits\nbrew a REAL beer, even if their" +
	" opinions of gnomes are questionable...\m");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
