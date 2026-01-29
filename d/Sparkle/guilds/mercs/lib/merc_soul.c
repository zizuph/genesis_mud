/*
 * /d/Genesis/guilds/merc/merc_soul.c
 *
 * Mercenary Soul, by Morrigan 10/2001
 *
 * Other relevant files:
 * specials          - /d/Genesis/guilds/merc/specials.h
 * emotes            - /d/Genesis/guilds/merc/emotes.h
 * language	     - /d/Genesis/guilds/merc/merc_lang.h
 *
 * Adapted from code by Gwyneth and Auberon
 *
 * Modification log:
 *     Made final changes to close the old guild. Players will be
 *     allowed to remain, but will not have any of their old powers.
 *     (Gorboth, March 2010)
 *
 */
#pragma save_binary

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";

#define SOULDESC(x) (this_player()->add_prop("_live_s_soulextra", (x)))

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <files.h>
#include <tasks.h>
#include <filter_funs.h>
#include <options.h>
#include "merc.h"
#include "include_specials.h"
#include "include_emotes.h"
#include "include_language.h"

#define MOREOBJ     "/obj/more"
#define I_GOT_A_DOG "_merc_lord_got_dog_once"
#define MY_DOG_IS   "_merc_lord_my_dog"
#define I_DCALLED_DOG "_i_dcalled_dog_reset"

public void
create()
{
    set_help_type(({ "mercenaries" }));
    read_help_dir(MHELP);
}

/*
 * Function name : get_soul_id
 * Description   : Give a name for this soul
 * Returns       : string - the soul's id
 */
string
get_soul_id()
{
    return "mercenaries";
}

/*
 * Function name : query_cmd_soul
 * Description   :   identify this as a valid cmdsoul
 * Returns       :       1
 */
int
query_cmd_soul()
{
    return 1;
}

/*
 * Function name : query_cmdlist
 * Description   : Get the commands available on this soul and
 *                 their corresponding function names.
 * Returns       : mapping - a mapping that maps command names
 *                 to function names.
 */
mapping
query_cmdlist()
{
    return ([ 
        "defend"   : "closed_status",
	"madvise"  : "madvise", "madv" : "madvise",
        "mappraise": "mappraise", "mapp" : "mappraise",
        "mattack"  : "closed_status", "matt" : "closed_status",
	"mbattle"  : "mbattle", "mbat" : "mbattle",
	"mcheck"   : "mcheck", "mche" : "mcheck",
        "mclean"   : "mclean", "mcle" : "mclean",
	"mcounsel" : "mcounsel", "mcou" : "mcounsel",
        "mdeclare" : "mdeclare", "mdec" : "mdeclare",
	"mdestiny" : "mdestiny", "mdes" : "mdestiny",
        "mfarewell": "mfarewell", "mfare" : "mfarewell", "mfar" : "mfarewell",
	"mface"    : "mface", "mfac" : "mface",
	"mglance"  : "mglance", "mglan" : "mglance",
	"mglare"   : "mglare", "mglar" : "mglare",
	"mhail"    : "mhail", "mhai" : "mhail",
        "minspect" : "minspect", "mins" : "minspect",
        "mkill"    : "closed_status",
     //   "mmercy"   : "mmercy", "mercy": "mmercy",
	"mnarrow"  : "mnarrow", "mnar" : "mnarrow", 
	"moffer"   : "moffer", "moff" : "moffer",
	"moptions" : "closed_status", "mopt" : "closed_status",
	"mresolve" : "mresolve", "mres" : "mresolve",
	"mrest"    : "mrest",
        "mrsay"    : "msay", 
	"msecure"  : "msecure", "msec" : "msecure",
	"mserious" : "mserious", "mser" : "mserious",
	"msettle"  : "msettle", "mset" : "msettle",
	"mspit"    : "mspit", "mspi" : "mspit",
	"mstray"   : "mstray", "mstr" : "mstray",
	"msuggest" : "msuggest", "msug" : "msuggest",
	"mswear"   : "mswear", "mswe" : "mswear",
	"mtalk"    : "mtalk", "mtal" : "mtalk",
	"mtitle"   : "closed_status", "mtit" : "closed_status", 
	"mtomorrow": "mtomorrow", "mtom" : "mtomorrow",
        "mwipe"    : "mwipe", "mwip": "mwipe",
	"mwork"    : "mwork", "mwor" : "mwork",
        "dgag"     : "closed_status", "dgagdog" : "closed_status",
        "dcall"    : "closed_status",
	"stop"     : "stop_def",
        "leave"    : "leave_mercs",
        ]) + help_cmdlist();
}


