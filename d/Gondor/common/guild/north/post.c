/*
 *  The Rangers of the North post-office
 *  'stolen' from the Minas Morgul post-office ;-)
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/post";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"

#define PIGEON_VALUE 12

string  exa_note();

void
create_room()
{
    set_short("The post-office of the Rangers of the North");
    set_long(BSN("In this room is the post-office. Along the walls you "
      + "see mailboxes. In one corner there is a writing desk. Fastened "
      + "on the wall above the desk are a big poster and a note. "
      + "Behind a counter there are cages with carrier-pigeons. A small "
      + "hobbit is taking care of the pigeons."));

    set_poster_name("big poster");
    create_post();
    add_item(({"note",}), exa_note());
    add_cmd_item(({"note","instructions"}), "read", exa_note());
    add_item(({"writing desk","desk"}), "At this desk you can write your "+
        "mail.\n");
    add_item("counter", "A small counter, probably suitable for a hobbit.\n");
    add_item(({"mailbox","mailboxes"}), "Among the mailboxes you spot "+
        "one with your name on it.\n");
    add_item("hobbit", "The hobbit is taking care of all mail and pigeons.\n");
    add_item(({"cage","cages"}), "The cages contain several carrier-pigeons.\n");
    add_item(({"pigeons","carrier-pigeons"}), "They seem well cared for.\n");

    add_exit(RANGER_NORTH_DIR+"e_corridor","west", 0);

}

void
mail_message(string new)
{
   write("\n"+
       "There is"+new+" mail for you in the post office of the \n"+
       "Northern Headquarters.\n\n");
}

string
exa_poster()
{
   return BSN(
      "Use the brand new service of this post-office: if you need to "
    + "get an urgent message through to a friend elsewhere in the world, "
    + "hire a carrier pigeon to bring it to him. This service may be bought for "
    + "the very low price of "+PIGEON_VALUE+" copper coins.");
}

string
exa_note()
{
  return "Here you may read and write your mail as in any other post office.\n"+
    "Check the mailreader for instructions.\n"+
    "The following aliases can be used here:\n"+
    "\tguildmaster - the guildmaster of the Rangers guild, King Elessar,\n"+
    "\tcouncil     - The Council of Rangers,\n"+
    "\tofficers    - The Officers of the Rangers of the North.\n";
}

void
add_aliases(object rdr)
{
    string *wizards;
    string *council;

    wizards = GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME);
    if (sizeof(wizards))
      rdr->set_alias("guildmaster", council);

    council = COUNCIL->query_officers();
    council -= ({ 0 });
    rdr->set_alias("council", council);

    council = ({ COUNCIL->query_north(), 
		 COUNCIL->query_north_deputy(),
		 COUNCIL->query_north_sergeant() });
    council -= ({ 0 });
    rdr->set_alias("officers", council);
}
