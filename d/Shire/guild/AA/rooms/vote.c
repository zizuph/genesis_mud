/*  The AA vote room
 *
 *
 *  Modification log:
 *
 *     2008.06.17, Toby: Allowed for wizards to enter north.
 */

#pragma save_binary
#pragma no_inherit
#pragma strict_types

#include <std.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include "../guild.h"

inherit SHIRE_ROOM;

#define AA_ACTIVITY_MAPPINGS  (AA_DIR+"obj/captain_activity_mappings")

#define BOARD_NAME  (AA_DIR+"boards/aa_board_vote")

static object Board;
static int alarm;

object
get_board()
{
    return Board;
}

/*
* Function name: reset_room
*/
void
reset_shire_room()
{
    object cleaner;
    FIXEUID;
    cleaner = clone_object("/std/monster");
    cleaner->set_name("guild_cleaner");
    cleaner->set_base_stat(SS_STR, 350);
    cleaner->set_base_stat(SS_DEX, 10);
    cleaner->set_base_stat(SS_CON, 150);
    cleaner->set_base_stat(SS_WIS, 10);
    cleaner->set_base_stat(SS_INT, 10);
    cleaner->set_base_stat(SS_DIS, 30);
    cleaner->set_pname("trolls");
    cleaner->set_race_name("troll");
    cleaner->set_adj(({"huge", "clumsy"}));
    cleaner->set_short("huge clumsy troll");
    cleaner->add_prop(LIVE_I_NEVERKNOWN, 1);
    cleaner->move(TO, 1);
    tell_room(TO, QCNAME(cleaner)+" arrives.\n");
    cleaner->command("get all");
    cleaner->command("sigh");
    cleaner->command("s");
    cleaner->command("e");
    cleaner->command("drop all");
    cleaner->command("w");
    cleaner->command("n");
    cleaner->command("say I have my orders... Keep this place tidy!");
    tell_room(TO, QCNAME(cleaner)+" leaves.\n");
    cleaner->remove_object();
}

/*
* Function name: block_exit
* Description:   Block out not councilmember, Lieutenant or Captain.
* Returns:       1 - Not alow to enter
*                0 - Alow enter
*/
int
block_exit()
{
    if (this_player()->query_wiz_level())
    {
        write("You are entering the council room, but as a "+
              "wizard you are allowed inside.\n");
        return 0;
    }
    if (AA_RANKS_OBJ->lieut_cap(TP->query_name())) return 0;  /* Lieutenant or Captain */
    //if (AA_COUNCIL_OBJ->is_council(TP->query_name())) return 0; /* Council member */
    //write("Only Captain and Lieutenants and Final Judges are allowed.\n");
    write("Only Captain and Lieutenants are allowed there!\n");
    return 1;
}

