/*
 *  Net spawned through fishing at Reefcutter Bay 
 *  for Ansalon-based Robe of the Darkling Sea quest.
 *  (see /d/Ansalon/QUESTS/)
 *
 *  inherits /d/Krynn/common/fishing/tangled_net.c
 *
 *  Arman Kharas, October 2021 
 */

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/common/fishing/tangled_net";

#define ROBEOFWOVENWORMS "_zeboim_robe_of_woven_worms"
#define ROBE             "/d/Ansalon/goodlund/kendermore/obj/zebrobe"
#define JUNK             "/d/Krynn/common/fishing/junk"

public void
create_net()
{
    // Mask this function to customize the object description, 
    // set the net reward, set the custom verb to 'open' the
    // object, and the object destruct message.

    set_name("net");
    set_adj("tangled");
    set_short("tangled net");
    set_long("A decaying net from the deck of the shipwreck " +
        "the 'Darkling Sea' that has tangled itself " +
        "around something. You could probably try and " +
        "untangle the net to see what that object is.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);

    set_net_reward(ROBE);
    set_custom_verb("untangle");
    set_destruct_msg("falls to pieces in your hands");

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

    // If the player already has a robe in their inventory
    // spawn junk object instead.
    setuid();
    seteuid(getuid());
    if (!present( ROBEOFWOVENWORMS, this_player() ))
        reward = clone_object(reward_file);
    else
        reward = clone_object(JUNK);

    reward->move(this_player(), 1);
 
    write("You " +verb+ " " +LANG_THESHORT(net_obj)+ " to reveal " +
        LANG_ASHORT(reward)+ "! " +capitalize(LANG_THESHORT(net_obj))+ 
        " " +query_destruct_msg()+ ".\n");
    say(QCTNAME(this_player()) + " " +verb+ "s " +LANG_ASHORT(net_obj)+ 
        ", revealing " +LANG_ASHORT(reward)+ "!\n");
    net_obj->remove_object();
      
    return 1;
}