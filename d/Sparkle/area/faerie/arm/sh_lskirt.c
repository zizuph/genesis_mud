/*
 * Cowhide skirt
 * -- Finwe, April 2005
 * spin around with skirt flaring out around you.
 */

#pragma save_binary;

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_object()
{
    setuid(); seteuid(getuid());

    set_name("skirt");
    set_short("cowhide skirt");
    set_long("This "+short()+" is made of soft leather. It flares out " +
        "from the waist and extends to your ankles. The skirt is decorated " +
        "with diamond shaped stitching.\n");
    add_item(({"stitching", "diamond shaped stitching", "diamond pattern"}),
        "It is a diagonal pattern sewn into the skirt, criss-crossing " +
        "each other to form a continuous diamond pattern.\n");
    add_item(({""}),
        "\n");
    
    set_slots(A_WAIST);
    set_layers(0);
    set_looseness(5);

    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 5);
}

void
init()
{  
   ::init();
   add_action("raise_skirt", "raise");
   add_action("raise_skirt", "lift");
   add_action("spin_skirt", "spin");
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}


/*
 * raise_skirt - raise skirt to flirt with
 */
int
raise_skirt(string str)
{
    object *oblist;
    int x,y;
    string *raise_type, *body_part;

    raise_type = ({"drool over", "gaze at", "oogle at", "yearn for", 
        "look at flirtatiously" }); 
    body_part = ({"pretty ankles", "muscular calves", "knobby knees", 
        "lovely legs", "shapely thighs"});

    x = random(sizeof(raise_type));
    y = random(sizeof(body_part));
    
    notify_fail("You must wear the " + short() + " first!\n");
    if(!query_worn())
        return 0;

    // no string supplied
    if(!strlen(str) || str=="skirt" )
    {
	    write("You raise your "+short()+" exposing your "+body_part[y]+" " +
            "for all to "+raise_type[x]+".\n");
	    all(" raises " + HIS_HER(TP) + " "+short()+" showing off " + 
            HIS_HER(TP) + " "+body_part[y]+" for you to "+raise_type[x]+".\n");
	return 1;
    }
}

int
spin_skirt(string str) 
{
    notify_fail("You must wear the " + short() + " first!\n");
    if(!query_worn())
        return 0;

    if(!strlen(str) || str=="around" )
    {
        write("You spin around, the " + short() + " flaring out " +
            "around you.\n");
        all(" spins around, " +HIS_HER(TP)+" " +short()+
            " flaring out around " +HIM_HER(TP)+".\n");
        return 1;
    }
}
