
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("At the top of a steep stairway");
  set_long("A long, narrow staircase decends eastward. "+
     "The staircase is only wide enough to accomodate two "+
     "people walking abreast. The steps are high and shallow "+
     "making for a steep journey downwards. The walls offer no "+
     "support. The staircase plunges down into the darkness "+
     "to the east while a low tunnel leads westwards.\n");

  add_item(({ "staircase", "stairway" }),
     "Certainly one of the steeper ones you've seen. One slip "+
     "could send you tumbling all the way down to your death.\n");
  add_item(({ "steps", "step", "stairs", "stair" }),
     "They are each two feet high by one foot deep.\n");
  add_item(({ "wall", "walls" }),
     "These dark stone walls are fairly smooth. A few cracks "+
     "can be seen marring its surface.\n");

  add_exit("/d/Shire/khazad/west/wd1","west",0,1);
  add_exit("/d/Shire/khazad/west/wd3","down",0,5);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/wd3")
    ob->catch_msg("You laboriously climb the treacherous stairs.\n");
}
