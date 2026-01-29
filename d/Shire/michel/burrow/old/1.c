inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 MICH_DIR + "gamroad1","out",0,1
#define EXIT2 MICH_DIR + "burrow/1a","south",0,1
#define EXIT3 MICH_DIR + "burrow/1b","north",0,1

void reset_room();
void make_hob();

static object hob;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 1; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This burrow is dug directly out of the White Downs, and "+
   "that is what gives this burrow its distinctive white walls and "+
   "floors.  The entryway is rather spartan with only a mat to wipe one's "+
   "feet and a solitary hook nailed to the wall for one's coat.  South seems "+
   "to lead to a parlor of some sort, and the main rooms of the smial lie "+
   "to the north.";

   add_item(({"walls","wall","floor","floors","white walls","white floors"}),
   "The white chalk of the White Downs is a fairly stable building material, "+
   "as this smial looks a few generations old but still kept up fairly well.\n");

   add_item(({"mat","entryway"}),
   "The mat is a dirty and obviously well-worn scrap of carpeting.\n");

   add_item(({"hook","solitary hook"}),
   "The brass hook nailed into the chalky white walls seems very strong, "+
   "though a little tarnished.\n");
   
   
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
    set_alarm(1.5,0.0,"make_hob");
   }
   	
}

void
make_hob()
{
   	hob = clone_object(ER_DIR +"npc/ghobbit");
   	hob->arm_me();
   	hob->move(TO);
}
