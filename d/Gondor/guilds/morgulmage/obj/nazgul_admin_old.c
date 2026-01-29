
/*

Pending ideas:

Bonus settings:
<herbalist> - Grants access to herb store.
<alchemist> - Grants access to potion store.
<rider> - Grants access to mortal version of our horses.
        - Our horseman would give them bree style horses.
*/

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <std.h>
#include <macros.h>
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
#include "nazgul_admin_ceremony.c"

void
create_object()
{
    set_short("_nazgul_admin_object");
    set_name("_nazgul_admin_object");
    set_long("A strange object that shifts and changes colours, making "
        + "it tremendously difficult to focus upon.\n");

    set_no_show();

    add_prop(OBJ_M_NO_GET, "You cannot focus upon this object long enough "
        + "to pick it up.\n");
    add_prop(OBJ_I_VOLUME,      10);
    add_prop(OBJ_I_WEIGHT,      10);
    add_prop(OBJ_I_VALUE,        0);
}

int declare_cmd(string args) 
{
    if (!this_player()->query_nazgul()) return 0;
    
    string name, setting, reason, msg;
    string *valid_settings = ({ "friend", "ally", "foe", "enemy", "worthless",
        "beneath" });
    
    if(!args || !parse_command(args, environment(), 
        "%w [as] %w [notice] [for] %s", name, setting, reason)) 
    {
        notify_fail("Usage: declare [who] as [friend/foe/beneath notice] "
            + "for [reason]?\n");
        return 0;
    }
    
    if (member_array(setting, valid_settings) == -1) {
        notify_fail("You can only declare someone as friend, foe or " 
            + "beneath notice.\n");
        return 0;
    }
    
    if (setting == "beneath") setting = "beneath notice";
    
    if (!SECURITY->exist_player(name))
    {
        notify_fail( "You have never heard about anyone of the name "+
            capitalize( name )+ "!\n" );
        return 0;
    }
    
    if (member_array(name, MORGUL_MASTER->query_mages()) > -1)
    {
        notify_fail(capitalize(name)+ " is a member of the Society "+
            "of Morgul Mages!\nYou cannot declare a member of the "+
            "Society as "+ setting + " of Minas Morgul!\n" );
        return 0;
    }
    
    switch(setting) 
    {
    case "friend":
    case "ally":
        MORGUL_MASTER->add_friend(name, reason, this_player()->query_real_name());
        msg = "a friend";
        break;
    case "enemy":
    case "foe":
        MORGUL_MASTER->add_foe(name, reason, this_player()->query_real_name());
        msg = "an enemy";
        break;
    case "worthless":
    case "beneath notice":
        MORGUL_MASTER->remove_friend_or_foe(name);
        msg = "beneath notice";
        break;
    }
    
    write("You declare " + capitalize(name) + " to be " + msg
        + " of Minas Morgul.\n");
    say(QCTNAME(this_player()) + " declares " + capitalize( name )
        + " to be " + msg + " of Minas Morgul!\n" );

    write_file(MORGUL_NAZGUL_RECORDS, this_player()->query_name() 
        + " declares " + capitalize(name) + " to be " + msg 
        + " of Minas Morgul: " + reason + " (" + ctime(time()) + ").\n");
    MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_MAJOR);
    return 1;
}

private string get_friends_or_foes(string type) 
{
    mapping fof = MORGUL_MASTER->query_friends_and_foes();
    string result = "";
    
    foreach(string name, mapping data : fof) 
    {
        if (data["status"] == type) {
            result += sprintf("  %15s - %-=60s\n",
                capitalize(name), data["reason"]);
        }
    }
    
    return result;  
}

/*
 * Function name: do_list
 * Description  : list the names of the players declared
 *                friend or foe of Minas Morgul
 * Arguments    : string arg - the command argument:
 *                list <friend|foe>
 * Returns      : 1/0
 */
