#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

inherit "/lib/store_support";
inherit SAIL_ROOM_BASE;

#define CUTLASS "/d/Ansalon/balifor/flotsam/obj/weapon/cutlass"
#define BANDANA "/d/Ansalon/balifor/flotsam/obj/armour/bandana2"

object cutlass, bandana;

void
reset_sea_room()
{
  reset_euid();

  if(!cutlass)
    (cutlass = clone_object(CUTLASS))->move(TO);
  if(!bandana)
    (bandana = clone_object(BANDANA))->move(TO);

}

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room()
{
    return 0; 
}

public void
sink(object ob)
{
    return;
}

create_sea_room()
{
    set_short("jetty storeroom");
    set_long("jetty storeroom.\n");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);

    reset_sea_room();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);

}