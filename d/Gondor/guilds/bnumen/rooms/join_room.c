/*
 *	Master file for Black Numenoreans guild
 *
 *	Copyright (c) 1994, 1997 by Christian Markus
 *
 *	Snarfed from Olorin, Coded in 1994.
 *
 *  Conversion by Palmer, Aug 2006
 *
 *  Modification log:
 *
 *      2006-08-25, Toby
 *           Changed from tables to plaque and modified
 *           long description to fit the ship. Also 
 *           removed the BSN since it is obsolete.
 */

#pragma strict_types

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

#define BNUMEN_TREE	         (GUILD_DIR + "bnumen")
#define BNUMEN_S_APPLIED_TO	 "_bnumen_s_applied_to"
#define BNUMEN_M_OATH        "_bnumen_m_oath"
#define BNUMEN_I_LINE        "_bnumen_i_line"
#define BNUMEN_S_VOUCHED_FOR "_bnumen_s_vouched_for"
#define BNUMEN_S_RELEASED_BY "_bnumen_s_released_by"
/* 2 months idle time */
#define LORD_IDLE_TIME		    4838400

#define DT_S_LNAME	0
#define DT_I_LGENDER	1
#define DT_AS_MEMBERS	2

/*
 * if the Lord/Lady does not login for more than 2 weeks,
 * someone else can replace him/her
 */
#define DT_LORD_TIME_LIMIT	1209600

/*
 *	Prototypes:
 */
public int query_open_house(string house);
public varargs int query_number_bnumen(string house, int silent = 1);
public varargs mixed oath_newbie(string house, string title, string name, int line);
public varargs mixed query_house_lord(string house);
public string exa_plaques();
public varargs string query_bnumen_house(string name);
public string query_is_lord(string lname);
public varargs int add_unhoused_bnumen(string name, string house, string lordname = 0);
public varargs int add_bnumen(string name, string house, string lordname = 0);
private int do_join(string house, object tp, object newbie);
public int remove_from_tree(string name, string house, int nohouse = 1);
public int remove_bnumen_from_house(object pl, string house, string reason);
private void set_up_houses();
public void add_to_tree(string name, string house);
private void continue_repeat(mixed arr, int i, object tp);
public mixed purge_house(mixed house);
public int check_idle_lord(string name);
public void purge_bnumen_houses();

/*
 *	Global variables:
 */

/*
 *	Houses: <name of the House> : ({ <name of the Lord/Lady>,
 *                                   <gender of the Lord/Lady>,
 *                                   ({ <name of the members>, ... }) })
 *	all entries start with capital letters!
 */
private mapping Houses = ([ ]);

/*
 * No_House: ({ <name of members w/o house>, ... })
 * This is not used yet.
 */
private string *No_House = ({ });

static string *Oath;

/*
 * Function name: create_gondor
 * Description:   Gondor room creator.
 */
public void
create_cabin()
{
    int     ih;

    set_short("the Cabin of the Houses");
    set_long("The Cabin of the Houses in the barque of the Black Numenoreans in "
      + "Harondor. In this particular Cabin ceremonies important to the Families of "
      + "the Black Numenoreans are performed. Here betrothals are announced, dead "
      + "lie in state, and the young are formally introduced into their "
      + "rights and duties as grown-ups when they have come of age. "
      + "In this rather large cabin, the heads of the Houses of the Black "
      + "Numenoreans can also adopt new members into their families. On the walls "
      + "there are large plaques listing the members of the Houses of the "
      + "Black Numenoreans. To the starboard side of the room is a locked " 
      + "door.\n");

    add_exit(BNUMEN_DIR + "ship/ndeck3", "fore");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"plaque", "plaques", "houses", "house", "bnumen", }),
        exa_plaques);
    add_item("pedestal", 
        "The pedestal is standing in the front end of the room. On it lies a large book.");
    add_item(({"door", "locked door", }),
        "The door has a sign that reads 'Captain.'\n");

    seteuid(getuid());
    restore_object(BNUMEN_TREE);

    if (!m_sizeof(Houses))
        set_up_houses();

    clone_object(BNUMEN_DIR + "obj/guild_book")->move(TO);

    floor();
    walls();
    ceiling();

    add_prop(ROOM_I_NO_CLEANUP, 1);
    set_alarm(3666.0, 0.0, &purge_bnumen_houses());
}

/*
 * Function name: set_up_houses
 * Description:   create the mapping Houses
 */
private void
set_up_houses()
{
    int     i,
            sh = sizeof(BNUMEN_HOUSES);

    for (i = 0; i < sh; i++)
    {
        Houses[BNUMEN_HOUSES[i]] = ({ 0, -1, ({}) });
    }

    save_object(BNUMEN_TREE);
}

/*
 * Function name: purge_house
 * Description:   help function to purge_bnumen_houses
 */
public mixed
purge_house(mixed house)
{
    string *members = house[DT_AS_MEMBERS];

    // Purge the lord of the house
    if (!SECURITY->exist_player(lower_case(house[DT_S_LNAME])))
    {
	house[DT_S_LNAME] = 0;
	house[DT_I_LGENDER] = -1;
    }

    if (check_idle_lord(lower_case(house[DT_S_LNAME])))
    {
        members += ({ house[DT_S_LNAME] });
 
        write_file(BNUMEN_LOG, "LORDS: " + capitalize(house[DT_S_LNAME]) +
            "was removed as Lord because of idleness on " + ctime(time()) + 
            ".\n");
        house[DT_S_LNAME]    =  0;
        house[DT_I_LGENDER]  = -1;
    }

    // Purge the members of the house the don't exist
    members = filter(members,  
		     &call_other("/secure/master", "exist_player", ) @
		     &lower_case());
    house[DT_AS_MEMBERS] = members;
    return house;
}

/*
 * Function name: purge_bnumen_houses
 * Description:   purges non existing players from the
 *		  Houses mapping.
 */
public void
purge_bnumen_houses()
{
    map(Houses, &purge_house());
    save_object(BNUMEN_TREE);
    return;
}

/*
 * Function name: exa_plaques
 * Description:	  examine/read the plaques
 * Returns:       the description
 */
public string
exa_plaques()
{
    string  desc;

    desc = "There are " + LANG_WNUM(sizeof(BNUMEN_HOUSES)) + " plaques, "
         + "each listing the members of one of the Houses of the "
         + "Black Numenoreans. The names of the Houses are: "
         + COMPOSITE_WORDS(BNUMEN_HOUSES)
         + ".\n";

    return desc;
}

/*
 * Function name: do_examine
 * Description:   let the player examine all tables with the
 *                names of the bnumen
 * Argument:      str - command line argument
 * Returns:       1/0 - success/failure
 */
