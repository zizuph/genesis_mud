/*
 *	/d/Gondor/common/guild2/newnpc/azrubel.c
 * 
 *	Copied from /d/Gondor/morgul/npc/ithil_wraith.c
 *	Olorin, July 1994
 *
 *	Modification log:
 *	Gorboth: added support for Amon Din quest, December 1995
 *      Mercade: Undid general support for processing loot, November 1997
 *      Morbeche: Edited security loading stuff, changed all references
 *                of mhiss to hiss,  Feb 2000
 *  Toby, 23-Sept-2007: Added support to reply on being asked about the Beastiary.
 *  Eowul, 26-Mar-2009: Added living name so he can be targeted using palanquendo
 *  Finwe, May 2020: Reformatted text and added evil versions of MT and Pelargir
 *                   tours and quests
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/newnpc/npc_mage.c";

#include <cmdparse.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"
#include "/d/Gondor/morgul/quest/din/din_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", MORGUL_DIR + "obj/wraith_mace", MORGUL_DIR + "obj/halberd"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/platemail"})
/* He can conveniently only have 3 armour pieces, so I'd rather him */
/* have both gloves and boots rather than a helm - Morbeche */
/*
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/platehelm"})
*/
#define ARM_ARRAY2 ({ GUILD_DIR + "obj/morgul_boots" })
#define ARM_ARRAY3 ({ GUILD_DIR + "obj/morgul_gloves" })

#define OBJ_I_MORGUL_WARDEN	"_obj_i_morgul_warden"

/*
 * Prototypes
 */

static string  ask_standard();
static string  ask_beacon();
static void    whisper_react(string name);
static void    whisper_react_din(string name);
static void    whisper_fail();
public void    store_loot();

static varargs void    do_intro(object tp);

/*
 * Global variables
 */
int     whisper_stage = 0,
hook_alarm,
whisper_alarm,
store_alarm;
object  quester;
string  name_key,
whisper_flag,
home;

static int     intro_id = 0;


void
create_mage()
{
    int     rnd;

    seteuid(getuid());

    set_name( "human" );
    set_living_name( "azrubel" );
    add_name("azrubel");
    remove_adj( ({"dark-skinned", "red-eyed"}) );
    add_adj(({"dark", "tall", "terrible", "undead"}));
    set_title("the Warden of the Tower");
    remove_prop( LIVE_I_NEVERKNOWN );

    set_long("This is Azrubel, the Warden of the Tower. He is a " +
        "dark towering shape with eyes glowing like coal. The Warden " +
        "is one of the servants of the Dark Lord, ages ago a mighty " +
        "warrior, but now he is undead, not a living man anymore, but " +
        "not one of the mighty Nazgul. His duty is to protect the " +
        "Tower of Morgul. Occasionally, he will also help others in " +
        "the service ot helping the Dark Lord. If you dare ask, he " +
        "may deign to give you a tour or quest.");

    rnd = random(15);
    default_config_npc(150+rnd);
    set_base_stat(SS_INT,160+rnd);
    set_alignment(-600-rnd*10);
    set_skill(SS_WEP_POLEARM, 95+rnd);
    set_skill(SS_WEP_AXE , 95+rnd);
    set_skill(SS_WEP_CLUB, 95+rnd);
    set_skill(SS_PARRY,    95+rnd);
    set_skill(SS_DEFENCE,  95+rnd);
    set_skill(SS_SPELLCRAFT,  95+rnd);
    set_skill(SS_FORM_ENCHANTMENT,  95+rnd);
    set_skill(SS_FORM_CONJURATION,  95+rnd);
    set_skill(SS_FORM_TRANSMUTATION,  95+rnd);
    set_skill(SS_ELEMENT_DEATH,  95+rnd);
    set_skill(SS_ELEMENT_AIR,  95+rnd);
    set_skill(SS_ELEMENT_FIRE,  95+rnd);
    add_prop(CONT_I_HEIGHT,205+rnd);
    add_prop(CONT_I_WEIGHT,69000+rnd*200);
    add_prop(CONT_I_VOLUME,69000+rnd*200);    
    add_prop(LIVE_I_SEE_DARK,10);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop("_ranger_i_not_brawl",1);

    set_chat_time(15+random(15));
    add_chat("Lugburz wants it, you will do it!");

    set_cchat_time(5+random(10));
    add_cchat("You little land-rat!");
    add_cchat("Dirty spy, take this!");

    set_act_time(15+random(15));	

    set_cact_time(2+random(2));
    add_cact("mhiss"); 
    add_cact("growl"); 
    add_cact("@@emote_enemy|snarl"); 

    set_tell_active(1);

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"quest", "help", "job", "for quest", "for help", "for job",
	"about quest", "about help", "about job", "tour", "for tour"}), 
        VBFC_ME("ask_help"));
    add_ask(({"standard", "flag" }), VBFC_ME("ask_standard"));
    add_ask(({"key", "tower key"}), VBFC_ME("ask_key"));
    add_ask(({"amon din","hilltop","beacon tower","beacon"}),
      VBFC_ME("ask_hilltop"));
    add_ask(({"servant","servants"}), VBFC_ME("ask_servant"));
    add_ask(({"mouths of the entwash","mouth of the entwash"}),
      VBFC_ME("ask_mouths"));
    add_ask(({"beastiary", "morgul beastiary" }), VBFC_ME("ask_beastiary"));
}

