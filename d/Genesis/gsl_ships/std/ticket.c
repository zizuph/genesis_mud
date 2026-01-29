/*
 * Base ticket file
 * TAPAKAH, 01/2008
 *
 * Modification history:
 *   - 10/5/2017: Added weight and volume (Gorboth)
 */

#include <stdproperties.h>

inherit "/std/object";

static int price;

void set_price   (int value);
int  query_price ();
int  is_ticket   ();

void
create_ticket ()
{

	::create_object();
	
  set_name("ticket");
  set_long("Just a base ticket");
  
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 30);
}

public nomask void
set_price (int value)
{

  price = value;
  add_prop(OBJ_I_VALUE, value);
}

public nomask int
query_price ()
{

  return price;
}

public nomask int
is_ticket ()
{
  return 1;
}
