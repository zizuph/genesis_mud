#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/goodlund/nethosak/city/obj/door.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define H1 KRHERB + "fireweed"
#define H2 KRHERB + "tiger_lily"
#define H3 KRHERB + "chokecherry"
#define H4 KRHERB + "chokecherry"

object boar;

void
reset_mithas_room()
{
   set_searched(random(4));

   if(!objectp(boar))
      {
      boar = clone_object(MNPC + "boar");
      boar->move(this_object());
   }
}

void
create_mithas_room()
{
    object gate;
    set_search_places(({"underbrush","herbs",
                       "trail", "path", "ground"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
   
    reset_mithas_room();
    set_short("Forest intersection");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest47","south",0);
    add_exit(MROOM + "forest45","west",0); 
    add_exit(MROOM + "forest50","east",0);
    gate = clone_object("/d/Ansalon/goodlund/nethosak/city/obj/city_gate2b");
    gate->move(this_object());   

}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "The air here is filled with the smell of decomposing "+
    "wood and leaves. Tall oak trees stretches themselves "+
    "toward the sky, these trees must be more then a century "+
    "old. The trail here continues to the north, south, east "+
    "and west.\n";
}


