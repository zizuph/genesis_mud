/* Inn for Festiwycke, coded by Elizabeth Cook/Mouse, August 1997 */

inherit "/std/room";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "../../mouse.h"

void create_room()  {

   set_short("Briarwood Inn");
   set_long("   The Briarwood Inn is the focal point of social activity in "+
       "the Festiwycke area. To some residents it has even become a "+
       "second home. This large, rustic room is pervaded with a homey "+
       "warmth. Thick-topped tables are crowded closely together. "+
       "Wrought iron candleholders are suspended from the ceiling "+ 
       "inbetween the exposed beams. A bar spans the length of the back "+
       "of the room, behind which tapped kegs of ale rest on sturdy "+
       "shelves. A burly bartender stands behind the bar, polishing "+ 
       "glasses. A huge stone hearth dominates the north wall. Two "+  
       "elderly men sit at a small table near the fireplace, arguing "+ 
       "over a game of checkers. The white plaster walls are decorated "+ 
       "with a few hunting trophies. A stairway to the second "+
       "floor rises along the south wall. There is a doorway in the "+  
       "wall underneath the stairs, leading to the kitchen. There is a "+
       "menu on the bar you can read.\n");
  
 add_cmd_item("menu","read","----------------------------------\n"+
                     "|         Briarwood Inn          |\n"+
                     "|                                |\n"+
                     "| hearty ale                15cc |\n"+
                     "| currant wine              25cc |\n"+
                     "| wassail                   30cc |\n"+
                     "| hair of the dog           50cc |\n"+
                     "| cornbread                 20cc |\n"+
                     "| roast beef dinner         70cc |\n"+
                     "| barbecued pork            60cc |\n"+
                     "| garden bounty             40cc |\n"+
                     "| Festiwycke pecan pie      25cc |\n"+
                     "|                                |\n"+
                     "----------------------------------\n"); 
   add_drink(({"hearty ale","ale","hearty ales","ales"}),"ale",
       "hearty",460,15,15,0,0, "The finest amber elven ale, brought "+
       "to Festiwycke by the Royal Elvish Navy.\n",0);
   add_drink(({"currant wine","wine","currant wines","wines"}),
       "wine","currant",200,30,25,0,0, "A dark, syrupy wine with a "+
       "rather bitter taste.\n",0);
   add_drink(({"wassail","wassails"}),"wassail","",340,30,30,0,0,
       "A deliciously warm and spicy mug of wine.\n",0);
   add_drink(({"hair of the dog","hair","hairs of the dog","hairs"}),
       "hair of the dog","",100,60,50,"hair of the dog",
       "hairs of the dog","A mysteriously odorless and colorless "+
       "potable that is 100 percent guaranteed to kill any microorganisms "+
       "living in your digestive tract, as well as a vital organ or two.\n",
       0); 
   add_food(({"cornbread","cornbreads"}),"cornbread","",20,20,0,0,
       "A piping hot square of golden yellow bread.\n",0);
   add_food(({"roast beef dinner","dinner","roast beef dinners",
       "dinners"}),"roast beef dinner","",100,70,"roast beef dinner",
       "roast beef dinners","Thin slices of tender beef with "+
       "potatoes, smothered in a thick gravy.\n",0);
   add_food(({"barbecued pork","pork","barbecue","porks","barbecues",
       "barbecued porks"}),"pork","barbecued",80,60,0,0,
       "Chunks of pork charbroiled and thickly coated with a spicy "+
       "sauce.\n",0);
   add_food(({"garden bounty","bounty","garden bounties","bounties"}),
       "bounty","garden",50,40,0,0,"A colorful blend of salad "+
       "greens and fresh vegetables straight from the chef's garden.\n",0);
   add_food(({"festiwycke pecan pie","pecan pie","pie","pies","pecan pies",
       "festiwycke pecan pies"}),"festiwycke pecan pie","",30,25,
       "festiwycke pecan pie","festiwycke pecan pies","A thick, sweet "+
       "slice of pie made in the local tradition, with generous "+
       "amounts of pecans and chocolate.\n",0);
   
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,2);   
 
   add_exit(ROOT+"village/rooms/V15","east");
   add_exit(ROOT+"village/rooms/hall","stairs",0,1,1);

   clone_object(ROOT+"village/mons/bwbarman.c")->move(TO);
   clone_object(ROOT+"village/mons/alice.c")->move(TO); 
}




void init()  {
    ::init(); 
    init_pub();
}

    
void reset_room()
{
  {
    if(!present("bartender"))
        clone_object(ROOT+"village/mons/bwbarman.c")->move(TO); 
  }

  {
    if(!present("alice"))
        clone_object(ROOT+"village/mons/alice.c")->move(TO); 

  }
}

int order(string str)
{
    if(!present("bartender"))
    {

        notify_fail("There's no bartender here to help you.\n");
        return 0;

    }
    return ::order(str);
}
