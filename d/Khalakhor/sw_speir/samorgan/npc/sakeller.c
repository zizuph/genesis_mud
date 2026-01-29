/**********************************************************************
 * - sakeller.c                                                     - *
 * - NPC in the Tavern in SaMorgan                                  - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"

#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>   // for G_FEMALE
#include <macros.h>  // for OB_NAME
#include <files.h>
#include <std.h>
#include "npc.h"


inherit "/d/Khalakhor/std/npc/human";
inherit "/d/Khalakhor/lib/knowledge_base";
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";

static mapping remembered = ([]), failed = ([]);
#define TIQRN        this_interactive()->query_real_name()

object shop;
object last_attacker;
int return_alarm_id,
    attacker_alarm_id,
    has_armed;

void
create_khalakhor_human()
{
    set_name("shamus");
    set_title("Keller Tavern owner");
    add_name(({"sakeller", "owner","waiter", "man"}));
    set_race_name("human");
    set_gender(G_MALE);
    add_adj(({"large", "pot-bellied"}));
    set_long("He is a large pot-bellied tavern owner.\n"+
      "He has crystal blue eyes.\n"+
      "He has fair freckled skin.\n"+
      "His hair is very short, brown with speckles of gray.\n");
    set_all_hitloc_unarmed(50);
    set_stats(({70,70,70,70,70,70}));
    add_prop(CONT_I_WEIGHT,48000);
    add_prop(CONT_I_HEIGHT,190);
  
    set_alignment(100);
    set_mm_in("arrives brushing out his apron.");
    MONEY_MAKE_SC(random(40))->move(this_object());
    set_act_time(15);
    seteuid(getuid());

    clone_object("/d/Khalakhor/common/arm/shirt_cloth")->move(TO);
    clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
    clone_object("/d/Khalakhor/common/kilts/kilt_morgan")->move(TO);
    clone_object("/d/Khalakhor/se_speir/port/arm/apron")->move(TO);
    command("wield all");
    command("wear all");

    add_act("ponder");
    add_act("smile thought");
    add_act("whistle soft");
    add_act("emote hums a tune.");
    add_act("emote clears some dishes from a table.");
    add_act("emote straightens his apron.");
    add_ask(({"undead"}),
      "say A word of warning the undead are closer than you realize.", 1);
    add_ask(({"help"}),
      "say I could always use a bit of help, but not today.",1);
    add_ask(({"task"}),
      "say I have no tasks for you to do.", 1);
    add_ask(({"quest"}), 
      "say Ahh now there is something I wish I could do, and that "+
      "is a quest. If only I could go off and discover something "+
      "but my cooking keeps me very busy.", 1);
    add_ask(({"food", "foods"}),
      "say Oh yes please look at the menu, we have plenty of food "+
      "here.",1);
    add_ask(({"drink", "drinks"}),
      "say Oh sure we have lots to drink here, alcohol just being one.",1);
    add_ask(({"dark ale"}),
      "say The dark ale is quite good. I purchased it from a merchant "+
      "not too far from here.",1);
    add_ask(({"ale"}),
      "say Aye, we have light and dark ale. Tak a good look at the "+
      "menu.",1);
    add_ask(({"light ale"}),
      "say We have very good light ale for those who prefer a mild "+
      "tasting brew.",1);
    add_ask(({"merchant"}),
      "say There are plenty of merchants around here.",1);
    add_ask(({"milk"}),
      "say We have buttermilk or strawberry milk.",1);
    add_ask(({"buttermilk"}),
      "say Sure we have got buttermilk for ye, look at the menu.",1);
    add_ask(({"strawberry milk"}),
      "say You like milk? We have fresh strawberry milk something my "+
      "young ones truly like so I put it on the menu.",1);
    add_ask(({"steamed clams", "clams"}),
      "say We select only the finest plump clams from a merchant down "+
      "the road and then we steam and season them. Try a plate full, I'm "+
      "sure you would like it.",1);
    add_ask(({"beef", "seasoned beef"}),
      "say There is a butcher not so far from here that brings "+
      "us fresh beef and I season it to perfection. Try a plate "+
      "and see.",1);
    add_ask(({"butcher"}),
      "say The butcher? He is a nice fellow, gives me a good "+
      "price on beef too since I always give him and his family "+
      "discount",1);
    add_ask(({"discount"}),
      "say You do not look like you need a discount.",1);
    add_ask(({"corncake", "corncakes"}),
      "say Corncakes are a specialty of mine, I learned to make "+
      "them after spending a few months in Port Macdunn and been "+
      "making them ever since.",1);
    add_ask(({"travel", "traveling"}),
      "say I've not been traveling in ages. I settled here and "+
      "have been quite content.",1);
    add_ask(({"eggs", "egg", "scrambled eggs"}),
      "say We only use fresh eggs, give it a try.",1);
    add_ask(({"muffin", "muffins"}),
      "say The blueberry muffins are perfect with any meal or "+
      "just by themselves.",1);
    add_ask(({"oyster", "oysters"}),
      "say Each oyster is fresh and specially breaded and fried.",1);
    add_ask(({"wife"}),
      "say Ahh yes, my wife, such a beautiful woman. I am a luckey "+
      "man to have found her.",1);
    add_ask(({"samorgan"}),
      "say Why.. ye be in SaMorgan. It's a friendly little port. "+
      "Go explore a bit and ye will see.",1);
    add_ask(({"explore"}),
      "say Explore? Sure there are lots of things to explore. I "+
      "like to to fish when I'm not busy tending to me tavern.",1);
    add_ask(({}),
      "",1);
    
    
}
/*********************************************************************
 * - Function name: hook_return_intro                              - *
 * - Description  : Called when someone introduces themselves.     - *
 * - Arguments    : str - Name of the player introducing.          - *
 * - Returns      : 1                                              - *
 *********************************************************************/
