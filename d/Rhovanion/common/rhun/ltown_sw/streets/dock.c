#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

#define NUM_RATS   6

static object *rats;

void reset_room();

void create_room()
{
  set_short("Ferry dock");
  set_long("This is a rather old-looking wooden"
        +" pier which extends into the water of the Sea of Rhun."
        +"  The ferry from across the bay lands here, piloted"
        +" by the esteemed Captain Dingle.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st8","southwest",0);
  rats = allocate(NUM_RATS);
  reset_room();
}

void make_rats()
{
  string room, dir = RHUN_DIR+"ltown_sw/streets/";
  string *rooms = get_dir(dir+"*")-({".",".."});
  int i;

  for(i=0; i<NUM_RATS; i++)
  if(!rats[i])
  {
    room = dir+ONE_OF_LIST(rooms);
    rats[i] = clone_object(NPC_DIR+"rat");
    rats[i]->set_restrain_path(RHUN_DIR+"ltown_sw/");
    rats[i]->move(room);
    tell_room(room,"A filthy rat comes in searching for food.\n");
  }
}

void reset_room()
{
  make_rats();
}
