/* 
 * marymoor - Makes players more sober
 * Finwe, January 2009
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb";

#define EFFECT 25
void
create_herb()
{
    set_name("mushroom");
    set_adj(({"large", "glossy"}));
    set_herb_name("marymoor");
    set_short("large glossy mushroom");
    set_pshort("large glossy mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a large glossy mushroom.\n");
    set_id_long("This large glossy mushroom is from the Marymoor mushroom. It grows deep in the Underdark and is pale colored. The mushroom is eaten to counter the effects of intoxication.\n");
    set_herb_value(( 4 * EFFECT) + (EFFECT * EFFECT)/4 );
    set_id_diff(30);
    set_find_diff(9);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_SPECIAL,"all",EFFECT);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }


void
special_effect()
{
    int curr_intox;

    curr_intox = TP->query_intoxicated();

    if(curr_intox < EFFECT)
        write("You don't feel any effect.\n");
    else
    {
        TP->set_intoxicated(TP->query_intoxicated() - EFFECT);
        write("You feel less intoxicated.\n");
    }

}


