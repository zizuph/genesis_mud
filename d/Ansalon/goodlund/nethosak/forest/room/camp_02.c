
/*
 * A small camp of minotaurs from the Hestos tribe.
 * By Cherek Jan 2007. 
 */
 
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define H1 KRHERB + "veronica"
#define H2 KRHERB + "onoclea"

object halamin, galdan;

void
reset_mithas_room()
{
    int halamin_check = 0;
    int galdan_check = 0;
   
    set_searched(random(4));

    if (!objectp(galdan))
    {
        galdan=clone_object(MNPC + "minotaur_galdan.c");
        galdan->move(this_object(), 1);  
        galdan_check = 1;
    } 
    else
    {
        galdan->guards_reset();
        halamin->guards_reset();
    }
    
    if (!objectp(halamin))
    {
        halamin=clone_object(MNPC + "minotaur_halamin.c");
        halamin->move(this_object(), 1); 
        halamin_check = 1;
    } 
    else
    {
        halamin->guards_reset();
        galdan->guards_reset();
    }

    if(galdan_check == 1)
    {
    galdan->set_friend(halamin);
    }

    if(halamin_check == 1)
    {
    halamin->set_friend(galdan);
    }
      
}

create_mithas_room()
{
    set_search_places(({"underbrush","herbs",
                       "trail", "path", "ground"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);

    reset_mithas_room();
    set_short("Small camp in a gloomy forest");
    set_long("@@long_descr"); 

    add_exit(MROOM + "camp_01","north", 0, 1); 
 

    add_item("forest",
             "The forest looks ancient. Old logs and branches "+
             "fill the forest floor and the strong smell of "+
             "decay and moisture fills the air. The forest "+
             "consists of different sorts of trees, a "+
             "mixture of pines and oaktrees. Many trees have been " +
             "chopped down in the southern part of the forest and the " +
             "ocean is clearly visible. \n");

    add_item(({"trees","oaktrees","pine trees", "pines"}),
               "The trees here consist of a mixture of pines "+
               "and oaktrees. Only a few old trees remains, the rest "+
               "of the trees are either dead or dying. Some trees have " +
               "even been chopped down. \n");

    add_item(({"underbrush","undergrowth"}),
               "The undergrowth here looks gray and dense with different "+
               "plants and herbs. It seems like it's impossible "+
               "to enter it. \n");

    add_item(({"canopy", "treetops"}),
               "The canopy above you looks thick, only a few sunrays "+
               "are able to enter the forest. You notice a few birds "+
               "above you, but they quickly vanish in the thick canopy.\n");

    add_item(({"leaves","branches"}),
               "The branches and leaves here, have almost decomposed "+
               "into dirt. A few of them look alive, but "+
               "they are still covered with moss and fungus. Some of "+
               "have been used to cover the tents. \n");

    add_item(({"herbs","plants"}),
               "There are a lot of different herbs here! If you want to "+
               "look at a specific one, perhaps you should search for "+
               "it.\n");
     
    add_item("view",
             "The view is splendid. The entire southern part of the " +
             "island is visible and the great Bloodsea lies before you. " +
             "Far away you spot a ship.\n");
          
    add_item("ship",
             "It is hard to make out any details this far away but you " +
             "think the sail is decorated with a red shield. \n");  
     
    add_item(({"sail", "sails", "shield"}),
               "The red shield is the mark of the Orilg tribe minotaurs. \n");
     
    add_item(({"sea","ocean","bloodsea","waters","water",
               "red waters","dark red waters","dark waters"}),
               "You realize you are standing on a small peninsula, " +
               "giving you an excellent view of the entire southern " +
               "shores of Mithas. \n"); 
     
    add_item(({"shore","shores", "southern shores"}),
               "The shore stretches out east and west from here. \n"); 
               
    add_item(({"peninsula","island","mithas"}),
               "It is hard to tell how large the island is from this " +
               "location. The dense forest makes it impossible to see " +
               "much more than the shores of this peninsula. \n");                
      
    add_item(({"camp", "clearing"}),
             "A small number of simple tents made from animal hides " +
             "make up the entire camp. The location is perfect since " + 
             "the view from here is excellent. \n");

    add_item(({"tent", "tents"}),
               "A small number of simple tents made from animal hides " +
               "make up the entire camp. The tents have been covered with " +
               "leaves and branches as if someone has tried to camouflage " +
               "the camp. \n");

    add_item(({"hides", "hide", "animal hides"}),
               "They are light gray in color and very rugged and heavy.\n");
               
    add_item("camouflage",
             "The leaves and branches makes the camp very hard to notice. " +
             "Especially for someone standing on a ship out at sea. \n");

    add_cmd_item("tent","enter","The tents are so well camouflaged " +
                 "you cannot find an entrance. \n");
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You stand within a small clearing in a gloomy forest in the " +
    "southern part of Mithas. The area is slightly elevated and " +
    "a few tents have been set up here. To the south several " +
    "trees have been chopped down and you can easily spot the " +
    "dark red waters of the Bloodsea. \n";
}
