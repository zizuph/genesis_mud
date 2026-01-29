/*
 *  /d/Gondor/guilds/rangers/north/s_corridor.c
 *
 *  A hallway in the North Hideout.
 *
 *  Coded by Elessar
 *
 *  Modification log:
 *    19-Feb-1997, Olorin: Changed includes to inherits.
 *    15-Jul-2001, Alto: Modified to fit revised ranger theme.
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../titles.h"
#include "check_exit.c"

public string      long_desc();

string
long_desc()
{
    string txt;

    if (gTstand->query_torch_is_lit())
        txt = " from which a warm flickering light plays off the walls, "
            + "floor and ceiling. ";
    else
        txt = ". ";

    return "You are standing in a southern corridor of the underground "
        + "hideout. A wonderful tapestry hangs on the north wall. Set into "
        + "the south wall is an iron torch stand" + txt + "The corridor "
        + "leads west toward an equipment shop and opens to the east "
        + "through a graceful archway. There is a poster on the wall "
        + "here, and next to it a list of rules. A door leads south.\n";
}

private string
print_member_list()
{
    string text, captain, deputy, sergeant, r_title;
    string *member_list;
    int    i;

    text = "These are presently the members of the Rangers of the North:\n\n";

    member_list = MANAGER->query_company_members(NORTH_LEVEL);

    seteuid(getuid());
    captain  = MANAGER->query_council_name(CAPTAIN_POSITION, "north"); 
    deputy   = MANAGER->query_council_name(LIEUTENANT_POSITION, "north");
    sergeant = MANAGER->query_council_name(SERGEANT_POSITION, "north");

    if (captain)
        text += "- " + capitalize(captain) + ", the Captain of the Rangers " 
          + "of the North\n";
    else
        text += "- There is no Captain of the Rangers of the North\n"; 

    if (deputy)
        text += "- " + capitalize(deputy) + ", the Lieutenant of the "
          + "Rangers of the North\n"; 
    else if (!deputy)
        text += "- There is no Lieutenant of the Rangers of the North\n"; 

    if(sergeant)
        text += "- " + capitalize(sergeant) + ", the Sergeant of the "
          + "Rangers of the North\n"; 
    else
        text += "- There is no Sergeant of the Rangers of the North\n"; 
    
    i = -1;
    while (++i < sizeof(member_list))
    {
        if ( (member_list[i] != (captain)) && 
          (member_list[i] != (deputy)) &&
          (member_list[i] != (sergeant)) )
        {
            /* Don't want a jr's name on the guildlist */
            if ((extract(member_list[i], -2) == "jr") &&
              !(TP->query_wiz_level()))
            {
                continue;
            }

            text += "- " + capitalize(member_list[i]) + ", of the Rangers " +
                "of the North\n";
        }
    }

    return text + "\n";
}


private string 
exa_poster()
{
    if (!NORTH_MEMBER(TI) &&
      SECURITY->query_wiz_domain(TI->query_real_name()) != "Gondor")
        return "The poster is written in a code you cannot seem to "
            + "decipher.\n";

    write("On the poster you read:\n\n");
    write(print_member_list());
    return "";
}

private string
exa_rules()
{
    if (NORTH_MEMBER(TI) || TI->query_wiz_level())
    {
        /* Make sure the council room is loaded. */
        (RANGERS_NOR_DIR+"north_council.c")->teleledningsanka();

        find_object(RANGERS_NOR_DIR + "north_council.c")->rule("list");
        return "";
    }

    return "The rules are written in a code you cannot seem to decipher.\n";
}

public void
create_gondor()
{
    object door;

    set_short("a southern corridor");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "corridor", "northern corridor"}), &long_desc());
    add_item(({"tapestry", "north wall"}), "On the tapestry is a hero from "
        + "the First Age. You see Earendil the sea-farer, sailing his ship "
        + "Vingilot, standing at the prow of his ship. On his brow is a "
        + "shining jewel, one of the three Silmarils, and he gazes towards "
        + "the horizon.\n");
    add_item(({"walls"}), "There are two primary walls in the room, the "
        + "north wall and the south wall.\n");
    add_item(({"north wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The north wall is relatively unadorned, "
        + "save for the iron torch stand mounted upon it.\n");
    add_item(({"archway", "graceful archway"}), "The archway leads into a "
        + "great hall.\n");
    add_item(({"south wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The south wall is relatively unadorned, "
        + "save for the wooden door in the center of it.\n");

    add_item(({"rangers","members","poster"}), exa_poster);
    add_cmd_item(({"rangers","members","poster"}), "read", exa_poster);
    add_item(({ "list", "rules"}), exa_rules);
    add_cmd_item(({ "list", "rules" }), "read", exa_rules);

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "shop",       "west");
    add_exit(RANGERS_NOR_DIR + "great_hall", "east");

    clone_object(RANGERS_OBJ + "n_c_door1")->move(TO);

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}