public int
do_examine(string str)
{
    mixed   hlist;
    string  desc,
           *dummy,
            house,
            foo,
            vb = query_verb();

    if (!strlen(str))
        return 0;

    str = LOW(str);

    if (vb == "l" || vb == "look")
    {
        dummy = explode(str, " ");
        if (dummy[0] != "at")
            NFN0("Look needs a preposition with an object.");
        str = implode(dummy[1..sizeof(dummy)-1], " ");
    }

    if (!parse_command(str, ({ }),
        "[the] 'house' / 'plaque' [of] [the] [house] [of] %w", house))
        return 0;

    house = CAP(house);

    if (member_array(house, BNUMEN_HOUSES) < 0)
        NFN0("There is no House of the Black Numenorean called " + house + "!");

    hlist = Houses[house];

    desc = "You look at the plaque listing the Members of the House of "
         + house + "." + "\n";
    if (!stringp(hlist[DT_S_LNAME]))
        desc += "\tThere is no Lord and no Lady of the House of " + house + ".\n";
    else
    {
        desc += ("\t"+hlist[DT_S_LNAME]+" is the "
             +  (hlist[DT_I_LGENDER] ? "Lady" : "Lord") 
             +  " of the House of " + house + ".\n");
    }
    if (sizeof(hlist[DT_AS_MEMBERS]))
    {
        switch(hlist[DT_I_LGENDER])
        {
	case -1: foo = "the"; break;
	case  0: foo = "his"; break;
	case  1: foo = "her"; break;
	case  2: foo = "its"; break;
        }
        desc += "\n\tThe members of "+foo
             + " House are:\n\n"
             + break_string(COMPOSITE_WORDS(hlist[DT_AS_MEMBERS]), 40, "\t")
             + ".\n";
    }
    else if (stringp(hlist[DT_S_LNAME]))
        desc += "\n\tThe House has no further members.\n";

    desc += "\n";

    write(desc);

    return 1;
}

/*
 * Function name: tell_bnumen
 * Description:   send a message to all bnumen
 * Arguments:     msg  - the message to be sent
 *                name - either a string or an array containing the
 *                       name or names of bnumen that should not
 *                       receive the message.
 */
public varargs object *
tell_bnumen(string msg, mixed name)
{
    int     i;
    object *bnums,
            soul = find_object(BNUMEN_SOUL);

    FIX_EUID;
    bnums = filter(users() - ({ 0 }), soul->query_is_bnumen);
    if (stringp(name))
	name = ({ find_player(LOW(name)) });
    if (pointerp(name) && (sizeof(name) >= 1))
    {
	if (stringp(name[0]))
	    name = map(name, find_player @ lower_case);
	else if (!objectp(name[0]))
	    name = ({ });
    }
    name -= ({ 0 });
    bnums  -=  name;

    bnums->catch_tell(msg + "\n");

    return bnums;
}

/*
 * Function name: do_enter
 * Description:	  enter the guild, only possible if there is no
 *                Lord or Lady of the House
 * Arguments:     str - Argument of 'enter', the name of the House.
 * Returns:       1 if sucess
 */
public int
do_enter(string str)
{
    int     result;
    object  tp = TP,
            member;
    string  gname = "",
            house,
            lordname,
            name = tp->query_real_name(),
            voucher;

    NFN("Enter what?");
    if (!strlen(str))
        return 0;

    if (tp->query_race() != BNUMEN_RACE)
        NFN0("Only humans can belong to the Houses of the Black Numenoreans!");

    if ((gname = tp->query_guild_name_race()) == GUILD_NAME)
    {
        house = tp->query_bnumen_house();
        if (strlen(house) && member_array(house, BNUMEN_HOUSES) > -1)
        {
            if (!strlen(lordname = tp->query_prop(BNUMEN_S_RELEASED_BY)) ||
                (lordname != query_house_lord(house)))
                NFN0("You are already a member of the House of "+house+"!");
        }
    }
    else if (strlen(gname) && gname != GUILD_NAME)
        NFN0("You are already a member of the "+CAP(gname)+"!");

    str = LOW(str);

    // Which House do we want to join?
    if (!parse_command(str, ({ }),
        "[the] [house] [of] %w", house))
    {
        NFN("Enter which House of the Black Numenoreans?");
	return 0;
    }

    // Does it exist?
    house = CAP(house);
    if (member_array(house, BNUMEN_HOUSES) < 0)
    {
        NFN("There is no House of the Black Numenoreans called "+house+"!");
	return 0;
    }

    /*
     * Does it already have a Lord or a Lady?
     * If yes, then we can enter only by adoption:
     */
    if (strlen(lordname = query_house_lord(house)))
    {
	NF("You can only enter a House if there is no Lord or Lady of the House!\n"
	   + "To become a member of the House of "+house
	   + ", you will have to apply to "+CAP(lordname)+".\n");
        return 0;
    }

    /*
     * check if the House has already other members,
     * and if not, if it may be opened
     */
    if (!(query_open_house(house)))
    {
        NFN("The House of "+house+" has no members yet, and it is "
          + "presently not possible to open a new House of the Black Numenoreans.");
        return 0;
    }

    /*
     * if the House already has some members, we need someone to
     * vouch for us:
     */
    if (sizeof(Houses[house][DT_AS_MEMBERS]))
    {
	NFN("A member of the House of " + house + 
	    " or a Lord or a Lady of the Houses has to vouch for you!");
        if (!(strlen(voucher = tp->query_prop(BNUMEN_S_VOUCHED_FOR))))
            return 0;

        if (!(objectp(member = find_player(LOW(voucher)))) ||
            !objectp(present(member, TO)) ||
            ((member_array(voucher, Houses[house][DT_AS_MEMBERS]) < 0)
	     && (member->query_bnumen_level() < DL_LORD)))
            return 0;
    }

    if (gname == GUILD_NAME)
    {
        if (result = add_unhoused_bnumen(name, house))
        {
            say(QCTNAME(tp) + " enters the House of " + house + "!\n",
                ({tp}));
            return 1;
        }
        else
        {
            notify_fail("Something unexpected happened! Please make " +
                "a bug report!\n");
            return 0;
        }
    }

    if (result = add_bnumen(name, house))
    {
        say(QCTNAME(tp)+" enters the House of "+house+"!\n", ({tp}));
        return 1;
    }
    NFN("Something unexpected happened! Please make a bug report!");
    return 0;
}

/*
 * Function name: do_vouch
 * Description:   vouch for someone who wants to join your house
 * Arguments:     str - the name of the new member
 * Returns:       1 if sucess
 */
public int
do_vouch(string str)
{
    object  tp = TP,
            newbie;
    string  tp_name = tp->query_name(),
            name;

    if (tp->query_guild_name_race() != GUILD_NAME)
        return 0;

    NFN("Vouch for whom?");
    if (!strlen(str))
        return 0;

    str = LOW(str);

    if (sscanf(str, "for %s", name) != 1)
        return 0;

    if (!(objectp(newbie = find_player(name))) || !present(newbie, TO))
    {
        NFN(CAP(name)+" is not here!");
        return 0;
    }

    if (!tp->query_met(name))
    {
        NFN("You do not know any "+CAP(name)+".");
        return 0;
    }

    if (newbie->query_guild_name_race() == GUILD_NAME &&
      strlen(newbie->query_bnumen_house()))
    {
        NFN(CAP(name)+" is already a member of the Houses of the Black Numenoreans!");
        return 0;
    }

    if (newbie->query_race() != BNUMEN_RACE)
    {
        NFN("Only humans may join the Houses of the Black Numenoreans!");
        return 0;
    }

    newbie->add_prop(BNUMEN_S_VOUCHED_FOR, tp_name);
    write("You vouch for "+CAP(name)+".\n");
    say(QCTNAME(tp)+" vouches for "+QTNAME(newbie)+".\n", ({ tp, newbie }));
    newbie->catch_msg(QCTNAME(tp)+" vouches for you.\n");
    return 1;
}

/*
 * Function name: do_release
 * Description:   Lords and Ladies can "release" a member
 *                of their Houses from their service, so 
 *                he or she can join another house.
 * Arguments:     str - the name of the new member
 * Returns:       1 if sucess
 */
