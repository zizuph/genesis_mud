inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/ut/1d","north",0,1
#define MIN_AWARE 15

void reset_room();
static object hob;
static object cloth;

void
create_room()
{
   
   areaname  = "Undertowers";		/*Name of village*/
   land          = "Westmarch";		/*Name of land   */
   roomtype  = 5;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
    
   add_exit(EXIT1);


   extraline = "This master bedroom is adorned in lush carpeting of "+
   "the richest forest green, and decorated on the walls by numerous "+
   "portraits and even a mirror.";

   add_item(({"carpet","carpeting","green carpet"}),
   "The carpet is as green as the forest floor.\n");

   add_item(({"portrait","portraits"}),
   "The portraits are obviously of family members, and "+
   "if you are not a hobbit, you would find them ugly.\n");
   add_item("mirror","You see yourself and some furniture behind "+
      "you.\n");
   add_item("furniture","A bed and a dresser are the only pieces "+
      "of furniture here.\n");

   add_item(({"window","view"}),
	"Looking out the window, you can see the peaceful "
	+areatype+" of "+areaname+".\n");
   remove_item("dresser");
   remove_item("dressers");
   add_item(({"dresser","dressers"}),"@@dresser_desc");
   add_prop("_obj_s_search_fun","do_search");
   reset_room();
   make_the_room();
}

void
reset_room()
{
    cloth = 0;

   if(!hob)
   {
    hob = clone_object(ER_BASE_DIR + "npc/bighobbit");
     hob->arm_me();
     hob->move(TO);
    }

}


string
dresser_desc()
{
   string my_desc;

   if(cloth)
   {
     my_desc = "The dresser is closed tightly and kept neatly.\n";
    }

    if(!cloth)
    {
      my_desc = "The dresser is closed tightly and kept neatly. "+
      "You wonder what kind of goodies it contains.\n";
     }

    return my_desc;
}


string
do_search(object searcher, string str)
{
   int awareness;

   awareness = searcher->query_skill(SS_AWARENESS);
   if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;
   if(!str || (str!= "dresser" && str != "dressers")) return 0;
   if(cloth) return 0;
   seteuid(getuid(TO));
   cloth = clone_object(MICH_DIR + "obj/cloth");
   cloth->move(searcher,1);
   say(QCTNAME(searcher)+ " finds something in the dresser.\n");
    return "You find a "+cloth->short()+" in the dresser.\n";
}