int     query_knight_prestige() { return  (- query_alignment()); }
/*
string
query_nonmet_name()
{
    return implode(({query_adjs()[0], query_adjs()[1]})," ") + " " +
    query_real_name();
}
*/
void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
    Arm3 = ARM_ARRAY3;

    home = file_name(ENV(TO));
}

void
do_attack(object target)
{
    if (objectp(query_attack()) || !CAN_SEE(TO, target))
	    return;

    if (!F_DARE_ATTACK(TO, target))
    {
        command("snarl " + target->query_real_name());
        target->catch_msg(QCTNAME(TO) + " aims at you with his " +
          "weapon, but he doesn't dare to attack you.\n");
        say(QCTNAME(TO) + " aims at "+QTNAME(target)+" with his weapon, "+
          "but doesn't dare to attack.\n");
        return;
    }
    command("shout Die, you miserable maggot!");
    command("kill " + target->query_real_name());
    return;
}

int
query_answer(object pl)
{
    switch(query_feeling(pl))
    {
        case 1:
            set_alarm(0.5, 0.0, &do_attack(pl));
            return 0;
            break;
        case 0:
            command("hiss Leave before I kill you!");
            command("kick " + pl->query_real_name());
            command("spit " + pl->query_real_name());
            return 0;
            break;
        case -1:
        default:
            return 1;
            break;
    }
}

string
default_answer()
{
    object  tp = TP;
    string  name = TP->query_real_name();

    if (!query_answer(tp))
	    return "";

    command("glare " + name);
    command("hiss What do you want, you wretched " + tp->query_race_name() + "?");
    command("hiss I might be able to help you, if you ask for it!");
    return "";
}

string
ask_mouths()
{
    if (TP->query_prop(DIN_I_SENT_TO_HERMIT))
    {
        command("hiss The Mouths of the Entwash?");
        command("ponder");
        command("hiss East of Edoras... yes, that is right.");
        command("hiss Now get going!");
        return "";
    }

    if (TP->query_nazgul())
    {
        command("hiss The Mouths of the Entwash?");
        command("hiss They are East of Edoras, Sire.");
        command("bow sil " + TP->query_real_name());
        return "";
    }

    command("say What?");
    command("hiss I do not give geography lessons!");
    command("hiss Now get out of my sight, you wretch!");
    return "";
}

string
ask_servant()
{
    if (TP->query_prop(DIN_I_SENT_TO_HERMIT))
    {
	command("hiss The servant is somewhere in the region known as"
	  + " the Mouths of the Entwash.");
	command("hiss So get going!");
	return "";
    }

    if (TP->query_nazgul())
    {
        command("hiss Yes my master, I am yours to command!");
        command("emote bows solemnly.");
        return "";
    }

    command("hiss What is this talk?");
    command("hiss All shall be servants unto the power of our Dark"
      + " Lord!");
    command("exalt");
    return "";
}

