/* Angeltear by Teth, Apr.5,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("mushroom");
    set_adj(({"pale", "white"}));
    set_herb_name("angeltear");
    set_short("pale white mushroom");
    set_pshort("pale white mushrooms");
    set_pname(({"mushrooms", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a pale white mushroom. It was " +
        "probably picked in a sewer or a dark wet place."));
    set_id_long(BSN("This is angeltear, an edible mushroom found " +
        "in dark wet places. Angeltear is a soft marshmallowy fungus, and "+
        "is rumoured to have beneficial properties for one's mind when "+
        "eaten. It grows to about 10 cm tall, at which point it releases "+
        "its spores and quickly decays."));
    set_effect(HERB_HEALING,"mana",2);
    set_herb_value(40);
    set_id_diff(5);
    set_find_diff(6);
    set_decay_time(2000);
    set_amount(2);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