public int
do_release(string name)
{
    object  tp = TP,
            newbie;
    string  tp_name = tp->query_name();

    if (tp->query_guild_name_race() != GUILD_NAME)
        return 0;

    if ((tp->query_bnumen_level() < DL_LORD) && !tp->query_wiz_level())
    {
        NFN("Only the Lord or the Lady of a House of the Black Numenoreans "
          + "can release a member of the Houses!");
	return 0;
    }

    NFN("Release whom?");
    if (!strlen(name))
        return 0;

    name = LOW(name);

    if (!(objectp(newbie = find_player(name))) || !present(newbie, TO))
    {
        NFN(CAP(name)+" is not here!");
        return 0;
    }

    if (!tp->query_met(name))
    {
        NFN("You do not know any "+CAP(name)+".");
        return 0;
    }

    if (newbie->query_guild_name_race() != GUILD_NAME)
    {
        NFN(CAP(name)+" is not a member of the Houses of the Black Numenoreans!");
        return 0;
    }

    if (newbie->query_bnumen_house() != tp->query_bnumen_house())
    {
        NFN(CAP(name)+" is not a member of your House!");
        return 0;
    }

    remove_bnumen_from_house(newbie, newbie->query_bnumen_house(), "released by "+CAP(tp->query_name())+" from");
    write("You release "+CAP(name)+" from your House.\n");
    say(QCTNAME(tp)+" releases "+QTNAME(newbie)+" from " + 
	tp->query_possessive() + " House.\n", ({ tp, newbie }));
    newbie->catch_msg(QCTNAME(tp)+" releases you from " + 
		      tp->query_possessive() + " House.\n" +
		      "You are now free to ask another Lord or Lady " +
		      "of the Houses of the Black Numenoreans to adopt you.\n");
    return 1;
}

/*
 * Function name: do_apply(string str)
 * Description:   apply to Lord/Lady of the House to join
 * Arguments:     str: [for] membership [in] [the] [house] [of] <house name>
 * Returns:       1 if sucess
 */
public int
do_apply(string str)
{
    object  lord,
            tp = TP;
    string  gname,
            lordname,
            house;

    NFN("Apply for what?");
    if (!strlen(str))
        return 0;

    if (tp->query_race() != BNUMEN_RACE)
    {
        NFN("Only humans can belong to the Houses of the Black Numenoreans!");
	return 0;
    }

    if ((gname = tp->query_guild_name_race()) == GUILD_NAME)
    {
	/*
	 * Members of another House require a release if their 
	 * House has a Lord or a Lady:
	 */
        if (strlen(house = tp->query_bnumen_house()) && 
	    (member_array(house, BNUMEN_HOUSES) > -1))
	{
	    if ((strlen(lordname = query_house_lord(house))) &&
	        (lordname != tp->query_prop(BNUMEN_S_RELEASED_BY)))
	    {
	        NFN("You have not been released by the " +
		    (Houses[house][DT_I_LGENDER] ? "Lady" : "Lord") +
		    " of your House!");
		return 0;
	    }
	}
    }
    else if (strlen(gname) && gname != GUILD_NAME)
    {
        NFN("You are already a member of the "+CAP(gname)+"!");
	return 0;
    }

    str = LOW(str);

    /*
     * Ok, the player has passed all checks:
     * Now lets see which House he/she wants to join:
     */
    if (!parse_command(str, ({ }),
        "[for] 'membership' [in] [the] [house] [of] %w", house))
    {
        NFN("Apply for membership in which House of the Black Numenoreans?");
	return 0;
    }

    house = CAP(house);
    if (member_array(house, BNUMEN_HOUSES) < 0)
    {
        NFN("There is no House of the Black Numenoreans called "+house+"!");
	return 0;
    }

    /*
     * The Lord or the Lady of the new House has to be here,
     * and Lord/Lady and applicant must have met:
     */
    if (!strlen(lordname = query_house_lord(house)) ||
	!objectp(lord = find_player(LOW(lordname))) ||
        !objectp(present(lord, TO)))
    {
	NFN("You can only apply if the Lord or the Lady of the House is present!");
	return 0;
    }
    if (!(lord->query_met(tp->query_real_name())))
    {
        NFN("Introduce yourself first!");
	return 0;
    }
    if (!(tp->query_met(LOW(lordname))))
    {
        NFN("You have not been introduced to "+CAP(lordname)+".");
	return 0;
    }

    /*
     * Now we are in business:
     * Tell the Lord/Lady that the player has applied,
     * and set the property:
     */
    write("You apply to "+CAP(lordname)
      + " for membership in the House of "+CAP(house)+"!\n");
    say(QCTNAME(tp)+" applies for membership in the House of "+CAP(house)+".\n",
        ({tp, lord}));
    lord->catch_msg(QCTNAME(tp)+" applies to you for membership in the House of "+house+"!\n");
    tp->add_prop(BNUMEN_S_APPLIED_TO, house);

    return 1;
}

/*
 * Function name: do_adopt
 * Description:   the Lord/Lady of a House adopts an applicant
 *                into the House
 * Argument:      str - the name of the applicant
 * Returns:       1/0 - success/failure
 */
public int
do_adopt(string str)
{
    int     result;
    object  newbie,
            tp = TP;
    string  house = tp->query_bnumen_house(),
            title;

    if (!strlen(house) || (member_array(house, BNUMEN_HOUSES) < 0))
    {
	NFN("You are not a member of a House of the Black Numenoreans!");
        return 0;
    }

    if ((tp->query_bnumen_level() < DL_LORD) && !tp->query_wiz_level())
    {
        NFN("Only the Lord or the Lady of a House of the Black Numenoreans "
          + "can adopt new members!");
	return 0;
    }

    if (!strlen(str))
    {
        NFN("Whom do you want to adopt?");
	return 0;
    }

    // the applicant must be present:
    str = LOW(str);
    if (!objectp(newbie = find_player(str)) || 
	!objectp(present(newbie, TO)))
    {
	NFN("Where is "+CAP(str)+"?");
        return 0;
    }

    if (newbie->query_prop(BNUMEN_S_APPLIED_TO) != house)
    {
        NFN(CAP(str) + " has not applied for membership in the House of "+house+".");
	return 0;
    }

    tp->command("$say I accept your service and I receive you into my house!");
    tp->command("$say Swear to me now! Repeat after me if you are resolved!");
    title = (tp->query_gender() ? "Lady":"Lord");

    // set up the text of the Oath:
    oath_newbie(house, title, str, -1);
    tp->command("$say " + oath_newbie(house, title, str, 0));
    newbie->add_prop(BNUMEN_M_OATH, ({ tp, house, title, str, }) );
    newbie->add_prop(BNUMEN_I_LINE, 1);

    return 1;
}

/*
 * Function name: do_repeat
 * Description:   the applicant repeats the oath of fealty
 * Arguments:     str - command verb argument
 * Returns:       1/0 - success/failure
 */
public int
do_repeat(string str)
{
    object  tp  = TP;
    int     i   = tp->query_prop(BNUMEN_I_LINE);
    mixed   arr = TP->query_prop(BNUMEN_M_OATH);
    string  lname,
            line,
            vb  = query_verb();

    if (!(sizeof(arr)))
        return 0;

    if (vb == "'")
    {
        vb = "say";
    }

    if (!strlen(str))
    {
        if (vb == "repeat")
        {
            NFN("Repeat what?");
	    return 0;
        }
        else
	{
            return 0;
	}
    }

    lname = arr[0]->query_name();

    str  = LOW(str);
    line = oath_newbie(arr[1], arr[2], arr[3], i-1);

    if ((str != ("after "+LOW(lname))) && (str != LOW(line)))
    {
        NFN("Repeat what?");
	return 0;
    }

    write("You say: "+line+"\n");
    say(QCTNAME(TP)+" says: "+line+"\n");

    if (!oath_newbie(arr[1], arr[2], arr[3], i))
    {
        tp->remove_prop(BNUMEN_I_LINE);
        tp->remove_prop(BNUMEN_M_OATH);
        set_alarm(1.0, 0.0, &do_join(arr[1], arr[0], tp));
        return 1;
    }
        
    if (!objectp(present(arr[0], TO)))
    {
        NFN(lname + " is not here anymore!");
	return 0;
    }

    set_alarm(5.0, 0.0, &continue_repeat(arr, i, tp));
    return 1;
}