/*
 * Function name:        closed_status
 * Description  :        provide mercenaries with the information
 *                       that the guild is now closed, and that
 *                       they should probably leave it. This
 *                       is called when they try to use old guild
 *                       abilities.
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        int 1 - always
 */
public int
closed_status(string arg)
{
    write("Your old abilities have left you. You sense that the ways"
      + " of the Mercenaries have changed. Perhaps if you visit the"
      + " old Guild Camp, things will become clear. If you wish, you"
      + " may <leave> the guild now. It seems there is little point"
      + " in remaining a member with your abilities gone.\n");

    return 1;
} /* closed_status */


/*
 * Function name: leave_mercs()
 * Description  : Leave the guild
 * Arguments    : arg: string following verb
 * Returns      : 1 if they left, 0 if they didn't
 *
 * This old function from the former join room will now be added to
 * the command soul for guild members. This allows them to simply leave
 * at will. (Gorboth, March 2010)
 */
public int
leave_mercs(string arg)
{
    object who = this_player();
    int level = who->query_stat(SS_OCCUP) / 10;

    if (!strlen(arg))
    {
        notify_fail("Leave what? Your team? The mercenaries?\n");
        return 0; /* let the mudlib handle this */
    }

    if (!parse_command(arg, ({}),
        "[the] 'mercenaries' / 'mercenary' [guild]"))
    {
        notify_fail("Leave the mercenaries?\n");
        return 0;
    }

    else if (!IS_MERC(who))
    {
	write("You aren't even a member, so you can't leave!\n");
        return 1;
    }

    write("You are no longer a mercenary.\n");
    say(QCTNAME(who) + " is no longer a mercenary.\n");

    /* The shadow will catch the rest. */
    who->remove_occ_merc(who, "left");
    return 1;
} /* leave_mercs */


/*
 * Function: help()
 * Purpose : Provide help for the mercenary guild
 */
int help(string str)
{
    string subject, filename;
    int merc_status = MCREST->query_lord_status(TP->query_name());
    int i;

    notify_fail("No help available for that. Try 'mhelp feelings' or 'mhelp "+
	"abilities'.\n");
    if (!str)
	return 0;

    i = sscanf(str, "%s", subject);

    if (i ==0)
        return 0;

    filename = MHELP + subject;

    if (subject == "dogs" && merc_status < MERC_STATUS_ASPIRING)
	return 0;

    if (subject == "order" && merc_status < MERC_STATUS_LORD)
	return 0;

    if (file_size(filename) > 0)
    {
    setuid();
    seteuid(getuid());
    if (subject == "feelings" && !MCREST->query_crest_member(TP->query_name()))
        TP->more(read_file(filename), 0);
    else if (subject == "feelings")
        TP->more((read_file(filename) + read_file(MHELP + "feelings2")), 0);
    else
        cat(filename);

    /* Add priviledged abilities to the abilities help file */
    if (subject == "abilities")
    {
        if (merc_status >= MERC_STATUS_ASPIRING)
    	    write("dogs            mercenary lord hunting dogs\n");
	
        if (MCREST->query_members_lord(TP->query_name()))
	    write("morder          direct your troops in battle\n");

    }

    if (subject == "abilities")
        write("\n   More specific help is available by using 'mhelp <ability>'.\n");

    return 1;
    }

    return 0;
}

/*
 * Function name: dgagdog
 * Description  : gag your dogs arrivals
 * Argument:      str - the string given
 * Returns:       0 - failure, 1 -success
 */
