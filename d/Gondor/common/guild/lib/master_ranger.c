/*
 *    The standard master ranger for the ranger guild
 *
 *    Created by copying functions from files by Elessar
 *    - Olorin, 20-Jan-1995
 *
 *	Modification log:
 *	- unknown changes by Elessar
 *	- rewritten part of the sponsor code, Olorin, 12-June-1995
 *	14-Oct-1997, Gnadnar: changed "list" to "disclose" in order
 *		not to conflict with new "list" command in training
 *		rooms.
 *	2-Jan-1998, Gnandar:  respond to questions about pupils,
 *		sponsors, etc, as well as to the "disclose" command.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/npc/npc_ranger";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/d/Gondor/common/lib/time.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <state_desc.h>
#include <std.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/lib/clock.h"

#define COMPANY \
	({ "Ranger Pupils", "Gondor", "Ithilien", "the North" })
#define NUMBER_OF_COMPANIES	3
#define SPONSORS		"/d/Gondor/common/guild/sponsors"
#define	TOKEN_NAME		({ "ring", "ring", "amulet", "rbrooch" })
#define	CNO_PUPILS		0
#define	CNO_GONDOR		1
#define	CNO_ITHILIEN	2
#define CNO_NORTH       3


#define LOST_RANGER_SEARCHER	"_ranger_i_searching_for_lost_ranger"
#define CLAIMING_HARAD_BANNER	"_ranger_i_claiming_harad_banner"
#define DID_VISIT_HARADCAMP	"_ranger_i_did_visit_haradcamp"
#define NO_MORE_RANGER_QUESTS_TODAY	"_denied_ranger_quests"

static string  master_ranger_file;
static int     orccamp_info,
               company_no;

/* prototypes */
public void		create_master_ranger();
public int		set_company_no(int no);
public void		arm_me();
public varargs string	introduce(mixed who);
public string		new_token();
public string		def_answer();
public void		enchant_seed();
public void		retrieve_banner();
public void		missing_ranger();
public string		give_task();
public string		inform_gondor();
public string		inform_ithilien();
public string		inform_north();
public string		inform_orc_camp();
public string		inform_disclose();
public void		do_thank(object pl, int no);
public void		quest_done(int no, object pl);
public void		quest_not_done(int i, object pl);
public void		test_quest_done(object ob);
public void		enter_inv(object ob, object from);
public varargs string	short(object for_obj);
public int		is_captain_of_this_company(object pl);
public int		list_pupils(string str);
public nomask void	create_ranger();
public void		init_living();

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

public int     query_company_no()		 { return company_no; }
public void    set_master_ranger_file(string fn) { master_ranger_file = fn; }
public string  query_master_ranger_file()	 { return master_ranger_file; }

public void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP_DIR + "dlsword")->move(TO);
    command("wield longsword");
    clone_object(ARM_DIR + "drcloak")->move(TO);
    command("wear cloak");
    clone_object(ARM_DIR + "dlboots")->move(TO);
    command("wear boots");
}

public varargs string
introduce(mixed who)
{
    object  player;

    if (objectp(who))
    {
        player = who;
        who = player->query_real_name();
    }
    else if (stringp(who))
    {
        who = LOW(who);
        player = find_living(who);
    }

    if (!objectp(player))
        player = TP;
    if (!interactive(player))
        return "";
 
    if (!present(player,ENV(TO)))
        return "";
 
    command("hail " + who);
    command("say My name is "+query_name()+". I am a Master Ranger here.");
    command("introduce me");
    return "";
}


/*
 * Function name:	new_token
 * Description	:	restore the player's ranger token
 * Returns	:	string "" -- always (msgs written here)
 *
 * if player is ranger and asked for token of her/his company and
 * and is in that company's guildhall and doesn't already have a token,
 * (or has wrong token, which we remove) give 'em a new one.
 *
 * call is set up via add_ask().
 */
