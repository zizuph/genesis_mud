/*
 * Post Office room
 * By Finwe, May 2006
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <stdproperties.h>
#include <const.h>

inherit "/d/Faerun/guilds/drow/rooms/base_room.c";

string messages;
int new_mail;

void
create_drow_room()
{
    add_prop(ROOM_S_MAP_FILE, "drow_guild_map.txt");

    set_short("Message Cave");
    set_long(short() + ". The enlarged cave is where drow send and receive messages. It is clean and well used. The chamber is dark except for faerie fire that limnes a sign hanging on a wall.\n");

    add_item(({"cages"}),
        "They are all sizes and made of metal. Some are tall, others short, some round and others square shaped. They look well maintained.\n");
    add_item(({"animals"}),
        "They fill the cages and are well taken care of. The animals are all sizes and shapes and can be purchased to deliver messages\n");
    
    add_item("sign", "There are words written on it. You should read them.\n");
    add_cmd_item(({"sign", "words"}), "read", "@@read_sign@@");

    add_item("plaque", "There are words written on it. You should read them.\n");
    add_cmd_item(({"plaque", "words"}), "read", "@@read_plaque@@");


    add_exit("board_pri", "north");

}

/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();

}
 
enter_inv(ob, from)
{
   object reader;
   object vote_room;
   string *masters;
 
   ::enter_inv(ob, from);
 
    if (!living(ob))
        return;
   if (present("mailreader", ob)) return;
   reader=clone_object("/secure/mail_reader");
   reader->move(ob, 1);
}
 
leave_inv(ob, to)
{
    object reader;
   
    ::leave_inv(ob, to);
    reader = present("mailreader", ob);
    if (reader && !this_player()->query_wiz_level()) 
        reader->remove_object();
}
 
query_mail(silent) 
{
   string name;
   string new;
   
   name = lower_case(this_player()->query_name());
   if (!restore_object("/d/Genesis/post_dir/"+name) || messages == "")
      return 0;
   if (silent)
      return 1;
   new = "";
   if (new_mail)
      new = " NEW";
   write("\n"+
      "There is"+new+" mail for you in the nearest post office.\n");
   return 1;
}


string read_sign()
{
    return "On the sign limned in faerie fires you read:\n\n" +
    "Examine the mailreader for a list of different commands available " +
    "to you.\n";
}