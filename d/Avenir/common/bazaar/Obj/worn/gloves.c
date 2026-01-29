// file name:    ~Avenir/common/bazaar/Obj/worn/gloves
// creator(s):    Lilith  15 January, 1997
// last update:   Lilith May 2022: converted to wearable item, etc
// purpose:       more frivolous clothing for dancers
// note:                   
// bug(s):                 
// to-do:                                           


inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/sys/language.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Avenir/include/defs.h"

#define HIS  this_player()->query_possessive()

string color, type;

void set_color(string str) {    color = str;    }
void set_type(string str)  {    type = str;     }
  
void
init_the_gloves()
{
    if (!color) color = one_of_list(({"blue","green","red",
                "yellow","ivory","purple","white","brown",
                "aquamarine","amethyst", "crimson","ochre",
                "grey","pink","scarlet","vermillion","grey", 
	            "snowy","cream","lavender","fawn","tan",
                "black","orange","indigo","gold", "silver"}));
	
    if (!type) type = one_of_list(({"satin","lace","silk","webcloth"}));

    set_short("pair of long "+ color + " "+ type + " gloves");
    set_pshort("pairs of long "+ color + " "+ type + " gloves");
    set_long("These "+ type +" gloves are a product of fine Sybarite "+
           "craftsmanship. They mold the hands perfectly and fit "+
           "snugly from wrist to just below the elbow. Elegant and "+
           "the height of fashion, they are "+ color +" in colour.\n");
    set_adj(({color, type}));
}

mixed
wear(object ob)
{
    write("You slip the "+ short() +" over your "+
        "hands and smooth them up your forearms.\n");
    say(QCTNAME(this_player()) +" slips into the "+ 
        short() +" and smoothes them up to "+ HIS +" elbows.\n");
    return 1;
}

mixed
remove(object ob)
{
    object tp = query_worn();

    tell_object(tp, "You pull the "+ short() +" off your "+
        "hands, one finger at a time.\n");
    say(QCTNAME(tp) +" pulls the "+ short() +" off "+ HIS +
        " hands one finger at a time.\n");
    return 1;
}

/*************** Creation ************/
void
create_object()
{
    config_wearable_item(A_HANDS, 1, 1, this_object());
    set_keep(1);

    if (!type)
       init_the_gloves();

    set_name("bazaar_gloves");
    add_name("gloves");
    set_pname("gloves");
    add_pname(({"clothes", "clothing"}));
    add_adj(({"long", "sybarun", "sybarite"}));

    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE, 125);
	  
   if (IS_CLONE)
      set_item_expiration();  	  	
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
    return MASTER + ":#type#" + type + "#color#" + color + "#"+ query_item_expiration_recover();
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
    sscanf(arg, "%s#color#%s#%s", dummy1, color, dummy2);
    init_item_expiration_recover(arg);
    init_the_gloves();
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
