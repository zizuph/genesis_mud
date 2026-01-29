/*
 *  The Edoras Adventurer's Guild
 *
 */

inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

create_room()
{
  object board;

  set_short("Edoras Adventurer's Guild");
  set_long(BS(
    "This room is the local meeting place for adventurers. This is where "
    + "they leave messages about the places they have visited. Here they also "
    + "trade information on unknown territories, in the hope to be able to "
    + "explore them further.\n") + BS(
    "There is a door leading south into a training hall.\n"));

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit("/d/Gondor/workroom","east","@@wizcheck");
  add_exit("/d/Gondor/rohan/edoras/path2", "west", 0);
  add_exit("/d/Gondor/rohan/edoras/rooms/trainhall", "south", 0);

  board = clone_object("/std/board");
  board->set_board_name("/d/Gondor/common/guild/boards/guild_board");
  board->set_num_notes(25);         /* Number of notes         */
  board->set_anonymous(1);          /* You may write anonymous */
  board->set_silent(0);             /* Make noise when reading */
  board->set_show_lvl(0);           /* Full wizards or higher  */
  board->set_remove_lvl(0);         /* Full wizards or higher  */
  board->set_remove_str("You somehow failed.");
  board->set_use_gedit(0);          /* Don't use that marvellous editor */
  board->move(TO);
}

wizcheck()
{
  string pretitle;

  if (TP->query_wiz_level()==0)
  {
    write("A strong guard appears from the room to the east. \n" +
      "The strong guard stops you. \n" +
      "The guard says: Sorry, only wizards may enter that room. \n" +
      "Then the guard returns to the room to the east.\n");
    return 1;
  }
  pretitle = "/secure/master"->query_wiz_pretitle(TP);
  write("\nWelcome, " + pretitle + " " + CAP(TP->query_real_name()) +
    ", Wizard of " + TP->query_domain() + "!\n\n");
  return 0;
}
