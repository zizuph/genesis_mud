inherit "/std/monster";
inherit "/d/Emerald/telberin/npc/aid_npc";

#include "default.h"

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

static object partner;
static string *patrol_path = ({ });

void arm_me();

void
create_monster()
{
   set_name(({ "guard squire", "guard", "squire" }));
   add_adj("young");
   set_race_name("elf");
   set_short("guard squire");
   set_long("This young elf is an aspiring guard.  He has been training to "+
      "become a royal guard, and maybe someday a Paladin of Telberin!\n He watches "+
      "everything around him intently, hoping to learn as much as he can. \n");
   
   set_stats(({ 27, 27, 25, 28, 23, 30 }));
   
   set_skill(SS_WEP_KNIFE, 30);
   set_skill(SS_PARRY, 33);
   set_skill(SS_DEFENCE, 32);
   set_skill(SS_AWARENESS, 24);
   set_skill(SS_UNARM_COMBAT, 19);   
   
   set_all_hitloc_unarmed(3);
   
   set_chat_time(19 + random(30));
   
   add_chat("There is no finer city than Telberin in all the realms.") ;
   add_chat("The guards have told me chilling stories "+
      "about the vampires of ancient times!\n");
   add_chat("We have a new Paladin, they say he is the finest swordsman "+
      "in all of Emerald!");
   add_chat("There is none more beautiful than our Queen!") ;
   add_chat("I've been practicing long and hard with my dagger!");
   add_chat("I hope you enjoy our town.") ;
   add_chat("One day I hope to be a paladin!");
   
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   
   set_alignment(150);
   
    set_give_aid(1);
   set_alarm(1.0, 0.0, arm_me);
}

void
arm_me()
{
map(({ WEP_DIR + "dagger", "/d/Emerald/telberin/castle/arm/" + "g_helmet" }),
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

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    get_assistance(enemy);
}

void
assist()
{
    tell_room(environment(this_object()),
           "The guard squire gives assistance unto his comrade!\n",
           this_object());
}
