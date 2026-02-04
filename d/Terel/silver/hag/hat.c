/*
   A pointy black hat, suitable for a witch. Mortricia 920720
   modify by Udana, to suit recoded Regata.
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"

create_terel_armour()
{
    set_name("hat");
	add_name("_regata_eq");
    set_short("black hat");
    set_adj(({"pointed", "black"}));
    set_long("It is a pointed black hat, usually worn by witches.\n");

    set_default_armour(5, A_HEAD, 0, 0);
}
