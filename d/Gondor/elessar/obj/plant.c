inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

int chopping = 0;
string planter; /* who planted this tree */
string engraving; /* our message */

void create_object()
{
    if (!IS_CLONE)
        return;
    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("A tree can't be planted inside!");
        return;
    }
    else
    {
        this_object()->move(environment(this_player()));
        write("What would you like to engrave on the trunk?\n");
        input_to("engrave");
    }

    planter = this_player()->query_real_name();

    set_short("tree planted by " + capitalize(planter));
    set_pshort("trees planted by " + capitalize(planter));
    set_name(({"tree", "sapling"}));

    add_prop(OBJ_M_NO_GET, "You'd have to be stronger than Lars himself to pull a tree from the ground!\n");
    add_prop(OBJ_I_NO_INS,1);
    call_out("decay1", 1000);
}


void chop()
{
    if (chopping)
    {
        tell_room(environment(this_object()), "CHOP!!\n");
        call_out("chop", random(10) + 1);
    }
}


void decay3()
{
    tell_room(environment(this_object()),
              "The gnome hauls the tree away for one of his pet projects.\n");
    remove_object();
}


void decay2()
{
    chopping = 0;
    tell_room("As the sapling falls, the gnome shouts, \"TIMBER!!\"\n" +
              "(Remember, these guys are pretty small.)\n");
    call_out("decay3", 5);
}


void decay1()
{
    tell_room(environment(this_object()),
              "A gnome walks in with a large axe and starts chopping down the tree.\n");
    chopping = 1;
    call_out("chop", random(10) + 1);
    call_out("decay2", 60);
}


void engrave(string message)
{
    if (!message || message == "")
    {
        write("You have to engrave something on the tree.\n");
        remove_object();
        return;
    }
    set_long("A tree planted by " + capitalize(planter) + ".\n" +
             "It's just a sapling, but it looks very sturdy.\n" +
             "There's a message engraved on the trunk, saying:\n" +
             break_string(message, 70) + "\n");
}
