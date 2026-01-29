/* This room is to be the herbshop for the PoT. */

/* Navarre July 3rd 2006, fixed typo, was experiements */
#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"

inherit TEMPLE + "std_base.c";
inherit "/d/Ansalon/guild/new_pot/lib/train_elements";

object gPriest;

void
reset_temple_room()
{
    setuid();
    seteuid(getuid());

    if (!objectp(gPriest))
    {
        gPriest = clone_object(GUILDNPC + "erdin");
        gPriest->arm_me();
        if (gPriest->move(TO))
            gPriest->move(TO, 1);
            
        set_trainer(gPriest);
    }
}

string
initiates()
{
    if (objectp(gPriest) && environment(gPriest) == TO)
        return "The initiates carry out the directions issued by " +
            gPriest->query_the_name(TP) + ".";
    else
        return "You see no initiates.";
}

string
activity()
{
    if (objectp(gPriest) && environment(gPriest) == TO)
        return "The room is a flurry of activity, as initiates are " +
            "hard at work with experiments under the supervision " +
            "of " + gPriest->query_the_name(TP) + ".";
    else
        return "The room is quiet as noone seems to be working here " +
            "at the moment.";
}

void
create_temple_room()
{
    set_short("In a workshop");
    set_long("This is a large workshop, filled with devices of " +
        "various kind. A number of workbenches are spread out around " +
        "the room, occupied with different kinds of experiments. " +
        "@@activity@@\n");

    add_item(({"devices"}), "Among the strange devices you notice one " +
        "thing almost like a coffin, but with a domed glass cover.\n");
    add_item(({"coffin", "glass", "domed glass", "glass cover"}), "You " +
        "look closer at the coffin-like thing, and beneath the cover " +
        "can see what must be dragon eggs bathing in some bubbling " +
        "liquid.\n");
    add_item(({"egg", "eggs", "dragon eggs"}), "The dragon eggs are " +
        "bathing in some bubbling liquid. Looking closely, you can see " +
        "miniscule cracks in the egg's surface, where the liquid seems " +
        "to be entering the egg.\n");
    add_item(({"liquid", "bubbling liquid"}), "The bubbling liquid is " +
        "dark, almost like ink. The surface froths as the liquid bubbles.\n");
    add_item(({"initiate", "initiates"}), "@@initiates@@\n");

    reset_temple_room();
    
    create_skill_raise();
    set_up_skills();

    add_exit( DUNGONE + "corr12.c", "south" );
}

void
init()
{
    ::init();
    
    init_skill_raise();
}
