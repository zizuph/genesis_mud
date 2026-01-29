/*
 * Tracks and reports changes to objects in the game.
 *
 * This was created to assist AoB in finding bugs and troublesome objects.
 * It was extended to a more general item database.
 *
 * Copyright Erik Gävert <erik@gavert.net> 
 */
#pragma strict_types
#pragma no_inherit
#pragma no_clone

#include <macros.h>
#include <files.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>
#include <formulas.h>

static mapping file_data = ([ ]);
static int      save_alarm = 0;
static int      loaded = 0;

#define PATH      "/d/Genesis/ateam/aob/magic_hunter/"
#define SAVE_FILE (PATH + "item_database2")

#define M_TIME   0
#define M_SHORT  1
#define M_TYPE   2
#define M_INFO   3

#define F_OBJECT 1
#define F_WEAPON 2
#define F_ARMOUR 4
#define F_HERB   8
#define F_POTION 16
#define F_HEAP   32

#define RECHECK_TIME    (1619772627) 

void loop();
mapping object_data(object ob, string file);
mapping weapon_data(object ob, string file);
mapping armour_data(object ob, string file);
mapping herb_data(object ob, string file);
mapping potion_data(object ob, string file);
mapping heap_data(object ob, string file);

mixed *filters = ({ });

void
add_filter(string name, int bit, mixed filter, function f)
{
    filters += ({ ({ filter, bit, f }) });    
}

void
restore_data()
{
    loaded = 1; 
    file_data = restore_map(SAVE_FILE);
}

void
create()
{
    setuid();
    seteuid(getuid());
    
    add_filter("object", F_OBJECT, 1, object_data);
    add_filter("heap", F_HEAP, &operator(==)(, HEAP_OBJECT) @ &function_exists("create_object", ), heap_data);
    add_filter("weapon", F_WEAPON, &operator(==)(, WEAPON_OBJECT) @ &function_exists("create_object", ), weapon_data);
    add_filter("armour", F_ARMOUR, &operator(==)(, ARMOUR_OBJECT) @ &function_exists("create_object", ), armour_data);
    add_filter("herb",   F_HERB,   &operator(==)(, HERB_OBJECT) @ &function_exists("create_heap", ), herb_data);
    add_filter("potion", F_POTION, &operator(==)(, POTION_OBJECT) @ &function_exists("create_heap", ), potion_data);

    // Setting up an alarm so loading the object will be guaranteed, in case eval_cost ever changes.
    // the restore_map takes quite a while.
    set_alarm(0.01, 0.0, restore_data);   
}


void
save()
{
    save_map(file_data, SAVE_FILE);
}

void
log(string file, string message)
{
    log_file("item_database", sprintf("[%s] [%-50s] %s\n", ctime(time()), file, message));
}

/*
 * Function:    alarmed_save
 * Description: Sets up an alarm to save the data using an alarm. It
 *              won't set up multiple alarms, so it allows multiple objects
 *              to get batched together in a single save operation.
 *              This function is called from the investigate functions after
 *              adding objects to the database.
 */
void
alarmed_save()
{
    if (get_alarm(save_alarm))
    {
        // A save alarm already exists, no need to save.
        return;
    }
    save_alarm = set_alarm(180.0, 0.0, save);
}

int
store_item(string file, mapping data)
{
    file_data[file] = ({ time(), data });
}


mixed *
query_item(string file)
{
    if (file_data[file]) {
        return secure_var(file_data[file]);
    }

    return 0;
}

mapping
object_data(object ob, string file)
{
    string str;
    mapping data = ([ ]); 

    
    
    data["short"] = ob->short();
    data["long"] = ob->long();
    data["value"] = ob->query_prop(OBJ_I_VALUE);
    data["weight"] = ob->query_prop(OBJ_I_WEIGHT);
    data["volume"] = ob->query_prop(OBJ_I_VOLUME);

    if (str = domain(ob))
        data["domain"] = str;

    mixed magic = ob->query_prop(MAGIC_AM_MAGIC);
    if (magic) {
        data["magic"] = magic;
    }
    
    if (strlen(str = ob->query_prop(OBJ_S_WIZINFO)))
    {
        data["wizinfo"] = str;
    }
    
    return data;
}

