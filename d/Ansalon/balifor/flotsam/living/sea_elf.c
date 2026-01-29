// Navarre May 17th 2009, Removed int 50 requirement as ogres are unable to solve
//                        the quest.

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit "/std/act/action";

inherit AM_FILE

#define PLAYER_I_FOUND_SEAELF  "_player_i_found_flotsam_seaelf"
#define PLAYER_I_FOUND_WEBNET  "_player_i_found_flotsam_webnet"
#define WEP FOBJ + "weapon/spear"
#define ARM FOBJ + "armour/sskin"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("sea-elf");
    add_name("elf");
    add_name("sea elf");
    set_race_name("sea-elf");
    set_adj("blue-skinned");
    add_adj("green-eyed");
    set_gender("G_MALE");
    set_long("This blue-skinned elf with brilliant green eyes " +
      "is a creature of legends and childhood tales, a sea elf! "+
      "Rumour has it that sea-elves are generally very reclusive " +
      "around air breathers, so what this one is doing out of its beloved ocean " +
      "is quite a mystery. \n");
    set_stats(({86,110,88,90,88,77}));
    set_hp(10000);

    set_alignment(800);
    set_knight_prestige(-5);

    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 85);

    set_act_time(5);
    add_act("emote looks at the sea wistfully.");
    add_act("say Another vessel was lost at sea during the " +
      "last storm.");
    add_act("say Rumours speak of the return of the sea dragons.");

    set_default_answer("The sea elf says: I have no idea "
      + "what you are talking about.\n");

    add_ask("[sea] 'shell' / 'shells'",
      VBFC_ME("shell_hint1"), 1);
    add_ask("'rare' 'shell' / 'shells'",
      VBFC_ME("shell_hint2"), 1);
    add_ask("[pink-hued] 'conch' 'shell' / 'shells'",
      VBFC_ME("shell_hint3"), 1);
    add_ask("price", VBFC_ME("price_hint"), 1);
    add_ask("'artifact' / 'webnet'",
      VBFC_ME("artifact_hint"),1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    clone_object(WEP)->move(this_object(),1);
    command("wield all");
    clone_object(ARM)->move(this_object(),1);
    command("wear all");
}


string
shell_hint1()
{
    command("hmm");
    command("say Although the Blood Sea of Istar is young, many "
      + "sorts of sea shells can be found in the depths of these "
      + "turbulent waters.");
    command("emote motions with one hand at the sea.");
    command("say Most of the shells to be found are common, but "
      + "with a keen eye and the knowledge to look in the right "
      + "places it is possible to find rare and valuable ones.");
    command("smile know");

    return "";
}


string
shell_hint2()
{
    command("nod .");
    command("say A long time ago when the Blood Sea was nothing more "
      + "than a large inland lake, and the open waters of the oceans "
      + "were far from here, fishermen used to dive for the shells.");
    command("say Most of them did so without much luck, but "
      + "occasionally someone would surface with a rare and valuable "
      + "sea shell.");
    command("smile long");
    command("say Among the rarest of the sea shells is the pink-hued "
      + "conch shell. To most races almost impossible to find, but to "
      + "those who are wise in the ways of the seas, it is different.");

    return "";
}


string
shell_hint3()
{
    command("scratch chin");
    command("say Hmm... Rare shells those pink-hued " +
      "conch shells.");
    command("say But I should be able to get you one...");
    command("smirk");
    command("say For a price, that is.");
    command("grin cunn");

    return "";
}

string
price_hint()
{
    command("say I will get you a rare pink-hued " +
	    "conch shell if you can return to me an artifact " +
	    "of my people that was lost in this general area.");
    TP->add_prop(PLAYER_I_FOUND_SEAELF, 1);
    return "";
}

string
artifact_hint()
{
    command("emote looks at you suspiciously.");
    command("say The artifact that was lost appears to be " +
	    "a hair ornament to the ignorant. Those knowledgeable of " +
	    "my people would recognize it as a webnet.");

    return "";
}

void
return_give_webnet(object from)
{
    object cshell;

    string who,
    what;

    who  = from->query_real_name();

    command("smile");
    command("say A webnet! I shall get you that shell!");
    command("emote dives into the water, and almost immediately " +
      "returns carrying a pink conch shell!");
    command("say Here we go... and thank you!");
    cshell = clone_object(FOBJ + "shell");
    what = cshell->query_short();
    cshell->move(TO);
    command("give " + what + " to " + who);
    command("drop " + what);
    command("smile");
    command("wave");
    command("emote dives into the waters of the Bloodsea, " +
      "and disappears.");
    from->add_prop(PLAYER_I_FOUND_WEBNET, 1);

    remove_object();
}
void
give_it_back(object ob, object from)
{
    string what,
    who;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("emote sneers with contempt.");
    command("give " + what + " to " + who);
    command("say This is not what I was after!");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);


    if(ob->id("_flotsam_r_webnet_"))
    {
	set_alarm(1.0, 0.0, &return_give_webnet(from));
	return;
    }

    if (ob->id("_flotsam_c_shell_"))
    {
	return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}