int
dgagdog(string str)
{
    NF("You must dgagdog on/off/enabled/disabled.\n");
    if (!str)
	return 0;

    if (str == "on" || str == "enable" || str == "enabled")
    {
        write("You will no longer see your dog arrive behind you.\n");
	TP->set_skill(SS_MERC_GAG_DOG, 1);
        return 1;
    }

    if (str == "off" || str == "disable" || str == "disabled")
    {
        write("You will always see your dog arrive behind you.\n");
        TP->set_skill(SS_MERC_GAG_DOG, 0);
        return 1;
    }

    return 0;
}

/*
 * Function: dcall()
 * Purpose : Call a dog to this person
 */
int dcall(string str)
{
    object dog, me = TP;
    string name = TP->query_name();
    mapping mounts = ([ ]);

    NF("What?\n");
    if (MCREST->query_lord_status(TP->query_name()) < MERC_STATUS_ASPIRING &&
	!TP->query_wiz_level())
	return 0;

   NF("Call whom? Your dog?\n");
   if (!str)
	return 0;

    NF("Call whom? Your dog?\n");
    if (str != "dog")
        return 0;

/* Disable this because it's annoying for people who don't start in the merc guild
    NF("You haven't yet retrieved a dog to call.\n");
    if (!TP->query_prop(I_GOT_A_DOG))
	return 0; */

    if (TP->query_prop(MY_DOG_IS))
        dog = find_object(TP->query_prop(MY_DOG_IS));

    NF("Your dog is standing right beside you!\n");
    if (objectp(dog) && E(dog) == E(TP))
        return 0;

    setuid(); seteuid(getuid());
    MKENNEL->teleledningsanka();

    if (TP->query_prop(I_DCALLED_DOG) && 
       (TP->query_prop(I_DCALLED_DOG) + 13) > time())
    {
        write("You have only recently called your dog, and not given "+
	MKENNEL->query_dog_poss(me->query_name())+" time to come to "+
	"you yet.\n");
        return 1;
    }

    if (MKENNEL->query_dog_dead(TP->query_name()))
    {
    me->catch_tell("You call to your dog from across the miles, hoping that "+
	MKENNEL->query_dog_pronoun(me->query_name())+" can find "+
	MKENNEL->query_dog_poss(me->query_name())+
	" way back to you.\n");
    tell_room(E(me), QCTNAME(me)+" closes "+POSSESSIVE(me)+" eyes and "+
	"concentrates for a moment.\n", me);
    return 1;
    }

    if (objectp(dog))
    {
        set_alarm(10.0, 0.0, &(dog)->fly_to_owner());
    }
    else
    {
        setuid();
	seteuid(getuid());

        dog = clone_object(MNPC + "dog");
        dog->move(find_object(MROOM + "dogs_temp"));

        me->add_prop(MY_DOG_IS, file_name(dog));

        MKENNEL->set_up_dog(dog, me);

        set_alarm(10.0, 0.0, &(dog)->fly_to_owner());
        
        me->add_prop(I_DCALLED_DOG, time());
    }

    me->catch_tell("You call to your dog from across the miles, hoping that "+
	PRONOUN(dog)+" can find "+(dog->query_gender() == 1 ? "her" : "his")+
	" way back to you.\n");
    tell_room(E(me), QCTNAME(me)+" closes "+POSSESSIVE(me)+" eyes and "+
	"concentrates for a moment.\n", me);
    return 1;
}

/*
 * Function: stop_advance()
 * Purpose : Stop an advance of this person 
 */
void stop_advance(object me)
{
    object them;

    if (!(them = me->query_prop(MERC_O_ADVANCING)))
	return;

    if (E(me) == E(them))
    {
        me->catch_tell("You fall out of position, preventing any "+
	    "possible retreat from "+them->query_the_name(me)+".\n");
        them->catch_tell(me->query_The_name(them)+" falls out of position, "+
	    "preventing your retreat.\n");
    }

    me->remove_prop(MERC_O_ADVANCING);
}

/*
 * Function: stop_retreat()
 * Purpose : Stop a retreat of this person 
 */
