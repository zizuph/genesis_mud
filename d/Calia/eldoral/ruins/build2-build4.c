#include "defs.h"

inherit STDROOM;

public void
reset_room()
{
    int i,
        num;

    ::reset_room();

    num = sizeof(filter(all_inventory(), &->id(RUBBLE_NAME)));    
    num -= 4;

    setuid();
    seteuid(getuid());

    while (num < 0)
    {
        num ++;
        if (!random(2))
            clone_object(OBJ + "large_rubble")->move(TO);
        else
            clone_object(OBJ + "small_rubble")->move(TO);
        tell_room(TO, "A piece of rubble falls from the " +
            "ceiling.\n");
    }
}

public void
create_room()
{
    set_short("a wide, arched hallway in " + CASTLE_NAME);
    set_long("You are in a wide, arched hallway, which runs from " +
        "the east to the west. This must, at one time, have been " +
        "a prominent room in the castle, as it's quite wide and " +
        "several hundred feet long. Stone pillars rise vertically " +
        "and arch inwards towards the top gracefully to meet at " +
        "the peak of the high, vaulted ceiling. Spaced along " +
        "the dusty, stone walls, a number of statues in various " +
        "stages of collapse stand guard before the tattered remains " +
        "of tapestries. Here and there you can see side exits leading " +
        "away from the main corridor, and you note that to " +
        "the west the ceiling comes to an end, perhaps rising " +
        "even higher, like in a tower.\n\n");

    add_item(({"ceiling", "roof"}),
        "High above you, the vaulted ceiling must have once been " +
        "an impressive sight. Now, however, the stone surface is " +
        "covered with cracks and holes where pieces of rubble have " +
        "fallen out.\n");
    add_item(({"walls"}),
        "The dusty stone walls lining the corridor were well " +
        "constructed, but not well enough to halt the march of " +
        "time, and now several places are buckling and sport a " +
        "number of cracks and gaps where stone has fallen out.\n");
    add_item(({"floor", "ground"}),
        "The floor of the hallway is quite simple, nothing more " +
        "than heavy flagstones carefully placed. However, the years " +
        "and impacts of rubble falling from the ceiling, have left " +
        "it full of cracks and holes where flagstones have shattered " +
        "completely.\n");
    add_item(({"cracks"}),
        "Large cracks spiderweb across almost every surface here.\n");
    add_item(({"hole", "holes"}),
        "Most every surface in the room has holes where stone has " +
        "fallen out, crumbled away, or been smashed to dust.\n");
    add_item(({"pillars"}),
        "The pillars are an interesting design, rising vertically " +
        "of fluted granite, the tops are curved to meet each other " +
        "at the peak of the ceiling.\n");
    add_item(({"statues", "statue"}),
        "The statues appear to all be men and women in a variety " +
        "of positions, but time has claimed any detail that might " +
        "have once yielded a clue as to their identity, and several " +
        "no longer even bear heads.\n");
    add_item(({"remains of tapestries", "remains"}),
        "Here and there along the walls, scraps of cloth or long " +
        "strings lie draped over rusted hooks, all that is left " +
        "of what were once tapestries.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "build2", "west");
    add_exit(RUIN + "build4_w", "east");

    reset_room();
}
