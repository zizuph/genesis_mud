
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>

void
create_moria_room()
{
  set_short("Top of stairway");
/*
  set_long("You stand at the top of a staircase. Two pillars "+
     "of grey stone support a slab of black rock forming a "+
     "portal through which a tunnel proceedes eastward. "+
*/
  set_long("Stairs descend westwards while to the east a high "+
  "arch signals the beginning of a central passageway.\n");

  add_item(({ "stairs", "staircase", "stairway", "steps" }),
     "The steps are smooth and worn down.\n");
  add_item(({ "archway", "arch" }),
     "A massive stone archway carved out from the surrounding rock. "+
     "It appears to have some form of writing on it.\n");
  add_item("writing",
     "Perhaps you could read it.\n");
     /* If race = dwarf or language skill is high enuf the writing */
     /* should be readable. Something along the lines of who made it */
     /* or perhaps an account of balin passing this way. */
  add_item(({ "passageway", "passage" }),
     "It runs straight away east while slanting upwards slightly.\n");
  add_exit("/d/Shire/khazad/west/stairs","down",0,3);
  add_exit("/d/Shire/khazad/west/wp1","east",0,1);
}
