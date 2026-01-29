// file name:    /d/Avenir/common/herbs/chartess.c
// creator(s):   Casca 12/18/99
// last update:  Lilith 2/19/2004 updated desc
// purpose:      
// note:         
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"
#include <stdproperties.h>

create_herb()
{
    set_name("mushroom");
    add_name("herb");
    add_pname(({"mushrooms","herbs"}));
    set_short("wide black mushroom");
    set_herb_name("chartess");
    set_adj("wide");
    add_adj("black");
    set_id_long("This mushroom has a wide black hood with a short narrow "+
        "stalk and pale translucent gills. "+
        "Its called Chartess and is known to be an excellent source of "+
        "food, particularly for those who are too tired to prepare a meal.\n");
    set_unid_long("This mushroom has a wide black hood with a short narrow "+
        "stalk and pale translucent gills.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(2);
    set_effect(HERB_HEALING,"fatigue", 20);
    set_amount(40);
    set_decay_time(1200);
    set_herb_value(100);
    set_dryable();
}

