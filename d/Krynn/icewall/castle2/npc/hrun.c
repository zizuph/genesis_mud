/* coded by Torqual */
/* tuned by Kessie */

#include "/d/Ansalon/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/icewall/castle2/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/sys/filter_funs.h"

inherit MIN_BASE
inherit "/lib/unique";

/* defines */
#define MIN_WEP1      KWEP + "hrun_sword"
#define MIN_WEP2      KWEP + "hrun_axe"
#define MIN_WEP1a     KWEP + "hrun_crap_sword"

void
create_minotaur()
{
   remove_name("minotaur");
   remove_prop("_live_i_neverknown");
   set_name("hrun");
   set_adj("musclebound");
   add_adj("brown-furred");
   set_race_name("minotaur");
   remove_adj("huge");
   set_gender(G_MALE);
   set_long("@@my_long");
   set_stats(({ 200, 180, 250, 150, 150, 180 }));
   set_skill(SS_LOC_SENSE,100);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_WEP_AXE, 100); 
   set_skill(SS_WEP_SWORD, 100);
   set_skill(SS_2H_COMBAT, 100);
   set_skill(SS_BLIND_COMBAT, 70);
   set_skill(SS_AWARENESS, 100);
   heal_hp(query_max_hp());
   set_all_hitloc_unarmed(50);
   set_exp_factor(135);
   
   set_act_time(11);
   add_act("emote snorts violently.");
   add_act("emote looks far into the distance as if looking for "+
	   "something.");
   add_act("say I wonder if there is any challenge in these wastelands. "+
	   "All I can see around is snow and ice and snow again. Curse "+
	   "those fat bastards that send me here.");
   add_act("emote inspects his weapons. They appear well taken care of.");
   add_act("pace");

   set_cchat_time(11);
   add_cchat("Right, I need some excercises. Show me your best.");
   add_cchat("Come on! Did you tire already?!");
   add_cchat("You're such a pretty little thing... It is almost a shame " +
     "for me to beat you to a pulp!");
   add_cchat("Last one I simply squeezed till his eyeballs popped out...");
   
   set_alarm(2.0,0.0,"arm_me");

}    

string
my_long()
{
    string str;

    str = "No one but another minotaur ever called one of their "+
	"number beautiful. Both bulls and cows are seldom less "+
	"than seven feet tall - this one is not an exception. "+
 	"Brown fur covers his heavily musculed, human/bovine frame "+
	"and horns long as a foot and a half long grow from his " +
	"browbones. Judging by their look and scars covering his " +
	"skin this minotaur has partaken in more than one duel in his " +
	"life.\n";

    return str;

}

string
query_my_title()
{
   return "Rumaafal of Loarath Clan, Champion of the Arena.\n";
}

void
introduce_me(object ob)
{
    if(!present(ob, E(TO)))
    {
        return;
    }

  tell_room(E(TO), QCTNAME(TO) + " snorts and grunts something that "+
	"sounds like: "+ query_name() + " " + query_my_title());
  set_alarm(3.0, 0.0, &command("emote appraises you carefully" +
	""));
   FILTER_LIVE(all_inventory(E(TO)))->add_introduced("hrun");
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

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if ((sizeof(TO->query_enemy(-1))) || (query_hp() >(query_max_hp()/2)))
    {
        command("say My dear " + ob->query_nonmet_name() + " I shall enjoy " +
            "this little fight. Infact I was getting little stiff in " +
	    "that cold air.");
        command("say Let noone interfere in my fight!");
        command("emote salutes you briefly and starts circling around you.");
    }
    else if (query_hp() > query_max_hp()/2)
    {
    	command("say The more the better. Come and get some, " +
    		ob->query_race_name() + ".");
    }
    else
    {
    	command("I drew the long odds, but I do not mind that." +
		"I will still rip your heart out through your eyesocket!");
	command("laugh misch");
    }
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_unique(MIN_WEP1, 3, MIN_WEP1a)->move(TO, 1);
    clone_object(MIN_WEP2)->move(TO, 1);
    command("wield all");
}