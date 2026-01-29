 /* Lavander. A country garden plant. The smell will enhance the 
  * healing of mana. Coded by Marisol (08/10/98) to be used in
  * Emerald. Copyright (c) Marisol Ramos 1998 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("spike");
    add_adj("purple");
    set_herb_name("twickle purple lavander");
    set_short("purple spike");
    set_pshort("purple spikes");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("An aromatic purple spike.\n");
    set_id_long("This is Twickle Purple, a beautiful plant of the "+
        "family of Lavander. It has grey-green aromatic foliage "+
        "and fragant spoles of light purple flowers. The aroma "+
        "is wholesome, filling you with a lightness of mind.\n");

    set_ingest_verb("sniff");
    set_find_diff(8);
    set_id_diff(55);
    set_effect(HERB_HEALING, "mana", 50);
    set_herb_value(900);
    set_decay_time(2000);
    set_dryable();
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
