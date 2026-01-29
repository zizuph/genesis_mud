/*
 *   streyroot.c
 * 
 * A poisonous herb.
 *
 * Baldacin@Genesis, Sep 2003
 */
 
inherit "/std/herb";
 
#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
 
void
create_herb()
{
    set_name("root");
    set_adj("thin");
    add_adj("reddish");
    set_herb_name("streyroot");
    set_short("thin reddish root");
    set_pname(({"roots", "herbs"}));
    set_pshort("thin reddish roots");
    set_unid_long("A thin reddish root, it looks quite chewable.\n");
    set_id_long("This thin reddish root is known as a "+
      "Streyroot, it is mildly poisonous when chewed.\n");
    set_id_diff(30);
    set_find_diff(4);
    set_effect(HERB_POISONING, "herb", 25);
    set_ingest_verb("chew");
    set_herb_value(500);
    set_decay_time(3000);
}
