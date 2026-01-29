/*
 * Primary Trainer for the Mercenary guild, by Morrigan 11/2001
 *
 * Adapted from code by Auberon Gwyneth on 19 February 2001
 */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include "../merc.h"
#include "room.h"

#define LEAVE_CAMP "/d/Sparkle/area/sparkle/room/wild/n_road2"
#define ENTER_CAMP "/d/Sparkle/guilds/mercs/room/center"

object gTrainer;
mapping gMembers = ([ ]);

public void
reset_room()
{
    if (!objectp(gTrainer))
    {
        gTrainer = clone_object(MNPC + "maligant");
        gTrainer->move(this_object(), 1);
    }
}

public object
query_maligant()
{
    return gTrainer;
}

void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_WEP_CLUB, "effectively use clubs", "club", 0, 
	CLUB_MEMBER_CLUB_MAX, SS_OCCUP, 100);
}

public int
enter_camp()
{
    if (MJOIN->query_not_allowed(TP->query_name()))
    {
	gTrainer->command("emote blocks the way into the camp.");
	gTrainer->command("say I remember you, you bastard, you aren't "+
	   "getting back in.");
	return 1;
    }

    if (MJOIN->query_warned(TP->query_name()))
    {
	gTrainer->command("emote blocks the way into the camp.");
	gTrainer->command("say You think you're sly, but I know what you "+
	   "did. Maybe some day I will forgive you. Maybe.");
	return 1;
    }

    return 0;
}

public void
create_room()
{
    set_short("Camp Entrance");
    set_long(OUTSIDE_DESC+
	"To the east is the center of the camp, and the road west "+
	"will take you back to the Dark Road.\n");
    add_item(({"tent", "tents"}), OUT_TENT_DESC);
    add_item("building", OUT_BUILDING_DESC);
    add_item(({"west", "road", "dark road"}), "To the west lies the "+
	"Dark Road, which heads south to the intersection just outside "+
	"the gates of Sparkle.\n");
    add_exit(ENTER_CAMP, "east", &enter_camp());
    add_exit(LEAVE_CAMP, "west");
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

    if(MJOIN->query_member(ob->query_real_name()))
    {
	if(MASTER_OB(to) == ENTER_CAMP) 
	    ob->catch_tell("You enter the camp.\n");
	
	if(MASTER_OB(to) == LEAVE_CAMP)
	    ob->catch_tell("You leave the camp.\n");
    }
    
    ::leave_inv(ob, to);
} 

public int
request_permission(string str)
{
    if (IS_MERC_OPEN == 0)
    {
	gTrainer->command("say I'm not accepting new mercenaries just yet. "+
	    "Try back later.");
	return 1;
    }

    if (!str)
    {
        gTrainer->command("emote folds his arms across his broad chest and "+
	    "snorts a loud 'hmph' at you!");
	gTrainer->command("say Request permission for what? A new brain?");
        return 1;
    }

    if (IS_MERC(TP))
    {
	gTrainer->command("emote yanks on his majestic beard angrily.");
	gTrainer->command("say Confound it! You're already a mercenary, "+
	    "leave me alone!");
	return 1;
    }

    if (TP->query_prop(MALIGANT_JOIN_PERMISSION, 1))
    {
	gTrainer->command("emote flushes in anger.");
	gTrainer->command("say I already gave you permission to join! "+
	    "Can't ya hear??");
	return 1;
    }

    if (str != "permission" && str != "permission to join")
    {
        gTrainer->command("emote folds his arms across his broad chest and "+
	    "snorts a loud 'hmph.'");
	gTrainer->command("say Request permission for what? A new brain?");
        return 1;
    }

    if (TP->query_average_stat() < 64)
    {
	gTrainer->command("say Sorry, "+(TP->query_gender() == 0 ? "lad" : "lass")+
	    ", we don't have much room for "+TP->query_exp_title()+"s here. Try "+
	    "the Cadets of Gelan in Calia. You can get there from pier nine in "+
	    "town.");
        return 1;
    }

    write(gTrainer->query_The_name(TP)+" looks you over with an appraising eye.\n");
    say(QCTNAME(gTrainer)+" looks "+QTNAME(TP)+" over with an appraising eye.\n");
    gTrainer->command("say I guess you'll do. Make sure you know the rules before "+
	"signing yer life away, I don't want to hear any blasted whining from ya.");
    TP->add_prop(MALIGANT_JOIN_PERMISSION, 1);
    return 1;
}

