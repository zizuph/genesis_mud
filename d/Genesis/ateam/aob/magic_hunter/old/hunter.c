/*
 * Tracks and reports changes to objects in the game.
 *
 * This is to assist AoB in finding bugs and troublesome objects.
 */
#pragma strict_types
#pragma no_inherit
#pragma no_clone

#include <macros.h>
#include <files.h>
#include <stdproperties.h>
#include <wa_types.h>

static mapping file_data = ([ ]);

#define PATH      "/d/Genesis/ateam/aob/magic_hunter/"
#define NEW_LOG   (PATH + "log/new")
#define SAVE_FILE (PATH + "item_database")

#define M_TIME   0
#define M_SHORT  1
#define M_TYPE   2
#define M_INFO   3

#define T_WEAPON 0
#define T_ARMOUR 1
#define T_ITEM   2

void loop();

void
create()
{
    setuid();
    seteuid(getuid());
    
    file_data = restore_map(SAVE_FILE);
    //    set_alarm(3600.0, 3600.0, &loop());
}

void
save()
{
    save_map(file_data, SAVE_FILE);
}

int
store_item(string file, string short, int type, string info)
{
    int new;

    if (!file_data[file])
        new = 1;

    
    file_data[file] = ({ file_time(file), lower_case(short), type, info });

    if (new)
    {
        write_file(NEW_LOG,
            "File: " + file + "\n" +
            "Short: " + short + "\n" + 
            info + "\n");
    }
    
}

/*
 * Check weapon for changes and some simple bug checks.
 */
void
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

    if (!file)
        dump_array(ob);
    
    store_item(file, ob->short(), T_WEAPON, info);
}


void
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

    store_item(file, ob->short(), T_ARMOUR, info);
}

/*
 * Herb Item
 */
void
herb_report(object ob, string file)
{
    
     
}

/*
 * Generic Item, this is only for search.
 */
void
item_report(object ob, string file)
{
    string info, tmp;
    info = ob->long();

    if (strlen(tmp = ob->query_prop(OBJ_S_WIZINFO)))
    {
        info += "WIZ: " + tmp + "\n";
    }

    if (!file)
        dump_array(ob);
    store_item(file, ob->short(), T_ITEM, info);
}

/*
 * Check if this item is something we need to add to our list.
 */
void
investigate(object ob)
{
    string file;

    if (!objectp(ob))
        return;
    
    file = MASTER_OB(ob) + ".c";
    if (file_data[file] && file_time(file) <= file_data[file][M_TIME])
        return;

    if (IS_WEAPON_OBJECT(ob))
    {
        /*
        if (ob->query_prop(OBJ_I_IS_MAGIC_WEAPON) ||
        ob->query_hit() > 35 || ob->query_pen() > 35)
        */
        {
            weapon_report(ob, file);
        }
    } 
    else if (IS_ARMOUR_OBJECT(ob))
    {
        /*
        if (ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR) ||
        ob->query_ac() > 40)
        */
        {
            armour_report(ob, file);
        }
    }
    else {
        item_report(ob, file);
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

    save_map(file_data, SAVE_FILE);
        
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
        // new = filter(new, &not() @ &->query_herb_name());
        // new = filter(new, &not() @ &->query_prop(HEAP_I_IS));
        
        items += new;
    }

    if (!sizeof(items))
        return;

    write("Found " + sizeof(items) + " items\n");
    investigate_list(items);
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
