inherit "/std/board";
#include "/d/Kalad/defs.h"

create_board()
{
   
   set_board_name("/d/Kalad/private/private_board_data");
   set_num_notes(40);
   set_anonymous(0);       /* no anonymous */
   set_silent(1);          /* silent */
   set_show_lvl(1);        /* show levels */
   set_remove_lvl(30);     /* Lord's or higher */
   set_remove_str("You must be a Lord or higher to remove notes.");
   set_err_log("/d/Kalad/log/errors");
   set_keep_discarded(1);  /* keep old notes */
}

varargs int
check_reader()
{
   
   if((SECURITY)->query_wiz_rank(TP->query_real_name()) >= WIZ_LORD)
      return 0;
   
   else
      if("secure/master"->query_wiz_dom(TP->query_real_name())!="Kalad")
      {
      if(P(this_interactive(), environment(this_object())))
         {
         write(BS("Only members of the Kalad domain may read the notes on "+
               "this board. Please use the board in the room adjacent to the "+
               "Tower of Domains to communicate to Kalad wizards via postings."+
               "\n"));
         say (QCTNAME(this_player()) + 
            " attempted to read a note but became befuddled.\n");
         }
      return 1;
   }
   else return 0;
   
}
