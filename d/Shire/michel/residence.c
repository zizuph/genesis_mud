inherit "/d/Shire/room.c";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
 
object mayor, roster;

#define MIN_AWARE 10

void
reset_room()
{
   roster = 0;
 if (!mayor)
 { 
   mayor=clone_object(MICH_DIR + "npc/mayor");
   mayor->move(TO);
 }
}

void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   set_short("The Mayor's residence");
  set_long("This house is the finest in all of Michel Delving.  Here "+
   "the Mayor of the Shire resides and holds office when the need arises.  "+
   "Some stairs lead down into a cellar.  The mayor has a fine oak desk here "+
   "for his correspondence as well as a nice soft chair to sit in.  A curtain "+
   "separates the office from the Mayor's personal chambers, where he sleeps.  "+
   "Windows line the western wall, and from the ceiling hangs a chandelier. "+
   "Out leads back to the street.\n");

   add_item(({"ceiling","chandelier","candles"}),
   "Hung from a solid oak beam in the ceiling, the Mayor's chandelier has "+
   "many candles attached to it, which burn at night.  A rope allows the "+
   "Mayor's assistants to lower it and refill the candleholders.\n");

   add_item("rope","It is a strong white rope.\n");

   add_cmd_item("rope","pull","You start to pull on the rope but change your mind, "+
   "thinking the Mayor would become displeased.\n");
 
   add_item(({"chair","soft chair","nice soft chair"}),
   "The Mayor's chair is made of oak but heavily padded with down pillows.  "+
   "The bottom of the chair is deformed however, as it seems the Mayor "+
   "is a rather heavy hobbit.\n");

   add_item(({"curtain","chambers"}),"The solid green curtain cannot be "+
   "seen through and divides the Mayor's chambers from his office.\n");

   add_item(({"window","windows","western wall","wall"}),
   "The windows are large round ones and offer a fine view of Michel Delving.\n");

   add_item("view","You see the street outside and the Mathom House across the "+
  "way.\n");

   add_item(({"cellar","stairs","stair"}),
   "The stairs look old and creaky, and they lead down to the cellar.\n");

   add_item(({"fine oak desk","oak desk","desk"}),
   "The desk has a lot of papers scattered on it.\n");

   add_item(({"paper","papers"}),
  "The papers are all written in the Mayor's scrawling illegible hand.  It is "+
   "hard to imagine anything readable in there.\n");

    add_prop(ROOM_M_NO_ATTACK, 1);
   add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_I_LIGHT, 2);
   add_prop(ROOM_I_INSIDE,1);
   add_prop("_obj_s_search_fun","do_search");
 
    add_exit(MICH_DIR + "gamroad3","out","@@check_naked");

   reset_room();
}
 
/* Description:     Check if a player has a i_listen_mayor property
 * Returns:         0 if the player has
 *                  1 otherwise
 * Modified function from  Shires herbshop
 */
check_naked()
{
   FIXEUID;
   if (TP->query_prop("_i_listen_mayor_"))
   {
      write("The Mayor has still not allowed you to leave!\n");
      say("The Mayor doesn't allow " + QCTNAME(TP) +" to leave.\n");
      return 1;
   }
   return 0;
}


string
do_search(object searcher, string str)
{
   int awareness;

   if(present("mayor"))
   {
     write("The mayor eyes you carefully and you stop searching.\n");
     return 0;
   }

   awareness = searcher->query_skill(SS_AWARENESS);
   if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;
   if(!str || (str!= "desk" && str != "papers")) return 0;
   if(roster) return 0;
   seteuid(getuid(TO));
   roster = clone_object(MICH_DIR + "obj/roster");
   roster->move(searcher,1);
   say(QCTNAME(searcher)+ " finds something in the Mayor's desk.\n");
    return "You find a "+roster->short()+" in the desk.\n";
}

