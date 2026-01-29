/*
 * File:     council.h
 * Created:  Cirion, 1999.03.02
 * Purpose:  Council commands for the monks
 * Modification Log:
 *
 */
#include <wa_types.h>
#include <composite.h>

int
mtoken_help()
{
    reset_euid();
    // read the help file
    return this_player()->more(MONK_DOC + "council/council_token.help", 1);
}

int
mtoken_create(string str)
{
    string    *parts, where, short_desc, long_desc;
    object    tp = this_player();
    // mapping of possible body locations
    mapping   locations =
        ([
          "body"              :  A_BODY,
          "torso"             :  A_TORSO,
          "chest"             :  A_CHEST,
          "head"              :  A_HEAD,
          "neck"              :  A_NECK,
          "waist"             :  A_WAIST,
          "legs"              :  A_LEGS,
          "right arm"         :  A_R_ARM,
          "left arm"          :  A_L_ARM,
          "both arms"         :  A_ARMS,
          "either arm"        :  A_ANY_ARM,
          "right hand"        :  A_R_HAND,
          "left hand"         :  A_L_HAND,
          "both hands"        :  A_HANDS,   
          "eith hand"         :  A_ANY_HAND,  
          "right finger"      :  A_R_FINGER,   
          "left finger"       :  A_L_FINGER,  
          "all fingers"       :  A_FINGERS,
          "any finger"        :  A_ANY_FINGER, 
          "right foot"        :  A_R_FOOT,
          "left foot"         :  A_L_FOOT, 
          "both feet"         :  A_FEET,
          "either foot"       :  A_ANY_FOOT,  
          "right wrist"       :  A_R_WRIST,
          "left wrist"        :  A_L_WRIST,
          "both wrists"       :  A_WRISTS,
          "any wrist"         :  A_ANY_WRIST, 
          "right ankle"       :  A_R_ANKLE,
          "left ankle"        :  A_L_ANKLE,
          "both ankles"       :  A_ANKLES, 
          "any ankle"         :  A_ANY_ANKLE,  
          "right ear"         :  A_R_EAR,
          "left ear"          :  A_L_EAR,
          "both ears"         :  A_EARS,
          "any ear"           :  A_ANY_EAR, 
          "right hip"         :  A_R_HIP,
          "left hip"          :  A_L_HIP,
          "both hips"         :  A_HIPS,
          "either hip"        :  A_ANY_HIP, 
          "right shoulder"    :  A_R_SHOULDER, 
          "left shoulder"     :  A_L_SHOULDER,
          "both shoulders"    :  A_SHOULDERS, 
          "either shoulder"   :  A_ANY_SHOULDER, 
          "eyebrow"           :  A_BROW,
          "eyes"              :  A_EYES,
          "back"              :  A_BACK,
        ]);


    parts = explode(str, ";"); // delimited by ; characters

    if(sizeof(parts) != 3)
    {
        notify_fail("You must specify: mtoken create <location>;<short description>;"
            + "<long description>\nSee 'mtoken help' for more details.\n");
        return 0;
    }

    where = parts[0];
    short_desc = parts[1];
    long_desc = parts[2];

    if(member_array(where, m_indices(locations)) == -1)
    {
        notify_fail("Invalid location: '" + where + "'.\nPossible choices are: "
            + COMPOSITE_WORDS(m_indices(locations)) + ".\n");
        return 0;
    }

    if(strlen(short_desc) > 45)
    {
        notify_fail("The short description of the item is too long.\n");
        return 0;
    }

    if(strlen(long_desc) < 20)
    {
        notify_fail("The long description of the item is too short.\n");
        return 0;
    }

    // save the information in the manager
    MANAGER->set_council_info(tp->query_real_name(), 0,
        locations[where], short_desc, long_desc);
    present("_token_" + tp->query_real_name(), tp)->remove_object(); // remove any token the player has

    reset_euid();
    clone_object(MONK_CTOKEN)->move_config(tp, tp->query_real_name()); // clone it back to him/her

    m_log(this_player()->query_name() + " created a council token: " + str);
    write("You create and obtain your council token.\n");
    return 1;
}

