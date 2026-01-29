#pragma strict_types
// Nethra       (/d/Avenir/common/herbs/nethra.c)
// Creator:      Glinda, june -9
// Purpose:      A herb for underwater breathing.
// Update:       Cirion, July 1996 - changed the way the water
//                    resistance works
//               Lucius, Jan 2009: Cleaned up and modified to share
//                       use of the water_res object.
//
inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Avenir/include/water.h"

public void
create_herb(void)
{
    set_name("alga", 1);
    set_pname("algae");
    add_name(({"_underwater_breathe_herb"}), 1);
    set_short("slimy red alga");
    set_pshort("slimy red algae");
    set_adj(({ "slimy", "red" }));

    set_unid_long("This is a thread of slimy red alga.\n");
    set_id_long("This is a thread of slimy red algae, known as Nethra, " +
      "well known for its magic powers of underwater breathing.\n");

    set_dryable();
    set_find_diff(5);
    set_id_diff(30);
    set_herb_value(226);
    set_herb_name("nethra");
    set_ingest_verb("eat");
    set_decay_time(700);
    set_effect(HERB_SPECIAL, "all", 10);
}

public void
special_effect(void)
{
    object who = environment(),
	   obj = present(MBW_CHECK_ID, who);
    
    if (objectp(obj))
    {
	obj->add_time(MBW_NETHRA);
	who->catch_tell("You feel refreshed, and your lungs "+
	    "seem to fill with more air than they can hold.\n");
	return;
    }

    if (!objectp(obj = clone_object(MBW_OBJECT)))
    {
	who->catch_tell("The taste makes you gag as though "+
	    "something were wrong.\nMake a bug report.\n");
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
