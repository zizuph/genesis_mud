/*
 * Changes
 * Cotillion - 2017-09-19
 * - Fixed syntax error preventing load
 */ 
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("berry");
    set_short("little black berry");
    set_pshort("little black berries");
    set_adj(({"little", "black", }));
    set_herb_name("blackberry");
    set_id_long("This is a blackberry. The blackberry has " + 
	"a mild purgative and restorative effect.\n");
    set_unid_long("This black berry looks like an ordinary " + 
	"berry. You don't know what it's for.\n");
    set_ingest_verb("eat");
    set_id_diff(15);
    set_find_diff(2);
    set_effect(HERB_HEALING, "fatigue", 2);
    set_decay_time(3600);
    set_herb_value(18);
    set_amount(3);
    add_prop(OBJ_I_WEIGHT, 3);
    add_prop(OBJ_I_VOLUME, 3);
}

