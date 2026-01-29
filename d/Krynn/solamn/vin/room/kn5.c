// kn5.c   High Justice Room
// grace sept 1994

/**********************************************************************
 * - Added the following:                                           - *
 * -   #include "/d/Krynn/solamn/vin/std/no_scry_room.c"            - *
 * -   add_prop(ROOM_M_NO_SCRY, query_no_scry);                     - *
 * -                                                                - *
 * - Modified by Damaris@Genesis 03/2005                            - *
 **********************************************************************/

#include "../knight/guild.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit IN_BASE;
#include "/d/Krynn/solamn/vin/std/no_scry_room.c"

#define MAILREADER_ID   "_reader_"
#define ROSE   ADMIN->query_conclave("rose")
#define WAIT \
   ({  \
      VROOM + "kn1", \
      VROOM + "void", \
   })


string query_crest_str();

mapping crest = ([ ]);
mapping members = ([ ]);

string query_crest_str()
{
    string gm_name = C((ADMIN)->query_conclave("rose"));

    restore_object(CREST);
    if (member_array(gm_name, m_indexes(members)) < 0)
	return "an exquisite red rose";

    return crest[members[gm_name]];
}


string long_desc()
{
   return "This is the private "+
     "abode of "+ ADMIN->query_conclave("rose") + 
     ", the High Justice of the Solamnian Knights.  "+
     "It is a stark room, both too large and too comfortable to be a "+
     "monk's cell, yet still rather cold and austere.\n   There is a modest "+
     "altar against the west wall, and a mosaic depicting "+
     query_crest_str()+" rests above it"+
     ".\n   A small brazier rests atop a rickety desk "+
     "that seems to squat in the northeast corner of the room.  Behind"+
     " it stands a letter-box, the kind one would see in a post-office"+
     ", and a chair with a blanket thrown over it.  There is an empty "+
     "fireplace along the south wall, and a small window near the door.\n";
}

void
create_vin_room()
{

    set_short("High Justice Room");
    set_long("@@long_desc");

    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_M_NO_SCRY, query_no_scry); 
   clone_object(VOBJ + "rose_b")->move(TO);

   AI(({"brazier","coals","charcoal"}),
       "The brazier is elegantly shaped, the only decorative item in"+
       " the room. Within it are contained live coals over which "+
       ROSE +" warms cold hands.\n");
   AI(({"fire", "fireplace", "grate"}),
       "The grate is cold and empty. It would seem that a fire has not "+
       "been lighted there in many a month, accounting for the chill of "+
       "the room.\n");
   AI(({"desk", "rickety desk", "table"}),
       "This is the poorest excuse for a desk that you have ever seen. "+
       "It appears to be a table salvaged from the refectory, much the "+
       "worse for wear and not the least pleased about it. Circular "+
       "stains from beverages, live coals, and boot heels mar its surface.\n");
   AI(({"scrolls", "parchment", "letters", "letter", "mail", "missives"}),
       "An astonishing volume of papers ranging from parchment scro"+
       "lls to bark-paper missives have been stuffed into the slots of "+
       "the letter-box in a vain attempt at organization.\n");
   AI(({"letterbox", "letter-box", "box", "slots"}),
       "Dusty, in serious disrepair, this letter-box nonetheless must be "+
       "of excellent quality to have withstood the tenure of this parti"+
       "cular High Justice. It has row upon row of slots, all stuffed to "+
       "capacity with scrolls, letters, personal mail, and a plethora of "+
       "official-looking missives.\n");
    AI("chair",
       "It looks like a stable enough chair, but you don't really want to "+
       "risk sitting in it. It appears to be "+ ROSE + "'s favorite place to "+
       "catch a nap. In your mind you can picture "+ ROSE +" leaning "+
       "back in the chair, feet propped on the table, with torso cove"+
       "red by the disreputable-looking blanket.\n");
    AI("blanket", "Looking at it is as close as you think you'll get. "+
       "You aren't sure how often "+ ROSE + " uses it, but the scent "+
       "would lead one to believe that it hasn't been washed in a while.\n");
    AI("altar", "It is as plain and severe as the rest of the room.\n");
    AI(({"mosaic", "dragon"}),
       "A well-crafted mosaic made of thousands of hammered squares "+
       "of platinum. The Dragon featured is the avatar form of Paladine, "+
       "patron of the Order of the Rose.\n");
    AI("window", "This window provides a view of the waiting room.\n"+
        "To see into it, try to <view room>.\n");
 
}

string
wait_desc()
{
    object *inv, *live;
    string room_to_load;
    int i;

    (VROOM + "greathall_balcony")->foo_bar_load_me();

    inv = all_inventory(find_object(VROOM + "greathall_balcony"));

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	if (sizeof(live) > 0)
	    return ("In that room you can see " +
	      COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be empty.\n");
}


int
do_view(string str)
{
    if (!str || str == "room" || str =="waiting room")
    {
	TP->catch_msg(wait_desc());
	return 1;
    }
    NF("View what?\n");
    return 0;
}

public void
init()
{
   add_action("do_view", "view");
   set_alarm(0.1,0.0,"do_write_welcome",TP);
}

void
do_write_welcome(object who)
{
    object mr;
    string ro = (ADMIN)->query_conclave("rose"),
           sw = (ADMIN)->query_conclave("sword"),
           cr = (ADMIN)->query_conclave("crown");
    string *conclave = ({ });

    int a = (ADMIN)->check_can_perform_command(who);
    object p = P(CONCLAVE_OBJ, who);
    mixed c = !p;

    if (c && a)
      {
	  who->catch_msg("In this room you have access to the conclave " +
			 "command object. Examine it to see your commands.\n");
	  clone_object(CONCLAVE_CMD)->move(who,1);

	  if (ro && stringp(ro) && ro != "")
	    conclave += ({ ro });
	  if (sw && stringp(sw) && sw != "")
	    conclave += ({ sw });
	  if (cr && stringp(cr) && cr != "")
	    conclave += ({ cr });
	  ::init();
	  mr = clone_object("/secure/mail_reader");
	  if (conclave)
	    mr->set_alias("conclave", conclave);
	  if (GUILDMASTERS)
	    mr->set_alias("guildmaster", GUILDMASTERS);
	  mr->move(who, 1);
      }
}

void
leave_inv(object ob, object to)
{
    object reader;
    ::leave_inv(ob, to);
    
    reader = present(MAILREADER_ID, ob);
    if (reader)
      reader->remove_object();
    reader = present(CONCLAVE_OBJ, ob);
    if (reader)
      reader->remove_object();
}