public string
new_token()
{
    int	tp_company = query_bin_bits(1, 16, 2, TP);
    string	q = query_question(),
		request;
    object	tp_token;

    if (!IS_RANGER(TP))
    {
	command("frown");
	command("say You must join our guild first!");
	return "";
    }

    if (!sscanf(q, "for %s", request))
    {
	request = q;
    }
    if (request == "token")
    {
	request = TOKEN_NAME[tp_company];
    }
    else if (request != TOKEN_NAME[tp_company])
    {
	/* asking for token not of her/his company */
	if (tp_company != CNO_PUPILS)
	{
	    /* and already belongs to a company */
	    command("frown");
	    command("say Why would a ranger of "+
		COMPANY[tp_company]+" want "+LANG_ADDART(request)+
		", instead of "+LANG_ADDART(TOKEN_NAME[tp_company])+"?");
	}
	else
	{
	    /* is a pupil */
	    command("say If you want "+LANG_ADDART(request)+
		", you must join the Rangers of "+
		COMPANY[member_array(request, TOKEN_NAME)]+".");
	}
	return "";
    }

    /* asking for the token of her/his company */
    if (request == TOKEN_NAME[company_no])
    {
    	/* and is in that company's guildhall */
    	if (objectp(tp_token = present("ranger_guild_object",TP)))
    	{
	    /* has a token */
	    if (tp_token->query_name() == request)
	    {
		/* has the correct token -- bail out */
		command("peer "+TP->query_real_name());
		command("say You already have "+LANG_ADDART(request)+"!");
		return "";
	    }
    
	    /* has the wrong token */
	    command("say Hmm, you shouldn't have that " +
		tp_token->query_name()+".");
	    command("say Well, I'll exchange it for "+
		LANG_ADDART(request)+"!");
	    tp_token->remove_object();
	}
	else
	{
	    /* doesn't have any token */
            command("say Lost your "+request+", have you?");
            command("say Be more careful with the new one!");
	}
    
    	/* give the token */
    	RANGER_GUILD->give_token(TP, 0);
    	command("smile");
        write_file(RANGER_LOG, "RANGERS: "+TP->query_name()+
            " given a new "+request+" on "+
	ctime(time())+".\n");
	return "";
    }

    /* asking for token of her/his company but not in that guildhall */
    switch (tp_company)
    {
    case CNO_PUPILS:
    case CNO_GONDOR:
        command("say You will have to go to Amaron, the master "+
	    "ranger in Gondor,");
        command("say if you want a new ring.");
        break;
    case CNO_ITHILIEN:
        command("say You will have to go to Mablung, the master "+
	    "ranger in Ithilien,");
        command("say if you want a new amulet.");
        break;
    }
    command("shrug");
    return "";
} /* new_token */

public string
def_answer()
{
    command("say I do not know what you are talking about!");
    return "";
}

public void
enchant_seed()
{
    command("say Amaron, master ranger of the Gondor Company sent");
    command("say me a message that their main supplier of herbs");
    command("say has asked him for help. Maybe you could go and");
    command("say talk to Amaron for further information?");
}

public void
retrieve_banner()
{
    if (!TP->query_prop(CLAIMING_HARAD_BANNER))
    {
	if (TP->query_prop(DID_VISIT_HARADCAMP,1))
	{
            if (present("_harad_banner_from_camp_",TP))
	    {
		/* player brought back banner before having been 
		 * assigned the quest -- following quest docs, perhaps?
		 */
        	command("say What are you running around, waving "+
			"that enemy banner for!?");
        	command("say I find that offensive, to put it mildly!");
        	command("scowl");
        	command("say Leave, and don't come back again today!");
        	command("spit");
        	TP->add_prop(NO_MORE_RANGER_QUESTS_TODAY,1);
        	return;
	    }
	    /* already visited camp today -- try later */
            command("say I don't think I need you to do any tasks today.");
            command("say Please come back some other day.");
            return;
        }

	/* ok, tell 'em about the banner */
	command("say A Ranger who travelled in Ithilien reported that he");
	command("say had seen a large army camped in the southern forest.");
	command("say He did not have the time to identify the forces of");
	command("say that army, and we need to know who we are dealing with.");
	command("say I want a proof of what army it is, preferably a banner");
	command("say showing their symbol, that would be good enough for");
	command("say our Captain. But be careful, and don't be too brave!");
	TP->add_prop(CLAIMING_HARAD_BANNER,1);
        START_QUEST(TP, "HARAD BANNER");
	return;
    }

    /* we've already told them about the banner -- maybe they
     * didn't hear the first time.
     */
    command("sigh impatiently");
    command("say Listen closely this time!");
    command("say A Ranger who travelled in Ithilien reported that he");
    command("say had seen a large army camped in the southern forest.");
    command("say He did not have the time to identify the forces of");
    command("say that army, and we need to know who we are dealing with.");
    command("say I want a proof of what army it is, preferably a banner");
    command("say showing their symbol, that would be good enough for");
    command("say our Captain. But be careful, and don't be too brave!");
}

