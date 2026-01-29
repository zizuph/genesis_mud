// Herb woman for Native Camp
// She sells and buys herbs....
// Maybe she can sell mild potions (?)

inherit "/std/monster";
#include "/d/Emerald/defs.h"


create_monster()
{
	set_name("sarah");
	add_name("woman");
	add_name("shopkeeper");
	set_race_name("human");
	set_gender(G_FEMALE);
	set_short("small woman");
	set_adj("merry");
	set_long("   This woman looks organized and adept at running " +
	"her small shop which loans out messangers for you to send " +
	"letters to your friends.\n\n");
   set_stats(({ 55, 55, 60, 99, 98, 55 }));
   set_hp(10000);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(CONT_I_WEIGHT,63000);
   add_prop(CONT_I_HEIGHT,174);

   set_skill(SS_UNARM_COMBAT,65);
   set_skill(SS_DEFENCE,52);

	set_chat_time(7);
	add_chat("How can I help you?");
	seteuid(getuid());
}


arm_me()
{
	object shirt, skirt;
	shirt = clone_object(VOBJ + "shirt.c");
	shirt -> move(this_object());
	skirt = clone_object(VOBJ + "skirt.c");
	skirt -> move(this_object());
	command("wear all");
}
void
intro_me()
{
	command("say My name is Marie.");
}
