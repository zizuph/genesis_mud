/*
 * This is the main Traveller guild room.
 * Here you can join, leave and list. 
*/

#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit TRAVELLERS_STD_DIR + "room_base";

public int
north()
{
    object tp = this_player();

    if(COUNCIL_MEMBER(tp->query_real_name()))
    {
        return 0;
    }

    if(tp->query_wiz_level())
        return 0;

     write("A strong forcefield blocks the way.\n");
     return 1;
}

public void
create_traveller_room()
{
    add_prop(ROOM_S_MAP_FILE, "trav_map.txt");
    string sign;
    set_short("Travellers Room");
    set_long("This is a large room, well lit by torches" +
        " and a huge fire against the far wall. A number of" +
        " chairs rest against the walls, and look very comfy." +
        " A large sign hangs above the fireplace.\n");
    add_exit("balcony", "south");
    add_exit("councilrm", "north", north);
    sign = "Here you can <join> or <leave guild> the Travellers guild.  " +
        "You may also <list> to see what guilds you are already " +
        "a part of.  Members can receive a <badge> to allow others " +
        "to join.\n";
    add_item("sign", sign);
    add_cmd_item("sign", "read", sign);
}


public int
join(string str)
{
    object sh, *badges, tp;
    mixed why;

    if(strlen(str))
    {
        return 0;
    }

    tp = this_player();

    if(!tp->query_wiz_level() &&
        !sizeof(badges = filter(deep_inventory(tp), 
        &wildmatch(TRAVELLERS_BADGE + "*") @ file_name)))
    {
        write("You have not been authorized, and cannot join.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    sh = clone_object(TRAVELLERS_SHADOW);

    if(stringp(why = sh->acceptable_member(this_player())))
    {
        write(why);
    } else {
        switch(sh->add_race_shadow(this_player()))
        {
            case 1:
                tp->clear_guild_stat(SS_RACE);

                if(sizeof(badges))
                {
                    badges[0]->remove_object();
                }

                write("You are now a Traveller.\n");
                write("You receive the Traveller walking stick, which " +
                    "magically adjusts to fit you.\n");
                say(QCTNAME(tp) + " joins the Travellers Guild.\n");
                log_file("travellers", 
                    capitalize(tp->query_real_name()) +
                    " joined " + ctime(time()) + "\n");

                return 1;
            case -4:
                write("Your other guilds don't want you in this one!\n");
                break;
            default:
                write("An error has prevented you from joining.\n");
        }
    }

    sh->remove_shadow();

    return 1;
}

public int
leave(string str)
{
    object tp = this_player();

    if(str != "guild")
    {
        return notify_fail("Leave what? The guild??\n");
    }
    
    if(!IS_MEMBER(tp))
    {
        write("You aren't a member!\n");
        return 1;
    }

    tp->leave_travellers();

    return 1;
}

public int
list(string str)
{
    if(strlen(str))
    {
        return 0;
    }

    str = this_player()->list_major_guilds();

    if(str)
    {
        write("You are a member of the following guilds.\n" + str);
    } else {
        write("You are not a member of any important guilds.\n");
    }

    return 1;
}

public int
badge(string str)
{
    object tp = this_player();

    if(IS_MEMBER(tp))
    {
        clone_object(TRAVELLERS_OBJ_DIR + "badge")->move(tp, 1);
        write("You receive a badge of authorization.\n");
        return 1;
    }

    write("You are not a member.\n");

    return 1;
}

public void
init()
{
    ::init();
    add_action(join, "join");
    add_action(leave, "leave");
    add_action(list, "list");
    add_action(badge, "badge");
}
