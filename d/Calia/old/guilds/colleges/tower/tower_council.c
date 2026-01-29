/* 
   A room on the second floor of the Tower of Elemental Magic 

   This is the council chamber, but the council code isn't here. The
   functions here just pass along variables to the council control object,
   which is located at ~Calia/guilds/colleges/specials/council_control.c 
    
   Created 16.1.2000, Bishop
   
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <filter_funs.h>
#include <composite.h>
#include "defs.h";

#define COUNCIL_I_SITTING "_council_i_sitting"


string
chairpeeps()
{
    object *sitters = filter(FILTER_LIVE(all_inventory(TO)), 
        &->query_prop(COUNCIL_I_SITTING));
    
    if (sizeof(sitters) > 2 && !(member_array(TP, sitters) == -1))
    {
        return "You are sitting in your chair, and so are " + 
            COMPOSITE_ALL_LIVE(sitters - ({ TP })) + ". ";
    }
    else
    if (sizeof(sitters) > 1 && !(member_array(TP, sitters) == -1))
    {
        return "You are sitting in your chair, and so is " + 
            COMPOSITE_ALL_LIVE(sitters - ({ TP })) + ". ";
    }    
    else if (sizeof(sitters) > 1)
    {
        return "Sitting in their chairs are " + COMPOSITE_ALL_LIVE(sitters) +
            ". ";
    }
    else if (sizeof(sitters) && sitters[0] == TP)
    {
        return "You are sitting at the table. ";
    }
    else if (sizeof(sitters))
    {
        return "Sitting in " + sitters[0]->query_possessive() + " chair is " + 
            COMPOSITE_ALL_LIVE(sitters[0]) + ". ";
    }
    else
    { 	
        return "";
    }
}


int
check_sitting()
{
    if (TP->query_prop(COUNCIL_I_SITTING) == 1)
    {
        TP->catch_tell("You need to get up before you can move!\n");
        return 1;
    }
    else
    {
        return 0;
    }
}


create_room()
{
    set_short("Tower Assembly Chambers");

    set_long("This is the meeting room for the Assembly. Here the Principals" +
        " of the Colleges gather and set policy for the rest of the guild." +
        " Four plush chairs stand in one corner of the room, facing each" +
        " other. @@chairpeeps@@Nearby, a fireplace burns with an eerie and" +
        " smokeless flame."+
        " On another wall there is a blackboard used to keep track of current"+
        " votes, next to it - a ballot box. A sign is posted near the box. " +
        basic_desc + " To the east a corridor stretches.\n");

    add_item(({"chairs", "plush chairs"}), "While each chair is lined with" +
        " comfortable cushions, they all look different. It is clear that" +
        " there is one for each element.\n");
    add_item(({"fire chair", "Fire chair"}), "The chair for the Principal of" +
        " the College of Fire Magic looks cut from some kind of lava stone," +
        " and has an organge hue.\n"); 
    add_item(({"water chair", "Water chair"}), "The chair for the Principal" +
        " of the College of Water Magic appears sculpted from ice, but it" +
        " does not melt nor does it feel particularly cool.\n"); 
    add_item(({"air chair", "Air chair"}), "The chair for the Principal of" +
        " the College of Air Magic seems to be crafted from a strange type" +
        " of crystal that looks clear, but distorts and twists any attempt" +
        " to view through it.\n");
    add_item(({"earth chair", "Earth chair"}), "The chair for the Principal" +
        " of the College of Earth Magic appears hewn from a massive block" +
        " of granite.\n");
    add_item(({"ballot box", "box"}), "This plain box is used to cast votes" +
        " in.\n");
    add_item("fireplace", "The silent flame that dances inside the fireplace" +
        " emits little noticable heat.\n");
    add_item("blackboard", "This square blackboard is used to list current" +
        " matters that are up for voting in the Assembly.\n");
    add_item("sign", "It is clearly written with instructions for how to use" +
        " the facilities here.\n");
        
    add_cmd_item("sign", "read", "Assembly members have three commands" +
        " available to them here. They are:\n" +
        "-'list agenda|results'. Used to list current matters up for" +
        " voting, or the recent vote results.\n" +
        "-'vote'. Used to vote on such a matter. Syntax for use is" +
        " 'vote <matter #> <Aye/Nay>'. Make sure you have thought this" +
        " through, because you cannot change your vote later.\n" +
        "-'propose'. Propose a new vote. Syntax for use is " +
        "'propose <vote type> <vote target, if any> <description, if" +
        " applicable>'."+
        " The following are the vote types available:\n" +
        "#1: Generic vote. Use when none of the below categories apply." +
        " This is the only vote where you need the description argument." +
        " Running time: one week.\n" +
        "#2: Vote to expel a member from the guild. Running time: one week.\n"+
        "#3: Vote to approve a promising student for membership, or revoke" +
        " a given approval. Running time: one week.\n" +
        "#4: Vote to make someone the Principal of their College. Note that" +
        " this will also promote them to the rank of Scholar." +
        " Running time: one week.\n" +
        "#5: Vote to remove a principal from office. Running time: two" +
        " weeks.\n" +
        "#6: Vote to spell ban a member. Running time: one day.\n" +
        "#7: Vote to confine a member to the Tower. Running time: one day.\n" +
        "#8: Vote to promote a member to the next rank. Running time: one" +
        " day.\n" +
        "#9: Vote to demote a member to the previous rank. Running time:" +
        " one day.\n" +
        "#10: Vote to lift all punishments from someone. Running time:" +
        " one day.\n\n" +
        "Some sample uses of this command: <propose 2 bishop>, or" +
        " <propose 1 disallow College members from joining the Krynn" +
        " thieves>.\n" +
        "Vote types 6-10 are not intended for normal use by the Assembly." +
        " It is normally a matter for the principal to administrate his/her" +
        " own College, these are here only as options if a principal is" +
        " absent. The running time of a vote only applies if the vote" +
        " doesn't get decided before that time. Also of note: the description"+
        " supplied when proposing a generic vote can't be very long. For all" +
        " votes it is customary to use the board to expound and outline" +
        " the reasons for the vote.\n");
        
    add_exit(TOWER + "tower_corr_2_1.c", "east", "@@check_sitting@@", 1);

    make_college_room();
    
    COUNCIL_OB->init_council();
}

int
do_vote(string str)
{
    int result;
    string *words;
    
    if (!str)
    {
        NF("Vote what?\n");
        return 0;
    }
    
    words = explode(str, " ");
    
    if (sizeof(words) == 2 && atoi(words[0]))
    {
        result = COUNCIL_OB->perform_vote(TP, atoi(words[0]) - 1, words[1]);
        
        if (!result)
        {
            write("You successfully voted on matter " + words[0] + ".\n");
            say(QCTNAME(TP) + " casts a vote.\n");
            return 1;
        }
        
        if (result == 1)
        {
            NF("No such matter up for voting.\n");
            return 0;
        }
        
        if (result == 2)
        {
            NF("You are not a member of the Assembly!\n");
            return 0;
        }
        
        if (result == 3)
        {
            NF("You have already voted on that matter!\n");
            return 0;
        }
        
        if (result == 4)
        {
            NF("You can only vote Aye or Nay.\n");
            return 0;
        }
    }
    else
    {
        NF("Vote what?\n");
        return 0;
    }
}

int
new_vote(string str)
{
    int result;
    string err_mess;
    string *words;
    
    if (!str)
    {
        NF("Propose what?\n");
        return 0;
    }
    
    words = explode(str, " ");
    
    if (sizeof(words) >= 2 && atoi(words[0]))
    {
        //Generic vote:
        if(atoi(words[0]) == 1)
        {
            result = COUNCIL_OB->start_vote(TP, 1, 
                implode(words - ({words[0]}), " "));
        }
        //Any other vote:
        else
        {
            if(SECURITY->exist_player(lower_case(words[1])))
            {
                result = COUNCIL_OB->start_vote(TP, atoi(words[0]), "", 
                    lower_case(words[1]));
            }
            else
            {
                NF("No player exists with the name of " + capitalize(words[1])
                     + "!\n");
                return 0;
            }
        }
    }
    else
    {
        NF("Invalid format for proposing new vote.\n");
        return 0;
    }
    
    if (!result)
    {
        write("You successfully started a vote.\n");
        say(QCTNAME(TP) + " starts a vote.\n");
        return 1;
    }
    
    switch(result)
    {
        case 1:
            err_mess = "You are not authorised to start votes!\n";
            break;
        case 2:
            err_mess = "Too long description. Max 50 characters.\n";
            break;
        case 3:
            err_mess = "That person is not a member!\n";
            break;
        case 4:
            err_mess = "That person is already a member!\n";
            break;
        case 5:
            err_mess = "That person is already a Principal!\n";
            break;
        case 6:
            err_mess = "That person is not a Principal!\n";
            break;
        case 7:
            err_mess = "That person is alredy under that punishment!\n";
            break;
        case 8:
            err_mess = "That person is already at the highest rank!\n";
            break;
        case 9:
            err_mess = "That person is already at the lowest rank!\n";
            break;
        case 10:
            err_mess = "That person has no current punishments!\n";
            break;
        case 11:
            err_mess = "Invalid vote type!\n";
            break;
        default:
            err_mess = "That member is but an apprentice, and can't possibly" +
                " be expected to lead a College!\n";
    }
    
    NF(err_mess);
    return 0;
}

            
int
do_list(string str)
{
    if (str == "agenda")
    {
        write(COUNCIL_OB->list_agenda());
        return 1; 
    }
    else if (str == "results")
    {
        if (file_size(COLLEGE_LOGS + "voteresults") != -1)
        {
            tail(COLLEGE_LOGS + "voteresults");
        }
        else
        {
            write("There are no votes on record.\n");
        }
        
        return 1;
    }
    else
    {
        NF("List what?\n");
        return 0;
    }
}

/*
 * Function name: do_sit
 * Description:   let a player sit on a chair
 * Arguments:     none
 * Returns:       0/1
 */
