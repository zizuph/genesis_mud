/* Skullcap by Teth, Apr.5,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("mushroom");
    set_adj(({"black", "rotting"}));
    set_herb_name("skullcap");
    set_short("rotting black mushroom");
    set_pshort("rotting black mushrooms");
    set_pname(({"mushrooms", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a rotting black mushroom. It was " +
        "probably picked in a sewer or a dark wet place."));
    set_id_long(BSN("This is skullcap, a barely edible mushroom found " +
        "in dark wet places. Skullcap is, however, a favoured food of " + 
        "many denizens of these places, although they are known to have " +
        "a high tolerance for the kinds of poisons produced by a mushroom " +
        "such as this. The mushroom itself is black and decaying, with " +
        "the smell of death clinging to it."));
    set_effect(HERB_POISONING,"hp",2);
    set_herb_value(30);
    set_id_diff(5);
    set_find_diff(4);
    set_decay_time(2000);
    set_amount(2);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