/*
 * Function name: continue_repeat
 * Description:   the Lord/Lady says the next line of the oath
 * Arguments:     arr  - the array in BNUMEN_M_OATH
 *                nl   - the line counter
 *                tp   - the applicant
 */
private void
continue_repeat(mixed arr, int nl, object tp)
{
    arr[0]->command("$say " + oath_newbie(arr[1], arr[2], arr[3], nl++));
    tp->add_prop(BNUMEN_I_LINE, nl);
    return;
}

/*
 * Function name: do_join
 * Description:   a bnumen is adopted into a House by the Lord/Lady
 * Arguments:     house  - the name of the House
 *                tp     - the Lord/Lady
 *                newbie - the bnumen
 * Returns:       1 / 0  - success/failure
 */
private int
do_join(string house, object tp, object newbie)
{
    int     result;
    string  nname = newbie->query_name(),
            lname = tp->query_name();

    tp->command("$say And this do I hear, "+lname+", "
      + (tp->query_gender() ? "Lady" : "Lord") + " of the House of "
      + house + ",");
    tp->command("$say and I will not forget it, nor fail to reward that which is given:");
    tp->command("$say fealty with love, valour with honour, oath-breaking with vengeance.");
    tp->catch_tell("You adopt "+CAP(nname)+" and receive "
      + newbie->query_objective() + " into the House of "+house+"!\n");
    say(QCTNAME(tp)+" adopts "+QCTNAME(newbie)+" and receives "
      + newbie->query_objective() + " into the House of "+house+"!\n",
      ({ tp, newbie, }));
    newbie->remove_prop(BNUMEN_S_APPLIED_TO);

    if (newbie->query_guild_name_race() == GUILD_NAME)
    {
        if (!(result = add_unhoused_bnumen(LOW(nname), house, lname)))
        {
            newbie->catch_tell("For unknown reasons, you are not able to " +
                "join the house.\n");
            tp->catch_tell("For unknown reasons, you are not able to adopt " +
                nname + ".\n");
            return 0;
        }

        set_alarm(2.0, 0.0, &newbie->command("$oath"));
        NF("");
        return result;
    }

    if(!(result = add_bnumen(LOW(nname), house, lname)))
    {
        newbie->catch_tell("For unknown reasons you are not able to join the guild.\n");
        tp->catch_tell("For unknown reasons you are not able to adopt "+nname+".\n");
        return 0;
    }

    set_alarm(2.0, 0.0, &newbie->command("$oath"));
    NF("");
    return result;
}

/*
 * Description: make an unhoused player join a house
 * Arguments  : name - name of the player ("olorin")
 *              house - Name of the house ("beor")
 *              lordname - Name of the Sponsor ("baran")
 * Returns:     0 if failure, 1 if success
 */
public varargs int
add_unhoused_bnumen(string name, string house, string lordname = 0)
{
    int result;
    object newbie;
    string gname,
           oldhouse;

    if (!stringp(name))
    {
        return 0;
    }

    name = LOW(name);
    if (!objectp(newbie = find_player(name)) ||
      !objectp(present(newbie, TO)))
    {
        return 0;
    }

    if (!strlen(house))
    {
        return 0;
    }

    if (strlen(gname = newbie->query_guild_name_race()))
    {
        if (gname != GUILD_NAME)
        {
            notify_fail("You are a member of " + gname + "!\n");
            return 0;
        }
        else
        {
            result = 1;
        }
    }
    else 
    {
        newbie->remove_bnumen_from_house(newbie, BNUMEN_NO_HOUSE, "joined " +
            "the House of " + CAP(house));
        result = 1;
    }
    add_to_tree(name, house);
    newbie->set_bnumen_house(house);
    newbie->save_me(1);
    newbie->catch_tell("You are now a member of the House of " + CAP(house) + "!\n");
    return result;
}

/*
 * Description: make a player join the guild
 * Arguments:   name - Name of the player ("olorin")
 *              house - Name of the House ("beor")
 *              lordname - Name of the Sponsor ("baran")
 * Returns:     0 if failure, 1 if sucess
 */
public varargs int
add_bnumen(string name, string house, string lordname = 0)
{
    int     result;
    object  newbie,
            shadow;
    string  gname,
            oldhouse,
            oldlord;

    if (!stringp(name))
        return 0;

    name = LOW(name);
    if (!objectp(newbie = find_player(name)) || 
	!objectp(present(newbie,TO)))
        return 0;

    if (!strlen(house))
        return 0;

    if (strlen(gname = newbie->query_guild_name_race()))
    {
	if (gname != GUILD_NAME)
	{
	    /*
	     * This should never happen:
	     */
	    NFN("You are a member of " + gname + "!\n");
	    return 0;
	}
	else if (strlen(oldhouse = newbie->query_bnumen_house()))
	{
	    /*
	     *	If the player is a member of another House, 
	     *  remove him/her now:
	     */
	    newbie->remove_bnumen_from_house(newbie, oldhouse, "applied " +
		"to the House of "+CAP(house)+" and was released by " +
		newbie->query_prop(BNUMEN_S_RELEASED_BY) + " of");
	    newbie->remove_prop(BNUMEN_S_RELEASED_BY);
            result = 1;
	}
	add_to_tree(name, house);
    }
    else
    {
	// We have to add to the tree before we shadow, so
	// init_race_shadow doesn't complain:
	add_to_tree(name, house);
	NFN("For unknown reasons you are not able to join the guild.");
	shadow = clone_object(BNUMEN_SHADOW);
	if ((result = shadow->shadow_me(newbie, GUILD_TYPE,
					GUILD_STYLE, GUILD_NAME)) != 1)
	{
	    write_file(BNUMEN_LOG, "ERROR: " + CAP(name) +
		       " failed to join the guild on " + 
		       ctime(time()) + "! Result = " + result + ".\n");
	    result = remove_from_tree(name, house, 0);
	    SECURITY->do_debug("destroy", shadow);
	    return 0;
	}
        newbie->add_soul();
        newbie->add_subloc(BNUMEN_S_SUBLOC, shadow);
	newbie->clear_guild_stat(SS_RACE);
	newbie->set_skill(SS_BNUMEN_LEVEL, 0);
    }

    newbie->set_bnumen_house(house);
/*    newbie->catch_tell("From now on you will start your journeys in " +
		       "the Houses of the Black Numenoreans.\n"); 
    newbie->set_default_start_location(BNUMEN_START_LOC);
*/
    newbie->save_me(1);

    if (strlen(lordname))
        write_file(BNUMEN_LOG, "BNUMEN: " + CAP(name)
          + " was adopted into the House of "+CAP(house)
          + " by "+CAP(lordname) + ". " + ctime(time()) + ".\n");
    else
        write_file(BNUMEN_LOG, "BNUMEN: " + CAP(name)
          + " entered the House of "+CAP(house)
	  + " vouched for by " + newbie->query_prop(BNUMEN_S_VOUCHED_FOR)
	  + ". " + ctime(time()) + ".\n");

    newbie->catch_msg("You are now a member of the House of "+CAP(house)+"!\n");
    return result;
}

/*
 * Function name: remove_bnumen_from_house
 * Description:   remove a bnumen from his or her house, but keep
 *                him or her in the guild
 * Arguments:     pl     - object pointer to player
 *                house  - name of the house
 *                reason - why do we remove the player?
 * Returns:       1/0    - success/failure
 */