public void
missing_ranger()
{
    command("say As soon as we heard of the large army camped in Ithilien,");
    command("say we sent a ranger named Leydon to scout the area further.");
    command("say We probably should have left that business for the");
    command("say Rangers of Ithilien, but too late to regret it now.");
    command("say Leydon hasn't returned. I want you to find out what has");
    command("say happened to him. If he is alive - bring him back");
    command("say to me. If not - bring proof of his demise.");
    TP->add_prop(LOST_RANGER_SEARCHER, 1);
    START_QUEST(TP, "LOST RANGER");
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
/*
    else if (IS_RANGER(TP))
    {
        ask_about_reports();
    }
*/
    else
        command("say I'm sorry - I have no tasks for you today.");

    return "";
}

public string
inform_gondor()
{
    command("say Gondor is a beautiful land.");
    command("say The main problem is the Enemy in the East.");
    command("say How can anyone live peacefully when large armies are "
      + "mustering to attack them?");
    command("sigh");
    return "";
}

public string
inform_ithilien()
{
    command("say Ithilien is even fairer than Gondor, some say.");
    command("say I haven't seen it myself, but when I do, I hope it is once "
      + "again a free land, and not corrupted by the orcs from Mordor.");
    command("spit");
    command("say If you are not a ranger, do not go there without permission from the Steward of Gondor!");
    command("say In these troubled days, you cannot just visit Ithilien.");
    command("say In Ithilien, the forces of Gondor know only friends and foes, "
      + "and those who do not serve Gondor will be treated as servants of the Dark Tower!");
    if (!IS_RANGER(TP))
        command("say Go to Minas Tirith and ask Hunthor. He might grant you the right to go to Ithilien.");
    return "";
}

public string
inform_north()
{
    command("say In the North was Arnor, the sister-kingdom of Gondor.");
    command("say It was a large and beautiful kingdom.");
    command("say But the accursed Witch-king of Angmar attacked, and after "
      + "a long war destroyed the kingdom totally.");
    command("say What's left there now is an empty land, and a few small villages.");
    command("say Halflings live there, and Rangers protect them from the world.");
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
        command("say The army surely contains Orcs, but we think there "
          + "may be humans there too.");
        command("say It would be good to know where those humans are from.");
        command("say In any case, be careful there. Red Eye Orcs are dangerous.");
        return "";
    }
    command("say The orc-camp is large.");
    command("say The orcs camped there are fierce orcs of the Red Eye army of Mordor.");
    command("say They have been joined by an army of Haradrim soldiers.");
    command("say The dark-skinned Haradrim are even fiercer fighters "
      + "than the Orcs of the Red Eye. Be careful there.");
    return "";
}

public string
inform_osgiliath_bridge()
{
    if ((rq_stage() < RQ_OSGILIATH_BROKEN) ||
        (rq_stage() >= RQ_OSGILIATH_FIXED))
    {
        command("say Osgiliath is in Gondorian hands currently, and we may cross "
          + "the bridge under the protection of soldiers from the Army of Gondor.");
    }
    else
    {
        command("say Forces from Imlad Morgul tried to capture Osgiliath recently.");
        command("sigh .");
        command("say Some of our men, along with soldiers of the Army of Gondor, "
          + "were forced to destroy the bridge to prevent the Enemy from crossing "
          + "the River Anduin and swarming into Anorien.");
        command("say For now you may cross the river on a ferry that we have set up.");
    }
    return "";
}   

public string
inform_disclose()
{
    list_pupils(query_question());
    return "";
}

