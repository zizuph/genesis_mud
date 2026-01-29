/*
 * /d/Gondor/guilds/rangers/ithilien/rockchamber
 *
 * Created by Elessar.
 *
 * The company post office of the Rangers of Ithilien.
 *
 * Modification log:
 * 19-Feb-1997, Olorin: Changed includes to inherits.
 * 12-Oct-1998, Gnadnar:   Add some items.
 * 21-Jul-2001, Alto:  Revise inheritance and make minor changes
 *                     to fit new rangers theme.
 * 24-March-2004: Updated by Tigerlily, add permanent torch,
 *                tweak descriptions
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../titles.h"
#include "exit.c"

public void      create_gondor();
public string    long_func();
public string    exa_window();
public void      reset_room();

static object    Door;


public string
print_member_list()
{
    string text, captain, deputy, sergeant, r_title;
    string *member_list;
    int i;

    text = "These are presently the members of the Rangers of Ithilien:\n\n";

    member_list = MANAGER->query_company_members(ITHILIEN_LEVEL);

    captain  = MANAGER->query_council_name(CAPTAIN_POSITION, "ithilien"); 
    deputy   = MANAGER->query_council_name(LIEUTENANT_POSITION, "ithilien");
    sergeant = MANAGER->query_council_name(SERGEANT_POSITION, "ithilien");

    if (captain)
        text += "- " + capitalize(captain) + ", the Captain of the Rangers of " 
             + "Ithilien\n";
    else
        text += "- There is no Captain of the Rangers of Ithilien\n"; 

    if (deputy)
        text += "- " + capitalize(deputy) + ", the Lieutenant of the "
            + "Rangers of Ithilien\n"; 
    else
        text += "- There is no Lieutenant of the Rangers of Ithilien\n"; 

    if(sergeant)
        text += "- " + capitalize(sergeant) + ", the Sergeant of the "
            + "Rangers of Ithilien\n"; 
    else
        text += "- There is no Sergeant of the Rangers of Ithilien"; 
    
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

            text += "- " + CAP(member_list[i]) + ", of the Rangers "
                + "of Ithilien\n"; 
        }
    }

    return text + "\n";
}


static string 
exa_poster()
{
    string name = TP->query_name();

    if (TP->query_company() == "ithilien" || 
      SECURITY->query_wiz_dom(name) == "Gondor" || 
      SECURITY->query_guild_is_master("rangers", name))
    {
        write("On the poster you read:\n\n");
        write(print_member_list());
        return "";
    }
    return "The poster is written in a code you cannot seem to decipher.\n";
}

static string
exa_rules()
{
    if (TP->query_company() == "ithilien" ||
      SECURITY->query_wiz_dom(TP->query_real_name()))
    {
        /* Make sure the council room is loaded. */
        (RANGERS_ITH_DIR+"ithilien_council.c")->teleledningsanka();

        find_object(RANGERS_ITH_DIR + "ithilien_council.c")->rule("list");
        return "";
    }
    return "The rules are written in a code you cannot seem to decipher.\n";
}

