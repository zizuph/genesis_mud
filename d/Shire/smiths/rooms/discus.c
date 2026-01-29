/*
     The discussion room in the smiths guild
     smiths board is placed here
*/

#pragma save_binary;

inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"



void
create_room() {
   object board;

   set_short("Smiths guild discussion room");
   set_long("This is the room where members of the Smiths Guild gather to"+
      " discuss and share news. The room is placed in the middle of the"+
      " large building used by the guild. In the middle of the room is a"+
       " board where people can place notes about various topics."+
      " You can hear hammering sounds from the east. The smell of fresh"+ 
      " food that used to flow into the room from the Broken Sword to the"+
      " north is gone now, after the Broken Sword Inn was closed.\n");
   add_exit(SMITHSDIR_ROOMS+"rest_r","northwest","@@membership@@");

  add_exit(SMITHSDIR_ROOMS+"forge_entr","east",0);
//   add_exit(SMITHSDIR_ROOMS+"forge_entr","east","@@block_me@@");
   add_exit(SMITHSDIR_ROOMS+"leather","south",0);
   add_exit(SMITHSDIR_ROOMS+"master_r","west",0);
   add_exit(SMITHSDIR_ROOMS+"entrance","northeast",0);

/*
    if (!objectp( board) )
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name( "/d/Shire/smiths/board2/");
        board->set_silent(0);
        board->set_show_lvl(0);
        board->set_remove_str("Sorry, you can't do that\n");
        board->move(this_object());
    }
*/

// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

   add_prop(ROOM_I_INSIDE,1);
}

int
membership()
{
    if (TP->query_wiz_level())
        return 0;

    if (IS_MEMBER(TP))
        return 0;

    TP->catch_tell("Only Smiths may go there.\n");
    return 1;
}


int
block_me()
{
    if (this_player()->query_wiz_level()) return 0;

        write("\n\nThe forge is currently closed for repairs.\n"+
        "It should reopen in the next day or two.\n\n"+
        "Berim\n\n");
    return 1;
}
