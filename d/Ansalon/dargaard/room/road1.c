/**  DARGAARD OUTSIDE ROOM **/
/* Added revelation for OotS - Arman 2017 */
 
#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/guilds/OotS/defs.h"
 
inherit DARGAARD_OUT;
 
/* defines */
#define WAGON_FILE "/d/Ansalon/dargaard/wagon/wagon.c"
#define CHANCE random(80)
 
/* prototypes */
int fetch_wagon(string wagon_file);
int wraith_found = 0;
int last_time;
object npc_wraith, leader, s1, s2, s3, s4;
#define WRAITH_INTERVAL (3600 * 4) 
 
void
reset_dargaard_room()
{
    if(CHANCE == 1)
    {
        find_player("arman")->catch_msg("UNDEAD attack on clan.\n\n");
        log_file("clan/undead_raid",extract(ctime(time()),4,15)+ " :Undead Raid.\n",
            500000);

        // This has not been loading for a long time. /Cotillion - 2020-05-08
        // Fixed. Arman 06-12-2021
        leader = clone_object(DNPC + "skeleton_leader");
        leader->arm_me();
        leader->move(TO);
        s1 = clone_object(DNPC + "skeleton");
        s1->move(TO);
        s2 = clone_object(DNPC + "skeleton");
        s2->move(TO);
        s3 = clone_object(DNPC + "skeleton");
        s3->move(TO);
        s4 = clone_object(DNPC + "skeleton");
        s4->move(TO);
    }

    if (time() - last_time > WRAITH_INTERVAL)
    {
        wraith_found = 0;
    }
}
 
void
create_dargaard_room()
{
    set_short("Road to Dargaard Keep");
    set_long(tod_descr()+ "" +season_descr()+ "You are standing "+
        "on a twisted road to the dreaded Dargaard Keep. "+
        "You feel extremely insecure as you notice the once "+
        "grand Dargaard Keep in the distance. The road continues "+
        "southeast towards the Keep and northwest onto the "+
        "Nightlund Plains. A withered tree stands near the road, and "+
        "you think you notice something hanging from it.\n");
    /*
      "A wooden sign has been placed here.\n");
    */
 
    add_exit("/d/Krynn/solamn/eplains/rooms/eplain-20-5-D","northwest",0);
 
    add_item(({"road", "path"}),
        "A few bones lies scattered on the path.\n");
 
    add_item(({"stones"}),
        "The road is made out of flat gray stones of various sizes. "+
        "Small patches of moss fill the cracks between the stones.\n");
 
    add_item(({"plants", "moss", "vegetation"}),
        "The vegetation here consists most of dried grass and plants. "+
        "Small green moss spots cover some of the rocks.\n");
 
    add_item(({"boulders", "huge boulders"}),
        "A few huge boulders lies next to the road, they have been gently "+
        "pushed aside to make way for the stone road.\n");
 
    add_item(({"plains", "nightlund plains"}),
        "The Nightlund plains lies before the Dargaard Mountains, the green "+
        "plain continues far into the distance.\n");
 
    add_item(({"bushes", "trees", "log", "logs"}),
        "Dead trees and dried bushes fill the area, the cold winds and dry "+
        "weather might have killed them.\n");
 
    add_item(({"dargaard keep", "keep"}),"@@dargaard_desc");
 
    add_item(({"tree"}),
        "As you begin to examine the ancient tree, you notice three "+
        "shadows hanging high above you in the branches of the tree.\n");
 
    /*
      add_item(({"sign", "letters"}),
      "Try reading it.\n");
    */
 
    add_item(({"figures", "corpses", "shadows"}),
        "You see that three figures are hanging from "+
        "its twisted branches. The first figure is an elf dressed in some "+
        "green and brown clothes. The second one "+
        "wears the insignias of the Knights of Solamnia and the last "+
        "figure wears the officers uniform of the Red Dragonarmy. "+
        "These figures were different in culture and goals in their life "+
        "but they are now united in their fate. Their faces are still "+
        "wearing expressions of absolute terror.\n");
 
    /*
      add_cmd_item(({"sign","letters"}),"read","@@read_sign");
 
      fetch_wagon(WAGON_FILE);
    */

    add_search(({"corpse","corpses","elf corpse","knight corpse",
                     "officer corpse","figures","shadows"}),2,"wraith_descr",1);


    reset_dargaard_room();
    /* Let's not spawn it right after armie */
    wraith_found = 1;
}

string
dargaard_desc()
{
    if(IS_OOTS(TP))
    {
          if(!OOTS_QUERY_REV(TP, "13warnings"))
          {
            TP->catch_msg("\n\nAs you look up at the grim walls of Dargaard Keep you are provided " +
                 "a dark revelation on the thirteen warnings from the Gods that preceded the " +
                 "Cataclysm.\n\n\n");
            OOTS_ADD_REV(TP,"13warnings","enlightenment - the fall of istar, the thirteen warnings");  
          }
    }

      return "The fortress high up in the mountains is known as Dargaard Keep. "+
        "It appears blackened as if it had been burnt, and an unnatural "+
        "darkness seems to radiate from it. You cannot make out any details, "+
        "since the keep is too far away.\n";
}
 
int
read_sign()
{
    write("The sign reads:\n"+
        "+----------------------------+\n"+
        "|                            |\n"+
        "|  Passage to Dargaard Keep  |\n"+
        "|                            |\n"+
        "|  Price: 6 copper coins.    |\n"+
        "|                            |\n"+
        "+----------------------------+\n");
 
    say(QCTNAME(this_player()) + " reads the wooden sign.\n");
    return 1;
}
 
int
fetch_wagon(string wagon_file)
{
    object wagon_obj;
 
    wagon_obj = clone_object(wagon_file);
    wagon_obj->move(TO);
    wagon_obj->start_moving();
    return 1;
}

string
wraith_descr(object who, string what)
{
    if (wraith_found)
    {
        return 0;
    }

    say("As " +QTNAME(who)+
        " approaches the corpses hanging from the twisted " +
        "branches of the tree, an unearthly moan escapes one of the " +
        "figures! A dark shape detaches itself from its mortal host and " +
        "launches itself at you!\n");
    
    npc_wraith = clone_object(DNPC + "tree_wraith");
    npc_wraith->arm_me();
    npc_wraith->move(TO);
    wraith_found = 1;
    last_time = time();
    
    return "As you approach the corpses hanging from the twisted "+
        "branches of the tree, an unearthly moan escapes from one of "+
        "the figures! A dark shade detaches itself from its mortal hoste "+
        "and launches itself at you!\n";
}
