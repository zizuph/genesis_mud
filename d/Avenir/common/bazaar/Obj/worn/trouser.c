// Lilith May 2022, converted to use item_expiration
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

string color, type;

void set_color(string str) {    color = str;    }
void set_type(string str)  {    type = str;     }

void 
init_the_trousers()
{
    if (!color) color = one_of_list(({"blue","green","red",
                "yellow","ivory","purple","white","brown",
                "aquamarine","amethyst", "crimson","ochre",
                "grey","pink","scarlet","vermillion", 
	            "snowy","cream","lavender","fawn","tan",
                "black","orange", "indigo", "gold",
                "silver", "brown"}));
    if (!type) type = one_of_list(({"satin","velvet","silk","webcloth"}));
	
    set_short("diaphanous "+ color + " "+ type + " harem pants");

    set_long("These trousers are loose-fitting from waist to thigh, "+
           "they taper to fit snugly below the knee to the ankle. "+
           "They are "+ color +" in colour and are made of fine, "+
           "diaphanous "+ type + ".\n");

    set_adj(({color, type}));
}

void
create_object()
{
    config_wearable_item(A_LEGS, 1, 1, this_object());
    set_keep(1);

    if (!type)    init_the_trousers();

   set_name("bazaar_trousers");
   add_name("trousers");
   add_name(({"harem", "pants"}));
   set_adj("diaphanous");   
   add_pname(({"clothes", "clothing"}));

   add_prop(HEAP_S_UNIQUE_ID, "trousers_" + color + "_" + type);
   add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
   add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
   add_prop(OBJ_I_VALUE, 160);
   
   if (IS_CLONE)
      set_item_expiration();  	  
   
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


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}


/*
 * Function name: query_my_recover
 * Description:   Return the recover strings for changing armour variables.
 * Returns:       Part of the recoder string
 */
string
query_my_recover()
{
    string rec;

    rec = MASTER + ":";
    rec += "#type#" + type;
    rec += "#color#" + color;
    rec += query_item_expiration_recover(); 
    return rec;
}

/*
 * Function name: init_my_recover
 * Description:   Initialize the armour variables at recover.
 * Arguments:     arg - The recover string as recieved from query_arm_recover()
 */
void
init_my_recover(string arg)
{
    string dummy;

    sscanf(arg, "%s#type#%s#%s", dummy, type, dummy);
    sscanf(arg, "%s#color#%s#%s", dummy, color, dummy);
    init_item_expiration_recover(arg);
    init_the_trousers();
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
    return MASTER + ":" + query_my_recover();
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
    init_my_recover(arg);
}
