/*
   A stupid hat.
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"

create_terel_armour()
{
    set_name("hat");
    set_short("silly hat");
    set_adj("silly");
    set_long("It's a silly looking hat, used by jesters and the like.\n");

    set_default_armour(5, A_HEAD, 0, 0);
}
