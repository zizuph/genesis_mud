#pragma strict_types
 
inherit "/std/room";
 
#include <stdproperties.h>
#include <macros.h>
 
#define CHAIR "/d/Genesis/start/human/obj/chair"

public void
create_room()
{
    set_short("Administrative Office");
    set_long("This is a comfortable yet simple office. A painting hangs " +
        "on the east wall; a banner is nailed over the western lintel. " +
        "A desk lurks in the corner.\n");
    add_item("painting", "The painting depicts one of the great battles " +
        "against what appear to be giant insects. A scholarly wizard " +
        "furiously scribbles on some parchment he holds; all around lie " +
        "dead bugs.\n");
    add_item("banner", "The banner fills the space between the lintel and " +
        "the roof, and is centered between the two walls. It has some words " +
        "written on it.\n");
    add_cmd_item("banner", "read", "Nolite es Bastardes carbarundum.\n");
    add_item("desk", "The desk is covered with dust; it does not seem to " +
        "get much use anymore.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 100);
    add_exit("/d/Genesis/start/human/town/post", "west");
}
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
        if (find_player("quetzl"))
            tell_object(find_player("quetzl"), ob->query_name() + " has entered the " +
                "office.\n");
        set_alarm(1.0, 0.0, "add_a_chair");
    }
}
 
public void
leave_inv(object ob, object to)
{
    object c, t;
    ::leave_inv(ob, to);
    if (interactive(ob))
    {
        if (c = ob->query_prop("_live_i_sit"))
        {
            t = this_player();
            set_this_player(ob);
            c->stand_up("");
            set_this_player(t);
        }
        set_alarm(1.0, 0.0, "remove_a_chair");
    }
}
 
public void
add_a_chair()
{
    reset_euid();
    tell_room(this_object(), "A giant trundles in with a chair in his arms " +
        "for the newest visitor, drops it, then toddles away.\n");
    clone_object(CHAIR)->move(this_object());
    return;
}
 
public int
empty_chair(object ob)
{
    if (!ob->id("chair"))
        return 0;
    if (ob->query_sitter())
        return 0;
    return 1;
}
 
public void
remove_a_chair()
{
    object *c;
    string word;
    reset_euid();
    c = ({});
    c = filter(all_inventory(this_object()), "empty_chair", this_object());
    if (!sizeof(c))
        return;
    tell_room(this_object(), "A giant lumbers into the room and picks up " +
        "the extra chair.\n");
    c[0]->remove_object();
}
