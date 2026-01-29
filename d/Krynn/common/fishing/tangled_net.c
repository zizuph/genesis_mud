/*
 *  Inheritable customisable object that contains a special object.
 *
 *  Description, accessing verb, reward file, and destruct
 *  message must be set in create_net object function.
 *
 *  Arman Kharas, October 2021 
 */

#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <language.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/object";
inherit "/lib/unique";

#define CLONE_MASTER    ("/d/Genesis/sys/global/unique")
#define JUNK             "/d/Krynn/common/fishing/junk"

string net_reward, custom_verb, destruct_msg;

public void
set_net_reward(string str)
{
    net_reward = str;
}

public string
query_net_reward()
{
    if(!strlen(net_reward))
        return JUNK;
    else
        return net_reward;
}

public void
set_custom_verb(string str)
{
    custom_verb = str;    
}

public string
query_custom_verb()
{
    if(!strlen(custom_verb))
        return "open";
    return custom_verb;
}

public void
set_destruct_msg(string str)
{
    destruct_msg = str;    
}

public string
query_destruct_msg()
{
    if(!strlen(destruct_msg))
        return "falls to pieces in your hands";
    return destruct_msg;
}

public void
create_net()
{
    // Mask this function to customize the object description, 
    // set the net reward, set the custom verb to 'open' the
    // object, and the object destruct message.

    set_name("net");
    set_adj("tangled");
    set_short("tangled net");
    set_long("An old abandoned net that has tangled itself " +
        "around something. You could probably try and " +
        "untangle the net to see what that object is.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);

    set_net_reward(JUNK);
    set_custom_verb("untangle");
    set_destruct_msg("falls to pieces in your hands");

    /*
     *  If you'd like the reward to be magical, you can mimick
     *  clone_unique by replacing set_net_reward with:
     * 
     * if (CLONE_MASTER->may_clone(MAGIC_ITEM_FILE, 20)) 
     *     set_net_reward(MAGIC_ITEM_FILE);
     * else
     *     set_net_reward(JUNK);
     * 
     */
}

void 
create_object()
{
    create_net();
}

public int
untangle_net(string str)
{
    object net_obj, reward;
    string reward_file = query_net_reward();
    string verb = query_verb();
    
    if(!strlen(str))
    {
        notify_fail(capitalize(verb)+ " what?\n");
        return 0;
    }
    if (!parse_command(str, deep_inventory(this_player()) + 
        deep_inventory(environment(this_player())), "[the] %o", net_obj))
    {
        notify_fail(capitalize(verb)+ " what??\n");
        return 0;
    }

    setuid();
    seteuid(getuid());
    reward = clone_object(reward_file);
    reward->move(this_player(), 1);
 
    write("You " +verb+ " " +LANG_THESHORT(net_obj)+ " to reveal " +
        LANG_ASHORT(reward)+ "! " +capitalize(LANG_THESHORT(net_obj))+ 
        " " +query_destruct_msg()+ ".\n");
    say(QCTNAME(this_player()) + " " +verb+ "s " +LANG_ASHORT(net_obj)+ 
        ", revealing " +LANG_ASHORT(reward)+ "!\n");

    net_obj->remove_object();
     
    return 1;
}

public void
init()
{
    ::init();
    add_action(untangle_net, query_custom_verb());
} 
