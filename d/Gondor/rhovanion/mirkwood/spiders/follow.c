/*
 *  This is the shadow that allows the spiders to follow their enemies
 *  around in the forests.
 *
 */

#include "../defs.h"
#include <macros.h>
#include <language.h>

inherit "/std/shadow";

public void remove_mirkwood_spider_follow_shadow();

object *followers = ({ });

private int
is_target_within_restrain_path(string target, object spider)
{
    string tmp;

    if (!objectp(spider)) return 0;
    if (!stringp(spider->query_restrain_path())) return 0;
    return sscanf(target, spider->query_restrain_path() + "%s", tmp);
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int result = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
    if(result) return result;

    string envfile = file_name(environment(shadow_who));
    
    object *remaining_followers = filter(followers, 
        &is_target_within_restrain_path(envfile));
    
    object *lost_target = followers - remaining_followers;
    lost_target->notify_lost_target(shadow_who);

    foreach(object spider : remaining_followers) 
    {
        tell_room(environment(spider), ({
            "The " + spider->query_nonmet_name() + " chases after " 
            + shadow_who->query_name() + ".\n",

            "The " + spider->query_nonmet_name() + " chases after the "
            + shadow_who->query_nonmet_name() + ".\n",

            ""
        }), ({ shadow_who }), shadow_who);

        tell_room(environment(shadow_who), 
            capitalize(LANG_ADDART(spider->query_nonmet_name())) + " rushes in.\n");

        spider->move_living("M", environment(shadow_who), 0, 0);
    }

    followers = remaining_followers;
    if (!sizeof(followers)) remove_mirkwood_spider_follow_shadow();
    return result;
}

public void
add_following_spider(object spider)
{
    followers += ({ spider });
}

public void 
remove_following_spider(object spider)
{
    followers -= ({ spider });
    followers = filter(followers, objectp);
    if (!sizeof(followers)) remove_mirkwood_spider_follow_shadow();
}

public int
has_mirkwood_spider_follow_shadow()
{
    return 1;
}

public void
remove_mirkwood_spider_follow_shadow()
{
    remove_shadow();
}

public void
add_follow_shadow(object spider, object target)
{
    if (!target->has_mirkwood_spider_follow_shadow()) 
    {
        setuid();
        seteuid(getuid());
        object shadow = clone_object(MASTER);
        shadow->shadow_me(target);
    }

    target->add_following_spider(spider);
}

public void
do_die(object killer) 
{
    shadow_who->do_die(killer);
    remove_mirkwood_spider_follow_shadow();
}