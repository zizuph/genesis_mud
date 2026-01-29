#pragma save_binary

#include "../guild.h"

int
start(string str)
{
    if (str != "here") 
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!IS_MEMBER(this_player()) ||
        (this_player()->query_vamp_coven() != LAIR_MANAGER->query_coven(file_name(this_object()))))
    {
        write("You may not start here.\n");
        return 1;
    }

    this_player()->set_default_start_location(file_name(this_object()));
    write("Ok.\n");
    return 1;
}

void
init_lair()
{
    add_action(start, "start");
}

public int
query_vamp_lair()
{
    return 1;
}

public void
make_coffin(string who)
{
    object ob;

    ob = clone_object(VAMP_ROOM_DIR + "coffin");
    ob->move(this_object(), 1);
    ob->set_owner(who);
}

int
mem_filter(string who)
{
    if (wildmatch("*jr", who))
    {
        return 0;
    }

    if (SECURITY->query_wiz_level(who))
    {
        return 0;
    }

    return 1;
}

public void
add_coffins()
{
    string *members;

    setuid();
    seteuid(getuid());

    members = MANAGER->query_all_coven_members(LAIR_MANAGER->query_coven(file_name(this_object())));
    members = filter(members, mem_filter);

    for_each(members, make_coffin);  
}
