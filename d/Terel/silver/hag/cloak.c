/*
   A cloak, suitable for a witch. Mortricia 920720
   modify by Udana, to suit recoded Regata.
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"

create_terel_armour()
{
    set_name("cloak");
	add_name("_regata_eq");
    set_short("black cloak");
    set_adj(({"black"}));
    set_long("It is a black cloak, suitable for a witch.\n");

    set_default_armour(5, A_ROBE, 0, 0);
}
