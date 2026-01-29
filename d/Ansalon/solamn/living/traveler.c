/*
	traveler.c
	__________

	Created by Kentari - July 1998 for the Kalaman-VK Highway
         (Modeled after Kayla in rl driving to a Gen Party in Spring 1998)

*/

#include <std.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
inherit M_FILE

public void
create_solamn_monster()
{
  set_name("kayla");
  add_name(({"traveler","girl"}));
  set_title("the Coachwoman of the Kalaman Highway");
  set_short("traveling girl");
  set_long("This young girl seems to be the driver of coach that now " +
	"lays as wreckage at her feet. Covered in road dust and a few " +
	"scrapes, she currently is in shock over what to do. She " +
	"looks like a very sweet girl, if not a very good driver.\n");

  set_adj("traveling");
  set_gender(G_FEMALE);
  set_knight_prestige(-2);

  set_default_answer("Kayla exclaims: I don't know what you're " +
	"talking about, but I'm a good driver, really!\n");
  add_ask(" [about] 'quest' / 'task' / 'help' / 'ride'",
	"Kayla looks around and says: Well, I'm not sure what " +
	"I'm gonna do yet, sorry.\n");

  set_stats(({70 + random(40), 80 + random(20), 100 + random(20),
		40 + random(20), 15 + random(15), 100 + random(25)}));
  set_skill(SS_AWARENESS, 55 + random(25);
  set_skill(SS_DEFENCE, 30 + random(30));
  set_skill(SS_PARRY, 30 + random(30));
  set_skill(SS_WEP_SWORD, 40 + random(30));
  set_skill(SS_WEP_KNIFE, 70 + random(30));

  MONEY_MAKE_GC(random(15) + 5)->move(TO);
  set_introduce(1);
  set_alignment(400);

  set_act_time(6);
  add_act("emote looks at the wreckage in despair.");
  add_act("emote mutters about how this could happen with her being " +
	"such a good driver.");
  add_act("emote pleads with you not to tell anyone as she'll never " +
	  "hear the end of it.");

  set_cact_time(6);
  add_cact("emote shrieks: Its not enough that I get in a wreck, " +
           but you attack me too!");
  add_cact("say will my troubles never end?!");
  add_cact("emote mutters: well, can't get much worse.");

  set_alarm(1.0, 0.0, "arm_me");

  add_prop(NPC_I_NO_LOOKS, 1);
  add_prop(NPC_I_NO_RUN_AWAY, 1);
}

public void
arm_me()
{
  switch (random(3)) 
    {
    case 0:
      clone_object(SWEAPON + "tsabre")->move(TO);
      break;
    case 1:
      clone_object(SWEAPON + "tblade")->move(TO);
      break;
    case 2:
      clone_object(SWEAPON + "knife")->move(TO);
      clone_object(SWEAPON + "knife2")->move(TO);
      break;
    }
  clone_object(SARMOUR + "dustcloak")->move(TO);
  clone_object(SARMOUR + "scarf")->move(TO);
  command("wear all");
  command("wield all");
}
