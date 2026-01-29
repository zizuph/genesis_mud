inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/2f","north",0,1

void reset_room();
void make_hob();
void make_bottle();

static object hob, bottle;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 6; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This bedroom has no actual beds in it, only piles of "+
   "down-filled pillows to rest on.  A doorway leads north.";

   add_item(({"pillows","pillow","down-filled pillows","piles"}),
   "These piles, though humble lodgings, look comfortable, and in "+
   "some places downright inviting.\n");
   
   add_exit(EXIT1);
   
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
    if(!present("bottle"))
   {
     set_alarm(1.2,0.0,"make_bottle");
   }   	
}

void
make_hob()
{
   	hob = clone_object(ER_DIR +"npc/bighobbit");
   	hob->arm_me();
   	hob->move(TO);
}

void
make_bottle()
{
   	hob = clone_object(MICH_DIR +"obj/bottle");
   	hob->add_prop(OBJ_I_HIDE, 10 + random(15));
   	hob->move(TO);
}
