#include <macros.h>
#include <language.h>

inherit "/std/food";

create_food()
{
    set_amount(400);
    set_name("loaf");
    add_name("bread");
    set_pname("loaves");
    add_adj("piece");
    set_short("@@size_str@@ loaf");
    set_pshort("@@size_pstr@@ loaf");
    set_long("This is @@what_str@@ loaf. It smells wonderful.\n");
    add_prop("_heap_s_unique_id", "@@size_str@@");
}

init()
{
    ::init();
    add_action("do_cut", "cut");
    add_action("do_slice", "slice");
}

string
size_str()
{
    switch(query_amount())
    {
	case 1..10:  return "very thin slice of a";
	case 11..40: return "thin slice of a";
	case 41..75: return "eight of a";
	case 76..150: return "quarter of a";
	case 151..250: return "half of a";
	case 251..375: return "off-cut piece of a";
	default:       return "large piece of a";
    }
}

string
size_pstr()
{
    switch(query_amount())
    {
	case 1..10:  return "very thin slices of a";
	case 11..40: return "thin slices of a";
	case 41..75: return "eights of a";
	case 76..150: return "quarters of a";
	case 151..250: return "halves of a";
	case 251..375: return "off-cut pieces of a";
	default:       return "large pieces of a";
    }
}

string
what_str()
{
    return LANG_ADDART(size_str());
}

int
do_cut(string arg)
{
    object copy;

    notify_fail(capitalize(query_verb())+" what?\n");
    if(!strlen(arg))
	return 0;

    if(!id(arg))
	return 0;
    if(query_amount()<41)
	return notify_fail("It would be better to slice it.\n");

    seteuid(getuid());

    copy = CLONE_COPY;

    copy -> set_amount(query_amount()/2);

    write("You cut "+check_call(short())+" in two.\n");

    set_amount(query_amount()/2);

    copy -> move(environment(this_object()));

    return 1;
}

int
do_slice(string arg)
{
    object copy;
    int new_amount;

    seteuid(getuid());

    notify_fail(capitalize(query_verb())+" what?\n");
    if(!strlen(arg))
	return 0;

    if(!id(arg))
	return 0;
    if(query_amount()<10)
	return notify_fail("It can't be sliced any more.\n");

    new_amount = random(MAX(query_amount()-5,10))+5;

    copy = CLONE_COPY;

    copy -> set_amount(new_amount);

    write("You slice a piece of "+check_call(short())+" in two.\n");
    set_amount(query_amount()-new_amount);

    copy -> move(environment(this_object()));

    return 1;
}
