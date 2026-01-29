inherit "/std/board";

#include <std.h>

#include "../defs.h"

void create_board()
{
 set_board_name(TRICKSTERS+"board");
 set_num_notes(30);
 set_silent(0);
 set_remove_rank(WIZ_MORTAL);
 set_remove_str("Only wizard or Jamadar of Jamadars can do that.\n");
}

int allow_remove()
{
 if(SECURITY->query_wiz_rank(TP->query_real_name())>=WIZ_ARCH) return 1;
 if((SERVER)->query_leader(TP->query_name())) return 1;
 
 return 0;
}

int block_reader()
{
 if((SERVER)->query_member(TP->query_name())) return 0;
 if(SECURITY->query_wiz_rank(TP->query_real_name())>=WIZ_ARCH) return 0;
 if(SECURITY->query_wiz_dom(TP->query_real_name())=="Earthsea") return 0;

 return 1;
}

int block_writer()
{
 return block_reader();
}

