#include "defs.h"

#undef    COMMON_ARM_DIR    
#define   COMMON_ARM_DIR    "/d/Raumdor/development/shanoga/common/arm/"

inherit STD_DIR + "monster";
inherit LIB_DIR + "intro";


void
create_monster()
{
    ::create_monster();
    set_name("Tihomir");
    add_name("inkeeper");
    set_adj("haggard");
    set_race_name("human");
    set_gender(G_MALE);
    set_long("@@long_desc@@");
    set_stats(({80,90,80,80,90,60}));
    set_exp_factor(50);
    set_title("the Innkeeper");
    set_act_time(5);
    add_act("emote shuffles around the room, tending to " + HIS(TO) +
      " duties.");
    add_act("emote mumbles about delayed supplies.");
    add_act("say If you're headed to Drakmere, I'd advise traveling only " +
      "during daylight.");
    set_cact_time(3);
    add_cact("emote screams: I knew I shouldn't have taken this job " +
      "way out here!\n");
    add_cact("grumble");
    add_cact("asay tiredly Just kill me already...");

    equip(({
        COMMON_ARM_DIR + "barkeep_apron",
        COMMON_ARM_DIR + "barkeep_shirt",
        COMMON_ARM_DIR + "barkeep_pants"
    }));
}

string
long_desc()
{
    string str = "This sloppily-dressed man looks exhausted from the long " +
      "nights and days of tending the Haven. ";
    if (DAY)
    {
        str += "He is busy rearranging tables and chairs that were strewn " +
          "about last night and left toppled by long-gone adventurers.\n";
    }
    else
    {
        str += "He seems overwhelmed by splitting his time between making " +
          "the rounds of the tables and filling orders from behind the " +
          "counter.\n";
    }
    return str;
}

void
greet(object ob)
{
   if (!CAN_SEE(TO, ob) || ob->query_wiz_level())
       return;
   command("asay uncaringly Hello, " + ob->query_nonmet_name() + ", and " +
     "welcome to the Haven. Have a seat if you're so inclined.");
}

void
init_living()
{
   ::init_living();
   if (interactive(TP))
      {
      set_alarm(1.0,0.0,&greet(TP));
   }
}