void stop_retreat(object me)
{
    object them;

    if (!(them = me->query_prop(MERC_O_RETREATING)))
	return;

    if (E(me) == E(them))
    {
        me->catch_tell("You fall out of position, preventing any "+
	    "possible advance of "+them->query_the_name(me)+".\n");
        them->catch_tell(me->query_The_name(them)+" falls out of position, "+
	    "preventing your advance before "+OBJECTIVE(me)+".\n");
    }

    me->remove_prop(MERC_O_RETREATING);
}

/*
 * Function: query_attackers()
 * Purpose : Find out who all is attacking this person directly
 */
public int query_attackers(object me)
{ 
    object *en = me->query_enemy(-1);
    int i;

    if (!sizeof(en))
	return 0;

    for (i=0;i<sizeof(en);i++)
        if (en[i]->query_attack() == me)
	    return 1;

    return 0;
}

/*
 * Function: retreat()
 * Purpose : Order someone to retreat so this person can advance
 */
int retreat(string str)
{
    object *oblist, ob, ret_ob, me = TP;
    int duration;

    oblist = parse_this(str, "%l");

    NF("Order whom to retreat?\n");
    if (!sizeof(oblist))
        return 0;

    NF("You can only order one person to retreat at a time.\n");
    if (sizeof(oblist) > 1)
        return 0;

    if (me->query_prop(MERC_O_ADVANCING))
    {
        ob = me->query_prop(MERC_O_ADVANCING);
        write("You have already advanced to allow for "+
	    ob->query_the_name(me)+"'s retreat, you cannot "+
	    "facilitate the retreat of two people at once.\n");
        return 1;
    }

    if (me->query_prop(MERC_O_RETREATING))
    {
	ob = me->query_prop(MERC_O_RETREATING);
        write("You have already fallen back to allow "+
	    ob->query_the_name(me)+" to advance, you cannot "+
	    "simultaneously advance and retreat.\n");
	return 1;
    }

    ob = oblist[0];

    if (ob->query_leader() != me &&
        me->query_leader() != ob &&
	member_array(ob, me->query_leader()->query_team()) < 0)
    {
        write("You cannot assist "+ob->query_the_name(me)+" in a "+
	    "retreat, because "+PRONOUN(ob)+" is not in your team.\n");
	return 1;
    }

    if (!query_attackers(ob))
    {
        write(ob->query_The_name(me)+" is not under attack.\n");
        return 1;
    }

    setuid(); seteuid(getuid());

    duration = me->query_skill(SS_MERC_TACTICS) / 5;

    ret_ob = clone_object(MOBJ+"retreat_object");
    ret_ob->set_duration(duration);
    ret_ob->set_advancer(me);
    ret_ob->set_advance_room(E(me));
    ret_ob->move(ob, 1);

    me->add_prop(MERC_O_ADVANCING, ob);
    set_alarm(itof(duration), 0.0, &stop_advance(me));

    write("You step toward " +ob->query_the_name(TP)+ ", shouting "+
	"for "+OBJECTIVE(ob)+" to retreat.\n");
    ob->catch_tell(TP->query_The_name(ob)+" steps toward you, "+
	"shouting for you to retreat.\n");
    say(QCTNAME(TP)+" steps toward "+QTNAME(ob)+", shouting for "+
	OBJECTIVE(ob)+" to retreat.\n", ({ TP, ob }));

    if (ob->query_skill(SS_MERC_AUTOCOMPLY))
        ob->command("$retreat "+OB_NAME(me));

    return 1;
}

/*
 * Function: advance()
 * Purpose : Order someone to advance so this person can retreat
 */
