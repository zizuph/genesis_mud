/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_2c.c
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
object servant = 0;

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("guest bedroom");
    set_long("This is the largest of the two guest bedrooms. " +
       "Without a doubt the most important thing in this room is the massive " +
       "bed placed against the center of the far wall. To the left of the door " +
       "is a table and two comfortable plush chairs. Dominating one wall is a " +
       "tapestry. Against the opposite wall is a fireplace with an armoire " +
       "to either side of it.\n");


    add_item(({"round table","table"}),
       "The round table is made of a dark red wood which has been " +
       "polished and cured forming almost mirror like quality.\n");

    add_item(({"chair","chairs","plush chair"}),
       "These high back plush chairs look very comfortable. Over the back " +
       "of each chair is a blanket so that the person using the chair can " +
       "keep warm while sitting.\n");

     add_item(({"large fireplace","fireplace"}),
       "The fireplace is placed into the northern wall. The mantle " +
       "is made of a single piece of dark red wood.\n");

    add_item(("tapestry"),
       "The tapestry is hanging on the southern wall. It covers the window and " +
       "helps prevent drafts and cold air from coming inside. The tapestry itself " +
       "is a dark redish brown color with a white knotwork pattern. It hangs from " +
       "a brass rod that allows it to be pulled aside when weather permits.\n");

    add_item(("bed"),"This bed is a massive piece of furniture. At each corner " +
       "is a tall wooden post, at the top of each post are beams that connect " +
       "the posts together. A large heavy cloth has been draped over the " +
       "beams and hangs down to the floor on all four sides. The posts have " +
       "been stained the same reddish tint that dominates the rest of the house. " +
       "The cloth and bedcovering are a light crimson.\n");

    add_item(("floor"),"The hardwood floor has been waxed and polished " +
       "to a high sheen.\n");

    add_item(({"armoire"}),
       "To either side of the fireplace rests an armoire. They are black enameled " +
       "with mother of pearl inlaid knotwork patterns.\n");

    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Crystal " +
       "lamps, two to a wall are evenly spaced around the room provide " +
       "ample light.\n");


    add_cmd_item("armoire","open","You open the armoire finding " +
                                  "nothing but and assortment of clothes " +
                                  "that doesn't fit your taste and decide " +
                                  "to close it.\n"); 


    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Eight crystal " +
       "lamps, two to a wall are evenly spaced around the room. In three of " +
       "the walls is a niche containing a statue, the fourth wall is dominated " +
       "by a large fireplace.\n");

    
    

    add_cmd_item(({"book"}),
                 ("read"),
                 ("You would rather not, there isn't a bed nearby and " +
                  "no doubt reading this would put you to sleep in " +
                  "short order.\n"));
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_2da_door");
       door->move(TO);


    reset_room();

}

void
reset_room()
{    
  
    if(!servant)
    {
       servant = clone_object(CALATHIN_DIR + "houses/npc/servant");
       servant->move(TO);
         
    }
}
