inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

int has_introduced=0;

void
create_monster()
{
	set_name("grimrot");
	set_race_name("half-giant");
	add_adj("black");
	add_adj("grim");
	set_short("grim black half-giant");
	set_long("This huge beast is half man, half giant. "+
	   "He looks very dangerous and capable of proving it. "+
	   "All his features are jet black, setting a forboding "+
	   "feeling about his entire presence.\n");

	set_stats(({ 100, 90, 120, 80, 80, 100 }));
	set_skill(SS_DEFENCE, 50);
	set_skill(SS_PARRY, 55);
	set_skill(SS_WEP_AXE, 90);
	set_skill(SS_UNARM_COMBAT, 35);

	set_alignment(-500);

	set_aggressive(1);

	refresh_mobile();

	set_act_time(7);
	add_act("emote looks contemptuously at you.");
	add_act("sigh angrily");
	add_act("growl");
	
	set_chat_time(8);
	add_chat("What do you want?");
	add_chat("Get out of my face.");

	set_cchat_time(10);
	add_cchat("You are a fool to disturb me!");
	add_cchat("I spare no one.");
	add_cchat("I kill all who intrude on me.");
	add_cchat("It is too late, you must end what you have begun!");

	trig_new("%w 'introduces' %s", "react_introduce");

	set_alarm(1.0, 0.0, "arm_me");
}
arm_me()
{
	seteuid(getuid(TO));
	clone_object(A_WEP_D +"axe1")->move(TO);
	clone_object(A_ARM_D +"scalemail")->move(TO);
	clone_object(A_ARM_D +"bcloak")->move(TO);
	clone_object(A_ARM_D +"blackboots")->move(TO);
        clone_object(A_ARM_D +"blackhelmet")->move(TO);


	command("wear all");
	command("wield all");
}

query_knight_prestige(){return 700;}

void
react_introduce()
{
	if (!has_introduced)
	{
	   set_alarm(4.0, 0.0, "introduce_me");
	   has_introduced=1;
	   set_alarm(15.0, 0.0, "remove_int");
	}
}

void
introduce_me()
{
   command("introduce myself");
}

void
remove_int()
{
   has_introduced=0;
}

string
query_title()
{
   return "King of the Slave Pens";
}

void
attacked_by(object player)
{
	add_prop(LIVE_O_ENEMY_CLING, player);
	::attacked_by(player);
}
