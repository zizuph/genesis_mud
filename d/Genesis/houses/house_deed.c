

inherit "/std/object";

#include "./defs.h"
#include <macros.h>
#include <stdproperties.h>

string house_name;
int auction_price;

public create_object()
{

  set_short("house deed");
  set_name("deed");
  add_adj("house");
  
  add_prop(OBJ_M_NO_STEAL, 1);
  add_prop(OBJ_M_NO_SELL, 
      "This is far too valuable to sell in a normal shop.\n");
  set_long("This is the deed to an unknown house.\n");
}

public void set_house_name(string str)
{
	mapping details = HOUSE_MANAGER->get_house_details(str);
	if (!mappingp(details))
	{
		tell_object(environment(this_object()),
		    "The house for this deed no longer " +
			"exists, and the deed vanishes.\n");
		remove_object();
		return;
	}
    house_name = str;
	set_short("deed for " + details[KEY_SHORT]);
	add_adj(details[KEY_SHORT]);
	set_long("This is the deed for " + details[KEY_SHORT] + "." +
      "  The taxes cost " + details[KEY_WEEKLY_TAX] + " platinum per week." +
	  "  It can be given to Sildan to finalize ownership of " +
	  "the house to you.\n");
	
}

public string query_house_name()
{
    return house_name;
}

public int query_auction_price()
{
    return auction_price;
}

public int is_valid_house_deed()
{
    if (!strlen(house_name))
    {
        return 0;
    }
    mapping details = HOUSE_MANAGER->get_house_details(house_name);
	if (!mappingp(details))
    {
        return 0;
    }
    return 1;
}

public int is_owner(object player)
{
    mapping details = HOUSE_MANAGER->get_house_details(house_name);
  
    if (mappingp(details))
    {
        if (details[KEY_OWNER] == player->query_real_name())
	    {
		    return 1;
        }
    }
    return 0;
}

public void tear_deed()
{
    HOUSE_MANAGER->deed_removed(house_name);
    remove_object();
}

public int
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (is_owner(to))
    {
        to->catch_tell("You already own the house, so you don't need a deed "
        + "to take possession.  You tear it up.\n");
        set_alarm(0.1, 0.0, tear_deed);
        return 0;
    }

    return 1;
}



public string
query_recover()
{
     return MASTER_OB(this_object()) + ":" + 
     "NAME##" + house_name + "##PRICE##" + auction_price;
}

public void notify_auction_sale_price(int price)
{
    auction_price = price;
}

public void
init_recover(string arg)
{
    if (!strlen(arg))
    {
        return;
    }
    string name;
    int price;
    if (!sscanf(arg, "NAME##%s##PRICE##%d##", name, price))
    {
        return;
    }
    set_house_name(name);
    auction_price = price;
}