mapping
heap_data(object ob, string file)
{
    string str;
    mapping data = ([ ]); 

    data["heap_value"] = ob->query_prop(HEAP_I_UNIT_VALUE);
    data["heap_weight"] = ob->query_prop(HEAP_I_UNIT_WEIGHT);
    data["heap_volume"] = ob->query_prop(HEAP_I_UNIT_VOLUME);
    return data;
}

mapping
weapon_data(object ob, string file)
{
    mapping data = ([ ]);
    
    data["pen"] = map(ob->query_pm(), &operator(+)(ob->query_pen(), ));
    data["hit"] = ob->query_hit();
    data["type"] = ob->query_wt();
    data["hands"] = ob->query_hands();

    return data;
}

mapping
armour_data(object ob, string file)
{
    mapping data = ([ ]);

    data["ac"] = map(ob->query_am(), &operator(+)(ob->query_ac(), ));
    data["type"] = ob->query_at();

    return data;
}

mapping
herb_data(object ob, string file)
{
    mapping data = ([ ]);

    data["herb_name"] = ob->query_herb_name();
    data["herb_value"] = ob->query_herb_value();
    data["herb_find_diff"] = ob->query_find_diff();
    data["herb_id_diff"] = ob->query_id_diff();
    return data;    
}

mapping
potion_data(object ob, string file)
{
    mapping data = ([ ]);
    data["potion_name"] = ob->query_potion_name();
    return data;
}


/*
 * Check weapon for changes and some simple bug checks.
 */
string
weapon_report(object ob, string file)
{
    int new;
    string info, tmp;
    int *mod_pen;
    
    mod_pen = map(ob->query_pm(), &operator(+)(ob->query_pen(), ));
    
    info = ob->wep_usage_desc();
    
    info += "Hit: " + ob->query_hit() + " Pen: " + ob->query_pen() + " (" +
        implode(
                map(mod_pen, &sprintf("%d", )),
                ", ") + ")\n";

    if (function_exists("did_hit", ob) != WEAPON_OBJECT)
        info += "Info: Weapon has special attack/messages\n";
    
    if (strlen(tmp = ob->query_prop(OBJ_S_WIZINFO)))
    {
        info += "WIZ: " + tmp + "\n";
    }
    
    if (reduce(&operator(+)(, ), ob->query_pm()))
        info += "Error: Sum of pen modifiers not 0\n";
    
    if (
        (ob->query_hands() == W_BOTH &&
            sizeof(filter(mod_pen, &operator(>)(, 60)))) ||
        (ob->query_hands() != W_BOTH &&
            sizeof(filter(mod_pen, &operator(>)(, 50)))))
    {
        info += "Error: Penetration value over limits.\n";
    }

    return info;
}


string
armour_report(object ob, string file)
{
    string info, tmp;
    int *mod_ac;
    
    info = ob->long();
    
    mod_ac = map(ob->query_am(), &operator(+)(ob->query_ac(), ));

    info += "Ac: " + ob->query_ac() + " (" +
        implode(
                map(mod_ac, &sprintf("%d", )),
                ", ") + ")\n";

    if (function_exists("got_hit", ob) != ARMOUR_OBJECT)
        info += "Info: Armour has special attack/messages\n";
    
    if (strlen(tmp = ob->query_prop(OBJ_S_WIZINFO)))
    {
        info += "WIZ: " + tmp + "\n";
    }

    return info;
}

/*
 * Herb Item
 */
string
herb_report(object ob, string file)
{
    
     
}

/*
 * Generic Item, this is only for search.
 */
string
item_report(object ob, string file)
{
    string info, tmp;
    info = ob->long();

    if (strlen(tmp = ob->query_prop(OBJ_S_WIZINFO)))
    {
        info += "WIZ: " + tmp + "\n";
    }

    return info;
}

