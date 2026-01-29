/*
 * /d/Gondor/guilds/rangers/ithilien/post.c
 *
 * The post office
 *
 * Gwyneth, July 4, 2001
 *   modified by Alto: Exits and ithilien hideout theme.
 */
inherit "/d/Gondor/common/lib/post";
#include "../rangers.h"

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "exit.c"

#define PIGEON_VALUE 12

string  exa_note();

void
create_room()
{
    set_short("The private Ithilien Council post office");
    set_long("You are standing in an enclosed chamber, a little light "
        + "entering from a small window above. A flight of wet steps leads "
        + "down. A note hangs on the rough stone wall, and a few pigeons "
        + "are sitting on perches. This is the private post office for "
        + "the Ithilien Council.\n");

    add_item(({"note",}), exa_note());
    add_cmd_item(({"note",}), "read", exa_note());

    add_exit(RANGERS_ITH_DIR + "ithilien_council", "down", &check_ranger());

    add_item(({"pigeons","pigeon"}), "The pigeons are here to deliver "
      + "the messages you write to the recipients as soon as possible.\n");
    add_item(({"floor", "stone floor", "ground"}), "The floor here "
        + "formed from the slow and ancient movement of water across "
        + "the bottom of the cave. In the middle of the floor runs a "
        + "shallow depression formed by the passage of many booted feet "
        + "over long years.\n");
    add_item(({"depression", "shallow depression"}), "The floor seems "
        + "a bit depressed in the areas where most traffic moves through. "
        + "It is a testament to the age of this place, and the many long "
        + "years the folk of Gondor have kept vigil here.\n");
    add_item(({"wall", "walls", "north wall", "south wall", "west wall",
        "east wall"}), "The walls, like the floors, are "
        + "smooth and cool. Most of the walls in Henneth Annun are bare, "
        + "although here and there you notice an iron torch stand mounted "
        + "upon the wall of the cave.\n");
    add_item(({"ceiling"}), "The ceiling of the cave, much like the floor "
        + "and walls, is smooth and cool.\n");
    add_item(({"hideout", "henneth annun"}), "It is all around you. Because "
        + "it entirely housed within a network of caves, it cannot be "
        + "seen from the outside.\n");
    add_prop(ROOM_M_NO_SCRY, 1);

    create_post();
}

void
mail_message(string new)
{
    write("\nThere is" + new + " mail for you in the message center " +
        "of the Ithilien Hideout.\n\n\n");
}


string
exa_note()
{
    string desc;
    desc = "This is the post-office of the Rangers of Ithilien.\n"
        + "Here you may read and write your mail as in any other post "
        + "office.\nAvailable commands are:\n\thire pigeon - Hire a "
        + "carrier pigeon (Cost: " + PIGEON_VALUE + " cc).\n" + get_std_use()
        + "The following aliases can be used to send mail:\n"
        + "\tguildmasters - the guildmaster of the ranger guild.\n"
        + "\tofficers    - the Officers of the Ithilien Company.\n";
    return desc;
}

void
add_aliases(object rdr)
{
    string *council = ({ });
    string *wizards = ({ });
    string captain, lieutenant, sergeant;

    captain = MANAGER->query_council_name(CAPTAIN_POSITION, "ithilien");
    lieutenant = MANAGER->query_council_name(LIEUTENANT_POSITION, "ithilien");
    sergeant = MANAGER->query_council_name(SERGEANT_POSITION, "ithilien");

    wizards = GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME);
    if (sizeof(wizards))
        rdr->set_alias("guildmasters", wizards);

    if (strlen(captain))
        council += ({ captain });
    if (strlen(lieutenant))
        council += ({ lieutenant });
    if (strlen(sergeant))
        council += ({ sergeant });

    council -= ({ 0 });
    rdr->set_alias("officers", council);
}
