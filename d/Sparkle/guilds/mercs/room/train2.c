/*
 * Secondary Trainer for the Mercenary guild, by Morrigan 11/2001
 *
 * Adapted from code by Auberon Gwyneth on 19 February 2001
 */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include "../merc.h"
#include "room.h"

object gTrainer, guard1;
mapping gMembers = ([ ]);

public void
reset_room()
{
    /* Commenting this out. Dalizen and guards have left. (Gorboth)
    if (!objectp(gTrainer))
    {
        gTrainer = clone_object(MNPC + "dalizen");
        gTrainer->move(this_object(), 1);
    }

    if (!guard1)
	(guard1 = clone_object(MNPC + "merc_base"))->move(this_object());
    */

}

void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_WEP_SWORD, "effectively use swords", "sword", 0, 
	SWORD_MEMBER_SWORD_MAX,	SS_OCCUP);
    sk_add_train(SS_WEP_CLUB, "effectively use clubs", "club", 0,
	UNDEC_MEMBER_CLUB_MAX, 64, SS_OCCUP);
    sk_add_train(SS_WEP_KNIFE, "effectively use knives", "knife", 0,
	64, SS_OCCUP);
    sk_add_train(SS_DEFENCE, "defend oneself", "defence", 0, 74);
    sk_add_train(SS_PARRY, "parry weapons", "parry", 0, 74);
    sk_add_train(SS_APPR_MON, "appraise the might of enemies", "appraise enemy", 0,
	74);
    sk_add_train(SS_MERC_TACTICS, "employ mercenary tactics", 
        "mercenary tactics", 50, 100);
}

public void
create_room()
{
    set_short("East side of Camp");
    set_long("The majority of the camp is back toward the west. To the "+
	"northwest, a large building occupies most of the northern area "+
	"of the camp. A stream winds its way around this side of the "+
	"area, forming a natural barrier.\n");
    add_item(({"stream", "barrier"}), "The stream comes from the northwest "+
	"where it vanishes behind the large building. It snakes around the "+
	"eastern outskirts here, and then flows rapidly back toward the "+
	"southwest, where it fades into the distance.\n");
    add_item("building", OUT_BUILDING_DESC);
    add_item(({"tent", "tents"}), OUT_TENT_DESC); 
    add_exit(MROOM + "center.c", "west", 0, 1, 0);
    set_up_skills();
    reset_room();
}

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    return (IS_MERC(who) || who->query_wiz_level());
}

public void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
} 

public int
did_choose(string str)
{
    object mitem;

    if (!TP->query_prop(MALIGANT_CHOOSE_PERMISSION))
    {
	gTrainer->command("say Don't waste my time until you have Maligant's "+
	    "permission to choose a weapon specialization.");
	return 1;
    }

    if (TP->query_race() == "goblin")
    {
        gTrainer->command("emote scowls dericively.");
        gTrainer->command("say Curse his dwarven sense of humour, "+
            "Maligant knows damn well I do not train your kind.");
        return 1;
    }

    if (!str)
    {
        gTrainer->command("say You can only choose to specialize in swords here.");
        return 1;
    }

    if (str != "sword" && str != "swords" && str != "in sword" && str != "in swords")
    {
        gTrainer->command("say You can only choose to specialize in swords here.");
	return 1;
    }

    if (MJOIN->query_type_member(TP->query_name()) != "undeclared")
    {
        gTrainer->command("say You have already chosen a weapon specialiation! "+
	   "Don't attempt to fool me with your trickery.");
	return 1;
    }

    gTrainer->command("smile slightly");
    gTrainer->command("say The sword is a weapon of elegance, it requires "+
	"much more delicate skill than those crude clubs of Maligant's. I "+
	"can make you a master of the sword, if you are an adept student.");

    MJOIN->set_type_member(TP->query_name(), "sword");
    write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
        capitalize(TP->query_real_name()) +
        " chose to specialize in sword.\n");

    if ((mitem = present("_merc_guild_item_", TP)))
    {
        write(gTrainer->query_The_name(TP)+" takes your black leather belt and hands "+
	    "you a black leather scabbard.\n");
        setuid();
	seteuid(getuid());
        mitem->remove_object();
        clone_object(MITEM)->move(TP);
    }
    else
    gTrainer->command("say You need to go see Gnimpsh for a new belt.");

    TP->remove_prop(MALIGANT_CHOOSE_PERMISSION);
    return 1;
}

public void
init()
{
    ::init();

    add_action(did_choose, "choose");
    add_action(did_choose, "specialize");
    init_guild_support();
    init_skill_raise();
}

/* Function name: sk_query_max
 * Description  : Give the max skill we can teach to for a skill.
 * Arguments    : int snum - the skill-number to check.
 *                int silent - don't tell anything to the player if true.
 * Returns      : int - the maximum you can train the skill to.
 */
