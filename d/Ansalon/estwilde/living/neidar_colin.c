#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>

#define WEP1 WEP + "teregul_axe"
#define ARM1 ARMOUR + "chainmail"
#define ARM2 ARMOUR + "leggings"
#define ARM3 ARMOUR + "i_gauntlets"
#define ARM6 ARMOUR + "i_boots"
#define ARM4 ARMOUR + "shield"
#define ARM5 ARMOUR + "horned_helmet"

inherit AM_FILE

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;
    set_name("corin");
    set_adj("grim");
    add_adj("black-bearded");
    set_living_name("corin");
    set_title("Windchaser, Grim Warrior of the Neidar " +
      "Clan");
    set_race_name("dwarf");
    set_gender("G_MALE");
    set_long("This rugged looking hill dwarf looks like he has " +
      "travelled far and wide across the lands of Ansalon. The " +
      "fire that burns in his eyes would suggest that he is on a " +
      "mission, and will stop at nothing to see his quest finished.\n");

    set_random_move(20);
    set_stats(({160,119,170,89,89,110}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(OBJ_I_RES_MAGIC, 50);
    add_prop(OBJ_I_RES_POISON, 70);
    add_prop(OBJ_M_NO_ATTACK, "By the fiery " +
      "look in the eyes of this dwarf, you know " +
      "he is not someone to cross.\n");

    set_alignment(700);
    set_knight_prestige(-3);

    set_default_answer("The dwarf looks at you funnily, as if " +
      "you should already know the answer to that.\n");
    add_ask(({"mission","quest","task"}),
      "say I am sorry, my quest is private, and is of no " +
      "concern to anyone but myself and my clansmen.", 1);
    add_ask(({"neidar clan", "clan", "hill dwarves"}),
      "say The hill dwarves are banding together within " +
      "the valley of Iron Delving.", 1);
    add_ask("karyth","say Ah, Karyth Skybolt.. my betrothed..", 1);
    add_ask(({"shale", "shale ironfist", "crimes"}),
      "emote becomes suddenly quiet, his face a stony mask. " +
      "You get the impression he doesn't want to talk about that.", 1);
    add_ask("teregul", "say My mentor, Teregul Stormbolt, was the finest " +
      "warrior the Neidar clan has ever had.", 1);

    set_act_time(5);
    add_act("emote stretches his gnarled hands before him.");
    add_act("emote curses the Mountain dwarves to eternal rust " +
      "and corrosion.");
    add_act("emote grumbles about the weather.");
    add_act("emote strokes his greying beard lovingly.");
    add_act("emote kneels on the ground and begins searching " +
      "for tracks.");
    add_act("say By Reorx do I miss Karyth!");
    add_act("say Shale Ironfist will pay for his crimes! " +
      "This I swear!");

    set_cact_time(0);
    add_cact("emote roars 'Great Reorx!' in astonishment!");
    add_cact("say curse yas to eternal rust and corrosion!");
    add_cact("emote roars: You doorknob! What ye think yur do'en?");


    seq_new("do_things");
    seq_addfirst("do_things", "@@arm_me");

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP1)->move(TO,1);
    clone_object(ARM1)->move(TO);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    clone_object(ARM4)->move(TO,1);
    clone_object(ARM5)->move(TO,1);
    clone_object(ARM6)->move(TO,1);
    command("wield all");
    command("wear all");
}

void
return_intro()
{
    command("introduce myself");
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
	set_alarm(1.0, 0.0, return_intro);
    }
}

void
greet_func(object friend)
{
    if(E(friend) != E(TO))
	return;

    if(!CAN_SEE(TO, friend))
    {
	friend->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }

    command("introduce myself to " + friend->query_real_name());
    friend->catch_msg("You relate your story to Corin, explaining " +
      "to him how you defeated Shale Ironfist, set Karyth's " +
      "spirit to rest, and was sent to find him by the ghost " +
      "of Teregul Skybolt.\n");
    command("rsay Finally. Justice has been seen to, and my quest " +
      "is finally over.");
    command("sigh relie");
    command("rsay You are truly a hero of the Neidar! Here, take this " +
      "as a sign of my gratitude!");
    command("give axe to " +friend->query_real_name());    

    if(!friend->test_bit("ansalon", 3, 5))
    {
	friend->set_bit(3, 5);
	friend->catch_msg("\nCongratulations! You have proven yourself as " +
	  "a true warrior of the Neidar clan! You may now train up to " +
	  "superior guru in your chosen weapon skill.\n\n");
	A_QUEST_LOG("quest", "Neidar Guru Quest", friend, 0);
    }      

    command("rsay Well, I shall begin my treck back to Iron Delving. " +
      "Until next, axes high warrior!");
    command("emote smiles dwarvishly, and trudges off.");

    friend->remove_prop(GIVEN_GURU_QUEST);
    friend->remove_prop(FREED_SPIRIT);
    friend->remove_prop(SPOKEN_TO_TEREGUL);

    TO->remove_object();
}


void
init_living()
{
    if(TP->query_prop(SPOKEN_TO_TEREGUL))
	set_alarm(6.0, 0.0, "greet_func", TP);

    ::init_living();
}
