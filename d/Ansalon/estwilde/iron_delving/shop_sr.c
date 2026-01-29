/*
* the store for the Iron Delving shop.
*/

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR1 ARMOUR + "i_gauntlets"
#define ARMOUR2 ARMOUR + "i_boots"

object arm1, arm2, arm3, arm4;

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

reset_room()
{
  reset_euid();

  if(!arm1)
    (arm1 = clone_object(ARMOUR1))->move(TO);
  if(!arm2)
    (arm2 = clone_object(ARMOUR1))->move(TO);
  if(!arm3)
    (arm3 = clone_object(ARMOUR2))->move(TO);
  if(!arm4)
    (arm4 = clone_object(ARMOUR2))->move(TO);

}

create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(IRON + "shop","north");

    INSIDE;  /* This is an inside room */
    reset_room();
}


