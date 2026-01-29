// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/flower/circlet.c
// creator(s):	  Lilith July 1997
// last update:	  
// purpose:       This is a circlet of flowers from the flower_stall.
// note:            
// bug(s):
// to-do:
#pragma strict_types

/* Inherit the standard armour file */
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Avenir/common/bazaar/Obj/flower/flower_base";

#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"


public string
long_desc(void)
{
    string str; 

    str = "Several "+ colour +" "+ type +" flowers, their stems "+
    "interwoven to form a small wreathe or circlet. "+
    flower_desc[type][2] +"\n   This circlet is "+
    "designed to be worn on your head.";

    if (message)
	str += " It has a small card with a beautiful, handpainted "+
	"illustration of a "+ type +" on the cover. There "+
	"is a message inside.";

    return str +"\n";
}

public string
message_desc(void)
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

public string
short_desc(void)
{
    return "circlet of "+ colour + " "+ (flower_desc[type][1]);    
}

public string
pshort_desc(void)
{
    return "circlets of "+ colour + " "+ (flower_desc[type][1]);    
}


public void
create_flower(void)
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
	add_cmd_item(({ "card", "message", "circlet", type +" card", 
	    size +" card", type +" message", size +" message", 
	    "card from "+ from, "message from "+ from }), "read", 
	  VBFC_ME("message_desc") + "\n");

    }

    add_item(type, capitalize(flower_desc[type][2]) +"\n");
    add_cmd_item(({ type, "flower", "flowers", "circlet", 
	(flower_desc[type][1]) }),
      ({"smell", "sniff" }), (flower_desc[type][3]) +"\n");
}

public void
create_object(void)
{
    set_name("circlet");
    add_name(({"flower arrangement"}));

    set_slots(A_BROW);
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT,  50);
    add_prop(OBJ_I_VOLUME, 200);    
    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");
}

public int
wear(object obj)
{
    write("You rest the " + short() + " upon the crown of your head.\n");
    say(QCTNAME(TP) + " rests a " + short() + " upon the crown of "
      + POSSESS(TP) + " head.\n");
    return 1;
}

public void
init_arg(string arg)
{
    sscanf(arg, "#SIZE#%s#TYPE#%s#COLOUR#%s", size, type, colour);
    create_flower();
}

public string
query_auto_load(void)
{
    /* 25% chance it won't auto-load after first time */
    if (!load)
    {
	int i = random(4);    
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


public string
query_recover(void)
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
