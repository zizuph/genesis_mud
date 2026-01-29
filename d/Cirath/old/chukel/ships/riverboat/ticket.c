 /*  /d/Cirath/chukel/ships/riverboat/ticket.c
  *  This is the ticket for the DurniRiver boatride.
  *  Decius, November 1996
  */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

void
create_object()
  {
	set_name("leaf");
	set_pname("leaves");
	add_name("DurniRiver");
   	add_adj("worn");
	add_adj("green");
	set_long("This worn green leaf appears to be "+
		"used for something more then... umm you know what.\n");
	add_prop(OBJ_I_VALUE, 10);
   	add_prop(OBJ_M_NO_SELL,1);
  }

