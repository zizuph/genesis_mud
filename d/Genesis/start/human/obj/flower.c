/*
 *   A standard heap of flowers. 	Styles 920710.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/heap";

#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
  
#define FLOWER_TYPES  ({ "dandelion",  "daisy",  "lilly",  "rose" })
#define FLOWER_PTYPES ({ "dandelions", "daisys", "lillys", "roses" })
#define FLOWER_VALUES ({ 1           ,  1      ,  2      ,  5 })
#define FLOWER_BOUKET ({ 100         ,  50     ,  10     ,  1 })
#define FLOWER_WEIGHT ({ 1           ,  1      ,  1      ,  2 })
#define FLOWER_VOLUME ({ 1           ,  1      ,  1      ,  2 })

void set_flower_type(string str);

string flower_type;

void
create_flowers()
{
    set_name(FLOWER_TYPES[0]);
    set_pname(FLOWER_PTYPES[0]);
    set_name("flower");
    add_pname("flowers");
    set_heap_size(1);
    set_flower_type(FLOWER_TYPES[0]);
}

void
create_heap()
{
    create_flowers();
    if (!query_prop(HEAP_S_UNIQUE_ID))
	set_flower_type(FLOWER_TYPES[0]);
}

void
reset_heap()
{
    this_object()->reset_flowers();
}

string
short()
{
    string str;

/*  if (!strlen(query_prop(HEAP_S_UNIQUE_ID)))
    {
        call_out("remove_object",1);
        return "ghost flowers";
    }
 */

    if (flower_type != "")
        str = " ";
    else
        str = "";
    if (num_heap() < 1) return 0;
    if (num_heap() < 2) return "a" + str + flower_type;

    if (num_heap() < 12)
	return LANG_WNUM(num_heap()) + str + flower_type;
 
    if (this_player() && this_player()->query_stat(SS_INT)/2 > num_heap())
	return num_heap() + str + flower_type;
    else
	return (num_heap() < 1000 ? "a large bouqet of" : "a huge bouqet of")
	    + str + flower_type;
}

string
long()
{
    if (num_heap() > 1)
	return "It's "+ short() +" and they are all very pretty.\n";
    else
	return "It's "+ short() +" and it's very pretty.\n";
}

void
set_flower_type(string str)
{
    int ix;

    mark_state();
    if (flower_type)
    {
        remove_name(flower_type + " flower");
        remove_adj(flower_type);
    }
    ix = member_array(str, FLOWER_TYPES);
    flower_type = str;
    if (ix >= 0)
    {
        add_prop(HEAP_I_UNIT_VALUE, FLOWER_VALUES[ix]);
        add_prop(HEAP_I_UNIT_WEIGHT, FLOWER_WEIGHT[ix]);
        add_prop(HEAP_I_UNIT_VOLUME, FLOWER_VOLUME[ix]);
    }

    add_prop(HEAP_S_UNIQUE_ID,"_flower_" + flower_type);
    add_name(flower_type + " flower");
    set_adj(flower_type);
    update_state();
}

string query_flower_type() { return flower_type; }

void
config_split(int new_num,mixed orig)
{
    ::config_split(new_num,orig);

    set_flower_type(orig->query_flower_type());
}
