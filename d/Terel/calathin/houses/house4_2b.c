/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4f.c
 * Calathin external house.
 * 09/30/1999 -- TOMAS
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
    set_short("guest room");
    set_long("The guest room looks quite comfortable. " +
       "A bed and headboard sits against the west wall. " +
       "Large windows concealed by heavy drapes cover " +
       "the south wall. A fireplace and two overstuffed " +
       "chairs can be seen against the north wall.\n");

    add_item(({"bed","headboard"}),
       "The bed looks very comfortable to sleep in. The mattress " +
       "has been stuffed with goosefeathers. Then covered with " +
       "cloth linens and a soft wool blanket. " +
       "The headboard was carved from a rich looking woodgrain.\n");

    add_item(({"fireplace"}), "The large fireplace keeps the room " +
       "warm and dry.\n");

    add_item(({"chair","chairs"}),"Two overstuffed chairs rest before " +
       "the fireplace.\n");

    add_item(({"windows","curtains"}),"The large windows are concealed " +
       "behind heavy drapes to keep the cold out.\n");

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
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_2aa_door");
       door->move(TO);


    reset_room();

}

