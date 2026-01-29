/* rd_pr_01: Promenade section 1: Serpine, 12-04-96
 * updated to include a carriage to raumdor and removed 
 * previous long and short - Damaris 08/2002 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";


#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

//void add_stuff();

object ship;
object sign;


void
create_room()
{
  set_short("Carriage loading dock");

  set_long("There are a few wooden crates scattered around and "+
    "some even form stacks against a wall. They sit waiting to "+
    "be transferred to the dozens of mekillot driven merchant "+
    "caravans that depart at another dock not too far from here.\n");

  add_item(({"crates","wooden crates","stacks"}),
    "These crates contain merchandise of every type and "+
    "quality known to Tyr, and are meant for export to "+
    "distant cities. Countless riches are contain within "+
    "these boxes, and many guards stand watch to insure "+
    "they remain so.\n");

  add_item("wall","It is a tall outer wall that stands, defying "+
    "all who would attack the dynastic trading houses within.\n");

  add_item(({"caravans","wagons","merchant caravans"}),
    "Caravans are large cargo wagons that carry commerce beyond the "+
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
  add_exit(TYR_NOBLE+"rd_pr_02.c", "south", "@@roof_message", 1);

  add_prop(ROOM_I_NO_CLEANUP,1);


  OUTSIDE;
  ADD_SUN_ITEM;
  add_prop(ROOM_I_LIGHT,1);
  reset_room();
  // ensure other pier loaded, ship on way
  //("/d/Raumdor/mountain/goudra/pass/trail/room/r0202")->get_this_object();
  //add_stuff();
}

/*
public void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!sign)
    {
        sign = clone_object("/d/Raumdor/ships/goudra/tyr/sign2");
        sign->move(this_object());
    }
}
*/