public varargs int 
sk_query_max(int snum, int silent)
{
    mixed skval;
    object pl;
    int lev = 100;
    int int_bonus;

    if (!mappingp(sk_default))
    {
        return 0;
    }

    if (!this_player() || ((this_player() != previous_object()) &&
        previous_object() != this_object()))
        pl = previous_object();
    else
        pl = this_player();

    /* To prevent skill decay of skills, even if mercenary cannot
     * actually train those skills here yet. Doesn't really make
     * sense, but is implemented for playability's sake. */
    if (silent == 1)
    {
        if (snum == SS_WEP_SWORD)
            if (MEMBER_SWORD(pl))
                return SWORD_MEMBER_SWORD_MAX;
            else if (MEMBER_CLUB(pl))
                return CLUB_MEMBER_SWORD_MAX;
            else
                return UNDEC_MEMBER_SWORD_MAX;

        skval = sk_trains[snum];
        return skval[2];
    }

    if (snum == SS_WEP_CLUB)
    {
        if (MEMBER_SWORD(pl))
	    lev = SWORD_MEMBER_CLUB_MAX;
        else 
	    lev = UNDEC_MEMBER_CLUB_MAX;
    }

    if (snum == SS_WEP_SWORD)
    {
	if (MEMBER_SWORD(pl))
	    lev = SWORD_MEMBER_SWORD_MAX;
	else if (MEMBER_CLUB(pl))
	    lev = CLUB_MEMBER_SWORD_MAX;
	else
	    lev = UNDEC_MEMBER_SWORD_MAX;
    }

    if (pl->query_stat(SS_INT) > 100)
        int_bonus = (pl->query_stat(SS_INT) - 100) / 3;
    else if (pl->query_stat(SS_INT) < 80)
        int_bonus = -(80 - pl->query_stat(SS_INT));
    else
        int_bonus = 0;

    skval = sk_trains[snum];
    if (sizeof(skval) > 2)
    {
        return MAX(30, MIN(pl->query_stat(SS_OCCUP) + int_bonus,
            MIN(skval[2], lev)));
    }

    return 0;
}

/*
 * Function name: sk_hook_no_list_learn
 * Description  : This hook is called when there are no more skills the
 *                player can learn here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_learn()
{
    gTrainer->command("say You have learned every skill from me already, "+
	"now you must practice.");
    return 1;
}

/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    gTrainer->command("say For now, your training is complete.");
    return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:     skill - The skill player wanted to improve
 * Returns:       0
 */
int
sk_hook_improved_max(string skill)
{
    gTrainer->command("say I have taught all I will teach about "+skill+
	".");
    return 1;
}

/*
 * Function name: sk_hook_not_allow_train
 * Description:   Message to print if you are not allowed to train
 * Returns:       string -- fail message
 */
public int
sk_hook_not_allow_train()
{
    gTrainer->command("say You are not a mercenary, I will not waste my "+
	"time on you.");
    return 1;
}

/*
 * Function name: sk_hook_unknown_skill
 * Description  : Player tries to improve or learn an unknown skill.
 * Arguments    : string skill - The skill he sought for.
 *                string verb  - 'learn' or 'improve'.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_unknown_skill(string skill, string verb)
{
    gTrainer->command("say I do not offer training "+
	skill+"!");
    return 1;
}

/*
 * Function name: sk_hook_improve_unknown
 * Description  : Player wants to improve a skill he has never learned.
 * Arguments    : string skill - the skill the player tried to improve.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_improve_unknown(string skill)
{
    gTrainer->command("say You have not yet learned the "+skill+" skill, "+
	"and must do so before you can work at improving it.");
    return 1;
}

/*
 * Function name: sk_hook_learn_known
 * Description  : Player wants to learn an already known skill.
 * Arguments    : string skill - the skill the player tried to learn.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_learn_known(string skill)
{
    gTrainer->command("say You have learned "+skill+" skill already.");
    return 1;
}

/*
 * Function name: sk_hook_cant_train
 * Description  : Player can't train that skill that high for some reason.
 * Arguments    : string skill - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    gTrainer->command("say You are not ready for this training, come back "+
	"later.");
    return 1;
}

/*
 * Function name: sk_hook_cant_pay
 * Description  : Player cannot pay for session. (Kill him?)
 * Arguments    : string skill  - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 *                int cost - the price that is required, in coppers.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    gTrainer->command("say You will not receive my services for free.");
    gTrainer->command("emote smiles haughtily.");
    return 1;
}

int
sk_improve(string sk)
{
    object mitem;

    if (!IS_MERC(TP))
    {
        
        return sk_hook_not_allow_train();
    }

    /* Check to make sure someone didn't change race to get by the restrictions */
    if (MEMBER_SWORD(TP) && TP->query_race() == "goblin")
    {
	gTrainer->command("say There must be some mistake here, I don't "+
	    "train goblin scum here! I can fix that!\n");
        MJOIN->set_type_member(TP->query_name(), "undeclared");
        write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
           capitalize(TP->query_real_name()) +
           " was a goblin sword user! now undeclared\n");
       
        if ((mitem = present("_merc_guild_item_", TP)))
        {
            write(gTrainer->query_The_name(TP)+" takes your black leather scabbard "+
        	"and hands you a black leather belt.\n");
            mitem->remove_object();
            setuid();
	    seteuid(getuid());
	    clone_object(MITEM)->move(TP);
        }
       else
        gTrainer->command("say You need to go see Gnimpsh for a new holster.");
    }
    
    if (MEMBER_CLUB(TP) && TP->query_race() == "hobbit")
    {
	gTrainer->command("say Who did you steel that holster from? Give it "+
	    "to me!");
	gTrainer->command("say I train all the halfling folk.");

        MJOIN->set_type_member(TP->query_name(), "undeclared");
        write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
           capitalize(TP->query_real_name()) +
           " was a hobbit club user! now undeclared.\n");
       
        if ((mitem = present("_merc_guild_item_", TP)))
        {
            write(gTrainer->query_The_name(TP)+" takes your black leather holster "+
        	"and hands you a black leather belt.\n");
            mitem->remove_object();
            setuid();
	    seteuid(getuid());
	    clone_object(MITEM)->move(TP);
        }
       else
        gTrainer->command("say You need to go see Gnimpsh for a new holster.");
    }

    return ::sk_improve(sk);
}
