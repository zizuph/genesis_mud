// Ziggurat  (zig_harness.c)
// creator(s):   Zielia 2006 (copied base from punisher harness by Lilith)
// last update:
// purpose:
// note:  copied base from punisher harness by Lilith
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "zigg.h"
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

public static int gender;
public static string color = one_of_list(({"black","brown","red","blue",
    "green","purple",}));
public static string size = one_of_list(({"tiny","small","adequate",
    "stupendous","huge","enormous","average","large","modest"}));

public int query_gender()      {    return gender;   }
public string query_size()     {    return size;     }
public string query_color()    {    return color;    }

public void
set_gender(string str)
{
    if (str == "male")
    {
	gender = 1;
	return;
    }

    if (str == "female")
    {
	gender = 2;
	return;
    }

    gender = 0;
}

public void
set_size(string str)
{
    size = str;
}

public void
set_color(string str)
{
    color = str;
}

public void
create_object(void)
{
    config_wearable_item(A_TORSO, 1, 15, this_object());

    set_name("harness");
    add_name(({"garment", "leather", "stat::item"}));
    add_pname(({"clothes", "clothing"}));    
    set_short("@@my_short");
    add_adj(({"leather", "harness", color, "sybarun", "ziggurat"}));
    set_long ("@@my_long");
    add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
    add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
    add_prop(OBJ_I_VALUE, 400);

    gender = random(3);
	
	if (IS_CLONE)
      set_item_expiration();
}

public string
my_short(void)
{
    switch(gender)
    {
    case 0:
	return color +" leather harness";
    case 1:
	return color +" leather harness with "+ LANG_ADDART(size) +
	    " codpiece";
    case 2:
	return "scanty "+ color +" leather harness";
    }
}

public string
my_long(void)
{
    string str;

    switch(gender)
    {
    case 0:
	str = "\n";
	break;
    case 1:
	str = "The straps of leather radiate outward from two rings each "+
	      "centered on the back and torso. Two of the straps pass "+
	      "over the shounders, two circle the abdomen and two meet "+
	      "the legstraps of the attached leather codpiece.\n";
	break;
    case 2:
	str = "The straps of leather are woven in such a way as to pass "+
	      "behind the neck like a halter and part into thinner strands "+
	      "which curve around and between the breasts, framing them "+
	      "flatteringly while leaving them exposed. The straps criss-"+
	      "cross around the stomach before braiding together again to "+
	      "pass between the legs and up the back to the neck in one "+
	      "taut strip that does not seem like it was designed with "+
	      "comfort in mind.\n";
	break;
    }

    return "This harness is composed of straps of leather "+
	"intricately woven together and dyed "+ color +". It looks like "+
	"its function is mostly decorative, as it wouldn't be much "+
	"protection in a fight. "+ str;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover() +
	"#!"+ gender +"!"+ size +"!"+ color +"!#";
}

public void
init_recover(string arg)
{
    init_keep_recover(arg);
    sscanf(arg, "%s#!%d!%s!%s!#%s", arg,
	gender, size, color, arg);

    init_item_expiration_recover(arg);
}

