// file name:    ~Avenir/common/bazaar/Obj/worn/qankr
// creator(s):    Grace  May  1995
// last update:            
// purpose:       ornamentation for the lovely dancer
// note:                   
// bug(s):                 
// to-do:                                           


inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

int times; /* How many times we can recover */
int  query_times()       {    return times;   }

void
create_object()
{
    config_wearable_item(A_R_ANKLE, 1, 15, this_object());

    if (times) times++;
    else       times = 1;

    set_keep(1);

    set_short("thick gold anklet");
    set_name("anklet");
    add_name(({"manacle", "fetter"}));
    set_adj(({"gold", "thick"}));
    set_long ("This thick gold anklet resembles a stylized fetter. "+
              "It is hammered to produce a scintillant surface with "+
              "a rich, dark colour. It looks like it is quite valuable.\n");

  add_prop(OBJ_I_VALUE,  700);
  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 500);
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


/*
 * Function name: query_my_recover
 * Description:   Return the recover strings for changing armour variables.
 * Returns:       Part of the recoder string
 */
string
query_my_recover()
{
    string rec; 

    if (times > 3)
        return 0;

    rec = MASTER + ":";
    rec += "#times#" + times;
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
    sscanf(arg, "%s#times#%d#%s", dummy, times, dummy);
    return;
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


