/*
 *  The post office of the Dunedain. Slightly modified version of the
 *  Rangers post office.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room.c";
inherit "/d/Gondor/common/lib/post";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

static string  exa_plaque();

public void
create_room() 
{
    set_short("the post office of the Dunedain");
    set_long(BSN("This small chamber is the post office of the "
	+ "Dunedain in Gondor. An arc is leading out of the "
	+ "chamber onto the hallway to the north. A poster and "
	+ "a plaque on the walls are there to inform about the "
	+ "features offered here."));

    add_item(({"plaque", }), exa_plaque());
    add_cmd_item(({"plaque", }), "read", exa_plaque());

    floor(1);
    walls(1);
    ceiling(1);

    add_exit(DUNEDAIN_DIR + "rooms/hallw_s3", "north", 0, 0);

    reset_room();
    create_post();
}

void
mail_message(string new)
{
    write("\n"+
      "There is"+new+" mail for you in the House of the Dunedain\n" +
      "  in Pelargir.\n\n");
}

string
exa_poster()
{
    return BSN(
      "If letters aren't quick enough to you, you may hire a pigeon "
      + "which will bring your message to other player very quickly. "
      + "The dunedain may use this service for a charge of only 12 "
      + "copper coins.");
}

string
exa_plaque()
{
    return
    "On the plaque, you can read the mail aliases defined here:\n"
    + "\tdunedainhouses      - all Lords and Ladies of the Houses,\n"
    + "\tguildmaster - the guildmaster.\n";
}

void
add_aliases(object rdr)
{
    string *dunedainhouses = DUNEDAIN_MASTER->query_house_lord();

    dunedainhouses -= ({ 0 });

    rdr->set_alias("guildmaster",
      GONDOR_MASTER->query_domain_aliases(DUNEDAIN_S_GUILD_NAME)); 
    if (sizeof(dunedainhouses))
	rdr->set_alias("dunedainhouses", dunedainhouses);
}
