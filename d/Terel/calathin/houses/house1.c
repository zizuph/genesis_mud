/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house1.c
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;

inherit "/d/Terel/std/herbsearch.c";

#define SE_HERBS  ({ (HERB_DIR + "blueberry"),\
                     (HERB_DIR + "holly"),\
                     (HERB_DIR + "mint"),\
                     (HERB_DIR + "attanar"),\
                     (HERB_DIR + "suranie"),\
                     (HERB_DIR + "blung"),\
                     (HERB_DIR + "catnip"),\
                     (HERB_DIR + "frostheal"),\
                     (HERB_DIR + "sumac"),\
                  })

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


#include <stdproperties.h>

object door;
object citizen = 0;
string climb_chimney();

public void
create_room()
{
    ::create_room();
    set_short("Small House");

    set_long("The road leads to a cobbled path which " +
       "ends before a small house. The house is separated " +
       "from the rest of the forest by a split-rail fence.\n");

    add_item(({"small house","house"}),
       "The small house seems in good shape, the outer " +
       "walls are made of wooden boards, painted white. " +
       "The 'A' framed roof is covered in a thick " +
       "blanket of snow except for the area surrounding the " +
       "small stone chimney protruding from the south side " +
       "of the house. Two windows can be seen on either side " +
       "of the door.\n");
    
    add_item(({"pine trees","trees"}),
       "The pine trees vary in size, other than that " +
       "you dont notice anything special about them.\n");

    add_item(("forest"),"The area surrounding the house " +
       "is densely populated with pine trees.\n");
   
    add_item(({"split-rail fence","fence"}),
       "Wooden posts cured with pitch to protect them " +
       "from the harsh climate.\n");

    add_item(({"board","boards"}),
       "The boards cover the exterior of the house. " +
       "They look like they were plained from pine by hand.\n");

    add_item(("pitch"),"A thick, black, lustrous, and " +
       "sticky substance obtained by boiling down tar.\n");
  
    add_item(({"cobbled path","path"}),
       "Someone has recently cleared the snow from the cobbled path " +
       "which is composed of various sized river rocks " +
       "fitted tightly together. The path runs through the yard " +
       "to the front of the house.\n");

    add_item(("road"),"The small road leads from the cobbled path " +
       "back to the main road.\n");

    add_item(("yard"),"The yard stretches from the fenceline " +
       "to the front of the house. Most of the yard is covered " +
       "in snow, except for small pockets of frozen grass around " +
       "the fenceposts.\n");

    add_item(({"frozen grass","grass"}),
       "Long strands of grass frozen over from the previous summer.\n");

    add_item(({"river rock","rock","stones","rocks"}),
       "The rocks are smooth polished by some nearby " +
       "river, varying in size.\n");

    add_item(("walls"), "The walls are thick boards nailed " +
       "over a wooden frame. They look quite sturdy.\n");

    add_item(({"wooden door","door"}), "The wooden door looks sturdy.\n");

    add_item(({"wooden posts","posts"}),
       "The fence posts are covered in pitch, but appear " +
       "to be cut from pine.\n");

    add_item(("windows"),"The windows are closed tight " +
       "with the shutters drawn to keep the cold out.\n");

    add_item(({"shutter","shutters","pane"}),
       "The shutters are made from sturdy pine boards, " +
       "painted white with green trim along the edges. " +
       "There is a cross cut out on the middle on each shutter " +
       "pane.\n");

    add_item(("roof"),"The roof is a thatch 'a' frame " +
       "configuration, covered under a thick blanket of snow " +
       "except for the area around the small chimney " +
       "which can be seen protruding from the southside " +
       "of the house.\n");

    add_item(("chimney"),"The chimney is comprised of " +
       "river rock and mortar.\n"); 

    add_item(("cross"),"You figure the cross could be used " +
       "to let light pass through or perhaps to allow the " +
       "inhabitants to fire arrows from.\n");

    add_item(("snow"),"The entire area is covered in it. " +
       "You get the feeling of being in a winter wonderland.\n");

    add_cmd_item("chimney","climb",climb_chimney);

    door = clone_object(CALATHIN_DIR + "houses/obj/house1_door");
       door->move(TO);


    set_up_herbs( ({ ONE_OF_LIST(ANY_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                  }),
                  ({"path","grass","yard"}) , 
                   3 );

    reset_room();
    add_exit(CALATHIN_DIR + "paths/path_w07","south",0);

}


void
reset_room()
{    
  
    if(!citizen)
    {
       citizen = clone_object(CALATHIN_DIR + "npc/std_citizen");
       citizen->move(TO);
   
    }
}


string
climb_chimney()
{
   if (TP->query_skill(SS_CLIMB) > 40)
   {
    write("You deftly climb up the side of the chimney.\n");
       TP->move_living("climbing up the chimney", 
       CALATHIN_DIR + "houses/house1_roof.c",1,0);
       return "";
   }

   else return "The chimney looks far too dangerous for you to climb.\n"; 
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
init()
{
    ::init();
    add_action("do_smell", "smell");
}

/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */
public int
do_smell(string what)
{
    string poss, str, *smells;
    object *ob;
    int i;

    ob = all_inventory(TO);
    poss = POSSESSIVE(TP);
    smells = ({"mint", "sumac", "cedar trees", "holley"});
    for (i = 0; i < sizeof(ob); i++) {
        if (living(ob[i]) && !ob[i]->query_wiz_level() && ob[i] != TP) {
            smells += ({QTNAME(ob[i])});
        }
    }
    str = "You inhale deeply through your nose, and recognise the " +
        "smell of ";
    TP->catch_msg(str + smells[random(sizeof(smells))] + ".\n");
    say(QCTNAME(TP) + " inhales deeply through " + poss + " nose.\n");
    return 1;
}