string
ask_hilltop()
{
    if (!TP->query_prop(DIN_I_SENT_TO_HERMIT))
    {
        command("peer " + TP->query_real_name());
        command("hiss What's that?");
        command("hiss What do you know of such things?");
        command("hiss Unless you feel that you are worthy of tasking,"
          + " then I suggest you get you pathetic hide out of my"
          + " sight!");
        command("sneer " + TP->query_real_name());
        return "";
    }

    if (TP->test_bit("Gondor", AMON_DIN_FIREWOOD_GROUP,
	    AMON_DIN_FIREWOOD_BIT))
    {
        command("hiss What's that?");
        command("hiss You have already done your part in that task!");
        command("hiss Make yourself useful some other way, like removing"
          + " your foolish self from my presence!");
        command("sneer " + TP->query_real_name());
        return "";
    }

    command("hiss Well, have you done what I have commanded or not?");
    command("hiss Have you some proof of your success?");

    if (TP->query_nazgul())
    {
        command("hiss My Lord, the sooner you succeed, the sooner I"
          + " will reward you.");
        command("bow humb " + TP->query_real_name());
        return "";
    }

    command("manger " + TP->query_real_name());
    command("hiss Get on with it, fool!");
    return "";
}

string 
ask_help()
{
    object  tp = TP;
    string  name = tp->query_real_name();

    if (!query_answer(tp))
	    return "";

    command("hiss Hmm, you are looking for a job?");
    command("peer " + name);

    if (!tp->test_bit("Gondor", AMON_DIN_FIREWOOD_GROUP, AMON_DIN_FIREWOOD_BIT))
    {
        ask_beacon();
        return "";
    }

    if (!tp->test_bit("Gondor", MORGUL_GROUP, ANGMAR_STANDARD_BIT))
    {
        ask_standard();
        return "";
    }

    command("hiss I've no use for you!");
    command("hiss Come back later, though.");
    command("hiss We might be able to find some work for you!");
    return "";
}

void
remove_mage_hook()
{
    quester = 0;
    whisper_flag = 0;
    command("hiss Well, if you don't know the name, then be gone, fool!");
}

string
ask_standard()
{
    object  tp = TP;
    string  name = TP->query_real_name();

    if (!query_answer(tp))
	    return "";

    if (tp->test_bit("Gondor", MORGUL_GROUP, ANGMAR_STANDARD_BIT))
    {
        command("hiss Be gone! That's ancient history!");
        return "";
    }

    if (tp->query_prop(BSW_I_SENT_TO_YRCHOR))
    {
        command("hiss But I already told you all I know!");
        command("hiss Go and find Yrchor! And stop bothering me!");
        command("glare "+name);
        return "";
    }

    if (objectp(quester))
    {
        command("hiss Come back later!");
        command("hiss I am busy right now!");
        return "";
    }

    command("cackle");
    command("hiss Do you know the name our Master, the King of Morgul, " +
      "used when he was fighting in the North, many centuries ago?");
    command("hiss If you know the name, then whisper it!");
    quester = tp;
    whisper_stage = 0;
    whisper_flag = "angmar";
    hook_alarm = set_alarm(60.0, 0.0, remove_mage_hook);

    return "";
}

