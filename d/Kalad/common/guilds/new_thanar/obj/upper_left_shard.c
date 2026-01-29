/*
 * /d/Kalad/common/guilds/new_thanar/obj/upper_right_shard.c
 *
 *  The upper left shard of the Thanar medallion you need
 *  to collect all four parts in order to create a complete
 *  medallion. 
 *  Created by Zignur Feb 2018
 *
 */
 
inherit "/d/Kalad/common/guilds/new_thanar/obj/shard_base";

#include <macros.h>

void
create_shard()
{
    add_name("upper left shard");
    add_name("_upper_left_shard_");
    add_name("upper left");
    add_adj( ({ "upper", "left", "upper left"}) );
    set_short("upper left shard");
    set_long("This seems to be the upper left shard of a broken "
           + "medallion. It looks like it could be attached to "
           + "another matching part of the medallion. You "
           + "get a feeling that you could study it if you wish.\n");
    /*
     * Example: If you want to match on ids, rather than file names.
     *  set_shard_companion("upper right shard");
     */
    set_shard_companion("/d/Kalad/common/guilds/new_thanar/obj/upper_right_shard");
    set_shard_result("/d/Kalad/common/guilds/new_thanar/obj/upper_half_shard");
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
        notify_fail("Study what? <study upper left shard>, perhaps?\n");
        return 0;
    }
   
    if (str != "upper left shard")
    {
        notify_fail("Study what? <study upper left shard>, perhaps?\n");
        return 0;
    }     
   
    write("You study the " + short()+ ".\n\n                          \n" +
          "       8888                                                \n" +
          "   888888                                                  \n" +
          "88888 --------                                             \n" +
         "888    / '*|                                                \n" +
         "888    : __ /                                               \n" +
        "88     /                                                     \n" +
        "88   _/                                                      \n" +
        "88 /   .   .                                                 \n" +
        "88 |          __/                                            \n" +
        "\n");

        
    this_player()->tell_watcher(QCTNAME(this_player()) + " studies " +
       "the " + short() + " of a broken medallion.\n", this_player()); 
   
    return 1;
    
} /* study_shard */