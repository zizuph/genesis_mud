/* Cabal of Hiddukel Thief guild, 02/23/94, by Aridor */

#include "guild.h"

inherit ROOM_BASE

#include <ss_types.h>
#include <macros.h>

/*Prototype*/
void load_board();

object the_board;

void
create_thief_room()
{
   set_short("Quarters");
   set_long("You are in the sleeping quarters of the thieves. Mats line " +
	    "the walls here and bunks are set into the walls. People are " +
	    "sleeping here and there and you recognize some of your friends," +
	    " regaining energy for another hard day out in the world.\n");
   add_prop(ROOM_M_NO_ATTACK, "You dare not attack here!\n");
   add_prop(ROOM_M_NO_MAGIC_ATTACK, "You dare not attack here!\n");
   
   add_cmd_item("here", "start", "@@do_start");
   add_item(({"mats","bunks"}),"@@who_is_out_there@@");
   
   add_exit("shop", "east");
   add_exit("train", "south");
   add_exit("chapel", "west");
   add_exit("post", "north");
   add_exit("common", "up");
   add_exit("master", "hiddukel","@@master_only@@",1,"@@master_see@@");
   
   INSIDE;
   LIGHT;

   load_board();

}

/* This loads the main guild bulletin board */
void
load_board()
{

    the_board = clone_object(TOBJ + "tboard");
    the_board->move(TO);

/*   object bb;
   
   seteuid(getuid(TO));
   bb = clone_object("/std/board");
   bb->set_board_name(LOG + "board_data");
   bb->set_short("The Cabal of Hiddukel Burglar Board");
   bb->set_num_notes(25);
   bb->set_silent(0);
   bb->set_show_lvl(0);
   bb->set_no_report(1);
   bb->set_remove_lvl(35);
   bb->set_remove_str("Sorry, Only a Lord may remove the notes");
   bb->set_err_log(LOG + "board_error");
   bb->move(TO);
   bb->set_fuse();

   the_board = bb;*/
}


int
do_start()
{
   NF("Only members can start here.\n");
   if (!MEMBER(TP))
      return 0;
   TP->set_default_start_location(START_ROOM);
   write("You will start from here now any time you enter the game.\n");
   return 1;
}

int
lex_greater_than(string a, string b)
{
    if (a < b)
      return 1;
    if (a == b)
      return 0;
    return -1;
}

string
who_is_out_there()
{
    object *thieves = users();
    string *tlines = ({ });
    int i;
    mixed tmp;

    if (!MEMBER(TP) && !TP->query_wiz_level())
      return "A couple of bunks and mats are empty, but several " +
	"people are also taking a nap right now.\n";
    thieves -= ({ 0 });
    write("You scan the mats and bunks and come up with the list of " +
	  "burglars who must currently be following Hiddukel's paths:\n");
    for(i=0;i<sizeof(thieves);i++)
      if (MEMBER(thieves[i]) && CAN_SEE(TP,thieves[i]) &&
	  (TP->query_wiz_level() ||
	   ((TP->query_introduced() ? TP->query_introduced() : ([])) +
	    TP->query_remembered())[thieves[i]->query_real_name()] ||
	   TP == thieves[i]))
	tlines += ({ sprintf("%1d%4d%s %s",thieves[i]->query_thief_level(),
			     thieves[i]->query_stat(SS_LAYMAN),
			     thieves[i]->query_name(),
			     ((tmp = thieves[i]->query_thief_title()) ? "the " + tmp : "")) });
    if (sizeof(tlines) > 1)
      tlines = sort_array(tlines,"lex_greater_than");
    for(i=0;i<sizeof(tlines);i++)
      write(" " + tlines[i][5..] + "\n");
    if (sizeof(tlines) == 1)
      write("There is currently 1 burglar known to you roaming the lands.\n");
    else
      write("There are currently " + sizeof(tlines) + " burglars known to you roaming the " +
	    "lands.\n");
    return "";
}

int
master_only()
{
    if ((GUILDR + "master")->is_master(TP))
    {
      write("You enter the private chamber of the Master of the Cabal of Hiddukel.\n");
      return 0;
    }
    write("What?\n");
    return 1;
}

int
master_see()
{
    if ((GUILDR + "master")->is_master(TP))
      return 0;
    return 1;
}

object
query_board()
{
    return the_board;
}

