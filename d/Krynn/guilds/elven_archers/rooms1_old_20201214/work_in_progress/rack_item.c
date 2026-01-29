#pragma save_binary

inherit "std/object.c";

#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include <cmdparse.h>

#include "../guild.h"
#include "../rack_defs.h"

/* Prototypes */

public void     init_rack_item(object player);
public int      set_rack_cmd(object player, string cmd, string new);
public string   query_rack_cmd(object player, string cmd);
public int      filter_cmd(object player, string str, string cmd);

public int      store_item(string str);
public int      collect_item(string str);
public int      do_configure(string str);

void            get_phase();
void            process_input(string str);

/* Variables */
int     phase;

public int
query_archer_rack_item()
{
    return 1;
}

public void 
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("_object_for_cmds_");
    set_short("cmd item");
    set_long("An item offering rack commands.\n");
    
    set_no_show();
}

/* Commands */

public void
init_rack_item(object player)
{
    add_action(store_item,   query_rack_cmd(player, "store"));
    add_action(store_item,   query_rack_cmd(player, "donate"));
    add_action(collect_item, query_rack_cmd(player, "collect"));

    add_action(do_configure, "configure");
    init();
}

public int
set_rack_cmd(object player, string cmd, string new)
{
    mapping cmds;
    string  name;
    object  store;
    int     num;
    
    store = safely_load_master_file(ROOMS + "store_room.c");
    name  = get_player_name(player);
    cmds  = RACK_MANAGER->query_option("rack_cmd", name);
    
    if (!stringp(new) || !strlen(new))
        return -3;
    
    if (member_array(new, m_values(cmds)) > -1)
        return -2;
    
    if (!mappingp(cmds))
        cmds = ([]);
    
    if (num = member_array(cmd, ({"store", "donate", "collect"})) > -1 &&
        num != member_array(new, ({"store", "donate", "collect"})))
        return -1;
    
    cmds[cmd] = new;
    
    return RACK_MANAGER->set_option("rack_cmd", name, cmds);
}

public string
query_rack_cmd(object player, string cmd)
{
    mapping cmds;
    string  name;
    object  store;
    
    store = safely_load_master_file(ROOMS + "store_room.c");
    name  = get_player_name(player);
    cmds  = RACK_MANAGER->query_option("rack_cmd", name);
    
    if (!mappingp(cmds) || member_array(cmd, m_indexes(cmds)) < 0 ||
        !strlen(cmds[cmd]))
        return cmd;
    
    return cmds[cmd];
}

public int
filter_cmd(object player, string str, string cmd)
{
    mapping list;    
    object  store, *items;
    string filter, item, *arr, *add_arr;
    
    if (!parse_command(cmd, ({}), "%w %s", filter, item))
        return -4;
    
    store   = safely_load_master_file(ROOMS + "store_room.c");
    list    = store->query_filter_list(player);
    
    switch(str)
    {
        case "price":
        if (member_array(item, store->query_value_strings()) > -1)
            add_arr = ({ item });
        
        str = "price_filter";
            break;
        case "imbue":
        if (member_array(item, store->query_imbue_stones()) > -1)
            add_arr = ({ item });
        
        str = "imbue_filter";
            break;
        case "scrap":
        items   = FIND_STR_IN_OBJECT(item, player) +
                  FIND_STR_IN_OBJECT(item, store);
        add_arr = map(items, &master_ob());
        str = "scrap_filter";
            break;
        case "prime":
        items   = FIND_STR_IN_OBJECT(item, player) +
                  FIND_STR_IN_OBJECT(item, store);
        add_arr = map(items, &master_ob());
        str = "prime_filter";
            break;
    }
    
    if (member_array(str, m_indexes(list)) > -1)
        arr = list[str];
    else
        arr = ({});
    
    if (!sizeof(add_arr))
        return -3;
    
    switch(filter)
    {
        case "add":
        arr += add_arr;
            break;
        case "remove":
        if (!sizeof(arr))
            return -2;
        arr -= add_arr;
            break;
        default:
            return -1;
    }
    
    list[str] = arr;
    return store->set_filter_list(player, list);
}

