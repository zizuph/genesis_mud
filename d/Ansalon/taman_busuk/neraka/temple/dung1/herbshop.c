/* This room is to be the herbshop for the PoT.
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"

inherit TEMPLE + "std_base.c";
inherit "/d/Ansalon/guild/new_pot/lib/train_herb";

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB   "/d/Krynn/common/herbs/"

object gGardener;

void
reset_temple_room()
{
    setuid();
    seteuid(getuid());

    if (!objectp(gGardener))
    {
        gGardener = clone_object(GUILDNPC + "alister");
        gGardener->arm_me();
        if (gGardener->move(TO))
            gGardener->move(TO, 1);

        set_trainer(gGardener);
    }
}

void
create_temple_room()
{
    set_short("In a strange cavern");
    set_long("You stand in a large cavern below the temple. This is " +
        "the Queen's Gardens, where strange and dangerous plants are " +
        "cultivated by magical means. Light spells along the high " +
        "ceiling of the cavern gives it the appearance of daylight " +
        "in places, while other spots are in darkness.\n");

    add_item(({"strange cavern","cavern"}), "It is oddly lit, and " +
        "seems to be full of plants.\n");
    add_item("ground", "The ground is soggy and marsh-like, with " +
        "small ponds at places.\n");
    add_item("ponds", "Small ponds are placed at intervals around " +
        "the cavern. They contain murky brown water.\n");
    add_item("water", "The water here is murky brown.\n");

    set_up_herbs(({KRHERB + "greenslime", KRHERB + "bkd_sedge",
        KRHERB + "skullcap", KRHERB + "mandrake"}), ({"ground"}));

    create_skill_raise();
    set_up_skills();

    reset_temple_room();
    add_exit( DUNGONE + "corr4.c", "southwest" );
}

void
init()
{
    ::init();

    init_skill_raise();
}    
