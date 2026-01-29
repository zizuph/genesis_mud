/* room coded by Elizabeth Cook, November 1996 */

inherit "std/room";
#include <stdproperties.h> 
inherit "/d/Gondor/open/HERBS/herbsearch";
#include "../../mouse.h"

int searched;  

void create_room()  {
     set_short("Festiwycke Road");
     set_long("   Crude wooden huts huddle close to the road. Each hut is "+
          "hemmed in by a wattle fence. Behind each fence is a carefully "+
          "tended vegetable garden. Next to some of the huts, black iron "+
          "pots bubble furiously over open fires, watched over by somber "+
          "looking women absorbed in their tasks. Several children are "+
          "playing in the ditch by the side of the road.\n");
     add_item("road","A worn, dusty road that runs northwest and southeast.\n"); 
     add_item("fence","The fences are constructed of small tree branches "+
          "interwoven with closely placed poles. They look as if they've "+
          "been woven with great care to protect the precious vegetables "+
          "inside from foraging beasts.\n");
     add_item("huts","Low roofed, small shacks that appear to be constructed "+
          "of cast off pieces of lumber. It is amazing they don't blow "+
          "away, since they look as if they were built with as much haste "+
          "as it would take to tear them down. These huts seem to be "+
          "neither warm nor comfortable.\n");
     add_item("garden","Behind each fence is a carefully kept garden with "+
          "rows of cabbages, potatoes, beets and turnips.\n");
     add_item("pots","Large, black, cast iron cauldrons suspended over "+
          "blazing fires. Some pots are being utilized for the making of "+
          "soap, while others for the dyeing of homespun cloth.\n");
     add_item("fires","Large fires are kept blazing beneath huge pots, in "+
          "order that their contents are maintained at a furious boil.\n");
     add_item("women","Gaunt women in plain dresses mindlessly stir the "+
          "contents of the pots, snapping out of their daydreams now and "+
          "then to scream at their ragged looking offspring.\n");
     add_item("ditch","A ditch full of weeds lies next to the road on the "+
          "left. There is a trickle of water running through it. A few "+
          "grubby children are playing in the water.\n");
     add_item("weeds","A variety of plants are growing wildly in the ditch.\n");  
     add_item("water", "A small trickle runs through the ditch.\n");
     
     add_exit(ROOT+"village/rooms/V8","northwest");
     add_exit(ROOT+"village/rooms/V6","southeast");

     set_up_herbs(({ROOT+"herbs/yarrow",
                    ROOT+"herbs/elecampane",
                    ROOT+"herbs/aconite"}), 
                    ({"ditch"}));
     places = ({"ditch"});
     reset_room();            

}

  
void reset_room()  {
     int i;
     if(!present("child"))
     for(i=0;i<5;i++)
         clone_object(ROOT+"village/mons/child.c")->move(TO); 
     this_object()->set_searched(0);   
}

