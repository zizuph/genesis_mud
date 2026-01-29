inherit "/d/Shire/eastroad/std/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 GREEN_DIR + "vill3","west",0,1

void reset_room();
void make_hob();

static object hob;

void
create_smial()
{
   
   areaname  = "Greenfields"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 1; /*Type of room in the smial   */
   areatype   = "hamlet"; /*Type of village*/
   smialsize   = "very small"; /*Size of the house*/
   
   extraline = "This very small burrow does not appear to have any other rooms. "+
   " It is the office of the Shirriffes of the Shire, North Farthing, division.  Usually "+
   "there is a Shirriffe here to assist you.  West is the hamlet of Greenfields.";

   add_item(({"office"}),
   "A typical office, it is equipped with a large desk filled with papers and a "+
   "nice comfortable chair next to it.\n");

   add_item(({"desk","large desk","papers","paper"}),
   "The large oak desk is covered with papers which look like love letters.\n");

   add_item("letters","The letters are personal, and you think the Shirriffe would "+
   "be very angry if he caught you reading them.\n");

   add_item(({"chair","nice comfortable chair","comfortable chair"}),
   "The chair is made of a strong birch and padded with a heavy down pillow.  "+
   "The middle of the pillow is depressed, as if someone had been sitting on it "+
   "for a long time.\n");
      
   add_exit(EXIT1);
   
   reset_room();
}

void
init()
{
   ::init();
   add_action("do_read","read");

}

int
do_read(string str)
{
   object shirriffe;

  if(!str)
  notify_fail("Read what?\n");

  if(str != "letters")
     notify_fail("Read what?\n");

   shirriffe = present("puddifoot",TO);
   if(shirriffe)
   {
    shirriffe->command("kick "+TP->query_real_name());
    shirriffe->command("say Those are personal, keep out of them.");
    return 1;
   }

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
   	hob = clone_object(GREEN_DIR + "npc/shirriffe");
   	hob->arm_me();
   	hob->move(TO);
           tell_room(TO, "A Shirriffe looks up at you from behind his desk.\n");
}
