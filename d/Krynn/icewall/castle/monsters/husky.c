/* Fixed Up By Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit M_FILE

init_living() 
{
    ADA("pet");
    ::init_living();
}

int 
pet(string str) 
{
    if ((str == "husky") || (str == "dog")) 
      {
	  write("You ruffle the husky's fur and it wags its tail.\n");
	  say(QCTNAME(TP)+" pets the husky.\n");
	  say("Husky wags its tail.\n");
	  return 1;
      }
    NF("Pet what?\n");
    return 0;
}


void
create_krynn_monster()
{
   int i;
   
   set_name("husky");
   set_race_name("dog");
   set_long(BS(
         "As you look down at the husky it looks up at you with"
         + " its huge, brown eyes and sticks it tongue out."
         + "",75));
   
   set_adj("furry");
   
   set_random_move(30);
   
   for (i = 0; i < 6; i++)
   set_base_stat(i, 2 + random(10));
   set_all_attack_unarmed(5, 5);
   set_all_hitloc_unarmed(4);
   set_alignment(100);
   set_knight_prestige(5);
   set_monster_home(ICE_CAST1_R + "main_hall.c");
   set_restrain_path("/d/Krynn/icewall/castle/floor1/");
   set_chat_time(3);
   add_chat("woof");
   add_chat("moo");
   add_chat("grrrrr");
   
}
