 /* Borage. This herb well smell will increase temporarily 
  * inteligence. Coded by Marisol (08/12/98) to be used in
  * Emerald. Copyright (c) Marisol Ramos 1998 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flower");
    add_adj("bright blue");
    set_herb_name("borage");
    set_short("bright blue flower");
    set_pshort("bright blue flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A bright blue star-like flower.\n");
    set_id_long("A flower from a borage plant. This star-like "+
        "flower is a favorite of gardener and bees alike. It is "+
        "beautiful to the sight and sweet smelling. It is said "+
        "that long time ago Telan-Ri blessed this flower with "+
        "some magical blessing of enlightment.\n");

    set_ingest_verb("sniff");
    set_find_diff(5);
    set_id_diff(50);
    set_effect(HERB_ENHANCING, "int", 45);
    set_herb_value(900);
    set_decay_time(5000);
}

string
query_recover()
{
    return MASTER + ":" + query_herb_recover();
}
void
int_recover(string arg)

{
    init_herb_recover(arg);
}
