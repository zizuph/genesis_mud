
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room() 
{
  set_short("On a steep stairway");
  set_long("You precariously stand upon a high, shallow step. The "+
     "dark stairway runs under an arched ceiling parallel with the "+
     "steps. Yellowed bones are scatterd among the rubble that "+
     "litters the steps here. A rotting stench lingers upon "+
     "these stairs. The staircase rises to the south and "+
     "descends steeply to the north.\n");
 
  add_item(({ "bones", "yellowed bones" }),
     "From the looks of it these have been here a while. They "+
     "appear to be from some type of humaniod.\n");
  add_item(({ "rubble", "debris" }),
     "Pieces of broken armours and weapons are strewn around here. "+
     "A great struggle took place here.\n");
  add_item(({ "broken weapons", "broken armours", "weapons", "armours" }),
     "Useless weapons and armours litter the steps.\n");
  add_item(({ "staircase", "stairway" }),
     "Certainly one of the steeper ones you've seen. One slip "+
     "could send you tumbling all the way down to your death.\n");
  add_item(({ "steps", "step", "stairs", "stair" }),
     "They are each two feet high by one foot deep.\n");
  add_item(({ "wall", "walls" }),
     "These dark stone walls are fairly smooth. A few cracks "+
     "can be seen marring its surface.\n"); 
  add_item("ceiling",
     "It is arched in the form of a semi-circle.\n");
 
  add_exit("/d/Shire/khazad/west/wd5","up",0,5);
  add_exit("/d/Shire/khazad/west/wd8","down",0,5);
}
 
public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/wd5")
  {
    ob->catch_msg("You laboriously make your way down the "+
      "treacherous stairs to the north.\n");
  }
 
  else if (file_name(from) == "/d/Shire/khazad/west/wd8")
    ob->catch_msg("You laboriously climb the treacherous stairs.\n");
}
