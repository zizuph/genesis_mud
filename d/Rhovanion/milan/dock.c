/* Dock in ltown_ne in Rhun, which starts the ship 
 * /d/Rhovanion/common/rhun/ltown_ne/streets/ferry to 
 * /d/Rhovanion/common/rhun/ltown_sw/streets/dock
 * 
 * Copied from examples supplied by Plugh
 */

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

#define NUM_RATS     7

static object rat_gob, *rats;

void load_ship();
void reset_room();

void create_room()
{
  set_short("Ferry dock");
  set_long("This is a wooden pier standing out in the"
    +" water of the bay where the River Carnen meets the Sea of Rhun."
    +"  The Ferry across the bay to the large neighbouring town on the"
    +" west side lands here.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st8","east",0);

  /* This room preloads to start the ship line */
  add_prop(ROOM_I_NO_CLEANUP,1);

  add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");

  load_ship();

  rats = allocate(NUM_RATS);
  reset_room();
}

void make_rats()
{
  string room, dir = RHUN_DIR+"ltown_ne/streets/";
  string *rooms = get_dir(dir+"*")-({".",".."});
  int i;

  for(i=0; i<NUM_RATS; i++)
  if(!rats[i])
  {
    room = dir+ONE_OF_LIST(rooms);
    rats[i] = clone_object(NPC_DIR+"rat");
    rats[i]->set_restrain_path(RHUN_DIR+"ltown_ne/");
    rats[i]->move(room);
    tell_room(room,"A filthy rat comes in searching for food.\n");
  }
  if(!rat_gob)
  {
    room = dir+ONE_OF_LIST(rooms);
    rat_gob = clone_object(NPC_DIR+"goblins/rat_gob");
    rat_gob->arm_me();
    rat_gob->move(room);
    tell_room(room,"A clumsy goblin arrives.\n");
  }
}

void reset_room()
{
  make_rats();
}

void load_ship()
{
  object ship;

  add_prop(ROOM_I_NO_CLEANUP, 1);

  seteuid(getuid());
  ship=clone_object(RHUN_DIR+"ltown_ne/streets/ferry");
  ship->move(TO,1);
  ship->start_ship();
}

string wizinfo()
{
  return "To restart the ship line, first make sure it "+
	 "is not already running. If it is, it should be removed "+
	 "completely (ie. ship & captain destructed). If the ship have "+
	 "been changed, update it before restarting.\n\n" +
	 "To actually load & restart the ship, give the following command:\n\n"+
	 "  Call here load_ship\n";
}

