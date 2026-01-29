inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void reset_room();
void add_mustard();

#define EXIT1 MICH_DIR + "burrow/1c","east",0,1

static object mustard;

void
create_room()
{
   
   areaname  = "Michel Delving";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 10;				/*Type of room in the smial   */
   areatype   = "town";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "The shelves are filled with jars and boxes of food.";
   add_item("shelves",
	"The hobbits store their food here.\n");
   add_item("jars",
	"These jars are full of jams and relishes and other wonderful "
	+"things. You wouldn't feel right about stealing this food "
	+"though.\n");
    add_item("boxes",
	"These boxes contain lots of different types of food, used to "
	+"cook wonderful meals.\n");
    add_item("food",
	"Your mouth waters at the sight of all this food. However, "
	+"you decide to leave it alone.\n");
 
   add_exit(EXIT1);

   make_the_room();
   reset_room();
}

void
reset_room()
{
   if (!mustard)
   {
    set_alarm(0.5,0.0,"add_mustard");
   }
   	
}

void
add_mustard()
{
   	mustard = clone_object(MICH_DIR + "obj/mustard");
   	mustard->move(TO);
}


