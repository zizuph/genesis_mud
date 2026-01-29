#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <macros.h>
#include <stdproperties.h>
#include <std.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"
#define BOARD_NAME  "/d/Rhovanion/common/boards/shield_club_council"
#define VOTE        (THIS_DIR+"vote")

void create_room()
{
  object board;

  set_short("Council room of Army of Angmar");
  set_long("This is the council room of Army of Angmar. Here councilmembers "+
           "together with Captain and Lieutenants can discuss things "+
           "about the army in privacy.\n");

  add_exit(THIS_DIR+"vote","south");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  seteuid(getuid());
  board = clone_object("/d/Rhovanion/lib/board");
  board->set_board_name(BOARD_NAME);
  board->set_remove_str("You are not able to delete any messages.\n");
  board->set_num_notes(20);
  board->set_reader(VBFC_ME("check"));
  board->set_writer(VBFC_ME("check"));
  board->set_remove(VBFC_ME("check"));
  board->move(this_object());
}

int check()
{
  /*** Council+Cap+Lieut+Rho wiz allowed ***/
  if(VOTE->rank_no(TP) > 4) return 0;  /* Lieutenant or Captain */
  if(member_array(TP->query_name(), VOTE->query_council()) != -1) return 0;
  if(SECURITY->query_wiz_dom(TP->query_name()) == "Rhovanion") return 0;
  return 1;
}

void enter_inv(object ob, object from)
{
  ::enter_inv(ob,from);
  if(!living(ob)) return;
  set_this_player(ob);
  if(check())
  {
    write("You are not allowed in Angmar's Army council room! Begone!!!\n");
    ob->move(from);
    return;
  }
  write("Welcome in Angmar's Army council room!\n"+
        "May your decisions always be to the benefit of the army.\n");
}

int query_prevent_snoop(){ return 1; }
