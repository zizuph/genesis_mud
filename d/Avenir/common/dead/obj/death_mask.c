// file name: /d/Avenir/common/dead/obj/death_mask.c
// creator(s): Lilith, June 2021
// purpose:   Something to find inside the sarcophagi.
//            The wearer can get easier access to the 
//            Necronisi and the Catacombs -- can 
//            walk onto the boat (no need for a 
//            coffin ride) and pass the gatekeeper.
// note:      This is some work to get access to.
// updates:   fixed bug with adjs
//            Lilith, Nov 2021  Updated looseness so you can't wear multiples.
//            Lilith, Feb 2022  Added the ogre wear prop.

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";
#include "../dead.h"
#include <files.h>
#include <macros.h>
#include <wa_types.h>
#include <math.h>

string type, adj;

void set_mtype(string str)   { str = type;   }
void set_madj(string str)    { str = adj;    }

public string query_mtype()  { return type;  }
public string query_madj()   { return adj;   }

string my_long()
{
    return "It is a " + adj + " mask, made of pure "+ type 
        +". The face depicted on this funerary mask is elven, "
		+"most likely one of the High Lords or Chatelaines of "
		+"Sybarus. A trefoil shape has been stamped into the "
	    +"metal on the inside of the mask, over the center "
		+"of the forehead.\n";	
}	

void
configure_mask()
{
    if (!strlen(type))
	{
		type = one_of_list(({"copper","silver","gold","platinum"}));
        set_mtype(type);
	}
    add_adj(type);
	
    if (!strlen(adj))
	{
	   adj = one_of_list(({"stunning","gorgeous","spectacular", "bejewelled"}));
	   set_madj(adj);
    }	    
    add_adj(adj);	
   	
	set_short(adj +" "+ type +" death mask");	
}

void
create_object()
{
    set_name("mask");
	add_name(({"_Avenir_death_mask", "mask", "death mask", "high lord mask", "funerary mask"}));	
	set_adj("death");
    set_long(my_long);
    add_item(({"trefoil", "stamp"}), "This stamp is the trefoil "
        +"shape associated with the subterranean city of Sybarus.\n");	
	configure_mask();
    set_keep(1); 
    set_wf(this_object()); 	
	
	/* These are thin metallic masks, not armour */
	config_wearable_item(A_BROW, 1, 3, this_object());
    add_prop("_aod_wear_prop", 1); 
    add_prop(OBJ_I_VALUE, 1700 +(random(500)));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 500);
	
    if (IS_CLONE)
        set_item_expiration();
}

mixed
wear(object ob)
{
    object wearer = ENV(TO);
	if (wearer->query_prop(DMASK_PROP))
	    return -1;
	if (ob != this_object() || !living(wearer))
        return -1;	
    wearer->add_prop(DMASK_PROP, 1);		
    return 0;
}

mixed 
remove(object ob)
{
	object wearer = ENV(TO);
	if (wearer) 
        wearer->remove_prop(DMASK_PROP);
    return 0;
}	


void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
	::leave_env(from, to);
}

void
appraise_object(int num)
{
    appraise_wearable_item();
    ::appraise_object(num);
}

string
query_arm_recover()
{
    return "#TYPE#" + type + "#ADJ#" + adj;
}

void
init_arm_recover(string arg)
{
    string foo, foo2;
    if(!strlen(arg))
      return;
    sscanf(arg, "%s#TYPE#%s#ADJ#%s#N#%s", foo, type, adj, foo2);
	configure_mask();
    init_item_expiration_recover(arg);
}


public string
query_recover()
{
    return MASTER + ":#TYPE#" + type + "#ADJ#" + adj + "#N#"
	              + query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
