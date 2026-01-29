#pragma strict_types
/*
 * /d/Avenir/inherit/storage.c
 *
 * This file is to be inherited into all storerooms for shops. It makes sure
 * that there are just a few items in stock in the shop. Too many items
 * occupy too much memory.
 */
inherit "/std/room";
inherit "/lib/store_support";

public static string shop_file;
public static object shop_object;


public void
set_shop_room(string shop)	{ shop_file = shop; }

public string
query_shop_room(void)		{ return shop_file; }

public object
query_shop_object(void)		{ return shop_object; }

public object
get_shop_object(void)
{
    if (objectp(shop_object))
	return shop_object;

    catch(shop_object = shop_file->get_this_object());

    return shop_object;
}

/*
 * Function name: hook_store_update
 * Description	: Call after store_update to allow for additional handling.
 */
public void
hook_store_update(object obj)	{ }

public void 
store_update(object obj)
{
    ::store_update(obj);
    hook_store_update(obj);
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}

/*
 * Function name: hook_reset_store
 * Description	: Called after reset_store to allow for additional handling.
 */
public void
hook_reset_store(void)		{ }

public void
reset_store(void)
{
    ::reset_store();
    hook_reset_store();
}

public void
reset_room(void)		{ reset_store(); }

public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);
    get_shop_object()->force_new_list();
}
