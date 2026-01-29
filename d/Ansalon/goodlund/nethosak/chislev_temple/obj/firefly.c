/*
 *  firefly.c
 *
 *  This is a firefly summoned by the druid, it
 *  will increase the levels of light in the room
 *  as well as cast blind on anyone who has
 *  nightvision.
 * 
 *  Created by Carnak, January 2016
 */
 
#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../local.h"

int life_time;


string
strLight()
{
    switch(this_object()->query_prop(OBJ_I_LIGHT))
    {
        case 0:
        return "The swarm of fireflies is spread out evenly "+
               "in the clearing.\n";
            break;
        case 1..6:
        return "The swarm begins to amass into a cluster just "+
        "above, engulfing the sky.\n";
            break;
        default:
        return "The swarm has covered the sky, forming a "+
        "glowing blanket above, filling the area with the "+
        "eerie green light.\n";
            break;
    }
}

void
create_object()
{
    add_name("swarm");
    add_name("firefly");
    set_name("fireflies");
    add_name("_chislev_swarm");
    set_short("swarm of fireflies");

    add_prop(OBJ_I_LIGHT, 0);
    add_prop(OBJ_M_NO_GET,    "How do you intend to capture a swarm "+
                              "of fireflies?\n");
    
    add_prop(OBJ_M_NO_ATTACK, "The fireflies swirl around in the "+
                              "air, avoiding your onslaught.\n");
    add_prop(OBJ_M_NO_MAGIC,  "As if corporeal, the fireflies "+
                              "avoid any attempts at harming them.\n");
}

public int
add_light(int i)
{
    tell_room(environment(this_object()),"The eerie green light grows "+
	"stronger as more fireflies emerge.\n",this_object(),this_object());
    add_prop(OBJ_I_LIGHT, i);
}

public void
init_lifetime()
{
    int light = this_object()->query_prop(OBJ_I_LIGHT)+random(5);
    
    if (random(light) > 25 && this_object()->query_prop(OBJ_I_LIGHT))
    {
        tell_room(environment(this_object()),"The fireflies scatter "+
		"in the wind.\n",this_object(),this_object());
        this_object()->remove_object();
        return;
    }
    
    if (light>this_object()->query_prop(OBJ_I_LIGHT))
        add_light(light);
    
    set_long("These fireflies emerged from nowhere, emitting an "+
    "eerie green glow which irritates your eyes. " + strLight());
    
    
    set_alarm(15.0, 0.0, &init_lifetime());
    
    object   tar,
            *targets = filter(all_inventory(environment(this_object())),
                         &->query_prop(LIVE_I_SEE_DARK));
    setuid();
    seteuid(getuid());
    
    object ob;
    int i;
    
    for ( i = 0; i < sizeof(targets); i++)
    {
        tar = targets[i];
        
        ob = clone_object(TDIR + "obj/blind");
        
        if (present("_firefly_blindness", tar))
        {
            ob->remove_object();
        }
        else if (random(4))
        {
            ob->set_blind_time(random(8)+16);
            ob->move(tar,1);
            ob->do_start();
        }
    }
}