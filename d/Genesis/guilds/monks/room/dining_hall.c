/*
 * File:    dining_hall
 * Creator: Cirion, 1998.06.01
 * Purpose: Dining hall of the monks. They can purchase
 *          food and drink from the NPC, maiko.
 */
#pragma strict_types
#include "defs.h"
#include <ss_types.h>
#include <language.h>
#include <composite.h>
#include <std.h>

inherit ROOMBASE;

void populate ();

object table = 0;
object maiko = 0;

private string *
get_monk_listed_members ()
{
    string *members = m_indices (MANAGER->query_members ());
    string *newmem = ({ });
    int i;

    for (i = 0; i < sizeof (members); i++)
    {
        if (wildmatch ("*jr", members [i]))
            continue;

        if (strlen (SECURITY->query_wiz_dom (members [i])))
            continue;

        newmem += ({ capitalize (members [i]) });
    }

    return newmem;
}

string
table_desc_vbfc()
{
    string table_desc;

    if (present (table))
        table_desc = table->describe_table ();
    else
        table_desc = " Something is very wrong with this room!";

    table_desc += " Around the table are "
        + LANG_WNUM (sizeof (get_monk_listed_members ()))
        + " oak chairs.";

    return table_desc;
}

string
chairs_desc()
{
    string str;
    string *newmem = get_monk_listed_members ();

    str = "The chairs are all identical, and are arranged "
        + "evenly around the table. The chairs each have a name "
        + "written on the back in a delicate script. The names read: "
        + COMPOSITE_WORDS (newmem) + ".\n";

    return str;
}

void
create_room ()
{
    set_short("dining hall");
//    set_long (dining_long);
    set_long("This is a long, warm room with a very high ceiling." + VBFC_ME("table_desc_vbfc")
        + NPC_DESC + " Set within the eastern wall is a large stone fireplace, "
        + "above which is a circular, green-glass window. Through the "
        + "window pale rays of sunlight fall upon the table, bathing "
        + "everything in a friendly, warm radiance. A doorway in the "
        + "west wall leads out into a dark hall.\n");

    add_item(({"floor","tile","tiles","ground","stone"}),"The "
        + "square tiles that make up the floor are rough stone, "
        + "fitted together evently and with great care. The "
        + "stone, although rough, is worn down by the passage "
        + "of many feet over the years.\n"
        + VBFC_SAY("stoops down to examine the stone tiles "
        + "that make up the floor.\n"));

    add_item(({"glass","window","glass window","green-glass window"}),
        "The window is made from four panes of smooth green "
        + "glass separated by thin slats of old wood. The window "
        + "softens the sunlight that hits it, making it seem to "
        + "flow like water into the room and come to rest on the "
        + "redwood table and hard stone floor.\n"
        + VBFC_SAY("peers up at the window, and is bathed in "
        + "green sunlight.\n"));

    add_item(({"fireplace","fire","fire pit"}), "The fireplace is "
        + "very large, its mantle almost level with the bottom "
        + "of the window. Some cold ashes lie in the fireplace, "
        + "a remnant of the last cold winter.\n"
        + VBFC_SAY("stoops to examine the fireplace.\n"));
    add_item(({"ash","ashes"}), "They are a reminder of the cold "
        + "winters.\n"
        + VBFC_SAY("sifts through the ashes.\n"));
    add_item(({"mantle","mantlepiece"}), "The mantle atop the "
        + "fireplace is a long, heavy slab of dark marble. Aside "
        + "from some dust, nothing rests atop it.\n");
    add_item(({"chair","chairs"}), VBFC_ME ("chairs_desc"));
    add_item(({"sun","sunlight","light","radiance"}),
        "The sunlight is given a green tint by the green-glass "
        + "window as it falls on the table and floor. It bathes "
        + "everything in a warm, friendly radiance.\n");

    WIZINFO("In this room, people can buy food or drink from "
        + "the NPC maiko.\n");

    // where, command
    add_exit("hall_lower_south", "west");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("west", "You pass through the doorway into the "
        + "large dining hall.\n");

    populate ();
}

void
populate ()
{
    table = m_clone_here (MONK_OBJ + "dining_table");
    maiko = m_clone_here (MONK_NPC + "maiko", 0, "", " Standing next to the table "
        + "is an elderly wrinkled human, his wizened and serene face indicating years "
        + "of dedicated service to the order.");
}

string
evaluate_composite_npc()
{
    return ::evaluate_composite_npc();
}