static string
ask_beacon()
{
    object  tp = TP;
    string  name = tp->query_real_name();

    if (!query_answer(tp))
	    return "";

    if (tp->test_bit("Gondor", AMON_DIN_FIREWOOD_GROUP, AMON_DIN_FIREWOOD_BIT))
    {
        command("hiss Bah, you would have me assign you the same task"
          + " twice?");
        command("glare "+name);
    }

    if (tp->query_prop(DIN_I_SENT_TO_HERMIT))
    {
        command("hiss You have been told what to do!");
        command("hiss Seek out the servant of Morgul in the Mouths"
          + " of the Entwash!");
        command("mrasp at "+name);
        return "";
    }

    if (objectp(quester))
    {
        command("hiss One at a time!");
        command("hiss Can you not see I am busy?");
        return "";
    }

    command("hiss I require proof of your loyalty before I will"
      + " allow you to undertake anything important.");
    command("hiss Long ago, the ancient Lord of Darkness who has"
      + " passed from the world built a mighty fortress, in which many"
      + " of the accursed Elves found enslavement and death.");
    command("hiss Though it is long since destroyed, its memory is"
      + " a proud one, and if you know its name, 'whisper' it to me"
      + " now!");
    quester = tp;
    whisper_stage = 0;
    whisper_flag = "angband";
    hook_alarm = set_alarm(60.0, 0.0, remove_mage_hook);

    return "";
}

string
ask_beastiary()
{

    if(TP->query_morgul_level() > 12)
    {  
        if (TP->query_nazgul())
        {
            command("rasp Yes my master, of course, I am yours to command!");
            command("emote bows solemnly.");
            command("rasp The beastiary you say...");
        }
        else
        {
            command("rasp The beastiary you query about, very well.");
        }

        command("msmile");
        command("rasp By rasping the command word Panta Assa you will ascend " +
                "unto the roof of the Tower.");
        command("rasp The same words are used to descend back into the Tower.");
        command("exalt");
        return "";
    }
    else if(TP->query_morgul_level())
    {
        command("rasp Such things are not for a mere Apprentice to receive " +
                "information about.");
        return "";
    }

    command("hiss What are you talking about, fool?");
    return "";
}

public int
check_whisper(string arg)
{
    object  tp = TP,
    *target;
    string  name = tp->query_real_name(),
    str,
    dummy;

    if (!strlen(arg) || !strlen(whisper_flag))
	    return 0;

    if (quester != tp)
	    return 0;

    arg = LOW(arg);
    if (!parse_command(arg, ENV(TO), " [to] [the] %l %s ", target, str))
	return 0;

    target = NORMAL_ACCESS(target, 0, 0);
    if ((sizeof(target) != 1) || (target[0] != TO))
	    return 0;

    remove_alarm(hook_alarm);
    hook_alarm = 0;

    if (str != whisper_flag)
    {
        set_alarm(2.0, 0.0, whisper_fail);
        quester = 0;
        return 0;
    }

    switch (whisper_flag)
    {
        case "angmar":
            whisper_alarm = set_alarm(1.0, 2.0, &whisper_react(name));
            break;
        case "angband":
            whisper_alarm = set_alarm(1.0, 2.0, &whisper_react_din(name));
            break;
        default:
            break;
    }

    whisper_flag = 0;
    return 0;
}

static void
whisper_fail()
{
    command("shout Fool!");
    command("hiss Leave now, before I smash your empty head!");
    command("hiss Learn more about the history of Middle Earth before " +
      "you come back!");
    return;
}

void
whisper_react(string name)
{
    object  pl;

    if (!present(pl = find_player(name), ENV(TO)))
	    whisper_stage = 999;

    switch (whisper_stage)
    {
        case 0:
            command("hiss Yess! That is the name!");
            break;
        case 2:
            command("hiss Be careful not to let Him hear you call " +
              "Him by that name!");
            break;
        case 3:
            command("hiss He hates to be reminded of being the " +
              "Witchking of Angmar.");
            break;
        case 5:
            command("hiss For more than 700 years he had laboured to destroy " +
              "those Numenorean traitors in the North and then, " +
              "when He had finally almost achieved His aim, that " +
              "rabble that He used as an army ran away from a " +
              "few elves and Gondorians!");
            break;
        case 6:
            command("hiss Oh, how did He curse His so called army!");
            break;
        case 8:
            command("hiss And He pursued that upstart Earnur with all " +
              "His wrath!");
            break;
        case 9:
            command("hiss When He finally managed to lure that fool " +
              "into this city, he was captured and then He " +
              "tortured him for months!");
            break;
        case 11:
            command("cackle maniaclly");
            command("mhiss They say that even the trolls pitied Earnur " +
              "when he had been in the dungeons for a few weeks!");
            break;
        case 14:
            command("hiss Anyhow, back to that fateful battle of Fornost!");
            command("sigh");
            break;
        case 15:
            command("hiss Among the spoils of war that Earnur conquered " +
              "that day was the battle standard of the Witchking, " +
              "our Lord!");
            break;
        case 17:
            command("hiss I don't know what happened to that standard " +
              "later on, but I do know that He wants it back!");
            break;
        case 19:
            command("hiss Go and ask Yrchor, if you want to know more.");
            if (objectp(pl = find_player(name)))
                pl->add_prop(BSW_I_SENT_TO_YRCHOR, 1);
                START_QUEST(pl, "BATTLE STANDARD - MORGUL");
            break;
        case 22:
            command("hiss He's captain in His army and must be somewhere " +
              "in town.");
            break;
        case 24:
            command("hiss Should you manage to find that standard, bring " +
              "it back to me, and you will be rewarded!");
            break;
        case 25:
        case 999:
            remove_alarm(whisper_alarm);
            whisper_alarm = 0;
            quester = 0;
            break;
        default:
            break;
    }

    whisper_stage++;
    return;
}

