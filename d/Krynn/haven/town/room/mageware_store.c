#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/haven/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/lib/store_support";
inherit HAVENINBASE;

#define STAFF "/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff"
#define STAFF_V "/d/Krynn/wayreth/obj/vstaff"
#define WAND "/d/Krynn/solace/poolbottom/obj/wand"

object staff1, staff2, staff3, staff4, staff5, staff6;
object wand1, wand2, wand3, wand4, wand5, wand6;

void
reset_haven()
{
  reset_euid();

  if(!wand1)
    (wand1 = clone_object(WAND))->move(TO);
  if(!wand2)
    (wand2 = clone_object(WAND))->move(TO);
  if(!wand3)
    (wand3 = clone_object(WAND))->move(TO);
  if(!wand4)
    (wand4 = clone_object(WAND))->move(TO);
  if(!wand5)
    (wand5 = clone_object(WAND))->move(TO);
  if(!wand6)
    (wand6 = clone_object(WAND))->move(TO);
  if(!staff1)
    (staff1 = clone_object(STAFF))->move(TO);
  if(!staff2)
    (staff2 = clone_object(STAFF))->move(TO);
  if(!staff3)
    (staff3 = clone_object(STAFF))->move(TO);
  if(!staff4)
    (staff4 = clone_object(STAFF_V))->move(TO);
  if(!staff5)
    (staff5 = clone_object(STAFF_V))->move(TO);
  if(!staff6)
    (staff6 = clone_object(STAFF_V))->move(TO);

}

create_haven()
{
    set_short("mageware storeroom");
    set_long("mageware storeroom.\n");

    reset_haven();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);

}