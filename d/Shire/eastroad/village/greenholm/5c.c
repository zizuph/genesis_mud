inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/5b","southwest",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/5d","southeast",0,1
#define MIN_AWARE 15

void reset_room();
string do_search(object searcher, string str);

object bowl;

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 3;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "There is a large fireplace in the southern wall, and a window "
	+"set into the northern wall lets light into the room during the "
	+"day.";
   
   add_item("fireplace",
      "Not currently lit, you can imagine the cheery warmth that "
      +"would come from this large fireplace.\n");
   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");
   remove_item("table");
   remove_item("dining table");
   add_item(({"dining table","table"}),"@@describe_table");
   add_prop("_obj_s_search_fun","do_search");

   add_exit(EXIT1);
   add_exit(EXIT2);

   make_the_room();
   reset_room();
}

string
describe_table()
{
   string my_desc;
   if(!bowl)
   {   
     my_desc = "The fine oak dining table is well-taken care of, as "+
   "evidenced by its smooth warm polish and shine.  There is a heap "+
   "of dishes on the table, you might search the table to see if any "+
   "are of value.\n";
   }
 
   if(bowl)
   {
     my_desc = "The fine oak dining table is well-maintained and "+
    "kept spotless by the hobbits that live here.\n";
   }

   return my_desc;

}

void
reset_room()
{
   bowl = 0;
}

string
do_search(object searcher, string str)
{
   int awareness;

   awareness = searcher->query_skill(SS_AWARENESS);
   if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;
   if(!str || (str!= "dining table" && str != "table")) return 0;
   if(bowl) return 0;
   seteuid(getuid(TO));
   bowl = clone_object(MICH_DIR + "obj/mbowl");
   bowl->move(searcher,1);
   say(QCTNAME(searcher)+ " finds something on the table.\n");
    return "You find a "+bowl->short()+" on the table.\n";
}
