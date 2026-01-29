/* 
 * /d/Gondor/minas/npc/denethor_noquest.c  
 *
 * Denethor II, Steward of Gondor - pre fall of Isengard
 *
 * Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include "/d/Gondor/minas/lib/porter_defs.h"

#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void  give_key();
int          query_disallow_mercy(object ob);


object guard, actor, *inv;

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj("sharp-eyed");
    add_adj("old");
    set_name("Denethor");
    set_pname("humans");
    add_name("human");
    add_name("steward");
    add_name("dunadan");
    add_name("denethor");
    set_race_name("human");
    set_title("II, Son of Ecthelion, Lord and Steward of Minas Tirith");

    set_long("This is the ruling Lord and Steward of the city. His carven "
        + "face with its proud bones and skin like ivory, and the long "
        + "curved nose between deep dark eyes, remind you of a King, and "
        + "yet he but holds the city in the King's stead. He is old, but "
        + "very proud, and wise; he can see things lesser men cannot. "
        + "Beware his keen gaze, for it is said he can often find things "
        + "which his supplicants would rather keep hidden. In his lap "
        + "rest two halves of a cloven wild-ox horn on either side of a "
        + "short white rod.\n");

    rnd = random(60);
    default_config_npc(150+rnd/2);
    set_base_stat(SS_DIS, 150 + rnd);
    set_alignment(300+rnd*10);

    set_gender(0);
    set_skill(SS_WEP_SWORD,100+random(10));
    set_skill(SS_DEFENCE,100+random(10));
    set_skill(SS_PARRY,100+random(10));

    add_prop(LIVE_I_NON_REMEMBER, 1);

    set_chat_time(10);
    add_chat("Dark indeed is the hour.");
    add_chat("All the signs forbode that the doom of Gondor is drawing nigh.");
    add_chat("Yea, though the Stones be lost, they say, still the lords "
        + "of Gondor have keener sight than lesser men, and many messages "
        + "come to them.");
    add_chat("I am old, but not yet dotard. I can see and hear, and little "
        + "is hidden from me!");
    add_chat("Where will other men look for help, if Gondor falls?");
    add_chat("Should even the House of the Stewards fail, mean folk shall "
        + "rule the last remnant of the Kings of Men, lurking in the hills "
        + "until all are hounded out.");
    add_chat("Ah, but for the ways that were. But if doom must deny me such, "
        + "then I will have naught: neither life diminished, nor love "
        + "halved, nor honour abated.");


    set_act_time(9);
    add_act("emote smiles, like a gleam of cold sun on a winter's evening.");
    add_act("emote stares at you, his eyes flashing suddenly.");
    add_act("emote relaxes and grows cold.");
    add_act("emote looks at you silently.");
    add_act("emote scans the great hall, a glint of madness in his eyes.");
    add_act("emote suddenly laughs.");
    add_act("frown");
    add_act("rap rod");
    add_act("peer thoughtfully rod");

    set_cact_time(2);
    add_cact("emote shouts: You dare to assault the Lord of the city?");
    add_cact("emote shouts: Begone, ere your own doom finds you!");
    add_cact("emote swings his white rod through the air in a sweeping arc.");
    add_cact("emote giggles with glee.");

    set_default_answer( ({ "say Excuse me?", "cough incoherently" }) );

    add_ask_item(({"key", "for key", "door"}), "@@give_key");
    add_ask_item(({"reward", "for reward", "about reward"}), "say Go see "
        + "Hunthor if you want such things! Do not trouble me!");

    add_ask_item(({"signs", "doom", "gondor", "Gondor"}), "say The days of "
        + "Gondor are numbered. Alas, if only it had come here, to me...");
    add_ask_item(({"boromir", "Boromir"}), "say My eldest son Boromir is the "
        + "best of Men. He left for Imladris some while back.");
    add_ask_item(({"faramir", "Faramir"}), "say Faramir, oh Faramir! He follows "
        + "that fool Mithrandir like a dog sniffing for scraps.");
    add_ask_item(({"horn", "cloven horn", "ox horn", "wild-ox horn"}), "say It "
        + "is now carried by my eldest son Boromir, the best of Gondor.");
    add_ask_item(({"stone", "stones", "palantir", "palantari"}), "say What "
        + "do you know of them? Do not concern yourself with things that "
        + "are beyond you. Such things would only teach you despair.");
    add_ask_item(({"rod", "white rod"}), "say I hold the rod and rule until the "
        + "King should come again. Alas the kings are all dead, and even "
        + "the House of Stewards is failing.");
    add_ask_item(({"sword", "longsword"}), "say This is the sword of Hurin. Do "
        + "not think me such an old dotard that I know not its use.");



    clone_object(INNER_MINAS + "/obj/white_rod")->move(TO);
    clone_object(INNER_MINAS + "/obj/hurin_sword")->move(TO);
    clone_object(INNER_MINAS + "/obj/denethor_robe")->move(TO);
    clone_object(INNER_MINAS + "/obj/new_throne_stair_key")->move(TO);


    command("wear all");
    command("wield sword");

    refresh_mobile();

}

public void
return_bow(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(2))
    {
    case 0:
        command("bow solemnly");
	       break;
    case 1:
        command("bow grim");
    default:
        break;
    }
}


public void
return_smile(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        command("say How interesting that you can smile when the doom "
            + "of Gondor is at hand.");
        command("scowl . " + actor->query_real_name());
        break;
    case 1:
        command("poke . "+ actor->query_real_name());
        command("say What do you have to smile about, stranger?");
        break;
    case 2:
        command("scowl . " + actor->query_real_name());
        command("say You mock me with your smile.");
        break;
    default:
        break;
    }
}

public void
return_grin(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
  	 return;

    switch (random(3))
    {
    case 0:
        command("say In the coming storm your skull may well grin for "
            + "eternity.");
        command("sigh .");
	       break;
    case 1:
	       command("peer . " + actor->query_real_name());
	       break;
    case 2:
        command("say In these evil times what can there be worth grinning "
            + "over?");
	       command("growl .");
	       break;
    default:
        break;
    }
}

public void
emote_hook(string emote, object actor, string adverb = "")
{
    if (!objectp(actor) || !interactive(actor))
        return 0;

    switch (emote)
        {
        case "smile":
	           set_alarm(2.0, 0.0, &return_smile(actor));
	           break;
        case "grin":
	           set_alarm(2.0, 0.0, &return_grin(actor));
	           break;
        case "bow":
            set_alarm(2.0, 0.0, &return_bow(actor));
            break;
    }
}


void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}

void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;

    set_alarm(2.0, 0.0, "sit_down", victim);
}

string
sit_down()
{
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
        return "";

    if (TP->query_wiz_level())
    {
        command("say Welcome to the White Tower, Wizard.");
        command("bow " + TP->query_real_name());
        command("sit chair");
        
    }
    else
    {
        command("say Who are you? I have little time or patience "
            + "for idle banter.");
        command("sit chair");
    }
    return "";
}


string
give_key()
{
    if (TP->query_wiz_level())
    {
        command("say But of course, Wizard.");
        command("bow");
        command("give key to " + TP->query_real_name());
        clone_object(INNER_MINAS + "/obj/new_throne_stair_key.c")->move(TO);
        
    }
    else
    {
        command("peer" + TP->query_real_name());
        command("say You have no business there. Begone!");
    }
    return "";
}

int 
query_disallow_mercy(object ob)
{
      return 1;
}

void
do_die(object killer)
{
    setuid();
    seteuid(getuid());

    guard = clone_object(INNER_MINAS + "/npc/throne_room_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/throne_room_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/throne_room_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/throne_room_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/throne_room_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/throne_room_guard");
    guard->move(ENV(TO));

    tell_room(ENV(TO), "With a gasp, the Steward falls to the ground and "
        + "chokes out a last breath.\n");

    command("say A curse upon you and all your House!");    
    command("give key to sixth guard");
    command("give sword to sixth guard");
    command("give rod to sixth guard");

    ::do_die(killer);
}


public int
query_knight_prestige() { return -80; }



