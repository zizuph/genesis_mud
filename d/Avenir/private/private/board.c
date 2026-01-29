// The domain's private board, by Cirion.
inherit "/std/board";

#include <std.h>
#include <macros.h>

/* These are the special wizards who can read this board. */
#define ALLOWED ({ "nikklaus", "mortricia", "triana", "tepisch", "mrpr" })

void
create_board() 
{
  if(file_name(this_object()) != MASTER_OB(this_object()))
    remove_object();

  setuid();
  seteuid(getuid(this_object()));

  set_short("The Private Board of Avenir");
  set_board_name(MASTER_OB(this_object()));
  set_num_notes(30);
  set_silent(0);
  set_show_lvl(1);
  set_remove_rank(WIZ_ARCH);
  set_remove_str("It is not permitted.\n");
}

/*
 * Function name: valid_reader
 * Description  : This function will return true if this_player() is allowed
 *                to read on the board. Note that players may always read
 *                their own notes, but this is not checked here.
 * Returns      : int 1/0 - true if the player may read.
 */
public nomask int
block_writer()
{
  string name = this_interactive()->query_real_name();
  
  if ((SECURITY->query_wiz_rank(name) >= WIZ_ARCH) ||
      (SECURITY->query_wiz_dom(name) == "Avenir") ||
      (member_array(name, ALLOWED) != -1))
    return 0;
  
  return 1;
}

public nomask int
block_reader()
{
  return block_writer();
}
