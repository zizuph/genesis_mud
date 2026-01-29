// codpiece&breeches: see book in bazaar library
// converted to /lib/wearable_item by Lilith 09 Jul 1998
// copied and altered by Zielia to be worn by NPC rynal.c June 2006

#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

public string randsize(void);
public static string size = randsize();

public void
create_object(void)
{
    config_wearable_item(A_LEGS, 1, 1, this_object());

    set_name("_codpiece_");
    add_name(({"trousers","clothing"}));
    add_pname("clothes");
    set_short("@@short_desc");
    set_long("@@long_desc");
    set_adj(size);
    set_adj(({"bright","white"}));
    
    add_prop(HEAP_S_UNIQUE_ID, "codpiece_white_trousers");
    add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
    add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
    add_prop(OBJ_I_VALUE, 200);

    add_item("codpiece", "It covers the crotch of tightfitting "+
      "men's trousers. It is decorated with various fertiliy "+
      "and virility symbols.\n");
    add_item(({"decoration", "decorations", "symbol", "symbols"}),
      "They are symbols of male potency.\n");
	
	set_keep(1);
			
	if (IS_CLONE)
      set_item_expiration();  	

	
}

public string
randsize(void)
{
    string str;

    switch(random(6))
    {
    case 0: str = "titanic";          break;
    case 1: str = "magnificent";      break;
    case 2: str = "brobdingnagian";   break;
    case 3: str = "gargantuan";       break;
    case 4: str = "humongous";        break;
    case 5: str = "massive";          break;
    case 6: str = "tremendous";       break;
    }
    return str;
}

public string
short_desc(void)
{
    return "bright white pair of trousers with a " +size+ " codpiece";
}

public string
long_desc(void)
{
    return "These trousers are white in colour. They are "+
    "very form-fitting and have a " +size+ " decorated "+
    "codpiece. This item of clothing can be worn under "+
    "most armour.\n";
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
    return MASTER + ":" + query_item_expiration_recover(); 
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}
