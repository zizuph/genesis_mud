/*
 * Gylvir - Allows breathing underwater. Restricted herb to Faerun and 
 * only found along seacoasts. Thanks to Lucius and Zielia for help with it.
 * Finwe, 
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>
// includes routines to breathe underwater
#include "/d/Avenir/include/water.h"

inherit "/std/herb";

void
create_herb()
{
    set_name("alga");
    add_name(({"_underwater_breathe_herb"}), 1);
    set_pname("algae");
    set_adj(({"slimy", "yellow"}));
    set_herb_name("gylvir");
    set_short("slimy yellow alga");
    set_pshort("slimy yellow algae");
    set_ingest_verb("eat");
    set_unid_long("This is a slimy yellow alga. It's from a coastal tidepool.\n");
    set_id_long("This slimy yellow alga is known to the locals as Gylvir. It is eaten to enable them to breathe underwater for a few minutes.\n");
    set_herb_value(( 4 * 10) + (10 * 10)/4 );
    set_id_diff(30);
    set_find_diff(5);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_SPECIAL,"all",10);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }

public void
special_effect(void)
{
    object who = environment(),
	   obj = present(MBW_CHECK_ID, who);
    
    if (objectp(obj))
    {
	obj->add_time(MBW_NETHRA);
	who->catch_tell("You feel a change come over you. Your lungs seem to change and you feel able to breathe underwater.\n");
	return;
    }

    if (!objectp(obj = clone_object(MBW_OBJECT)))
    {
	who->catch_tell("The taste of water becomes bitter and the pressure presses down on you.\nMake a bug report.\n");
	return;
    }

    int prop = who->query_prop(MAGIC_I_BREATH_WATER);

    if (!prop &&
	((environment(who)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER) ||
	 (environment(who)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)))
    {
	who->catch_tell("You find that you can breathe in the water.\n");
    }

    who->catch_tell("The air tastes different.\n");
    obj->set_time(MBW_NETHRA);
    obj->move(who, 1);
}
