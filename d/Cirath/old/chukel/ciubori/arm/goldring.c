/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/arm/goldring.c
* Comments: Edited by Luther Oct. 2001
*/

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/std/combat/combat.h"
#include <wa_types.h>
#include "defs.h"

query_auto_load()
{
  	return MASTER;
}

public string 
show_subloc(string subloc, object me, object for_obj)
{
  	string data;

  	if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    		return "";

  	if(for_obj != me)
    		data = capitalize(this_player()->query_pronoun()) + 
           		" has a golden ring in "+TP->query_possessive()+
           		" nose.\n";
  	else
    		data = "You have your golden ring in your nose.\n";

  	return data;
}

void
create_object()
{
  	set_name("ring");
  	set_pname("rings");
  	add_name("ciubori_gold_ring");
  
  	set_short("golden nose-ring");
  	set_pshort("golden nose-rings");
  
  	set_adj("golden");
  
  	set_long("This is a golden nose-ring.\n");

  	add_prop(OBJ_M_NO_DROP,1);
  	this_object()->set_no_show_composite(0);
  	add_prop(OBJ_I_VALUE,250);
  	add_prop(OBJ_I_WEIGHT,10);
  	add_prop(OBJ_I_VOLUME,5);
}

init()
{
  	::init();
}

enter_env(object dest,object old)
{
  	remove_name("ciubori_gold_ring");
  	add_name("ciubori_gold_ring");
  	if(living(ENV(TO)))
  	dest->add_subloc("ciubori_gold_ring", this_object());
}

public void
leave_env(object from, object to)
{
  	this_player()->remove_subloc("ciubori_gold_ring");
}