public int
remove_bnumen_from_house(object pl, string house, string reason)
{
    int     result;
    string  name = pl->query_name();

    if (pl->query_guild_name_race() != GUILD_NAME)
        return 0;

    if (!strlen(house))
        house = pl->query_bnumen_house();

    result = remove_from_tree(name, house, 1);
    write_file(BNUMEN_LOG, "BNUMEN: "+name+" "+reason +
	       " the House of "+house+" on "+ctime(time()) +
	       ". Result = "+result+".\n");
    pl->set_bnumen_house(BNUMEN_NO_HOUSE);

    /*
     * Clears guildstat when changing houses.
     */

    pl->clear_guild_stat(SS_RACE);
    
    if (result)
	return 1;
    return 0;
}

/*
 * Function name: remove_shadow
 * Description:   remove the player from the guild
 * Arguments:     pl - the player object
 * Returns:       see remove_race_guild()
 */
static int
remove_shadow(object pl)
{
    int     result;

    if (result = pl->remove_guild_race())
    {
        pl->clear_guild_stat(SS_RACE);
        pl->remove_skill(SS_BNUMEN_LEVEL);
        pl->setup_skill_decay();
        if (pl->query_default_start_location() == BNUMEN_START_LOC)
            pl->set_default_start_location(pl->query_def_start());
        pl->remove_cmdsoul(BNUMEN_SOUL);
        pl->update_hooks();
    }

    return result;
}

/*
 * Function name: punish_player
 * Description:   punish the player for leaving this guild
 * Argument:      pl - the player object
 * Returns:       1 - player punished, 0 - player was not punished.
 */
private int
punish_player(object pl)
{
    return 1;
}

/*
 * Function name: remove_bnumen
 * Description:   remove a bnumen from the guild
 * Arguments:     pl     - object pointer to player
 *                house  - name of the house
 *                reason - why do we remove the player?
 * Returns:       1 / 0  - success/failure
 */
public int
remove_bnumen(object pl, string house, string reason)
{
    int     result = 0;
    string  name = pl->query_name();

    if (pl->query_guild_name_race() != GUILD_NAME)
        return 0;

    if (!strlen(house))
        house = pl->query_bnumen_house();

    if (!strlen(house))
        house = BNUMEN_NO_HOUSE;

    if (result = remove_shadow(pl))
    {
        if (!stringp(reason))
            punish_player(pl);
        write_file(BNUMEN_LOG, "BNUMEN: "+name+" "+reason
          + " the House of "+house+" on "+ctime(time())+".\n");
        remove_from_tree(name, house, 0);
    }
    else
    {
        write_file(BNUMEN_LOG, "ERROR: "+name+" failed to leave on "
          + ctime(time())+". Reason: "+reason+".\n");
    }

    return result;
}

/*
 * Function name: add_to_tree
 * Description:   add the name of a new bnumen to the Houses mapping
 *                or to the No_House array
 * Arguments:     name - name of the bnumen
 *                house - name of the house, or 0 for No_House
 */
public void
add_to_tree(string name, string house)
{
    string *members;

    name = CAP(LOW(name));

    /*
     *	check if we should add the player to the list of
     *	bnumen without a House:
     */
    if (!stringp(house) || (house == BNUMEN_NO_HOUSE))
    {
	   if (member_array(name, No_House) < 0)
	   {
	       No_House += ({ name });
	       No_House -= ({ 0 });
	       save_object(BNUMEN_TREE);
	   }
	   else
	   {
	       write_file(BNUMEN_LOG, "ERROR: "+name+" added to the " +
               "list of Black Numenoreans without a House, but is " +
		       "already listed there!\n");
       }
       return;
    }

    /*
     *	Get the array of members of the player's new House:
     */

    members = Houses[house][DT_AS_MEMBERS];
    if (!sizeof(members))
        members = ({ });

    if (member_array(name, members) >= 0)
        write_file(BNUMEN_LOG, "ERROR: " + name + 
		   " joins the Houses of " +house +
		   ", but is already listed as a member!\n");
    else
        members += ({ name });
    members -= ({ 0 });

    Houses[house][DT_AS_MEMBERS] = members;

    /*
     *	If the player was listed as bnumen without a House,
     *	remove that entry:
     */
    No_House -= ({ name, 0 });

    save_object(BNUMEN_TREE);
}

/*
 * Function name: add_lord_to_tree
 * Description:   modify the Houses mapping when a new Lord is created
 * Arguments:     name - name of the Lord/Lady
 *                gender - gender id: G_MALE/G_FEMALE
 *                house - name of the House
 */
public void
add_lord_to_tree(string name, int gender, string house)
{
    string  lordname,
           *members;

    if (!sizeof(members = Houses[house][DT_AS_MEMBERS]))
        members = ({});

    name = CAP(LOW(name));

    if (stringp(lordname = Houses[house][DT_S_LNAME]))
    {
        members += ({ lordname });
        write_file(BNUMEN_LOG, "LORDS: "+lordname
          + " replaced by "+name+" as Lord of the House of "
          + house+" on " + ctime(time()) + ".\n");
    }

    members -= ({ name });
    members -= ({ 0 });

    Houses[house][DT_AS_MEMBERS] = members;
    Houses[house][DT_S_LNAME]    = name;
    Houses[house][DT_I_LGENDER]  = gender;
    write_file(BNUMEN_LOG, "LORDS: "+name+" became "
      + (gender ? "Lady" : "Lord") + " of the House of "
      + house+" on "+ctime(time()) + ".\n");

    save_object(BNUMEN_TREE);
}

/*
 * Function name: remove_from_tree
 * Description:   remove a name from the Houses mapping
 *                or from the No_House array
 * Arguments:     name    - name to be removed
 *                house   - name of the House
 *                nohouse - should the player be added to the
 *                          list of bnumen without a House?
 * Returns:		0 - failure, not listed as member
 *                      1 - removed from Houses and added to No_Houses
 *                      2 - removed from Houses and not added to No_Houses
 *                      3 - removed from No_House
 */
public int
remove_from_tree(string name, string house, int nohouse = 1)
{
    int     result = -1;
    string *members;

    if (!strlen(house))
        house = query_bnumen_house(name);

    if (!strlen(house))
        house = BNUMEN_NO_HOUSE;

    name = CAP(LOW(name));
    if (member_array(house, m_indexes(Houses)) < 0)
    {
	if (member_array(name, No_House) < 0)
	{
	    write_file(BNUMEN_LOG, "ERROR: tried to remove " + 
		       name + " from house "+house+"!\n");
	    return 0;
	}
	else
	{
	    No_House -= ({ name });
	    save_object(BNUMEN_TREE);
	    return 3;
	}
    }

    members = Houses[house][DT_AS_MEMBERS];

    if (member_array(name, members) < 0)
    {
        write_file(BNUMEN_LOG, "ERROR: " + name +
		   " leaves the Houses of " + house +
		   ", but is not listed as a member!\n");
	result = 0;
    }
    else
    {
        members -= ({ name });
	result = 2;
    }
    members -= ({ 0 });

    Houses[house][DT_AS_MEMBERS] = members;

    /*
     *	If the player does not leave the guild, he or she should  be
     *	added to the list of bnumen without a House:
     */
    if (nohouse && result)
    {
	No_House += ({ name });
	result = 1;
    }

    save_object(BNUMEN_TREE);

    return result;
}

/*
 *Function name: remove_lord_from_tree
 *Description:   remove the lord entry for a house
 *Arguments:     name  - the name of the Lord or Lady
 *               house - the name of the House
 */
