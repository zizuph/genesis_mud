inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>

object deer;

create_room() 
{
 street = "overgrown, stone paved road";
 where = "southeast";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "sparse dry green grass";
 extraline = "You are on a rolling plateau extending as far as the"
           + " eye can see. In all directions, the " +vegetation
           + " covers the land of " +county+ ". You see"
           + " an old road running in from the northwest and vanishing to the"
           + " southeast.";

  add_exit(DUN_DIR+"road/r09","northwest",0);
  add_exit(DUN_DIR+"road/r07","southeast",0);

  make_the_room();
  add_stuff();
}

query_road()
{
 return 1;
}

add_stuff()
{
  if (!deer)
  {
    deer = clone_object("/d/Gondor/dunland/npc/deer");
    deer->move(this_object());
  }
}

reset_room()
{
  add_stuff();
}

