inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>


void
create_herb()
{
    set_name("root");
    add_adj("red");
    add_adj("yellow-spotted");
    set_short("red yellow-spotted root");
    set_id_long("This is a very valuable herb, known as flameroot. It "+
    "is hotter than even the hottest peppers. It is rather small in "+
    "size, slightly smaller than a clove of garlic, and is bright "+
    "red in color. It is dotted with yellow spots. It is said to give "+
    "people resistance against fire when eaten...for those who brave "+
    "its hot taste!\n");

    set_unid_long("This a small root, slightly smaller than a garlic, "+
    "and is bright red. It has some yellow spots on it.\n");

    set_herb_name("flameroot");
    set_amount(2);
    set_decay_time(600);
    set_id_diff(35);
    set_find_diff(9);
    set_herb_value(200);
    set_ingest_verb("eat");
    set_effect(HERB_ENHANCING,"fire",4);
}
