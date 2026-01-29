#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>
#include <wa_types.h>

inherit "/d/Krynn/std/room";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include "../rack_defs.h"

/* Prototypes */
public string query_armory_desc();

public int rack_list(string str);

void
reset_krynn_room()
{
}

void
create_krynn_room()
{
    set_short("You are standing in the armory of the elven camp");
    
    set_long("You are standing inside of a gigantic tree trunk. It appears " +
    "that it has been magically formed into a large round room. The area is " +
    "well lit, well protected, and dry.  This makes it the perfect place to " +
    "store equipment. There are racks here in which you could store " +
    "equipment that may be useful to the inhabitants of the camp. The " +
    "armory is " + query_armory_desc() + ".\n");
    
    add_item(({"opening", "hut", "camouflaged hut", "tree", "tree trunk",
    "gigantic tree trunk"}), "The hut is built around the large tree trunk, " +
    "which has a large opening into it. This opening is used as an armory.\n");
    add_item(({"room", "area", "armory"}), long());
    add_item("equipment", "Equipment can be stored in the racks infront of " +
    "you.\n");
    add_item(({"rack", "racks"}), "The racks are " + query_armory_desc() +
    ". You can <list> the contents of the racks.\n");
    
    INSIDE;
    
    add_exit(ROOMS + "hut_postoffice", "south", 0);
    reset_room();
}

/* Descriptive */

public string
query_armory_desc()
{
    string  armory_desc;
    int     items;
    object  store;
    
    store = safely_load_master_file(ROOMS + "store_room.c");
    items = sizeof(deep_inventory(store));
    
    switch(items)
    {
        case 0:
        armory_desc = "empty";
            break;
        case 1..10:
        armory_desc = "poorly stocked";
            break;
        default:
        armory_desc = "brimming with equipment";
            break;
    }
    
    return LANG_ADDART(armory_desc);
}

/* Rack Command Item */

#ifdef RACK_ITEM

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    object  item,
           *rack_item = filter(all_inventory(ob), &operator(>)(,0) @
                                                  &->query_archer_rack_item());
    
    /* Add function that checks for allowed layman member */
    if (!sizeof(rack_item) && (ob->query_guild_name_occ() == GUILD_NAME ||
        ob->query_wiz_level()))
    {
        item = clone_object(RACK_ITEM);
        item->move(ob, 1);
        item->init_rack_item(ob);
    }
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    object *rack_item = filter(all_inventory(ob), &operator(>)(,0) @
                                                  &->query_archer_rack_item());
    
    foreach(object item: rack_item) { item->remove_object(); }
}

#endif

public string
query_equipment_value(object item, object player)
{
    object store;
    
    if (!objectp(store = safely_load_master_file(ROOMS + "store_room")))
        return "";
    
    return store->query_equipment_value(item, player);
}



object *
filter_containers(object store, string str)
{
    object *items,
           *itema;
    string *imbues, last, oname;
    int     num;
    
    if (!sizeof(itema = filter(all_inventory(store), is_container)))
        itema = ({});
    
    itema += ({ store });
    items  = ({});
    imbues = RACK_MANAGER->query_option("imbue_stones", "storage_list");
    
    if (!stringp(str) || !strlen(str))
        return ({});
    
    /* Removes lasting/non-lasting descs from string */
    if (parse_command(str, ({}), "%w %s", last, oname) && member_array(last,
        ({ "lasting", "saving", "non-lasting", "non-saving" })) > -1)
        str = oname;
    
    foreach(object item: itema)
    {
        /* Lists items by cost estimate */
        if (member_array(str, store->query_value_strings()) > -1)
        {
            items += filter(FIND_STR_IN_OBJECT("items", item),
                     &operator(==)(str) @
                     &query_equipment_value(, this_player()));
            continue;
        }
        
        /* Lists item by verifying item descriptions */
        items += FIND_STR_IN_OBJECT(str, item);
    }
    
    /* Filters out any lasting / non-lasting item based on specification */
    if ((num = member_array(last, ({ "lasting", "saving",
                                     "non-lasting", "non-saving" }))) > -1)
    {
        items = filter(items, &operator(==)(,(num > 1) ? 0 : 1) @
                &->check_recoverable());
    }
    
    /* Filter by imbue stone type */
    if (member_array(last, imbues) > -1)
        items = filter(items, &operator(==)(last) @ &->query_nullstone_type());
    
    return items;
}

