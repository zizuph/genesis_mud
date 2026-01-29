inherit "/std/object";
inherit "/d/Gondor/rohan/entwash/obj/tree_extra";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define  ENT_I_BROKE_BRANCH		"_ent_i_broke_branch"

string  exa_branch();
string  tree = ONE_OF_LIST( ({"willow","alder","oak"}) );

void
create_object()
{
    set_name("entwash_live_tree");
    add_name(({"tree",tree+" tree",tree}));
    set_short("tall " + tree);
    set_pshort("tall " + tree +"s");
    set_long(BSN("This seems to be one of the only living trees in"
      + " these fens. It grows tall and strong, with a thick trunk"
      + " and many branches splayed out overhead to shade the area."
      + " Somehow the "+tree+" does not offer much comfort, and only makes"
      + " more poignant the lack of life in this area."));

    add_item(({"branches","branch"}), "@@exa_branch");

    add_item(({"trunk","trunks"}), BSN(
        "The trunk of this large " +tree+ " grows out of the wet and"
      + " muddy ground to rise high into the mist. It is covered with"
      + " moisture, and you notice that there are a few holes near to"
      + " its roots."));

    add_prop(OBJ_M_NO_GET, "Don't be absurd!\n");
    add_prop(OBJ_I_WEIGHT, 800000);
    add_prop(OBJ_I_VOLUME, 200000);

    FIX_EUID
}

int
climb_tree(string str)
{
    if (!str)
    {
        NFN("Climb what?");
        return 0;
    }

    if (str != "tree" && str != tree)
    {
        NFN("That does not seem like an option.");
        return 0;
    }

    write(BSN("The nearest branches are well out of reach."));
    return 1;
}

void
init()
{
    ::init();
    add_action(climb_tree, "climb");
    if (tree == "willow")
    {
        add_action(break_branch, "break");
    }
}

string
exa_branch()
{
    string  type;
    string  willow = "The branches of this "+tree+" splay out"
                   + " beautifully above and swoop down again to hang"
                   + " all about in long leafy swaths.";

    string  txt = " Toward the base of the tree you notice one small"
                + " branch which looks as if it could be easily broken"
                + " off.";

    if (!TP->query_prop(ENT_I_BROKE_BRANCH))
    {
        willow += txt;
    }

    switch(tree)
    {
        case "oak":
        case "alder":
            type = "The branches of this "+tree+" rise towards the sky"
                 + " above. The life they display draws a sharp"
                 + " contrast against the scenery of these fens.";
            break;
        case "willow":
            type = willow;
            break;
    }
    return BSN(type);
}
