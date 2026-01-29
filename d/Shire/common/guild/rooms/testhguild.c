/*
 *   /d/Shire/common/guild/hguild.c
 *   The guildroom of the Hin Warrior Guild.
 */
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "std/room";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"


int closed;
object meditate, board;
string name;

/* Prototypes */
void reset_room();

void
create_room()
{
   if (!present("board",this_object()))
   {
      board = clone_object("/std/board");
      name = HIN_DIR + "boards";
      if (file_size(name) != -2)
         mkdir(name);

      board->set_board_name(name + "/guildboard");
      board->set_num_notes(30);
      board->set_silent(1);
      board->set_show_lvl(0);
      board->set_remove_lvl(0);
      board->set_remove_str("You burn your fingers trying to remove a note");
      board->move(this_object());
   }

   set_short("A heap of rubble");
   set_long("A heap of rubble is all that is left of the Hsqwin Mountain, "+
   "and the guild that once resided in its gentle halls.  To the south, you "+
   "can pick your way through the debris to the East Road.\n");



   add_exit("/d/Shire/common/bree/bridge1","south",0,1);

   add_prop(ROOM_I_NO_ATTACK, 1);
   add_prop(ROOM_I_NO_STEAL, 1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

   reset_room();
}

void
reset_room()
{
   if (!present("party_hat"))
      clone_object(OPEN_DIR + "party/party_hat")->move(this_object());
}