void
whisper_react_din(string name)
{
    object pl;

    if (!present(pl = find_player(name), ENV(TO)))
	    whisper_stage = 999;

    switch (whisper_stage)
    {
        case 0:
            command("hiss Your answer is correct!");
            break;
        case 3:
            command("hiss The Lord of Morgul has long known that an"
              + " agreement has been forged between the rabble in"
              + " Rohan and our foes in the walled city of Minas"
              + " Tirith.");
            break;
        case 6:
            command("hiss Should the Gondorians call for aid, they"
              + " will almost certainly have the support of the cursed"
              + " Riders of Rohan.");
            break;
        case 7:
            command("snarl");
            break;
        case 8:
            command("hiss This will not do.");
            break;
        case 10:
            command("hiss Thus, the Master has decreed that we are to"
              + " cripple the beacon which acts as the initial signal"
              + " to the Rohirrim.");
            break;
        case 11:
            command("hiss Know you of Amon Din?");
            break;
        case 13:
            command("hiss It is there that this signal lies, and"
              + " there that we must strike.");
            break;
        case 15:
            command("hiss Spies tell us that the signal is a fire"
              + " burned atop a high tower.");
            break;
        case 17:
            command("hiss Your task is to destroy the fuel for this"
              + " beacon so that even if word is sent, the signal will"
              + " never come!");
            break;
        case 18:
            command("cackle");
            break;
        case 21:
            command("hiss I do not know how you are to accomplish this, but"
              + " a servant has been sent into the region known as the"
              + " Mouths of the Entwash to explore some possibilities.");
            break;
        case 23:
            command("hiss Find him, and ask him for information about"
              + " Amon Din.");
            pl->add_prop(DIN_I_SENT_TO_HERMIT, 1);
                START_QUEST(pl, "AMON DIN FIREWOOD -MORGUL");
            break;
        case 24:
            command("hiss Unless he wishes death, he should know what"
              + " to do by now.");
            break;
        case 26:
            command("hiss Go then, and bring back some evidence that"
              + " you have destroyed the fuel if you desire a reward!");
            break;
        case 27:
        case 999:
            remove_alarm(whisper_alarm);
            whisper_alarm = 0;
            quester = 0;
            break;
        default:
            break;
    }

    whisper_stage++;
    return;
}

void
return_object(object obj, object to)
{
    if (obj->id("coin"))
	    return;

    command("hiss I have no use for this!");
    to->catch_msg(QCTNAME(TO)+" gives you "+obj->short()+".\n");
    tell_room(ENV(TO), QCTNAME(TO)+" gives "+LANG_ADDART(obj->short())+
      " to "+QTNAME(to)+".\n", to);

    if(obj->move(to))
	    obj->move(to, 1);
}

void
reward_repeat(object pl)
{
    command("hiss Where did you get this standard?");
    command("glare "+pl->query_real_name());
    command("hiss Leave before I smash your stupid head!");
    command("hiss This standard belongs to Him, and He doesn't like it " +
      "when some fools are playing around with it!");
    command("kick "+pl->query_real_name());
}

