// Locket Merchant
// creator(s): Cirion
// last update: Created May 20th, 1997
//             -Added signet rings. Sirra, July 2002.
// purpose:
// note:
// bug(s):
// to-do:
inherit "/d/Avenir/inherit/monster.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

void
create_monster()
{
	 ::create_monster();
	 set_name("kriantosh");
	 set_adj(({"tiny", "agile"}));
	 set_title("the Locketsmith");
	 add_name(({"shopkeeper","keeper","smith","locketsmith","merchant"}));
	 set_race_name("gnome");
	 set_gender(G_MALE);

	 set_long("This tiny creature has small, nimble hands and "
		 + "tired eyes.\n");

	 set_stats(({5,5,60,60,5,5}));

	 add_prop(NPC_I_NO_RUN_AWAY,1);

	 set_alignment(random(100));
	 set_knight_prestige(-2);

	 set_chat_time(20);
		  add_chat("Lockets lockets lockets. Rings rings rings.");
		  add_chat("I can put pictures in lockets or rings.");
		  add_chat("Wanna locket or signet ring? They're pretty.");
		  add_chat("Something to remember your beloved? Worn near the heart...");

	set_act_time(5);
		  add_act(({"emote picks up a small engraving tool.",
						"emote starts to engrave a locket.",
						"emote holds up a " + VBFC_ME("a_metal") + " locket, "
					 + "examining it closely.",
						"emote places the locket in the case."}));
		  add_act(({"emote starts to clean the shop.",
						"emote sweeps some dirt from the floor.",
						"emote polishes the glass case with a linen rag.",
						"emote tidies up his workbench.",
						"emote looks around with satisfaction."}));
		  add_act(({"open locket","show locket to all", "close locket"}));
		  add_act("hold locket");
		  add_act("rub locket");
		  add_act("rub ring");
                  add_act("shout Signet Rings! I have signet rings to sell!");


	set_cact_time(1);
		  add_cact("slap enemy");
		  add_cact("scream");

	 add_ask(({"locket", "order", "make locket", "help", "signet ring", "ring"}),
		  "say To order a locket or signet ring made, use <order ring> or <order locket>.",1);
}

void
arm_me()
{
	object loc;
	object rin;

	seteuid(geteuid(this_object()));
	MONEY_MAKE_SC(random(40))->move(this_object());

	loc = clone_object(BAZAAR + "Obj/worn/locket");
	  loc->set_metal("brass");
	  loc->set_engraving("Soft light that plays over our eyes as we sleep.");
	  loc->set_image("lambient veins embedded into a rock wall");
	  loc->move(TO, 1);

	rin = clone_object(BAZAAR + "Obj/worn/sig_ring");
		rin->set_metal("brass");
		rin->set_engraving("Meet on the level. Part on the Square.");
		rin->set_image("an eye over a triangle");
		rin->move(TO, 1);

	clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
	clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
	clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
	clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);

	command("wear all");
}

void add_introduced(string str)
{
	object who = present(str, ENV(TO));

	if(!who || !interactive(who) || who->query_met(query_real_name()) ||
		!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, who))
	  return;

	set_alarm(1.0 + itof(random(5)), 0.0, &command("introduce myself"));
}

string
a_metal()
{
	 return ONEOF(({"copper","silver","bronze","brass","iron","steel","gold"}));
}

string race_sound()
{
	return ONEOF(({"cries","babbles","mumbles","murmurs","sings"}));
}