int
mtoken_revoke(string str)
{
    mixed      info;

    info = MANAGER->get_council_info(lower_case(str));

    if(!pointerp(info) || (sizeof(info) < 4))
    {
        notify_fail(capitalize(str) + " does not have any council token.\n");
        return 0;
    }

    if (info[1] == MONK_TOKEN_NONE)
    {
        notify_fail("The council token of " + capitalize(str) + " has already "
            + "been revoked.\n");
        return 0;
    }

    MANAGER->set_council_info(lower_case(str), 0, MONK_TOKEN_NONE, MONK_TOKEN_NONE, MONK_TOKEN_NONE);

    m_log(this_player()->query_name() + " revoked the council token of: " + str);
    write("You revoke the token of " + capitalize(str) + ".\n");
    return 1;
}


/*
 * Function name: mtoken
 * Description:   Council command to be able to offer
 *                or configure their own special token.
 * Returns:       1 if successful
 */
public int
mtoken(string str)
{
    object    *oblist;
    object     who;
    object     token;
    object     tp = this_player();
    mixed      info;
    int        when, time_until;

    if(!m_query_council_member(tp)) // command is only allowed for council
        return 0;

    notify_fail("Mtoken <help / create / revoke / who>?\n");
    if(!strlen(str))
        return 0;

    if(str == "help")
        return mtoken_help();

    if(sscanf(str, "create %s", str) > 0)
        return mtoken_create(str);

    if(sscanf(str, "revoke %s", str) > 0)
        return mtoken_revoke(str);

    // otherwise assume we are giving it to a player
    oblist = parse_this(str, "[to] [the] %l");
    if(!sizeof(oblist))
    {
        notify_fail("Mtoken <help / create / who>?\n");
        return 0;
    }

    if(sizeof(oblist) > 1)
    {
        notify_fail("You can only give your token to one person "
            + "at a time.\n");
        return 0;
    }

    who = oblist[0];

    if(present("_token_" + tp->query_real_name(), who))
    {
        notify_fail("That person already has your token.\n");
        return 0;
    }

    info = MANAGER->get_council_info(tp->query_real_name());

    notify_fail("You have not yet created a token. You need to "
        + "first do so with 'mtoken create'.\n");
    if((!pointerp(info)) || (sizeof(info) < 4))
        return 0;

    if(info[1] == "" || info[2] == "")
        return 0;


    when = info[3];
    time_until = (time() - when) / (60 * 60 * 24);

    /*
    if(time_until < 30)
    {
        write("You can only give away one token per month. You "
            + "still have " + (30 - time_until) + " days left until "
            + "you can give out another.\n");
        if(tp->query_wiz_level())
            write("... but since you are a wizard, you can anyway.\n");
        else
            return 1;
    }
    */

    if (info[1] == MONK_TOKEN_NONE)
    {
        notify_fail("Your council token has been revoked. You need to "
            + "create a new one.\n");
        return 0;
    }

    // record the last time this player gave away a token
    MANAGER->set_council_info(tp->query_real_name(), time());

    reset_euid();
    token = clone_object(MONK_CTOKEN);
    token->move_config(who, tp->query_real_name()); // clone it to him/her
    actor("You present", oblist," with " + LANG_ADDART(token->short(tp)) + ".");
    target(" presents you with " + LANG_ADDART(token->short(target)) + ".", oblist);
    all2actbb(" presents", oblist, " with " + LANG_ADDART(token->short(tp)) + ".");
    return 1;
}

int mtitle (string str)
{
    string  who;
    string * titles = ({
        "Eye of the Dragon",
        "Mind of the Dragon",
        "Heart of the Dragon",
        "Body of the Dragon",
        "Soul of the Dragon",
        "Ear of the Dragon",
        "Claw of the Dragon",
        "Wing of the Dragon",
        "nothing" });

    if(!m_query_council_member(this_player ())) // command is only allowed for council
        return 0;

    notify_fail ("Set your council title to what? Possible options "
        + "are: " + COMPOSITE_WORDS (titles) + ".\n");


    if (!strlen (str))
        return 0;

    if (member_array (str, titles) == -1)
        return 0;

    if ((who = MANAGER->find_council_title (str)) != "")
    {
        if (m_query_council_member (who))
		{
        	notify_fail ("That title is already taken by "
            	+ capitalize (who) + ".\n");
        	return 0;
		}
    }    

    write ("You set your council title to: " + str + ".\n");
    if (str == "nothing")
        str = "";

    MANAGER->set_council_title (this_player()->query_real_name(),
        str);
    return 1;
}

