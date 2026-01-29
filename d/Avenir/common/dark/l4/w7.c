inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"



void
create_room()
{
  set_short("Western passageway");
  set_long("The western tunnel, now a passageway with nearly-\n" +
       "smooth walls, turns here, heading west and south.  The walls\n" +
       "are well cut and squared, as if by a skilled craftsman.\n");
  
  add_exit(L4 + "w6", "west", 0);
  add_exit(L4 + "w8", "south",0);

  add_prop(ROOM_I_LIGHT, 0);
  IN;
  	add_npc(MON + "ogre_dad", 1, &->equip_me() );
  reset_room();
}
