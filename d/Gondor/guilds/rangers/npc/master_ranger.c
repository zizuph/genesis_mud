/*
 *    The standard master ranger for the ranger guild
 *
 *    Created by copying functions from files by Elessar
 *    - Olorin, 20-Jan-1995
 *
 * Modification log:
 * 24-Feb-2002, Alto: Moved, modified to fit new rangers structure.
 * 27-Oct-2003, Tigerlily: set_size_descs added for tall, lean
 *
 */
inherit "/std/monster";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/d/Gondor/common/lib/time.c";
inherit "/d/Genesis/lib/intro";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <state_desc.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/common/lib/clock.h"

#define COMPANY ({ "the Westlands", "Ithilien", "the North" })
#define NUMBER_OF_COMPANIES 2
#define CNO_WESTLANDS       0
#define CNO_ITHILIEN        1
#define CNO_NORTH           2


#define LOST_RANGER_SEARCHER        "_ranger_i_searching_for_lost_ranger"
#define CLAIMING_HARAD_BANNER       "_ranger_i_claiming_harad_banner"
#define DID_VISIT_HARADCAMP         "_ranger_i_did_visit_haradcamp"
#define NO_MORE_RANGER_QUESTS_TODAY "_denied_ranger_quests"

static string  master_ranger_file;
static int     orccamp_info,
               company_no;

/* prototypes */
public void            create_master_ranger();
public int             set_company_no(int no);
public void            arm_me();
public void            enchant_seed();
public void            retrieve_banner();
public void            missing_ranger();
public string          give_task();
public string          inform_gondor();
public string          inform_ithilien();
public string          def_answer();
public string          inform_north();
public string          inform_orc_camp();
public void            do_thank(object pl, int no);
public void            quest_done(int no, object pl);
public void            quest_not_done(int i, object pl);
public void            test_quest_done(object ob);
public void            enter_inv(object ob, object from);
public varargs string  short(object for_obj);
public void            initiate_ranger_soul();
public void            introduce(object who);
public void            greet(object who);

string def_answer();


public void
create_master_ranger()
{
}

public int
set_company_no(int no)
{
    if ((no < sizeof(COMPANY)) && (no >= 0))
    {
        company_no = no;
        return 1;
    }
    return 0;
}

public int
query_company_no()
{
    return company_no;
}

public void
set_master_ranger_file(string fn)
{
    master_ranger_file = fn;
}

public string
query_master_ranger_file()
{
    return master_ranger_file;
}

public void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP_DIR + "dlsword")->move(TO);
    clone_object(ARM_DIR + "drcloak")->move(TO);
    clone_object(ARM_DIR + "dlboots")->move(TO);

    if (query_company_no() == CNO_NORTH)
        clone_object(RANGERS_NOR_EMBLEM)->move(TO, 1);
    else if (query_company_no() == CNO_ITHILIEN)
        clone_object(RANGERS_ITH_EMBLEM)->move(TO, 1);
    else if (query_company_no() == CNO_WESTLANDS)
        clone_object(RANGERS_APP_EMBLEM)->move(TO, 1);

    command("wield sword");
    command("wear all");
}


public void
enchant_seed()
{
    command("say Amaron, master ranger of the Westlands sent " +
        "me a message that their main supplier of herbs " +
        "has asked him for help. Maybe you could go and " +
        "talk to Amaron for further information?");
}

public void
retrieve_banner()
{
    if (!TP->query_prop(CLAIMING_HARAD_BANNER))
    {
        if (TP->query_prop(DID_VISIT_HARADCAMP, 1))
        {
            if (present("_harad_banner_from_camp_", TP))
            {
                /* player brought back banner before having been 
                 * assigned the quest -- following quest docs, perhaps?
                 */
                command("say What are you running around, waving " +
                    "that enemy banner for!?");
                command("say I find that offensive, to put it mildly!");
                command("scowl");
                command("say Leave, and don't come back again today!");
                command("spit");
                TP->add_prop(NO_MORE_RANGER_QUESTS_TODAY, 1);
                return;
            }
            /* already visited camp today -- try later */
            command("say I don't think I need you to do any tasks today.");
            command("say Please come back some other day.");
            return;
        }

        /* ok, tell 'em about the banner */
        command("say A Ranger who travelled in Ithilien reported that he " +
            "had seen a large army camped in the southern forest.");
        command("say He did not have the time to identify the forces of " +
            "that army, and we need to know who we are dealing with.");
        command("say I want a proof of what army it is, preferably a " +
            "banner showing their symbol, that would be good enough for " +
            "our Captain. But be careful, and don't be too brave!");
        TP->add_prop(CLAIMING_HARAD_BANNER, 1);
        return;
    }

    /* we've already told them about the banner -- are they
     * just confused?  */
    command("say Why are you asking me again?");
    command("say If you've found what I wanted, please give it to me.");
    command("say If you haven't, then you shouldn't be here wasting my time.");
}

