inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/2","north",0,1
#define EXIT2 MICH_DIR + "burrow/2c","southeast",0,1
#define EXIT3 MICH_DIR + "burrow/2f","southwest",0,1

void reset_room();
void make_hob();

static object hob, hob2, hob3;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 2; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "The parlor room is the center of this burrow- here "+
   "corridors branch off towards the kitchen and the bedroom areas. "+
   " In the middle of the western wall is a large fireplace which "+
   "provides, heat, light and entertainment.";

   add_item(({"western wall","wall","fireplace","large fireplace"}),
   "The fireplace on the western wall is lit and glowing with the "+
   "intensity of a newly lit fire.\n");

   
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   
   make_the_room();
   reset_room();
}

void
reset_room()
{
   if (!hob)
   {
    if(random(2))
    {
     set_alarm(1.5,0.0,"make_hob");
   }
 }  	
}

void
make_hob()
{

   	hob = clone_object(ER_DIR +"npc/wehobbit");
   	hob->arm_me();
   	hob->move(TO);

   	hob2 = clone_object(ER_DIR +"npc/ghobbit");
   	hob2->arm_me();
   	hob2->move(TO);

   	hob3 = clone_object(ER_DIR +"npc/bighobbit");
   	hob3->arm_me();
   	hob3->move(TO);

}
