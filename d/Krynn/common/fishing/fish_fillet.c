/*
 *  Fillet object from fish object.
 *
 *  Arman, April 2021
 */
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/food";
inherit "/lib/keep";

mixed * fish_value = ({ });
int vol, wgt, val;
string name, short, long;

#define FISH_DEBUG(x)  find_player("arman")->catch_msg("[Fish] " + x + "\n")

public void
set_fillet_attributes(int volume, int weight, int value, string n,
    string short_desc, string long_desc)
{
    vol = volume;
    wgt = weight;
    val = value;
    name = n;
    short = short_desc;
    long = long_desc;
}

public void
create_fillet()
{         
    set_name("@@fillet_name");
    set_short("@@fillet_short");
    set_pshort("@@fillet_pname");
    set_long("@@fillet_long");
    add_adj("@@fillet_name");

    // Food amount in grams.
    if(!wgt)
        wgt = 1;

    set_amount(wgt);

    add_prop(HEAP_I_UNIT_VOLUME, vol);
    add_prop(HEAP_I_UNIT_WEIGHT, wgt);
    add_prop(HEAP_I_UNIT_VALUE, val);
}

string
fillet_name()
{
    if(!strlen(name))
        return "fillet";

    return name;
}

string
fillet_short()
{
    if(!strlen(short))
        return "fish fillet";

    return short;
}

string
fillet_pshort()
{
    if(!strlen(short))
        return "fish fillets";

    return short + "s";
}

string
fillet_long()
{
    if(!strlen(long))
        return "A fish fillet of unknown origin.\n";

    return long;
}


public void 
create_food()
{
    add_name("fillet");
    add_pname("fillets");
    set_long("Default fish fillet object.\n");	
}

/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover. It will only function for food that has a
 *                real file rather than being cloned from /std/food.c
 *                since only the amount of food on the heap is saved.
 */
public string
query_recover()
{
    string file = MASTER;
    /* Don't recover bare /std/drinks since we only recover the amount of
     * drinks and no descriptions.
     */

    if (file == FOOD_OBJECT)
    {
        return 0;
    }

    return file + ":heap#" + num_heap() + "#" + vol + "&&" +
        wgt + "&&" + val + "&&" + name + "&&" +
        short + "&&" + long;
}

/*
 * Function name: init_recover
 * Description  : This function is called when the food recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_recover(string str)
{
    string foobar;
    int    num;

    if (sscanf(str, "%sheap#%d#%s", foobar, num, foobar) == 3)
    {
        set_heap_size(num);
    }

    string *a = explode(foobar,"&&");
    vol = atoi(a[0]);
    wgt = atoi(a[1]);
    val = atoi(a[2]);
    name = a[3];
    short = a[4];
    long = a[5];

    if(sizeof(a) > 1)
        create_fillet();
}
