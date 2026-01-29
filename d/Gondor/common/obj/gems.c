/*
 * /d/Gondor/common/obj/gems.c
 *
 * Copied from /std/coins.c
 *
 *	Copyright (c) 1995 by Christian Markus
 *
 * 15-February-98, Gnadnar:     in set_gem_type(), use LANG_PWORD
 *      to add pname. we were generating "rubys".
 *
 * July 24 2001 by Mercade: Changed to use Genesis gems instead of Gondorian
 *   gems when possible.
 */

#pragma strict_types
inherit "/std/heap";
inherit "/lib/keep";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/gems.h"

#define GENESIS_GEM_DIR "/d/Genesis/gems/obj/"

void   set_gem_type(string str);

static string   gem_type;

public void
create_gems()
{
    set_heap_size(1);
    set_gem_type(GEM_TYPES[0]);
}

public nomask void
create_heap()
{
    set_name("gem");
    set_pname("gems");
    create_gems();

    if (!query_prop(HEAP_S_UNIQUE_ID))
        set_gem_type(GEM_TYPES[0]);
}

public nomask
void reset_heap() { this_object()->reset_gems(); }

void
rem_drop_prop()
{
    remove_prop(OBJ_I_NO_DROP);
}

string
query_auto_load()
{
    add_prop(OBJ_I_NO_DROP, 1); /* Destruct when saving */
    set_alarm(1.0, 0.0, rem_drop_prop);

    /* If a similar genesis gem exists, use that one. */
    if (file_size(GENESIS_GEM_DIR + gem_type + ".c") > 0)
    {
        return GENESIS_GEM_DIR + gem_type + ":" + num_heap();
    }
    else
    {
        return MASTER + ":" + num_heap() + "," + gem_type;
    }
}

/* 
 * Called when autoloading
 */
void
init_arg(string arg)
{
    int sum;
    string ct;

    if (sscanf(arg, "%d,%s", sum, ct) == 2)
    {
         set_heap_size(sum);
         set_gem_type(ct);
    }
}

public varargs string
short()
{
    string str;
    
    if (!strlen(query_prop(HEAP_S_UNIQUE_ID)))
    {
        call_out("remove_object", 1);
        return "ghost gems";
    }
    if (gem_type != "")
        str = " ";
    else
        str = "";
    if (num_heap() < 1) return 0;
    if (num_heap() < 2) return LANG_ADDART(gem_type);
    
    if (num_heap() < 12) 
        return LANG_WNUM(num_heap()) + str + LANG_PWORD(gem_type);
    
    if (this_player() && this_player()->query_stat(SS_INT) / 2 > num_heap())
        return num_heap() + str + LANG_PWORD(gem_type);

    return (num_heap() < 1000 ? "many" : "a huge heap of")
   + str + LANG_PWORD(gem_type);
}

varargs public mixed
long()
{
    /* It is a heap of ...
     */
    if ((num_heap() < 2) || (num_heap() >= 1000))
   return "It is " + short() + ", it looks pretty and quite valuable.\n";
    else
   return "These are " + short() + ", they sparkle and look quite valuable.\n";
}

/*
 * Description: Set the type of gems we have here.
 */
void  
set_gem_type(string str)
{
    int ix;

    mark_state();
    if (gem_type)
    {
        remove_name(gem_type + " gem");
        remove_name(gem_type);
        remove_name("_gem_ingredient");
        remove_pname(gem_type+"s");
        remove_adj(gem_type);
    }
    ix = member_array(str, GEM_TYPES);
    gem_type = str;
    if (ix >= 0)
    {
        add_prop(HEAP_I_UNIT_VALUE, GEM_VALUES[ix]);
        add_prop(HEAP_I_UNIT_WEIGHT, GEM_WEIGHT[ix]);
        add_prop(HEAP_I_UNIT_VOLUME, GEM_VOLUME[ix]);
    }
    
    if (ix >= GEMS_NOT_INGREDIENT)
        add_name("_gem_ingredient");
    add_prop(HEAP_S_UNIQUE_ID, "_gem_" + gem_type);
    add_name(gem_type + " gem");
    add_name(gem_type);
    add_pname(LANG_PWORD(gem_type));
    set_adj(gem_type);
    update_state();
}

/*
 * Description: Return what type of gems we have.
 */
string query_gem_type() { return gem_type; }

void
config_split(int new_num,mixed orig)
{
    ::config_split(new_num, orig);
    set_gem_type(orig->query_gem_type());
}

string
query_smiths_item()
{
    if (member_array(gem_type, GEMS_FOR_SMITHS_BONUS) >= 0)
        return "gondor_gem";
    else return "gondor_cheap_gem";
}

string
stat_object()
{
    string str;

    str = ::stat_object();

    str += "Gem type: " + gem_type + "\n";

    return str;
}

int
convert_to_base()
{
    int b;
    b = num_heap() * GEM_VALUES[member_array(gem_type, GEM_TYPES)];
    return b / GEM_VALUES[0];
}