int
do_sit()
{
    if(TP->query_prop(COUNCIL_I_SITTING))
    {
        NF("You are already sitting in your chair!\n");
        return 0;
    }
    else 
    if (!COUNCIL_OB->query_council(TP->query_name()))
    {
        NF("You are not a Principal, these chairs are not for you!\n");
        return 0;
    }
    else
    {
        write("You sit down in the " + capitalize(TP->is_college_member()) + 
            " chair.\n");
        say(QCTNAME(TP) + " sits down in the " + 
            capitalize(TP->is_college_member()) + " chair.\n");
        TP->add_prop(COUNCIL_I_SITTING, 1);
        TP->set_no_show_composite(1);
        return 1;
    }
}    
 
/*
 * Function name: do_rise
 * Description:   let a player rise from a chair
 * Arguments:     none
 * Returns:       0/1
 */
int
do_rise()
{
    if(TP->query_prop(COUNCIL_I_SITTING))
    {
        write("You rise from your chair.\n");
        say(QCTNAME(TP) + " rises from " + TP->query_possessive() + 
            " chair.\n");
        TP->remove_prop(COUNCIL_I_SITTING);
        TP->set_no_show_composite(0);
        return 1;
    }
    else
    {
        NF("You're not sitting!\n");
        return 0;
    }
} 


public void
leave_inv(object ob, object to)
{
    if (TP->query_prop(COUNCIL_I_SITTING))
    {
        TP->remove_prop(COUNCIL_I_SITTING);
        TP->set_no_show_composite(0);
    }
    
    ::leave_inv(ob, to);
}


init()
{
    ::init();
    
    add_action("do_list", "list");
    add_action("do_vote", "vote");
    add_action("new_vote", "propose");
    add_action("do_sit", "sit");
    add_action("do_rise", "rise");
}    