/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_2f.c  Master Bedroom
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo
 *
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>
object door;

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("master bedroom");
    set_long("The master bedroom is one of the largest rooms in the house. " +
       "A great four posted bed rests against the southern wall beneath " +
       "large curtained windows. A chest of drawers can be seen against " +
       "the west wall. A cast iron bathtub sits upon a raised platform " +
       "against the eastern wall next to a large fireplace. Several paintings " +
       "and tapestries cover the walls. " +
       "The hardwood floor has been polished to a brilliant " +
       "sheen. The moldings are gilded in gold and bronze. \n");

    add_item(({"floor","hardwood floor"}),
       "The hardwood floor has been polished to a brilliant sheen. Its mouldings " +
       "are gilded in gold and polished bronze.\n");

    add_item(("bed"),"A large four posted bed supports two overstuffed " +
       "mattresses covered in silk sheets and soft wool blankets. " +
       "The wood frame and posts are made from a dark red wood " +
       "characteristic with the wood furnishing found within the house. " +
       "The deep colored woodgrain has been polished showing intricate " +
       "carvings of beautiful maidens riding unicorns about a wooded " +
       "glen. It looks quite lavish.\n");

    add_item(({"chest","chest of drawers","drawers"}),
       "The chest of drawers contains several various sized drawers. " +
       "The wood is made from a dark red wood with golden gilded edges.\n");

    add_item(({"curtains","windows"}),
       "Large single paned glass windows covered with heavy curtains to keep " +
       "the cold out.\n");
   
    add_item(({"paintings","painting","tapestry","tapestries"}),
       "Several lavishly decorated tapestries cover the walls. Some expensive " +
       "looking framed paintings hang from the walls.\n");


    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Eight crystal " +
       "lamps, two to a wall are evenly spaced around the room. In three of " +
       "the walls is a niche containing a statue, the fourth wall is dominated " +
       "by a large fireplace.\n");

    add_item(("bathtub"),"The cast iron bathtub looks heavy.\n");

    add_item(("fireplace"),"The large fireplace is used to heat the entire room.\n");
    
    
       
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_2ea_door");
       door->move(TO);
    
    
    reset_room();

}

