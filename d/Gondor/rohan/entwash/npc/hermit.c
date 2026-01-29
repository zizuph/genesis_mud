/*
 *  /d/Gondor/rohan/entwash/npc/hermit.c
 *
 *  The quest npc for the Entwash area
 *
 *  Coded by Gorboth, October 1995
 *
 *  Special thanks to: Jeremiah
 */
inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/common/lib/binbit.h"
#include "/d/Gondor/morgul/quest/din/din_defs.h"

#define GONDOR_I_LARVAE_QUEST      "_gondor_i_larvae_quest"

// Prototypes:
void  react_dally();

// Global Variables:
int     tell_alarm,
        tell_stage = 0;
object  quester;

void
create_monster()
{
    int rnd1 = random(20);
    int rnd2 = random(20);

    set_name("hermit");
    set_race_name("human");
    set_adj(({"old", "miserable"}));

    set_short("old miserable hermit");
    set_long("While clearly human, this hermit is a terribly"
      + " filthy and wretched individual. So old and bent is he"
      + " that it would not be difficult at all to mistake him for an"
      + " orc from a distance. Perhaps he has something to say to"
      + " those who would listen.\n");

    default_config_npc(60 + rnd1);
    set_base_stat(SS_INT, 80 + rnd1);

    set_skill(SS_WEP_CLUB, 70);
    set_skill(SS_DEFENCE,  80);
    set_skill(SS_AWARENESS,70);
    set_skill(SS_BLIND_COMBAT, 80);
    set_alignment(-400);

    set_chat_time(10);
    add_chat("Curse that beacon attendant!");
    add_chat("The Warden thinks I am worthless, but I'll show him!");
    add_chat("Infernal insect! Quit buzzing in my ear!");
    add_chat("Guards... guards everywhere! Wretched hilltop.");

    set_cchat_time(3);
    add_cchat("Curse you, you bastard! You'll not have me!");
    add_cchat("My friends from the East will roast you for this!");
    add_cchat("I will defile your corpse soon enough, wretch!");

    set_act_time(10);
    add_act("emote slaps himself suddenly, as if to fend off a fly.");
    add_act("cough");
    add_act("peer bitt");

    set_cact_time(5);
    add_cact("growl");
    add_cact("peer desp");
    add_cact("scowl bitt");

    // better than: add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"job","help","task","quest","about job","about help",
            "about task","about quest","for job","for task",
            "for help","for quest"}),
        VBFC_ME("mosquito_inform"));
    add_ask(({"mosquito","mosquitos","bug","bugs","about mosquito",
            "about mosquitos","about bug","about bugs"}),
        VBFC_ME("pool_inform"));
    add_ask(({"attendant","beacon attendant", "about attendant",
            "about beacon attendant"}),
        VBFC_ME("attendant_inform"));
    add_ask(({"amon din","hilltop","about amon din","about hilltop"}),
        VBFC_ME("din_inform"));
    add_ask(({"warden","tower warden","about warden",
            "about tower warden"}),
        VBFC_ME("warden_inform"));
    add_ask(({"minas morgul","about minas morgul"}),
        VBFC_ME("morgul_inform"));
    add_ask(({"assignment","about assignment","your assignment",
            "about your assignment"}),
        VBFC_ME("assignment_inform"));
    add_ask(({"grubb","grubbs","about grubb","about grubbs"}), 
        VBFC_ME("ask_grubb"));

    FIX_EUID
}

void
react_nazgul(object who)
{
    if (!CAN_SEE(TO, who))
    {
        return;
    }

    switch(who->query_nazgul())
    {
        case 2:
            command("gasp");
            command("say Turulairi!");
            command("emote turns pale and backs away slightly.");
            command("say Be merciful my King! I am working as fast as"
                + " I am able!");
            command("grovel " + who->query_real_name());
            break;
        case 1:
            command("say By Udun, one of the Nine has come to call!");
            command("emote turns pale and backs away slightly.");
            command("say Master, be merciful!");
            break;
        case 0:
            break;
    }
}

void
init_living()
{
    ::init_living();

    set_alarm(1.0, 0.0, "react_nazgul", TP);
}

string
default_answer()
{
    command("glare sil " + TP->query_real_name());
    command("say I neither know nor care about that!");
    return "";
}

string
attendant_inform()
{
    command("peer quick");
    command("say The beacon attendant!");
    command("spit");
    command("say How do you know about him?");
    command("say Have you been atop Amon Din?");
    command("say That fool has ruined all of my attempts...");
    command("frown");
    command("say I warn you, the beacon attendant is no one to fool with!");
    return "";
}

string
morgul_inform()
{
    command("sigh bitt");
    command("say The City of Dark Sorcery...");
    command("say I can't wait to return!");
    command("ponder his seemingly difficult situation");
    command("say But I don't dare to return until I have completed my assignment.");
    return "";
}

string
assignment_inform()
{
    command("say What do you care about that for?");
    command("say Now quit asking me questions and go away!");
    command("cough pain");
    return "";
}

