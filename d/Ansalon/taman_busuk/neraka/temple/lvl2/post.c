/* This room is supposed to be the post office for the PoT.
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
#include <const.h>
#include <files.h>

inherit TEMPLE + "std_temple.c";
inherit TEMPLE + "lib/seats.c";
inherit "/d/Genesis/lib/post";

#define ALLOWED_COMMANDS ({ \
    "mail", "from", "autocc", "read", "mread", "malias", "resend", \
    "bug", "idea", "praise", "typo", \
    "sysbug", "sysidea", "syspraise", "systypo", \
    "alias", "unalias", "do", "resume", "save", "quit", "options", \
    "commune", "reply", "help", "last", "date", "who", \
    "look", "l", "examine", "exa", \
    "sit", "rise", \
    })

string *gSign = ({ });

string
alias_names()
{
    return implode(gSign, "\n ");
}

void
create_temple_room()
{
    ::create_temple_room();

     set_short("The Post Office");
    set_long("This semi-circular room serves as the post office of the " +
        "temple. A couple of writing pulpits stand along the round wall and " +
        "a wooden shelf can be seen just next to the entrance.\n");

    add_item(({"pulpits", "writing pulpits"}), "Ordinary wooden writing " +
        "pulpits where one can take a seat and read and respond to " +
        "letters in a practical fashion. A sign has been fastened " +
        "upon them.\n");
    add_item(({"shelf", "wooden shelf"}), "Lining the wall by the " +
        "entrance at breast height, is a simple wooden shelf upon " +
        "which parchments of various make has been placed.\n");
    add_item("parchments", "Lying on the simple wooden shelf are " +
        "parchments of various make.\n");
    add_item("sign", "It appears to be a list of some sort.\n");
/*
    add_cmd_parse("[by] [in] [the] [writing] 'pulpits'", ({ "sit" }),
        "You sit down in an empty writing pulpit.\n");
*/
    add_cmd_item("sign", ({ "read" }), "Those who also can recieve letters " +
        "here are:\n @@alias_names@@\n");

    /* Got tired of writing, six ought to be enough. :)
     */
    set_chairs(({"writing pulpit", "writing pulpit", "writing pulpit",
        "writing pulpit", "writing pulpit", "writing pulpit" }));

    add_exit( LVLTWO + "corr2.c", "southeast" );
}

void
add_aliases(object reader)
{
    string name, *arr, *arr2;
    int gender, x, size;
    object pl;

    gSign = ({ });
    
    if (strlen((name = GUILD_ADMIN->query_council_seat("leader"))) > 2)
    {
        if (find_player(name))
            gender = (find_player(name)->query_gender());
        else
        {
            setuid();
            seteuid(getuid());
            
            pl = SECURITY->finger_player(name);
            gender = pl->query_gender();
            pl->remove_object();
        }
        
        switch (gender)
        {
            case G_FEMALE:
                reader->set_alias("nightlady", ({ name }));
                gSign += ({ "Nightlady" });
                break;
            default:
                reader->set_alias("nightlord", ({ name }));
                gSign += ({ "Nightlord" });
                break;
        }
    }
    if (strlen((name = GUILD_ADMIN->query_council_seat("herbmanager"))) > 2)
    {
        reader->set_alias("herbmanager", ({ name }));
        gSign += ({ "Herbmanager" });
    }
    if (strlen((name = GUILD_ADMIN->query_council_seat("mentor"))) > 2)
    {
        reader->set_alias("headmentor", ({ name }));
        gSign += ({ "Headmentor" });
    }
    if (strlen((name = GUILD_ADMIN->query_council_seat("inquisitor"))) > 2)
    {
        reader->set_alias("inquisitor", ({ name }));
        gSign += ({ "Inquisitor" });
    }
    if (strlen((name = GUILD_ADMIN->query_council_seat("librarian"))) > 2)
    {
        reader->set_alias("librarian", ({ name }));
        gSign += ({ "Librarian" });
    }

    gSign += ({ "Council" });
    arr = GUILD_ADMIN->query_guild_council();
    arr -= ({ 0 });

    for (x = 0, arr2 = ({ }) ; x < sizeof(arr) ; x++)
    {
        if (member_array(arr[x], arr2) < 0)
            arr2 += ({ arr[x] });
    }
    
    reader->set_alias("council", arr2);
}

void
leave_inv(object ob, mixed to)
{
    seats_leave_inv(ob, to);

    ::leave_inv(ob, to);
    
    post_leave_inv(ob, to);
}

public int
silent_room(string str)
{
    int x, size;
    mixed *arr;

    /* For the stamp event
     */
    if (!this_player()->query_npc() && query_verb() == "buy")
        return 0;

    /* Catch allowed commands and exit commands */
    if (member_array(query_verb(), ALLOWED_COMMANDS +
        this_object()->query_exit_cmds()) >= 0)
        return 0;

    /* Catch actions added by add_cmd_item() */
    for (x = 0, arr = query_cmd_item(), size = sizeof(arr) ; x < size ; x++)
    {
        if (member_array(query_verb(), arr[x][1]) >= 0)
            return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("Because you are a wizard you find yourself able to do that " +
            "anyway.\n");
        return 0;
    }

    write("The post office is a place of silence. Please honour it.\n");
    return 1;
}

void
init()
{
    ::init();
    
    post_init();
    add_action(silent_room, "", 1);
    seats_init();
}
