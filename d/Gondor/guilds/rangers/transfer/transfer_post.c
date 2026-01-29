/*
 * /d/Gondor/guilds/rangers/transfer_post.c
 *
 * The post office for use when
 * rangers are in the transfer room, waiting
 * to make their decision.
 *
 * Tigerlily -- December 7, 2003
 */
inherit "/d/Gondor/common/lib/post";

#include "/d/Gondor/defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../rangers.h"

string  exa_note();

void
create_room()
{
    set_short("Ranger Post Office.");
    set_long("A small chamber above the Room of " +
        "Decision has been cleared for the purpose of " +
        "a post office. From here ranger apprentice messengers " +
        "regularly drop off and pick up mail to deliver to the " +
        "far places of the realms. A small writing desk stands " +
        "against one wall where a note is attached. There is " +
        "a makeshift wooden ladder leading down.\n");

    add_item(({"cave", "small cave", "Room of Decision"}), 
        "The Room of Decision lies below, and this small " +
        "area is kept dry and quiet for the purpose of " +
        "writing and sending mail.\n");
    add_item(({"makeshift wooden ladder", "wooden ladder",
        "ladder", "makeshift ladder"}),
        "Crudely crafted yet sturdy, the ladder is made " +
        "from the green branches of a black walnut tree.\n");
    add_item(({"wall", "walls", "ceiling", "floor"}),
        "The walls, ceiling and floor are bare granite, " +
        "cool yet dry. A small writing desk stands " +
        "against the south wall.\n");
 
    add_item(({"note"}), exa_note());
    add_cmd_item(({"note","instructions"}), "read", exa_note());
    add_item(({"writing desk","small desk", "desk", 
        "small writing desk"}), "At this desk you can write your " +
        "mail.\n");

    add_exit(RANGERS_DIR + "transfer/transfer", "down", 0, 0);
}

void
mail_message(string new)
{
    write("\nThere is" + new + " mail for you in the message center " +
        "of the Room of Decision.\n\n\n");
}
 

string
exa_note()
{
    return (
        "Here you may read and write your mail as in any other post office.\n"
        + "Check the mailreader for instructions.\n"
        + "In addition the following aliases can be used here:\n"
        + "\tguildmaster - the guildmaster of the Rangers guild.\n"
        + "\tgondor - The wizards of Gondor.\n");
}

void
add_aliases(object rdr)
{

    string *wizards = ({ });
    wizards = GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME);
    if (sizeof(wizards))
        rdr->set_alias("guildmaster", wizards);


}

