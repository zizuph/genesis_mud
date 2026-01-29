// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/flower/corsage.c
// creator(s):	  Lilith July 1997
// last update:	  Zielia July 2009 converted from armour to wearable ob
// purpose:       This is a wearable women's flower from the flower_stall.
// note:      
// bug(s):
// to-do:

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Avenir/common/bazaar/Obj/flower/flower_base";

#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"

string
long_desc()
{
    string str; 

    str = "This corsage is made with a "+ colour +" "+ type +
          " flower, along with a small spray of baby's breath "+
          "and a delicate, feathery fern frond. "+
          flower_desc[type][2] +"\n   This lovely, "+
          "compact flower arrangment is designed to be worn "+
          "pinned to a woman's clothing, over her heart.";

    if (message)
        str += " It has a small card with a beautiful, handpainted "+
               "illustration of a "+ type +" on the cover. There "+
               "is a message inside.";

    return str +"\n";
}

string
short_desc()
{
    return colour + " "+ (flower_desc[type][0]) +" corsage";    
}

string
pshort_desc()
{
    return colour + " "+ (flower_desc[type][0]) +" corsages";    
}

public string
message_desc()
{
    int last;
    string msg;

    if (!strlen(message))
        return "Thinking of you";
    if (!strlen(from))
        return "anonymous";

    last = message[strlen(message) - 1];
    if (last < 'A' || last > 'z')
        msg = capitalize(message);
    else
        msg = capitalize(message) + ".";

    return "Written in an ornate, flowing script are the letters:\n     "+
           msg +"\n          Signed:  "+ capitalize(from) +".\n";    
}

void
create_flower()
{
    add_adj(({ type, colour }));
    add_pname((flower_desc[type][1]));
    add_name(flower_desc[type][1]);
    set_short(VBFC_ME("short_desc"));
    set_pshort(VBFC_ME("pshort_desc"));
    set_long(VBFC_ME("long_desc"));

    if (strlen(message))
    {
        add_item(({"card", "message", type +" card", size +" card",
            type +" message", size +" message", "card from "+ from,
            "message from "+ from }), 
            VBFC_ME("message_desc"));
        add_cmd_item(({ "card", "message", "corsage", type +" card", 
            size +" card", type +" message", size +" message", 
            "card from "+ from, "message from "+ from }), "read", 
            VBFC_ME("message_desc") + "\n");

    }

    add_item(type, capitalize(flower_desc[type][2]) +"\n");
    add_cmd_item(({ type, "flower", "flowers", "corsage", 
        (flower_desc[type][1]) }),
        ({"smell", "sniff" }), (flower_desc[type][3]) +"\n");
}

void
create_object()
{
    set_name("corsage");
    add_name(({"flower arrangement"}));
    
    config_wearable_item(A_CHEST, 1, 10, this_object());

    add_prop(OBJ_I_WEIGHT,  50);
    add_prop(OBJ_I_VOLUME, 200);    
    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");
}

public int
wear(object ob)
{
    write("You wear the " + short() + " over your heart.\n");
    say(QCTNAME(TP) + " wears a " + short() + " over "
        + POSSESS(TP) + " heart.\n");
    return 1;
}

void
init_arg(string arg)
{
    sscanf(arg, "#SIZE#%s#TYPE#%s#COLOUR#%s", size, type, colour);
    create_flower();
}

mixed
query_auto_load()
{
    int i;
    
    /* 25% chance it won't auto-load after first time */
    if (!load)
    {
        i = random(4);    
        if (i == 3)
           return 0;
    }

    if(!strlen(type))
       return 0;

    /* if it is going to auto-load, don't drop it when quitting */
    add_prop(OBJ_M_NO_DROP, 1);
    set_alarm(1.0, 0.0, &remove_prop(OBJ_M_NO_DROP));

    return MASTER + ":#SIZE#"+ size +"#TYPE#"+ type +"#COLOUR#"+ 
                     colour;
}


public mixed
query_recover()
{
    return 0;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