void
reward_repeat_din(object pl)
{
    command("peer "+pl->query_real_name());
    command("hiss My, what a fine example of destroyed lumber.");
    command("hiss It reminds me very much of the one you brought me"
      + " some time ago, and for which I already rewarded you.");
    command("hiss So perhaps you want another reward for an already"
      + " completed task, is that it?");
    command("loom "+pl->query_real_name());
    command("hiss Get out of my sight, you pathetic fool!");
}

void
reward_emyn_arnen(object pl)
{
    int     exp;
    string  name = pl->query_real_name();

    if (!present(pl, ENV(TO)))
	    return;

    command("examine standard");
    command("hiss This is actually His battle standard which He lost at " +
      "the Battle of Fornost to Earnur!");
    command("cackle");
    command("hiss He will be very pleased ... with me!");
    command("pat "+name);
    command("hiss Well done!");
    MONEY_MAKE_SC(30)->move(TO);
    command("give 30 silver coins to "+name);
    FIX_EUID

    if ((exp = pl->query_exp()) > ANGMAR_STANDARD_QUEST_EXP)
	    exp = ANGMAR_STANDARD_QUEST_EXP;

    pl->add_exp_quest(exp);
    pl->adjust_alignment(-500);
    pl->set_bit(MORGUL_GROUP, ANGMAR_STANDARD_BIT);
    pl->catch_msg("You feel more experienced!\n");
    LOG_QUEST(pl, exp, "BATTLE STANDARD - MORGUL");
    command("hiss You can go, I have no more use for you right now!");
    pl->remove_prop(BSW_I_FOUND_IT);
    BSW_TREASURY_FILE->remove_enter(name);
}

void
reward_amon_din(object pl, object log)
{
    int     exp;
    string  name = pl->query_real_name();

    if (!present(pl, ENV(TO)))
	    return;

    if (!pl->query_prop(DIN_I_SENT_TO_HERMIT))
    {
        command("hiss What is the meaning of this?");
        return_object(log, pl);
        return;
    }

    if (!pl->query_prop(DIN_I_DESTROYED_FIREWOOD))
    {
        command("hiss I am not impressed!");
        command("hiss If you believe that I would let such an"
          + " important duty go unobserved, then you are more of a fool"
          + " than I first believed!");
        command("hiss My spies have reported that it was not you who"
          + " destroyed this firewood, and I therefore give you the"
          + " following reward!");
        command("spit " + name);
        return;
    }

    if (!log->query_prop(DIN_I_FIREWOOD))
    {
        command("exa log");
        command("frown");
        command("hiss You expect me to reward you for this dry log?");
        command("manger "+name);
        command("hiss This proves nothing!");
        command("hiss Show me that you have destroyed the fuel, and"
          + " then I might consider letting you live another day!");
        command("rasp");
        return;
    }

    command("examine log");
    command("hiss If this is what I think it is...");
    command("emote examines the ash-grey log closely.");
    command("hiss You must have discovered a way to destroy the fuel"
      + " that the Gondorians are using for their beacon signal!");
    command("cackle");
    command("Excellent!");
    command("approve "+pl->query_real_name());
    command("hiss You have done well!");
    MONEY_MAKE_GC(2)->move(TO);
    command("give 2 gold coins to "+name);
    FIX_EUID

    if ((exp = pl->query_exp()) > AMON_DIN_FIREWOOD_EXP)
	    exp = AMON_DIN_FIREWOOD_EXP;

    pl->add_exp_quest(exp);
    pl->adjust_alignment(-400);
    pl->set_bit(AMON_DIN_FIREWOOD_GROUP, AMON_DIN_FIREWOOD_BIT);
    pl->catch_msg("You feel more experienced!\n");
    LOG_QUEST(pl, exp, "AMON DIN FIREWOOD -MORGUL");
    command("hiss Now be off, I have no more use for you right now!");
}

void
remove_standard(object flag)
{
    flag->remove_object();
}