private void
remove_lord_from_tree(string name, string house)
{
    string  lordname,
           *members;

    name  = CAP(LOW(name));
    house = CAP(LOW(house));

    if (name != Houses[house][DT_S_LNAME])
    {
        write_file(BNUMEN_LOG, "ERROR: " + name
          + " tried to resign as Lord of the House of "+house
          + " without being Lord of the House! "
          + ctime(time()) + ".\n");
        return;
    }

    if (!sizeof(members = Houses[house][DT_AS_MEMBERS]))
        members = ({ });

    members += ({ name });
    members -= ({ 0 });

    Houses[house][DT_AS_MEMBERS] = members;
    Houses[house][DT_S_LNAME]    =  0;
    Houses[house][DT_I_LGENDER]  = -1;
    write_file(BNUMEN_LOG, "LORDS: "+name+" resigned as "
      + "Lord of the House of "+house+" on "+ctime(time())+".\n");

    save_object(BNUMEN_TREE);
}

/*
 * Function name: remove_lord_through_death
 * Description:   relieve a Lord or a Lady from his or her position
 *                following a death
 *                called from second_life in the shadow
 * Arguments:     lname - the name of the Lord or Lady
 */
public void
remove_lord_through_death(string lname)
{
    string  house,
            msg,
           *members;

    if (!strlen(lname))
        return;

    lname = CAP(LOW(lname));
    house = query_is_lord(lname);
    if (!strlen(house))
        return;

    if (!sizeof(members = Houses[house][DT_AS_MEMBERS]))
        members = ({});

    msg = "\n\t\t"+CAP(lname) + " died!\n"
      + "\tThe house of "+house+" has lost its "
      + (Houses[house][DT_I_LGENDER] ? "Lady":"Lord")+"!\n";

    tell_bnumen(msg, lname);

    members += ({ lname });
    members -= ({ 0 });

    Houses[house][DT_AS_MEMBERS] = members;
    Houses[house][DT_S_LNAME]    =  0;
    Houses[house][DT_I_LGENDER]  = -1;
    write_file(BNUMEN_LOG, "LORDS: "+lname+" died and was removed "
      + "as Lord of the House of "+house+" on "+ctime(time())+".\n");

    save_object(BNUMEN_TREE);
}

/*
 * Function name: check_open
 * Description:   is the House <house> open?
 * Argument:      house - array for the House in the Houses mapping
 * Returns:       1 / 0 - true/false
 */
public int
check_open(mixed house)
{
    if (sizeof(house[DT_AS_MEMBERS]) || strlen(house[DT_S_LNAME]))
        return 1;
    return 0;
}

/*
 * Function name: query_number_houses
 * Description:   how many of the Houses are open?
 * Returns:       the number of open Houses
 */
public int
query_number_houses()
{
    mapping open_houses;
    open_houses = map(Houses, check_open);
    return sizeof(m_values(open_houses) - ({ 0 }));
}

/*
 * Function name: query_number_bnumen
 * Description:   count the members of the guild or a House
 * Arguments:     house - if given, count members of that House
 *                        if not given, count all members
 *                silent - do we want output written?
 * Returns:       the number of bnumen in the guild/a House
 */
public varargs int
query_number_bnumen(string house, int silent = 1)
{
    int     ndu,
           *ndh,
            i;

    if (strlen(house))
    {
        house = CAP(LOW(house));
        if (member_array(house, m_indexes(Houses)) < 0)
            return 0;
        ndu = sizeof(Houses[house][DT_AS_MEMBERS]);
        if (strlen(Houses[house][DT_S_LNAME]))
            ndu++;
        if (!silent)
            write(sprintf("House of %-11s %14s members.\n",
                house+":", LANG_WNUM(ndu)));
        return ndu;
    }

    ndh = map(m_indexes(Houses), &query_number_bnumen( , silent));

    for (i = 0, ndu = 0; i < sizeof(ndh); i++)
        ndu += ndh[i];
    
    return ndu;
}

/*
 * Function name: query_number_lords
 * Description:	  how many Lords and Ladies of the Black Numenoreans are there?
 * Returns:       the number
 */
public int
query_number_lords()
{
    mixed lords;
    lords = map(m_indexes(Houses), query_house_lord);
    lords -= ({ 0 });
    return sizeof(lords);
}

/*
 * Function name: query_open_house
 * Description:   it is allowed to open the House <house>?
 *                no new House may be opened if:
 *                - there are three or more houses w/o a Lord or Lady,
 *                - there are on average less than 3 bnumen per
 *                  open House.
 * Argument:      house - the name of the House to be opened
 * Returns:       1 / 0 - ok to open/not ok to open
 */
public int
query_open_house(string house)
{
    int     nho,
            ndu,
            nlo;

    if (!strlen(house))
        return 0;

    if (sizeof(Houses[house][DT_AS_MEMBERS]))
        return 1;

    nho = query_number_houses();
    ndu = query_number_bnumen();
    // no new house if not enough bnumen
    if ((nho * 3) > ndu)
        return 0;
    nlo = query_number_lords();
    // no new house of there are three house w/o lord
    if ((nho - nlo) >= 3)
        return 0;

    return 1;
}

/*
 *Function name: check_active
 *Description:   check how long the player <name> has not logged in
 *Argument:      name - name of the player
 *Returns:          1 - the player has logged in in the last two weeks
 *                  0 - the player has not been active recently
 */
public int
check_active(string name)
{
    int     login_time;
    object  fp;

    name = LOW(name);
    fp = SECURITY->finger_player(name);
    login_time = fp->query_login_time();
    fp->remove_object();

    if ((time() - login_time) > DT_LORD_TIME_LIMIT)
        return 0;
    return 1;
}

/* Function name: check_idle_lord
 * Description  : check if a lord is idle and must be removed
 * Argument     : name of the lord
 * Returns      : 1 - lord is idle, remove him
 *                0 - lord is not idle, don't do anything
 */
public int
check_idle_lord(string name)
{
    int     login_time;
    object  fp;
 
    if (!strlen(name))
        return 0;

    name = LOW(name);
    fp = SECURITY->finger_player(name);
    login_time = fp->query_login_time();
    fp->remove_object();
 
    if ((time() - login_time) < LORD_IDLE_TIME)
        return 0;
    return 1;
}

/*
 * Function name: query_house_lord
 * Description:   who is Lord or Lady of the House <house>?
 * Argument:      house - name of the House
 *                if not given, return the names of all Lords and
 *                Ladies in an array
 * Returns:       the name of the Lord or Lady
 */
public varargs mixed
query_house_lord(string house)
{
    int     i;
    string *lords = ({});

    if (!strlen(house))
    {
        for (i = 0; i < sizeof(BNUMEN_HOUSES); i++)
            if (stringp(Houses[BNUMEN_HOUSES[i]][DT_S_LNAME]))
                lords += ({ Houses[BNUMEN_HOUSES[i]][DT_S_LNAME] });
        return lords;
    }

    house = CAP(LOW(house));
    if (member_array(house, BNUMEN_HOUSES) < 0)
        return 0;

    return Houses[house][DT_S_LNAME];
}

/*
 * Function name: query_is_lord
 * Description:   is <lname> a Lord or a Lady of the Black Numenoreans?
 * Argument:      lname - the name of the player
 * Returns:       the name of the House or 0
 */
public string
query_is_lord(string lname)
{
    int     i;

    lname = CAP(LOW(lname));

    for (i = 0; i < sizeof(BNUMEN_HOUSES); i++)
        if (Houses[BNUMEN_HOUSES[i]][DT_S_LNAME] == lname)
            return BNUMEN_HOUSES[i];

    return 0;
}

