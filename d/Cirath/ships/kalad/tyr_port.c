 /* /d/Cirath/ships/kalad/tyr_port.c
  * Caravan loading docks.
  *Decius, December 1996
  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "ship.h"
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

object ship;

void
reset_room()
{
  if(!ship){
    ship=clone_object(SHIPS+"ship.c");
    ship->move(TO);
    ship->start_ship();
    }
}

void
create_room()
{
  set_short("Caravan loading docks");

  set_long("Hundreds of wooden crates form stacks against "+
    "the wall outside of Tyr's Iron Square. They sit waiting to "+
    "be transferred to the dozens of mekillot driven "+
    "merchant caravans that depart here regularly. "+
    "The occasional scream can be heard as a hungry "+
    "mekillot eats an unfortunate slave, followed by "+
    "bellows of laughter by amused overseers. Well "+
    "dressed merchants supervise the loading of their "+
    "wagons with practised ease... all in all, this "+
    "is organized chaos. It is here where may be found "+
    "passage to distant lands.\n");

  add_item(({"crates","wooden crates","stacks"}),
    "These crates contain merchandise of every type and "+
    "quality known to Tyr, and are meant for export to "+
    "distant cities. Countless riches are contain within "+
    "these boxes, and many guards stand watch to insure "+
    "they remain so.\n");

  add_item("wall","The tall outer wall of the Iron Square stands, defying "+
    "all who would attack the dynastic trading houses within.\n");

  add_item(({"caravans","wagons","merchant caravans"}),
    "These large cargo wagons carry commerce beyond the "+
    "walls of Tyr, far into the mighty desert. Many "+
    "depart every day, some never return.\n");

  add_item("merchants","Well dressed merchants scurry at "+
    "a frantic pace around their wagons, shouting commands "+
    "at slaves, inspecting their cargoes, and nervously "+
    "eyeing the desert as they prepare for the journeys "+
    "ahead.\n");

  add_item("overseers",
    "Whip-wielding overseers take cruel pleasure "+
    "in enforcing their master's commands. They beat their "+
    "fellow slaves for being too slow, or too fast, or "+
    "mishandling crates... or any other excuse they can "+
    "think of.\n");

  add_item("slaves","Miserable slaves of every common race "+
    "work endlessly loading and unloading the caravan "+
    "wagons, under the close 'supervision' of the "+
    "overseers.\n");

  add_item("guards","Heavily armed half-giants stand "+
    "guarding the crates. Every once in a while one of "+
    "them invites a passer-by to try to steal a crate. "+
    "Their offers are always politely declined.\n");

  add_exit(TYR+"caravan/rd_cw_07.c","north",0,1);
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_prop(OBJ_S_WIZINFO,"To restart the ship, type "+
    "'Call here restart_ship <reason>'.\n");

  OUTSIDE;
  ADD_SUN_ITEM;
  add_prop(ROOM_I_LIGHT,1);
  reset_room();
}
