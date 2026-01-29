inherit "/std/room";

#include "defs.h"
#include "/d/Shire/open/herbsearch.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

/* Prototypes */
void reset_room();

void
create_room()
{
    set_short("garden");
    set_long(break_string(
      "This part of the garden is used to cultivate flowers. At least, "
    + "that is what you suppose those twigs are going to grow to be. "
    + "At the moment the twigs are far from beautiful flowers.\n", 70));

    add_item(({"twigs","flowers"}), break_string(
      "On closer inspection, some of the twigs have rosebuds. Perhaps "
    + "the twigs are the remnants of beautiful roses that have been "
    + "cut to sell on the market. Maybe some of them can be found "
    + "in the flowerbed in which the twigs stand.\n", 70));

    add_item(({"flowerbed", "bed"}),break_string(
      "The flowerbed is covered with small twigs which might grow "
    + "to become flowers in the future. On your first glance you "
    + "cannot make out anymore, but who knows what a search might "
    + "reveal?\n",70));

    add_prop(ROOM_I_INSIDE,0);

    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"flowerbed", "bed"}));
    add_herb_file(STAND_HERB + "pawnrose");

    add_exit(STAND_DIR + "farthing1.c","north");

    reset_room();
}

void
reset_room()
{
    int ran;
    object pouch, herb;

    /* Give out a pouch with a random herb */
    if (!present("pouch"))
    {
	pouch = clone_object(STAND_OBJ + "pouch");
	switch(random(5))
        {
	case 0:
	    herb = clone_object(STAND_HERB + "pawnrose");
	    break;
	case 1:
	    herb = clone_object(STAND_HERB + "huckleberry");
	    break;
	case 2:
	    herb = clone_object(STAND_HERB + "treemushroom");
	    break;
	case 3:
	    herb = clone_object(STAND_HERB + "parsley");
	    break;
	case 4:
	    herb = clone_object(STAND_HERB + "grass");
	    break;
	}
	herb->move(pouch);
	pouch->move(this_object());
    }

if (!present("herbalist"))
clone_object("/d/Shire/dunstable/npc/herbalist")->move(this_object());
}
