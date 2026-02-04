/*
   A belt
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"

create_terel_armour()
{
    set_name("belt");
    set_short("black belt");
    set_adj(({"black"}));
    set_long("It's a black belt.\n");

    set_default_armour(5, A_WAIST, 0, 0);
}
