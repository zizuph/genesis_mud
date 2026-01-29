#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";
inherit "/d/Genesis/lib/post";

#include <std.h>

void create_vamp_room()
{
    set_short("Bat dispatch room");
    set_long("   The walls are lined with cages, most of which " +
        "contain bats.  The dull glow of reflected sunlight shows " +
        "through the darkness onto the floor near the far end of the " +
        "room, where an opening in the ceiling apparently leads to " +
        "to the outside.  This is apparently a place for dispatching " +
        "important messages to the outside world using the bats as " +
        "carriers.\n");

    add_item(({ "cage", "cages" }), "Large metal cages take up the " +
        "wall space.  Several dozen large bats are held within them.\n");

    add_item(({ "bat", "bats", "large bats" }), "Several dozen large " +
        "bats are held within the cages which line the walls.  It " +
        "would seem that they have somehow been trained to deliver " +
        "messages.\n");

    add_item(({ "glow", "dull glow", "sunlight", "opening", "outside" }),
        "A few meager rays of light make their way down a narrow tunnel " +
        "through the ceiling.\n");

    add_cmd_item(({ "tunnel", "opening", "hole" }), "enter", "You can't " +
        "possibly squeeze in.\n");

    add_prop(ROOM_I_LIGHT, -1);

    add_exit("hall3", "down");
}

int
member_filter(string who)
{
    if (SECURITY->query_wiz_level(who))
    {
        return 0;
    }

    if (wildmatch("*jr", who))
    {
        return 0;
    }

    if (MANAGER->query_rogue(who))
    {
        return 0;
    }

    return 1;
}

void
add_aliases(object reader)
{
    string *guildmembers;
   
    setuid();
    seteuid(getuid());

    guildmembers = MANAGER->query_all_guild_members();
    guildmembers = filter(guildmembers, member_filter);

    for_each(({ "guild", "vamps", "vampires" }), 
        &reader->set_alias(, guildmembers));
}
 
void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

void
init()
{
    ::init();
    post_init();
}

#if 0
void
post_init()
{
    object reader;
    reader = clone_object("/d/Wiz/shiva/mail_reader");
    add_aliases(reader);
    reader->move(this_player(), 1);
}
#endif
