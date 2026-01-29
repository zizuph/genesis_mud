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
*/

#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

#define TEMP_M_NO_SELL "_temp_m_no_sell"

private int worn,
            packbeheld;

public void
create_container()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("large backpack");
    set_pshort("large backpacks");
    set_adj("large");
    set_long("This is a large backpack made in the city of " +
        "Esgaroth by the shopkeeper.  He discovered this method of " +
        "carrying equipment in Calia, and since he had such " +
        "a hard time figuring it out, he has made help available " +
        "by typing 'packhelp'.\n");

    add_prop(CONT_I_WEIGHT, 4500); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

    add_prop(OBJ_I_VALUE, 450); 		/* Worth 450 cc */
 
    packbeheld = worn = 0;
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
    from->catch_msg("The backpack rejects the " + ob->short() + ".\n");
}

public int
wear(string str)
{
    if ((str != "backpack") && (str != "large backpack"))
        return 0;

    if (environment() != this_player())
        return 0;

    notify_fail("You are already wearing it!\n");
    if (worn)
        return 0;
  
    notify_fail("You can't wear two backpacks at once!\n");
    if (member_array("backpack", this_player()->query_sublocs()) != -1)
        return 0;

    this_player()->add_subloc("backpack", this_object());

    write("You wear the large backpack on your back.\n");
    say(NAME + " wears the large backpack on " +
        this_player()->query_possessive() + " back.\n");
    add_prop(OBJ_M_NO_DROP, "Remove the backpack first!\n");
    worn = 1;

    set_no_show_composite(1);
    return 1;
}

public int
remove(string str)
{
    if (str != "backpack")
        return 0;

    if (environment() != this_player())
        return 0;

    notify_fail("But you aren't wearing the backpack!\n");
    if (!worn)
        return 0;

    this_player()->remove_subloc("backpack");
    write("You remove the large backpack.\n");
    say(NAME + " removes the large backpack.\n");
    remove_prop(OBJ_M_NO_DROP);
    worn = 0;

    set_no_show_composite(0);

    return 1;
}

public void
leave_env(object dest, object old)
{
    this_player()->remove_subloc("backpack");
    remove_prop(OBJ_M_NO_DROP);
    ::leave_env(dest, old);
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string mess;

    if (subloc != "backpack")
        return "";

    if (for_obj != on)
        return capitalize(on->query_pronoun()) + " is wearing a " +
            "large backpack on " + on->query_possessive() + " back.\n";
    else
        return "You are wearing a large backpack on your back.\n";
}

/* Filter out certain objects when shifting stuff in or out of backpack */
public int
a_filter(object ob)
{
    if ((ob->query_prop(OBJ_M_NO_SELL)) || (ob->query_prop(OBJ_M_NO_GIVE)) ||
        (ob->query_prop(OBJ_M_NO_DROP)) || (ob->query_prop(CONT_I_IN)) ||
        (ob->query_worn()) || (ob->query_wielded()) ||
        (!ob->query_prop(OBJ_I_VALUE)) || (ob->query_prop(LIVE_I_IS)) ||
        (ob->query_name() == "backpack"))
        return 0;
    return 1;
}

/* Enable player to sell the backpack */
public int
packsell(string arg)
{
    notify_fail("Packsell what?\n");
    if (strlen(arg))
        return 0;

    notify_fail("You weren't that fond of it to begin with!\n");
    if (!packbeheld)
        return 0;

    packbeheld = 0;
    write("You decide you might want to sell that backpack " +
        "after all.\n");

    add_prop(OBJ_M_NO_SELL, query_prop(TEMP_M_NO_SELL));
    return 1;
}

/* Tell player about how to use the backpack */ 
public int 
packhelp(string arg)
{
    notify_fail("Packhelp what?\n");
    if (strlen(arg))
        return 0;

    write("How to use the backpack:\n" +
        "'packsell' will make the backpack sellable, " +
        "'packhold' will make in unsellable.  " +
            "'packstore' puts all unworn and unwielded items " +
        "(excluding coins and other special items) into the backpack.  " +
        "'packget' will retrieve all such items from the " +
        "backpack into your main inventory.  'packhelp' gets this message.\n");
    return 1;
}

public string
query_recover()
{
    return MASTER;
}

/* Store selected items in the backpack */
public int
packstore(string arg)
{
  object *conts, *moved;
  int x, y;

    notify_fail("Packstore what?\n");
    if (strlen(arg))
        return 0;

  moved = ({ });

  conts = filter(all_inventory(this_player()), "a_filter", this_object());
  
    for (x = 0; x < sizeof(conts); x++)
        if (!conts[x]->move(this_object()))
            moved += ({ conts[x] });
  
    if (!sizeof(moved))
        write("You didn't put anything in the backpack.\n");
    else
    {
        write("You store " + COMPOSITE_DEAD(moved) +
            " in the large backpack.\n");
        say(NAME + " stores " + COMPOSITE_DEAD(moved) + " in the " +
            "large backpack.\n");
    }

    return 1;
}

/* Retrieve selected items from the backpack */
public int
packget(string arg)
{
    object *conts, *moved;
    int x;

    notify_fail("Packget what?\n");
    if (strlen(arg))
        return 0;

    moved = ({});

    conts = filter(all_inventory(), "a_filter", this_object());

    for (x = 0; x<sizeof(conts); x++)
       if (!conts[x]->move(this_player()))
            moved += ({ conts[x] });

    if (!sizeof(moved))
        write("You didn't retrieve anything from the backpack.\n");
    else
    {
        write("You retrieve " +COMPOSITE_DEAD(moved) +
            " from the large backpack.\n");
        say(NAME + " retrieves " + COMPOSITE_DEAD(moved) + 
            "from the large backpack.\n");
    }

    return 1;
}

public int
packhold(string arg)
{
    notify_fail("Packhold what?\n");
    if (strlen(arg))
        return 0;

    notify_fail("You have already decided not to sell the backpack.\n");
    if (packbeheld)
        return 0;

    packbeheld = 1;
    write("The backpack will not be sold now.\n");

    add_prop(TEMP_M_NO_SELL, query_prop(OBJ_M_NO_SELL));

    return 1;
}

public void
init()
{
   ::init();
   add_action("packsell", "packsell");
   add_action("packhold", "packhold");
   add_action("packstore", "packstore");
   add_action("packget", "packget");
   add_action("packhelp", "packhelp"); 
   add_action("wear", "wear");
   add_action("remove", "remove");
} 