public void
do_thank(object pl, int no)
{
    if (no == 0)
        command("say You have braved a great risk, but you have already"
          + " brought us that banner!");
    else if (no == 1)
    {
        command("say Ah, so you've helped us again! Thanks so much, but"
          + " I can't give you any reward this time.");
        command("smile "+pl->query_real_name());
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
            command("say The army is from Harad, from the lands south of Gondor!");
            if ((pl->query_prop(CLAIMING_HARAD_BANNER) == 0) ||
                (pl->query_prop(NO_MORE_RANGER_QUESTS_TODAY) == 1))
            {
                command("say But why did you bring this to me? I have not asked for it.");
                command("shrug");
                pl->add_prop(NO_MORE_RANGER_QUESTS_TODAY, 1);
                return;
            }
            else if (pl->query_prop(DID_VISIT_HARADCAMP) != 2)
            {
                command("say I'm thankful that you have revealed this to us.");
                if (pl->query_prop(DID_VISIT_HARADCAMP) == 1)
                    command("say But I have reason to believe you have not even"
                      + " been to the enemy camp after I gave you the quest.");
                else
                    command("say But I have reports that you have not even been to"
                      + " the enemy camp today.");
                command("say I do not like to be cheated, so you will not become"
                  + " more experienced by this. Now leave!");
                pl->add_prop(NO_MORE_RANGER_QUESTS_TODAY,1);
                pl->remove_prop(DID_VISIT_HARADCAMP);
                pl->remove_prop(CLAIMING_HARAD_BANNER);
                return;
            }
            command("thank "+pl->query_real_name());
            pl->remove_prop(CLAIMING_HARAD_BANNER);
            pl->remove_prop(DID_VISIT_HARADCAMP);
            pl->set_bit( TOUR_GROUP, HARAD_BANNER_BIT);
            pl->add_exp_quest(HARAD_BANNER_EXP);
            LOG_QUEST(pl, HARAD_BANNER_EXP, "HARAD BANNER");
            pl->catch_msg("You feel more experienced.\n");
            orccamp_info = 1;
            present("_harad_banner_from_camp_",TO)->remove_object();
        }
    }
    else if (pl->test_bit("Gondor", GONDOR_GROUP, LOST_RANGER_BIT))
        do_thank(pl,1);
    else
    {
        command("say Alas! Leydon's ring! I understand he is not with us"
          + " anymore then.");
        command("sigh");
        if (pl->query_prop(LOST_RANGER_SEARCHER) != 2)
        {
            command("say But something tells me this is not something "
              + "you discovered yourself.");
            command("say I think I will wait with rewarding you till I "
              + "know you deserve it.");
            return;
        }
        command("say I'm thankful that you found out the truth for us though.");
        command("thank "+pl->query_real_name());
        pl->set_bit( GONDOR_GROUP, LOST_RANGER_BIT);
        pl->add_exp_quest(LOST_RANGER_EXP);
        LOG_QUEST(pl, LOST_RANGER_EXP, "LOST RANGER");
        pl->catch_msg("You feel more experienced.\n");
        if (pl->query_prop("_gondor_met_rangers_wife"))
        {
            command("say Could you perhaps go to Minas Tirith and give the ring"
              + " to Leydon's widow? I know, she would appreciate it.");
            command("give ring to "+pl->query_real_name());
            command("smile");
        }
    }
}

public void
quest_not_done(int i, object pl)
{
    command("say Well, this is the banner of the Orcs of Mordor,"
      + " but it was hardly a surprise we would find those in Ithilien.");
    command("chuckle");
    command("say No, the scout said there were humans in that army too.");
    command("say I wanted the banner of the humans, not the Orcs.");
    command("say Please try again, will you? Thanks for your effort.");
    present("_red_eye_banner_from_camp_",TO)->remove_object();
}

