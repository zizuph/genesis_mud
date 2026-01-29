inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* A very poisonous herb , Sarr */

void
create_herb()
{
    set_name("berry");
    add_adj("purple");
    add_adj("large");
    set_short("large purple berry");
    set_id_long("This berry is very large in size, about 3 centimeters "+
    "in diameter. It is a deep purple color. It is said to grow only "+
    "in the dark, wet places such as a bog or swamp. It is known "+
    "as mindleech, as it has the power to drain the power out of "+
    "the minds of wizards and sages.\n");

    set_unid_long("This is a very large berry, about 3 centimeters "+
    "in diameter. It is a deep purple color.\n");

    set_herb_name("mindleech");
    set_amount(3);
    set_decay_time(1200);
    set_id_diff(35);
    set_find_diff(5);
    set_herb_value(15);
    set_ingest_verb("eat");
    set_effect(HERB_HEALING,"mana",-500);
}
