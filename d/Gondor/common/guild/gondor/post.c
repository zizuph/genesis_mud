/*
 *  The Rangers post-office, a modification of the Hobbiton post-office
 *  Updated to use /d/Gondor/common/lib/post.c
 *  - Olorin, January 1995
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/post";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"

#define PIGEON_VALUE 24

string  exa_note();

void
create_room()
{
   set_short("The post office of the Rangers' Guild");
   set_long(BSN(
      "This is the post office of the Rangers' Guild. Some Rangers work "
    + "here to sort out mail to and from the Rangers, and you notice "
    + "carrier-pigeons being sent off in all directions with today's "
    + "mail. On one wall hangs a note, and a poster on the other "
    + "contains instructions. A doorway leads east to the corridor."));

    add_prop(ROOM_M_NO_STEAL, no_theft);

   add_item(({"note",}), exa_note());
   add_cmd_item(({"note",}), "read", exa_note());

   add_item(({"pigeons","pigeon", "carrier-pigeons", }), BSN(
    "The pigeons are here to deliver the messages you write "+
    "to the recipients as soon as possible."));

   set_poster_name("big poster");

   add_exit(RANGER_GON_DIR + "wcorr", "east", 0);

   create_post();
}

void
mail_message(string new)
{
   write("\n"+
       "There is"+new+" mail for you in the post office in the Rangers Guild.\n"+
        "  (Somewhere in central Gondor)\n\n");
}

string
exa_poster()
{
   return BSN(
      "Use the brand new service of this post-office: if you need to "
    + "get an urgent message through to a friend elsewhere in the world, "
    + "hire a carrier pigeon to bring it to him. This service may be bought "
    + "for the very low price of "+PIGEON_VALUE+" copper coins. ");
}

string
exa_note()
{
  return "Here you may read and write your mail as in any other post office.\n"+
    "Check the mailreader for instructions.\n"+
    "The following aliases can be used here:\n"+
    "\tguildmaster - the guildmaster of the Rangers guild and the liege,\n"+
    "\tcouncil     - The Council of Rangers,\n"+
    "\tofficers    - The three Officers of the Gondor Company.\n";
}

void
add_aliases(object rdr)
{
    string *council = ({ });
    rdr->set_alias("guildmaster",
		   GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME));

    council += COUNCIL->query_officers();
    council -= ({ 0 });
    rdr->set_alias("council", council);

    council = ({ COUNCIL->query_gondor(), 
		 COUNCIL->query_gondor_deputy(),
		 COUNCIL->query_gondor_sergeant() });
    council -= ({ 0 });
    rdr->set_alias("officers", council);
}