public int list_cmd( string arg )
{
    switch (arg)
    {
    case "friends":
    case "friend":
    case "allies":
    case "ally":
        string friends = get_friends_or_foes("friend");
        if (!strlen(friends))
        {
            write( "\tFeared be the Dark Lord!\n"+
                "\tNone have been declared to be His allies!\n" );
        }
        else
        {
            write("These are the names of those who have "+
                "been declared to be allies of the Dark Lord and of "+
                "Minas Morgul:\n\n" + friends); 
        }
        break;
    case "enemies":
    case "enemy":
    case "foes":
    case "foe":
        string foes = get_friends_or_foes("foe");
        if (!strlen(foes))
        {
            write("\tPraised be the Dark Lord!\n"+
                "\tNone have been declared to be His enemies!\n");
        }
        else
        {
            write("These are the names of those who have "+
                "been declared to be foes of the Dark Lord and of "+
                "Minas Morgul:\n\n" + foes);
        }
        break;
    case "all":
    case "friends and foes":
        list_cmd( "friends" );
        write("\n");
        list_cmd( "foes" );
        break;
    default:
        notify_fail( "Syntax: List <friends|foes>\n" );
        return 0;
    }
    MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_MINOR);
    return 1;
}

private mixed is_candidate_for_nazgul(string name)
{
    string *nazgul_names = MORGUL_MASTER->query_nazgul_names();
    
    if (sizeof(nazgul_names) == 9) 
        return "There is no ring left to create a new Nazgul!\n";
        
    if (member_array(name, nazgul_names) != -1)
        return capitalize(name) + " is already on of the Nazgul!\n";
        
    if (!MORGUL_MASTER->query_is_mage(name))
        return "There is no Servant of the Dark Lord of that name!\n";
            
    if (!MORGUL_MASTER->query_is_full_mage(name))
        return "An apprentice may not become one of the Nazgul!\n";
        
    if (SECURITY->query_wiz_rank(name))
        return "A Wizard may not become one of the Nazgul!\n";
        
    return 1;
}

private mixed is_candidate_for_lord_nazgul(string name)
{
    string lord = MORGUL_MASTER->query_lord_nazgul();
    if (lord) 
        return capitalize(lord) + " is already Lord of the "
            + "Nazgul, King of Morgul!\n";
    
    string *nazgul_names = MORGUL_MASTER->query_nazgul_names();
    if (member_array(name, nazgul_names) == -1)
        return "There is none of the Nazgul of that name and "
            + "only a Nazgul can become Lord of the Nazgul!\n";
    
    if (sizeof(nazgul_names) < 3)
        return "There must be at least three Nazgul before "
            + "there can be a Lord of the Nazgul!\n";
            
    return 1;
}

public int vote_cmd(string args)
{
    string name, which;
    
    if (!this_player()->query_nazgul()) return 0;
    
    notify_fail("Vote for <candidate> for Nazgul or for Lord.\n");
    if (!args || args == "")
    {        
        return 0;
    }
    
    if ((sscanf(args, "for %s", name) == 1) &&
        sizeof(explode(name, " ")) == 1)
    {
        which = "nazgul";
    }
    else if (sscanf(args, "for %s for %s", name, which) != 2)
    {
        return 0;
    }

    name = lower_case(name);
    
    if (which == "nazgul") 
    {   
        mixed result = is_candidate_for_nazgul(name);
        
        if (stringp(result)) {
            notify_fail(result);
            return 0;
        }
        
        MORGUL_MASTER->add_vote_for_nazgul(this_player(), name);
        
        write("You vote for " + capitalize(name) + " to become one of "
            + "the Nazgul!\n");
        say(QCTNAME(this_player()) + " votes for " + capitalize( name )
            + " to become one of the Nazgul!\n");
            
        MORGUL_MASTER->increase_activity(this_player(), 2 * ACTIVITY_TYPICAL);        
        return 1;
    }
    
    if (which == "lord")
    {
        mixed result = is_candidate_for_lord_nazgul(name);        
        if (stringp(result)) {
            notify_fail(result);
            return 0;
        }
        
        MORGUL_MASTER->add_vote_for_lord_nazgul(this_player(), name);
        
        write("You vote for " + capitalize(name) + " to become Lord of "
            + "the Nazgul!\n");
        say(QCTNAME(this_player()) + " votes for " + capitalize( name )
            + " to become Lord of the Nazgul!\n");
        
        MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_MAJOR);
        return 1;
    }
    
}