public string *
query_members(string house = 0)
{
    int     i, s;
    string *members = ({ }),
           *houses;

    if (!strlen(house))
    {
	houses = m_indexes(Houses);
	for (i = 0, s = sizeof(houses); i < s; i++)
	    if (pointerp(Houses[houses[i]][DT_AS_MEMBERS]))
		members += Houses[houses[i]][DT_AS_MEMBERS];
	return members;
    }

    house = CAP(LOW(house));
    if (member_array(house, BNUMEN_HOUSES) < 0)
        return 0;

    return Houses[house][DT_AS_MEMBERS];
}

/*
 * Function name: query_bnumen_house
 * Description:	  Return the name of the House the player belongs to
 * Argument:      name - the name of the player
 * Returns:       the name of the House
 */
public varargs string
query_bnumenorean_house(string name)
{
    int     i;

    if (!strlen(name))
        name = TP->query_name();
    else
        name = CAP(LOW(name));

    for (i = 0; i < sizeof(BNUMEN_HOUSES); i++)
    {
        // added this check to prevent a runtime error in the login sequence
        // if the save file is corrupted
        if (!sizeof(Houses[BNUMEN_HOUSES[i]]))
            return BNUMEN_HOUSES[i];
        if ((member_array(name, Houses[BNUMEN_HOUSES[i]][DT_AS_MEMBERS]) >= 0) ||
            (Houses[BNUMEN_HOUSES[i]][DT_S_LNAME] == name))
            return BNUMEN_HOUSES[i];
    }
    if (member_array(name, No_House) >= 0)
	return BNUMEN_NO_HOUSE;
    return 0;
}

/*
 * Function name: promote_to_lord
 * Description:	  Promote someone to Lord or Lady of a House
 * Argument:      name - name of the new Lord or Lady
 * Returns:       0 success, else error message
 */
public mixed
promote_to_lord(string name)
{
    object  cand;
    string  lordname,
            house;

    name = LOW(name);
    if (!objectp(cand = find_player(name)))
        return "Where is "+CAP(name)+"?\n";

    if (cand->query_guild_name_race() != GUILD_NAME)
        return "You are not a member of a House of the Black Numenoreans, "
          + CAP(name)+"!\n";

    if (cand->query_wiz_level())
        return "No wizard may become "
          + (cand->query_gender() ? "Lady" : "Lord")
          + " of a House of the Black Numenoreans, "+CAP(name)+"!\n";

    house = cand->query_bnumen_house();
    if (stringp(lordname = Houses[house][DT_S_LNAME]))
    {
        if (check_active(lordname))
            return lordname+" is "
              + (Houses[house][DT_I_LGENDER] ? "Lady" : "Lord")
              + " of the House of "+house+"!\n";
    }

    if (cand->query_bnumen_level() < DL_SUB_LORD)
        return "You are not yet worthy to become "
          + (cand->query_gender() ? "Lady" : "Lord")
          + " of a House of the Black Numenoreans, "+CAP(name)+"!\n";

    cand->set_bnumen_lord_level();
    add_lord_to_tree(CAP(name), cand->query_gender(), house);

    return 0;
}

/*
 * Function name: do_renounce
 * Description:   renounce your House - leave the guild
 * Argument:      str - command line argument: [the] 'house' [of] <name>
 * Returns:       1/0 - success/failure
 */
public int
do_renounce(string str)
{
    int     result;
    object  tp = TP;
    string  gname,
            my_house,
            house;

    NFN(CAP(query_verb())+" what?");
    if (!strlen(str))
        return 0;

    if ((gname = TP->query_guild_name_race()) != GUILD_NAME)
    {
        NFN("You are not a member of a House of the Black Numenoreans!");
        return 0;
    }

    my_house = tp->query_bnumen_house();

    if (!strlen(my_house))
    {
        str = lower_case(str);

        if (!parse_command(str, ({ }), "[the] 'bnumen'"))
        {
            notify_fail("Renounce the Black Numenoreans?\n");
            return 0;
        }
        if (result = remove_bnumen(tp, BNUMEN_NO_HOUSE, "renounced"))
        {
            write("You renounce your membership in the Black Numenoreans!\n");
            say(QCTNAME(tp)+" renounces " + tp->query_possessive() +
                " membership in the Black Numenoreans.\n");
        }
 
        notify_fail("For some unknown reason you are unable to " +
            "renounce the Black Numenoreans.\nPlease make a bug report!\n");
        return result;
    }

    str = LOW(str);

    if (!parse_command(str, ({ }), "[the] 'house' [of] %w", house))
    {
        NFN("Renounce which House of the Black Numenoreans?");
	return 0;
    }

    house = CAP(house);
    if (member_array(house, BNUMEN_HOUSES) < 0)
    {
        NFN("There is no House of the Black Numenoreans called "+house+"!");
	return 0;
    }

    if (house != my_house)
    {
        NFN("You are not a member of the House of "+house+"!");
        return 0;
    }

    if (tp->query_bnumen_level() == DL_LORD)
    {
        NFN("As "+(tp->query_gender() ? "Lady" : "Lord") + " of the House of "
          + house+", you cannot renounce your own House!");
        return 0;
    }

    if (result = remove_bnumen(tp, house, "renounced"))
    {
        write("You renounce your membership in the House of "+house+"!\n");
        say(QCTNAME(tp)+" renounces " + tp->query_possessive()
          + " membership in the House of "+house+".\n");
    }

    NFN("For some unknown reason you are unable to renounce your House.\n"
	+ "Please make a bug report!\n");
    return result;
}

/*
 *Function name: do_resign
 *Description:   resign the office of Lord or Lady of the Black Numenoreans
 *Argument:      str - command line argument
 *Returns:       1/0 - success/failure
 */
public int
do_resign(string str)
{
    object  tp = TP;
    string  my_title,
            title,
            my_house,
            house;

    NFN(CAP(query_verb())+" as what?");
    if (!strlen(str))
        return 0;

    if (tp->query_guild_name_race() != GUILD_NAME)
    {
        NFN("You are not a member of a House of the Black Numenoreans!");
        return 0;
    }

    str = LOW(str);

    if (tp->query_gender())
        title = "Lady";
    else
        title = "Lord";

    if (!parse_command(str, ({ }),
        "'as' %w [of] [the] [house] [of] %w", my_title, my_house))
    {
        NFN("Perhaps you wish to resign as the "+title+" of your House?");
        return 0;
    }

    my_title = CAP(my_title);
    my_house = CAP(my_house);

    if ((title != my_title) || (tp->query_bnumen_level() < DL_LORD))
    {
        NFN("You are not the "+title+" of your House!");
        return 0;
    }

    if (member_array(my_house, BNUMEN_HOUSES) < 0)
    {
        NFN("There is no House of the Black Numenoreans called "+house+"!");
	return 0;
    }

    if ((house = tp->query_bnumen_house()) != my_house)
    {
        NFN("You are not the "+title+" of the House of "+my_house+"!");
        return 0;
    }

    tp->set_bnumen_level(DL_SUB_LORD);
    remove_lord_from_tree(tp->query_name(), house);
    write("You resign as "+title+" of the House of "+house+"!\n");
    say(QCTNAME(tp)+" resigns as "+title+" of the House of "+house+"!\n");
    return 1;
}

/*
 * Function name: do_expel
 * Description:	  a Lord or a Lady can expel a members of his or her House
 *                the bnumen will remain in the guild. Any lord or lady
 *                may expel an unhoused Black Numenorean.
 * Argument:      str - command line argument
 * Returns:       1/0 - success/failure
 */
