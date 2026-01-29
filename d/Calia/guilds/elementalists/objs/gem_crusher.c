
/*
 * Gem Crusher
 * This is used by the Elemental Clerics to crush a gem into shards
 * which are used for some of their prayers (spells)
 *
 */
 
inherit "/std/object";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"

#define STD_SPELL_OBJ_DIR "/d/Genesis/specials/std/spells/obj/"
 
void 
create_object() 
{
    set_name(({"gem crusher","crusher"}));
    add_name("_temple_gem_crusher");
    set_adj("gem");
    set_short("gem crusher");
    set_long("It is a small vice-like machine that can be used to crush "+
        "gems into shards using the command <crush> <gem>.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_M_NO_INS,1);
    add_prop(OBJ_M_NO_TELEPORT,1);
}

public int
do_crush(string str)
{
	if (!str)
	{
		NF("Crush what?\n");
		return 0;
	}
	
	object dest_ob = present(str, TP);
	
	if (!dest_ob)
	{
		NF("Crush what?\n");
		return 0;
	}
	
	if (dest_ob->query_gem_shard())
	{
		NF("You cannot crush an already sharded gem.\n");
		return 0;
	}
		
	if (!dest_ob->query_gem())
	{
		NF("This only crushes gems.\n");
		return 0;
	}
	
	int num_gems = dest_ob->num_heap();
	
	if (!num_gems)
	{
		NF("You don't seem to have any "+str+"s that you can crush.\n");
		return 0;
	}
	
	int new_gems = (num_gems - 1);
	
	int num_shards = (5 + random(3));
	setuid();
        seteuid(getuid());
        object shard = clone_object(STD_SPELL_OBJ_DIR + "gem_shard");
        shard->config_shards(dest_ob->query_gem_name());
        shard->set_heap_size(num_shards);
        shard->move(TP,1);

	write("You insert your "+dest_ob->query_name()+" into the gem crusher and "+
	    "crush it. You collect "+LANG_NUM2WORD(num_shards)+" shards "+
	    "from the gem crusher.\n");
	say(QCTNAME(TP)+" inserts "+TP->query_possessive()+" "+dest_ob->query_name()+
	    " into the gem crusher and crushes it. "+capitalize(TP->query_pronoun())+
	    " collects "+LANG_NUM2WORD(num_shards)+" shards from the gem crusher.\n");
	    
	if (new_gems == 0)
		dest_ob->remove_object();
	else
		dest_ob->set_heap_size(new_gems);	
	return 1;
}

void
init()
{
    ::init();
    add_action(do_crush, "crush");
    add_action(do_crush, "shatter");
}
