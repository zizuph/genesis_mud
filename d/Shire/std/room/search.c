#include <language.h>
#include <stdproperties.h>
#include <macros.h>

static string *gSearch_items = ({}), *gSearch_places = ({});


nomask public int
add_search(mixed places, mixed items, int time = 5)
{
    if (stringp(places)) 
	gSearch_places = ({places});
    else if (pointerp(places))
	gSearch_places = places;
    else
	return 0;

    if (stringp(items)) 
	gSearch_items = ({items});
    else if (pointerp(items))
	gSearch_items = items;
    else
	return 0;

    if (this_object()->query_prop(OBJ_S_SEARCH_FUN))
	return 0;

    this_object()->add_prop(OBJ_S_SEARCH_FUN, "shire_search_fun");
    if (time <= 0)
	time = 5;
    this_object()->add_prop(OBJ_I_SEARCH_TIME, time);
    return 1;
}

nomask public string
shire_search_fun(object searcher, string what)
{
    object item;

    if (!present(searcher,this_object()))
	return 0;
    if (!what || member_array(what, gSearch_places))
	return 0;
    if (this_object()->query_searched())
	return 0;
    if (!sizeof(gSearch_items))
	return 0;

    setuid(); seteuid(getuid());
    item = clone_object(gSearch_items[random(sizeof(gSearch_items))]);
    if (!item)
	return 0;
    this_object()->set_searched(1);
    if (item->move(searcher, 1))
    {
	item->move(environment(searcher), 1);
	tell_room(this_object(), QCTNAME(searcher) + " finds something and "+
	  "places it on the "+(this_object()->query_prop(ROOM_I_INSIDE) ? 
	    "floor" : "ground")+".\n", searcher);
	return "You find "+LANG_ASHORT(item)+", but are unable to carry it so "+
	"you place it on the "+(this_object()->query_prop(ROOM_I_INSIDE) ? 
	  "floor" : "ground") + ".\n";
    }
    tell_room(this_object(), QCTNAME(searcher) + " finds something "+
      "and quickly picks it up.\n",searcher);
    return "You find "+LANG_ASHORT(item)+" and quickly pick it up.\n";
}

string *
query_search_items()
{
    return gSearch_items;
}

string *
query_search_places()
{
    return gSearch_places;
}

void
reset_shire_search()
{
    this_object()->set_searched(0);
}
