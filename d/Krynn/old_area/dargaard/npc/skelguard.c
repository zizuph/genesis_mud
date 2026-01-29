#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>

inherit M_FILE

public void
create_krynn_monster()
{
  set_name(({"guard", "skeleton"}));
  set_pname(({"guards", "skeletons"}));
  set_short("skeletal guard");
  set_pshort("skeletal guards");
  set_long("This skeletal warrior is one of Lord Soth's personal " +
	   "guards. It looks even more deadly and evil the the warriors, if " +
	   "that's even possible. The gleam in his glowing eyes seem to warn " +
	   "you that if dare attack such a foe, you will be slain.\n");
  set_adj("skeletal");
  set_gender(2);
  set_stats(({80 + random(50), 100 + random(50), 100 + random(50),
		45 + random(20), 30 + random(15), 130 + random(25)}));
  set_skill(SS_AWARENESS, 60);
  set_skill(SS_DEFENCE, 60 + random(30));
  set_skill(SS_PARRY, 60 + random(30));
  set_skill(SS_WEP_SWORD, 60 + random(30));
  set_skill(SS_WEP_POLEARM, 70 + random(30));
  set_skill(SS_WEP_AXE, 60 + random(30));

  set_alignment(-3000);

  set_act_time(6);
  add_act("emote growls something unintelligible.");
  add_act("emote glares coldly at you, eager for living flesh.");
  add_act("emote looks at you, and you feel a supernatural chill " +
	  "run up your spine.\n");

  set_cact_time(6);
  add_cact("emote growls: Fool! You will soon join me in unlife!");
  add_cact("emote shrieks a terrible shrill sound.");
  add_cact("emote stares silently around with glowing eyes.");
  add_cact("emote grins evilly.");

  set_alarm(1.0, 0.0, "arm_me");

  trig_new("%w 'introduces' %s", "react_intro");

  add_prop(NPC_I_NO_LOOKS, 1);
}

public int
react_intro(string who)
{
  if (who) {
	     who = lower_case(who);
	     if (find_player(who)) {
				     set_alarm(3.0, 0.0, "return_intro", who);
				   }
	     return 1;
	   }
}

void 
return_intro(string who)
{
  command("scream");
  command("kill " + who);
}

public void
arm_me()
{
  switch (random(3)) 
    {
    case 0:
      clone_object("/d/Krynn/dargaard/weapon/skelsword")->move(TO);
      clone_object("/d/Krynn/dargaard/weapon/skelsword")->move(TO);
      break;
    case 1:
      clone_object(WEAPON + "skelhalb")->move(TO);
      break;
    case 2:
      clone_object(WEAPON + "skelsword2")->move(TO);
      break;
    }
  clone_object(ARMOUR + "skelhelm")->move(TO);
  clone_object(ARMOUR + "skelmail")->move(TO);
  clone_object(ARMOUR + "skelrobe")->move(TO);
  command("wear all");
  command("wield all");
}
