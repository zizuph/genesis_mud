/* IMPORTANT!                                                 */
/* ----------                                                 */
/* This is only the temporary pier for the shipline to Calia. */
/* pier.old contains the proper code for the intended ship-   */
/* line to Arcoron.                                           */
/*                          Jeremiah. 95/07/04                */


/* created by Aridor 07/03/94 */

#include "local.h"

inherit STREET_BASE

#include <stdproperties.h>
#include <macros.h>
#define SIGN_MESS   "The far away lands of Calia can be reached from this pier.\n" 
#define OPEN_SHIP   "/d/Krynn/solamn/palan/ship4/ship_open"

object ship;
int ship_open = 0;  

/*prototype*/
void add_stuff();


void
create_palan_room()
{

    set_short("New wooden pier in the Harbour");
    set_long("You are on a small wooden pier that has been built into " +
	     "the harbour basin. There is a sign hanging at the end of " +
	     "the pier. To the southeast, the main pier can be seen, with " +
	     "a tower on it further south.\n");

    add_exit(PIER2,"southeast");

    add_item("sign",SIGN_MESS);
    add_cmd_item("sign","read",SIGN_MESS);
    add_item("tower","It's a small tower but you have to go closer to see more.\n");

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type 'Call here restart_ship <reason>'.\n");

    add_item("pier", "The pier is built from wood.\n");
    
    restore_object(OPEN_SHIP);

    add_stuff();

}

void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!ship && ship_open)
    {
    	ship = clone_object(SHIP_D + "ship");
    	ship->start_ship();
    }
}

void
reset_palan_room()
{
    add_stuff();
}
/*
post_sign()
{
    object sign;

    seteuid(getuid(this_object()));

    sign = clone_object(OBJ + "sign");
    sign->move(SIGN_ROOM);
}

*/


restart_ship(string reason)
{
  if (!reason)
    {
      write("Can't restart the ship without a reason.\n");
      return 0;
    }
  (ship->query_captain())->remove_object();
  ship->remove_object();
  add_stuff();
  write_file("/d/Krynn/common/log/shiprestart", extract(ctime(time()), 4, 15)
               + " Palanthas-Arcoron " + capitalize(TP->query_real_name()) + " " + reason + "\n");
  write("Ship restarted.\n");
}

open_shipline()
{
    if (TP->query_name() == "Horatio" && TP->query_wiz_level())
      {
	  seteuid(getuid(TO));
	  ship_open = 1;
	  save_object(OPEN_SHIP);
	  add_stuff();
	  write("Shipline started. This state is saved and doesn't need to be repeated.\n");
      }
}

string
very_soon()
{
    if (ship_open)
      return "";
    else
      return " very soon";
}