public void
create_gondor()
{
    set_short("the rock chamber");
    set_long(long_func);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit((RANGERS_ITH_DIR + "rackchamber"), "east", &check_ranger());
    add_exit((RANGERS_ITH_DIR + "window"), "west", &check_ranger());
    add_exit((RANGERS_ITH_DIR + "shop"), "north", &check_ranger());

    ith_add_items();

    add_item( ({ "waters", "water", "waterfall", "curtain", "veil",
        "window", }), exa_window);
    add_item( ({ "archway", "gate" }),
        "A forbidding archway opens west onto a veil of water.\n");
    add_item( ({ "rock-chamber", "cave", "chamber", }), "The cave is "
        + "wide and roughly hewn, with an uneven roof. It extends east, "
        + "and you see an opening west.\n");
    add_item( ({ "opening", "openings", }), "Three openings pierce the "
        + "rough walls of the cave: an archway to the west, a dark narrow "
        + "door to the south, and a low open doorway to the north.\n");
    add_item( ({ "low doorway", "doorway", }),
        "A low unframed opening leads north from the cave.\n");
    add_item("floor", "The floor is simply bare rough rock.\n");
    add_item( ({ "wall", "walls" }), "The chamber walls are dark grey "
        + "rock, rough and unadorned. They glisten faintly with moisture.\n");
    add_item( ({ "moisture" }), "The walls glisten with a thin layer of "
        + "moisture, as if mist from the waterfall sometimes drifts into "
        + "this chamber.\n");
    add_item( ({ "ceiling", "roof" }), "The uneven chamber roof does not "
        + "seem to have been shaped by hammer and chisel, but rather by "
        + "the forces of water and time.\n");
    add_item( ({ "stone", "rock" }), "The rough-surfaced rock is dark "
        + "grey, almost black. It shows no sign of having been smoothed "
        + "or polished.\n");

    add_item(({"rangers","members","poster"}), exa_poster);
    add_cmd_item(({"rangers","members","poster"}), "read", exa_poster);

    add_item(({ "list", "rules"}), exa_rules);
    add_cmd_item(({ "list", "rules" }), "read", exa_rules);

    reset_room();
}

/*
 * Function name: long_func
 * Description  : VBFC for room desc, dependant on time of day
 * Returns      : string -- the desc
 */
public string
long_func()
{
    string longtxt = "";

    longtxt = "This wide chamber is roughly shaped from dark grey "
        + "rock, and the uneven roof stoops low overhead. An iron "
        + "torch stand is fixed into the wall and holds a fresh torch "
        + "that is constantly replenished by ranger sentinels. "
        + "The cave extends inwards to the east, a low doorway opens "
        + "to the north, and a poster hangs to one side of a narrow "
        + "door leading south. Next to the poster is a list of rules. ";

    switch (tod())
    {
    case "night":
        longtxt += "The grey veil of a waterfall is dimly visible "
            + "through the archway to the west. ";
        break;
    case "early morning":
        longtxt += "To the west, a faint light shines through the "
            + "grey veil of the waterfall. Day is arising outside. ";
        break;
    case "morning":
    case "noon":
    case "afternoon":
        longtxt += "From the west archway, daylight enters the "
            + "chamber through the clear curtain of a waterfall. ";
        break;
    case "evening":
        longtxt += "To the west opens a rough-hewn gate of rock, "
            + "beyond which a thin veil of water shimmers. The level "
            + "shafts of the setting sun behind beats upon the veil, and "
            + "the red light breaks into many flickering beams of "
            + "ever-changing colour. ";
        break;
    }
    return (longtxt + "\n");
}


/*
 * Function name: exa_window
 * Description  : VBFC for window desc, dependant on time of day
 * Returns      : string -- the desc
 */
public string
exa_window()
{
    string  desc = "";
    switch (tod())
    {
    case "evening":
        desc = "The waterfall is to the west, and level rays from "
            + "the setting sun behind it beat upon it, red light being "
            + "broken into many flickering beams of ever-changing colour. "
            + "It is as if you are standing at the window of some "
            + "elven-tower, curtained with threaded jewels of silver "
            + "and gold, and ruby, sapphire and amethyst, all kindled "
            + "with an unconsuming fire.";
        break;
    case "night":
    case "early morning":
        desc = "The veil of water is hardly visible now in the "
            + "darkness of night.";
        break;
    case "morning":
    case "noon":
    case "afternoon":
        desc = "The veil of the waterfall is clearly visible "
            + "through the archway to the west, and the plash of "
            + "falling waters echoes gently off the rock walls. "
            + "Diffuse daylight enters through the veil.";
        break;
    }
    return (desc + "\n");
}

/*
 * Function name: reset_room
 * Description  : be sure it has door 
 */
public void
reset_room()
{
    if (!objectp(Door))
    {
        Door = clone_object(RANGERS_OBJ + "rdoor1");
        Door->move(TO);
    }
}
