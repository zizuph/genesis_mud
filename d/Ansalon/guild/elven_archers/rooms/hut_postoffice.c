/**
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
inherit "/d/Krynn/std/room";

#define MAILREADER      "/secure/mail_reader"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_long("You are in a small room that appears to have been fashioned into the side of a tree " +
             "trunk. The branches making up the ceiling grows low here, but the area feels well protected and sheltered from the wind. "+
             "There are well trained pigeons in a cage here, ready to carry your messages to the desired destination.\n");

    set_short("You are standing in the pigeon room");    

    add_item(({"room", "area"}), long());
    add_item(({"tree", "trunk", "tree trunk"}), "The tree trunk has this room built into it.\n");
    add_item(({"branches", "ceiling"}), "The branches are making up the ceiling of this room.\n");
    add_item(({"pigeons", "trained pigeons", "well trained pigeons", "cage"}), "There is a cage here, " +
             "which holds a group of pigeons ready for duty to bring your message to its destination.\n");
    add_item(({"hut", "camouflaged hut"}), "You are standing in it.\n");

    INSIDE;
    add_exit(ROOMS + "hut_board", "west", 0);
    add_exit(ROOMS + "hut_rack", "north", 0);
    add_exit(ROOMS + "hut_rope", "east", 0);
    reset_room();
}

void
init()
{
    ::init();

    object mr;
    setuid();
    seteuid(getuid());

    mr = clone_object(MAILREADER);
    mr->move(this_player(), 1);
}

void
leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);

   object reader;   
   reader = present(MAILREADER_ID, ob);
   
   if (reader)
      reader->remove_object();
}

int
query_mail(int silent)
{
   string new;
   int mail;
   
   mail = MAILREADER->query_mail();
   
   if (!mail) return 0;
   
   if (silent) return 1;
   
   new = "";
   if (mail == 2) new = " NEW";
   if (mail == 3) new = " unread";
   
   write("\n" +
      "There is" + new + " mail for you in the " +
      "post office in the archers guild.\n\n");
   return 1;
}                                                