public void
test_quest_done(object ob)
{
    if (present("_red_eye_banner_from_camp_",TO) == ob)
        quest_not_done(0,TP);
    else if (present("_harad_banner_from_camp_",TO) == ob)
        quest_done(0,TP);
    else if (present("Ranger_Quest_Ring",TO) == ob)
        quest_done(1,TP);
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
    string  desc,
           *adj;

    if (!for_obj)
        for_obj = TP;

    if (notmet_me(for_obj))
    {
        // desc = TO->query_nonmet_name();
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

public int
is_captain_of_this_company(object pl)
{
    int co;
    switch(company_no) 
    {
        case 1:
            return (COUNCIL->query_gondor() == TP->query_name());
        break;
        case 2:
            return (COUNCIL->query_ithilien() == TP->query_name());
        break;
        default:
            return 0;
    }
}

public int
query_is_recruiter(object pl)
{
    if (!objectp(pl))
        return 0;
    if (pl->query_skill(SS_MASTER_TASK) == RECRUITER)
        return 1;
}

public int
can_check_applicants(object pl)
{
    if (!objectp(pl))
        pl = this_player();

    if (pl->query_ranger_mentor())
        return 1;
    else if (COUNCIL->is_officer(pl->query_real_name()))
        return 1;
    else if (query_is_recruiter(pl))
        return 1;
    else if (SECURITY->query_wiz_rank(pl->query_real_name()) > WIZ_MORTAL)
        return 1;
    else
        return 0;
}

public int
approve_application(string str)
{
    int     test,
            result;
    string  pos;

    notify_fail("Please 'vouch' for a pupil to make them your pupil.\n");
    return 0;

    if (COUNCIL->is_officer(TP->query_real_name()))
        pos = "officer";
    else if (query_is_recruiter(TP))
        pos = "recruiter";
    else if (SPONSORS->query_can_sponsor(TP->query_real_name()))
        pos = "mentor";
    else
    {
        command("say Approving applications is not for you.");
        command("stare . " + TP->query_real_name());
        return 1;
    }
    if (!strlen(str))
    {
        command("say Whose application did you want to approve?");
        return 1;
    }

    result = SPONSORS->change_applicant_status(str, "approve", pos);
    if (result == -2)
    {
        command("say " + CAP(LOW(str)) + " has not been approved by the Recruiters yet.\n");
        return 1;
    }
    else if (result == -1)
    {
        command("say " + CAP(LOW(str)) + " is not an applicant.\n");
        return 1;
    }
    else if (result == 0)
    {
        command("say " + CAP(LOW(str)) + " has already been approved "
          + "by " + LANG_ADDART(pos) + ".");
        command("say Thanks anyway.");
        command("smile " + TP->query_real_name());
        return 1;
    }
    else if (result == 1)
    {
        command("say You have now approved " + CAP(LOW(str))
          + " for admittance as a pupil.");
        write(SPONSORS->list_applicant_status(str));
        return 1;
    }
    else
    {
        command("say Something is clearly wrong. Please contact a wizard.");
        return 1;
    }
    return 1;
}

public int
deny_application(string str)
{
    if (!query_is_recruiter(TP) 
        && !COUNCIL->is_officer(TP->query_real_name()))
    {
        command("say Only a Ranger Officer or a Recruiter may do that.");
        return 1;
    }
    if (!strlen(str))
    {
        command("say Whose application did you want to deny?");
        return 1;
    }
    SPONSORS->change_applicant_status(str, "deny", 0);
    command("say You have denied " + CAP(LOW(str)) + "'s application.");
    command("say Please remember to send them a mail about it.");
    return 1;
}

public int
graduate_pupil(string str)
{
    object  pup;
    int     tp_is_mentor = 0;

    if (!strlen(str))
    {
        command("say What pupil did you want to declare graduated?");
        return 1;
    }
    tell_room(environment(TP), QCTNAME(TP) + " requests that " + QTNAME(TO)
        + " have " + CAP(LOW(str)) + " declared a graduated pupil.\n", ({TP}));

    if (!COUNCIL->is_officer(TP->query_real_name()) &&
        !TP->query_ranger_mentor())
    {
        command("say You do not have the authority to do that.");
        command("say Only an officer or the pupil's mentor may "
          + "declare a pupil graduated.");
        return 1;
    }

    str = LOW(str);
    if (!present(str, ENV(TP)))
    {
        command("say I do not see anyone named " + CAP(str) + " here.");
        return 1;
    }
    pup = present(str, ENV(TP));
    if (pup->query_company() != "the Ranger pupils")
    {
        command("peer " + TPQRN);
        command("say to " + TPQRN + " What are you trying to pull?");
        command("say to " + TPQRN + " " + CAP(PRONOUN(pup))
          + " is not a Ranger pupil!");
        command("rolleyes");
        return 1;
    }
    if ((pup->query_base_stat(SS_OCCUP) < COMP_REQUIREMENT) ||
        (pup->query_ranger_rank(2) < PUP_RANK_REQUIREMENT))
    {
        command("peer . " + str);
        command("say to " + TPQRN + " " + CAP(PRONOUN(pup))
          + " is not ready to graduate yet, I am sorry.");
        command("smile .");
        return 1;
    }
    if (!COUNCIL->is_officer(TPQRN))
    {
        if (SPONSORS->query_sponsor(pup->query_real_name()) != CAP(TPQRN))
        {
            command("say to " + TPQRN + " You are not authorized to declare "
              + CAP(str) + " graduated.");
            command("say I am sorry. I cannot help you.");
            return 1;
        }
        tp_is_mentor = 1;
    }
    SPONSORS->graduate_pupil(pup->query_real_name());
    command("bow");
    command("say to " + pup->query_real_name() + " Congratulations! "
      + "You are now considered graduated, and ready to join a company.");
    command("shake " + pup->query_real_name());
    if (tp_is_mentor)
    {
        command("say to " + TPQRN + " And congratulations to you! "
          + "Your pupil is now released from your responsibility.");
        command("say to " + TPQRN + " This means you may start "
          + "considering a new applicant that you would want to "
          + "become a Mentor for.");
        command("smile warm");
    }
    return 1;
}

public int
apply_to_rangers(string str)
{
    string  dummy;

    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " about something.\n", TP);
    if (!strlen(str))
    {
        command("say What are you trying to do? Apply to join the Rangers?");
        return 1;
    }
    if (sscanf(str, "%sanger%s", dummy, dummy) != 2)
    {
        command("say What do you mean? Do you want to apply to join the Rangers?");
        command("peer . " + TP->query_real_name());
        return 1;
    }
    if (SPONSORS->query_applicant(TP->query_real_name()))
    {
        command("say You have already applied, " + TP->query_name() + ".\n");
        return 1;
    }

    if (member_array(TP->query_exp_title(), SD_AV_TITLES) < member_array("wanderer", SD_AV_TITLES))
    {
        command("ponder");
        command("say I am sorry, but I think you may have some growing up to do first.");
        command("say Come back when you are titled a Wanderer.");
        command("smile . " + TP->query_real_name());
        return 1;
    }
    if (IS_RANGER(TP))
    {
        command("poke " + TP->query_real_name());
        command("say No thanks, jester. I know that you are a Ranger already.");
        return 1;
    }
    if (strlen(TP->query_guild_name_occ()))
    {
        command("eyebrow thought " + TP->query_real_name());
        command("say You're not serious about applying, are you?");
        command("say I mean, you are already occupied in another guild!");
        return 1;
    }
    if (TP->query_race() == "goblin")
    {
        command("emote pulls his sword and points it at you.");
        command("say Begone, orc! I am not amused!");
        return 1;
    }
    if (TP->query_race_name() == "kender")
    {
        command("peer suspic " + TP->query_real_name());
        command("say I am sorry, but I do not believe Kenders are capable");
        command("say of the seriousness the responsibilities of a Ranger demand.");
        command("say We cannot let you join.");
        return 1;
    }
    /* COMMENTED OUT< GNOMES ARE ALLOWED
    if (TP->query_race() == "gnome")
    {
        command("smile soft " + TP->query_real_name());
        command("say I am sorry, but gnomes are not considered "
          + "fit for the responsibilities of a Ranger.");
        command("say You will have to look for an occupation elsewhere.");
        return 1;
    }
    */
    if (RANGER_GUILD->query_banned(TP->query_real_name()))
    {
        command("say Your treachery against the Rangers is not that easily forgotten!");
        command("say Get out! Or I will strike you down myself!");
        command("spit");
        return 1;
    }
    if (!(SPONSORS->add_applicant(TP->query_real_name(), time(), 0)))
    {
        command("say I would register you, but I have forgotten my records somewhere!");
        command("say Please come back later, and we'll see what we can do!");
        return 1;
    }
    command("say Thank you! I have registered you as an applicant.");
    command("say If you have not already done so, you should send a letter to");
    command("say the Recruitment team, telling a bit about yourself.");
    command("say They need to know your name and full title; your previous");
    command("say allegiances - if any; when you are usually present in the");
    command("say realms; and last but not least, why you want to be a Ranger.");
    return 1;
}

public int
applicant_info(string str)
{
    if (!can_check_applicants(TP))
    {
        command("say You are not authorized to do that.");
        return 1;
    }
    if (!strlen(str))
    {
        command("say What applicant did you want to know the status of?");
        return 1;
    }
    write(SPONSORS->list_applicant_status(str));
    return 1;
}

public int
list_pupils(string str)
{
    if (!strlen(str))
    {
        command("say Disclose what?");
        if (can_check_applicants(TP))
        {
            command("say I can disclose all applicants, new applicants, "
              + "approved applicants, or denied applicants.");
            command("say I can also tell you the status of individual "
              + "applications if you do 'status <name>'. And ...");
        }
        if (IS_RANGER(TP) || TP->query_name() == "Elessar")
        {
            command("say I can disclose all pupils, pupils with mentors, "
              + "pupils without mentors, graduated pupils, all officers, "
              + "all master rangers, all mentors, mentors with "
              + "pupils, or mentors without pupils."); 
        }
        else
        {
            command("say I can disclose all officers and possible mentors.");
        }
        command("peer "+TP->query_name()+" expect");
        return 1;
    }

    switch (LOW(str))
    {
    case "all applicants":
    case "applicants":
      if (!can_check_applicants(TP))
      {
          command("say I'm sorry, but you are not authorized to see that list.");
          break;
      }
      write("These are the current applicants:\n");
      write(SPONSORS->list_applicants("all"));
      break;
    case "new applicants":
    case "fresh applicants":
    case "undecided applicants":
      if (!can_check_applicants(TP))
      {
          command("say I'm sorry, but you may not see that list.");
          break;
      }
      write("These are the applicants that have still not been "
        + "approved:\n");
      write(SPONSORS->list_applicants("fresh"));
      break;
    case "worthy applicants":
    case "ready applicants":
    case "retained applicants":
    case "approved applicants":
      if (!can_check_applicants(TP))
      {
          command("say I'm sorry, but that is none of your business.");
          break;
      }
      write("These applicants have been approved and are ready to "
        + "join:\n");
      write(SPONSORS->list_applicants("worthy"));
      break;
    case "denied applications":
    case "denied applicants":
    case "refused applications":
    case "refused applicants":
      if (!can_check_applicants(TP))
      {
          command("say That is none of your concern.");
          break;
      }
      write("These applications have been denied:\n");
      write(SPONSORS->list_denied_applicants());
      break;
    case "pupils":
    case "all pupils":
    case "ranger pupils":
    if (!IS_RANGER(TP) && TP->query_name() != "Elessar")
	{
	    command("say Why would you want to know that? You are not a Ranger.");
	    break;
	}
	write(RANGER_GUILD->print_member_list(0));
	break;
    case "pupils with mentors":
    case "mentored pupils":
    if (!IS_RANGER(TP) && TP->query_name() != "Elessar")
	{
	    command("say What are you trying to do? Spy on us?");
	    break;
	}
	write("These pupils have mentors:\n");
	write(SPONSORS->list_pupils()+".\n");
	break;
    case "mentors with pupils":
    if (!IS_RANGER(TP) && TP->query_name() != "Elessar")
	{
	    command("say I will not give secret information like that to you.");
	    break;
	}
	write("This is the current rota of mentors with their pupils:\n");
	write(SPONSORS->query_sp_list()+".\n");
	break;
    case "pupils without mentors":
    case "unmentored pupils":
    case "pupils without mentor":
    if (!IS_RANGER(TP) && TP->query_name() != "Elessar")
	{
	    command("say You won't get secret information about our guild from me!");
	    break;
	}
	write("These pupils are without mentors:\n");
	write(SPONSORS->list_free_pupils()+".\n");
	break;
    case "graduated pupils":
        if (!IS_RANGER(TP) && TP->query_name() != "Elessar")
      {
          command("say That's none of your business.");
          break;
      }
      write("These pupils have graduated and are ready to join a company:\n");
      write(SPONSORS->list_graduated_pupils());
      break;
    case "master rangers":
    case "all masters":
    case "all master rangers":
    if (!IS_RANGER(TP) && TP->query_name() != "Elessar")
	{
	    command("say That is confidential. Please go away.");
	    break;
	}
	write("Current Master Rangers are:\n");
      write(COUNCIL->query_masters() + ".\n");
	break;
    case "officers":
	command("say The current Ranger Officers are:");
        command("say as follows:\n");
        tell_room(ENV(TO), COUNCIL->query_council());
	break;
    case "all mentors":
    if (!IS_RANGER(TP) && TP->query_name() != "Elessar")
	{
	    command("say That is confidential. Go find something useful to do!");
	    break;
	}
	write("These are the current list of people who can be mentors:\n");
	write(SPONSORS->list_mentors()+".\n");
	break;
    case "possible mentors":
    case "mentors without pupils":
      command("say These Rangers do not have a pupil currently:");
	command("say "+SPONSORS->list_free_sponsors()+".");
	break;
    default:
	command("say Hmm. I seem to have lost the list you ask for.");
      if (can_check_applicants(TP))
      {  
            command("say The lists I have are: all applicants, new applicants, "
              + "approved applicants, and denied applicants.");
            command("say I can also tell you the status of individual "
              + "applications if you do 'status <name>'. And ...");
      } 
    if (IS_RANGER(TP) || TP->query_name() == "Elessar")
	    command("say I have lists of: all pupils, mentored " +
		"pupils, graduated pupils, unmentored pupils, officers, " +
            "master rangers, all mentors, possible mentors, and mentors with pupils.");
	else
	    command("say The lists I have are of: officers and possible mentors.");
	break;
    }
    return 1;
}

public nomask void
create_ranger()
{
    set_name(({"man", "dunadan", }));
    set_race_name("human");
    set_gender(G_MALE);
    set_adj("master");

    create_master_ranger();

    set_base_stat(SS_OCCUP, 100);

    add_prop(NPC_M_NO_ACCEPT_GIVE,0);

    add_chat("I have tasks to do.");

    set_cact_time(2);
    add_cact("brawl");
    add_cact("spit");

    set_default_answer(def_answer);

    add_ask(({"task","quest","job","tasks","quests","jobs","about task",
        "about quest","about job","about tasks","about quests","about jobs",
        "for task","for quest","for job","for tasks","for quests","for jobs"}),
        give_task);
    add_ask(({"for token","token", "for ring", "ring", "for amulet",
		  "amulet", }),   new_token);
    add_ask("name", introduce);
    add_ask(({"about gondor","gondor"}), inform_gondor);
    add_ask(({"about ithilien","ithilien"}), inform_ithilien);
    add_ask(({"about north","north"}), inform_north);
    add_ask(({"about osgiliath", "about bridge", "about osgiliath bridge",
      "about the bridge", "about the osgiliath bridge", "bridge", "osgiliath",}),
      inform_osgiliath_bridge);
    add_ask(({"about orc camp","orc camp"}), inform_orc_camp);
    add_ask( ({ "info", "information", "list", "pupils", "all pupils",
	"ranger pupils", "pupils with mentors", "mentored pupils",
	"mentors with pupils", "pupils without mentors", "graduated pupils",
	"unmentored pupils", "pupils without mentor", "master rangers",
	"all masters", "all master rangers", "officers", "all mentors",
	"possible mentors", "mentors without pupils" }), inform_disclose);
}

public void
init_living()
{
    ::init_living();

    add_action(approve_application, "approve");
    add_action(deny_application,    "deny");
    add_action(graduate_pupil,      "graduate");
    add_action(apply_to_rangers,    "apply");
    add_action(list_pupils,         "disclose");
    add_action(applicant_info,      "status");
}
