 /* Meadowsweet. This herb will give some magic resistance
 * It is found in Emerald. Coded by Marisol (08/10/98)
 * Copyright(c) Marisol Ramos 1998 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flowerhead");
    add_adj("white");
    set_herb_name("meadowsweet");
    set_short("white flowerhead");
    set_pshort("white flowerheads");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A green plant with massive white flowerhead.\n");
    set_id_long("A meadowsweet! This plant, as the name suggestes, "+
        "it is found in meadows near water. The leaves and flowers "+
        "are very aromatic; the leaves smell rather like "+
        "wintergreen, yet the flowers have a sweet almond-and-honey "+
        "fragance in the evening air. This plant is mainly favor "+
        "by wise women and sage femme for spells against evil "+
        "magic, but that is only hearsay.\n");

    set_ingest_verb("eat");
    set_find_diff(8);
    set_id_diff(12);
    set_effect(HERB_ENHANCING, "magic", 16);
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
