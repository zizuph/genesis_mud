/**
 * Sap object.
 * This object is cloned into a victim when they are
 * the target of a tsap ability.  It keeps thems from being
 * sapped for an amount of time.
 * Louie 2004
 */
 
inherit "/std/object";
//#include "../local.h"
#include <stdproperties.h>

/** prototypes **/
public void set_time_to_stay(float f);

public void
create_object()
{
	set_name("sap_ob");
	set_short("sap object");
	set_long("You shouldn't see this.\n");
	set_no_show();
	
	set_time_to_stay(360.0);

	add_prop(OBJ_M_NO_DROP, 1);
	add_prop(OBJ_I_VOLUME, 1);
	add_prop(OBJ_I_WEIGHT, 1);
	
}

/*
 * We set how long this lasts.
 */
public void
set_time_to_stay(float f)
{
	set_alarm(f, 0.0, &remove_object());
}