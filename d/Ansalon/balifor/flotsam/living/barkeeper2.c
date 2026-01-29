#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP "/d/Ansalon/balifor/flotsam/obj/weapon/bclub"

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("barkeeper");
   set_short("half-ogre barkeeper");
   set_long("This big half-human, half-ogre is the barkeeper " +
      "of this joint. His technique at pouring beers is bad, as " +
      "he always has one hand on a large club. Understandably, " +
      "the locals here don't complain.\n");
   set_stats(({110,70,110,50,50,90}));
   set_hp(10000);
   
   set_skill(SS_WEP_CLUB, 65);
   set_skill(SS_DEFENCE, 55);
   
   set_act_time(5);
   add_act("emote attempts to pour a beer with one hand.");
   add_act("emote grunts: Whatcha want!");
   
   set_cact_time(0);
   add_cact("shout HEY! IM DA BARKEEP!");
   add_cact("shout Smeg ya to da Abyss den! I smash ya!");
   add_cact("emote belts you savagely with his club!");
   
   add_ask("quest","emote grunts: Smeg off. If ya dont wanna " +
      "drink then getcha out of 'ere!",1);
   
}

void
arm_me()
{
   seteuid(getuid(this_object()));
   clone_object(WEP)->move(this_object(),1);
   command("wield all");
}
