inherit "/std/monster";

#include "default.h"

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

static object partner;
static string *patrol_path = ({ });

void
create_monster()
{
   set_name(({ "royal guard", "guard" }));
   set_race_name("elf");
   set_short("royal guard");
   set_long("This is one of the provincial guards who guard the city. He " +
      "looks like he is trained in the art of war.\n");

   set_stats(({ 32, 28, 30, 33, 28, 35 }));   
   
   set_skill(SS_WEP_SWORD, 36);
   set_skill(SS_2H_COMBAT, 40);
   set_skill(SS_PARRY, 39);
   set_skill(SS_DEFENCE, 38);
   set_skill(SS_AWARENESS, 30);
   set_skill(SS_UNARM_COMBAT, 30);   

   set_all_hitloc_unarmed(3);
   
   set_chat_time(40 + random(20));
   
   add_chat("There is no finer city than Telberin in all the realms.") ;
   add_chat("I hope those nasty vampires never return!") ;
   add_chat("We have a new Paladin, they say he is the finest swordsman "+
      "in all of Emerald!");
   add_chat("There is none more beautiful than our Queen!") ;
   add_chat("I heard that the Royal Keep may soon open to visitors...") ;
   add_chat("I hope you enjoy our town.") ;
   add_chat("I hear the King will send us reinforcements soon!") ;
   
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   
   set_alignment(150);
}

void
arm_me()
{
  map(({ WEP_DIR + "g_sword", WEP_DIR + "dagger",
         ARM_DIR + "g_brig",  ARM_DIR + "g_helmet" }), 
         clone_object)->move(this_object(), 1);
  
   command("wield all");
   command("wear all");
}

int set_partner(object ob)
{
  if (partner)
  {
    return 0;
  }

  partner = ob;
  return 1;
}

object query_partner() { return partner; }

void init_living()
{
  ::init_living();

  if (!partner && MASTER_OB(this_player()) == MASTER)
  {
    if (this_player()->set_partner(this_object()))
    {
      set_partner(this_player());
    }
  }
}
