/*
 * /d/Ansalon/goodlund/nethosak/docks/obj/pouch.c
 *
 * glain
 *
 * A common pouch that pretty much every minotaur will have filled
 * with various coinage and tidbits.  Prolly be moved up to a higher
 * dir.  Pretty much just borrowd Armans pouch, but made it minotaur
 * size.
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/std/pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Ansalon/common/defs.h"

object this;

void 
create_pack()
{
   set_name("pouch");
   set_pname("pouches");
   set_short("large leather pouch");
   set_pshort("large leather pouches");
   set_long("This is a leather pouch used by the minotaurs, and " +
      "looks funny worn by smaller creatures.  You may <fill> and " +
      "<empty> the pouch as you wish.\n");

   set_mass_storage(1);

   add_prop(CONT_I_WEIGHT, 1200);
   add_prop(CONT_I_MAX_WEIGHT, 15000);
   add_prop(CONT_I_MAX_VOLUME, 225000);

   add_prop(OBJ_I_VALUE, 120);
}


/* Standard code for recovery of a keepable object.*/

string 
query_recover()
{
   return MASTER + ":" + query_container_recover() + query_keep_recover();
}

void 
init_recover(string arg)
{
   init_container_recover(arg);
   init_keep_recover(arg);
}