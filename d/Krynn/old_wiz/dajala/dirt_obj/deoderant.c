inherit "/std/object";
#include "/d/Kalad/defs.h"

int uses=3;

create_object()
{
    set_name("deoderant");
    add_name("can");
    set_adj("small");
    add_name("can of deoderant");
    set_short("small can of deoderant");
    set_long("@@my_long");

}


string
my_long()
{
    string empty_desc;

    if (uses < 1)
      empty_desc = "It feels empty.";
    else
      empty_desc = "It feels like it has some use left in it.";

    return BS(
      "It is a can of deoderant. " + empty_desc + "\n");
}


init()
{
    ::init();
    AA(do_spray,spray);
    AA(do_spray,use);
}


do_spray(str)
{
    NF(query_verb() + " what?\n");
    if (!str)
      return 0;

    if (query_verb() == "spray")
    {
      if(str != "myself" && str != "deoderant" && str != "deoderant on myself")
        return 0;
    }
    else
      if(str != "deoderant" && str != "deoderant on myself")
        return 0;

    NF(BS("The can makes a strange noise but nothing comes " +
      "out except a few drops.\n"));
    if (uses < 1)
      return 0;

    write(BS("You spray the deoderant on yourself and hope " +
      "you smell a little better.\n"));
    say(BS(QCTNAME(TP) +
      " tries to be descrete but you glimpse " +
      TP->query_objective() + " spraying deoderant in " +
      TP->query_possessive() + " armpits.\n"));
    uses = uses - 1;
    remove_dirt();
    return 1;
}


remove_dirt()
{
    int dirty_level;

    dirty_level = TP->query_prop(LIVE_I_DIRTY);
    if (!dirty_level || dirty_level < 1)
      return;

    dirty_level = (9 * dirty_level) / 10; /*remove 10% of dirt*/
    TP->add_prop(LIVE_I_DIRTY,dirty_level);
}
