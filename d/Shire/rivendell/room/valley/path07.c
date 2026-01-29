/*
 * The terrace path along the river in Imladris
 * By Finwe, December 1997
 */
 
#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit VALLEY_BASE;

object reeds;

void
create_valley_room()
{
 
    set_extraline("The path twist and turns past some rocks " +
        "that jut up from the riverbank's edge. The river " +
        "rushes over the rocks, splashing into some pools " +
        "below. Some fruit trees hang over the path here, " +
        "shading you. The ground slopes towards the river.");
 
    add_item(({"road","ground","path","stony path", "down"}),
        "The path is made out of flat stones that closely fit " +
        "together.\n");  
    add_item(({"last homely house", "house"}),
        "The house is constructed of stone with ornately carved " +
        "dark beams. The beams  for a criss-cross and diamond " +
        "patterns across the face of the house. Gables extend from " +
        "the roof. The roof is covered with cedar shingles.\n");
    add_item(({"shingles", "cedar shingles"}),
        "The cedar shingles are weather worn but still " +
        "in good condition.\n");
    add_item("roof",
        "The roof is steeply pitched, allowing snow and " +
        "rain to roll off the house quickly and easily.\n");
    add_item("gables",
        "The extend from the roof, allowing more space in " +
        "the upper rooms.\n");
    add_item(({"beam", "beams"}),
        "The beams are made from dark oak. They are polished " +
        "to a deep luster and decorate the face of the house.\n");
    add_item("garden",
        "The garden surrounds the house. Many fruit trees, " +
        "vegetables, and edible plants can be seen growing " +
        "there. a split-rail fence surrounds the garden.\n"); 
    add_item(({"fence", "wooden fence", "split-rail fence"}),
        "The fence is constructed of timbers that have been " +
        "split in two. They are secured to posts that have been " +
        "sunk into the ground.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "This finger of the river Bruinen rushes west over " +
        "polished rocks. The water is clear and cold as it " +
        "comes from deep in the mountains. Its gentle music " +
        "fills the air.\n"); 
 
    add_prop(OBJ_I_CONTAIN_WATER,1);
    reset_shire_room();

    add_exit(VALLEY_DIR + "t_path08",  "east");
    add_exit(VALLEY_DIR + "t_path06",  "west");
 
}

void
init()
{   
    ::init();
    add_action("drink_it",      "drink");
}
 
drink_it(string s)
{
 
int amount;
 
   if(s=="water" || s=="water from river")
       {
           amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
           if (TP->drink_soft(amount))
           {
           TP->catch_msg("You kneel before the river, dipping " +
                "your cupped hands into the river and get a " +
                "drink of the clear icy water. Its taste " +
                "refreshes your mind and body.\n");
 
           say(QCTNAME(TP)+" kneels before the river and gets a " +
                "drink.\n");
           
           }
           else
           {
           write("You cannot drink more water.\n");
           }
 
            return 1;
        }
    else
            NF("Drink what?\n");
}
 
string short_desc()
{
    return ("The terrace path along the Bruinen");
}


void reset_shire_room()
{
    reeds = 0;
}

string
do_search(object searcher, string str)
{
   if(!str || (str!= "reeds" && str != "river")) return 0;
   if(reeds) return 0;
   seteuid(getuid(TO));
   reeds = clone_object(ROBJ_DIR + "rushes");
   reeds->move(searcher,1);
   say(QCTNAME(searcher)+ " finds something in the reeds.\n");
    return "You find some "+reeds->short()+" in the reeds.\n";
}
