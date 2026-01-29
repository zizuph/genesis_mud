/*
 *  /d/Gondor/guilds/rangers/hq/office.c
 *
 *  The Office of Ranger Central Headquarters
 *
 *  Coded by Alto, 21 June 2001
 *    Original theme of Druedain hideout by Elessar
 *    Previous incarnations of office.c modified by Olorin & Gnadnar
 *    Updated by Tigerlily, 02 January 2004
 *    Updated by Gwyneth, 3 May 2004
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../titles.h"

object board;

public string long_desc();


public string
print_member_list()
{
    string text, *apprentice_list, *trusted_list;
    int i, j;

    text = "These are presently the members of the Ranger Apprentices:\n\n";

    trusted_list = MANAGER->query_company_members(APPROVED_APP_LEVEL);
    apprentice_list = MANAGER->query_company_members(APPRENTICE_LEVEL);

    i = -1;
    while (++i < sizeof(trusted_list))
    {
        /* Don't want a jr's name on the guildlist */
        if ((extract(trusted_list[i], -2) == "jr") &&
          !(TP->query_wiz_level()))
        {
            continue;
        }

        text += "- " + capitalize(trusted_list[i]) + ", of the Trusted "
            + "Ranger Apprentices\n";
    }

    j = -1;
    while (++j < sizeof(apprentice_list))
    {
        /* Don't want a jr's name on the guildlist */
        if ((extract(apprentice_list[j], -2) == "jr") &&
          !(TP->query_wiz_level()))
        {
            continue;
        }

        text += "- " + CAP(apprentice_list[j]) + ", of the Ranger "
            + "Apprentices\n"; 
    }

    return text + "\n";
}


static string 
exa_poster()
{
    write("On the poster you read:\n\n");
    write(print_member_list());
    return "";
}

static string
exa_rules()
{
    /* Make sure the council room is loaded. */
    (RANGERS_HQ_DIR + "ch_council.c")->teleledningsanka();

    find_object(RANGERS_HQ_DIR + "ch_council.c")->rule("list");

    return "";
}

string
long_desc()
{
    return "This is the office of Ranger Central Headquarters. "
        + "Rangers stationed in the occupied regions of Ithilien, as well as "
        + "those from the distant "
        + "North Kingdom come here to share news of the four corners "
        + "of the realms. The wooden floor creaks beneath your feet, "
        + "not as a result of poor carpentry, but rather because the hideout "
        + "stands partially in the trees and was built by clever hands "
        + "to shift in the wind. From the east you hear the "
        + "clacking of practice swords, while inviting firelight flickers "
        + "from the passage to the south. There is a poster on the wall, "
        + "and next to it a list of rules.\n";
}


void
create_gondor()
{
    set_short("the Office of Ranger Central Headquarters");
    set_long(&long_desc());

    add_exit(RANGERS_HQ_DIR + "ucorridor2", "north", 0, 1);
    add_exit(RANGERS_HQ_DIR + "cozy",       "south", 0, 1);
    add_exit(RANGERS_HQ_DIR + "ch_council", "west",  0, 1);
    add_exit(RANGERS_HQ_DIR + "ch_train",   "east",  0, 1);

    hideout_add_items();

    add_item(({"office", "room"}), &long_desc());
    add_item(({"firelight"}), "The firelight flickering from the south "
        + "passage is warm and inviting.\n");
    add_item(({"passage", "south passage", "passage to the south"}), "It "
        + "can be reached by walking south. The inviting firelight "
        + "there suggests it would be a worthwhile visit.\n");
    add_item(({"wall", "walls"}), "The walls, like most things in the "
        + "hideout, are constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions. One wall is also a little warmer "
        + "as a result of the iron torch stand mounted upon it.\n");

    add_item(({"rangers","members","poster"}), exa_poster);
    add_cmd_item(({"rangers","members","poster"}), "read", exa_poster);
    add_item(({"rules", "list"}), exa_rules);
    add_cmd_item(({"rules", "list"}), "read", exa_rules);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    clone_object(RANGERS_OBJ + "cdoor1")->move(TO);

    FIX_EUID;
    board = clone_object(RANGERS_OBJ + "hq_board");
    board->move(TO, 1);

}