public int remove_vote_cmd(string args)
{
    string which;
    
    if (!this_player()->query_nazgul()) return 0;

    notify_fail( "Remove vote for Nazgul or for Lord.\n" );
    if (!args || args == "") return 0;


    if (!parse_command(args, ({}), "[vote] [for] %w", which))
        return 0;
        
    if (which == "nazgul") {
    
        string *voters = m_indices(MORGUL_MASTER->query_nazgul_votes());
        if (member_array(this_player()->query_real_name(), voters) == -1)
        {
           notify_fail( "You have not cast a vote for Nazgul!\n" );
           return 0;
        }
        
        MORGUL_MASTER->remove_vote_for_nazgul(this_player());

        write("You remove your vote for Nazgul!\n");
        say(QCTNAME(this_player()) + " removes " 
            + this_player()->query_posessive() + " vote for Nazgul!\n");
           
        MORGUL_MASTER->increase_activity(this_player(), 2 * ACTIVITY_TYPICAL);
        return 1;        
    }
    
    if (which == "lord") {

        string *voters = m_indices(MORGUL_MASTER->query_lord_nazgul_votes());
        if (member_array(this_player()->query_real_name(), voters) == -1)
        {
           notify_fail( "You have not cast a vote for Lord Nazgul!\n" );
           return 0;
        }
        
        MORGUL_MASTER->remove_vote_for_lord_nazgul(this_player());

        write("You remove your vote for Lord of the Nazgul!\n");
        say(QCTNAME(this_player()) + " removes " 
            + this_player()->query_posessive() + " vote for Lord of the "
            + "Nazgul!\n");
           
        MORGUL_MASTER->increase_activity(this_player(), 2 * ACTIVITY_TYPICAL);
        return 1;        
    }
    
    return 0;
}

private string print_votes(string which)
{
    int nazgul_count = sizeof(MORGUL_MASTER->query_nazgul_names());
    string str = "";

    if (which == "nazgul")
    {
        str = "\n\tThere " + (nazgul_count == 1 ? "is ":"are ") 
            + LANG_WNUM(nazgul_count) + " Nazgul!\n";
            
        if (nazgul_count == 9)
        {
            str += "\tThere are only nine rings for mortals doomed to die!\n"
                + "\tWithout a ring to spare, there can be no new Nazgul!\n";
            return str + "\n";
        }
        else {
            int remaining_rings = 9 - nazgul_count;
            str += "\tThere are nine rings for mortals doomed to die!\n"
                + "\tSo there " + (remaining_rings == 1 ? "is one ring"
                : "are " + LANG_WNUM(remaining_rings) + " rings")
                + " left to create new Nazgul!\n";
        }

        mapping votes = MORGUL_MASTER->query_nazgul_votes();
        if (m_sizeof(votes) == 0)
        {
            return str + "\n" + "\tThere have been no votes cast yet!\n\n";
        }
                
        string *candidates = ({ });
        str += "\n\tThe following votes have been cast:\n";
        foreach(string nazgul, string mage : votes) 
        {
            str += sprintf("\t%-12s voted for %-12s\n",
                capitalize(nazgul), capitalize(mage));
            if (member_array(mage, candidates) == -1) 
                candidates += ({ mage });
        }
        
        foreach(string mage : candidates) 
        {
            if (!MORGUL_MASTER->query_valid_promotion_to_nazgul(mage)) 
                continue;
                
            str += "\n\t"+ capitalize(mage)
                + " has sufficient votes to be promoted to Nazgul!\n";
            
            if (MORGUL_MASTER->is_idle(mage))
            {
                str += "\tThe Dark Lord, however, has some doubts and "
                    + "your request will be rejected.\n"
                    + "\tWith the power of the Black Master flowing "
                    + "through you,\n\tfeeling the bond, you feel "
                    + "certain however that in time\n\t" + capitalize(mage)
                    + " will regain the His trust.\n";
            }
            
            str += "\n";
        }
        return str + "\n";
    }
    else if ((which == "lord") || (which == "king"))
    {
        string lord = MORGUL_MASTER->query_lord_nazgul();
        if (strlen(lord))
        {
            str = "\n\t" + capitalize(lord)
                + " is Lord of the Nazgul and King of Morgul!\n";
            return str+ "\n";
        }
        
        str = "\n\tThere " + (nazgul_count == 1 ? "is " : "are ") 
            + LANG_WNUM(nazgul_count) + " Nazgul!\n";
            
        if (nazgul_count < 3)
        {
            str +=
                "\tThere must be at least three Nazgul before it is\n"+
                "\tpossible to vote for the Lord of the Nazgul!\n";
            return str+ "\n";
        }
        
        mapping votes = MORGUL_MASTER->query_nazgul_votes();
        if (m_sizeof(votes) == 0)
        {
            return str + "\n\tThere have been no votes cast yet!\n\n";
        }
        
        string *candidates = ({ });
        str += "\n\tThe following votes have been cast:\n";
        foreach(string nazgul, string mage : votes) 
        {
            str += sprintf("\t%-12s voted for %-12s\n",
                capitalize(nazgul), capitalize(mage));
            if (member_array(mage, candidates) == -1) 
                candidates += ({ mage });
        }
        
        foreach(string mage : candidates) 
        {
            if (!MORGUL_MASTER->query_valid_promotion_to_lord_nazgul(mage)) 
                continue;

            str += "\n\t"+ capitalize(mage)+ " has sufficient votes "
                + "to be promoted to Lord of the Nazgul!\n";
        }                

        return str + "\n";
    }

    return 0;
}

