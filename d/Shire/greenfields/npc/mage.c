/*
 * /d/Shire/greenfields/npc/mage
 * This mage is created using the standard Morgul Mage from Gondor
 * Thanks to Olorin, Elessar, myself, and all others who participated
 * in the creation of that guild and this code.
 * Mayhem  Sept 7, 1994
 * Modified for quest use by Dunstable Nov 6, 1994
 * Credit again goes to Olorin- he made the locket quest functions :)
 *
 *  Modified by Igneous to use the Shire questmaster June 1998
 *  Modified by Stern for unique check for black platemails, April 2000
 *  Modified by Shanoga to remove "much" from quest reward text, Aug 2019
 */

inherit "/d/Gondor/common/guild2/newnpc/npc_mage";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define QUEST_NAME "mage"
#define Q_MASTER  "/d/Shire/sys/global/quest_master"
#define GREEN_DIR "/d/Shire/greenfields/"
#define CAMP_DIR   (GREEN_DIR + "camp/")
#define MAGE_HOME  (CAMP_DIR + "tent15")
#define WEP_ARRAY1 ({GREEN_DIR + "wep/hmstar"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/platehelm"})
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/platemail_unique"})

#define MAGES_MEET_SAYS ({ "Ah, reinforcements!",\
        "Here to help take the Shire are you?",\
        "I could go for a long pull on a bottle of ghash-water right now." })

#define GENERAL_SAYS1   ({ "The power of Dark Sorcery is supreme.",\
        "We will remake this land in the image of Mordor!",\
        "All will fall before the strength of Mordor!!" })

#define GENERAL_SAYS2   ({ "Remember, the Eye sees all.",\
        "Only the foolish resist the forces of the Dark Lord."\
                        })
#define KILL_ACTIONS   ({ "msneer","mlaugh"\
                        })

int     react_c,
        react_alarm,
        def_c,
        def_alarm,
	home_alarm;


string give_task();
void drop_this_item(object obj);
void go_home();

void
create_mage()
{
    int     rnd = random(10);

    set_name("mauhur");
    set_living_name("mauhur");
    remove_adj(({"dark-skinned", "red-eyed"}));
    set_adj(({"light-skinned", "dark-haired"}));
    set_alignment(MORGUL_I_ALIGN_JOIN - 150);

    set_attack_chance(0);
    set_restrain_path(CAMP_DIR);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_stats(({75+rnd, 75+rnd, 79+rnd, 85+rnd, 80-rnd, 85+rnd,0, 85+rnd,0}));
    add_prop("_live_m_no_drain", 1);
    add_chat("If only I had that jewel from the master's scimitar...");
    add_chat("I hate it here. Gorgun and his lieutenant think " +
        "they are more powerful.");

    add_act("eat all");
    add_act("twirl idly");
    add_act("twirl combat");
    add_cact("twirl threat");
    add_cact("twirl combat");
    add_act("drink all");
    add_ask(({"gorgun","scimitar","jewel"}),VBFC_ME("give_task"));
}

void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
}

void
loot_corpse()
{
    command("get all from corpse");
    command("spit");
    command(ONE_OF_LIST(KILL_ACTIONS));
}

void
init_living()
{
    object  tp = TP;

    ::init_living();

    if (!interactive(tp) ||
	!CAN_SEE(TO, tp))
	return;

    set_alarm(3.0, 0.0, "react_meet", tp);
}

