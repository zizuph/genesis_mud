/* coded by Torqual */

#include "/d/Ansalon/common/defs.h"
#include "local.h"

inherit "/d/Genesis/ship/captain";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Ansalon/balifor/flotsam/ship3/local.h"
#include "/sys/filter_funs.h"


void
create_captain()
{
   set_name("goar");
   add_name("captain");
   set_race_name("minotaur");
   set_adj("huge");
   add_adj("black-furred");
   set_gender(G_MALE);
   set_long("@@my_long");
   set_stats(({ 180, 180, 180, 80, 80, 130 }));
   set_skill(SS_SWIM, 100);
   set_skill(SS_LOC_SENSE,100);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,90);
   heal_hp(query_max_hp());
   
   add_act("emote snorts violently.");
   add_act("emote looks far into the distance.");

   set_cchat_time(11);
   add_cchat("Right, I need some excercises. Show me your best.");
   add_cchat("Come on! I'll beat the living daylights out of you!");
   add_cchat("Right! I'm really gonna stump you this time!");
   add_cchat("I'm gonna smack you so hard....");
   
   add_prop(OBJ_M_NO_ATTACK,
      "It would be foolish to attack that minotaur when his crew "+ 
      "is around, wouldn't it?\n");
   add_prop(OBJ_M_NO_MAGIC_ATTACK, "Somehow no harm can be done to "+
      "that minotaur by means of magic. How strange.\n");
    add_prop(OBJ_I_RES_MAGIC, 200);
   
   set_ticket(TICKET);
   set_price(PRICE);
   
}    

string
my_long()
{
    string str;

    str = "No one but another minotaur ever called one of their "+
	"number beautiful. Both bulls and cows are seldom less "+
	"than seven feet tall - this one is almost eight. "+
 	"Short, black fur coveres his heavily muscled, human/bovine frame "+
	"and horns as much as a foot long grow from his browbones. Judging "+
	"by their look and scars covering his skin this minotaur is "+
	"quite an experienced fighter.\n";

    return str;

}

string
query_my_title()
{
   return "N'sarth of Klaf Clan, Captain of \"The Longhorn\".\n";
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
introduce_me(object ob)
{
    if(!present(ob, E(TO)))
    {
        return;
    }

  tell_room(E(TO), QCTNAME(TO) + " snorts something that sounds like: "+
   "Goar N'sarth of Klaf Clan, Captain of \"The Longhorn\".\n");
   FILTER_LIVE(all_inventory(E(TO)))->add_introduced("goar");
}

void
add_introduced(string person)
{
    object ob = find_player(lower_case(person));
    if(ob && !ob->query_met(TO))
    {
         set_alarm(3.0, 0.0, &introduce_me(ob));
    }
}
