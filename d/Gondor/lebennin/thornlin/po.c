/*
  * Thornlin post office, originally written for MT
  * by Elessar, Jan 18th, 1995.
  * updated to use the new /d/Gondor/common/lib/post.c
  * Olorin, 19-January-1995
  * Modified for Thornlin Jan. 1, 2001, by Auberon
  * (primarily changed descs., and MT-specific code
  * removed)
*/

/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above.
 */

#include "/d/Gondor/defs.h"
inherit (LIB_DIR + "post.c");

#include <macros.h>
#include <stdproperties.h>

#define CURRENT_WIZ "auberon"

void
create_room()
{
    set_short("The post office of Thornlin");
    set_long(
      "This is the post office of Thornlin.  The locals come by with "
      + "letters and mail to be sent to friends, relatives, and "
      + "people in other parts of the world, even outside of Gondor.  "
      + "There are regular mail-transports to Minas Tirith, to Bree, "
      + "Esgaroth and Pelargir, and even to lands across the Great Sea.  "
      + "There is a poster on one wall, and a note on another.  "
      + "East is the exit to the Militia office.\n");

    set_poster_name("big poster");
    create_post();

    add_exit(THORN_DIR + "guardhouse.c", "east", 0);

    add_item(({"note", "faded note", "words", "faded words"}), "The "
        + "words on the note have faded over time and are now illegible.\n");

}

void
mail_message(string new)
{
    write("\n"+
      "There is"+new+" mail for you in Thornlin.\n"+
      "  (Somewhere in Gondor)\n\n");
}

string
exa_note()
{
    return "\n"
    + "Here you may read and write your mail as in any other post office.\n"
    + "Check the mailreader for instructions.  \n"
    + "Pigeons may be hired for a nominal fee.  \n"
    + "The following aliases can be used here:\n"
    + "\tresponsible  - the wizard responsible for Thornlin.\n";
}

void
add_aliases(object rdr)
{
    rdr->set_alias("responsible",({CURRENT_WIZ}));
}