int advance(string str)
{
    object *oblist, ob, adv_ob, me = TP;
    int duration;

    oblist = parse_this(str, "%l");

    NF("Order whom to advance?\n");
    if (!sizeof(oblist))
        return 0;

    NF("You can only order one person to advance at a time.\n");
    if (sizeof(oblist) > 1)
        return 0;

    if (me->query_prop(MERC_O_ADVANCING))
    {
        ob = me->query_prop(MERC_O_ADVANCING);
        write("You have already advanced to allow for "+
	    ob->query_the_name(me)+"'s retreat, you cannot "+
	    "simultaneously advance and retreat.\n");
        return 1;
    }

    if (me->query_prop(MERC_O_RETREATING))
    {
	ob = me->query_prop(MERC_O_RETREATING);
        write("You have already fallen back to allow "+
	    ob->query_the_name(me)+" to advance, you cannot "+
	    "have two people advancing at once.\n");
	return 1;
    }

    ob = oblist[0];

    if (ob->query_leader() != me &&
        me->query_leader() != ob &&
	member_array(ob, me->query_leader()->query_team()) < 0)
    {
        write("You cannot retreat behind "+ob->query_the_name(me)+
	    ", because "+PRONOUN(ob)+" is not in your team.\n");
	return 1;
    }

    if (!query_attackers(me))
    {
        write("You are not under attack.\n");
        return 1;
    }

    setuid(); seteuid(getuid());

    duration = me->query_skill(SS_MERC_TACTICS) / 5;

    adv_ob = clone_object(MOBJ+"advance_object");
    adv_ob->set_duration(duration);
    adv_ob->set_retreater(me);
    adv_ob->set_retreat_room(E(me));
    adv_ob->move(ob, 1);

    me->add_prop(MERC_O_RETREATING, ob);
    set_alarm(itof(duration), 0.0, &stop_retreat(me));

    write("You fall back in " +ob->query_the_name(TP)+ "'s direction, "+
	"shouting for "+OBJECTIVE(ob)+" to advance.\n");
    ob->catch_tell(TP->query_The_name(ob)+" falls back in your direction, "+
	"shouting for you to advance.\n");
    say(QCTNAME(TP)+" falls back in "+QTNAME(ob)+"'s direction, shouting for "+
	OBJECTIVE(ob)+" to advance.\n", ({ TP, ob }));

    if (ob->query_skill(SS_MERC_AUTOCOMPLY))
        ob->command("$advance "+OB_NAME(me));

    return 1;
}

/*
 * Function: get_all_teammates()
 * Purpose : Get all of this person's teammates
 */
public object *get_all_teammates(object ob)
{
    int i;
    object *team = ({ }), *new_team = ({ });

    if (ob->query_leader())
    {
        team = ob->query_leader()->query_team();
	     team += ({ ob->query_leader() });

    }
    else if (sizeof(ob->query_team()))
    {
        team = ob->query_team();
    }

    if (!sizeof(team))
        return 0;

    for (i=0;i<sizeof(team);i++)
    {
        if (E(team[i]) == E(ob))
            new_team += ({ team[i] });
    }

    return new_team;
}

/*
 * Function: get_merc_teammates()
 * Purpose : Get all the mercenaries on this person's team
 */
public object *get_merc_teammates(object ob)
{
    object *team = ({ }), *mercs = ({ });
    int i;

    team = get_all_teammates(ob);

    if (!sizeof(team))
	return 0;

    for (i=0;i<sizeof(team);i++)
    {
	if (IS_MERC(team[i]) && 
	    MCREST->query_members_lord(team[i]->query_name()) == 
	    ob->query_name())
	{
	    mercs += ({ team[i] });
	}
       else if (IS_MERC_SUBLORD(ob))
	{
	    if (MCREST->query_members_lord(team[i]->query_name()) ==
		MCREST->query_members_lord(ob->query_name()))
		mercs += ({ team[i] });
        }
    }

    if (!sizeof(mercs))
        return 0;

    return mercs;
}

/* Function: order_assist()
 * Purpose : Order the team to assist this person
 */
