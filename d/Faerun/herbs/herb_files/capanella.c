/* 
 * capanella - Heals mana over a period of time. Based on
 * Earthsea's skunkberries. Thanks Earthsea!
 * Finwe, march 2009
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb";

void
create_herb()
{
    set_name("mushroom");
    set_adj(({"small", "woody"}));
    set_herb_name("capanella");
    set_short("small woody mushroom");
    set_pshort("small woody mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a small woody mushroom.\n");
    set_id_long("The top of the cap is pale yellow, fading into a tan color. The stalk is thick and dark brown with a black ring about half way down it. At the base of the stalk are red bumps.\n");
    set_herb_value(( 4 * 25) + (25 * 25)/4 );
    set_id_diff(50);
    set_find_diff(8);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_SPECIAL,"all",25);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }


public void
special_effect()
{
    object poison;

    write("As you eat the small woody mushroom, your tongue swells up cutting off your airway for a minute.\n");
    TP->command("choke");
    setuid();
    seteuid(getuid(TO));
    poison = clone_object(HERB_POISON + "cap_poison");
    poison->move(TP, 1);
}
