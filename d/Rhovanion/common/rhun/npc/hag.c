
inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
#include "/d/Rhovanion/common/rhun/sw/s_s/sw_ent_quest.h"

/* Global object for ointment, since it is cloned in one func
 * and moved in another.
 */
 object ob;

create_monster() {
set_race_name("human");
set_adj("ugly");
add_adj("old");
set_short("An ugly old hag");
set_name("hag");
add_name("_sw_quest_hag");

set_alignment(5);
set_gender(1);
   set_long(break_string(
    "This old hag apparently lives here in these ruins.  You "+
    "wonder what in the world she stays here for.\n",75));
add_prop(CONT_I_WEIGHT, 70*1000);
add_prop(CONT_I_VOLUME, 70*1000);
add_prop(CONT_I_HEIGHT, 168);
add_prop(NPC_M_NO_ACCEPT_GIVE,0);
set_stats(({20,25,20,25,25,20}));
set_hp(query_max_hp());


set_skill(SS_UNARM_COMBAT, 12);
set_skill(SS_DEFENCE, 12);
   set_pick_up(43);

set_chat_time(4);
add_chat("I have the secret ointment.");
add_chat("The shadowlord has the treasure...");

set_act_time(4);
add_act("emote smiles fiendishly.");
add_act("cackle crazily");
add_act("grin insanely");

SGT
ob=clone_object(RHUN+"npc/ointment");
ob->move(this_object(), 1);

}


enter_inv(object obj, object from)
{
    if (!from) return;
    ::enter_inv(obj,from);
    if(obj==present("_sw_ent_quest_coin"))
    {
	if(TP->query_prop(I_DID_NOT_KILL_SHADOW_GUY))
	{
    command("say The treasure!");
    command("say I shall trade you!  Take this!");
    write("The old hag gives you a strange ointment.\n");
	ob->move(from);
    TP->add_prop(I_DID_NOT_KILL_HAG,1);
    }

	else
	{
		command("say What?  Have you slain the shadowlord?!?");
		command("say How dare you!");
		command("scream satan");
	}
   }
    else
    {
      command("say What is this?  I don't want this.");
	command("say Bring me the treasure!");
	write("The old hag returns it to you.\n");
      obj->move(from);
      return 1;
    }
}
