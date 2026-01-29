/* 
 * /d/Gondor/minas/npc/denethor.c  
 *
 * Denethor II, Steward of Gondor
 *
 * Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/d/Gondor/common/lib/binbit.c";
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
#include "/d/Gondor/bits.h"

#define INNER_MINAS "/d/Gondor/minas"

public void  give_key();
string       discuss_tombs();
int          query_disallow_mercy(object ob);
int          query_knight_prestige();


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
    add_chat("My Boromir! Now we have need of you. Faramir should have gone "
        + "in his stead.");
    add_chat("Each eldest son of our house, far back into the vanished years "
        + "before the failing of the kings, bore this horn.");
    add_chat("The River brought the horn borne by my son Boromir home to "
        + "me, broken: it will wind no more.");
    add_chat("Yea, though the Stones be lost, they say, still the lords "
        + "of Gondor have keener sight than lesser men, and many messages "
        + "come to them.");
    add_chat("I am old, but not yet dotard. I can see and hear, and little "
        + "is hidden from me!");
    add_chat("Stir not the bitterness in the cup that I mixed for myself. "
        + "Have I not tasted it now many nights upon my tongue, forboding "
        + "that worse lay in the dregs?");
    add_chat("Where will other men look for help, if Gondor falls?");
    add_chat("Should even the House of the Stewards fail, mean folk shall "
        + "rule the last remnant of the Kings of Men, lurking in the hills "
        + "until all are hounded out.");
    add_chat("My life is broken.");
    add_chat("Ah, but for the ways that were. But if doom must deny me such, "
        + "then I will have naught: neither life diminished, nor love "
        + "halved, nor honour abated.");


    set_act_time(9);
    add_act("emote smiles, like a gleam of cold sun on a winter's evening.");
    add_act("emote gazes sadly upon the cloven wild-ox horn in his lap.");
    add_act("show horn");
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
    add_ask_item(({"reward", "for reward", "about reward"}), "@@discuss_tombs");

    add_ask_item(({"signs", "doom", "gondor", "Gondor"}), "say The days of "
        + "Gondor are numbered. Alas, if only it had come here, to me...");
    add_ask_item(({"boromir", "Boromir"}), "say My eldest son Boromir was the "
        + "best of Men. Ah, and how he is needed now. But he is lost. "
        + "Lost... Would that I had sent Faramir in his stead!");
    add_ask_item(({"faramir", "Faramir"}), "say Faramir, oh Faramir! He follows "
        + "that fool Mithrandir like a dog sniffing for scraps. A reward "
        + "of folly is all he has earned of it.");
    add_ask_item(({"horn", "cloven horn", "ox horn", "wild-ox horn"}), "say It "
        + "came back to me, broken. Boromir! What became of thee?");
    add_ask_item(({"stone", "stones", "palantir", "palantari"}), "say What "
        + "do you know of them? Do not concern yourself with things that "
        + "are beyond you. Such things would only teach you despair.");
    add_ask_item(({"rod", "white rod"}), "say I hold the rod and rule until the "
        + "King should come again. Alas the kings are all dead, and even "
        + "the House of Stewards is ending.");
    add_ask_item(({"sword", "longsword"}), "say This is the sword of Hurin. Do "
        + "not think me such an old dotard that I know not its use.");



    clone_object(INNER_MINAS + "/obj/white_rod")->move(TO);
    clone_object(INNER_MINAS + "/obj/hurin_sword")->move(TO);
    clone_object(INNER_MINAS + "/obj/denethor_robe")->move(TO);
    clone_object(INNER_MINAS + "/obj/denethor_horn")->move(TO);
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

void
reward_tombs()
{
    string  who = TP->query_real_name();

    if (!present(who, ENV(TO)))
        return;

    if (TP->test_bit("Gondor", MTIRITH_PORTER_GROUP, MTIRITH_DENETHOR_BIT))
        return;

    MONEY_MAKE_PC(30)->move(TO);
    command("give platinum coins to " + who);

    TP->set_bit(MTIRITH_PORTER_GROUP, MTIRITH_DENETHOR_BIT);
    TP->add_exp_quest(MTIRITH_DENETHOR_EXP);
    TP->catch_msg("You feel more experienced!\n");
    TP->remove_prop(ANSWERED_ALL_RIDDLES);
    TP->remove_prop(QUESTING_FOR_BUNDLE);
    TP->remove_prop(FOUND_DENETHOR_BUNDLE);
    TP->remove_prop(QUESTING_FOR_HALLOWS);
    TP->remove_prop(DELIVERED_DENETHOR_BUNDLE);
    TP->remove_prop(SENT_TO_DENETHOR);
    LOG_QUEST(TP, MTIRITH_DENETHOR_EXP, "MTIRITH DENETHOR QUEST");
    return;
}

string
discuss_tombs()
{
    string pname;

    pname = TP->query_real_name();

    if (!TP->query_prop(SENT_TO_DENETHOR))
    {
        command("say Why are you wasting my time? I am a busy man!");
        return "";
    }


    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_DENETHOR_BIT))
    {
        TO->command("say Yes yes, I have already rewarded you and given you "
            + "my gratitude. Please leave before my welcome grows cold.");
        return "";
    }

    if (TP->query_prop(SENT_TO_DENETHOR))
    {
        command("peer carefully " + pname);
        command("say Hmm, so you have carried out my commands. Good. That "
            + "is very very good....");
        set_alarm(4.0, 0.0, &command("cackle"));
        set_alarm(8.0, 0.0, &command("say You see, that fool Mithrandir "
            + "does not know everything that I know. Not by far! Oh, and "
            + "if he did, he would know despair. Fool though he is, no "
            + "man should know the depths of despair I have found."));
        set_alarm(13.0, 0.0, &command("giggle insanely"));
        set_alarm(14.0, 0.0, &command("emote mutters to himself: They are "
            + "all fools. Ah, to be such a fool. Would that folly would "
            + "have found me before I .. before He .."));
        set_alarm(19.0, 0.0, &command("emote blinks and seems to return "
            + "his attention to the present."));
        set_alarm(20.0, 0.0, &command("smile coldly. " + pname));
        set_alarm(21.0, 0.0, &command("say Ignorance truly is bliss, my "
            + "friend. Let that be your solace in the last days before the "
            + "Storm."));
        set_alarm(26.0, 0.0, &command("emote stares at the cloven horn in "
            + "his lap and sighs deeply."));
        set_alarm(30.0, 0.0, &command("blink"));
        set_alarm(31.0, 0.0, &command("say What was it you wanted again? Ah, "
            + "yes, you wish a reward for building my funeral pyre. How "
            + "much is life of Denethor worth? Pah. Perhaps I should give "
            + "you two coppers for your troubles and send you on your way."));
        set_alarm(34.0, 0.0, &command("wink"));
        set_alarm(37.0, 0.0, &command("say Ah, but I suppose the life "
            + "of my poor Faramir is worth more than that of his wretched "
            + "sire. I am sure the fruits of your labour will suffice to "
            + "send both of us beyond the reach of ..."));
        set_alarm(41.0, 0.0, &command("shudder"));
        set_alarm(42.0, 0.0, &command("emote draws a shaking hand across "
            + "his brow."));
        set_alarm(45.0, 0.0, &command("say My apologies, Servant of the Tombs. "
            + "Such things are not your concern, and would doubtless be beyond "
            + "you if they were. Nay, do not take offence! Be thankful for "
            + "the lowly position fate has granted you. I assure you that "
            + "in my heart of hearts I would rather shovel the droppings of "
            + "horses than bear the weight of this "
            + "city in its death-throes."));
        set_alarm(50.0, 0.0, &command("sigh gravely"));
        set_alarm(53.0, 0.0, &command("cackle"));
        set_alarm(54.0, 0.0, &command("peer carefully"));
        set_alarm(56.0, 0.0, &command("say Mithrandir wants my chair, you "
            + "know. He and that upstart imposter he plans to foist upon us. "
            + "Let them have it, I say! The House of Stewards is at an end, "
            + "and all of Gondor with it. They will have nothing, I say. "
            + "Nothing!"));
        set_alarm(61.0, 0.0, &command("emote giggles softly and mutters to "
            + "himself: King of Nothing, heh."));
        set_alarm(65.0, 0.0, &command("peer " + pname));
        set_alarm(66.0, 0.0, &command("say Are you still here? Take your "
            + "reward and begone!"));
        set_alarm(67.0, 0.0, &reward_tombs());

        return "";
    }

    else
        command("say Hmm. How did you get in here?");

    return "";
}


int 
query_disallow_mercy(object ob)
{
//   if(ob->query_merciful())
//   {
      write_file(INNER_MINAS + "/lib/knight_mercy",
      TP->query_name()+" tried to use mercy on " + ctime(time()) + "\n");
      query_knight_prestige();
      M_TIRITH_MASTER->add_enemy(ob);
      return 1;
//   }
//   return 0;
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
query_knight_prestige() { return -4500; }



