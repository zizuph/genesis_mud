/*
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 *
 * Updated by Vitwitch, Nov 2020
 */
    
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/d/Krynn/guilds/elven_archers/rooms2/baseroom_fort";

#define GUILDROOMS "/d/Krynn/guilds/elven_archers/rooms2/"
#define VIEWDEST "/d/Krynn/qualinesti/elf_camp/camp5"

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

    set_short("A postal tree in a treetop fortress");

    set_long(gBlurbPfx +
             " A curious tree stands in the centre of the room. "+
             "The many holes in the living wood of the tree, are variously filled "+
             "with the mail of Elven Archers, fetched and carried by unseen agency "+
             "to and from the far corners of the Realms. "+
             gBlurbSfx +
             " To the southwest there lies "+
             "the thrumming heart of the fortress. To the west lies a room, "+
             "from which an enticing scent wafts.\n");

    add_item(({"fort","fortress","treetop fortress"}),"@@fort_purpose");
    add_item(({"treetops","whispering treetops","branches"}),"@@fort_description");
    add_item(({"walls","wall"}),"@@fort_walls");
    add_item(({"stakes","stakes","strands","strand"}),"@@fort_stakes");
    add_item(({"loopholes","loophole","window","windows","ground","ground below"}),"@@fort_vantage");
    add_item(({"foliage"}),"@@fort_foliage");

    add_cmd_item(({"down", "ground", "loophole", "window"}), "view", "@@view_down");
    set_tell_time(250);
    add_tell("Wings flutter unseen behind the holes in the old postal tree.\n");


    gViewFallDest = VIEWDEST;

    INSIDE
    
    add_exit(GUILDROOMS + "fort_reservoir", "west", 0);
    add_exit(GUILDROOMS + "fort_nexus", "southwest", 0);

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

