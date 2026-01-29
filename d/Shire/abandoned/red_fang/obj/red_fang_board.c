/* 
 * /d/Kalad/common/wild/pass/goblin/guild/red_fang_board.c
 * Purpose    : Fang's board
 * Located    : plan_room.c
 * Created By : Sarr  ??.??.??
 * Modified By: Sarr 17.Arp.97
 */ 

inherit "/std/board";
#include "/d/Kalad/defs.h"

void
create_board()
{
   set_short("dusty wooden board");
   set_board_name(KALAD(log/red_fang));
   set_num_notes(30);
}