/*
 * Function name: figure_category
 * Description:   Figure out which category ob belongs to
 * Arguments:     ob - the object to describe
 * Returns:       The category - weapon type, armour type or "General"
 */
public string
query_category(object ob)
{
    int val;
    
    if (ob->check_weapon())
    {
        switch(ob->query_wt())
        {
            case W_SWORD: return "Sword";
            case W_AXE: return "Axe";
            case W_KNIFE: return "Knife";
            case W_CLUB: return "Club";
            case W_POLEARM: return "Polearm";
            case W_MISSILE: return "Missile";
            case W_JAVELIN: return "Javelin";
            default: return "Weapon";
        }
    }
    
    if (ob->check_armour())
    {
        val = ob->query_at();
        if (val == A_SHIELD) return "Shield";
        if ((val & A_BODY) || (val & A_BACK)) return "Body";
        if (val == A_HEAD) return "Helmet";
        if (val & A_LEGS) return "Legs";
        if (val & A_FEET) return "Boots";
        if (val & A_ARMS) return "Arms";
        if (val & A_HANDS) return "Gloves";        
        if (val & A_FINGERS) return "Ring";
        return "Armour";
    }
    
    return "General";
}

/*
 * Function name: sort_list
 * Description  : Sorts the array list.
 * Returns      : an array with items
 */
mixed *
sort_list(object *oblist)
{
    oblist = filter(oblist, objectp);
    oblist = FILTER_DEAD(oblist);
    oblist = unique_array(oblist, "short", 0);
    
    return oblist;
}

public int
query_rack_condition(object item)
{
    object store;
    
    store = safely_load_master_file(ROOMS + "store_room");
    
    return store->query_rack_condition(item);
}

public varargs int
display_rack(object *items, mixed *sorted)
{
    int     i;
    object *packs, store;
    string  result, last_cat;

    store = safely_load_master_file(ROOMS + "store_room.c");
    
    if (!sizeof(items))
        return 0;
    
    if (!sizeof(sorted))
        sorted = items;
 
    result = "The armory contains:\n" +
    "+-----------------------------------------------------+--------+-----+\n" +
    "|                 Name                                | Price  | Num |\n" +
    "+-----------------------------------------------------+--------+-----+\n";
    for(i = 0; i < sizeof(sorted); i++)
    {
        if (!pointerp(sorted[i]))
            sorted[i] = ({ sorted[i] });
        
        if (!last_cat || last_cat != query_category(sorted[i][0]))
            result += sprintf("| %-51s |        |     |\n", "") + 
                      sprintf("| %-51s |        |     |\n",
                      LANG_PWORD(query_category(sorted[i][0])) + ":");
        
        last_cat = query_category(sorted[i][0]);
        
        result += sprintf("| %-3s %-47s | %-6s | %3d |\n", 
                  sizeof(filter(sorted[i], &operator(>)(,3) @
                  &query_rack_condition())) ? "[!]" :
                  sizeof(filter(sorted[i], &operator(==)(,1) @
                  &->check_recoverable())) ? "[*]" : "[ ]",
                  extract(sorted[i][0]->short(), 0, 47), 
                  store->query_equipment_value(sorted[i][0], this_player()),
                  sizeof(sorted[i]));
        
        /* Displays the pack name below an item if it is stored in the pack */
        if (sizeof(packs = filter(sorted[i], &operator(!=)(,store) @
            &environment())))
        {
            result += sprintf("|     %-47s |        |     |\n", "'--> " + 
            environment(packs[0])->short());
            
            if (i > sizeof(sorted))
                result += sprintf("| %-51s |       |     |\n", "");
        }
        
    }
    result += "" +
    "|                                                     |        |     |\n" +
    "+-----------------------------------------------------+--------+-----+\n";

    this_player()->more(result, 0);
    return 1;
}