public void
missing_ranger()
{

    command("say As soon as we heard of the large army camped in Ithilien, " +
        "we sent a ranger named Leydon to scout the area further.");
    command("say We probably should have left that business for the " +
        "Rangers of Ithilien, but too late to regret it now.");
    command("say Leydon hasn't returned. I want you to find out what has " +
        "happened to him. If he is alive - bring him back " +
        "to me. If not - bring proof of his demise.");
    TP->add_prop(LOST_RANGER_SEARCHER, 1);
}

public string
give_task()
{

    if (TP->query_prop(NO_MORE_RANGER_QUESTS_TODAY))
        command("say I'm sorry - I have no task for you right now.");
    else if (!TP->test_bit("Gondor", GONDOR_GROUP, ENCHANT_SEED_BIT))
        enchant_seed();
    else if (!TP->test_bit("Gondor", TOUR_GROUP, HARAD_BANNER_BIT))
        retrieve_banner();
    else if (!TP->test_bit("Gondor", GONDOR_GROUP, LOST_RANGER_BIT))
        missing_ranger();
    else
        command("say I'm sorry - I have no tasks for you today.");

    return "";
}

public string
inform_gondor()
{

    command("say Gondor is a beautiful land.");
    command("say The main problem is the Enemy in the East.");
    command("say How can anyone live peacefully when large armies are " +
        "mustering to attack them?");
    command("sigh");
    return "";
}

public string
inform_ithilien()
{

    command("say Ithilien is even fairer than Gondor, some say.");
    command("say I haven't seen it myself, but when I do, I hope it is " +
        "once again a free land, and not corrupted by the orcs from Mordor.");
    command("spit");
    command("say If you are not a ranger, do not go there without " +
        "permission from the Steward of Gondor!");
    command("say In these troubled days, you cannot just visit Ithilien.");
    command("say In Ithilien, the forces of Gondor know only friends and " +
        "foes, and those who do not serve Gondor will be treated as " +
        "servants of the Dark Tower!");
    if (!RANGERS_MEMBER(TP))
        command("say Go to Minas Tirith and ask Hunthor. He might grant " +
            "you the right to go to Ithilien.");
    return "";
}

public string
inform_north()
{
    command("say In the North was Arnor, the sister-kingdom of Gondor.");
    command("say It was a large and beautiful kingdom.");
    command("say But the accursed Witch-king of Angmar attacked, and after " +
        "a long war destroyed the kingdom completely.");
    command("say What's left there now is an empty land, and a few small " +
        "villages.");
    command("say Halflings live there, and Rangers protect them from the " +
        "world.");
    command("smile");
    return "";
}

public string
inform_orc_camp()
{
    command("frown");
    if (!orccamp_info)
    {
        command("say I'm afraid we know little else than its location.");
        command("say It is in the forests south of the Morgulduin river.");
        command("say The army surely contains Orcs, but we think there " +
            "may be humans there too.");
        command("say It would be good to know where those humans are from.");
        command("say In any case, be careful there. Red Eye Orcs are " +
            "dangerous.");
        return "";
    }

    command("say The orc-camp is large.");
    command("say The orcs camped there are fierce orcs of the Red Eye " +
        "army of Mordor.");
    command("say They have been joined by an army of Haradrim soldiers.");
    command("say The dark-skinned Haradrim are even fiercer fighters " +
        "than the Orcs of the Red Eye. Be careful there.");
    return "";
}

public string
inform_osgiliath_bridge()
{
    if ((rq_stage() < RQ_OSGILIATH_BROKEN) ||
        (rq_stage() >= RQ_OSGILIATH_FIXED))
    {
        command("say Osgiliath is in Gondorian hands currently, and we " +
            "may cross the bridge under the protection of soldiers from " +
            "the Army of Gondor.");
    }
    else
    {
        command("say Forces from Imlad Morgul tried to capture Osgiliath " +
            "recently.");
        command("sigh .");
        command("say Some of our men, along with soldiers of the Army of " +
            "Gondor, were forced to destroy the bridge to prevent the " +
            "Enemy from crossing the River Anduin and swarming into Anorien.");
        command("say For now you may cross the river on a ferry that we " +
            "have set up.");
    }
    return "";
}   

public string* get_valid_major_virtue_options(object player)
{
    string* valid_options = ({});
    
    foreach (int num, string name : MAJOR_VIRTUES_TO_NAME)
    {
        if (player->is_major_virtue_valid(num))
        {
            valid_options += ({ "the " + name });
        }
    }
    return valid_options;
}

public string* get_valid_minor_virtue_options(object player)
{
    string* valid_options =({});
    
    foreach (int num, string name : MINOR_VIRTUES_TO_NAME)
    {
        if (player->is_minor_virtue_valid(num))
        {
            valid_options += ({ "the " + name  });
        }
    }
    return valid_options;
}


public string inform_virtues()
{
    if (IS_RANGER(TP))
    {
        command("say There are many virtuous paths that a ranger can " +
            "follow, and each provides different strengths to help " +
            "defeat our foes.");
        command("say You will be able to adapt a major and minor " +
           "virtue, which affects what strengths you bring to the cause.");
    }
    else
    {
        command("say The path of a ranger provides many virtuous options.");
    }

}

public string inform_major_virtues()
{
    if (IS_RANGER(TP))
    {
        if (TP->query_ranger_has_virtues())
        {
            if (TP->query_ranger_major_virtue())
            {
            string* major_options = get_valid_major_virtue_options(TP);
            command("say The major " +
              (sizeof(major_options) == 1 ? "virtue " : "virtues ") +
              "available to you " + (sizeof(major_options) == 1 ? "is " : "are ") +
               COMPOSITE_WORDS(major_options) + ".");

            command("say You practice the specialization of the " + 
                MAJOR_VIRTUES_TO_NAME[TP->query_ranger_major_virtue()] + ".");
            if (MANAGER->can_change_major_virtue(TP->query_real_name()))
            {
                command("say You can adapt a new specialization if you wish " +
                "at this time.");
            }
            }
            else
            {
            command("say Once you have a company, you can choose which virtues " +
                "that you will focus on.");
            }
        }
        else
        {
        command("say You will be able to choose a major virtue soon.");
            string* all_major = m_values(MAJOR_VIRTUES_TO_NAME);
            command("say The major " +
              (sizeof(all_major) == 1 ? "virtue is " : "virtues are ") +
               COMPOSITE_WORDS(all_major) + ".");
        }
    }
    else
    {
        command("say The path of a ranger provides many virtuous options.");
    }
    return "";
}

public string inform_minor_virtues()
{
    if (IS_RANGER(TP))
    {
        if (TP->query_ranger_has_virtues())
        {
        if (TP->query_ranger_minor_virtue())
        {
            string* minor_options = get_valid_minor_virtue_options(TP);
            command("say The minor " +
              (sizeof(minor_options) == 1 ? "virtue " : "virtues ") +
              "available to you " + (sizeof(minor_options) == 1 ? "is " : "are ") +
               COMPOSITE_WORDS(minor_options) + ".");
            command("say You are familiar with the " +
                MINOR_VIRTUES_TO_NAME[TP->query_ranger_minor_virtue()]  + ".");
            if (MANAGER->can_change_minor_virtue(TP->query_real_name()))
            {
                command("say You can adapt a different option if you wish " +
                "at this time.");
            }
        }
        else
        {
            command("say Once you have a company, you can choose which virtues " +
                "that you will focus on.");
        }
        }
        else
        {
            command("say You will be able to choose a minor virtue soon.");
            string* all_minor = m_values(MINOR_VIRTUES_TO_NAME);
            command("say The minor " +
                (sizeof(all_minor) == 1 ? "virtue is " : "virtues are ") +
                COMPOSITE_WORDS(all_minor) + ".");
        }
    }
    else
    {
        command("say The path of a ranger provides many virtuous options.");
    }

    return "";
}

public string describe_major_virtue(int virtue)
{
    if (!IS_RANGER(TP))
    {
        return def_answer();
    }
    switch (virtue)
    {
        case RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST:
           command("say That virtue is a path followed by many rangers in the past.");
           command("say It is well rounded, with focus on stealth and sword fighting.");
        break;
        case RANGER_MAJOR_VIRTUE_HAND_OF_THE_KING:
            command("say That virtue bears many similarities to the Enemy of the East.");
            command("say There is more focus on knowledge of herbs, alchemy, and stealth.");
        break;
        case RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_SHADOW:
            command("say That virtue focuses more heavily on combat than the Enemy of the East.");
            command("say The two sword style is commonly used by those that study this.");
            command("say It is practiced by the company of the North.");
        break;
        case RANGER_MAJOR_VIRTUE_SENTINEL_OF_IMLADRIS:
            command("say That virtue is based on the skills of the elves.");
            command("say Bows are their preferred weapon, rather than swords.");
            command("say In addition, it provides the healing gifts of Aule.");
            command("say It is practiced by the company of the North.");
        break;
        case RANGER_MAJOR_VIRTUE_DAUNTLESS_GUARDIAN:
            command("say That virtue focuses heavily on defence in combat.");
            command("say Sword skill for the Dauntless Guardian is unmatched.");
            command("say This is practiced by the company of Ithilien.");
        break;
        case RANGER_MAJOR_VIRTUE_DEFENDER_OF_OSGILIATH:
            command("say That virtue is often seen by those that take advanced positions.");
            command("say Instead of a sword, they use polearms to keep the enemy at bay.");
            command("say This is practiced by the company of Ithilien.");
        break;
        case RANGER_MAJOR_VIRTUE_OLD_HATRED:
            command("say The Old Hatred uses the teachings of the dwarves.");
            command("say Axe skill, both with one and two axes, are their specialty.");
            command("say The Rockfriends that join our efforts can practice this.");
        break;
    }
    return "";
}

public string describe_minor_virtue(int virtue)
{
    if (!IS_RANGER(TP))
    {
        return def_answer();
    }
    switch (virtue)
    {
        case RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR:
           command("say Blessing of the Eldar provides the magical gifts of healing.");
        break;
        case RANGER_MINOR_VIRTUE_DEEP_SONGS:
            command("say Those that practice the Deep Songs have axe and parry skill.");
            command("say It is practiced by the Rockfriends.");
        break;
        case RANGER_MINOR_VIRTUE_WARDEN_OF_PELENNOR:
            command("say The Wardens of Pelennor further train polearm and parry.");
            command("say It is practiced by those in the Thornlin Militia.");
        break;
        case RANGER_MINOR_VIRTUE_DEADLY_ARCHERS:
            command("say The Deadly Archers are experts in bows and arrows.");
            command("say These are the speciality of the Noldor.");
        break;
        case RANGER_MINOR_VIRTUE_ART_OF_DISAPPEARING:
            command("say The Art of Disappearing helps those who like to travel hidden.");
            command("say This is practiced by Adventurous Hobbits.");
        break;
        case RANGER_MINOR_VIRTUE_NOBLE_LINEAGE:
            command("say Those of Noble Lineage have advanced skill in sword and parry.");
            command("say This is practiced by the Dunedain.");
        break;
        case RANGER_MINOR_VIRTUE_FRIEND_OF_ROHAN:
            command("say Those with the Teachings of Rohan have more expertise on horseback.");
        break;
        case RANGER_MINOR_VIRTUE_GIFTS_OF_ESTE:
            command("say Those with the Gifts of Este focus on herbalism and alchemy.");
        break;
    }
    return "";
}

public void update_major_virtue(object player, int virtue)
{
    if (virtue == MANAGER->query_major_virtue(player->query_real_name()))
    {
        command("say That is already your major virtue.");
        return;
    }
    if (!player->is_major_virtue_valid(virtue))
    {
        command("say That is not currently an option for yourself.");
        return;
    }
    if (!MANAGER->can_change_major_virtue(player->query_real_name()))
    {
        command("say Have patience, you cannot be released yet from your role.");
        return;
    }
    MANAGER->set_major_virtue(player->query_real_name(), virtue);
    command("say May you find strength with the ways of the "
      + MAJOR_VIRTUES_TO_NAME[virtue] + ".");
}

public void update_minor_virtue(object player, int virtue)
{
    if (virtue == MANAGER->query_minor_virtue(player->query_real_name()))
    {
        command("say That is already your minor virtue.");
        return;
    }
    if (!player->is_minor_virtue_valid(virtue))
    {
        command("say That is not currently an option for yourself.");
        return;
    }
    if (!MANAGER->can_change_minor_virtue(player->query_real_name()))
    {
        command("say Have patience, you are not yet ready to change.");
        return;
    }
    MANAGER->set_minor_virtue(player->query_real_name(), virtue);
    command("say May you find strength with the ways of the "
      + MINOR_VIRTUES_TO_NAME[virtue] + ".");
}

public int
do_adapt(string str)
{
    str = lower_case(str);
    if (!IS_RANGER(TP))
    {
        return 0;
    }
    if (!TP->query_ranger_has_virtues())
    {
        return 0;
    }
    notify_fail("Adapt what?\n");
    if (!str)
    {
        return 0;
    }
    foreach (int virtue, string name: MAJOR_VIRTUES_TO_NAME)
    {
        if (lower_case(name) == str)
        {
            update_major_virtue(TP, virtue);
            return 1;
        }
    }
    foreach (int virtue, string name: MINOR_VIRTUES_TO_NAME)
    {
        if (lower_case(name) == str)
        {
            update_minor_virtue(TP, virtue);
            return 1;
        }
    }
    return 0;
}


public void
do_thank(object pl, int no)
{
    if (no == 0)
        command("say You have braved a great risk, but you have already " +
            "brought us that banner!");
    else if (no == 1)
    {
        command("say Ah, so you've helped us again! Thanks so much, but " +
            "I can't give you any reward this time.");
        command("smile " + OB_NAME(pl));
    }
}

public void
quest_done(int no, object pl)
{
    if ((no < 0) || (no > 1))
        return 0;

    if (!objectp(pl))
        return 0;

    if (no == 0)
    {
        if (pl->test_bit("Gondor", TOUR_GROUP, HARAD_BANNER_BIT))
            do_thank(pl, 0);
        else
        {
            command("say Ah! This is the banner of the Haradrim!");
            command("say The army is from Harad, from the lands south " +
                "of Gondor!");
            if ((pl->query_prop(CLAIMING_HARAD_BANNER) == 0) ||
                (pl->query_prop(NO_MORE_RANGER_QUESTS_TODAY) == 1))
            {
                command("say But why did you bring this to me? I have " +
                    "not asked for it.");
                command("shrug");
                pl->add_prop(NO_MORE_RANGER_QUESTS_TODAY, 1);
                return;
            }
            else if (pl->query_prop(DID_VISIT_HARADCAMP) != 2)
            {
                command("say I'm thankful that you have revealed this to us.");
                if (pl->query_prop(DID_VISIT_HARADCAMP) == 1)
                    command("say But I have reason to believe you have " +
                        "not even been to the enemy camp after I gave you " +
                        "the quest.");
                else
                    command("say But I have reports that you have not " +
                        "even been to the enemy camp today.");

                command("say I do not like to be cheated, so you will " +
                    "not become more experienced by this. Now leave!");
                pl->add_prop(NO_MORE_RANGER_QUESTS_TODAY, 1);
                pl->remove_prop(DID_VISIT_HARADCAMP);
                pl->remove_prop(CLAIMING_HARAD_BANNER);
                return;
            }

            command("thank " + OB_NAME(pl));
            pl->remove_prop(CLAIMING_HARAD_BANNER);
            pl->remove_prop(DID_VISIT_HARADCAMP);
            pl->set_bit( TOUR_GROUP, HARAD_BANNER_BIT);
            pl->add_exp_quest(HARAD_BANNER_EXP);
            LOG_QUEST(pl, HARAD_BANNER_EXP, "HARAD BANNER");
            pl->catch_tell("You feel more experienced.\n");
            orccamp_info = 1;
            present("_harad_banner_from_camp_", TO)->remove_object();
        }
    }
    else if (pl->test_bit("Gondor", GONDOR_GROUP, LOST_RANGER_BIT))
    {
        do_thank(pl,1);
    }
    else
    {
        command("say Alas! Leydon's ring! I understand he is not with us " +
            "anymore then.");
        command("sigh");
        if (pl->query_prop(LOST_RANGER_SEARCHER) != 2)
        {
            command("say But something tells me this is not something " +
                "you discovered yourself.");
            command("say I think I will wait with rewarding you till I " +
                "know you deserve it.");
            return;
        }

        command("say I'm thankful that you found out the truth for us though.");
        command("thank " + OB_NAME(pl));
        pl->set_bit( GONDOR_GROUP, LOST_RANGER_BIT);
        pl->add_exp_quest(LOST_RANGER_EXP);
        LOG_QUEST(pl, LOST_RANGER_EXP, "LOST RANGER");
        pl->catch_tell("You feel more experienced.\n");
        if (pl->query_prop("_gondor_met_rangers_wife"))
        {
            command("say Could you perhaps go to Minas Tirith and give " +
                "the ring to Leydon's widow? I know, she would appreciate it.");
            command("give ring to " + OB_NAME(pl));
            command("smile");
        }
    }
}

public void
quest_not_done(int i, object pl)
{
    command("say Well, this is the banner of the Orcs of Mordor," +
        " but it was hardly a surprise we would find those in Ithilien.");
    command("chuckle");
    command("say No, the scout said there were humans in that army too.");
    command("say I wanted the banner of the humans, not the Orcs.");
    command("say Please try again, will you? Thanks for your effort.");
    present("_red_eye_banner_from_camp_", TO)->remove_object();
}

public void
test_quest_done(object ob)
{
    if (present("_red_eye_banner_from_camp_", TO) == ob)
        quest_not_done(0, TP);
    else if (present("_harad_banner_from_camp_", TO) == ob)
        quest_done(0, TP);
    else if (present("Ranger_Quest_Ring", TO) == ob)
        quest_done(1, TP);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (!objectp(from) || !living(from))
        return;

    if (ob->id("_red_eye_banner_from_camp_"))
        test_quest_done(ob);
    if (ob->id("_harad_banner_from_camp_"))
        test_quest_done(ob);
    if (ob->id("Ranger_Quest_Ring"))
        test_quest_done(ob);
}

public varargs string
short(object for_obj)
{
    string desc, *adj;

    if (!for_obj)
        for_obj = TP;

    if (notmet_me(for_obj))
    {
        if (sizeof((adj = (string *)TO->query_adj(1))) > 0)
            desc = implode(adj, " ") + " ranger";
        else
            desc = "ranger";
    }
    else
    {
        desc = TO->query_met_name();
    }

    if (query_prop(LIVE_S_EXTRA_SHORT))
        desc = desc + query_prop(LIVE_S_EXTRA_SHORT);

    return desc;
}

public nomask void
create_monster()
{
    set_name(({"man", "dunadan", }));
    add_name(({"ranger", "master ranger", "master"}));
    add_name("_R_enlister_");
    set_race_name("human");
    set_gender(G_MALE);
    set_adj("master");

    create_master_ranger();

    set_base_stat(SS_OCCUP, 100);
    set_size_descs("tall", "lean");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(160);
    set_act_time(120);

    set_cact_time(2);
    add_cact("brawl");
    add_cact("spit");


    add_ask(({"task", "quest", "job", "tasks", "quests", "jobs",
        "about task", "about quest", "about job", "about tasks",
        "about quests", "about jobs", "for task", "for quest",
        "for job","for tasks","for quests","for jobs"}), give_task);
    add_ask(({"virtues", "virtue", "the virtues", "about the virtues" }),
        inform_virtues);
    add_ask(({"major virtues", "major virtue", "about major virtues"}), 
        inform_major_virtues);
    add_ask(({"minor virtues", "minor virtue", "about minor virtues"}),
        inform_minor_virtues);

    add_ask(({"enemy of east"}),
            &describe_major_virtue(RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST));
    add_ask(({"hand of king"}),
            &describe_major_virtue(RANGER_MAJOR_VIRTUE_HAND_OF_THE_KING));
    add_ask(({"enemy of shadow"}),
            &describe_major_virtue(RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_SHADOW));
    add_ask(({"sentinel of imladris"}),
            &describe_major_virtue(RANGER_MAJOR_VIRTUE_SENTINEL_OF_IMLADRIS));
    add_ask(({"dauntless guardian"}),
            &describe_major_virtue(RANGER_MAJOR_VIRTUE_DAUNTLESS_GUARDIAN));
    add_ask(({"defender of osgiliath"}),
            &describe_major_virtue(RANGER_MAJOR_VIRTUE_DEFENDER_OF_OSGILIATH));
    add_ask(({"old hatred"}),
            &describe_major_virtue(RANGER_MAJOR_VIRTUE_OLD_HATRED));

    add_ask(({"blessing of eldar"}),
            &describe_minor_virtue(RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR));
    add_ask(({"deep songs"}),
            &describe_minor_virtue(RANGER_MINOR_VIRTUE_DEEP_SONGS));
    add_ask(({"ways of warden of pelennor"}),
            &describe_minor_virtue(RANGER_MINOR_VIRTUE_WARDEN_OF_PELENNOR));
    add_ask(({"art of deadly archery"}),
            &describe_minor_virtue(RANGER_MINOR_VIRTUE_DEADLY_ARCHERS));
    add_ask(({"art of disappearing"}),
            &describe_minor_virtue(RANGER_MINOR_VIRTUE_ART_OF_DISAPPEARING));
    add_ask(({"noble lineage"}),
            &describe_minor_virtue(RANGER_MINOR_VIRTUE_NOBLE_LINEAGE));
    add_ask(({"teachings of rohan"}),
            &describe_minor_virtue(RANGER_MINOR_VIRTUE_FRIEND_OF_ROHAN));
    add_ask(({"gifts of este"}),
            &describe_minor_virtue(RANGER_MINOR_VIRTUE_GIFTS_OF_ESTE));


    add_ask("name", introduce);
    add_ask(({"about gondor", "gondor"}), inform_gondor);
    add_ask(({"about ithilien", "ithilien"}), inform_ithilien);
    add_ask(({"about north", "north"}), inform_north);
    add_ask(({"about osgiliath", "about bridge", "about osgiliath bridge",
        "about the bridge", "about the osgiliath bridge", "bridge",
        "osgiliath",}), inform_osgiliath_bridge);
    add_ask(({"about orc camp", "orc camp"}), inform_orc_camp);
    set_default_answer(&def_answer());
}

string
def_answer()
{
    command("say I know nothing of these matters.");
    command("hmm");
    return "";
}


void
initiate_ranger_soul()
{
    TO->add_cmdsoul("/d/Gondor/guilds/rangers/soul/rangers_soul");
    TO->update_hooks();
}

void
init_living()
{
    ::init_living();
    initiate_ranger_soul();
    add_action(do_adapt, "adapt");
}
public void
greet(object who)
{
      // He won't greet an enemy! 
    if (member_array(who, query_enemy(-1)) > -1) 
    { 
        command("kill " + OB_NAME(who)); 
    } 
    else if (!objectp(query_attack())) 
    {  
        command("rhail " + OB_NAME(who));
    } 
} 


public void 
introduce(object who)
{
    if (who->query_race_name() == "goblin")
    {
        command("peer suspiciously " + OB_NAME(who));
        command("rsay Be gone, foul creature!");
        command("kill " + OB_NAME(who));
        return;
    }

      // He won't intro to an enemy 
    if (member_array(who, query_enemy(-1)) > -1) 
    { 
        command("kick " + OB_NAME(who)); 
        return;
    } 
    command("introduce me to " + OB_NAME(who));
    command("emote lowers his gaze briefly as he bows gracefully.");
    return;

} 
