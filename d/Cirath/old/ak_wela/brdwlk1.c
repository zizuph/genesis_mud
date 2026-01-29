inherit "/d/Cirath/ak_wela/inherit/outside";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("A busy, crowded boardwalk near the docks.");
    set_long("The northern end of the boardwalk offers a beautiful view " +
        "of the ocean to the north and east.  The coastline to the north " +
        "first makes a shallow dip to the west, then rises into pale " +
        "white cliffs as it once again turns east, where it fades away " +
        "in the distance.  The beautiful sight is only slightly spoiled " +
        "by the raucous patrons of the establishment to the west, and by " +
        "the female 'employees' who are waving and smiling at the crowds " +
        "of sailors here on the docks.  The beach north of here seems " +
        "to offer a much calmer and quieter atmosphere in which to enjoy " +
        "the beauty of this area.  The northernmost pier lies to the " +
        "east, and the boardwalk continues south.\n");

    add_exit(AK_WELA_DIR + "pier1", "east", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "saloon", "west", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "n_beach1", "north", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "brdwlk2", "south", 0, 2 /* crowds */ );

    add_item(({ "view", "coastline", "cliffs" }), "The view of the " +
             "coastline is simply breathtaking.  The chalk cliffs seem to " +
             "almost glow in the sunlight.\n");
    add_item(({ "prostitutes", "employees", "women", "ladies" }),
             "These 'ladies of the evening' don't seem to care what " +
             "time it is.  They are looking for company, and your " +
             "coinpurse might suffice!\n");

    ::create_room();
}
