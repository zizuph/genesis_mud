/*
 * /d/Kalad/common/guilds/new_thanar/arm/medallion.c
 * The reward for collecting four parts of a medallion and having
 * the blacksmith in kalad mending it into a medallion. This 
 * item will be be part of the quest to summon the Avatar.
 * 
 * Created by Zignur Feb 2018
 *
 */

#pragma strict_types
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Kalad/defs.h"
inherit "/std/armour";

/* Global Variables */


#define ADJ1 ({"faded","diminished"})
#define ADJ2 ({"platinum", "adamantium"})
/* Prototypes */ 

public int          study_medallion(string str);
                   

/*
 * Function name:        create_armour
 * Description  :        Function used to create the medallion
 *                   
 */
public void
create_armour()
{
   string adj1 = one_of_list(ADJ1);
   string adj2 = one_of_list(ADJ2);
   
   setuid();
   seteuid(getuid());
    
   set_name("medallion");
   add_name("chain medallion");
   add_name("long chain medallion");
   add_name("_thanar_medallion_");
   set_adj(adj1);
   add_adj(adj2);
   set_short(adj1 + " " + adj2 + " medallion");
   set_long("A long, beautifully-crafted "+adj2+" chain medallion. It is a "+
      "symbol of servitude to the beliefs and purpose of the Thanarians "+
      "and the patron god of humanity, Thanar. It radiates with power " +
      "this is clearly a very ancient and powerful artifact. The front " +
      "of the the medallion is engraved with a symbol of a snake. Its " +
      "back is covered with delicate inscribed ancient writing.\n");
   set_wf(this_object());
   set_slots(A_NECK);
   
   add_item(({"symbol", "engraved symbol", "snake symbol", "snake"}),
      "The symbol is engraved within the medallion and the design "+
      "is of the head of a snake.\n");
   add_item(({"writing", "ancient writing", "delicate ancient writing"}),
      "Delicate ancient writing covers the back of the medallion, but "+
      "you fail to understand its meaning.\n");

   add_prop(MAGIC_AM_ID_INFO,({"Medallion infused with enough Magic to "
   + "summon Thanar. But nothing else.\n",15}));
   
   add_prop(OBJ_S_WIZINFO, "Item used for the Quest to summon the avatar " +
      " in Kalad, this version is if they didn't manage to do it with their "+
      "actual magic one.\n");
  
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 200);
} /* create_armour */


/*
 * Function name:        study_medallion
 * Description  :        Dispays a ascii image of the medallion
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
study_medallion(string str)
{

    if(!strlen(str))
    {
        notify_fail("Study what? <medallion>, perhaps?\n");
        return 0;
    }
   
    if (str != "medallion")
    {
        notify_fail("Study what? <study medallion>, perhaps?\n");
        return 0;
    }     
   
    write("You study the " + short()+ ".\n\n                          \n" +
          "           8888888888888                                   \n" + 
          "      888888           8888888                             \n" +
          "   88888 ------------------- 88888                         \n" +
          "  888    / '*|       / .'*| |    8888                      \n" +
          " 888    : __ /      /__ -'   |.   888                      \n" +
          "88     /                      )    88                      \n" +
          "88   _/                  >   .'    88                      \n" +
          "88 /   .   .       _.-  /  .'      88                      \n" +
          "88 |           __/      /.'/|      88                      \n" +
          "88  | '--  .-  /     //' |/|       88                      \n" +
          "88   ||  | | /     //_ _ |/|       88                      \n" +
          "88    `.  |:     //|_ _ _|/|       88                      \n" +
          "88     | |/.    //  | _ _ |/|      88                      \n" +
          " 88     |_ | |/ /    | _ _ |/|    88                       \n" +
          "  88       |__/      | _ _ |/|  88                         \n" +
          "    88                         88                          \n" +
          "     888                    888                            \n" +
          "      88888            88888                               \n" +
          "          88888888888888                                   \n" +
          "\n");      
    
    this_player()->tell_watcher(QCTNAME(this_player()) + " studies " +
      "the "+ short() + ".\n");

    return 1;
    
} /* study_medallion */

/*
 * Function name: init
 * Description  : add some actions to the player
 */
public void
init()
{
    ::init();
    add_action(study_medallion, "study");
} /* init */


