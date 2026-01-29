// - candy_sh.c
// creator(s):   Zielia 2007
// last update:
// purpose:   Shadow for candy so you can taste it on the eater's lips when
//            they are kissed.
// note:      works with candy_lips.c
// bug(s):
// to-do:/*

#pragma no_shadow
#pragma strict_types

#include "zigg.h"
#include <language.h>
inherit "/std/shadow";

private static string *flavors;

public object
query_zig_candy_shadow(void)	{ return TO; }

public string *
query_flavors(void)		{ return flavors; }

public void
set_flavors(string *arr)	{ flavors = arr; }

public void
remove_candy_sh(void)		{ remove_shadow(); }

/*
 * Capture some emote hooks.
 *
 *  oblist->emote_hook(query_verb(), this_player(), adverb, all_oblist,
 *	cmd_attr, 1);
 */
public void
emote_hook(string emote, object actor, string adverb,
    		object *oblist, int attr, int target)
{
    if (!target || !query_interactive(actor))
    {
	shadow_who->emote_hook(emote, actor, adverb, oblist, attr, target);
	return;
    }

    switch(emote)
    {
    case "kiss":
    	if(!strlen(adverb))
    	    break;
    	    
	actor->catch_tell(capitalize(HIS(shadow_who)) +" lips taste "+ 
	    one_of_list(({"delicious", "scrumptious", "wonderful", 
	    "delectable", "delightful", "divine"}))+ ", like "+
	    one_of_list(flavors) +".\n");
	break;
    case "french":
	actor->catch_tell("You lick away every last trace of "+ 
	    one_of_list(({"delicious", "scrumptious", "wonderful", 
	    "delectable", "delightful", "divine"})) +" "+ 
	    one_of_list(flavors) +" from "+ HIS(shadow_who) +" lips.\n");

            object ob = present("Zig::Cbreath", shadow_who);
	    
	set_alarm(1.0, 0.0, ob->remove_object);
	   
	break;	
    case "dkiss":
	actor->catch_tell("You savor the taste of "+  HIS(shadow_who) +" "+
	    one_of_list(flavors) +"-flavored lips.\n");
	break;	
    }
    
    shadow_who->emote_hook(emote, actor, adverb, oblist, attr, target);
}
