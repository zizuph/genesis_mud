inherit "/d/Genesis/ship/captain";
#include "/d/Ansalon/goodlund/nethosak/ship/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>

#define ENV(xxx) environment(xxx)

int intro = 0;

void
create_monster()
{
   set_name("sangreal");
   add_name("captain");
   set_race_name("minotaur");
   add_adj("strong");
   set_adj("dark-haired");
   set_gender(G_MALE);
   set_long("This is one of the minotaurs on the Island of Mithas. "+
             "It's extremely tall almost seven feet in height, short "+
             "fur covers his massive body and a thin fuzz hides their "+
             "faces and covers their forearms. It's bullish face is "+
             "brutish and ugly, with a broad snout and wide-set eyes. "+
             "It has long, wide hands with thick fingers ending in short "+
             "claws.\n");
   set_stats(({ 80, 80, 100, 60, 60, 90 }));
   set_skill(SS_SWIM, 100);
   set_skill(SS_LOC_SENSE,100);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,50);
   heal_hp(10000);
   
   set_chat_time(8);
   add_chat("Damn those pirates. I wish they could find some dragonarmy "+
            "ships to plunder instead of mine.");
   add_chat("Where's my bottle of booze?");
   add_chat("Ahh, how I love the smell of the Bloodsea");
   
   set_cchat_time(11);
   add_cchat("Stop it, you pestering dog!");
   add_cchat("Right, you'll pay for that!");
   add_cchat("Come on! I'll beat the living daylights out of you!");
   add_cchat("Right! I'm really gonna stump you this time!");
   add_cchat("Give it to me, big-nose!");
   add_cchat("I'm gonna smack you so hard....");
   
   trig_new("%w 'introduces' %s", "react_introduce");
   
   add_prop(OBJ_M_NO_ATTACK,
      "You feel this minotaur is under strong protection.\n");
   
   set_ticket(TICKET);
   set_price(PRICE);
   
}    

string
query_my_title()
{
   return "The captain of 'The Gladiator'";
}

int
buy(string str)
{
   if (this_player()->query_average_stat() < 20)
      {
      notify_fail("You don't need to buy any ticket. " +
            "Young travel for free.\n");
      return 0;
   }
   
   return ::buy(str);
}

void
react_introduce(string person,string who)
{
   if (!intro)
      intro = set_alarm(4.0,0.0,"introduce_me");
}

void
introduce_me()
{
   tell_room(E(TO),QCTNAME(TO) + " introduces herself as:\n" +
      "Captain Sangreal of the house of Nar-Klaf's, champion, male minotaur.\n");
   FILTER_LIVE(all_inventory(E(TO)))->add_introduced("sangreal");
   intro = 0;
}


