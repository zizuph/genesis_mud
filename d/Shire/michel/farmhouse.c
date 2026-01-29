inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>


create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   set_short("A farmer's house");
   set_long("You have entered a big red farmhouse and "+
   "the inside is pretty much what you expected. A sink "+
   "stands in the corner opposite the barnyard exit and a table and set "+
   "of chairs is arranged neatly in the middle of the room. "+
   "You can go out to the courtyard or to the barnyard if you like. "+
   "The light coming from the table lamp is very bright.\n");

   add_item(({"sink","corner","table","chairs","chair"}),
   "The sink in the corner is piled with dirty dishes, it "+
   "seems there has been no one there to wash them for quite a "+
   "long time. The table and chairs look undisturbed by this, "+
   "however.\n");

   add_item(({"courtyard","barnyard"}),
   "The courtyard is outside and leads back towards "+
   "Michel Delving. To go further into the farm, follow your "+
   "nose towards the barnyard.\n");
   add_item(({"lamp","table lamp","lamp on the table"}),
   "The table lamp is lit and seems securely mounted to "+
   "the surface of the table.\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 4);
   add_exit(MICH_DIR + "barnyard","barnyard",0,1);
   add_exit(MICH_DIR + "farmrd4","out",0,1);

reset_room();
}
reset_room()
{
     add_stuff();
}
void
add_stuff()
{
   object farmer;

   if(!present("farmer"))
   {
   farmer = clone_object(MICH_DIR + "npc/farmer");
   farmer->command("wear all");
   farmer->command("wield all");
   farmer->move(TO);
   }

}