void
remove_log(object flag)
{
    flag->remove_object();
}

void
check_emyn_arnen_quest(object pl, object flag)
{
    string  winner,
    name = pl->query_real_name();

    set_alarm(60.0, 0.0, &remove_standard(flag));
    if (pl->test_bit("Gondor", MORGUL_GROUP, ANGMAR_STANDARD_BIT))
    {
        reward_repeat(pl);
        return;
    }
    if ((winner = flag->query_prop(BSW_S_RETRIEVED_BY)) != name)
    { 
        command("hiss I have received reports that you have stolen " +
          "this standard from "+CAP(winner)+"!");
        command("hiss I do not like people who try to cheat me!");
        command("growl");
        command("shout So be gone before I smash your stupid head!");
        command("kick "+name);
        return;
    }
    command("hmm");
    set_alarm(1.0, 0.0, &reward_emyn_arnen(pl));
}

void
check_amon_din_quest(object pl, object log)
{
    string  winner,
    name = pl->query_real_name();

    set_alarm(60.0, 0.0, &remove_log(log));

    if (pl->test_bit("Gondor", AMON_DIN_FIREWOOD_GROUP,
	AMON_DIN_FIREWOOD_BIT))
    {
        reward_repeat_din(pl);
        return;
    }

    command("peer int "+name);
    set_alarm(1.0, 0.0, &reward_amon_din(pl, log));
}

void
key_returned(object key, object tp)
{
    if (!strlen(name_key))
    {
        command("rasp Where did you get this key?");
        command("rasp There is already one key to the Tower in my custody!");
        command("rasp I don't want this one!");
        set_alarm(0.5, 0.0, &return_object(key, tp));
        return;
    }

    if (tp->query_real_name() == name_key)
    {
        command("rasp Ah, the key!");
        command("rasp Good that it is back with me now!");
    }
    else
    {
        command("hmm");
        command("rasp Where did you get that key?");
        command("rasp I gave it to "+CAP(name_key)+", not to you!");
        command("rasp Well, at least it's back now!");
    }

    set_alarm(0.0, 0.0, &key->remove_object());
    name_key = 0;
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from))
    {
        obj->add_prop(OBJ_I_MORGUL_WARDEN, 1);
        return;
    }

    if (!living(from))
    {
        if (!store_alarm)
            store_alarm = set_alarm(10.0, 0.0, store_loot);
        return;
    }

    if (obj->id("_Morgul_Tower_Key"))
    {
	key_returned(obj, from);
	return;
    }

    if (!obj->id(BSW_BATTLE_STANDARD) && !obj->id("log"))
    {
        set_alarm(0.5, 0.0, &return_object(obj, from));
        return;
        }

    if (obj->id("log"))
    {
        set_alarm(1.0, 0.0, &check_amon_din_quest(from, obj));
        return;
    }

    set_alarm(1.0, 0.0, &check_emyn_arnen_quest(from, obj));
}

