/* Ashlar, 4 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include "/d/Ansalon/guild/pot/guild.h"

inherit TEMPLE_BASE;
inherit "/d/Ansalon/guild/pot/lib/train_elements";

object priest;

void
reset_neraka_room()
{
    if (!objectp(priest))
    {
        priest = clone_npc(NNPC + "erdin");    	
        set_trainer(priest);
    }
}

string
initiates()
{
    if (objectp(priest))
        return "The initiates carry out the directions issued by " +
        priest->query_the_name(TP) + ".\n";
    else
        return "You see no initiates.\n";
}

string
activity()
{
    if (objectp(priest))
        return "The room is a flurry of activity, as initiates are hard at " +
        "work with experiments under the supervision of " +
        priest->query_the_name(TP) + ".";
    else
        return "The room is quiet as noone seems to be working here at the " +
        "moment.";
}

string
long_descr()
{
    return "This is a large workshop, filled with devices of various kind. " +
    "A number of workbenches are spread out around the room, occupied with " +
    "different kinds of experiments. " + activity() + "\n";
}

void
create_neraka_room()
{
    set_short("In a workshop");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"devices"}),
        "Among the strange devices you notice one thing almost like a " +
        "coffin, but with a domed glass cover.\n");
    add_item(({"coffin","glass","domed glass","glass cover"}),
        "You look closer at the coffin-like thing, and beneath the cover " +
        "can see what must be dragon eggs bathing in some bubbling " +
        "liquid.\n");
    add_item(({"egg","eggs","dragon eggs"}),
        "The dragon eggs are bathing in some bubbling liquid. Looking " +
        "closely, you can see miniscule cracks in the egg's surface, " +
        "where the liquid seems to be entering the egg.\n");
    add_item(({"liquid","bubbling liquid"}),
        "The bubbling liquid is dark, almost like ink. The surface froths " +
        "as the liquid bubbles.\n");
    add_item(({"initiate","initiates"}),
        "@@initiates");

    reset_room();

    create_skill_raise();
    set_up_skills();

    add_exit(NTEMPLE + "d4", "northwest");
    add_exit(NTEMPLE + "d11", "southwest");
}

public void
init()
{
    init_skill_raise();
    ::init();
}
