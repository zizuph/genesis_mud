/*
 *   athly.c
 * 
 * A mana restoring herb.
 *
 * Baldacin@Genesis, Sep 2003
 */
 
inherit "/std/herb.c";
 
#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
 
void
create_herb()
{
    set_name("vine");
    set_adj("gnarled");
    add_adj("dark-green");
    set_herb_name("athly");
    set_short("gnarled dark-green vine");
    set_pname(({"vines", "herbs"}));
    set_pshort("gnarled dark-green vines");
    set_unid_long("A gnarled dark-green vine, it looks "+
      "quite chewable.\n");
    set_id_long("A gnarled dark-green vine, known as "+
      "Athly. It is said to give your mind a soothing "+
      "effect when chewed.\n");
    set_id_diff(45);
    set_find_diff(6);
    set_effect(HERB_HEALING, "mana", 60);
    set_ingest_verb("chew");
    set_herb_value(750);
    set_decay_time(4000);
}
 
string query_recover() { return MASTER + ":" + query_herb_recover(); }
void init_recover(string arg) { init_herb_recover(arg); }
