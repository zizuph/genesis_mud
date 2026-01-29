inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
    set_short("Top of Elven Tower");
    set_long("   The top of this tower is bright and cheery. The room "+
             "has a roof with small windows. There are large windows "+
             "all about you. From here you can see the vast beautiful land of "+
             "Emerald. You can look in every direction to see Emerald. "+
             "Beneath each window is a bench. In the center of the room "+
             "there is a small circular pit for a fire. Above the pit, "+
             "is a hole for the ventilation of smoke. The stairs spirial down "+
             "from here.\n\n");   

    add_item(({"window","windows"}), "There are small and large windows.\n");
    add_item(({"large window","large windows"}), "The large windows circle the "+
            "room. Looking through the north, west, east, or south windows may "+
            "show a better look of Emerald.\n");
    add_item(({"bench","benches"}), "The benches are here for your relaxation. "+
            "They are made of maple and do not look very comfortable.\n");
    add_item(({"roof","small window","small windows"}), "The roof has small "+
            "windows which allows light to enter in the room.\n");
    add_item(({"pit"}), "The pit has a few burnt logs in it. It looks like they "+
            "havn't had to have a fire in it for a while.\n");
    add_item(({"emerald"}), "As you attempt to look at the beautiful land of "+
            "Emerald. You realize it might be easier to look in a direction.\n");
    add_item(({"hole"}), "The hole is in the ceiling.  It allows ventilation of "+
            "the smoke caused by the fire.\n");
    add_item(({"stairs", "stair"}), "The stairs spirial down.\n");
    add_item(({"west window","west windows"}), "As you look through the west "+
            "window you can see, a large island. The island is surrounded by "+
            "mist and is too difficult to make out any features of the island.\n");
    add_item(({"north window","north windows"}), "As you look through the north "+
            "window you can see, a large mountain and a volcano.\n");
    add_item(({"south window","south windows"}), "As you look through the south "+
            "window you can see, a large vast forest, and a city.\n");
    add_item(({"island", "mist"}), "From this view point all you can see of the "+
            "island is just that.  Its an Island covered with mist.\n");
    add_item(({"mountain"}), "The mountain is black and surrounded by a thick "+
            "swirrling mist.\n");
    add_item(({"volcano"}), "The volcano appears to be an active volcano. There "+
             "is thick clouds of smoke and steam rising from the crater.\n");
    add_item(({"forest"}), "The forest is a rich green. Years of growth can be "+
             "seen from here. The trees stand tall and strong.\n");
    add_item(({"city"}), "The city you see is Telberin. Its a beautiful city "+
             "with a castle.  Perhaps you should go visit it.\n");

    add_exit(VILLAGE_DIR + "stairs2", "down",);

}
