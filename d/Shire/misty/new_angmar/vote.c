/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"

void
create_shire_room()
{
    set_short("Court room of Army of Angmar");
    set_long("This is the court room of Army of Angmar. Internal matters " +
        "of the Army were taken care of here. On the wall you see the " +
        "silver plaque and a sign\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_item("sign", "It is quite plain with some instructions on it.\n");
    add_item(({"plaque","silver plaque"}), "A very nice silver plaque indeed. "+
        "It has something engraved on it and it looks rather "+
        "important.\n");
    add_cmd_item("sign", "read", "@@read_sign");
    add_cmd_item(({"plaque","silver plaque"}), "read", "@@read_pun_list");

    add_exit(NEW_ANGMAR + "priv","south");
    add_exit(NEW_ANGMAR + "library","east");
    add_exit(NEW_ANGMAR + "council","north");
}

/*
* Function name: read_pun_list
* Returns:       What you get when you 'read punishments'.
*/
string
read_pun_list()
{
    return "THE LIST OF PUNISHMENTS\n\n"+
        "      1. Ban from training for 2 weeks\n"+
        "      2. Lowering effectivity of specials for 10 days + above\n"+
        "      3. Disallowing specials for 1 week + above\n"+
        "      4. Beating on the head (losing skills) + above\n"+
        "      5. Extermination\n"+
        "      6. Rejecting from Army + beating on the head\n";
}

/*
* Function name: read_sign
* Returns:       What you get when you 'read sign'.
*/
string
read_sign()
{
    return "Available commands:\n"+
        "  To suggest punishment no. <num> for <name> use:\n"+
        "     'punish <name> <num>'\n"+
        "  To vote/change vote on punishment no. <num> for <name> use:\n"+
        "     'vote punish <name> <num> <yes/no>'\n"+
        "  To start election for council position no. <num> use:\n"+
        "     'start election for council <num>'\n"+
        "  To apply for council position no. <num> use:\n"+
        "     'apply for council <num>'\n"+
        "  To withdraw application for council position use:\n"+
        "     'withdraw application'\n"+
        "  To vote/change vote for <name> for council position no. <num> use:\n"+
        "     'vote council <num> <name>'\n"+
        "  To check your votes use:\n"+
        "     'check votes'\n"+
        "  Captain can promote <name> to the Recruitment Officer with:\n"+
        "     'promote Recruitment Officer <name>'\n"+
        "  and demote from Recruitment Officer with:\n"+
        "     'demote Recruitment Officer <name>'\n";
}

