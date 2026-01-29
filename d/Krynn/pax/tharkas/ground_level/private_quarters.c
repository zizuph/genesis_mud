/*
   Pax Tharkas, Ground level, Private quarters of Highlord verminaard.

   private_quarters.c
   ------------------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/05/08
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit PAXINROOM;

#define I_FOUND_DIARY  "_i_found_pax_diary"
#define SOHM_I_SEARCH_BOOKSHELF   "_sohm_i_search_verms_bookshelf"

int page_found = 0; /* 0 = diary_page NOT found. */
object scroll;


void
reset_pax_room()
{
   if(page_found)
   {
      if(page_found > 1)
         page_found = 0;
      else
         page_found++;
   }
}


void
create_pax_room()
{
   set_short("Private quarters");
   set_long("You are in a room that look like someones private " +
            "quarters. A large bed is standing at the east wall. " +
            "Red drapes covers the view to, and from, the bed. In the " +
            "northeastern corner there is a scroll rack and a desk, " +
            "with a large comfortable looking chair before it. " +
            "In the middle of the room " +
            "a dining table, around which eight chairs has been placed. " +
            "On the wall you see a picture of a somewhat peculiar " +
            "looking dragon.\n");
	
   INSIDE;

   add_item(({"bed", "large bed"}), "You peek through the drapes, and " +
            "see a large bed of oak wood. " +
            "The ends and the sides of the bed are decorated with " +
            "the most delicate carvings showing woodland sceneries.\n");

   add_item(({"drape", "drapes"}), "These are red drapes made from " +
            "red dyed heavy cloth of exquisite fabric. Fine threads " +
            "of gold has been woven into the red cloth.\n"); 

   add_item("desk", "A desk carved of dark wood. Each of the legs " +
            "carrying the desk, resembles a warrior with elven features. " + 
            "On the desk you see a large map. Across the top of the map " +
            "you see the name Abanasinia. Furthermore you see a few " +
            "papers written in a language you do not seem to understand.\n");

   add_item(({"scroll rack","scrolls","rack"}), "A small scroll rack stands " +
            "beside the desk. There are a few scrolls stacked neatly upon it.\n");

   add_item("papers", "@@paper_descr");

   add_item("map", "You examine the map closer. The kharolis mountains " +
            "covers large parts of the map. In the north part of the map " +
            "you find Solace, and further south you see Pax Tharkas. " +
            "In the most southern part of the map you see a large " +
            "harbour city called Tarsis. Someone has crossed out the " +
            "name of the bay at which the city lies. Actually the whole " +
            "bay has been crossed out. Most remarkable on the map is a " +
            "large red circle drawn around a city somewhere halfway " +
            "between Solace and Pax tharkas. A city called Qualinost in a " +
            "very large forest called Qualinesti.\n");

   add_item("chair", "This is a large comfortable looking chair, carved " +
            "out of dark wood. Nice carvings decorate the large chair.\n");

   add_item("chairs", "These are ordinary dining room chairs. Placed " +
            "at a large dining table, four at each side.\n");

   add_item("table", "A long wooden dining room table. The table has " +
            "been prepared for eight persons. Eight chairs stands next " +
            "to the table, four along each side.\n"); 

   add_item("picture", "Looking closer at the picture you see a painting " +
            "of a five headed dragon. The heads of the dragon are all of " +
            "a different colour. Black, green, blue, white and red. The " +
            "head of the red dragon seems to look straight at you.\n"); 

   add_search(({"scroll rack","rack","scrolls","scroll"}),
        10,"search_scrollrack",1);

   add_exit(GROUND_LEVEL + "corridor1", "north",0);
}

string
search_scrollrack(object searcher, string what)
{
    if((this_player()->query_guild_name_occ() == "School of High Magic") ||
       (this_player()->query_guild_name_occ() == "Wizards of High Sorcery"))
    {
            if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothixen"))
             {
		tell_room(environment(this_player()), QCTNAME(this_player()) + 
                " searches through the scroll rack, looking for " +
                "something of interest.\n", ({ this_player() }));

		return ("You don't find anything in the scroll rack of " +
                "interest.\n");
              }

             if(!this_player()->query_prop(SOHM_I_SEARCH_BOOKSHELF))
             {
                 tell_room(environment(this_player()), QCTNAME(this_player()) + 
                 " searches through the scroll rack, and finds " +
                 "something of interest!\n", ({ this_player() }));

                 scroll = clone_object("/d/Krynn/common/scrolls/prot_fire_scroll");
                 scroll->move(this_player());

	         this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, 1);

	          return ("You search through the scroll rack for anything " +
                  "of interest. What is this? You come across an ancient scroll!\n");
             }

    }

    tell_room(environment(this_player()), QCTNAME(this_player()) + 
        " searches through the scroll rack, looking for " +
        "something of interest.\n", ({ this_player() }));

    return ("You search through the scroll rack for anything of interest. " +
            "You don't uncover anything.\n");
 
}

string
paper_descr()
{
   string ret_str;

   ret_str = "Going through the papers on the desk, ";

   tell_room(TO, QCTNAME(TP) + " looks through some papers on the " +
             "desk.\n", TP);

   if((page_found) && (!P("_diary_page_", TO)))
   {
      ret_str += "you find nothing of any real value to you, only " +
                 "papers written in languages you do not understand.\n";

      return ret_str;
   }

   ret_str += "you discover an old piece of paper, with faded writing " +
              "on it. It is written in a language you understand. " +
              "Quickly you take the old piece of paper.\n";

   clone_object(POBJ + "diary_page")->move(TP);
   TP->add_prop(I_FOUND_DIARY, 1);
   page_found = 1;

   return ret_str;
}
