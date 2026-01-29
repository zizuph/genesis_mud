// kn4.c   High Clerist Room
// grace sept 1994
// write(OTHER_ROOM->long());   or query_long());


#include "../local.h"
#include <stdproperties.h>

inherit SPURRM;

#undef ADMIN
#define ADMIN           "/d/Krynn/guilds/knights/admin/admin"
#undef CONCLAVE_OBJ
#define CONCLAVE_OBJ     "/d/Krynn/guilds/knights/obj/conclave_cmd"
#define MAILREADER_ID   "_reader_"
#define SWORD           ADMIN->query_conclave("sword")
#define WAIT \
   ({  \
      ROOM + "kn1", \
      ROOM + "void", \
   })


void
create_spur_room()
{

   SHORT("High Clerist Room");
   LONG("You have entered a warmly-lit room.\nThis is the private "+
     "office of "+ SWORD + ", the High Clerist of the Solamnian Knights."+
     "  A fire burns "+
     "in the fireplace along one wall, and hung above the mantle are "+
     "three swords.  A huge banner bearing a kingfisher and swords "+
     "hangs on another wall. A massive oaken desk dominates the "+
     "room and is neatly stacked with parchments, scrolls, and tomes.  "+
     "A bookcase leans against a third wall, laden with a motley assort"+
     "ment of books and scrolls.  A soft rug covers the stone floor, and "+
     "there is a small window cut into the wall near the door.\n");

   INSIDE;
   LIGHT;
 
   clone_object(SOBJ + "sword_b")->move(TO);

   AI(({"fire","fireplace","firewood","woodbox", "tongs", "tools"}),
       "This large fireplace warms the room considerably, keeping the "+
       "High Clerist alive in those cold winter evenings.  Beside the fire"+
       "place sits a large woodbox and some rathe low-quality tongs "+
       "and tools for manipulating the firewood.\n");
   AI("swords", "These swords are displayed above the mantle of "+
       "the fireplace.  The first is an heirloom of some sort, probably "+
       "belonging to the High Clerist's family.  It rests in a lacquered " +
       "wooden scabbard, well maintained.  The sword which hangs "+
       "above it is a functional two-handed sword, well cleaned and "+
       "sharpened, which bears the mark of the Solamnian armoury.  "+
       "Finally, the third sword, which hangs below the ornamented "+
       "sword, is a short sword of very poor quality, perhaps taken "+
       "as a trophy from a draconian or hobgoblin.  It hangs incongru"+
       "ously below the beautiful, ornamental sword and the sharp, "+
       "strong, large sword.\n");
   AI(({"banner", "kingfisher"}),
       "This large, blue banner bears a great yellow kingfisher emb"+
       "lem, crossed behind with two swords.  Above the kingfisher "+
       "hangs a smaller crown and below rests a rose in bud.  Appar"+
       "ently this is the standard of the Order of the Sword.\n");
   AI("desk",
       "This huge oaken desk bears the weight of the High Clerist's "+
       "work.  It is apparently quite old, and has been scarred by time;"+
       " you even see marks of blades swung carelessly or in haste "+
       "marring its front.\n");
   AI(({"scrolls", "parchments"}),
       "The large amount of paperwork which dominate this desk attest"+
       "to the workload of a High Knight.  You see mails from Knights "+
       "and non-Knights, commissions of supplies, and plans for a strong"+
       "hold.  One side of the desk seems to be dedicated to the High "+
       "Knight's clerical duties, and you see half-composed prays, medi"+
       "tations, and even a poem, to your surprise.\n");
   AI("bookcase", "This large bookcase contains the High Clerist's small "+
       "personal library. Here you see prayerbooks, dictionaries of the "+
       "common speech, elven and dwarvish, and histories painstakingly "+
       "copied from the Library of Palanthas.  The crowning piece of this "+
       "bookshelf is an exquisetly detailed set of the Measure of the Knig"+
       "hts of Solamnia, illuminated and lovingly cared for.\n");
    AI("rug", "This soft carpet warms the room and softens the surface "+
       "of the stone floor.\n");
    AI("window", "This window provides a view of the waiting room.\n"+
        "To see into it, try to <view room>.\n");
 
}


string
wait_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = WAIT;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
      return ("In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be empty.\n");
}
                                                                                                                                                    
                                                                 
init()
{
   add_action("do_view", "view");
   set_alarm(0.1,0.0,"do_write_welcome",TP);
   ::init();
}

int                                                                           
do_view(string str)
{                                                                             
     object old_env;   

     old_env = environment(this_interactive());
                                                                                                
     if (!str || str == "room" || str =="waiting room")
     {
     write("=================================================="+
              "====================\n");
     this_interactive()->move(ROOM + "kn1.c");
     this_interactive()->command("l");                                        
     this_interactive()->move(old_env);                                       
     write("=================================================="+
             "====================\n");
     return 1;
     }
   return 0;
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
			 "command object. Examine it to see your commands. " +
			 "If you have problems, suggestions or " +
			 "improvements, contact 'krynn'.\n");
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
}