public int check_cmd(string args)
{
    string which;

    notify_fail(capitalize(query_verb()) + " votes for Nazgul or for Lord?\n");
    if (!args || args == "")
    {
        return 0;
    }
    
    if (args == "votes")
    {
        which = "nazgul";
    }
    else if (sscanf(args, "votes for %s", which ) != 1)
    {
        return 0;
    }

    if ((which != "nazgul") && (which != "lord") && (which != "king"))
    {
        return 0;
    }
    
    if (!this_player()->query_nazgul() && 
        (SECURITY->query_wiz_rank(this_player()->query_real_name()) < WIZ_NORMAL))
    {
        notify_fail("You do not have the power to " + query_verb() + " the votes!\n");
        return 0;
    }

    write(print_votes(which));
    MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_MINOR);
    return 1;
}

public int lord_has_voted_for_mage(string name) {
	string lord = MORGUL_MASTER->query_lord_nazgul();
	if (!lord) return 0;
	
	foreach(string nazgul, string mage : MASTER->query_nazgul_votes()) {
		if ((nazgul == lord) && (mage == name)) return 1;
	}
	
	return 0;
}

public int promote_cmd(string args)
{
    string name, which, tmp;
    int use_ceremony = 1;
    
    if (!this_player()->query_nazgul()) return 0;

    notify_fail("Promote whom to Nazgul or Lord?\n" );
    if (strlen(args) && (sscanf(args, "%s without ceremony", tmp) == 1)) 
    {
        args = tmp;
        use_ceremony = 0;
    }
    
    if (!strlen(args) || (sscanf(args, "%s to %s", name, which) != 2))
    {
        return 0;
    }
    
    object player = find_player(name);
    if (!objectp(player) || (environment(player) != environment(this_object())))
    {
        notify_fail("The candidate must be in this room.\n");
        return 0;
    }
    
    if (which == "nazgul")
    {
        string lord = MORGUL_MASTER->query_lord_nazgul();
		
		int player_is_not_lord = (this_player()->query_real_name() != lord); 
        if ((lord && player_is_not_lord) && !lord_has_voted_for_mage(name))
        {
            notify_fail("Only the Lord of the Nazgul may promote a Servant "
                + "of the Dark Lord to Nazgul!\n");
            return 0;
        }
        
        if (MORGUL_MASTER->is_idle(player))
        {
            notify_fail(capitalize(player->query_real_name())
                + " didn't regain the trust of the Dark Lord yet!\n" );
            return 0;        
        }
        
        mixed result = is_candidate_for_nazgul(name);        
        if (stringp(result)) {
            notify_fail(result);
            return 0;
        }
        
        if (!MORGUL_MASTER->query_valid_promotion_to_nazgul(name))
        {
            notify_fail(capitalize(player->query_real_name())
                + " doesn't have sufficient votes to be promoted!\n" );
            return 0;        
        }

        if (!use_ceremony) 
        {
            MORGUL_MASTER->set_player_as_nazgul(player);
            
            write("You advance " + capitalize(name) + " into the rank of "
                + "a Nazgul!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())
                + " transforms " + QTNAME(player) + " into a nazgul!\n",
                ({ this_player(), player, }) );
            player->catch_tell("You have been transformed into a Nazgul by "+
                this_player()->query_name()+ ", "+
                this_player()->query_guild_title_occ()+ "!\n");
                
            MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_REWARD);
        }
        else
        {
            write("You initiate the ceremony to advance " + capitalize(name) 
                + " into the rank of a Nazgul!\n");
            initiate_nazgul_ceremony(this_player(), player);
        }
        
        MORGUL_MASTER->clear_votes_for_nazgul();
        return 1;
    }
    else if (which == "lord")
    {
        mixed result = is_candidate_for_lord_nazgul(name);        
        if (stringp(result)) {
            notify_fail(result);
            return 0;
        }
        
        if (!MORGUL_MASTER->query_valid_promotion_to_lord_nazgul(name))
        {
            notify_fail(capitalize(player->query_real_name())
                + " doesn't have sufficient votes to be promoted!\n" );
            return 0;        
        }
        
        if (this_player()->query_real_name() == name)
        {
            notify_fail("You cannot promote yourself to Lord Nazgul.\n");
            return 0;
        }
        
        MORGUL_MASTER->set_player_as_lord_nazgul(player);
        
        write("You promote " + capitalize(name) + " to the Lord of the "+
            "Nazgul!\n");
        player->catch_tell("You have been promoted to Lord of the "
            + "Nazgul by "+ this_player()->query_name()+ ", "
            + this_player()->query_guild_title_occ()+ "!\n" 
            + "As sign of your rank you receive the Crown of Morgul.\n");
        
        MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_REWARD);
        MORGUL_MASTER->clear_votes_for_lord_nazgul();
        return 1;        
    }
}

