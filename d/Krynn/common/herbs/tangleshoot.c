/* Tangleshoot by Teth, Apr.2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("vine");
    set_adj(({"twisted", "thorned"}));
    set_herb_name("tangleshoot");
    set_short("twisted thorned vine");
    set_pshort("twisted thorned vines");
    set_pname(({"vines", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a twisted thorned vine. It was probably " +
        "discovered in a north temperate forest."));
    set_id_long(BSN("This is a vine of tangleshoot, a noxious herb that is " + 
        "found in temperate forests. Tangleshoot is a vine that can cover " +
        "the forest floor, making it extremely difficult for one to pass " +
        "through freely. In addition, this vine has small thorns which poke " +
        "through flesh, so that the vine can receive some vital nutrition. " +
        "This herb has no known use."));
    set_herb_value(25);
    set_id_diff(3);
    set_find_diff(7);
    set_decay_time(5000);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