void
grubb_inform(string name)
{
    object  pl;

    if (!present(pl = find_player(name), ENV(TO)))
        tell_stage = 999;

    switch(tell_stage)
    {
        case 0:
            command("say So, the Warden has sent you to check on my"
             + " progress, has he?");
            break;
        case 1:
            command("say Well, he will not be disappointed.");
            break;
        case 2:
            command("say North of my hut are noxious fens which extend"
              + " some distance before meeting with the Anduin.");
            break;
        case 4:
            command("say Many horrible things have I found there, but"
              + " among them is a very special kind of grubb.");
            break;
        case 6:
            command("say Black to the core it is, and its hunger is"
              + " insatiable!");
            break;
        case 9:
            command("say It feeds on wood... any kind of wood, and it"
              + " drains the many liquids and oils contained in the"
              + " pulp.");
            break;
        case 13:
            command("say Surely this creature is spawned from some"
              + " enchantment, for a handfull of them can drain a full"
              + " grown tree trunk in mere minutes!");
            break;
        case 15:
            command("say If you fully wish to please the Warden, these"
              + " creatures are your only option.");
    // Do not use TP in a function called by an alarm!
    // It is not well-defined!
            pl->add_prop(DIN_I_GET_GRUBB, 1);
            break;
        case 17:
            command("say Now listen closely!");
            break;
        case 20:
            command("say We do not want to alert the Gondorian guards"
              + " to the fact that they have been sabotaged, and that"
              + " is the beauty of these worms.");
            break;
        case 22:
            command("say They leave the wood whole, but drained.");
            break;
        case 25:
            command("say The only difference in appearance is that the"
              + " wood is left an ash-grey colour once the grubbs have"
              + " feasted.");
            break;
        case 27:
            command("say The beacon tower will be left with false fuel"
              + "- apparently normal, but unburnable!");
            break;
        case 29:
            command("cackle");
            break;
        case 31:
            command("say You are going to have a difficult time finding"
              + " them.");
            break;
        case 33:
            command("say They have already killed most of the trees"
              + " in the swamp, and move very quickly.");
            break;
        case 35:
            command("peer doubt " + pl->query_real_name());
            break;
        case 37:
            command("say Return to me with one of these grubbs, and"
              + " I will tell you what to do next.");
            break;
        case 38:
        case 999:
            remove_alarm(tell_alarm);
            tell_alarm = 0;
            quester = 0;
            tell_stage = 0;
            break;
        default:
            break;
    }
    tell_stage++;
    return;
}

void
react_grubb(string name)
{
    object  pl;

    if (!present(pl = find_player(name), ENV(TO)))
        tell_stage = 999;

    switch(tell_stage)
    {
        case 0:
            command("exa grubb");
            break;
        case 1:
            command("say Well now!");
            break;
        case 3:
            command("say I see that you have managed to locate one"
              + " of these little nasties... impressive!");
            break;
        case 5:
            command("say The next step is to locate the pathway which"
              + " leads up to Amon Din.");
            break;
        case 7:
            command("say This will be difficult, so I certainly hope"
              + " you have some skill in tracking!");
            break;
        case 9:
            command("say Following the Great West Road southeast from"
              + " the gates of Edoras will eventually bring you near"
              + " to the Druadan forest.");
            break;
        case 11:
            command("say Be on the lookout for a tall hilltop, because"
              + " that will let you know you are close to the trail.");
            break;
        case 13:
            command("say Those blasted Gondorians have hidden it well,"
              + " so it may take you a bit of doing to find it!");
            break;
        case 15:
            command("say Once you do, then it is up to you to get past"
              + " all those fools on the summit.");
            pl->add_prop(DIN_I_SENT_PATH, 1);
            break;
        case 17:
            command("swear angr");
            break;
        case 19:
            command("say And watch out for that damn beacon attendant!");
            break;
        case 20:
            command("fume bitt");
            break;
        case 21:
            command("say In any case, the fuel is stored up there"
              + " somewhere, I know it!");
            break;
        case 23:
            command("say There is probably a big stack of firewood"
              + " hidden away under guard.");
            break;
        case 25:
            command("say When you do find the fuel, just put that"
              + " grubb on it, and watch it go to work!");
            break;
        case 27:
            command("say Knowing the Warden, he will want to see some"
              + " sort of proof that you have done your job properly.");
            break;
        case 30:
            command("grin " + pl->query_real_name());
            break;
        case 32:
            command("say I can't think of anything else to tell you,"
              + " so hurry off and get this over with... ");
            break;
        case 34:
            command("say The sooner you finish this, the sooner we can"
              + " both sleep easy!");
            break;
        case 35:
        case 999:
            remove_alarm(tell_alarm);
            tell_alarm = 0;
            quester = 0;
            tell_stage = 0;
            command("give grubb to "+pl->query_real_name());
            break;
        default:
            break;
    }
    tell_stage++;
    return;
}

