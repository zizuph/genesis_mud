// -*-C++-*-
// file name:   /d/Avenir/common/bazaar/Obj/flower/posy.c
// creator(s):  Lilith July 1997
// last update:	  
// purpose:     This is a posy of flowers from the flower_stall.
// note:            
// bug(s):
// to-do:

#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"

/* Inherit the standard weapon file */
inherit "/std/weapon";
inherit "/d/Avenir/common/bazaar/Obj/flower/flower_base";

string
long_desc()
{
    string str; 

    str = "This posy has a half-dozen "+ colour +" "+ type +
          " flowers, arranged with sprays of baby's breath "+
          "and delicate, feathery fern fronds. "+
          flower_desc[type][2] +"\n   This lovely "+
          "flower arrangment is designed to be carried "+
          "in a woman's hands.";

    if (message)
        str += " It has a small card with a beautiful, handpainted "+
               "illustration of a "+ type +" on the cover. There "+
               "is a message inside.";

    return str +"\n";
}

string
short_desc()
{
    return "posy of "+ colour + " "+ (flower_desc[type][1]);    
}

string
pshort_desc()
{
    return "posies with "+ colour + " "+ (flower_desc[type][1]);    
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
        add_cmd_item(({ "card", "message", "posy", type +" card", 
            size +" card", type +" message", size +" message", 
            "card from "+ from, "message from "+ from }), "read", 
            VBFC_ME("message_desc") + "\n");
    }

    add_item(type, capitalize(flower_desc[type][2]) +"\n");
    add_cmd_item(({ type, "flower", "flowers", "posy", 
        (flower_desc[type][1]) }),
        ({"smell", "sniff" }), (flower_desc[type][3]) +"\n");
}

void
create_weapon()
{
    set_name("posy");
    add_name(({"flower arrangement"}));

    set_hit(0);
    set_pen(0);
    set_wt(W_CLUB);
    set_hands(W_LEFT);
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT,  50);
    add_prop(OBJ_I_VOLUME, 200);    
    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");
}

mixed wield()
{
    write("You hold the " + short() + " in your left hand.\n");
    say(QCTNAME(TP) + " holds a " + short() + " in "
        + POSSESS(TP) + " left hand.\n");
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

