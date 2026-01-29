/*
 * /d/Gondor/guilds/rangers/north/post.c
 *
 * The post office
 *
 * Gwyneth, July 4, 2001
 *   modified by Alto: Exits and north hideout theme.
 */
inherit "/d/Gondor/common/lib/post";

#include "/d/Gondor/defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../rangers.h"
#include "check_exit.c"

string  exa_note();

void
create_room()
{
    set_short("the private Council post office");
    set_long("This is a private post office for the Council, who "
        + "by virtue of their positions, must spend many hours "
        + "responding to correspondence and reading mails. "
        + "With low ceilings and subdued lighting, " 
        + "it is a quiet spot away from the hoi polloi.\n");


    set_poster_name("big poster");
    add_prop(ROOM_M_NO_SCRY, 1);

    add_item(({"room"}), "You look around and see a number of interesting "
        + "things.\n");
    add_item(({"floor", "stone floor", "ground"}), "The floor here "
        + "is made from ancient slabs of stone covered by soft carpets. "
        + "Near the walls you can still make out the rich forest green "
        + "of the carpet as it was when first placed over the floor. "
        + "In most places, however, the colouration has long been worn away "
        + "by the passage of generations of booted feet.\n");
    add_item(({"carpet", "carpets"}), "The carpets covering the floor were "
        + "once dyed with a rich green stain. Only those places out of the "
        + "way of booted feet, however, have survived the ages unscathed.\n");
    add_item(({"slabs", "ancient slabs", "stone"}), "The floor is made up of "
        + "great slabs of stone, quarried long ago by dwarves in the service "
        + "of the kingdom of Arnor.\n");
    add_item(({"wall", "walls"}), "The walls, like most things in the "
        + "hideout, are constructed from stone. Unlike most rock, however, "
        + "the stone of the hideout feels almost warm to the touch. Deep "
        + "roots are not touched by the frost.\n");
    add_item(({"ceiling"}), "The ceilings of the hideout vault above you, "
        + "supported by graceful arches. The ceiling here is lower" 
        + "than the rest of the hideout, making it feel more cavelike.\n");
    add_item(({"arches", "graceful arches"}), "The crafting of the "
        + "ceiling must have required amazing labour and skill. The arches "
        + "supporting it are thin, sweeping and graceful, and from a distance "
        + "appear to be real trees growing inside.\n");
    add_item(({"hideout", "north hideout", "northern hideout"}), "It "
        + "is all around you. The compound is entirely below the ground, and "
        + "were you to view it from the outside, all you would see are the "
        + "remains of the tower above.\n");

    create_post();

    add_item(({"note"}), exa_note());
    add_cmd_item(({"note","instructions"}), "read", exa_note());
    add_item(({"writing desk","desk"}), "At this desk you can write your "
        + "mail.\n");
    add_item("counter", "A small counter, probably suitable for a hobbit.\n");
    add_item(({"mailbox","mailboxes"}), "Among the mailboxes you spot "
        + "one with your name on it.\n");
    add_item("hobbit", "The hobbit is taking care of all mail and pigeons.\n");
    add_item(({"cage","cages"}), "The cages contain several "
        + "carrier-pigeons.\n");
    add_item(({"pigeons","carrier-pigeons"}), "They seem well cared for.\n");

    add_exit(RANGERS_NOR_DIR + "north_council", "down", &check_ranger());
}

void
mail_message(string new)
{
    write("\nThere is" + new + " mail for you in the message center " +
        "of the North Hideout.\n\n\n");
}
 
string
exa_poster()
{
    return "Use the pigeon service of this post-office: If you need to get "
        + "an urgent message through to a friend elsewhere in the world, hire "
        + "a carrier pigeon to bring it to him or her. This service may be "
        + "bought for the very low price of twelve copper coins.\n";
}

string
exa_note()
{
    return (
        "Here you may read and write your mail as in any other post office.\n"
        + "Check the mailreader for instructions.\n"
        + "The following aliases can be used here:\n"
        + "\tguildmaster - the guildmaster of the Rangers guild.\n"
        + "\tofficers    - The Officers of the Rangers of the North.\n");
}

void
add_aliases(object rdr)
{
    string *council = ({ });
    string *wizards = ({ });
    string captain, lieutenant, sergeant;

    captain = MANAGER->query_council_name(CAPTAIN_POSITION, "north");
    lieutenant = MANAGER->query_council_name(LIEUTENANT_POSITION, "north");
    sergeant = MANAGER->query_council_name(SERGEANT_POSITION, "north");

    wizards = GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME);
    if (sizeof(wizards))
        rdr->set_alias("guildmaster", wizards);

    if (captain)
        council += ({ captain });
    if (lieutenant)
        council += ({ lieutenant });
    if (sergeant)
        council += ({ sergeant });

    council -= ({ 0 });
    if (sizeof(council))
        rdr->set_alias("officers", council);
}
