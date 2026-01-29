#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
inherit M_FILE

void
create_krynn_monster()
{
set_name(({"warrior","skeleton"}));
set_pname(({"warriors","skeletons"}));
set_short("skeletal warrior");
set_pshort("skeletal warriors");
set_long("This is an undead warrior, damned to an eternal unlife "+
"of servitude to the Lord of this ghastly Keep. It's bones "+
"are decayed, and it still wears the tattered clothes from "+
"it's mortal life.\n");
set_adj("skeletal");
set_gender(2);
set_stats(({50 + random(50), 60 + random (50), 10 + random(10),
15 + random(20), 10 + random(15),100 + random(25)}));
set_skill(SS_AWARENESS, 60);
set_skill(SS_DEFENCE, 30 + random(30));
set_skill(SS_PARRY, 30 + random (30));
set_skill(SS_WEP_SWORD, 40 + random(30));
set_skill(SS_WEP_POLEARM, 50 + random(30));
set_skill(SS_WEP_AXE, 40 + random(30));
set_alignment(-1000);
set_cact_time(10);
add_cact("emote looks at you with undisguised hatred.");
add_cact("emote shrieks a terrible shrill sound.");
add_cact("emote stares silently around with glowing eyes.");
set_alarm(0.0,0.0,"arm_me");
trig_new("%w 'introduces' %s", "react_intro");
}

int react_intro(string who)
{
if (who)
{
who = lower_case(who);
if(find_player(who))
{
set_alarm(3.0,0.0,"return_intro", who);
}
return 1;
}
}

void return_intro(string who)
{
command("scream");
command("kill " +who);
command("kill " +who);
}

arm_me()
{
clone_object("/d/Krynn/dargaard/weapon/baksword")->move(TO);
clone_object("/d/Krynn/alustrial/skelhelm")->move(TO);
clone_object("/d/Krynn/alustrial/skelrobe")->move(TO);
command("wear all");
command("wield all");
}