public int resign_cmd(string args)
{
    if (!this_player()->query_nazgul()) return 0;
    
    if (!args || args == "" || (args != "as nazgul" && args != "as lord")) 
    {
        notify_fail("Resign as nazgul or lord?\n");
        return 0;
    }

    if (args == "as nazgul")
    {
        MORGUL_MASTER->remove_player_as_nazgul(this_player(), "resignation");
        MORGUL_MASTER->set_as_archmage(this_player());
        
        write("You resign as Nazgul!\n");
        say(QCTNAME(this_player())+ " resigns as Nazgul!\n");
        
        MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_REWARD);
    }
    
    if (args == "as lord")
    {
        if (MORGUL_MASTER->query_lord_nazgul() != this_player()->query_real_name())
        {
            notify_fail("You do not hold the rank of Lord of the Nazgul.\n");
            return 0;
        }
        
        MORGUL_MASTER->remove_player_as_lord_nazgul(this_player(), "resignation");
        
        write("You resign as Lord of the Nazgul!\n");
        say(QCTNAME(this_player()) + " resigns as Lord of the Nazgul!\n");
        
        MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_REWARD);
    }
    
    return 1;
}

void init()
{
    ::init();
    
    // Voting system
    add_action(vote_cmd,        "vote" );
    add_action(remove_vote_cmd, "mremove" );
    add_action(check_cmd,       "check" );
    add_action(check_cmd,       "read" );
    
    // Promoting / resigning
    add_action(promote_cmd,     "promote");
    add_action(resign_cmd,      "resign");
    
    // Friend or Foes
    add_action(declare_cmd,     "declare");
    add_action(list_cmd,        "list");
}
