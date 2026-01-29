/*
 *  /d/Gondor/morgul/city/mm_stables/court.c
 *
 *  The stable court of the stables of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/std/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "mm_stables.h"

void
create_room()
{
    ::create_room();
    
    set_short("In the stable court of Minas Morgul");
    set_long("The archway opens up in a cobbled yard which serves as the " +
             "stable court of Minas Morgul. The ground here is largely " +
             "covered with a muddy mixture of hay, horse-droppings and " +
             "dirt, muffling the sound of scurrying feet. Several groups " +
             "of swarthy men are to be seen around the court, piling hay, " +
             "carrying equipment and exercising horses. A chariot rests " +
             "against the south wall of the court. To the north, you see " +
             "a very large, run down building. In the east end of the " +
             "court you see a somewhat smaller building, guarded by " +
             "two swarthy men.\n");
    
    add_item(({"steed", "steeds"}),
              ("The horses currently out on the court seem sound enough of " +
               "feet and stature, but do not strike you as war horses. " +
               "Perhaps they are employed rather for scouting and " +
               "messaging purposes. As you look at the horses, however, " +
               "a chilling neigh fills the courtyard. You are certain that " +
               "it did not come from any the horses before you.\n"));
    
    add_item(({"men"}),
              ("The men are all Easterlings, identifiable as such by their " +
               "short, but broad stature and their dark skin. Judging by " +
               "their dress and equipment, they are most likely more than " +
               "mere stablehands. Even now, as you look straight at them, " +
               "they seem to take little notice of you.\n"));
    
    add_item(({"chariot"}),
              ("It is a very old chariot, old enough to have been employed " +
               "by many an Easterling chieftain on their raids. Now, its " +
               "detachable body rests against the south wall. A yoke hangs " +
               "loosely from a long shaft. The leather straps around it " +
               "seem worn, but still hold the yoke and shaft together. " +
               "The yoke has an ornate central knob, and its outer ends " +
               "are fitted with rings to guide the outside reins. Three " +
               "gilded wheels, one of which is broken, are stacked against " +
               "the cart.\n"));
    
    add_item(({"building", "buildings"}),
              ("Which building do you want to look at, the large or the " +
               "small one?\n"));
    
    add_item(({"large building"}),
              ("Considering the number of horses being led into and out " +
               "from this wooden building, you conclude it must be the " +
               "main stable. The structure is simple, if not primitive. " +
               "The somewhat extended gables, and a massive ridgepole " +
               "running along the roof seem to weigh down hard on the " +
               "building, in spite of its size.\n"));
    
    add_item(({"small building", "guarded building"}),
              ("The building consists of two bodies, the second of which " +
               "juts out like a pier to the south of the first, smaller " +
               "wing. The building lacks windows, you notice, and seems " +
               "possible to enter only through the first of its two " +
               "bodies. On the other hand, the entrance is big enough " +
               "to admit a mounted rider. A large black banner hangs " +
               "across the facade.\n"));
    
    add_item(({"guard", "guards"}),
              ("These guards look like fierce fighters, but even so they " +
               "seem uneasy somehow.\n"));
    
    add_item(({"banner"}),
              ("The black banner which hangs across the facade of the " +
               "guarded building is adorned with the Red Eye. The Eye " +
               "is rimmed with fire, but glazed like a cats. Its pupil " +
               "is slit.\n"));
    
    add_prop(ROOM_I_INSIDE, 0);
    
    add_exit("archway.c", "west", 0, 0);
    add_exit("office.c", "east", 0, 0);
    add_exit("stable.c", "north", 0, 0);
}