int order_assist(string str)
{
    object *mercs = get_merc_teammates(TP);
    
    int i;

    NF("You can only order your team to assist.\n");
    if (str != "team")
	return 0;

    NF("You are not currently attacking anyone.\n");
    if (!TP->query_attack())
        return 0;

    NF("You are not a member of a team.\n");
    if (!sizeof(get_all_teammates(TP)))
	return 0;

    write("You shout an order for your teammates to assist you against "+
	TP->query_attack()->query_the_name(TP)+".\n");
    say(QCTNAME(TP)+" shouts an order for "+POSSESSIVE(TP)+" teammates "+
        "to assist "+OBJECTIVE(TP)+" against "+
        QTNAME(TP->query_attack())+".\n");

    for (i=0; i<sizeof(mercs); i++)
    {
        if (mercs[i]->query_skill(SS_MERC_AUTOCOMPLY))
        {
            mercs[i]->add_prop(LIVE_O_LAST_KILL, TP->query_attack());
            mercs[i]->command("$assist "+lower_case(TP->query_name()));

            if (!mercs[i]->query_prop(PLAYER_I_MATTACK_RESETTING) &&
		!mercs[i]->query_prop(PLAYER_I_MATTACK_PREPARING))
		mercs[i]->command("$mattack");

        }
    }

    return 1;
}

/*
 * Function: order_attack()
 * Purpose : Order the team to attack someone
 */
int order_attack(string str)
{
    object *oblist = ({ }), *mercs = get_merc_teammates(TP);
    int i;

    oblist = parse_this(str, "[defend] [the] %l");

    NF("You are not a member of a team.\n");
    if (!sizeof(get_all_teammates(TP)))
	return 0;

    NF("Order your teammates to attack whom?\n");
    if (!sizeof(oblist))
        return 0;

    if (sizeof(oblist) > 1)
        return 0;

    if (member_array(oblist[0], get_all_teammates(TP)) != -1)
    {
        write(oblist[0]->query_The_name(TP)+" is a member of your "+
	    "team!!\n");
        return 1;
    }

    write("You shout an order for your teammates to attack "+
	oblist[0]->query_the_name(TP)+".\n");
    say(QCTNAME(TP)+" shouts an order for "+POSSESSIVE(TP)+" teammates "+
	"to attack "+QTNAME(oblist[0])+".\n");

    TP->command("$kill "+ OB_NAME(oblist[0]));

    if (TP->query_prop(PLAYER_I_MATTACK_RESETTING) &&
        TP->query_prop(PLAYER_I_MATTACK_PREPARING))
	TP->command("$mattack");

    for (i=0; i<sizeof(mercs); i++)
    {
        if (mercs[i]->query_skill(SS_MERC_AUTOCOMPLY))
        {
            mercs[i]->add_prop(LIVE_O_LAST_KILL, oblist[0]);
            mercs[i]->command("$kill "+ OB_NAME(oblist[0]));

            if (!mercs[i]->query_prop(PLAYER_I_MATTACK_RESETTING) &&
		!mercs[i]->query_prop(PLAYER_I_MATTACK_PREPARING))
		mercs[i]->command("$mattack");

        }
    }

    return 1;
}


/*
 * Function: order_defend()
 * Purpose : Order the team to defend a member of the team
 */
int order_defend(string str)
{
    object *oblist = ({ }), *mercs = get_merc_teammates(TP);
    int i;

    if (str == "me" || str == (TP->query_name()) ||
	str == (lower_case(TP->query_name())))
        oblist += ({ TP, });
    else
        oblist = parse_this(str, "[defend] [the] %l", 0, 1);

    NF("You are not a member of a team.\n");
    if (!sizeof(get_all_teammates(TP)))
	return 0;

    NF("Order your teammates to defend whom?\n");
    if (!sizeof(oblist))
        return 0;

    if (sizeof(oblist) > 1)
        return 0;

    if (!oblist[0]->query_attack())
    {
        write(oblist[0]->query_The_name(TP)+" is not currently fighting anyone.\n");
	return 1;
    }

    if (sizeof(oblist[0]->query_defenders()) > 1)
    {
        write(oblist[0]->query_The_name(TP)+" is already well defended.\n");
        return 1;
    }

    write("You shout an order for your teammates to defend "+
	oblist[0]->query_the_name(TP)+".\n");
    say(QCTNAME(TP)+" shouts an order for "+POSSESSIVE(TP)+" teammates to "+
	"defend "+QTNAME(oblist[0])+".\n");

    for (i=0; i<sizeof(mercs); i++)
    {
        if (mercs[i]->query_skill(SS_MERC_AUTOCOMPLY) &&
        !mercs[i]->query_defending() && mercs[i] != oblist[0])
            mercs[i]->command("$defend "+OB_NAME(oblist[0]));

        if (mercs[i] == oblist[0] && mercs[i]->query_defending())
            mercs[i]->command("$stop defending");
    }
        
    if (sizeof(oblist[0]->query_defenders()) < 2 &&
	!TP->query_defending() && oblist[0] != TP)
        TP->command("$defend "+OB_NAME(oblist[0]));
    return 1;
}

