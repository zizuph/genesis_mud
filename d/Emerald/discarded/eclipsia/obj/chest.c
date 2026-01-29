/* Created by Lucas Nov 6 1996 */
/* Modeled after Teth's chest */

inherit "/std/container";
#include <macros.h>
#include <filter_funs.h>
#include <money.h>
#include <stdproperties.h>
#define TO this_object()

void put_pearls();

void
create_container()
{
	object pearl;
    object emerald;
   set_name("chest");
   set_adj("old");
   set_long("This chest of old has been here so long that it has " +
      "rusted, in an open position, luckily. This must have been " +
      "what the ship was hauling back home when it was attacked " +
      "by the kraken.\n");
   
   add_prop(CONT_I_WEIGHT, 2500000);
   add_prop(CONT_I_MAX_WEIGHT, 22500000);
   add_prop(CONT_I_VOLUME, 3000);
   add_prop(CONT_I_MAX_VOLUME, 20300);
   add_prop(OBJ_I_VALUE, 400);
   add_prop(CONT_I_CLOSED, 0);
   
   MONEY_MAKE_GC(100)->move(TO);


   
   put_pearls();
}

void
put_pearls()
{
	object pearl;
   object emerald;
	int i;

	setuid();
	seteuid(getuid());

	for (i = 0; i < random(10) + 2; i++)
	{
		pearl = clone_object("/d/Emerald/eclipsia/obj/pearl");
		pearl->move(TO, 1);
	}
/*
   emerald = clone_object("/d/Emerald/eclipsia/obj/emerald");
   emerald->move(TO,1);
*/
}
