/*
 *   strim.c
 * 
 * A healing herb.
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
    set_name("straw");
    set_adj("thin");
    add_adj("dark-brown");
    set_herb_name("strim");
    set_short("thin dark-brown straw");
    set_pname(({"straws", "herbs"}));
    set_pshort("thin dark-brown straws");
    set_unid_long("This is a thin dark-brown straw. By looking at it you "+
      "quickly come up with the conclusion that it grows in damp and moister "+
      "areas.\n");
    set_id_long("This thin dark-brown straw is called Strim. It grows in damp "+
      "and moister areas and is widely known for its healing effect when chewed.\n");
    set_id_diff(30);
    set_find_diff(5);
    set_effect(HERB_HEALING, "hp", 25);
    set_ingest_verb("chew");
    set_herb_value(750);
    set_decay_time(3000);
}
 
string query_recover() { return MASTER + ":" + query_herb_recover(); }
void init_recover(string arg) { init_herb_recover(arg); }
