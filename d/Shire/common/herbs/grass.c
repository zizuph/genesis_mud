/*
 *  grass straw
 *             
 * Added pshort, Palmer Feb 13, 2003
 */

inherit "/std/herb.c";
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/sys/herb.h"

create_herb()
{
    set_adj(({"green"}));
    set_name("straw");
    add_name("straw");
  
    set_ingest_verb("smoke");
    set_short("green straw");
    set_pshort("green straws");
    set_herb_name("evendim grass");
    set_id_long("This green, brittle, straw is known for its magic " +
        "properties. It is said that the hobbits have used it to improve " +
        "their abilities to dodge a thrown stone.\n");
    set_unid_long("This green straw is quite brittle, and smells terrible.\n");
    set_herb_value(175);
    set_find_diff(2);
    set_id_diff(3);
    set_effect(HERB_ENHANCING,"dex",8);
    set_decay_time(500);
    set_dryable();

}
query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }

