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
inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/d/Gondor/common/lib/time.c";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <state_desc.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"
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
#define MR_I_CEREMONY               "_master_ranger_i_ceremony"

static string  master_ranger_file;
static int     orccamp_info,
               company_no;

/* prototypes */
public void            create_master_ranger();
public int             set_company_no(int no);
public void            arm_me();
public varargs string  introduce(mixed who);
public void            enchant_seed();
public void            retrieve_banner();
public void            missing_ranger();
public string          give_task();
public string          inform_gondor();
public string          inform_ithilien();
public string          inform_north();
public string          inform_orc_camp();
public void            do_thank(object pl, int no);
public void            quest_done(int no, object pl);
public void            quest_not_done(int i, object pl);
public void            test_quest_done(object ob);
public void            enter_inv(object ob, object from);
public varargs string  short(object for_obj);
public int              set_ceremony(int i);
public int              shut_up_mr();
public int              restart_chats();
public int              query_in_ceremony();

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
introduce(object who)
{
    command("hail " + OB_NAME(who));
    command("say My name is " + query_name() + ". I am a Master Ranger here.");
    command("introduce me to " + OB_NAME(who));
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
    if (query_in_ceremony())
    {
        write(TO->query_The_name(TP) + " signals to you for " +
            "silence.\n");
        return "";
    }
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
    if (query_in_ceremony())
    {
        write(TO->query_The_name(TP) + " signals to you for " +
            "silence.\n");
        return "";
    }
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
    if (query_in_ceremony())
    {
        write(TO->query_The_name(TP) + " signals to you for " +
            "silence.\n");
        return "";
    }
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
    if (query_in_ceremony())
    {
        write(TO->query_The_name(TP) + " signals to you for " +
            "silence.\n");
        return "";
    }
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

void
return_introduce(object pl)
{
    command("introduce me to " + OB_NAME(pl));
    command("emote lowers his gaze briefly as he bows gracefully.");
    return;
}

public nomask void
create_gondor_monster()
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

    set_default_answer("say I do not know what you are talking about!");

    add_ask(({"task", "quest", "job", "tasks", "quests", "jobs",
        "about task", "about quest", "about job", "about tasks",
        "about quests", "about jobs", "for task", "for quest",
        "for job","for tasks","for quests","for jobs"}), give_task);
    add_ask("name", introduce);
    add_ask(({"about gondor", "gondor"}), inform_gondor);
    add_ask(({"about ithilien", "ithilien"}), inform_ithilien);
    add_ask(({"about north", "north"}), inform_north);
    add_ask(({"about osgiliath", "about bridge", "about osgiliath bridge",
        "about the bridge", "about the osgiliath bridge", "bridge",
        "osgiliath",}), inform_osgiliath_bridge);
    add_ask(({"about orc camp", "orc camp"}), inform_orc_camp);

    set_intro(3.0, return_introduce);
}

public int
set_ceremony(int i)
{
// either 0 = not in ceremony
// 1 = in ceremony at the moment
// so behave quietly.

    add_prop(MR_I_CEREMONY, i);

    if (i == 0)
        TO->restart_chats();
    else
        TO->shut_up_mr();
    return 1;
}

public int
query_in_ceremony()
{
    return query_prop(MR_I_CEREMONY);
}

public int
shut_up_mr()
{
    clear_chat();
    clear_act();
    write(TO->query_The_name(TP) + " signals to you for " +
            "silence.\n");
    return 1;
}

public int
restart_chats()
{
    clear_chat();
    clear_act();
    add_chat("We pay a high price for our freedom.");
    add_chat("Always be sure to cover your tracks when you approach the "
        + "hideout! The Enemy is searching for rumours of us.");
    add_chat("It is our way to travel incognito. Best that the Enemy does "
        + "not guess our true nature .. or our true numbers.");
    add_chat("The shadow in the East is growing.");
    add_act("emote looks at you piercingly, seeming to read your thoughts.");
    add_act("ponder");
    add_act("emote scans the area, constantly vigilant.");

    return 1;
}
