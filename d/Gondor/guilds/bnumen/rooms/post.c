/*
 *  The post office of the Black Numenoreans. Slightly modified version of the
 *  Rangers post office.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";
inherit "/d/Gondor/common/lib/post";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

static string  exa_plaque();

public void
create_room() 
{
    set_short("the post office of the Black Numenoreans");
    set_long("This small chamber is the post office of the "
	+ "Black Numenoreans in Gondor.  A poster and "
	+ "a plaque on the walls are there to inform about the "
	+ "features offered here.\n");

    add_item(({"plaque", }), exa_plaque());
    add_cmd_item(({"plaque", }), "read", exa_plaque());

    floor(1);
    walls(1);
    ceiling(1);

    add_exit(BNUMEN_DIR + "ship/ncabin_hall3", "starboard", 0);


    reset_room();
    create_post();
}

void
mail_message(string new)
{
    write("\n"+
      "There is"+new+" mail for you in the House of the Black Numenoreans\n" +
      "  in Pelargir.\n\n");
}

string
exa_poster()
{
    return BSN(
      "If letters aren't quick enough to you, you may hire a pigeon "
      + "which will bring your message to other player very quickly. "
      + "The Black Numenoreans may use this service for a charge of only 12 "
      + "copper coins.");
}

string
exa_plaque()
{
    return
    "On the plaque, you can read the mail aliases defined here:\n"
    + "\thouses      - all Lords and Ladies of the Houses,\n"
    + "\tguildmaster - the guildmaster.\n";
}

void
add_aliases(object rdr)
{
    string *houses = BNUMEN_MASTER->query_house_lord();

    houses -= ({ 0 });

    rdr->set_alias("guildmaster",
      GONDOR_MASTER->query_domain_aliases(BNUMEN_S_GUILD_NAME)); 
    if (sizeof(houses))
	rdr->set_alias("houses", houses);
}
