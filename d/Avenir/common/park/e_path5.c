// file name: /d/Avenir/common/park/e_path5.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
//		Sirra added the wolf bone functions March 1998.
// purpose:     Search a bit, find some herbs, find the toe bone
//		    to the wolf quest in the wall.
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Avenir/common/park/park.h"
#include "/d/Avenir/common/holm/wolf.h"

string do_search(object player, string str);
int found;

void
create_room()
{
    set_short("Wide dirt path");
    set_long("You are standing on a wide, well-marked dirt"
        +" path which curves here to lead from north to southwest."
        +" Heavy foliage surrounds the path on both sides, and the"
        +" remnants of low stone walls can be seen. Vines strewn across"
        +" your way and persistently snagging weeds serve to"
        +" impede your progress.\n");

    add_item(({"wall","walls","stone"}),"The walls that border the path are " 
        +"too high to see over, but through cracks in the stones you can "
    	  +"see thick and fierce vegetation growing. Something white "
	  +"appears lodged in the stone.\n");

    AE(PK+"e_path6","north",0);  
    AE(PK+"e_path4","southwest",0);

    add_prop(ROOM_I_LIGHT,1);IN

    ECANOPY EVINE EPATH COURTLIGHT COURTCEILING

    set_search_places(({"vines","vine","underbrush","weeds","weed"}));
    add_prop(OBJ_I_SEARCH_TIME,2);

    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_herb_file(SHIRE+"huckleberry");
    add_herb_file(SHIRE+"parsley");
    add_herb_file(GONDOR+"blung");

    reset_room();
}

//This is a masked search_herb() copied straight from 
//~Avenir/common/herb/herbsearch.h. It is masked to 
//include the toe bone (TOE_ID) for the wolf quest.

string 
do_search(object player, string str)
{
    string  place,
           *herb_names = ({}),
            this_herb;
    int     i;
    object bone;

    if (!places)
        places = ({"here","ground"});

    if (sscanf(str,"%s for %s", place, this_herb) == 2
        && member_array(place,places) >= 0)
    {
        if (this_herb == "herbs")
            return this_object()->search_for_herbs(player);

        for (i = 0; i < sizeof(herbs); i++) 
            herb_names += ({ herbs[i]->query_herb_name() });
        if ((i = member_array(this_herb, herb_names)) > -1)
            return this_object()->search_for_herbs(player, herbs[i]);
    }

    if (str == "wall" || str == "walls" || str == "stone")
    {
	  if (found <1)
	  return "";

	  found--;

	  bone = clone_object(WOLF_BONE + "toe.c");
	  bone->move(this_player(), 1);

	  return "You find a toe bone!\n";
     }
     return "";
}


void 
reset_room()
{
  found = 1;

  set_searched(0);
}

void
init()
{
    ::init();

    if(found>0)
    add_item(({"wall","walls","stone"}),"The walls that border the path are " 
      +"too high to see over, but through cracks in the stones you can "
      +"see thick and fierce vegetation growing. Something white "
      +"appears lodged in the stone.\n");

    else
    add_item(({"wall","walls","stone"}),"The walls that border the path are " 
      +"too high to see over, but through cracks in the stones you can "
      +"see thick and fierce vegetation growing.\n");

}
