/*
 *  The Rangers post-office, a modification of the Hobbiton post-office
 *
 *  Last mod: Updated for use with new mail reader, Olorin, 1-nov-1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/post";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"

#define PIGEON_VALUE 12

string  exa_note();

void
create_room()
{
    set_short("The mail service of the Rangers of Ithilien");
    set_long(BSN(
        "You are standing on a wet landing, a little light entering "
      + "from above. A flight of wet steps leads up towards open air, "
      + "and down into the darkness below. A note hangs on the rough "
      + "stone wall, and a few pigeons are sitting on perches. This "
      + "is the mail-service of the Ithilien Rangers."));

    add_item(({"note",}), exa_note());
    add_cmd_item(({"note",}), "read", exa_note());

    add_exit(RANGER_ITH_DIR+"landing","up",0);
    add_exit(RANGER_ITH_DIR+"passage1","down",0);

    add_item(({"pigeons","pigeon"}), BSN(
        "The pigeons are here to deliver the messages you write "+
        "to the recipients as soon as possible."));

    create_post();
}


void
mail_message(string new)
{
   write("\n"+
        "There is"+new+" mail for you in Henneth Annun.\n"+
        "\n");
}

string
exa_note()
{
  string desc;
  desc = "This is the post-office of the Rangers of Ithilien.\n"+
         "Here you may read and write your mail as in any other post office.\n"+
         "Available commands are:\n"+
          "\thire pigeon - Hire a carrier pigeon (Cost: "+PIGEON_VALUE+" cc).\n"
        + get_std_use()
        + "The following aliases can be used to send mail:\n"
        + "\tguildmasters - the guildmaster of the ranger guild and the liege.\n"
        + "\tcouncil     - the Council of Rangers,\n"
        + "\tofficers    - the Officers of the Ithilien Company.\n";
  return desc;
}

void
add_aliases(object rdr)
{
    string *council = ({ });
    string *wizards = ({ });
    
    wizards = GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME);
    if (sizeof(wizards))
	rdr->set_alias("guildmaster", wizards);

    council += COUNCIL->query_officers();
    council -= ({ 0 });
    rdr->set_alias("council", council);

    council = ({ COUNCIL->query_ithilien(), 
		 COUNCIL->query_ithilien_deputy(),
		 COUNCIL->query_ithilien_sergeant() });
    council -= ({ 0 });
    rdr->set_alias("officers", council);
}
