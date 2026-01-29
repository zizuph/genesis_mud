/*
 * Marshmallow
 * Finwe, March 2003
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"

create_herb()
{
    set_name("marshmallow");
    add_name("root");
    set_adj(({"pale","thick"}));
    set_short("pale thick root");
    set_herb_name("marshmallow");
    set_id_long("This is the root of the common marshmallow plant. It is " +
        "well known for its healing properties, and cultivated for many " +
        "centuries. This plant has a green fleshy stem and broad egg shaped " +
        "leaves, both of which are covered with downy hairs. It has " +
        "five petalled, pale pink flowers which sit at the base of the " +
        "leaves. The plant grows best in damp soils and often found " +
        "along streams and rivers. \n");
    set_unid_long("This is a pale thick root.\n");
    set_ingest_verb("eat");
    set_id_diff(23);
    set_find_diff(1);
    set_effect(HERB_HEALING,"hp",5);
    set_decay_time(2500);
    set_herb_value(350);
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
