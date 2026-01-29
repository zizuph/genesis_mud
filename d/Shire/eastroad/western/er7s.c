#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

object herbalist;

void
create_er_room()
{
    area = "outside of";
    areaname = "Michel Delving";
    land = "Shire";
    areatype = 1;
    areadesc = "meadow";
    grass = "green";

    extraline = "The White Downs are just to the east, but here in the "+
    "valley between the Far and White Downs, the very land smells fresh. "+
    "Michel Delving lies east of here; north and west are the Greenholm.";

    add_item(({"white downs"}),
      "As you examine the White Downs off in the distance, it is very plain "+
      "how they got their name- they are as white as the purest sand, and "+
      "they are either made of that or of chalk, you can't tell which from here.\n");

    add_item(({"far downs"}), "The Far Downs are on the other side of this "+
      "wide lush valley.\n");

    add_item(({"valley","land","wide lush valley"}),
      "The valley between the Far and White Downs is wide and lush, very good "+
      "for farming.\n");

    add_prop(ROOM_I_NO_ATTACK, 1); 
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    set_noshow_obvious(1);
    add_exit(EAST_R_DIR + "er7","north");
    add_exit(EAST_R_DIR + "er6s","west");   

    reset_shire_room();
}

void
reset_shire_room()
{

    int ran;
    object herb, pouch;

    /* Give out a pouch with a random herb */
    if (!present("pouch"))
    {
	pouch = clone_object("/d/Gondor/common/obj/herbpouch");
	switch(random(5))
	{
	case 0:
	    herb = clone_object(HERB_DIR + "pawnrose");
	    break;
	case 1:
	    herb = clone_object(HERB_DIR + "huckleberry");
	    break;
	case 2:
	    herb = clone_object(HERB_DIR + "treemushroom");
	    break;
	case 3:
	    herb = clone_object(HERB_DIR + "parsley");
	    break;
	case 4:
	    herb = clone_object(HERB_DIR + "grass");
	    break;
	}
    herb->move(pouch, 1);
	pouch->move(this_object());
    }

   if (!objectp(herbalist))
    {
	herbalist = clone_object(ER_NPC + "herbalist");
/*
   herbalist->set_restrain_path(({"/d/Shire/eastroad/western"}));
   herbalist->set_random_move(2);
*/
   herbalist->set_monster_home("/d/Shire/eastroad/western/er7s");   
   herbalist->add_prop(OBJ_I_NO_ATTACK, 1); 
   herbalist->add_prop(OBJ_I_NO_MAGIC_ATTACK, 1); 
	herbalist->move(this_object());
    }
}
