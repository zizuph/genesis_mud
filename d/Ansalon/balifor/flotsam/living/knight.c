#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit "/std/act/action";
inherit AM_FILE

#define PLAYER_I_KILLED_KERNAN  "_player_i_killed_flotsam_kernan"
#define ARM "/d/Krynn/solamn/vin/armour/full_armour"
#define WEP FOBJ + "/weapon/lsword"

/*Thanks go to Cirion for the code to set the maximum health */
/*for the knight, so he always looks at least terribly hurt */

/* Code mentioned above was buggy. Never use set_hp() in query_hp()
 * as set_hp() calls query_hp() -> infinite recursion.
 * Fixed by Milan 1.3.99.
 */

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("knight");
    set_adj("injured");
    set_race_name("human");
    set_gender("G_MALE");
    set_short("injured knight");
    set_long("This young Knight of Solamnia is a long way from home. " +
      "From the looks of things he has been seriously injured in a recent " +
      "fight. Even so, he still manages to hold his head high with dignity " +
      "as you look upon him. \n" + "He is a Knight of the Crown.\n");

    set_stats(({90,110,80,75,75,90}));
    set_hp(500);
    set_alignment(1200);
    set_knight_prestige(-1200);

    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 100);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_AWARENESS, 65);

    set_act_time(5);
    add_act("emote murmurs 'Est Sularus oth Mithas'.");
    add_act("emote coughs weakly.");
    add_act("emote tends to a nasty wound on his arm.");
    add_act("emote mumbles a prayer to Paladine for guidance.");

    set_default_answer("The injured knight says: I am sorry, I know little of this " +
      "wretched area, " +
      "so cannot help you with that. \n");

    add_ask(({"help","task","quest"}),VBFC_ME("quest_hint"),1);
    add_ask("fight","say While searching for information on a lost " +
      "family heirloom, I ran afoul of a group of draconians. " +
      "Although they all died by my blade, I took some injuries.",1);
    add_ask("injuries","say I have seen knights take worse injuries " +
      "and not even flinch. I should survive.",1);
    add_ask(({"heirloom","family heirloom"}),"say It is a blade " +
      "of fine make. It was taken from the corpse of my brother " +
      "who died on the field of battle, cruelly slain by an " +
      "officer of the blue dragonarmy. For the honour of my " +
      "fallen brother and my family, I have come to get it " +
      "back.",1);
    add_ask("draconians","say Creatures from my nightmares they are, " +
      "half lizard, and half human. Their hearts are as black as night, and from " +
      "what I have heard, they are not of this world!",1);
    add_ask("officer","say My brother challenged the officer " +
      "to combat, yet the coward refused, attacking him on his great " +
      "blue dragon. My brother had no chance.",1);
    add_ask("brother","say He was my older brother. He lived " +
      "and died a true Knight of Solamnia, fighting " +
      "for the freedom of those unable to protect " +
      "themselves.",1);
    add_ask("blade","say It was a blade forged back during " +
      "the reign of Vinas Solamnus. The blades were given " +
      "to his officers, and have been passed down from " +
      "generation to generation",1);
    add_ask(({"knight","knights"}),"say There is a covert Circle of the Knighthood just " +
      "outside the gates of Flotsam in the forest.",1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

}

string
quest_hint()
{
    command("emote holds his head high with pride.");
    command("say I shall not ask for help in my quest. My " +
      "honour does not allow for charity, but thank you " +
      "anyway.");

    return "";
}
void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP)->move(TO);
    clone_object(ARM)->move(TO);
    command("wear all");
    command("wield all");
}


void
calculate_experience(object who)
{
    int xp_base = 1500;

    if (who->test_bit("ansalon", 0, 10))
    {
	who->catch_msg("Nice job, but no experience second time.\n");

	return;
    }

    xp_base -= (who->query_prop(PLAYER_I_KILLED_KERNAN) ? 0 : 1000);

    who->catch_msg("You feel more experienced!\n");
    if (who->query_wiz_level())
    {
	who->catch_msg("xp: " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0, 10);

    A_QUEST_LOG("quest", "Wounded Knight", who, xp_base);

    return;
}


void
return_give_sword(object from)
{
    command("say Our family heirloom!");
    command("You have my thanks for retrieving " +
      "it for me.");
    command("emote salutes you in the manner of a " +
      "Knight of Solamnia.");
    command("say May the blessings of Paladine go with " +
      "you!");

    calculate_experience(from);

    command("emote limps out of the window and is gone.");
    remove_object();
}

void
give_it_back(object ob, object from)
{

    string what,
    who;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("say I will not take charity!");
    command("give " + what + " to " + who);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_flotsam_r_sword_"))
    {
	set_alarm(1.0, 0.0, &return_give_sword(from));
	return;
    }

    if(ob->id("platemail"))
    {
	return;
    }

    if(ob->id("_long_sword_"))
    {
	return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}

int
query_hp()
{
    int my_hp = ::query_hp(); 
    if(my_hp > 300)
	heal_hp(300 - my_hp);
    return ::query_hp();
}

void
init_living()
{
    ::init_living();
}