mixed
search(string query)
{
    string *results = ({ });
    
    foreach (string file, mixed entry: file_data)
    {
        mixed data = entry[1];
        
        if ((stringp(data["short"]) && wildmatch(query, data["short"])) ||
            (stringp(data["herb_name"]) && wildmatch(query, data["herb_name"])) ||
            (stringp(data["potion_name"]) && wildmatch(query, data["potion_name"])))
            results += ({ file });
    }

    

    return filter(results, &SECURITY->valid_read(, this_interactive()->query_real_name(), function_name(search)));
}

int
sort_one(string key, string a, string b)
{

    if (file_data[a][1][key] > file_data[b][1][key])
        return -1;
    if (file_data[a][1][key] < file_data[b][1][key])
        return 1;
    return 0;
}


int
sort_fun(string key, string a, string b)
{

    if (file_data[a][1][key][0] > file_data[b][1][key][0])
        return -1;
    if (file_data[a][1][key][0] < file_data[b][1][key][0])
        return 1;
    return 0;
}

int
lookup_sort(mapping m, string a, string b)
{
    if (m[a] > m[b])
        return -1;
    if (m[a] < m[b])
        return 1;
    return 0;
}

mixed
list(int wt, int hands)
{
    int i;


    write("WT: " + wt + "\n");
    string *weapons = ({ });
    foreach (string file : m_indexes(file_data))
    {
        mixed data = file_data[file][1];
        if (file[0..2] == "/w/")
            continue; 

        if (wt != -1 && data["type"] != wt)
           continue; 

        if (!data["hit"])
           continue;

        if (hands != -1 && data["hands"] != hands)
            continue;

        weapons += ({ file });
    }

    if (!sizeof(weapons))
    {
        write("No matches\n");
        return;
    }

    mixed m = map(weapons, &operator([])(, "pen") @ &operator([])(, 1) @ &operator([])(file_data, ));
    mapping sort_map = mkmapping(weapons, map(m, &reduce(&operator(+)(,), )));

    string *keys = sort_array(weapons, &lookup_sort(sort_map, , ));

    int cnt = min(50, sizeof(keys));

    i = -1;
    while (++i < cnt)
    {
        string file = keys[i];
        mixed data = file_data[file][1];

        object ob;
        int clones = 0;
        if (ob = find_object(file))
            clones = sizeof(filter(object_clones(ob), &not() @ &->query_prop(OBJ_I_BROKEN))); 

        float pen = itof(reduce(&operator(+)(,), data["pen"])) / 3.0;

        write(sprintf("%-60s: %2d / %2.2f (%d clones)\n", file, data["hit"], pen, clones));
    }

}

mixed 
list2(mixed query, int exact = 0)
{
    int i;
    int at;
    string *weapons = ({ });
  
    if (intp(query))
       at = query;
    if (stringp(query))
       at = atoi(query);
  
    write("Searching for at: " + at + " " + query + "\n");
    foreach (string file : m_indexes(file_data))
    {
	if (file[0..2] == "/w/")
            continue; 

        mixed data = file_data[file][1];

        if (!data["ac"])
            continue;

        if (at == 0)
        {
            weapons += ({ file });
            continue;
        }


        if ((!exact && data["type"] & at) ||
            (exact && data["type"] == at))
        {
            weapons += ({ file });
        }
    }

    mixed m = map(weapons, &operator([])(, "ac") @ &operator([])(, 1) @ &operator([])(file_data, ));
    mapping sort_map = mkmapping(weapons, map(m, &reduce(&operator(+)(,), )));

    string *keys = sort_array(weapons, &lookup_sort(sort_map, , ));

    i = -1;
    while (++i < 100 && i < sizeof(keys))
    {
        mixed data = file_data[keys[i]][1];
        float default_weight = 0.0;
	int clones = 0;
	object ob;
	float density = itof(data["weight"]) / itof(data["volume"] + 1);

        if (strlen(keys[i]) > 2)
        {
            default_weight = itof(F_WEIGHT_DEFAULT_ARMOUR(data["ac"][0], data["type"])) / 1000.0;
        }
	if (ob = find_object(keys[i]))
	   clones = sizeof(filter(object_clones(ob), &not() @ &->query_prop(OBJ_I_BROKEN))); 

        float ac = itof(reduce(&operator(+)(,), data["ac"])) / 3.0;

        if (ac < 40.0)
            break;

        write(sprintf("%-60s: %2.2f %6.2fkg %6.2f l %6.2f kg %9.2f (%3d clones) %s\n", keys[i], ac, 
		itof(data["weight"]) / 1000.0, 
		itof(data["volume"]) / 1000.0, default_weight, density, clones, TIME2STR(time() - file_data[keys[i]][M_TIME], 1) ));
    }
    
}


