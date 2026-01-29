/*
*   2021-08-08 Meton Changed write() to tell_room to avoid /lplog errors
*       line 201
*/

inherit "/std/object";

#include "../local.h";

// Prototypes
public int          attach_shard(string str);
public int          study_shard(string str);
public void         do_vanish();

// Global Variables
static string  *gShardCompanion,
                gShardResult;
public mixed    Vanish_Alarm = 0;

public varargs string *
query_shard_companion(object shard)
{
    /* This is one way of doing it.. if you want to match descriptions.. 
     * for cohesion, it would be better to match file names.
     *
    function f = &->id();
    if (objectp(shard))
        return filter(gShardCompanion, &f(shard,));
    */
    if (member_array(MASTER_OB(shard), gShardCompanion) > -1)
        return ({ MASTER_OB(shard) });
    
    return gShardCompanion;
}

public void
set_shard_companion(mixed shard)
{
    if (stringp(shard))
        shard = ({ shard });
    
    if (pointerp(shard))
        gShardCompanion = shard;
}

public string
query_shard_result()
{
    return gShardResult;
}

public void
set_shard_result(string result)
{
    gShardResult = result;
}

public void
create_shard()
{
}

public nomask void
create_object()
{
    setuid();
    seteuid(getuid());

    create_shard();
    
    set_name("shard");
    add_name("_thanar_medallion_shard_");
    add_prop(MAGIC_AM_MAGIC,( {20,"enchantment"} ));
    add_prop(MAGIC_AM_ID_INFO, ({
          "You sense an ancient dark power emitting from the shard, you " + 
          "can't help but wonder what would happen if you assemble the " +
          "whole medallion.\n", 20 }) );
    add_prop(OBJ_S_WIZINFO, "This one part of the Thanar medallion used to "
                          + "summon the avatar.\n");
    add_prop(OBJ_M_NO_GIVE, "This shard is critical to your mission. You'd "
    +"better keep that.\n");
    add_prop(OBJ_M_NO_SELL, "The shard has no monetary value.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    
}

public status
filter_master(object ob)
{
    return ( MASTER_OB(ob) == MASTER );
}

public object *
find_duplicates(object target)
{
    return filter(deep_inventory(target), &filter_master());
}

public void
remove_shards(object *shards)
{
    if (sizeof(shards))
        shards->remove_object();
}

public void
destruct_me()
{
    object room;
 
    if (living(room = environment()))
    {
        room = environment(room);
    }
 
    tell_room(room, "The shard melts into a pool and evaporates away in "+
      "mist.\n");
    remove_object();
}

/*
 * Function name:        attach_shard
 * Description  :        Attaches the shard to another piece of the medallion
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
attach_shard(string str)
{
    string  match1,
            match2;
    object *oblist;
    
    notify_fail("Attach what?\n");
    if (!strlen(str) || !CAN_SEE_IN_ROOM(this_player()))
        return 0;
    
    str = lower_case(str);
    notify_fail("Attach what with what?\n");
    if (!parse_command(str, all_inventory(this_player()), 
    "[the] %s 'with' [the] %s", match1, match2))
        return 0;
    
    oblist = ({});
    foreach(string desc: ({ match1, match2 }))
    {
        object *obs;
        
        obs = FIND_STR_IN_OBJECT(desc, this_player());
        obs = filter(obs, &->id("_thanar_medallion_shard_"));
        
        if (!sizeof(obs))
        {
            notify_fail("You do not possess " + LANG_ART(desc) + " " + desc + ".\n");
            return 0;
        }
        
        oblist += ({ obs[0] });
    }
    
    if (sizeof(oblist[0]->query_shard_companion(oblist[1])))
    {
        object result;
        
        if (LOAD_ERR(oblist[0]->query_shard_result()))
            return 0;
        
        result = clone_object(oblist[0]->query_shard_result());
        result->move(this_player(), 1);
        
        write("You merge the pieces of shard together. You feel it is only "
        +"a temporary solution until the blacksmith can forge them properly.\n");
        
        set_alarm(0.0, 0.0, &remove_shards(oblist));
        return 1;
    }
    
    return 0;
}

/*
 * Function name:        study_shard
 * Description  :        Dispays a ascii image of the medallion
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
study_shard(string str)
{
    
}

public void
dedup_shards(object *shards)
{
    shards -= ({ this_object() });
    
    if (sizeof(shards))
    {
        set_alarm(0.2, 0.0, &remove_shards(shards));
        set_alarm(0.2, 0.0, &tell_room(environment(), "The shards "+
            "merge.\n"));
    } 
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
    
    dedup_shards(find_duplicates(dest));
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
         tell_room(env, "The shard of medallion dissolves into mist and"
           + " is gone.\n");
     }
     else if (living(env))
     {
         env->catch_tell("The shard of medallion dissolves into mist and is"
           + " gone.\n");
     }
     if (Vanish_Alarm)
     {
         remove_alarm(Vanish_Alarm);
     }
     Vanish_Alarm = 0;
     remove_object();
 } /* do_vanish */
/*
 * Function name: init
 * Description  : add some actions to the player
 */
public void
init()
{
    ::init();
    add_action(attach_shard, "attach");
    add_action(study_shard, "study");
} /* init */

/*
 * Function name:   query_recover
 * Description  :   Called to check whether this armour is recoverable.
 *                  If you have variables you want to recover yourself,
 *                  you have to redefine this function, keeping at least
 *                  the filename and the armour recovery variables, like
 *                  they are queried below.
 *                  If, for some reason, you do not want your armour to
 *                  recover, you should define the function and return 0.
 * Returns:         string - the default recovery string.
 */
string
query_recover()
{
    return 0; // Don't want this item to recover.
} /* query_recover */