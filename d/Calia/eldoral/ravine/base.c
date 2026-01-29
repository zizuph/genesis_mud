#include "defs.h"

inherit "/std/room";

string main;

public int
player_knows_eldoral()
{
    if (TP->query_skill(SK_ELDORAL_CASTLE_NAME) &
        SK_ELDORAL_NAME_VALUE)
        return 1;
    return 0;
}

public string
eldoral_name()
{
    if (player_knows_eldoral())
        return "Eldoral Isle";
    return "the island";
}

public void
create_ravine()
{
    main = "You are in a thickly-forested ravine on what you believe " +
        "to be the north end of " + VBFC_ME("eldoral_name") + 
        ". The trees here seem " +
        "different from those on the rest of the island, somehow, more " +
        "ominous. Thick tangles of moss dangle from their knotted " +
        "branches, some of which are twisted at odd angles, " +
        "as if partially broken from supporting a heavy weight. " +
        "Beneath the trees, thorny underbrush covers most of the " +
        "ground, though what little ground you can see seems to be " +
        "littered with the decaying remains of broken branches " +
        "and bones of undefinable origins. ";
    set_short("a forested ravine in the north of " +
        VBFC_ME("eldoral_name"));

    add_cmd_item(({"tree", "trees"}), ({"climb"}), 
        "The trees look too old and brittle to try climbing.\n");
    add_cmd_item(({"cliff", "cliffside", "wall"}), ({"climb"}),
        "The cliff wall is far too steep to climb, even if " +
        "you could manage to reach it.\n");
    add_item(({"trees", "tree", "forest"}),
        "The forest here is comprised of trees which appear to " +
        "evergreens, but time and decay have left them in a state " +
        "from which it's hard to be sure.\n");
    add_item(({"moss"}),
        "Thick beards of moss dangle from the skeletal trees, " +
        "like flesh from a decaying corpse.\n");
    add_item(({"branch", "branches"}),
        "The branches on the trees are thin, twisted and knotted, " +
        "many of them partially broken and concealed beneath " +
        "thick beards of moss.\n");
    add_item(({"underbrush", "thorns"}),
        "Beneath the trees the ground is matted in a thick " +
        "tangle of thorny underbrush.\n");
    add_item(({"bones","bone"}),
        "Here and there beneath the underbrush you can see the " +
        "yellowish-white skeletal remains of unknown creatures " +
        "that have died in the forest.\n");
}

public void
create_wall(string where)
{
    if (!strlen(where))
        return;
    else
    {
        add_item(({"wall","cliff","ravine wall"}),
            "Off to the " + where + ", you can see the steep, " +
            "rocky wall of the ravine rising thirty or forty feet " +
            "into the air, up to the level of the rest of the " +
            "forest of the island.\n");
        main += "You see the ravine wall rising at least thirty " +
            "or forty feet above the forest floor, beyond the " +
            "trees to the " + where + ". ";
    }
    set_long(main + "\n\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

  /* Beast doesn't react to non-interactive objects */
    if (!interactive(ob))
        return;

  /* Notify the brain if 'from' is nothing, or if */
  /* create_ravine() is not defined in this file, */
  /* or if the beast isn't currently hunting. */
    if (!from || 
        function_exists("create_ravine", from) != RAVINE + "base" ||
        !BEAST_BRAIN->query_hunting())
    BEAST_BRAIN->notify_arrived(ob);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

  /* Don't make any checks for non-interactive objects */
    if (!interactive(ob))
        return;

  /* Notify the brain if 'from' is nothing, or if */
  /* create_ravine() is not defined in this file. */
    if (!to || 
        function_exists("create_ravine", to) != RAVINE + "base")
    BEAST_BRAIN->notify_left(ob);
}
