#include "defs.h"

#include <macros.h>

inherit "/d/Earthsea/std/room";
inherit "/lib/unique";

int no_npc;

public void set_no_npc(int n)
{
  no_npc = n;
}

void create_thwil_room()
{

}

nomask void create_earthsea_room()
{
  create_thwil_room();
  reset_room();
}

void reset_room()
{
  object npc;
  ::reset_room();

  /* Randomly clone Roke apprentices */
  while (!no_npc && random(10) > 8)
  {
      string file = THWIL+"monster/roke" + (random(5) + 1);
      LOAD_ERR(file);

      object ob = find_object(file); 

      if (sizeof(object_clones(ob)) < 4) {
	npc = clone_object(file);
        npc->move(this_object());
      }
  }
}