void
react_meet(object tp)
{
    string  occ,
    name = tp->query_real_name();

    if (!present(tp, ENV(TO)))
	return;

    occ = tp->query_guild_name_occ();

    switch(occ)
    {
    case GUILD_NAME:
	command("hail "+name);
	command("rasp Good to see a familiar face.");
	react_c = 0;
	remove_alarm(react_alarm);
	react_alarm = set_alarm(4.0, 5.0, "react_morgul", tp);
	break;
    case "Rangers of the Westlands":
	command("snarl "+name);
	command("shout Death to all rangers!");
	break;
    case "The Ancient Mystic Order":
	command("tempt "+tp->query_real_name());
	if (react_c == 0)
	{
	    remove_alarm(react_alarm);
	    react_alarm = set_alarm(3.2, 4.5, "react_mystic", tp);
	}
	break;
    case "Calian warrior's guild":
	command("cackle");
	command("hiss I'll rip Calia's colours off your dead body, " +
        tp->query_name()+"!");
	break;
    case "Solamnian Knights":
	command("hiss Paladine can't help you any more, " +
        tp->query_name()+"!");
	command("sneer");
	break;
    case "Dragonarmy":
	command("hiss Takhisis is not worthy of life. And you, you " +
        "are are even more worthless, pitiful "+ tp->query_name()+"!");
	command("sneer");
        command("kill "+name);
        break;
    default:
	if ((!tp->query_met(query_real_name())) && (tp->query_alignment() < 0))
	    command("present me");
	if (react_c == 0)
	{
	    remove_alarm(react_alarm);
	    react_alarm = set_alarm(2.7, 6.0, "react_default", tp);
	}
	break;
    }
}

void
react_morgul(object tp)
{
    if (!present(tp, ENV(TO)))
    {
	react_c = 0;
	remove_alarm(react_alarm);
    }

    switch(react_c++)
    {
    case 0:
	command("present me");
	break;
    case 2:
	command("rasp "+ONE_OF_LIST(MAGES_MEET_SAYS));
	break;
    case 5:
	command("rasp "+ONE_OF_LIST(GENERAL_SAYS2));
	break;
    case 9:
	react_c = 0;
	remove_alarm(react_alarm);
	break;
    default:
	break;
    }
}

void
react_dragonarmy(object tp)
{
    if (!present(tp, ENV(TO)))
    {
	react_c = 0;
	remove_alarm(react_alarm);
    }

    switch(react_c++)
    {
    case 0:
	command("present me");
	break;
    case 2:
	command("pat "+tp->query_real_name());
	break;
    case 4:
	command("hiss "+ONE_OF_LIST(GENERAL_SAYS2));
	break;
    case 8:
	command("hiss "+ONE_OF_LIST(GENERAL_SAYS1));
	break;
    case 9:
	react_c = 0;
	remove_alarm(react_alarm);
	break;
    default:
	break;
    }
}

void
react_mystic(object tp)
{
    if (!present(tp, ENV(TO)))
    {
	react_c = 0;
	remove_alarm(react_alarm);
    }

    switch(react_c++)
    {
    case 2:
	command("beckon "+tp->query_real_name());
	break;
    case 6:
	command("hiss your ancients have deserted you in your hour " +
        "of need, " + tp->query_name()+".");
	break;
    case 7:
	react_c = 0;
	remove_alarm(react_alarm);
	break;
    default:
	break;
    }
}

void
react_default(object tp)
{
    if (!present(tp, ENV(TO)))
    {
	react_c = 0;
	remove_alarm(react_alarm);
    }

    switch(react_c++)
    {
    case 2:
	command("beckon "+tp->query_real_name());
	break;
    case 5:
	command("hiss "+ONE_OF_LIST(GENERAL_SAYS1));
	break;
    case 9:
	command("hiss "+ONE_OF_LIST(GENERAL_SAYS2));
	break;
    case 10:
	react_c = 0;
	remove_alarm(react_alarm);
	break;
    default:
	break;
    }
}

string
default_answer()
{
    if (!def_c)
	def_alarm = set_alarm(2.0, 2.5, "default_react", TP);
    return "";
}

void
default_react(object tp)
{
    if (!present(tp, ENV(TO)))
    {
	def_c = 0;
	remove_alarm(def_alarm);
    }

    switch(def_c++)
    {
    case 0:
	if (tp != query_attack())
	    command("peer "+tp->query_real_name());
	break;
    case 1:
	if (tp == query_attack())
	    command("hiss ask Death for you shall meet him soon!");
	else
	    command("hiss Only a pitiful fool would ask about that!");
	break;
    case 2:
	command("cackle");
	break;
    case 3:
	if (tp != query_attack())
	    command("pat "+tp->query_real_name());
	def_c = 0;
	remove_alarm(def_alarm);
	break;
    default:
	break;
    }
    if (tp = query_attack())
    {
	return;
    }

}

