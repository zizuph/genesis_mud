inherit "/d/Calia/maniac/open/backpack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Rhovanion/defs.h"

string query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}
void init_recover(string arg)
{
  init_container_recover(arg);
  init_keep_recover(arg);
}

void set_keep(int keep = 1)
{
    if (keep) { ::set_keep(keep); }
    else this_object()->add_prop(OBJ_M_NO_SELL, "@@my_obj_m_no_sell@@");
}

int query_keep()
{
    return (query_prop_setting(OBJ_M_NO_SELL) != "@@my_obj_m_no_sell@@");
}

mixed my_obj_m_no_sell()
{
    if (sizeof(all_inventory()))
        return "You should empty the " + short() + " before selling it.\n";
    return 0;
}

public void
create_backpack()
{
    set_name("rucksack");
    set_pname("rucksacks");
    set_short("big rucksack");
    set_pshort("big rucksacks");
    set_adj(({"large","big"}));
    set_long("You can wear this rucksack on your back. It helps a lot "+
            "when you carry burdens on your adventures. More information "+
            "can be revealed by 'help rucksack'.\n");

    set_keep();

    add_prop(CONT_I_WEIGHT, 4500);      /* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000);      /* ml */
    remove_prop(CONT_I_RIGID);

    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */
    add_prop(CONT_I_REDUCE_VOLUME, 125);

    add_prop(OBJ_I_VALUE, 250);                 /* Worth 250 cc */
}

public int
a_filter(object ob)
{
    if ((ob->query_prop(OBJ_M_NO_SELL)) || (ob->query_prop(OBJ_M_NO_GIVE)) ||
        (ob->query_prop(OBJ_M_NO_DROP)) || (ob->query_prop(CONT_I_IN)) ||
        (ob->query_worn()) || (ob->query_wielded()) ||
        (!ob->query_prop(OBJ_I_VALUE)) || (ob->query_prop(LIVE_I_IS)) ||
        (ob->query_name() == query_name()))
        return 0;
    return 1;
}

/* Tell player about how to use the backpack */
public int
help(string arg)
{
    if (arg != "rucksack")
      return 0;

    write("How to use the "+short()+":\n" +
        "'packstore' puts all unworn and unwielded items " +
        "(excluding coins and other special items) into the "+short()+".  " +
        "'packget' will retrieve all such items from the "+short()+
        " into your main inventory.  'packhelp' gets this message.\n" +
        "Note that you can do this only when you carry the "+short()+".\n");
    return 1;
}

/* Store selected items in the backpack */
public int
packstore(string arg)
{
  object *conts, *moved;
  int x, y;

    NF("Packstore what?\n");
    if (strlen(arg))
        return 0;

    NF("First you must have it!\n");
    if(environment() != this_player())
        return 0;

  moved = ({ });

  conts = filter(all_inventory(TP), "a_filter", TO);

    for (x = 0; x < sizeof(conts); x++)
        if (!conts[x]->move(this_object()))
            moved += ({ conts[x] });

    if (!sizeof(moved))
    {
      NF("You didn't put anything in the "+short()+".\n");
      return 0;
    }
    write("You store "+COMPOSITE_DEAD(moved)+" in your "+short()+".\n");
    tell_room(ENV(TP), QCTNAME(TP)+" stores "+COMPOSITE_DEAD(moved)+
                           " in "+HIS(TP)+" "+short()+".\n", TP);
    return 1;
}

/* Retrieve selected items from the backpack */
public int
packget(string arg)
{
    object *conts, *moved;
    int x;

    NF("Packget what?\n");
    if (strlen(arg))
        return 0;

    NF("First you must have it!\n");
    if(environment() != this_player())
        return 0;

    moved = ({});

    conts = filter(all_inventory(), "a_filter", this_object());

    for (x = 0; x<sizeof(conts); x++)
       if (!conts[x]->move(this_player()))
            moved += ({ conts[x] });

    if (!sizeof(moved))
    {
      NF("You didn't retrieve anything from the "+short()+".\n");
      return 0;
    }
    write("You retrieve "+COMPOSITE_DEAD(moved)+" from your "+short()+".\n");
    tell_room(ENV(TP), QCTNAME(TP)+" retrieves "+COMPOSITE_DEAD(moved)+
            " from "+HIS(TP)+" "+short()+".\n", TP);
    return 1;
}

public int
packhold(string arg)
{
   NF("Use 'keep' instead of packhold."
     + " See 'help keep' for better instructions.\n");
    return 0;
}

public void
init()
{
   ::init();
   add_action("packhold", "packsell");
   add_action("packhold", "packhold");
   add_action("packstore", "packstore");
   add_action("packget", "packget");
   add_action("help", "help");
}

