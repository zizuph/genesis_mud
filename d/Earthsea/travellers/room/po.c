#pragma strict_types
#pragma save_binary

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>

inherit TRAVELLERS_STD_DIR + "room_base";
inherit "/d/Genesis/lib/post";

public string
relax()
{
    object tp = this_player();
    write("You sit down and relax to read your mail.\n");
    say(QCTNAME(tp) + " takes a seat and seems very relaxed.\n");
    tp->command("sigh quietly");
    tp->command("stretch");
    return "";
}

public void
create_traveller_room()
{
    add_prop(ROOM_S_MAP_FILE, "trav_map.txt");
    set_short("Council Members' Mail Room");
    set_long(
        "This is where the Traveller council members can come " +
        "to read and send their mail. There are a few bags of " +
        "mail on the floor. There is a nice little chair in the " +
        "corner that looks perfectly comfortable. A small " +
        "sign mounted upon the wall. You may exit south " +
        "through the door you entered.\n" + get_std_use());
    add_cmd_item("in chair", "sit", relax);
    add_item(({ "bags", "bag", "bags of mail" }),
        "They look full, but none are adressed to you.\n");
    add_item("sign", "Why not read it, eh tough guy?\n");
    add_item(({ "chair", "comfortable chair" }),
        "Mmmm, looks comfy, why don't you sit in it?\n");
    add_cmd_item("sign", "read", "The sign reads:\n" +
        "You have all of your regular post office commands " +
        "here. Use 'from', 'read', and 'mail'.\n");
    add_exit("councilrm", "south");
}

public void
init()
{
    ::init();
    post_init();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

public void
add_aliases(object reader)
{
    setuid();
    seteuid(getuid());
    reader->set_alias("council", 
        TRAVELLERS_MANAGER->query_council_members());
}

public void
mail_message(string new)
{
    write("There is" + new + " mail in the Traveller post office!\n\n");
}
