/*
  * Minas Tirith post-office, updated to the latest version
  * by Elessar, Jan 18th, 1995.
 * updated to use the new /d/Gondor/common/lib/post.c
 * Olorin, 19-January-1995
 */

inherit "/d/Gondor/common/lib/post.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string  exa_note();
int     test_tour(object player);

void
create_room()
{
   set_short("The post office of Minas Tirith");
   set_long(BSN(
      "This is the post office of Minas Tirith. Here the citizens deliver "
    + "letters and mail to be sent to friends, relatives, and "
    + "people in other parts of the world, even outside of Gondor. "
    + "There are regular mail-transports to Rohan, to Bree, "
    + "Esgaroth and Pelargir, and even to lands across the Great Sea. "
    + "On one wall is a big poster with a drawing of a pigeon on it. "
    + "By the doorway is a note with instructions. East is "
    + "the exit to the street."));

   set_poster_name("big poster");
   create_post();

   add_item(({"note","instructions"}), exa_note());
   add_cmd_item(({"note","instructions"}), "read", exa_note());

   add_exit(MINAS_DIR + "e2crc1","east",0);

}

void
init()
{
    ::init();
    test_tour(TP);
}

void
mail_message(string new)
{
   write("\n"+
        "There is"+new+" mail for you in Minas Tirith.\n"+
        "  (Somewhere in Gondor)\n\n");
}

string
exa_note()
{
    return "\n"
       + "Here you may read and write your mail as in any other post office.\n"
       + "Check the mailreader for instructions.\n"
       + "The following aliases can be used here:\n"
       + "\tresponsible  - the wizard responsible for Minas Tirith\n";
}

void
add_aliases(object rdr)
{
  rdr->set_alias("responsible",({"elessar",}));
}

void
tour_done(object player)
{
    player->catch_msg("This is obviously the place that Hunthor, "
      + "Master of Advice told you to find. You guess you can "
      + "return to him now.\n");
}

int
test_tour(object player)
{
  object  note;
  if (present("Minas_Tirith_Tour_Note",player))
  {
      note = present("Minas_Tirith_Tour_Note",player);
      if (note->query_tour_no() != 0)
          return 0;
      note->set_tour_done();
      set_alarm(5.0, 0.0, "tour_done", player);
      return 1;
  }
}

