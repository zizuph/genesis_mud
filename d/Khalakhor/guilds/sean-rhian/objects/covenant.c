//
// Stone Tablet with the Covenant of Maighal
//
// used to bind a player to the covenant (join the guild)
//    Presbytair must do 'prepare to bind <seeker> to the covenant'
//    Seeker then may do 'bind myself to the Covenant of Maighal'
// also used to leave the guild; the penalty is DEATH
//    member may do      'break the covenant'
//
// History:
// Date         Coder           Action
// --------     --------------  ---------------------------------------
// 7/31/98      Zima            Created
//
inherit  "/std/object";
#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <ss_types.h>
#include <macros.h>
 
string author       = "";     // name of presbytair who autorized join
string prep_name    = "";     // name of new member about to join
 
//
// create_object
//
void create_object()
{
   set_name("tablet");
   add_name(({"covenant",SR_COVENANT}));
   add_adj(({"large","stone"}));
   set_short("large stone tablet");
   add_prop(OBJ_I_VOLUME,3000);
   add_prop(OBJ_I_WEIGHT,18000);
   add_prop(OBJ_I_VALUE,0);
   set_long(
  "                        -------------------------  \n"+
  "                       /                         \\                   \n"+
  "                     /      THE COVENANT OF        \\                 \n"+
  "                   /    MAIGHAL THE ARCHANGEL THE    \\               \n"+
  "                 /       HIGH SERVANT OF ARDAUGH       \\             \n"+
  "               /                                         \\           \n"+
  "             /   I. Ye shall worship Ardaugh the Most      \\         \n"+
  "           /        High; None other gods shall ye have      \\       \n"+
  "         /          but Him.                                   \\     \n"+
  "       /                                                         \\   \n"+
  "     /   II. Ye shall adore Maighal the Archanangel, The High      \\ \n"+
  "    |        Servant of Ardaugh, Maker of the Covenant.             | \n"+
  "    |                                                               | \n"+
  "    |   III. Ye shall venerate the Solsheyderi, the Servants of     | \n"+
  "    |        the Servant of Ardaugh.                                | \n"+
  "    |                                                               | \n"+
  "    |    IV. Ye shall heed the words of the Oracles of Ardaugh,     | \n"+
  "    |        for they reveal the Will of the Most High.             | \n"+
  "    |                                                               | \n"+
  "    |     V. Ye shall obey the edicts of the Seirsanach, for he     | \n"+
  "    |        is chosen as Chief Shepherd of the flocks of Ardaugh.  | \n"+
  "    |                                                               | \n"+
  "    |   VI. Ye shall give allegiance to thy Ard-Athair who is       | \n"+
  "    |       set over you as the Shepherd of thy flock.              | \n"+
  "    |                                                               | \n"+
  "    |  VII. Ye shall honor the Presbytairs of the Faithful who      | \n"+
  "    |       have been given great Wisdom.                           | \n"+
  "    |                                                               | \n"+
  "    | VIII. Ye shall maintain the Peace and Harmony of the          | \n"+
  "    |       Faithful, for they are thy brathairs and sistairs.      | \n"+
  "    |                                                               | \n"+
  "    |   IX. Ye shall ever proclaim The Faith to those in darkness,  | \n"+
  "    |       that they may receive the Light of the Most High.       | \n"+
  "    |                                                               | \n"+
  "    |    X. Ye shall use thy gifts to accomplish and live by        | \n"+
  "    |       the Covenant that thy make.                             | \n"+
  "    |                                                               | \n"+
  "    |      HE WHO WOULD BIND HIMSELF TO THE COVENANT OF MAIGHAL     | \n"+
  "    |          AND THEN BREAK THE COVENANT SHALL SURELY DIE!        | \n"+
  "    |_______________________________________________________________| \n"
  );
  add_cmd_item(({"tablet","covenant"}),"read",query_long());
}
#include "covenant.inc"
 
//
// help_cov
//
int help_cov(string cmd)
{
   int    ispresb    = ((TP->query_sr_level())>=SRLVL_PRESB);
   int    isaspirant = objectp(present(SHAM_PENDANT,TP));
   int    issaggart  = (TP->is_saggart());
   int    cmdok      = (stringp(cmd) &&
                        parse_command(lower_case(cmd), all_inventory(TP), 
                        "%s 'tablet' / 'covenant' / 'prepare' / 'bind' / "+
                        "'break' / 'leave' %s"));
 
   if (!((issaggart || isaspirant) && cmdok)) return 0;
   write("Help on using the Tablet of the Covenant:\n");
   if (ispresb)
      write("- prepare to bind <player> to the Covenant (Presbytair only)\n");
   if (ispresb || isaspirant)
      write("- 'bind myself to the Covenant of Maighal' when instructed\n");
   write("- 'break the Covenant' and ye shall surely die!\n");
   return 1;
}
 
//
// init
//
void init()
{
   ::init();
   add_action(&help_cov(),"help");
   add_action(&do_break(),"break");
   add_action(&prep(),    "prepare");
   add_action(&do_bind(), "bind");
}
