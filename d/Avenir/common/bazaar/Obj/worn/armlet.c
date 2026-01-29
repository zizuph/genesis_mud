// updated 07/15/98 by Lilith
// Lilith, May 2022:  added item_expiration for recovery

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

string metl, type;
string randtype();
string randmetl();

void set_metl(string str) {    metl = str;    }
void set_type(string str) {    type = str;    }

void
init_the_armlet()
{
    if (!metl) metl = randmetl();
    if (!type) type = randtype();

    set_short(type + " " + metl + " armlet");
    set_long("This "+ metl +" armlet has been carefully crafted. "+
           "The "+ metl +" is "+ type +", making it very much a work "+
           "of art that can be worn as jewelry. This armlet is "+
           "made to be worn on the left arm.\n");
    set_adj(({metl, type}));

}

/*************** Creation ************/
void
create_object()
{
    set_slots(A_L_ARM);    
    set_looseness(6);
    set_layers(3);
    set_wf(this_object());

    if (!metl)
        init_the_armlet();

    set_name("_bazaar_armlet");
    add_name("armlet");
    add_pname(({"clothes", "clothing"}));
    add_prop(HEAP_S_UNIQUE_ID, "armlet_" + metl + "_" + type);
    add_prop(OBJ_I_VOLUME, 500);   
    add_prop(OBJ_I_WEIGHT, 500);  
    add_prop(OBJ_I_VALUE, 250); 
    add_item("enamel", "The enamel is in translucent colours "+
        "that form exquisitely rendered symbols.\n");
    add_item(({"decoration", "decorations", "symbol", "symbols",
       "carving", "carvings"}), "They are symbols of male and "+
       "female potency.\n");
    add_item(({"gem", "gems"}), "The gems are semi-precious and "+
       "cut in tiny facets which glitter in the light.\n");
    set_keep(1);	  
	if (IS_CLONE)
	    set_item_expiration();  
}             


string
randmetl()
{
    string str;

    switch(random(10))
    {   
        case 0: str="gold";         break;
        case 1: str="silver";       break;
        case 2: str="blue crystal"; break;
        case 3: str="platinum";     break;
        case 4: str="brass";        break;
        case 5: str="copper";       break;
        case 6: str="bronze";       break;
        case 7: str="steel";        break;
        case 8: str="ivory";        break;
        case 9: str="onyx";         break;
    } 
    return str;                                                                               
}

string
randtype()
{
    string str;

    switch(random(9))
    {   
        case 0: str="enamelled";   break;
        case 1: str="gem-studded"; break;
        case 2: str="serpentine";  break;
        case 3: str="filigreed";   break;
        case 4: str="carved";      break;
        case 5: str="polished";    break;
        case 6: str="hammered";    break;
        case 7: str="delicate";    break;
        case 8: str="exquisite";   break;
    }
    return str;                                                                               
}

public mixed
wear(object ob)
{
    write("You wear the "+ short() +" high on your upper arm, near "+
        "the shoulder.\n");
    say(QCTNAME(this_player()) +" wears the "+ short() +" high on " + 
        this_player()->query_possessive() +" upper arm, near the "+
        "shoulder.\n");
    return 1;
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":#type#" + type + "#metl#" + metl + "#"+ query_item_expiration_recover();
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    string dummy1, dummy2;

    sscanf(arg, "%s#type#%s#%s", dummy1, type, dummy2);
    sscanf(arg, "%s#metl#%s#%s", dummy1, metl, dummy2);
    init_item_expiration_recover(arg);
    init_the_armlet();
}


void
leave_env(object dest, object old)
{
    /* If I don't call this func, and people drop or put this while 
     * it is worn, it looks like it is still in the players inventory
     */
    wearable_item_leave_env(dest, old);    

    ::leave_env(dest, old);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
