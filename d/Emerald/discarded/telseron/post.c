/*
 * Post Office of Telseron
 * Updated by Finwe September 1996
 * The all_cmd routine was taken from /d/Genesis/login/bodies.c
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
#define MAILREADER      "/secure/mail_reader"
 
void
create_room()
{
    set_short("Telseron's post office");
    set_long( "    You are in the post office of Telseron. This is a "+
        "place of great magic! From here you can reach people with a "+
        "written message, all over the world. As a courtesy to those " +
        "who are present, the Postmaster insists that everyone here " +
        "be quiet. A sign is posted here.\n\n");
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_item("sign", 
        "Instructions are painted on the sign.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");
 
 
    add_exit(TOWNSHIP_DIR + "post_foyer", "down", "@@downstairs@@");
}
 
init()
{
    object reader;
 
    ::init();
    reader=clone_object(MAILREADER);
    if (!reader) 
    {
        write("No mailreader is available at this time.\n");
        return;
    }
    reader->move(this_player());
    
    add_action("all_cmd", "", 1); /* catches cmds and examines them */
}
 
leave_inv(object ob,mixed to)
{
    object reader;
 
    ::leave_inv(ob,to);
    reader=present("mailread",ob);
    if (reader)
        reader->remove_object();
}
 
int downstairs()
{
    write ("You quietly descend the stairs to the foyer.\n");
}
 
string
read_sign()
{
    return   "          Common commands are:\n" + 
             "          read           Read your mail.\n" +
             "          mail <name>    Mail to player 'name'.\n" + 
             "          from           List all mail headers.\n\n" +
             "Examine the mailreader for more commands.\n";
}
 
 
/*
 * Function name: all_cmd
 * Description  : Catch all player commands. Take care of the legal ones
 *                and throw all the others away
 */
public int
all_cmd(string str)
{
    if(TP->query_wiz_level())
	return 0;
    switch(query_verb())
    {
    case "v":
    case "vitals":
    case "date":
    case "commune":
    case "mail":
    case "from":
    case "resend":
    case "read":
    case "mread":
    case "malias":
    case "autocc":
    case "quit":
    case "look":
    case "exa":
    case "examine":
    case "save":
    case "typo":
    case "sysbug":
    case "idea":
    case "praise":
    case "down":
    case "i":
    case "l":
    case "who":
    case "remember":
    case "reply":
    case "last":
    case "alias":
    case "Items":
    case "bug":
    case "!":
        return 0;
        break;
    default:
    {
	write("The postmaster looks up and glares at you. You decide " +
	      "to be quiet here.\n");
	return 1;
    }
    }
}
