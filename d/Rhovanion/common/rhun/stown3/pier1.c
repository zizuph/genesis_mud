/* Pier #1 in SmallTOWN3 in Rhun.... this loads ship1, which travels
 * upriver to Esgaroth, etc.
 * Copied from examples supplied by Plugh
 */

#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#define NUM_RATS   5

static object *rats;

void load_ship();
void reset_room();

void create_room()
{
  set_short("Pier");
  set_long("You are standing on a solidly-built wooden"
	+" pier which extends from the southwest end of this small"
        +" town"
	+" into the rushing waters of the River Carnen as it meets"
	+" the Sea of Rhun east and south of here.  The ship from"
        +" the northwest docks here regularly to take passengers"
	+" upriver toward Esgaroth.\n");

  add_exit(RHUN_DIR+"stown3/south_road","east",0);
  add_exit(RHUN_DIR+"stown3/pier2","northwest",0);

  add_prop(ROOM_I_LIGHT,1);

  /* This room preloads to start the ship line */
  add_prop(ROOM_I_NO_CLEANUP,1);

  add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");

  load_ship();
  rats = allocate(NUM_RATS);
  reset_room();
}

void make_rats()
{
  string room, dir = RHUN_DIR+"stown3/";
  string *rooms = get_dir(dir+"*")-({".","..","storeroom.c"});
  int i;

  for(i=0; i<NUM_RATS; i++)
  if(!rats[i])
  {
    room = dir+ONE_OF_LIST(rooms);
    rats[i] = clone_object(NPC_DIR+"rat");
    rats[i]->set_restrain_path(RHUN_DIR+"stown3/");
    rats[i]->move(room);
    tell_room(room,"A filthy rat comes in searching for food.\n");
  }
}

void reset_room()
{
  make_rats();
}

void load_ship()
{
    object ship;

    seteuid(getuid());
    ship=clone_object(RHUN_DIR+"ships/ship1");
    ship->move(this_object());
    ship->start_ship();
}

string wizinfo()
{
    return "To restart the ship line, first make sure it "+
	   "is not already running. If it is, it should be removed "+
	   "completely (ie. ship & captain destructed). If the ship have "+
	   "been changed, update it before restarting.\n\n" +
	   "To actually load & restart the ship, give the "+
           "following command:\n\n"+
	   "  Call here load_ship\n";
}
