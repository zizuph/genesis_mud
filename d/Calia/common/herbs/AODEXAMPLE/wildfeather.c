/*
 *   wildfeather.c
 * 
 * A fatigue regaining herb.
 *
 * Baldacin@Genesis, Sep 2003
 */
 
inherit "/w/leia/InProgress/stdChanges/leia_herb";
 
#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

void
create_herb()
{
    set_name("flower");
    set_adj("yellow");
    set_herb_name("wildfeather");
    set_short("yellow flower");
    set_pname(({"flowers", "herbs"}));
    set_pshort("yellow flowers");
    set_unid_long("A small yellow flower, it looks edible.\n");
    set_id_long("This small yellow flower is known as a "+
      "Wildfeather, used by weary travellers to regain some "+
      "strength. It looks edible.\n");
    set_id_diff(30);
    set_find_diff(4);
    set_effect(HERB_HEALING, "fatigue", 20);
    set_ingest_verb("eat");
    set_herb_value(500);
    set_decay_time(3000);
}
 
string query_recover() { return MASTER + ":" + query_herb_recover(); }
void init_recover(string arg) { init_herb_recover(arg); }