/*
 * Function: order()
 * Purpose : This is the main order function, which calls other 
 *	     functions to carry out the actual orders of the lord.
 */
public int order(string str)
{
    int stat;
    string one, two;

    stat = MCREST->query_lord_status(TP->query_name());

    if (TP->query_wiz_level())
	stat = MERC_STATUS_WARLORD;

    switch(stat)
    {
        case MERC_STATUS_NONE:
            notify_fail("As a mercenary, you may use: morder "+
	        "autocomply on/off\n");
	    break;
	case MERC_STATUS_ASPIRING:
	    notify_fail("As an aspiring lord you may use the following "+
		"orders in battle:\n"+
		"  'morder assist'\n"+
		"  'morder attack target'\n"+
		"  'morder defend target'\n");
	    break;
	case MERC_STATUS_LORD:
            if (IS_MERC_SUBLORD(TP))
            {
	    notify_fail("As a mercenary lord you may use the following "+
		"orders in battle:\n"+
		"  'morder autocomply on/off'\n"+
		"  'morder assist'\n"+
		"  'morder attack <target>'\n"+
		"  'morder defend <target>'\n"+
		"  'morder <target> advance'\n"+
		"  'morder <target> retreat'\n");
	    }
	    else
	    {
	    notify_fail("As a mercenary lord you may use the following "+
		"orders in battle:\n"+
		"  'morder assist'\n"+
		"  'morder attack <target>'\n"+
		"  'morder defend <target>'\n"+
		"  'morder <target> advance'\n"+
		"  'morder <target> retreat'\n");
	    }
	    break;
	case MERC_STATUS_WARLORD:
	    notify_fail("As a mercenary lord you may use the following "+
		"orders in battle:\n"+
		"  'morder team assist'\n"+
		"  'morder attack <target>'\n"+
		"  'morder defend <target>'\n"+
		"  'morder <target> advance'\n"+
		"  'morder <target> retreat'\n");
	    break;
    }

    if (!str)
	return 0;

    NF("Use the syntax: 'morder <target> <order>' / 'morder <order> <target>', "+
	"or just 'morder' to see your available orders.\n");
    if (!parse_command(str, ({ }), "%w %w", one, two))
        return 0;

    if (!TP->query_wiz_level())
    if (stat < MERC_STATUS_ASPIRING || (one == "autocomply" && IS_MERC_SUBLORD(TP)))
    {
        notify_fail("As a mercenary, you may use: morder autocomply on/off\n");
        if (one != "autocomply")
	    return 0;

         if (two == "on")
	     TP->set_skill(SS_MERC_AUTOCOMPLY, 1);
         else if (two == "off")
	     TP->set_skill(SS_MERC_AUTOCOMPLY, 0);
         else
             return 0;

         write("Autocompliance with orders set to "+two+".\n");
             return 1;
    }

    if (two == "retreat" && stat >= MERC_STATUS_LORD)
        return retreat(one);
    else if (two == "advance" && stat >= MERC_STATUS_LORD)
	return advance(one);
    else if (two == "assist" && stat >= MERC_STATUS_ASPIRING)
        return order_assist(one);
    else if (one == "defend" && stat >= MERC_STATUS_ASPIRING)
        return order_defend(two);
    else if (one == "attack" && stat >= MERC_STATUS_ASPIRING)
	return order_attack(two);
    else
	return 0;
}
