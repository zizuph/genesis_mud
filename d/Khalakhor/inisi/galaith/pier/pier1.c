/**********************************************************************
 * - pier1.c                                                        - *
 * - Created by Damaris 09/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 * Ported to the new ship system by Tapakah, 04/2009
 * Samorgan - EG exit block via quest transferred here,
 * Tapakah, 04/2009
 * Samorgan - EG exit block updated to the new quest layout,
 * Tapakah, 09/2021
 **********************************************************************/

#pragma strict_types

#include "/d/Khalakhor/sys/paths.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "/d/Khalakhor/sw_speir/samorgan/npc/riddler.h"
#include "../defs.h"

inherit PIER_ROOM;
inherit "/d/Khalakhor/common/room/samorgan-galaith-exit";

int *
query_local_coords ()
{
  return ({3, 5});
}

object ship;
object sign;

void
create_pier()
{

  add_prop(ROOM_I_NO_CLEANUP,1);    
  add_exit("pier2", "east", check_exit, 0, show_exit);
  add_pier_entry(MASTER_OB(TO), "Eil Galaith", "Route to Cadu");
  initialize_pier();
}

void
add_stuff ()
{
  seteuid(getuid(this_object()));
  if (!ship) {
    ship = clone_object(SHIPS + "sw_speir/galaith/ship");
    ship->start_ship();
  }
  if (!sign) {
    sign = clone_object(SHIPS + "sw_speir/galaith/sign");
    sign->move(this_object());
  }
}

void
restart_ship (string reason)
{
  if (!reason) {
    write("You need a [good] reason to restart a ship!\n");
    return 0;
  }
  (ship->query_captain())->remove_object();
  ship->remove_object();
  add_stuff();
  write_file("/d/Khalakhor/log/shiprestart", extract(ctime(time()), 4, 15)
             + " Galaith - Khalakhor " + capitalize(this_player()->query_real_name())
             + " " + reason + "\n");
  write("Ship restarted.\n");
}

