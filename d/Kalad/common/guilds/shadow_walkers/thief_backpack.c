/*   An large backpack for the hardware store in Calia

coder(s):   Maniac

history:    31.1.94     created                         Maniac
purpose:    hold items

to do:      none
bug:        none known
*/
/* Revision History:

Imported and slightly changed by Quetzl
(many thanks to Maniac for permission)  April, 1994

Yet little more changed  to general form by Milan, Jun, 1994
*/

#pragma strict_types

inherit "/d/Calia/maniac/open/backpack";
inherit "/lib/keep";


#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Kalad/defs.h"

#define MY_OBJ_M_NO_SELL "@@my_obj_m_no_sell@@"

private int worn,
temp_no_sell;

public void
create_backpack()
{
    set_name("backpack");
    add_name("pack");
    set_pname("backpacks");
    add_adj("black");
    add_adj("hemp");
    set_short("black hemp backpack");
    set_pshort("black hemp backpacks");
    set_long("It is large backpack made of tightly woven hemp. It "+
        "is dyed black for better concealment in the shadows. It "+
        "can probably hold a fair amount of your stuff in it. "+
        "Use 'keep' to keep it from being sold and 'packstore' or "+
        "'fillpack' and "+
        "'packget' or 'emptypack' to store and retrieve items from it.\n");
    
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 175000);
    add_prop(CONT_I_VOLUME, 9000);
    remove_prop(CONT_I_RIGID);
    
    add_prop(CONT_I_MAX_VOLUME, 175000);
    add_prop(CONT_I_REDUCE_VOLUME, 125);
    add_prop(OBJ_M_NO_DROP, VBFC_ME("can_it_be_dropped"));
    set_keep(); /* add the protection */
    add_prop(OBJ_I_VALUE, 500);
    temp_no_sell = worn = 0;
}

void
set_keep(int keep = 1)
{
    if (keep)
        {
        ::set_keep(keep);
    }
    else
        {
        this_object()->add_prop(OBJ_M_NO_SELL, MY_OBJ_M_NO_SELL);
    }
}

int
query_keep()
{
    return (query_prop_setting(OBJ_M_NO_SELL) != MY_OBJ_M_NO_SELL);
}

mixed
my_obj_m_no_sell()
{
    if (sizeof(all_inventory()))
        {
        return "You should empty the " + short() + " before selling it.\n";
    }
    return 0;
}

mixed
can_it_be_dropped()
{
    if(environment()->query_ghost()) return 0;
    
    if(worn) return "Remove the "+short()+" first!\n";
    
    return 0;
}

public void
enter_inv(object ob, object from)
{
    if (ob->query_prop(CONT_I_IN))
        {
        set_alarmv(1.0, 0.0, "fail_message", ({ ob, from }));
        ob->move(from);
        return;
    }
    ::enter_inv(ob, from);
}

public void
fail_message(object ob, object from)
{
    from->catch_msg("The "+short()+" rejects the "+ob->short()+".\n");
}

public int
wear(string str)
{
    if ((str != query_name()) && (str != short()))
        return 0;
    
    if (environment() != this_player())
        return 0;
    
    NF("You are already wearing it!\n");
    if (worn)
        return 0;
    
    NF("You already wear something on your back!\n");
    if (member_array("backpack", this_player()->query_sublocs()) != -1)
        return 0;
    
    TP->add_subloc("backpack", TO);
    
    write("You wear the "+short()+" on your back.\n");
    tell_room(environment(TP), QCTNAME(TP)+" wears the "+short()+" on " +
        HIS(TP) + " back.\n", TP);
    worn = 1;
    
    set_no_show_composite(1);
    return 1;
}

public int
remove(string str)
{
    if ((str != query_name()) && (str != short()))
        return 0;
    
    if (environment() != this_player())
        return 0;
    
    NF("But you aren't wearing the "+short()+"!\n");
    if (!worn)
        return 0;
    
    TP->remove_subloc("backpack");
    write("You remove the "+short()+".\n");
    tell_room(environment(TP), QCTNAME(TP)+" removes the "+short()+" from "+
        HIS(TP)+" back.\n", TP);
    worn = 0;
    set_no_show_composite(0);
    
    return 1;
}

public void
leave_env(object dest, object old)
{
    worn = 0;
    set_no_show_composite(0);
    ::leave_env(dest, old);
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != "backpack")
        return "";
    
    if (for_obj != on)
        return capitalize(on->query_pronoun()) + " is wearing a "+
    "a "+short()+" on "+HIS(on)+" back.\n";
    else
        return "You are wearing the "+short()+" on your back.\n";
}

/* Filter out certain objects when shifting stuff in or out of backpack */
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
packhelp(string arg)
{
    if (arg != "backpack")
        return 0;
    
    write("How to use the "+short()+":\n" +
        "'unkeep backpack' will make the "+short()+" sellable, " +
        "'keep backpack' will make in unsellable.  " +
        "'packstore' puts all unworn and unwielded items " +
        "(excluding coins and other special items) into the "+short()+".  " +
        "'packget' will retrieve all such items from the "+short()+
        " into your main inventory.  'packhelp' gets this message.\n" +
        "Note that you can do this only when you carry the "+short()+".\n");
    return 1;
}

/*
* Recovery stuff
*/
public string
query_recover()
{
    return MASTER+":#ck#"+temp_no_sell+"#";
}

public void
init_recover(string arg)
{
    string foobar;
    int tmp;
    
    sscanf(arg, "%s#ck#%d#%s", foobar, tmp, foobar);
    temp_no_sell = tmp;
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
    tell_room(environment(TP), QCTNAME(TP)+" stores "+COMPOSITE_DEAD(moved)+
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
    tell_room(environment(TP), QCTNAME(TP)+" retrieves "+COMPOSITE_DEAD(moved)+
        " from "+HIS(TP)+" "+short()+".\n", TP);
    return 1;
}

public void
init()
{
    ::init();
    add_action("packstore", "packstore");
    add_action("packstore", "fillpack");
    add_action("packget", "packget");
    add_action("packget", "emptypack");
    add_action("packhelp", "packhelp");
    add_action("wear", "wear");
    add_action("remove", "remove");
}