string
ask_key()
{
    object  key;
    string  name = TP->query_real_name();

    if (!IS_MORGUL_MAGE(TP))
	    return default_answer();

    if (strlen(name_key))
    {
        command("rasp I don't have the key!");
        command("rasp "+CAP(name_key)+" asked for it and I handed it over.");
        return "";
    }

    if (!CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
    {
        command("peer cauti");
        command("rasp I see you not! Show yourself to me!");
        return "";
    }

    key = clone_object(MAGES_DIR + "obj/tower_key");
    key->move(TO, 1);

    command("peer "+name);
    command("rasp The key for the Tower?");

    if (!TP->query_nazgul())
    {
        command("rasp Well, here it is, but take good care of it!");
        command("rasp If you lose it, the Nazgul will feed you to Shelob!");
    }
    else
    {
        command("rasp As you command!");
        command("rasp Here it is.");
    }

    command("give "+OB_NAME(key)+" to "+name);

    if (present(key))
	    command("rasp But you cannot carry it!");

    name_key = name;
    return "";
}

void
react_meet(object tp)
{
    string  name = tp->query_real_name(),
    mage_name;

    if (!objectp(tp) || !present(tp, ENV(TO)) || 
      !CAN_SEE(this_object(), tp))
    {
	    return;
    }

    command("hail "+name);
    mage_name = MORGUL_MASTER->query_mage_name(tp->query_real_name());
    if (strlen(mage_name))
    {
        if (tp->query_nazgul())
        {
            mage_name = ", " + (tp->query_gender() == 1 ? "Lady " : "Lord ") + 
            mage_name;
        }
        else
            mage_name = ", " + mage_name;
    }
    else
	    mage_name = "";

    command("rasp " + ONE_OF_LIST(
	({ "Greetings" + mage_name + "! How art thou?",
	  "Greetings" + mage_name + "! How fare thy travels?",
	})));
}

void
init_living()
{
    add_action(check_whisper, "whisper");
    ::init_living();

    if (IS_MORGUL_MAGE(TP))
	set_alarm(3.0, 0.0, &react_meet(TP));
}

/*
void
remove_object()
{
    object  env = ENV(TO);

    if (TP->query_wiz_level())
    {
	FIX_EUID
	log_file("violations", TP->query_name() + " removed "
	  + MASTER + " in "
	  + (objectp(env) ? file_name(env) : "the void")
	  + " on " + ctime(time()) + ".\n");
	write("Your action has been logged. Please refrain from "
	  + "repeating it, as it is potentially disruptive.\n");
    }

    ::remove_object();
}
*/

public void
store_loot()
{
    int     i, s;
    object *objs = all_inventory(TO);

    if (objectp(query_attack()) || (file_name(ENV(TO)) != home))
    {
        store_alarm = set_alarm(30.0, 0.0, store_loot);
        return;
        }

    store_alarm = 0;

    command("north");

    objs -= filter(objs, &->query_prop(OBJ_I_MORGUL_WARDEN));

    for (i = 0, s = sizeof(objs); i < s; i++)
	    command("put "+OB_NAME(objs[i])+" into rack");

    set_alarm(5.0, 0.0, &command("south"));
}

/*
 * Function name: monster_do_act
 * Description:   alled by VBFC in seq_heartbeat
 */
public void
monster_do_act()
{
    ::monster_do_act();

    if (!strlen(home))
    {
        home = file_name(ENV(TO));
        return;
    }

    if (objectp(query_attack()) || (home == file_name(ENV(TO))))
	    return;

    move_living("back to his office", home);
}

/*
 * Function name: remove_surplus
 * Description  : This function destructs items when the warden is too
 *                encumbered. However, for the warden, this is undesired
 *                behaviour.
 * Arguments    : object ob - the object to be destructed.
 */
public void
remove_surplus(object ob)
{
}

/*
 * Function name: check_weapons
 * Description  : The warden will check weapons he receives and wield it
 *                should it be better than his own. For the warden, this
 *                is undesired behaviour.
 * Arguments    : object new - the object to check.
 */
public void
check_weapons(object new, object from)
{
}

/*
 * Function name: check_armours
 * Description  : The warden will check armours he receives and wear it
 *                should it be better than his own. For the warden, this
 *                is undesired behaviour.
 * Arguments    : object new - the object to check.
 */
public void
check_armours(object new, object from)
{
}

void hook_received_palanquendo(object caster, string message)
{
//    find_living("eowul")->catch_msg("Warden received message: " + message + " from " + caster->query_real_name() + "\n");
}

/*****************************************************************************
 * New Routines
 ****************************************************************************/



static varargs void
do_intro(object tp)
{
    if (!objectp(tp))
        tp = TP;

    if (tp->query_npc() || !CAN_SEE_IN_ROOM(TO) ||
        !CAN_SEE(TO, tp) || tp->query_met(query_real_name()))
        return;
    if (sizeof(get_alarm(intro_id)))
        return;
    intro_id = set_alarm(3.0, 0.0, &command("introduce myself to "
      + tp->query_name()));
    return;
}

public void
add_introduced(string str)
{
    object  who = find_player(str);

    if (objectp(who))
        do_intro(who);
}