public int
did_change(string str)
{
    object mitem;

    if (!str)
    {
	gTrainer->command("emote shakes his head in exasperation.");
        gTrainer->command("say Change what, you oaf?");
        return 1;
    }

    if (!IS_MERC(TP))
    {
	gTrainer->command("emote eyes you up as a potential mercenary.");
	gTrainer->command("say I know what you should change first, "+
	(TP->query_gender() == 0 ? "lad" : "lass")+".\n");
        return 1;
    }

    if (str == "club" || str == "clubs" || str == "to club" || str == "to clubs" ||
	str == "sword" || str == "swords" || str == "to sword" || 
	str == "to swords")
    {
        gTrainer->command("say You can't change that easily, first ya got to "+
	    "change your specialization. Then, once you unlearn what you have "+
	    "already learned, you can start yer training again.");
	return 1;
    }

    if (str != "specialization" && str != "my specialization" && str != "mind"
	&& str != "weapon" && str != "choice" && str != "my mind")
    {
	gTrainer->command("say Just change yer mind ya blooming idiot!");
	return 1;
    }

    if (MJOIN->query_type_member(TP->query_name()) == "undeclared")
    {
	gTrainer->command("rolleyes");
	gTrainer->command("say You haven't even chosen a specialization yet!"+
	    " How can you be changing yer mind??");
        return 1;
    }

    gTrainer->command("emote shakes his head in disbelief.");
    gTrainer->command("say You just can't make up yer mind, can ya, "+
	(TP->query_gender() == 0 ? "lad" : "lass")+".\n");

    MJOIN->set_type_member(TP->query_name(), "undeclared");
    write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
        capitalize(TP->query_real_name()) +
        " changed status to undeclared\n");

    if ((mitem = present("_merc_guild_item_", TP)))
    {
        write(gTrainer->query_The_name(TP)+" takes your "+mitem->short()+
	    " and hands you a black leather belt.\n");
          mitem->remove_object();
          setuid();
	  seteuid(getuid());
	  clone_object(MITEM)->move(TP);
    }
    else
    gTrainer->command("say You need to go see Gnimpsh for a new belt.");
    
    return 1;
}

public int
did_choose(string str)
{
    object mitem;

    if (!str)
    {
        gTrainer->command("say You can only specialize in clubs or swords here.");
        return 1;
    }

    if (!IS_MERC(TP))
    {
	gTrainer->command("emote snorts derisively.");
	gTrainer->command("say Aye, you're a mercenary all right, and I'm a "+
	    "bearded gnome! Get out of here!");
        return 1;
    }

    if (str != "club" && str != "clubs" && str != "in club" && str != "in clubs" &&
	str != "sword" && str != "swords" && str != "in sword" && 
	str != "in swords")
    {
        gTrainer->command("say You can only specialize in swords or clubs here.");
	return 1;
    }

    if (MJOIN->query_type_member(TP->query_name()) != "undeclared")
    {
	gTrainer->command("growl irritably");
	gTrainer->command("say You have already chosen to specialize in "+
		MJOIN->query_type_member(TP->query_name())+"s! Stop wasting "+
		"my time!");
        return 1;
    }

    if (TP->query_skill(SS_WEP_CLUB) < UNDEC_MEMBER_CLUB_MAX ||
	 TP->query_skill(SS_WEP_SWORD) < UNDEC_MEMBER_SWORD_MAX)
    {
	gTrainer->command("rolleyes");
	gTrainer->command("say You can barely fight worth a damn as it is, how "+
	    "can you know what you want to specialize in? Come back when you've "+
	    "educated yourself a bit more.");
        return 1;
    }

    if (TP->query_race() == "hobbit")
    {
	gTrainer->command("say Oh no! I don't train your kind here. I won a bet "+
	    "with Dalizen, now he has to train all the little halfling sorts. "+
	    "Even the Kender!");
	gTrainer->command("emote slaps his knees and roars with laughter.");
	TP->add_prop(MALIGANT_CHOOSE_PERMISSION, 1);
	return 1;
    }

    if (TP->query_skill(SS_WEP_SWORD) > CLUB_MEMBER_SWORD_MAX)
    {
        gTrainer->command("say Apparently you have chosen to specialize in swords "+
	    "already! You are too set in your ways, and "+
	    "will have to unlearn that before I will bother teaching you.");
	gTrainer->command("say If Dalizen wishes to teach you, I will allow it.");
        TP->add_prop(MALIGANT_CHOOSE_PERMISSION, 1);
        return 1;
    }

    if ((str == "sword" || str == "swords" || str == "in sword" || 
	str == "in swords")
	&& TP->query_skill(SS_WEP_CLUB) > SWORD_MEMBER_CLUB_MAX)
    {
	gTrainer->command("say You're already skilled with a club, why would you "+
	    "resort to using a pointy stick? I'll give ya some time to mull that "+
	    "one over.");
	gTrainer->command("wink");
	return 1;
    }

    if (str == "sword" || str == "swords" || str == "in sword" || 
	str == "in swords")
    {
	gTrainer->command("say Only weak-armed folk prefer pointy sticks to a "+
	    "nice solid club, but suit yourself. If that's what you want, be "+
	    "my guest.");
	gTrainer->command("chuckle amusedly");
	TP->add_prop(MALIGANT_CHOOSE_PERMISSION, 1);
	return 1;
    }

    if (TP->query_prop(MALIGANT_CHOOSE_PERMISSION))
        TP->remove_prop(MALIGANT_CHOOSE_PERMISSION);

    gTrainer->command("grin broad");
    gTrainer->command("say So you would be a master with the club? A good choice, "+
	(TP->query_gender() == 0 ? "lad" : "lass")+". Soon you will be walloping "+
        "Dalizen's silly stick-wielders.");


    MJOIN->set_type_member(TP->query_name(), "club");
    write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
        capitalize(TP->query_real_name()) +
        " chose to specialize in club\n");

    if ((mitem = present("_merc_guild_item_", TP)))
    {
        write(gTrainer->query_The_name(TP)+" takes your black leather belt "+
	    "and hands you a black leather holster.\n");
          mitem->remove_object();
          setuid();
	  seteuid(getuid());
	  clone_object(MITEM)->move(TP);
    }
    else
    gTrainer->command("say You need to go see Gnimpsh for a new holster.");


    
    return 1;
}

