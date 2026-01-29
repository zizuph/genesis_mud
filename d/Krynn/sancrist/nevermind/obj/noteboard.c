 /* The board in the joinroom.c
 * Created by Dajala  22.03.96
 */

inherit "/std/board";

#include <std.h>
#include "../guild.h"

void
create_board()
{
   set_board_name("/d/Krynn/gnome/guild/log/board_data_common");
   set_long("    This is the common board for the inventor's " +
	    "guild.\n\n" +
	    "You may use it for discussion of guild-related issues.\n\n" +
	    "\nAn officially looking note pinned to the top catches your " +
	    "attention.\n");
   set_num_notes(25);
   set_remove_rank(WIZ_NORMAL);
   //set_err_log("/d/Krynn/gnome/guild/log/board_errors");
   set_remove_str("Sorry, only the guildmaster may remove the "
	+ "notes.\n");
   set_short("Inventor's Board");
   add_name("Inventor's Board");
   add_name("inventor's board");
   set_silent(0);

   add_cmd_item(({"note", "official note", "officially looking note"}),
   	({"examine", "exa"}), "It seems to be a note from the Head Tinker "
   	+ "of the inventor guild.\n");
   add_cmd_item(({"note", "official note", "officially looking note"}),
   	"read", "@@read_note");
}
/*
public mixed
long()
{
   write(::long());
   write("\nAn officially looking note pinned to the top catches your "
   	+ "attention.\n");
   return "";
}*/
  
string
read_note()
{
   seteuid(getuid());
   cat(HEAD_TIN_MESSAGE);
   return "";
} 
