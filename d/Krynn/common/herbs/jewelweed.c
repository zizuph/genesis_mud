/* Jewelweed by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj("green");
    set_herb_name("jewelweed");
    set_short("green leaf");
    set_pshort("green leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("smear");
    set_unid_long(BSN("This is a green leaf. It was probably " +
        "picked from a plant near a riverbank or lakeshore."));
    set_id_long(BSN("This is the leaf of a jewelweed, an herb found " +
        "near temperate riverbanks and lakeshores. Jewelweed (Impatiens " + 
        "biflora) has a small pouch-like sepal that terminates in a nectar-" +
        "filled spur. The flowers are orange and dotted with brown or " +
        "purplish spots. The plant is fairly succulent. It grows to a " + 
        "height of 1.5 meters. Jewelweed smeared on the skin is one of " +
        "the only cures for poison ivy."));
    set_herb_value(232);
    set_id_diff(45);
    set_find_diff(8);
    set_effect(HERB_CURING,"ivy",50);
    set_decay_time(2000);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
