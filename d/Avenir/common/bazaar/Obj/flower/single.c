// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/flower/single.c
// creator(s):	  Lilith July 1997
// last update:	  
// purpose:       This is a single flower from the flower_stall.
// note:      
// bug(s):
// to-do:
#pragma strict_types

/* Inherit the standard weapon file */
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/d/Avenir/common/bazaar/Obj/flower/flower_base";
#include <language.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"


public string
long_desc(void)
{
    string str; 

    str = "This is a single "+ colour +" "+ type +
    " flower. "+ flower_desc[type][2];

    if (message)
	str += " It has a small card with a beautiful, handpainted "+
	"illustration of "+ LANG_ADDART(type) +" on the cover. There "+
	"is a message inside.";

    return str +"\n";
}

public string
short_desc(void)
{
    return "single "+ colour + " "+ (flower_desc[type][0]);    
}

public string
pshort_desc(void)
{
    return "single "+ colour + " "+ (flower_desc[type][1]);    
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

public void
create_flower(void)
{
    add_adj(({ size, colour }));
    add_pname((flower_desc[type][1]));
    add_name((flower_desc[type][0]));
    set_short(VBFC_ME("short_desc"));
    set_pshort(VBFC_ME("pshort_desc"));
    set_long(VBFC_ME("long_desc"));

    if (strlen(message))
    {
	add_item(({"card", "message", type +" card", size +" card",
	    type +" message", size +" message", "card from "+ from,
	    "message from "+ from }), 
	  VBFC_ME("message_desc"));
	add_cmd_item(({ "card", "message", "single ", type +" card", 
	    size +" card", type +" message", size +" message", 
	    "card from "+ from, "message from "+ from }), "read", 
	  VBFC_ME("message_desc") + "\n");

    }

    add_item(({"flower", "flowers"}), VBFC_ME("long_desc"));
    add_cmd_item(({ type, "flower", "flowers", "single", 
	(flower_desc[type][1]) }),
      ({"smell", "sniff" }), (flower_desc[type][3]) +"\n");
}

public void
create_object(void)
{
    set_name("single");
    add_name(({"flower arrangement", "flower"}));

    set_slots(W_ANYH);

    add_prop(OBJ_I_WEIGHT,  50);
    add_prop(OBJ_I_VOLUME, 200);    
    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");
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

    return MASTER + ":#SIZE#"+ size +"#TYPE#"+ type +"#COLOUR#"+ colour;
}

public string
query_recover(void)
{
    return 0;
}

public int
smell_flower(string str)
{
    if ((str) && (str == type))
    {
	write("You inhale the scent from the " +type+ " and think " +
	  "fondly of the person you got it from.\n");
	say(QCTNAME(TP) + " lifts the " +TO->short()+ " to "+
	   TP->query_possessive() +" face and smells it. "+
	   capitalize(TP->query_pronoun())+
	  " gets a look on " +TP->query_possessive()+ " face " +
	  "making you belive " +TP->query_pronoun()+ " might " +
	  "be in love.\n");
	return 1;
    }
    return 0;
}

public void
init(void)
{
    ::init();
    add_action("smell_flower","smell");
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}