/*
* Function name: create_room
*/
void
create_shire_room()
{
    //set_short("The old Court room of Army of Angmar");
    //set_long("This is the court room of Army of Angmar. On the wall you "+
      //  "see the silver plaque, sign, the announcement list and the "+
        //"list of punishments.\n");

    set_short("The old Court room of Army of Angmar");

    set_long("This is the old court room, where rulings were "
        + "made,in the days when the army was run a council of elected "
        + "individuals. These days it is rather empty. The High "
        + "Command is located to the north of here, which "
        + "means it would be very wise to not make unneccessary "
        + "noise so as not to disturb them. East of here, the "
        + "so - called library of the army is located. Should "
        + "you, for some reason, feel the need to actually read "
        + "something of interest, venturing east might not be "
        + "such a bad idea. You vaguely feel the presence of the Emissary "
        +"of the Dark Lord in this area.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    //add_item(({"punishments","list of punishments"}),"All possible punishments "+
     //   "are listed here.\n");
   // add_item(({"list","announcement list"}), "Here you may find interesting "+
   //     "announcements regarding army-life.\n");
    //add_item("sign", "It is quite plain with some instructions on it.\n");
    add_item(({"plaque","silver plaque"}), "A very nice silver plaque indeed. "+
        "It has something engraved on it, but for the moment you can't "
        +"quite figure out what it says. Maybe someone will fix this later.\n");
    //add_cmd_item(({"punishments","list of punishments"}), "read", "@@read_pun_list");
    //add_cmd_item(({"list","announcement list"}), "read", "@@read_ann_list");
    //add_cmd_item("sign", "read", "@@read_sign");
    //add_cmd_item(({"plaque","silver plaque"}), "read", "@@read_plaque");

    add_exit(AA_DIR+"rooms/priv","south");
    add_exit(AA_DIR+"rooms/library","east");
    add_exit(AA_DIR+"rooms/council","north",block_exit);

    FIXEUID;
    Board = clone_object("/d/Shire/std/board");
    Board->set_board_name(BOARD_NAME);
    Board->set_remove_str("You are not able to delete any messages.\n");
    Board->set_num_notes(50);
    Board->add_prop(OBJ_I_INVIS, 100);

    Board->move(TO, 1);
}

/*
* Function name: read_pun_list
* Returns:       What you get when you 'read punishments'.
*/
string
read_pun_list()
{
    return "THE LIST OF PUNISHMENTS\n\n"+
        "      1. Ban from training for 2 weeks\n"+
        "      2. Lowering effectivity of specials for 10 days + above\n"+
        "      3. Disallowing specials for 1 week + above\n"+
        "      4. Beating on the head (losing skills) + above\n"+
        "      5. Extermination\n"+
        "      6. Rejecting from Army + beating on the head\n";
}

/*
* Function name: read_ann_list
* Returns:       What you get when you 'read list'.
*/
string
read_ann_list()
{
    string s = "BEGINNING OF ANNOUNCEMENTS...\n";
    s += AA_COUNCIL_OBJ->ann_list();
    s += "\n";
    s += AA_PUNISH_OBJ->ann_list();
    return s+"...END OF ANNOUNCEMENTS\n";
}

/*
* Function name: read_sign
* Returns:       What you get when you 'read sign'.
*/
string
read_sign()
{
    return "Available commands:\n"+
        "  To suggest punishment no. <num> for <name> use:\n"+
        "     'punish <name> <num>'\n"+
        "  To vote/change vote on punishment no. <num> for <name> use:\n"+
        "     'vote punish <name> <num> <yes/no>'\n"+
        "  To start election for council position no. <num> use:\n"+
        "     'start election for council <num>'\n"+
        "  To apply for council position no. <num> use:\n"+
        "     'apply for council <num>'\n"+
        "  To withdraw application for council position use:\n"+
        "     'withdraw application'\n"+
        "  To vote/change vote for <name> for council position no. <num> use:\n"+
        "     'vote council <num> <name>'\n"+
        "  To check your votes use:\n"+
        "     'check votes'\n"+
        "  To resign your council position use:\n" +
        "     'resign from council'\n" +
        "  Captain can promote <name> to the Recruitment Officer with:\n"+
        "     'promote Recruitment Officer <name>'\n"+
        "  and demote from Recruitment Officer with:\n"+
        "     'demote Recruitment Officer <name>'\n";
}

/*
* Function name: read_plaque
* Returns:       What you get when you 'read plaque'.
*/
string
read_plaque()
{
    return AA_COUNCIL_OBJ->list_council_ro();
}


// NEW
int
claim_captain(string str)
{
    int a = 0;
    //int b = 0;
    
    setuid();
	seteuid(getuid());

    
    if (str == "captaincy")
    {
        if (AA_COUNCIL_OBJ->no_captain() == 1)
        {
            a = 1;
        }

        /*if (AA_COUNCIL_OBJ->no_lieutenants() == 1)
        {
            b = 1;
        }*/

        /*if (AA_RANKS_OBJ->is_lieutenant(TP->query_name()) == 1 && a == 1)
        {
            // promote lt to captain.
            write("You claim the posision as the Captain of the Army "
                + "of Angmar!\n");

            a = 0;

            AA_COUNCIL_OBJ->promote_captain(TP->query_name());

            return 1;
        }*/
        
        if (present("captain_cooldwn_obj", this_player()))
        {
            write("You have lost your position as the Captain of "
            +"the Army of Angmar! Return abit later to reclaim the position if it's "
            +"still available!\n");
            
            return 1;      
        }
        
        if (AA_ACTIVITY_MAPPINGS->query_captain_rejoin_cooldown(TP->query_name()) == 1)
        {
            write("You have lost your position as the Captain of "
            +"the Army of Angmar! Return abit later to reclaim the position if it's "
            +"still available!\n");
            
            clone_object(AA_DIR 
            + "obj/captain_cooldwn_obj")->move(this_player(), 1);
            
            AA_ACTIVITY_MAPPINGS->clean_captain_rejoin_cooldown(TP->query_name());
            
            return 1;      
        }

        if (a == 1)
        {
            if(TP->query_guild_name_occ() == GUILD_NAME)
            {
				if (TP->query_stat(SS_OCCUP) < 100)
				{
					write("You feel you have not spent enough "
					+"time serving the Army to assume this "
					+"position! Try later when you are more experienced "
					+"as a member in the army.\n");
					
					return 1;
				}
                // promote regular member to captain.
                write("You claim the posision as the Captain of the Army "
                    + "of Angmar!\n");

                a = 0;
                //b = 0;

                AA_COUNCIL_OBJ->promote_captain(TP->query_name());

                return 1;
            }
            
            write("Only occupational members of the army can assume the "
            +"role of the captain!\n");
                    
            return 1;
            
        }


        /*if (AA_RANKS_OBJ->is_lieutenant(TP->query_name()) == 1)
        {
            write("The army already has a Captain!\n");

            return 1;
        }*/


        write("There is a captain currently commanding "
        +"the army!\n");

        return 1;
    }

    
    write("The correct syntax is 'claim captaincy'.\n");

    return 1;
}



/****************************************************************************
*
*   NOW COMES FUNCTIONS THAT HANDLE COMMANDS
*
****************************************************************************/
/*
* Function name: init
* Description:   adds commands to player in this room
*/
void
init()
{
    ::init();

    add_action(claim_captain, "claim");    /* resign from council position */

    //add_action("apply","apply");       /* apply for council position      */
    //add_action("check","check");       /* check your votes                */
    //add_action("council","start");     /* start election for a council    */
    //add_action("demote","demote");     /* remove Recruitment Officer      */
    //add_action("promote","promote");   /* add Recruitment Officer         */
    //add_action("punish","punish");     /* propose a punishment on someone */
    //add_action("vote","vote");         /* vote on punishment or council   */
    //add_action("withdraw","withdraw"); /* withdraw application            */
    //add_action("resign", "resign");    /* resign from council position */
}

/*int
apply(string str)
{
    int p;
    if ((!str) || (sscanf(str, "for council %d", p) != 1))
    {
        NF("Syntax is: 'apply for council <num>'\n");
        return 0;
    }
    AA_COUNCIL_OBJ->apply_council(p);
    return 1;
}

int
check(string str)
{
    string vvv;
    if (str != "votes")
    {
        NF("Check what?\n");
        return 0;
    }
    vvv = AA_COUNCIL_OBJ->check_votes(TP->query_name());
    vvv += AA_PUNISH_OBJ->check_votes(TP->query_name());
    if (vvv == "")
        write("You have not voted on anything.\n");
    else
        write("You have voted:\n"+vvv);
    return 1;
}

int
council(string str)
{
    int p;
    if ((!str) || (sscanf(str, "election for council %d", p) != 1))
    {
        NF("Syntax is: 'start election for council <num>'\n");
        return 0;
    }
    if ((p < 1) || (p > 5))
    {
        write("Proper syntax is: 'start election for council <num>'\n"+
            "where <num> is number of position in council (1-5) "+
            "you want to start election for.\n");
        return 1;
    }
    AA_COUNCIL_OBJ->start_election(p);
    return 1;
}

int
demote(string str)
{
    string name;
    if ((!str) || (sscanf(str, "Recruitment Officer %s", name) != 1))
    {
        NF("Syntax is: 'demote Recruitment Officer <name>'\n");
        return 0;
    }

    if (!AA_COUNCIL_OBJ->is_captain(this_player()->query_name()))
    {
        NF("You are not the Captain of the Army of Angmar.\n");
        return 0;
    }

    AA_COUNCIL_OBJ->demote_ro(name);
    return 1;
}

int
promote(string str)
{
    string name;
    if ((!str) || (sscanf(str, "Recruitment Officer %s", name) != 1))
    {
        NF("Syntax is: 'promote Recruitment Officer <name>'\n");
        return 0;
    }

    if (!AA_COUNCIL_OBJ->is_captain(this_player()->query_name()))
    {
        NF("You are not the Captain of the Army of Angmar.\n");
        return 0;
    }


    AA_COUNCIL_OBJ->promote_ro(name);
    return 1;
}

int
punish(string str)
{
    string name;
    int p;
    if ((!str) || (sscanf(str, "%s %d", name, p) != 2))
    {
        NF("Proper syntax is:\n"+
            "  'punish <name> <num>'\n"+
            "where <num> is a number of punishment.\n");
        return 0;
    }
    AA_PUNISH_OBJ->start_punish(name, p);
    return 1;
}

int
vote(string str)
{
    string name, v;
    int p;
    if (!str)
    {
        NF("Try vote something.\n");
        return 0;
    }
    if (sscanf(str, "council %d %s", p, name) == 2)
    {
        AA_COUNCIL_OBJ->vote_council(CAP(name), p);
        return 1;
    }
    if (sscanf(str, "punish %s %d %s", name, p, v) == 3)
    {
        AA_PUNISH_OBJ->vote_punish(CAP(name), p, v);
        return 1;
    }
    NF("Proper syntax is:\n"+
        "     'vote punish <name> <num> <yes/no>'\n"+
        "or:  'vote council <num> <name>'\n");
    return 0;
}

int
withdraw(string str)
{
    if (str != "application")
    {
        NF("Withdraw what?\n");
        return 0;
    }
    AA_COUNCIL_OBJ->withdraw_application();
    return 1;
}

int
resign(string str)
{
    if(str != "from council")
    {
        NF("Resign from what? Council?\n");
        return 0;
    }
    
    if (!TP->query_prop("angmar:confirmedresign")) 
    {
        write("Are you sure you want to resign from a council position?\n");
        write("State your intentions once more to confirm.\n");
        TP->add_prop("angmar:confirmedresign", 1);
        return 1;
    }
    
    AA_COUNCIL_OBJ->resign_as_council();
    return 1;
}*/

void
do_whispers()
{  
    if (AA_COUNCIL_OBJ->no_captain() == 1)
    {
        this_player()->catch_tell("\n\nYou hear a whisper from the "
        +"Emissary of the Dark Lord, saying: The Captain of the Army "
        +"of Angmar is gone! You may 'claim captaincy' here in this very room "
        +"if you want it, soldier!\n\n");    
    
        return;   
    }
        
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {  
        set_alarm(1.0, 0.0, &do_whispers());
    }
}