public int
rack_list(string str)
{
    mixed  *sorted;
    object *items, *itema, store;
    
    store = safely_load_master_file(ROOMS + "store_room.c");
    
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    items = deep_inventory(store);
    
    switch(str)
    {
        case "all":
            // No filtering to do here
            break;
        case "general":
        items = filter(items, not @ is_weapon);
        items = filter(items, not @ is_armour);
            break;
            
        // Armour listings
        case "armour":
        case "armours":
        items = filter(items, is_armour);
            break;
        case "body":
        items = filter(items, &operator(&)(A_BODY) @ &->query_at()) + 
                filter(items, &operator(&)(A_BACK) @ &->query_at());
            break;
        case "shield":
        case "shields":
        items = filter(items, &operator(==)(A_SHIELD) @ &->query_at());
            break;
        case "glove":
        case "gloves":
        items = filter(items, &operator(&)(A_HANDS) @ &->query_at());
            break;
        case "helm":
        case "helms":
        case "helmet":
        case "helmets":
        items = filter(items, &operator(==)(A_HEAD) @ &->query_at());
            break;
        case "ring":
        case "rings":
        items = filter(items, &operator(&)(A_FINGERS) @ &->query_at());
            break;
        case "boot":
        case "boots":
        items = filter(items, &operator(&)(A_FEET) @ &->query_at());
            break;
        case "leg":
        case "legs":
        items = filter(items, &operator(&)(A_LEGS) @ &->query_at());
            break;
        case "arm":
        case "arms":
        items = filter(items, &operator(&)(A_ARMS) @ &->query_at());
            break;
        
        // Weapon listings
        case "weapon":
        case "weapons":
        items = filter(items, is_weapon);
            break;
        case "sword":
        case "swords":
        items = filter(items, is_weapon);
        items = filter(items, &operator(==)(W_SWORD) @ &->query_wt());
            break;
        case "axe":
        case "axes":
        items = filter(items, &operator(==)(W_AXE) @ &->query_wt());
            break;
        case "knife":
        case "knives":
        items = filter(items, &operator(==)(W_KNIFE) @ &->query_wt());
            break;       
        case "club":
        case "clubs":
        items = filter(items, &operator(==)(W_CLUB) @ &->query_wt());
            break;
        case "polearm":
        case "polearms":
        items = filter(items, &operator(==)(W_POLEARM) @ &->query_wt());
            break;       
        case "missile":
        case "missiles":
        items = filter(items, &operator(==)(W_MISSILE) @ &->query_wt());
            break;
        case "javelin":
        case "javelins":
        items = filter(items, &operator(==)(W_JAVELIN) @ &->query_wt());
            break;
        case "imbue":
        case "imbues":
        items = filter(items, &stringp() @ &->query_nullstone_type());
            break;
        default:
        if (sizeof(items = filter_containers(store, str)))
            return display_rack(sort_list(items));
        
        notify_fail("Your specified listing returned no results.\n");
            return 0;
    }
    
    /* Filters the items based on stored player data */
    if (str != "all")
        items = store->query_equipment_filter(this_player(), items);
    
    if (!sizeof(items) || !sizeof(sorted = sort_list(items)))
    {
        if(str == "all")
            write("The armory is completely empty.\n");
        else
            write("The armory does not contain any '" + str + "'.\n");
        
        return 1;
    }
    
    return display_rack(items, sorted);
}

void
init()
{
    ::init();
    
    add_action(rack_list,         "list");
}

/* Parsing items in the storage */

/*
 * Function name: long
 * Description  : Describe the object or one pseudo item in it. This
 *                resolves possible VBFC.
 *                *** NOTE! This lfun does not do a write() !! ***
 * Arguments    : string str - the pseudo-item to describe. This is an
 *                             item added with add_item. If this is 0, it
 *                             will return the description of the whole
 *                             object.
 *                object for_obj - the object trying to get the long.
 * Returns      : string - the description of the object or pseudo-item.
 */
varargs public mixed
long(string str, object for_obj)
{
    object store, *items = ({});
    
    store = safely_load_master_file(ROOMS + "store_room");
    
    if (objectp(store) && sizeof(items = filter_containers(store, str)))
        return items[0]->long();
    
    return ::long(str, for_obj);
}