#include "/d/Emerald/defs.h"

inherit EMERALD_MONSTER;

inherit "/d/Emerald/telberin/npc/aid_npc";

#include "default.h"

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

static object partner;
static string *patrol_path = ({ });

void
create_emerald_monster()
{
   set_name(({ "royal guard", "guard" }));
   set_race_name("elf");
   set_short("royal guard");
   set_long("This tall and imposing elf is a member of the Royal "+
      "Guards of Telberin. He looks like he has seen a few battles "+
      "in his lifetime, and watches the city with a confident gaze.\n");
   
   set_give_aid(1);

   /*
   set_long("This is one of the provincial guards who guard the city. He " +
      "looks like he is trained in the art of war.\n");
   */
   
   
   set_stats(({ 50, 58, 49, 50, 48, 45 }));
   /* I raised these stats as they seemed imbalanced for the equip, and we
   need some mid-level guards...  Xak@Genesis - 11Mar96
   set_stats(({ 32, 28, 30, 33, 28, 35 }));   
   */

   add_prop(NPC_I_NO_RUN_AWAY, 1);   
   
   set_skill(SS_WEP_SWORD, 46);
   set_skill(SS_WEP_KNIFE, 46);
   set_skill(SS_2H_COMBAT, 50);
   set_skill(SS_PARRY, 49);
   set_skill(SS_DEFENCE, 48);
   set_skill(SS_AWARENESS, 40);
   set_skill(SS_UNARM_COMBAT, 40);   
   
   set_all_hitloc_unarmed(3);
   
   set_chat_time(21 + random(30));
   
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

   set_monster_home(NPC_HANDLER);
   set_random_move(10 + random(5));
   set_restrain_path(TELBERIN_DIR);

   add_equipment(({ CASTLE_DIR + "wep/g_sword", WEP_DIR + "dagger",
                CASTLE_DIR + "arm/g_brig", CASTLE_DIR + "arm/g_helmet"}));
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

object *query_team()
{
  if (partner)
  {
      return ({ partner }) + ::query_team();
  }

  return ::query_team();
}

object query_partner() { return partner; }

void init_living()
{
   ::init_living();
   
   if (!partner && MASTER_OB(this_player()) == MASTER)
   {
      if (this_player()->set_partner(this_object(), 1))
      {
         set_partner(this_player());
      }
   }
}

void attacked_by(object enemy)
{
  ::attacked_by(enemy);
  get_assistance(enemy);
}

void assist()
{
  tell_room(environment(), "The guard gives assistance unto his " +
      "comrade.\n", this_object());
}
