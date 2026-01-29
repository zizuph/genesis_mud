inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* A very poisonous herb , Sarr */

void
create_herb()
{
    set_name("vine");
    add_adj("black");
    add_adj("red-pitted");
    set_short("black red-pitted vine");
    set_id_long("This small vine comes from the dark reaches of Raumdor. "+
    "It has many little pits filled with red ooze in it. It is not "+
    "very tasty at all, but surprisingly, not poisonous. The black "+
    "vine also has a few withered leaves on it.\n");

    set_unid_long("This small vine is black and has a few withered "+
    "leaves on it. Its length is covered with pits filled with strange "+
    "red ooze in it. It looks unhealthy.\n");

    set_herb_name("vinerot");
    set_amount(2);
    set_decay_time(600);
    set_id_diff(30);
    set_find_diff(5);
    set_herb_value(20);
    set_ingest_verb("eat");
    set_effect(HERB_HEALING,"fatigue",-500);
}