public int
hook_return_intro(string str)
{
   if (SECURITY->query_wiz_rank(TIQRN) >= WIZ_ARCH)
    {
        command("asay devoted Blessed be my soul!");
        present(str, environment(TO))->add_introduced(query_real_name());
        command("kneel " + str);
        command("asay devoted Greetings to ye, " + capitalize(str) +
            ". I am " + query_name() + " " + query_title() + 
            ", humble servant to ye.");
        command("asay devoted Ask anything of me and I shall do "+
            "my best to please ye.");
        remembered[str] = "nice";

    }  
   else if (SECURITY->query_wiz_rank(TIQRN, "Khalakhor"))
    {
        command("asay devoted Greetings to ye, " + capitalize(str) +
            ". I am " + query_name() + " " + query_title() + 
            ". I am most pleased that ye has graced me with ye "+
            "pressence. How may I serve ye?");
        present(str, environment(TO))->add_introduced(query_real_name());
        command("kneel " + str);
        remembered[str] = "nice";

    }  
 
    else if (!remembered[str])
    {
        command("say Greetings to ye, " + capitalize(str) +
            ", I am " + query_name() + " " + query_title() + 
            ". A pleasure to make ye acquaintance.");
        present(str, environment(TO))->add_introduced(query_real_name());
        command("bow " + str);
        remembered[str] = "nice";

    }
    else if (remembered[str] == "bad")
    {
        command("growl sof");
        command("say I remember thou very well. So be on ye way!");
    }
    else
    {
        command("emote beams with pleasure.");
        command("say I remember ye very well from ye " +
          "last visit, " + capitalize(str) + ". How could I "+
          "ever forget ye.");
        command("curtsey " +str);
        command("say I hope thou art faring well, and enjoying our "+
          "fine city?");
    }
    return 1;
}
public void
add_introduced(string who)
{
    kb_add_introduced(who);
}

public void
init_living()
{
    ::init_living();
    kb_init_living();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    kb_enter_env(to, from);
}
