/* 
 * This is laranthas. It increases strength. 
 * It is based on the same herb by Theobald, Jan 24, 1995, originally 
 * from the old Rhovanion domain.
 * Updated by Finwe, May 2004
 *
 * 2004/06/05 Last update
 * 2011/07/21 Lavellan - Added "green" adjective.
 */

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_herb()
{
    set_name("berry");
    set_pname("berries");
    set_adj("small");
    add_adj("green");
    add_adj("wrinkled");
    set_short("small green wrinkled berry");
    set_pshort("small green wrinkled berries");
    set_herb_name("laranthas");
    set_id_long("This is a small green wrinkled berry known as Laranthas. " +
        "It grows in fields and comes from small, ground hugging plants. " +
        "The berries are rare but are used by travellers to aid them when " +
        "they feel weak.\n");
    set_unid_long("This is a small green wrinkled berry.\n");
    set_id_diff(20);
set_effect(HERB_ENHANCING, "str", 10);
    set_ingest_verb("eat");
    set_find_diff(5);
    set_decay_time(1800);
    set_herb_value(512);
}

