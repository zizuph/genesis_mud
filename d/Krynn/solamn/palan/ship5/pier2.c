/* created by Aridor 06/21/93 */

#pragma save_binary

#include "local.h"

inherit STREET_BASE

#include <stdproperties.h>
#include <macros.h>
#define SIGN_MESS   "A shipline from Grey Havens in the Shire will anchor " +\
                    "here every now and then, taking passengers across " +\
                    "the ocean.\n"


object ship;
object worker;

/*prototype*/
void add_stuff();


void
reset_palan_room()
{
    add_stuff();
    if (worker)
      return;
    worker = clone_object(LIV + "harbour_worker");
    worker->move(TO);
}

void
create_palan_room()
{
    set_short("Pier in the Harbour");
    set_long("The pier divides the harbour. There is a small tower " +
	     "here on the pier, so ships will find their " +
	     "way in at night as well. There is a sign on the western " +
	     "side of the pier. " +
	     /* "A new wooden pier has been built into the harbour basin " +
		"to the northwest. " + */
	     "To the north a pier extends " +
	     "into the bay and to your south you can see some kind of " +
	     "gate leading into the city itself.\n");
    
    add_exit(ROOM + "street13","south","@@only_unwielded",1);
    add_exit(PIER2,"north");
    add_exit(PIER3,"northwest");
    
    add_item("sign",SIGN_MESS);
    add_item("tower","@@tower_desc");
    add_item(({"gate","guard"}),
	     "There is an iron gate with a guard shutting off this pier " +
	     "from the rest of the city to the south. The gate is open " +
	     "though.\n");
    add_cmd_item("rod",({"take","get"}),"@@take_the_rod");
    add_cmd_item("tower",({"climb","enter"}),
		 "You realize quickly that this is not possible.\n");
    
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_S_WIZINFO,
	     "To restart the ship, ONLY if it is stuck, type 'Call here " +
	     "restart_ship <reason>'.\n");
    
    add_item("pier", "The pier is built from stone.\n");
    
    add_stuff();
    
}

void
init()
{
    ::init();
    add_action("read","read");
}

int
only_unwielded()
{
    if (this_player()->query_weapon(-1) != ({}))
      {
	  write("The guard at the gate steps up to you and says:\n" +
		"    You have no access to the city.\n" +
		"    Offensive people are not welcome in the beautiful city " +
		"of Palanthas.\n" +
		"    No weapons may be wielded within the city limits.\n");
	  return 1;
      }
    write("The guard steps aside and says: You may pass. Welcome to the " +
	  "beautiful city of Palanthas. Enjoy your stay.\n");
    return 0;
}

string
tower_desc()
{
    object ob;
    if (ob = present("tour4", TP))
      ob->set_arr("lighttower");
     return "It's a small lighthouse about 20 feet high.\n";
}

int
read(string str)
{
    NF("Read what?\n");
    if (str != "sign")
      return 0;
    write(SIGN_MESS);
    return 1;
}

void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!ship)
      {
	  ship = clone_object(SHIP_D + "ship");
	  ship->start_ship();
      }
}

int
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
               + " Grey Havens-Palanthas " + capitalize(TP->query_real_name())
	       + " " + reason + "\n");
    write("Ship restarted.\n");
    return 1;
}