object *
filter_containers(object store, string str)
{
    object *items,
           *itema,
           *saving;
    int     lasting,
            nonlast;
    string  herb;
    
    if (!sizeof(itema = filter(all_inventory(store), is_container)))
        itema = ({});
    
    itema += ({ store });
    items  = ({});
    
    lasting = parse_command(str, ({}), "'lasting' / 'saving' %s", str);
    nonlast = parse_command(str, ({}), "'non-lasting' / 'non-saving' %s", str);
    
    foreach(object item: itema)
    {
        items += FIND_STR_IN_OBJECT(str, item);
    }
    
    saving = filter(items, &operator(>)(,0) @ &->check_recoverable());
    
    if (lasting)
        return saving;
    else if (nonlast)
        return (items - saving);
    
    return items;
}

public int
store_item(string str)
{
    object *itemf = ({}),
           *items = ({}),
            store;
    int     donate, num;
    string  herb;
    store = safely_load_master_file(ROOMS + "store_room.c");
    
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (query_rack_cmd(this_player(), "donate") == query_verb())
        donate = 1;
    
    if (!sizeof(items = filter_containers(this_player(), str)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    /*
    if (sizeof(filter(items, &->query_herb_name())) &&
        parse_command(str, ({}), "%d %s", num, herb))
    {
        if (store->store_item(item, this_player(), num, donate))
            return 1;
    }*/
    
    foreach(object item: items)
    {
        if (!store->store_item(item, this_player(), 0, donate))
            continue;
        
        itemf += ({ item });
    }
    
    if (sizeof(itemf) && !sizeof(items -= itemf))
    {
        if (sizeof(filter(itemf, &operator(>)(,0) @ &->query_keep())))
        {
            notify_fail("You cannot store kept items in the armory. " +
            "You must 'unkeep' it first.\n");
            return 0;
        }
        
        notify_fail("You fail to store " + COMPOSITE_DEAD(itemf) +
        " in the armory.\n");
        return 0;
    }
    
    write("You store " + COMPOSITE_DEAD(items) + " into the armory.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + " stores " +
    COMPOSITE_DEAD(items) + " into the armory.\n", this_player());
    return 1;
}

public int
collect_item(string str)
{
    object *itemf = ({}),
           *items, *itema,
            store;
    
    store = safely_load_master_file(ROOMS + "store_room.c");
    
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (!sizeof(items = filter_containers(store, str)))
    {
        notify_fail("The armory does not contain any '" + str + "'.\n");
        return 0;
    }
    
    foreach(mixed item: items)
    {
        if (!store->collect_item(item, this_player()))
            continue;
        
        itemf += ({ item });
    }
    
    if (sizeof(itemf) && !sizeof(items -= itemf))
    {
        notify_fail("You lack the rack points to collect " +
        COMPOSITE_DEAD(itemf) + "\n");
        return 0;
    }
    
    write("You collect " + COMPOSITE_DEAD(items) + " from the armory.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) +
    " collects " + COMPOSITE_DEAD(items) + " from the armory.\n",
    this_player());
    return 1;
}

/* Configure Settings */

public int
do_configure(string str)
{
    phase = MENU;
    get_phase();
    return 1;
}

void
get_phase()
{
    object  store, *files;
    string *filter;
    mapping list;
    
    store = safely_load_master_file(ROOMS + "store_room.c");
    
    switch(phase)
    {
        case MENU:
        this_player()->catch_msg("" +
        sprintf("%65|s\n\n%65|s\n%65|s\n\n%65|s\n%65|s\n\n",
        "~~ < Configure Menu > ~~", "[Commands]",
        "List configurable commands.", "[Filter]",
        "Manage the rack filters."));
            break;
        case ST_DO_CO_CMD:
        this_player()->catch_msg("You must specify a command to replace " +
        "the old one.\n");
        case COMMAND:
        this_player()->catch_msg("" +
        sprintf("%65|s\n\n%21|s %21|s %21|s\n%21|s %21|s %21|s\n\n" +
        "%-65s\n%-65s\n", "~~ < Command List > ~~",
        "[Store Command]", "[Donate Command]", "[Collect Command]",
        "<" + query_rack_cmd(this_player(), "store") + ">",
        "<" + query_rack_cmd(this_player(), "donate") + ">",
        "<" + query_rack_cmd(this_player(), "collect") + ">",
        "To change a command simple enter <command> <new command>.",
        "Example: <store deposit> sets the store command to deposit."));
            break;
        case FILTER:
        if (!m_sizeof(list = store->query_filter_list(this_player())))
            list = ([]);
        this_player()->catch_msg("" +
        sprintf("%65|s\n\n%65|s\n%65|s\n%65|s\n\n%65|s\n%65|s\n%65|s\n\n" +
        "%65|s\n%65|s\n%65|s\n\n%65|s\n%65|s\n%65|s\n\n%65|s\n%65|s\n%65|s\n\n",
        "~~ < Filter > ~~", "[Price Filter]",
        "This filter hides all items in one or more price ranges.", 
        (pointerp(filter = list["price_filter"]) && sizeof(filter)) ?
        implode(filter, ", ") : "<empty>",
        "[Imbue Filter]", "Any imbue on this list is filtered out.",
        (pointerp(filter = list["imbue_filter"]) && sizeof(filter)) ?
        implode(filter, ", ") : "<empty>",
        "[Scrap Filter]", "This filter hides single items.",
        (files = safely_load_array_files(list["scrap_filter"]) &&
        sizeof(files)) ?
        implode(map(files, &->short()), ", ") : "<empty>",
        "[Prime Filter]", "Any items in this filter ignores other filters.",
        (files = safely_load_array_files(list["prime_filter"]) &&
        sizeof(files)) ?
        implode(map(files, &->short()), ", ") : "<empty>",
        "How to manage filters: <filter> <add/remove> <target>",
        "Examples: <price add low>, <imbue remove hobbitstone>",
        "<prime add composite bow>, <scrap add rusty sword>"));
            break;
    }
    
    this_player()->catch_msg("To leave the configure mode, simple type " +
    "<q>, <quit> or <stop>.\n> Please enter your choice:\n");
    input_to(process_input, 1);
}

void
process_input(string str)
{
    string  cmd;
    mapping list;
    
    parse_command(str, ({}), "%w %s", str, cmd);
    
    if (IN_ARRAY(str, ({ "q", "quit", "stop" }) ))
    {
        this_player()->catch_msg("You leave the configuring mode.\n");
        init_rack_item(this_player());
        return;
    }
    
    switch(lower_case(str))
    {
        /* Menu */
        case "menu":
        case "configure":
        phase = MENU;
            break;
            
        /* Commands: */
        case "command":
        case "commands":
        phase = COMMAND;
            break;
            
        /* Store/Donate/Collect Command */
        case "store":
        case "donate":
        case "collect":
        if (strlen(cmd))
        {
            if (set_rack_cmd(this_player(), str, cmd) > 0)
            {
                this_player()->catch_msg("You have changed your " + str +
                " command to " + cmd + "\n");
                set_rack_cmd(this_player(), str, cmd);
                phase = COMMAND;
                    break;
            } else
                this_player()->catch_msg("You were unable to change your " +
                str + " command to " + cmd + "\n");
                
            phase = COMMAND;
                break;
        }
        phase = ST_DO_CO_CMD;
            break;
            
        /* Filters: */
        case "filter":
        case "filters":
        phase = FILTER;
            break;
        case "price":
        case "imbue":
        case "scrap":
        case "prime":
        filter_cmd(this_player(), str, cmd);
            break;
        /* Item must be present or in rack to be removed..*/
            break;
        default:
            break;
    }
    
    get_phase();
}