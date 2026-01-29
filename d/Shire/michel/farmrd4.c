inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void add_stuff();

void
create_er_room()
{
add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
    area = "outside of";
    areaname = "Michel Delving";
    land = "the Shire";
    areatype = 2;
    areadesc = "courtyard";
    grass = "green";

    extraline = "You stand in the courtyard of a farmhouse, "+
    "its white picket fence standing out against the green "+
    "grass. The house itself is two stories high and full of "+
    "windows, quite odd for a hobbit's abode."+
    " All around you, this farmer's acres stretch out, he must be "+
    "quite wealthy indeed. You could go in or follow the path back west.";

    add_item(({"courtyard","fence","grass","acres","acre"}),
      "The white picket fence looks recently painted and the courtyard "+
      "appears well-maintained. You doubt you could find "+
      "a single weed among the green grass.\n");

    add_item(({"abode","farmhouse","farm","house","stories","windows"}),
      "The farmhouse is painted a brilliant red color and the planks "+
      "seem undamaged by weather or the elements. The presence "+
      "of the upper floor is odd, since hobbits only sleep on the ground."+
      " The windows look locked, and in any case, too small for you "+
      "to enter.\n");

    add_exit(MICH_DIR + "farmhouse","in",0,1);
    add_exit(MICH_DIR + "farmrd3","southwest",0,1);

    add_stuff();
}

void
reset_shire_room()
{
    add_stuff();
}

void
add_stuff()
{

    object chicken, chicken2, chicken3, chicken4;

    if(!present("chicken"))
	chicken = clone_object(MICH_DIR + "npc/chicken");
    chicken->move(TO);

    if(!present("chicken2"))
	chicken2->add_name("chicken2");
    chicken2->move(TO);

    if(!present("chicken3"))
	chicken3->add_name("chicken3");
    chicken3->move(TO);

    if(!present("chicken4"))
	chicken4 = clone_object(MICH_DIR + "npc/chicken");
    chicken4->add_name("chicken4");
    chicken4->move(TO);

}
