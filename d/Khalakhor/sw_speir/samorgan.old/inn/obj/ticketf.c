/*********************************************************************
 * - ticketf.c                                                     - *
 * - female public bathing room                                    - *
 * - Created by Damaris 6/2003                                     - *
 *********************************************************************/
#pragma save_binary
#pragma strict_types
 
inherit "/std/object";
#include "../inn.h"
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
 
public void create_object()
{
	set_name("ticket");
	add_name(TICKET_BATH_F);
	add_adj(({"female", "bathing"}));
	set_long("The pale pink ticket is made from a thin sheet "+
	"of parchment died pale pink. It gives the bearer "+
	"access to the female bathing room in the SaMorgan Inn.\n");
	add_prop(OBJ_I_VALUE,  PRICE);
	add_prop(OBJ_I_WEIGHT, 1);
	add_prop(OBJ_I_VOLUME, 5);
}
 
