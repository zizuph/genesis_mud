/*********************************************************************
 * - griogair.c                                                    - *
 * - This is the NPC for SaMorgan Inn                              - *
 * - Created by Damaris 04/2006                                    - *
 *********************************************************************/
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

#define TUNIC "/d/Khalakhor/sw_speir/samorgan/arm/tunic"
#define KILT "/d/Khalakhor/common/kilts/kilt_morgan"

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
	set_name("bruce");
	set_title("MacGriogair of Clann 'Ic an t-Sagairt, Innkeeper");
	add_name(({"shopkeeper","keeper", "man"}));
	set_race_name("human");
	set_gender(G_MALE);
	add_adj(({"stout", "well-dressed"}));
	set_long("He is an innkeeper.\n"+
	"He has sparkling silver eyes.\n"+
	"He has smooth pale skin.\n"+
	"His hair is very short, sandy blonde and layered.\n");
	set_all_hitloc_unarmed(50);
	set_stats(({70,70,70,70,70}));
	add_prop(CONT_I_WEIGHT,48000);
	add_prop(CONT_I_HEIGHT,190);
	
	set_mm_in("arrives brushing out his kilt.");
	MONEY_MAKE_SC(random(40))->move(this_object());
	set_act_time(15);
	add_act("ponder");
	add_act("smile secret");
	add_act("whistle");
	add_act("emote hums a tune.");
	add_act("say Oh I do hope the Clans will be "+
	"pleased with my new menu.");
	add_act("emote moans saying: Oh my this has been a long day.");
	add_act("say Have you been to the Otherworld?");
	add_act("say They say if you ever go to the Otherworld you "+
	"will never return.");
	add_ask(({"undead"}),
	"say A word of warning the undead are closer than you "+
	"realize.", 1);
	add_ask(({"help"}),
	"say I could always use a bit of help, but not today.",1);
	add_ask(({"task"}),
	"say I have no tasks for you to do.", 1);
	add_ask(({"quest"}),
	"say Ahh now there is something I wish I could do, and that "+
	"is a quest. If only I could go off and discover something "+
	"but my Inn keeps me very busy.", 1);
	add_ask(({"minotaur", "minotaurs"}),
	"say Heh, Minotaur? You mean the cows? They are quite a "+
	"strange bunch.", 1);
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
		present(str, environment(TO))->add_introduced("bruce");
		command("kneel " + str);
		command("asay devoted Greetings to thee, " + capitalize(str) +
		". I am " + query_name() + " " + query_title() + 
		", thy humble servant.");
		command("asay devoted Ask anything of me and I shall do "+
		"my best to please thee.");
		
		remembered[str] = "nice";
	}
	else if (SECURITY->query_wiz_rank(TIQRN, "Khalakhor"))
	{
		command("asay devoted Greetings to thee, " + capitalize(str) +
		". I am " + query_name() + " " + query_title() + 
		". I am most pleased that thee has graced me with "+
		"thy pressence. How may I serve thee, a glass of "+
		"wine or perhaps thou art hungry?");
		present(str, environment(TO))->add_introduced("bruce");
		command("kneel " + str);
		remembered[str] = "nice";
	}
	else if (!remembered[str])
	{
		command("say Greetings to thee, " + capitalize(str) +
		", I am " + query_name() + " " + query_title() + 
		". A pleasure to make thy acquaintance.");
		present(str, environment(TO))->add_introduced("bruce");
		command("curtsey " + str);
		remembered[str] = "nice";
	}
	else if (remembered[str] == "bad")
	{
		command("growl sof");
		command("say I remember thou very well. So be on thy way!");
	}
	else
	{
		command("emote beams with pleasure.");
		command("say I remember thee very well from thy " +
		"last visit, " + capitalize(str) + ". How could I "+
		"ever forget thee.");
		present(str, environment(TO))->add_introduced("bruce");
		command("curtsey " +str);
		command("say I hope thou art faring well, and enjoying "+
		"our lovely village?");
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
