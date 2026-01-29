/*
The corral.  Terel horses are kept here

Trofast 4-1999

 */


#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>

#define MAX_HORSES 6

inherit STDROOM;

#include <stdproperties.h>

//Function prototypes
void    reset_room();
string  long_desc();
string  climb_fence();
int     dump();

/*
 * Function:     reset_room
 * Description:  At reset, check how many horses for sale remain, and
 *               add more if need be, up to MAX_HORSES 
 */

void
reset_room()
{
  int i;
  object horse, jonas, stable_yard;
  object *horses;


  horses = filter(all_inventory(), &->id("terel_ass_pony"));                       
  if (sizeof(horses)>=MAX_HORSES)
    return;
  
  tell_room (TO, "Suddenly the corral door swings open, and two wranglers "+
	     "bring in some more horses.\n");

  for (i=MAX_HORSES;i>sizeof(horses);i--)
    {
      horse=clone_object(CALATHIN_DIR+"npc/terel_horse.c");
      horse->move(TO);
      tell_room(TO, "A "+horse->short()+" joins the herd.\n");
    }
  tell_room(TO, "With a dusty grin, one of the wranglers slams the corral "+
	    "door shut.\n");

}


/*
 * Function:     long_desc
 * Description:  give a variable long if there are horses or not.
 */

string
long_desc()
{
  object *horses;
  string desc = "A large, fenced pasture.";

  horses = filter(all_inventory(), &->id("terel_ass_pony"));                       
  if (!sizeof(horses))
    {
      return desc+" The hard-packed dirt ground here shows many signs of "+
	"hoofprints.  There are no horses here at present, however.\n";
    }
  

  return desc+" The horses here belong to the stable.\n";


}


/*
 * Function:      climb_fence
 * Description:   no obvious exit to get out, "climb fence" instead
 */
string
climb_fence()
{
if (TP->query_skill(SS_CLIMB) > 35)
  {

    write("You put one foot on the lower plank, grab the top "+
      "of the fence and heave yourself over.\n");

    TP->move_living("climbing over the fence", 
		    CALATHIN_DIR+"stable_yard.c",
		    1,
		    0);
    return "";

  }
else return "The fence is too high for you to dare climb.\n"; 
}



create_room()
{
  set_short("The corral");
  set_long(long_desc);

  add_prop(ROOM_I_ALLOW_STEED,1);
  add_item("fence",  "A high fence made of thick wooden planks.\n");
  
  add_cmd_item("fence","climb",climb_fence);
  reset_room();
}

int
dump()
{

object *horses;

horses = filter(all_inventory(), &->id("terel_ass_pony"));                       
write ("The size of the array is "+sizeof(horses));
dump_array(horses);
}
