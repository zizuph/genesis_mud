/*
 * /d/Kalad/common/guilds/new_thanar/obj/upper_half.c
 *
 *  The upper half of the Thanar medallion you need
 *  to collect all four parts in order to create a complete
 *  medallion. 
 *  Created by Zignur Feb 2018
 *
 */

#include "../local.h"
#include <macros.h>
inherit "/d/Kalad/common/guilds/new_thanar/obj/shard_base";
 
 void
 create_shard()
 {
     add_name("upper half shard");
     add_name("_upper_half_shard_");
     add_name("upper half");
     add_name("top half");
     add_adj( ({ "upper", "half", "upper half"}) );
     set_short("upper half shard");
     set_long("This seems to be the upper half of a broken "
            + "medallion. It looks like it could be attached to "
            + "another matching part of the medallion. You "
            + "get a feeling that you could study it if you wish.\n");
     
     /*
      * Example: If you want to match on ids, rather than file names.
      *  set_shard_companion("upper left shard");
      */
     set_shard_companion("/d/Kalad/common/guilds/new_thanar/obj/bottom_half_shard");
     set_shard_result("/d/Kalad/common/guilds/new_thanar/obj/medallion");
 } /* create_object */

/*
 * Function name:        study_shard
 * Description  :        Dispays a ascii image of the medallion
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
study_shard(string str)
{

    if(!strlen(str))
    {
        notify_fail("Study what? <study upper shard>, perhaps?\n");
        return 0;
    }
   
    if (str != "upper shard")
    {
        notify_fail("Study what? <study upper shard>, perhaps?\n");
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
          "\n");    
    
    this_player()->tell_watcher(QCTNAME(this_player()) + " studies " +
       "the " + short() + " of a broken medallion.\n", this_player());
    
    return 1;
    
} /* study_shard */