string give_task()
{
    if (!Q_MASTER->check_quest(TP, QUEST_NAME))
    {
	command("hiss Silence, fools.");
	if(TP->query_prop("_magebane_quest"))
	{
	    command("glare " + TP->query_name());
	    command("hiss Do you think all I do is stand around here " +
            "and repeat myself?");
	    return "";
	}
	command("hiss That blasted Gorgun! If he didn't have that " +
        "repulsive army backing him.");
	command("msneer");
	command("hiss scimitar of his, I'd be running the show.");
	command("hiss Bring me the jewel from his scimitar and I " +
        "shall reward you dearly!");
	command("hiss If you fail me, I will punish you.");
	command("msmile");
	TP->add_prop("_magebane_quest",1);
	return "";
    }
    else
    {
	command("hiss I need you not, fool!\n");
	return "";
    }
}

void test_locket_quest(object player)
{
    if (!player->query_prop("_i_got_the_leech_jewel"))
    {
	command("cackle evil");
	command("hiss You? You were strong enough to get this jewel?");
	command("hiss I don't think so!");
	command("emote mumbles something about pitiable puny mortals.");
	return;
    }

    if (!player->query_prop("_magebane_quest"))
    {
	command("eyebrow "+player->query_real_name());
	command("hiss I did not ask you to fetch this for me!");
	command("hiss Nonetheless I will keep it.");
	command("hiss You may leave me now giver of gifts unasked for.");
	command("smile sarc");
	return;
    }

    if (!Q_MASTER->reward_quest(player, QUEST_NAME))
    {
	command("hiss I'm not stupid. Get out of here!");
	return;
    }
    else
    {
	command("emote cackles with delight.");
	command("hiss Now there's a pretty stone, isn't it?");
	command("emote tucks the jewel away in a hidden pouch.");
	command("hiss You have done nicely!");
	command("hiss Gorgun will get his now!");
	command("hiss And you will get yours.");
	player->remove_prop("_magebane_quest");
	tell_object(player,"You feel more experienced!\n");
	say(QCTNAME(player) + " got a nice reward.\n");
    }
}


public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    /*command("say DEBUG: enter_inv entered with from = " + (objectp(from) ? from->query_name() : " no object ") +
    " and obj = " + (objectp(obj) ? obj->query_name() : " no object "));*/
    if (!living(from))
	return;
    if (obj->id("_leech_jewel_"))
	set_alarm(1.0,0.0, &test_locket_quest(from));

    else
    {
	set_alarm(1.0, 0.0, &drop_this_item(obj));
	return;
    }
}

void
drop_this_item(object obj)
{
    command("hiss What would I want with that, pitiful fool?");
    command("drop "+ OB_NAME(obj));
    return;
}


/*
 * Function name:	enter_env
 * Description	:	mask parent to log if leave our restrain_path
 *			and move us back
 * Arguments	:	object dest -- new env
 *			object old -- old env
 *
 * The problem may be that we don't call set_monster_home(). In
 * monster_ranwalk(), if home isn't set and there are no exits
 * that match the restrain path, it'll move anywhere.
 * However, it's not clear that we want to teleport all the way back
 * to our tent, which is the behaviour provided by setting monster home.
 * For now, i'll log it and try moving back to old env first. Of course,
 * it's not clear how he gets into a room with no exits matching
 * restrain_path, in the first place. 		Gnadnar 9 Jul 1999
 */
public void
enter_env(object dest, object old)
{
    string	destname,
		tmpstr;

    ::enter_env(dest, old);
    if (home_alarm)
    {
	return;
    }

    destname = file_name(dest);
    if (sscanf(destname, (CAMP_DIR + "%s"), tmpstr))
    {
	return;
    }

    home_alarm = set_alarm(1.0, 0.0, go_home);
}

public void
go_home()
{
    string	here = file_name(environment(this_object()));

    home_alarm = 0;
    if (here != MAGE_HOME)
    {
    	log_file("mauhur",
	    ctime(time()) + " moved from " + here + " to tent.\n");
	move_living("X", MAGE_HOME);
    }
}
