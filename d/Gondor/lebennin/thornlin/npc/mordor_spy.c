/* 
 * thornlin/npc/mordor_spy.c
 *
 * Thanks to Shire for this file!
 * I redid it to fit into Thornlin in Gondor!
 *
 * Revision : Calador 1996. Added : Ohtari entrance quest.
 *                          Removed : non-working functions.
 *          : Gorboth 2009. Added: Death Spell skill to represent Merc Trainer
 */

inherit "/std/monster";
#include "/d/Gondor/defs.h"
inherit (LIB_DIR + "friend_or_foe.c");

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../locals.h"

//  Global variables
int     intro_id;

void
create_monster()
{
    set_name("athir");
    add_name(({"man","old man"}));
    set_living_name("athir");
    set_adj("old");
    set_race_name("human");
    set_long("This is an old man with red eyes burning like coals.\n");

    set_stats(({40,15,20,35,45,10}));
    set_alignment(-300);  

    add_act("say Who are you ?");
    add_act("say Those fools don't know who to put their money on!");
    add_act("emote mumbles: He is coming, soon!");
    add_act("say All those women and children from Minas Tirith think "+
      "they are safe here...");
    add_act("emote mumbles: Soon I will own this place!");
    add_act("emote mumbles: They always laughed at me, it'll stop "+
      "when He gets here!");
    add_cact("shout The Eye will win!");
    add_cact("shout I am protected!");
    add_cact("emote grumbles: You will suffer for this!");
    add_cact("emote screams wildly: You may defeat me, but we will win "+
      "anyways!");
    add_cact("say You can't defeat Him, you haven't seen his power");
    add_cact("emote covers his head with his arms.");
    add_cact("grin");
    add_cact("laugh");
    add_cact("cackle evil");
    set_act_time(5);
    set_cact_time(5);

    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_AWARENESS, 35);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_WEP_KNIFE, 70);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_2H_COMBAT, 45);

}

/* Test if I was the victim */
public void
attacked_by(object ob) 
{
    object  draughuan = find_living("draughuan");

    if (!objectp(draughuan))
    {
	command("shout Killing me won't stop us!");
	command("shout He will get you, the red Eye watches you!");
	command("grin");
    }
    else
    {
	command("say That was a big mistake.");
	command("emote screams: You will die now, " + ob->query_race_name());
	command("emote waves with his hand at his wolf dog!");
	command("shout Kill!");
	command("emote mumbles: But make "+TP->query_objective()+" suffer!");

	ob->attack_object(draughuan);
	::attacked_by(ob);
	say(QCTNAME(TP) + " attacks the old man, but the wolf-dog jumps "
	  + "between them and defends his master!!\n");
    }
}

void
arm_me()
{
    FIX_EUID
    clone_object(OBJ_DIR + "cane")->move(TO);
    clone_object(WEP_DIR + "poison_dagger")->move(TO);
    command("wield cane");
    command("wield dagger");
    command("emote hisses: Thought you could catch me off guard did you?");
}

public void
add_introduced(string name)
{
    object player;

    if (!objectp(player = present(find_player(name), ENV(TO))))
	return;

    if (player->query_met(query_name()))
	return;

    if (query_friend_or_foe(player) > 0)
	set_alarm(2.0, 0.0, &command("spit " + name));
    else
	set_alarm(2.0, 0.0, &command("present me to " + name));
}
