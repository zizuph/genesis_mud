// codpiece&breeches: see book in bazaar library
// converted to /lib/wearable_item by Lilith 09 Jul 1998
// converted to use item_expiration, code cleanup--Lilith, May 2022

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/sys/language.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

string name, size, tint;

void set_size(string str)  {    size = str;    }
void set_tint(string str)  {    tint = str;     }

public string query_size() {    return size;   }
public string query_tint() {    return tint;   }

void configure_me()
{
	string shstr;
	
    if (!strlen(name))
    {
        name = one_of_list(({"leggings","trousers","hose","breeches","trews"}));
    }
	
	if (!strlen(tint))
    {
        tint = one_of_list(({"blue","green","red",
                "yellow","ivory","purple","white","brown",
                "aquamarine","amethyst", "crimson","ochre",
                "grey","pink","scarlet","vermillion", 
	            "snowy","cream","lavender","fawn","tan",
                "black","orange", "indigo", "gold",
                "silver", "brown"}));
    }
	
	if (!strlen(size))
    {
        size = one_of_list(({"tiny","small","adequate", 
               "stupendous","huge","enormous","average", 
			   "large","modest"}));
    }
	
	add_name(name);	
    add_adj(tint);
    add_adj(size);
	
    shstr = tint +" "+ name +" with "+ LANG_ADDART(size) +" codpiece";	
    set_short(shstr);
}	
	
string my_long()
{
    return "These "+ name +" are "+ tint +" in colour. They are "+
           "very form-fitting and have "+ LANG_ADDART(size) + 
		   " decorated codpiece. This item of clothing can be "+
		   "worn under most armour.\n";
}


void
create_object()
{
   config_wearable_item(A_LEGS, 1, 1, this_object());
   configure_me();

   set_name("_codpiece_");
   set_long(my_long);
   set_adj(({"sybarun", "sybarite"}));
   add_pname(({"clothes", "clothing"}));
   
   set_keep(1);
   
   add_prop(HEAP_S_UNIQUE_ID, "codpiece_" + tint + "_" +name);
   add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
   add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
   add_prop(OBJ_I_VALUE, 200);

   add_item("codpiece", "It covers the crotch of tightfitting "+
      "men's trousers. It is decorated with various fertility "+
      "and virility symbols.\n");
   add_item(({"decoration", "decorations", "symbol", "symbols"}),
      "They are symbols of male potency.\n");
	  
   if (IS_CLONE)
      set_item_expiration();  	  
}             


public string
query_recover()
{
    return MASTER + ":#name#" + name + "#size#" + size + "#tint#" + tint + "#"+ query_item_expiration_recover();  
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

    sscanf(arg, "%s#name#%s#%s", dummy1, name, dummy2);
    sscanf(arg, "%s#size#%s#%s", dummy1, size, dummy2);
    sscanf(arg, "%s#tint#%s#%s", dummy1, tint, dummy2);
    init_item_expiration_recover(arg);
    configure_me();
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}


/*
 * Function name: leave_env
 * Description:   The clothing is moved from the inventory.
 * Arguments:     from - Where from  to - Destination.
 */
void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}
