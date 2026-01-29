#pragma save_binary

inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include "hobbit.h"

static object hob, chair;

void reset_room();

void
create_room()
{
   add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");

    set_short("Entrance hall");
    set_long("This is the entrance hall of the Adventuresome Hobbits "+
      "guild.  Lining the walls are maps of far-off and not so far-off lands. "+
      "Farther south is the guildhouse proper and east lie the fields near "+
      "Michel Delving.\n");

    add_item(({"wall","walls","map","maps","lands","land"}),
      "The walls are completely covered in maps of far away lands.\n"+
      "To see one closer, examine them one by one- first map, second map.\n"+
      "There are in all, six maps.\n");

    add_item(({"first map","first"}),
      "At the top of the map you see a name, Hobbiton, written in a messy "+
      "script.  Other names connected by faint lines include Michel Dlvg, "+
      "Frogm, Bywater, and Waym.\n");

    add_item(({"second map","second"}),
      "The legend of this map reads: Gondor, the land of Stone.\n"+
      "At the center is a name, M. Tirith, and it connects by black "+
      "lines to dots titled O, Pel, Ed and M. Morgul.\n");

    add_item(({"third map","third"}),
      "The legend of this map reads: Bree, and the lands beyond the Shire.\n"+
      "It has lines pointing towards an arrow titled Shire, and dots named "+
      "Riven., Isengard, Edoras, and M.Mts.\n");

    add_item(({"fourth map","fourth"}),
      "This map is more general and is titled: Shire.\n"+
      "Dots on it include: Bree, Frogmorton, Michel Delving, Gamwich, "+
      "Waymeet, The Marish, Buckland, Hobbiton, Bywater, Long Cleeve, "+
      "Greenfields, Scary, Tighfield, Annum., Bree, Staddle, Archet, "+
      "Forn., Tookbank, Sackville, Rushy, Stock and Longbottom.\n");

    add_item(({"fifth map","fifth"}),
      "This map is titled: MiddleEarth.\n"+
      "Names that catch your eye on it are:\n"+
      "Hobbiton, Bree, Shire, Elf-king, Mirkwood, Lonely Mountain, "+
      "Dale, Mordor, M. Morgul, M. Tirith, Ithilien, Anorien, Rohan, "+
      "Edoras, Isengard, Fangorn, Anduin, Misty Mountains, Moria "+
      "Blue Mts, Mithlond, and an arrow pointing west of Mithlond "+
      "titled 'Ersea'.\n");

    add_item(({"sixth map","sixth"}),
      "This map is obviously incomplete as it has no names or lines on it, "+
      "just a figure of land shaped like a five-pointed star.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,"No fighting, please!\n");

    add_exit(HOBGLD_DIR + "party", "west", 0, 1);
    add_exit(HOBGLD_DIR +"join","south","@@test_quest@@");
    add_exit(MICH_DIR + "gamroad4","east",0,1);

    reset_room();  
}

int
test_quest()
{
    /*
       if(!TP->test_bit("Shire",WESTERN_GROUP, HOBBIT_ENTRANCE_BIT))
       {
	 write("You have not proved your adventuresomeness yet.\n");
	 write("You are not allowed entrance at this time.\n");
	 return 1;
       }
    */

    write("Welcome to the Adventuresome Hobbits Guild.\n");
    return 0;

}

void  
reset_room()
{ 
    if (!hob)
    {
	hob = clone_object(HOBGLD_DIR + "doorhobbit");
	hob->move(TO);
    }

    if(!chair)
    {
	chair = clone_object(MICH_DIR + "mathom/obj/chair");
	chair->move(TO);
    }
}
