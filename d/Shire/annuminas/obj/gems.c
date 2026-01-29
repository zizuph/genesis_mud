/*
 * /d/Gondor/common/obj/gem.c
 *
 * Copied from /std/coins.c
 */
inherit "/std/heap";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

void rem_drop_prop();
void   set_gem_type(string str);

#define GEM_TYPES	({ "amber", "jade", "garnet", \
                           "tourmaline", "turquoise", "emerald", \
                           "opal", "topaz", "sapphire", \
                           "ruby", "smaragd", "diamond", })
#define GEM_VALUES	({ 144,  216,  288,  432,  576,  864, \
                          1152, 1728, 2304, 3456, 4608, 6912, })
#define GEM_WEIGHT	({   6,    6,    6,    6,    6,    6, \
                             6,    6,    6,    6,    6,    6, })
#define GEM_VOLUME	({   6,    4,    3,    3,    2,    2, \
                             1,    1,    1,    1,    1,    1, })

int alarm_id;
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
    add_name("_gem_ingredient");
    create_gems();

    if (!query_prop(HEAP_S_UNIQUE_ID))
        set_gem_type(GEM_TYPES[0]);
}

public nomask
reset_heap() { this_object()->reset_gems(); }

string
query_auto_load()
{
    add_prop(OBJ_I_NO_DROP, 1); /* Destruct when saving */
    alarm_id = set_alarm(1.0,0.0,&rem_drop_prop());
    return MASTER + ":" + num_heap() + "," + gem_type;
}

void rem_drop_prop()
{
    remove_alarm(alarm_id);
    remove_prop(OBJ_I_NO_DROP);
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
        remove_object();
        return "ghost gems";
    }
    if (gem_type != "")
        str = " ";
    else
        str = "";
    if (num_heap() < 1) return 0;
    if (num_heap() < 2) return LANG_ADDART(gem_type);
    
    if (num_heap() < 12) 
        return LANG_WNUM(num_heap()) + str + gem_type + "s";
    
    if (this_player() && this_player()->query_stat(SS_INT) / 2 > num_heap())
        return num_heap() + str + gem_type + "s";

    return (num_heap() < 1000 ? "many" : "a huge heap of")
   + str + gem_type + "s";
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
    
    add_prop(HEAP_S_UNIQUE_ID, "_gem_" + gem_type);
    add_name(gem_type + " gem");
    add_name(gem_type);
    add_pname(gem_type+"s");
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
stat_object()
{
    string str;

    str = ::stat_object();

    str += "Gem type: " + gem_type + "\n";

    return str;
}

