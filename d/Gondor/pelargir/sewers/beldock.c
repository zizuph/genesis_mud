inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object *rats = allocate(5);

void
add_rats()
{
    int     i;

    for (i = 0; i < sizeof(rats); i++)
    {
        if (!objectp(rats[i]))
        {
            rats[i] = clone_object(NPC_DIR + "rat");
            rats[i]->set_random_move(20);
            rats[i]->set_restrain_path(PELAR_DIR + "sewers");
            rats[i]->move_living("down", TO);
            set_alarm(60.0 + 120.0 * rnd(), 0.0, add_rats);
            return;
        }
    }
}

void
reset_room()
{
    add_rats();
}

void
create_room()
{
    set_short("below the dock");
    set_long(BSN("Somehow you have managed to get yourself below one "
      + "of the docks in the harbour of Pelargir. Above you are the "
      + "aged boards of the dock, and out in the river you can see a "
      + "few ships. Balancing a few feet above the river on a "
      + "meshwork of planks gives you a fair view of the river and "
      + "docks without being seen. "
      + "There is an opening at the base of the dock."));
    add_item(({"boards"}), BSN("There are a few cracks in boards "
      + "above you, and where they are not caked with fish grime, "
      + "you can make out vague shadows of people walking about."));
    add_item("river", "The river Anduin flows past towards the sea.\n");
    add_item(({"meshwork","planks"}), BSN("These seemingly haphazard "
      + "planks are sturdy and wide enough to walk on. Perhaps "
      + "someone put them here for just that reason."));
    add_item("opening", BSN("Picking your way through the dock "
      + "supports you can see that the opening is big enough to enter, "
      + "though a strong smell of decay and excrements coming from it."));
    
    add_exit(PELAR_DIR+"docks/dock8","up",0);

    reset_room();
}

int
enter_sewers(string str)
{
    NFN("Enter what?");
    if (!strlen(str) || (str != "opening" && str != "hole"))
        return 0;

    set_dircmd(str);
    TP->move_living("into the opening", PELAR_DIR + "sewers/dock_ent");
    TP->init_command("$look");
    return 1;
}

void
init()
{
    ::init();

    add_action(enter_sewers, "enter");
}

