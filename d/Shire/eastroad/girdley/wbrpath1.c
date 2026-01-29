inherit "/d/Shire/eastroad/std/er_base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "local.h"

#define EXIT1 ER_BASE_DIR + "girdley/underbridge","north",0,2
#define EXIT2 ER_BASE_DIR + "girdley/wbrpath2","south",0,2

int enter_river(string str);
 void
create_er_room()
{
    area = "south of";
   areaname = "the Bridge of Stonebows";
   land = "the Shire";
   areatype = 7;
   areadesc = "overgrown river path";
   grass = "green";
    extraline = "This narrow overgrown path leads north and south along "+
   "the west bank of the Brandywine river.  Here the river deepens and grows "+
   "more swift, having been strengthened by the narrowing at the bridge. "+
   "A canopy of birch and willow trees provide shade on either side of "+
   "the river. "+
   "West a steep muddy hill rises up, a second bank to the one on which "+
    "you stand.  North you may go under the bridge, and south the path "+
   "leads through a tangled mess of vines.";
    add_item(({"path","narrow path"}),
   "The narrow path is made considerably thinner by the influx of underbrush "+
   "and small bushes and tangling vines.\n");
   add_item(({"vine","vines","tangling vines"}),
   "The tangling vines are long but curly, perfect for catching an ankle in.\n");
   add_item(({"bush","bushes","small bushes","underbrush"}),
   "The underbrush is a continuous line of various green and flowering "+
   "bushes trying to peek out under the canopy of trees that line the "+
   "riverside path.\n");
   add_item(({"tree","trees","canopy","canopy of trees"}),
   "The trees are mostly willows and tall birch trees which lean out "+
   "across the water to feed in all the available sunlight.\n");
   add_item("water","The water is brown and muddy, flowing slowly by.\n");
   add_item(({"bank","river","brandywine river","ford"}),
   "The bank on this side is narrow and slightly muddy along the river, which "+
   "flows southward towards Sarn Ford.\n");
   add_item(({"bridge","bridge of stonebows","brandywine bridge"}),
   "The Bridge of Stonebows is very ancient and well-made.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);

    set_up_herbs( ({    GONDOR_HERB_DIR + "tuo",
                        GONDOR_HERB_DIR + "curugwath",
                        SHIRE_HERB_DIR  + "maroea", 
                        SHIRE_HERB_DIR  + "lianor_berry",
                        GONDOR_HERB_DIR + "strawberry",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);

    set_drink_from( ({ "river", "brandywine", "baranduin", }) );

}
 void
init()
{
    ::init();
    init_drink();

//    add_action("enter_river","e");
//    add_action("enter_river","east");
    add_action("enter_river","enter");
//    add_action("enter_river","swim");
}

int enter_river(string str)
{
    if (query_verb() == "enter")
        if (str == "bushes" || str == "vines")
        {
            write("You find the bushes and vines are too tightly "
              + "entangled for you to pass through them.\n");
            return 1;
        }
/*
    if((TP->query_skill(SS_SWIM)) < (20 + random(25)))
   {
    write("You are not skilled enough in swimming to enter the water.\n");
    say(QCTNAME(TP)+ " looks longingly at the water, but does not dare enter it.\n");
    return 1;
   }
     say(QCTNAME(TP)+" splashes out into the brown water, swimming happily.\n");
   write("You step into the river and are swept away with the current.\n"+
   "You manage to keep your head above water, though.\n");
   TP->move_living(ER_BASE_DIR + "girdley/brandy1");
   return 1;
*/
 }

/*
* Function name: drink_message
* Description : do the msgs for drinking from river
*/
public void
drink_message(string from)
{
    write("You drink some of the yellow water of the Brandywine river.\n"
    + "It tastes dirty and muddy.\n");
    say(QCTNAME(TP) + " drinks some water from the river.");
} 