/* Raspberry by Teth, Feb.16,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("berry");
    set_adj(({"frosty", "red"}));
/* renamed to frosty raspberry to differentiate better with the red and black
 * raspberries in Gondor. Mercade, March 2011. */
    set_herb_name("frosty raspberry");
    set_short("frosty red berry");
    set_pshort("frosty red berries");
    set_pname(({"berries", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a frosty red berry. It was probably " +
        "picked off a shrub in a forest."));
    set_id_long(BSN("This is a frosty raspberry, a frosty red berry found " +
        "in temperate forests. Raspberry (Rubus idaeus) is a shrub " +
        "that grows to about 1 meter high. It has thorny canes. This " +
        "berry is said to refresh a weary soul."));
    set_herb_value(40);
    set_id_diff(3);
    set_find_diff(4);
    set_effect(HERB_HEALING,"fatigue",5);
    set_decay_time(3000);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
