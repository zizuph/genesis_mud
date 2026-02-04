/*
   A cloak, suitable for a witch. Mortricia 920720
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"

create_terel_armour()
{
    set_name("cloak");
    set_short("black cloak");
    set_adj(({"black"}));
    set_long("It is a black cloak, suitable for a witch.\n");

    set_default_armour(5, A_ROBE, 0, 0);
}
