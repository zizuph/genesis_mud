/*
 * /d/Kalad/common/guilds/new_thanar/obj/medallion.c
 *
 *  The result when you attach four shards of the Thanar
 *  medallion. This medallion needs to be brought to the smith
 *  in Kalad so he can forge it into the real medallion.
 *  Created by Zignur Feb 2018
 *
 */
 
inherit "/std/object";
#include "../local.h";
#include <stdproperties.h>
#include <macros.h>

/* Prototypes */
public int          study_shard(string str);
public void         do_vanish();
public mixed        Vanish_Alarm = 0;


void
create_object()
{
    set_name("ancient medallion");
    add_name("medallion");
    add_name("ancient Thanar medallion");
    add_name("Thanar medallion");
    add_name("_t_medallion_");
    set_adj("ancient medallion");
    add_adj( ({ "ancient","Thanar", "medallion"}) );
    set_short("ancient thanar medallion");
    set_long("This seems to be the an ancient Thanar medallion. "
           + "It its assembled from four shards. It seems to be missing " 
           + "a notched piece.\n");
    add_prop(MAGIC_AM_MAGIC,( {20,"enchantment"} ));
    add_prop(MAGIC_AM_ID_INFO, ({
          "You sense an ancient dark power emitting from the medallion, you " +
          "can't help but wonder what would happen if you brought this " +
          "medallion to a capable smith.\n", 20 }) );
    add_prop(OBJ_S_WIZINFO, "This the unforged Thanar medallion used to "
                          + "summon the avatar.\n");
    add_prop(OBJ_M_NO_GIVE, "This shard is critical to your mission. You'd "
          +"better keep that.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_M_NO_SELL, "This " +TO->short()+ " is not worth anything.\n");
} /* create_object */

/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If you have variables you want to recover yourself,
 *                you have to redefine this function, keeping at least
 *                the filename and the armour recovery variables, like
 *                they are queried below.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
string
query_recover()
{
    return 0; // Don't want this item to recover.
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 */   
public void
enter_env(object dest,object old)
{
    ::enter_env(dest, old);
 
    if (dest->query_prop(ROOM_I_IS))
    {
        Vanish_Alarm = set_alarm(1.0, 0.0, "do_vanish");
    }
     
}

/*
 * Function name:        do_vanish
 * Description  :        the object disappears
 */
 public void
 do_vanish()
 {
     object env = environment(this_object());
     if (env->query_prop(ROOM_I_IS))
     {
         tell_room(env, "The medallion dissolves into mist and is gone.\n");
     }
     else if (living(env))
     {
         env->catch_tell("The medallion dissolves into mist and is gone.\n");
     }
     if (Vanish_Alarm)
     {
         remove_alarm(Vanish_Alarm);
     }
     Vanish_Alarm = 0;
     remove_object();
 } /* do_vanish */


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
        notify_fail("Study what? <ancient medallion>, perhaps?\n");
        return 0;
    }
   
    if (str != "ancient medallion")
    {
        notify_fail("Study what? <study ancient medallion>, perhaps?\n");
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
      "studies the "+ short() +  " medallion.\n");

    return 1;
    
} /* study_shard */


/*
 * Function name: init
 * Description  : add some actions to the player
 */
public void
init()
{
    ::init();
    add_action(study_shard, "study");
} /* init */