public void
init()
{
    ::init();

    add_action(did_change, "change");
    add_action(did_choose, "choose");
    add_action(did_choose, "specialize");
    add_action(request_permission, "request");
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

    /* To prevent the mercy skill from decaying */
    if (snum == SS_MERC_MERCY)
        return 1;

    /* To prevent the mtitle skill from decaying */
    if (snum == SS_MERC_TITLE)
        return 4;

    /* To prevent the mattack auto skill from decaying */
    if (snum == SS_MERC_AUTOMATTACK)
	return 1;

    /* To prevent the autocomply skill from decaying */
    if (snum == SS_MERC_AUTOCOMPLY)
	return 1;

    /* To prevent the gagdog skill from decaying */
    if (snum == SS_MERC_GAG_DOG)
        return 1;

    /* To prevent skill decay of skills, even if mercenary cannot
     * actually train those skills here yet. Doesn't really make
     * sense, but is implemented for playability's sake. */
    if (silent == 1)
    {
        if (snum == SS_WEP_CLUB)
            if (MEMBER_CLUB(pl))
                return CLUB_MEMBER_CLUB_MAX;
            else if (MEMBER_SWORD(pl))
                return SWORD_MEMBER_CLUB_MAX;
            else
                return UNDEC_MEMBER_CLUB_MAX;

        skval = sk_trains[snum];
        return skval[2];
    }

    if (pl->query_stat(SS_INT) > 100)
        int_bonus = (pl->query_stat(SS_INT) - 100) / 3;
    else if (pl->query_stat(SS_INT) < 80)
        int_bonus = -(80 - pl->query_stat(SS_INT));
    else
        int_bonus = 0;

    if (snum == SS_WEP_CLUB && MEMBER_CLUB(pl))
        return MIN(CLUB_MEMBER_CLUB_MAX, pl->query_stat(SS_OCCUP) + int_bonus);

    if (snum == SS_WEP_CLUB)
	return 0;

    skval = sk_trains[snum];
    if (sizeof(skval) > 2)
    {
        return skval[2];
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
    gTrainer->command("say Looks like ya've learned the skills, now you "+
	"just need to practice them.");
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
    gTrainer->command("say I think yer done training for now, "+
	"now go adventure and find me some more mercenaries.");
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
    gTrainer->command("say I already taught you all I know about that. "+
	"Or all I'm gonna teach you, anyway!");
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
    gTrainer->command("say Get the hell out of here, I'm not training you "+
	"to do squat!");
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
    gTrainer->command("say I don't have the foggiest idea about training "+
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
    gTrainer->command("say You haven't even learned "+skill+" skill yet, "+
	"how can you be improving it?");
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
    gTrainer->command("say Ya already learned "+skill+" skill, genius.");
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
    gTrainer->command("say You just don't seem to be getting the hang of "+
	"this, come back later.");
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
    gTrainer->command("say What do you think this is, a charity?!");
    gTrainer->command("emote slaps his knee and roars with laughter.");
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
    if (MEMBER_CLUB(TP) && TP->query_race() == "hobbit")
    {
	gTrainer->command("say There must be some mistake here, I don't "+
	    "train hobbits!\n");
        MJOIN->set_type_member(TP->query_name(), "undeclared");
       write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
           capitalize(TP->query_real_name()) +
           " was a hobbit sword user! now undeclared\n");
       
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
    
    if (MEMBER_SWORD(TP) && TP->query_race() == "goblin")
    {
	gTrainer->command("say Who did you steel that scabbard from? Give it "+
	    "to me!");
	gTrainer->command("say Dalizen won't train goblins, and I know that's "+
	    "true.");

        MJOIN->set_type_member(TP->query_name(), "undeclared");
       write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
           capitalize(TP->query_real_name()) +
           " was a goblin sword user! now undeclared\n");
       
        if ((mitem = present("_merc_guild_item_", TP)))
        {
            write(gTrainer->query_The_name(TP)+" takes your black leather "+
	        "scabbard and hands you a black leather belt.\n");
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
