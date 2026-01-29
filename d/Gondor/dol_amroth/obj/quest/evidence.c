/* -*- Mode: C -*-
 *
 * obj/quest/evidence.c
 *
 * Evidence that there is a spy in the city.
 */
inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("envilop");
    add_name( ({ "evidence", "papers", "DolAmrothEvidence" }) );
    set_short("thick envilop");
    set_pshort("thick envilopes");
    set_long("This is an envilop filled with evidence that there is a spy " +
	     "lurking in Dol Amroth. Give it to the harbour master so he " +
	     "can complete the investigation and put the spy for trial.\n");

    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 25);
    add_prop(OBJ_I_WEIGHT, 150);
}