void
herbs()
{
    foreach (string file, mixed fields: file_data)
    {
        mixed data = fields[1];

        if (file[0..2] == "/w/")
            continue; 

        if (!(data["filters"] & F_HERB))
            continue;

        write(sprintf("%-40s %4d %2d/%3d\n", data["herb_name"], data["herb_value"], data["herb_find_diff"], data["herb_id_diff"] ));
    }
}

/*
 * Check if this item is something we need to add to our list.
 */
void
investigate(object ob, function callback = 0)
{
    string file;
    mapping data = ([ ]);
    int fi = 0;

    if (!loaded)
        return;

    if (!objectp(ob))
        return;

    /* Shadowed items need to be skipped */
    if (shadow(ob, 0))
    {
        return;
    }
    
    file = MASTER_OB(ob) + ".c";

    if (file[0..2] == "/w/")
        return;


    if (file_data[file]) {
        int last_time = file_data[file][M_TIME];
        if (file_time(file) > last_time) {
            log(file, "Item modified");
        } else if (last_time < RECHECK_TIME) {
            log(file, "Refreshing due to recheck time.");
        } else if (IS_HERB_OBJECT(ob)) {
            log(file, "Herb refresh\n");
        } else {
            return;
        }
    } else {
        log(file, "New item");
    } 
 
    foreach (mixed f : filters)
    {
        function check = f[0];
        int bit = f[1];
        function data_fun = f[2];
        mixed ret;

        if (intp(check))
            ret = check;
        if (functionp(check))
            ret = check(ob);

        if (!ret)
            continue;

        data += data_fun(ob, file);
        fi |= bit;
    }

    data["filters"] = fi;

    if (!functionp(callback)) {
        store_item(file, data);
        alarmed_save();
    } else {
        callback(file, data);
    }
}

/*
 * We get a list of items that has to be checked slowly to not cause lag.
 */
void
investigate_list(object *items)
{
    object ob;
    int size, count;

    size = sizeof(items);

    while (size--)
    {
        ob = items[size];
        items[size] = 0;

        investigate(ob);
        
        count++;

        if (count > 1000)
        {
            items -= ({ 0 });
            set_alarm(5.0, 0.0, &investigate_list(items));
            return;
        }
    }
}


/*
 * Locate objects within players.
 */
void
loop()
{
    object *items = ({ });
    object *new;

    foreach (object player: filter(users(), &not() @ &->query_wiz_level()))
    {
        if (wildmatch("*jr", player->query_real_name()))
            continue;

        new = deep_inventory(player);
        items += new;
    }

    if (!sizeof(items))
        return;
    
    write("Found " + sizeof(items) + " items\n");
    investigate_list(items);
}

void
purge()
{
    foreach (string file, mixed data: file_data)
    {
        if (file_size(file) == -1 && !objectp(find_object(file))) {
            write("Purging file: " + file + "\n");
            m_delkey(file_data, file);
        }
    }

}

mixed
query_alarms()
{
    return get_all_alarms();    
}

string
stat_object()
{
    string str;

    str = "Magic Hunter v1.0\n";
    str += m_sizeof(file_data) + " items in the database.\n";

    return str;
}
