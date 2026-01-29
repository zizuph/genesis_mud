/*
 * Modified:
 * Louie April 2006 - Added leave_env and appraise_object funcs.
 */

/* 
 * Navarre Feb 11 2007, Changed it from being a holdable item.
 * Since it was not used for anything.
 * Also increased the duration, as it they would expire too fast
 * for anyone to take advantage of them. 
 */

inherit "/std/object";

inherit "/lib/keep";
#include <const.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"

/* Global variable */
static int alarm_id = 0;
static int weight_id = 0;

/* Prototypes */
void remove_dark();

public void
create_object()
{
    set_name("orb");
    set_adj("negatively");
    add_adj("charged");
    set_short("negatively charged orb");

    set_long("This orb is the impacted remains of a creature of darkness. " +
      "For a short period, it remains in the physical world before departing "+
      "to the plane of negative energy.\n");
 
    add_prop(OBJ_I_WEIGHT, 235);
    add_prop(OBJ_I_VOLUME, 79);
    add_prop(OBJ_I_VALUE, 3 * 12 * 12 * 12);
    add_prop(OBJ_I_LIGHT, DARKNESS_TEMPORARY);


    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({
	"An orb of darkness, caused from the implosion of an undead " +
        "creature.\n", 40 }) );

    add_prop(OBJ_S_WIZINFO, "This orb is the remains of an undead creature. It " +
        "lasts for around four hours, for which " +
        "OBJ_I_LIGHT set to DARKNESS_TEMPORARY.\n");

    set_alarm(itof(3*3600+random(2*3600)), 0.0, &remove_dark());    
 
}

void
remove_dark()
{
    write("The negatively charged orb dissipates into nothing.\n");
    remove_object();
}
 