string
din_inform()
{
    string  name = TP->query_real_name();

    command("peer " + TP->query_real_name());
    command("say The hilltop of Amon Din?");
    command("grumble");

    if (TP->query_prop(DIN_I_SENT_PATH))
    {
        command("frown");
        set_alarm(1.0, 0.0, &react_dally());
        return "";
    }

    if (TP->query_prop(DIN_I_GET_GRUBB))
    {
        command("say Didn't I tell you what you need to do?");
        command("say Bring me one of those black grubbs from the swamp!");
        return "";
    }

    if (TP->query_prop(DIN_I_SENT_TO_HERMIT))
    {
        quester = TP;
// Never, _ever_, set a repeating alarm without checking if it is already active!
        if (!tell_alarm || !sizeof(get_alarm(tell_alarm)))
            tell_alarm = set_alarm(1.0, 2.0, &grubb_inform(name));
        return "";
    }

    command("say I won't talk to you about that!");
    command("say If you want to get involved, you had better go and talk to the warden in Minas Morgul.");
    command("say He used to spend most of his time in the Tower of Dark Sorcery.");
    command("emote shudders suddenly.");
    command("say But don't tell him I sent you!");
    command("say And watch out for the Society members!");
    command("say Now go away, I don't want to speak to you anymore!");
    return "";
}

string
warden_inform()
{
    if (TP->query_prop(DIN_I_SENT_TO_HERMIT))
    {
        command("say The way you ask makes me suspicious!");
        command("say What do you want from me?");
        command("peer grim"+TP->query_name());
        return "";
    }

    command("emote frowns darkly.");
    command("say Why do you speak of such things?");
    command("say It is perfectly obvious that you have not been to see him.");
    command("say Now go away!");
    return "";
}

string
mosquito_inform()
{
    command("peer doubt " + TP->query_real_name());
    command("say Bah, you don't look capable of anything useful!");
    command("grumble");
    command("say Blast these wretched mosquitos!");
    return "";
}

string
pool_inform()
{
    if (TP->test_bit("Gondor", ENTWASH_LARVAE_GROUP,
                               ENTWASH_LARVAE_BIT))
    {
        command("say What?");
        command("peer " + QCTNAME(TP) + ".");
        command("say You've fixed those beasts already, I checked!");
        command("say You can play in the puddles till you drown for");
        command("say all I care.");
        command("spit");

        return "";
    }

    if (TP->query_prop(GONDOR_I_LARVAE_QUEST))
    {
        command("scowl angr");
        command("say I told you what to do. Go do it!");

        return "";
    }

    command("say Hmmm... well if you want to help, I won't stop you!");
    command("say Somewhere in these swamps there is sure to be a");
    command("say large pool where these vermin breed. It is sure to");
    command("say be covered with the larva of these beasts. I usually");
    command("say keep morgurth on hand to throw into the pool. It");
    command("say kills them right off! I've looked everywhere, and");
    command("say I've run clean out of blossoms! Go find some");
    command("say morgurth! Throw it in the pool if you can find it!");
    command("spit");
    command("say And be quick about it!");

    TP->add_prop(GONDOR_I_LARVAE_QUEST, 1);
    START_QUEST(TP, "ENTWASH LARVAE");
    return "";
}

string
ask_grubb()
{
    if (TP->query_prop(DIN_I_SENT_PATH))
    {
        command("say I gave it back to you!");
        command("say Put it on the firewood you find at Amon Din!");
        command("frown");
        react_dally();
        return "";
    }

    if (TP->query_prop(DIN_I_GET_GRUBB))
    {
        command("say Did you find one yet?");
        command("say If not, keep looking, you will need one!");
        command("spit");
        return "";
    }

    command("say Grubbs?");
    command("say This swamp is full of 'em!");
    command("cough");
    command("say And what do you care?");
    command("peer " + TP->query_real_name());

    return "";
}

void
arm_me()
{
    FIX_EUID

    clone_object(ENTWASH_DIR + "/obj/bone")->move(TO);
    command("wield all");
}

void
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("say What!? Who's there?");
        return;
    }

    command("say Bah! I haven't got any use for names...");
}

public void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;
    set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(TP));
}

void
return_object(object obj, object to)
{
    string  name = TP->query_real_name(),
            obname = OB_NAME(obj);

    if (obj->id("coin"))
    {
        command("cackle");
        command("say I'll keep that!");
        return;
    }

    if (obj->id("grubb"))
    {
        if (!TP->query_prop(DIN_I_GET_GRUBB))
        {
            command("say Well well, it looks like you have found one of"
              + " the Entwash's hungriest residents!");
            command("put grubb on "+name);
            command("say Oh! He likes you!");
            command("laugh "+name);
            return;
        }

        if (TP->query_prop(DIN_I_SENT_PATH))
        {
            command("give grubb to "+TP->query_real_name());
            set_alarm(1.0, 0.0, &react_dally());
            return;
        }

        quester = TP;
        if (!tell_alarm || !sizeof(get_alarm(tell_alarm)))
            tell_alarm = set_alarm(1.0, 2.0, &react_grubb(name));
        return;
    }

    command("say What? I don't want anything from you!");
    command("give "+obname+" to "+to->query_real_name());
        if (present(obname, TO))
        command("drop "+obname);
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from) || !objectp(obj) || !living(from))
        return;

    set_alarm(0.5, 0.0, &return_object(obj, from));
}

void
react_dally()
{
    command("say Quit wasting time, fool!");
    command("say Go and find Amon Din!");
}
