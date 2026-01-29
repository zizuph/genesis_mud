#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";
#include "../guild.h"
#define WEAPON_DIR "/d/Shire/misty/wep/"
#define ARMOUR_DIR "/d/Shire/misty/arm/"

void
reset_room()
{
  int i;

  for(i=0; i<9; i++)
  {
    if(random(2))
    {
      if(random(4))
        clone_object(WEAPON_DIR+"club_low")->move(TO);
      else
        clone_object(WEAPON_DIR+"club_med")->move(TO);
    }
    else
    {
      if(random(4))
        clone_object(ARMOUR_DIR+"shield_low")->move(TO);
      else if(random(4))
        clone_object(ARMOUR_DIR+"shield_med")->move(TO);
      else
        clone_object(ARMOUR_DIR+"shield_high")->move(TO);
    }
  }
}

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(AA_DIR + "rooms/shop", "west");
   add_exit(AA_DIR + "rooms/store_r", "east");

   set_max_values(15, 5);

   reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
