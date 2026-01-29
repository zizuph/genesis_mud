inherit "/std/monster"; 
#include "/d/Emerald/defs.h"
string follow;
 
void
create_monster()
{
 
   set_adj("yellow");
   set_name("bird");
   add_name("canary");
   set_short("yellow canary");
   set_race_name("bird");
   set_long("A yellow - feathered bird that is used to detect poison " +
     "in caves.\n"); 
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(NPC_I_NO_LOOKS, 1);
   add_prop(OBJ_I_WEIGHT, 30000);
   add_prop(OBJ_I_VOLUME, 39732);
   add_prop(CONT_I_HEIGHT, 8);
   set_stats(({10,10,10,10,10,10}));
   add_prop(OBJ_M_NO_ATTACK, 1);
   add_prop(OBJ_M_NO_MAGIC, 1);
   add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
   add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
}
 
void
init_living()
{
   ::init_living();
 
 
   if (!stringp(follow) && this_player()->check_player_pub())
      {
      follow = this_player()->query_real_name();
      set_follow(follow);
   }
}
 
string
query_follow()
{
   return follow;
}