public int
do_expel(string str)
{
    object  tp = TP,
            victim;
    string  house;

    if (tp->query_guild_name_race() != GUILD_NAME)
        return 0;

    if (tp->query_bnumen_level() < DL_LORD)
        return 0;

    if (!strlen(str))
    {
        NFN(CAP(query_verb())+" whom?");
        return 0;
    }

    str = LOW(str);

    if (!objectp(victim = find_player(str)))
    {
        write("That person is not within the realms at the moment!\n");
        return 1;
    }

    if (victim == tp)
    {
        NFN("You cannot expel yourself!");
        return 0;
    }

    if (victim->query_guild_name_race() != GUILD_NAME)
    {
        NFN(CAP(str)+" is not a member of a House of the Black Numenoreans!");
        return 0;
    }

    /* Only allow the lord/lady to expel members of their own house
       or unhoused members. */
    house = tp->query_bnumen_house();
    if (victim->query_bnumen_house() != house && 
      strlen(victim->query_bnumen_house()))
    {
        NFN(CAP(str)+" is not a member of your House!");
        return 0;
    }

    if (remove_bnumen(victim, house, "expelled by "+tp->query_name()+" from"))
    {
	write("You expel "+CAP(str)+" from the House of "+house+"!\n");
	say(QCTNAME(tp)+" expels "+CAP(str)+" from the House of "+house+"!\n",
	    ({ tp, victim}));
	victim->catch_msg(QCTNAME(tp)+" expels you from the House of "+house+"!\n");
	return 1;
    }
    NFN("You fail to expel "+CAP(str)+" from the House of "+house+"!\n" +
	"Please make a bug report!");
    return 0;
}

/*
 * Function name: keep_player
 * Description:   do we want to keep this player?
 * Argument:      pl  - player object
 * Returns:       1/0 - keep/don't keep
 */
public int
keep_player(object pl)
{
    string  race = pl->query_race();

    if ((race != BNUMEN_RACE) && (race != "ghost"))
    {
        pl->catch_msg("Only humans can belong to the Houses of the Black Numenoreans!\n");
        return 0;
    }
    return 1;
}

/*
 * Function name: wiz_add
 * Description:   Admin function to add someone to a house.
 */
public int
wiz_add(string str)
{
    int     result;
    string  name,
            house;

    if (!TP->query_wiz_level())
	return 0;

    if (sscanf(LOW(str), "%s to %s", name, house) != 2)
    {
	NFN("Add whom to which house?");
	return 0;
    }

    if (result = add_bnumen(name, CAP(house)))
	write("You add " + CAP(name) + " to House " + CAP(house) + ".\n");
    else
	write("ERROR: You fail to add " + CAP(name) + " to House " + 
	      CAP(house) + ".\n");

    return result;
}

public int
lord_list(string str)
{
    int     i, s;
    string *lost,
            msg;

    if (!TP->query_wiz_level() &&
	!strlen(query_is_lord(TP->query_name()))) 
	return 0;

    NFN("List what? Try: \"list lost members\".");
    if (!strlen(str))
	return 0;

    if (!parse_command(LOW(str), ({ }), 
		       " 'lost' [members] [bnumen] "))
	return 0;

    lost = filter(query_members(), not @ &SECURITY->exist_player());

    if (!(s = sizeof(lost)))
    {
	write("There are no members of the Houses of the Black Numenoreans " +
	      "that are lost.\n");
	return 1;
    }

    msg = "\n" +
	"\tThese members of the Houses of the Black Numenoreans are lost:\n";

    for (i = 0; i < s; i++)
    {
	msg += "\t" + CAP(lost[i]) + " of the House of " +
	    query_bnumen_house(lost[i]);
	if (i == (s-1))
	    msg += ".\n";
	else
	    msg += ",\n";
    }
    write(msg + "\n");
    return 1;
}

public int
lord_remove(string name)
{
    int     is_wiz;
    string  house,
            lord;

    if (!(is_wiz = TP->query_wiz_level()) &&
	!strlen(query_is_lord(TP->query_name()))) 
	return 0;

    if (!strlen(name))
    {
	NFN("Remove which lost members of the Houses from the " +
	    "lists?");
	return 0;
    }

    name = CAP(LOW(name));
    if (!strlen(house = query_bnumen_house(name)) ||
	SECURITY->exist_player(name))
    {
	NFN(name + " is not one of the lost members of the " +
	    "Houses of the Black Numenoreans.");
	return 0;
    }

    if (strlen(lord = query_house_lord(house)) && 
	(TP->query_name() != lord) && !is_wiz)
    {
	NFN("You can only remove the names of lost members of " +
	    "your own house or of houses without Lord and Lady.");
	return 0;
    }

    write_file(BNUMEN_LOG, "LORDS: " + TP->query_name() +
	       " removes " + name + 
	       " from House " + house + ". " + ctime(time()) +
	       ".\n");
    remove_from_tree(name, house, 0);
    write("You remove the name " + name + " from the list of the " +
	  "members of the House of " + house + ".\n");
    return 1;
}

/*
 * Function name: init
 * Description:   setup commands
 */
public void
init()
{
    ::init();
    add_action(do_enter,    "enter");
    add_action(do_adopt,    "adopt");
    add_action(do_apply,    "apply");
    add_action(do_renounce, "renounce");
    add_action(do_resign,   "resign");
    add_action(do_expel,    "expel");
    add_action(do_expel,    "dexpel");
    add_action(do_examine,  "l");
    add_action(do_examine,  "look");
    add_action(do_examine,  "exa", 1);
    add_action(do_examine,  "read");
    add_action(do_repeat,   "repeat");
    add_action(do_repeat,   "say");
    add_action(do_repeat,   "'", 2);
    add_action(do_vouch,    "vouch");
    add_action(do_release,  "drelease");
    add_action(do_release,  "release");
    // administrative commands for Lords and wizards:
    add_action(wiz_add,     "add");
    add_action(lord_list,   "list");
    add_action(lord_remove, "remove");
}

/*
 * Function name: oath_newbie
 * Description:   the oath sworn by a bnumen being adopted into a House
 * Arguments:     house - the name of the House
 *                title - "Lord"/"Lady"
 *                name  - the name of the newbie
 *                line  - line number, if == -1, set up the text.
 * Returns:       an array holding the text of the oath if line < 0
 *                or or the text of the line
 */
public varargs mixed
oath_newbie(string house, string title, string name, int nl)
{
    int     s;

    if (nl < 0)
    {
	Oath = ({ "Here do I swear fealty and service to Gondor,",
		  "to the Lord and Steward of the realm,",
		  "and to the House of "+house+",",
		  "to speak and to be silent, to do and to let be,",
		  "to come and to go, in need or plenty, in peace or war,",
		  "in living or dying, from this hour henceforth,",
		  "until my "+title+" release me, or death take me,",
		  "or the world end.",
		  "So say I, "+CAP(name)+".", 
	      });

	return Oath;
    }

    if (nl > (s = sizeof(Oath)))
        return Oath;
    else if (nl == s)
        return 0;
    else
        return Oath[nl];
}

/*
 * Function name: query_bnumen_house
 * Description:	  Interface to query_bnumen_house for
 *                backwards compatibility.
 * Argument:      name - the name of the player
 * Returns:       the name of the House
 */
public varargs string
query_bnumen_house(string name)
{
    return query_bnumenorean_house(name);
}

public int
fix_it(string name)
{
    object pl = find_player(LOW(name));

    if (!TP->query_wiz_level())
	return 0;
    pl->set_bnumen_house(query_bnumen_house(CAP(LOW(name))));
    return 1;
}
