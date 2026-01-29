/* created by Zizuph 09/2021 */

#include "../local.h"

inherit CITY_ROOMBASE;

object desk;

object official;

void
reset_palan_room()
{
    seteuid(getuid(TO));
    if (!desk)
    {
        desk = clone_object(OBJ + "thau_desk");
        desk->move(TO);
    }
    if (!official)
    {
        official = clone_object(LIV + "thaumaturgist");
        official->move_living(0,TO);
    }
}


public int check_warn()
{
    if (this_player()->query_prop("_thau_in_transformation"))
    {
        this_player()->remove_prop("_thau_in_transformation");
        if (official)
        {
            official->command("say If you try to move again, you will " +
                "lose both the transformation and your money.");
            return 1;
        }
    }
    if (this_player()->query_prop("_thau_in_racechange"))
    {
        this_player()->remove_prop("_thau_in_racechange");
        if (official)
        {
            official->command("say If you try to move again, you will " +
                "lose your race change.");
            return 1;
        }
    }
    return 0;
}

void
create_palan_room()
{
    set_short("Thaumaturgy");
    set_long("This is the Thaumaturgist's office, the place where wonders "
	      + "are worked. You would be forgiven for thinking that this room "
		  + "is rather boring for a place where miracles are supposedly "
		  + "wrought, for it is very similar to all the other offices you "
		  + "have passed in the building. There are cupboards filled "
          + "with books here, as well as a grand desk. You can see a "
          + "few chairs stationed facing the desk, and a big X painted "
		  + "on the floor in the center of the room.\n");

    add_exit(PALACE + "hall6","west",check_warn,0);

    add_item(({"cupboards", "cupboard"}),
            "They are made of wood that bows in some places under the "
		  + "weight of many precious books, while others are stuffed "
		  + "nearly to over-flowing with baskets and bins and little "
		  + "pouches of mysterious ingredients.\n");
    add_item(({"books", "book"}), 
	        "They are mostly stacked neatly in the cupboard, but some "
		  + "are open, balanced atop other books. All of them are "
          + "safely out of the reach of prying eyes like yours.\n");
	add_item(({"x", "floor", "painting on the floor"}),
	        "You can see a big white X painted on the floor, and "
		  + "scuff marks from many boots resting on either side of "
		  + "where the arms of the X cross.\n"); 
	
    add_prop(ROOM_M_NO_ATTACK, "The magic in this room makes it a " +
        "dangerous place for combat.\n");
    reset_palan_room();
}
