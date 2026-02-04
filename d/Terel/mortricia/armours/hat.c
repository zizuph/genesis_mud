/*
   A pointy black hat, suitable for a witch. Mortricia 920720
 */

inherit "/std/armour";
#include "/sys/wa_types.h"

create_armour()
{
    set_name("hat");
    set_short("black hat");
    set_adj(({"pointed", "black"}));
    set_long("It is a pointed black hat, usually worn by witches.\n");

    set_default_armour(5, A_HEAD, 0, 0);
}
