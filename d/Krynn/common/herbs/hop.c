/* Common Hop by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("vine");
    set_adj(({"woody", "twining"}));
    set_herb_name("common hop");
    set_short("woody twining vine");
    set_pshort("woody twining vines");
    set_pname(({"vines", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a woody twining vine. It was probably " +
        "picked from a moist place, perhaps near a roadside or forest."));
    set_id_long(BSN("This is the vine of common hop, a vine found " +
        "in temperate moist forested areas. Common hop (Humulus lupulus) " +
        "has shiny palmately lobed leaves. The fruit is a resinous achene " +
        "which is used to flavour alcoholic beverages. Consuming it in its " +
        "herbal form can cause a headache of sorts."));
    set_herb_value(24);
    set_id_diff(16);
    set_find_diff(3);
    set_effect(HERB_HEALING,"mana",-1);
    set_decay_time(7500);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
