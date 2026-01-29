#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#include "guild.h"

void
create_room()
{
  set_short("starting room");
  set_long("This is a big dark hall with rows of beds in it. Every "+
           "warrior from Angmar's army has his own bed here and whenever "+
           "he wishes to, he can sleep here.\n");

  add_item(({"bed", "beds", "warrior", "warriors"}), "Most of the beds are "+
        "empty at the moment but you can see some warriors sleeping here.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(THIS_DIR+"train", "east");
}

void
init()
{
  ::init();
    add_action("start","start");
    add_action("start","sleep");
}

int 
start(string str)
{
  NF(CAP(query_verb())+" where?\n");
  if(str != "here") return 0;

  if(TP->query_guild_member(GUILD_NAME))
  {
    if(TP->set_default_start_location(MASTER_OB(TO)))
      write("Ok. You will be sleeping here.\n");
    else
      write("There are some problems. Please try again.\n");
    return 1;
  }
  write("No way!!! The owner of the bed will kill you for sure!\n");
  return 1;
}
