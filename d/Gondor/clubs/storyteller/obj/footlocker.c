/*
 * /d/Gondor/clubs/storytellers/obj/footlocker.c
 */
inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

void
create_container()
{
  set_name("footlocker");
  add_name("box");
  add_name("locker");
  set_short("beautiful cherrywood footlocker");
  set_long("This is a large footlocker that has been placed by the "+
	"door, presumably to store items in. On the footlocker is "+
	"written: He who throws junk on the floor, may find himself "+
	"shoved out the door.\n");
  add_prop(CONT_I_MAX_WEIGHT,  2000000); /* 2000 kilos */
  add_prop(CONT_I_MAX_VOLUME,  2000000); /* 2000 liters */
  add_prop(CONT_I_WEIGHT, 20000);
  add_prop(CONT_I_VOLUME, 160000);
  add_prop(CONT_I_RIGID, 1);
  add_prop(OBJ_M_NO_GET, "The footlocker is far too big to be taken.\n");
}                               
