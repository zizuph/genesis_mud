/*
 * Spell Component Belt
 *
 * A wearable belt that allows anyone to collect spell components and
 * place them inside. The belt comes with the added benefit of providing 
 * a way to view the contents is a readable fashion and filter the 
 * contents.
 *
 * Created by Petros, September 2008
 */
 
 /*
  *Updated by Leia, December 2015
  *
  *Changed to allow coins in the belt to accommodate spells that require
  *coins to cast.
  */

#pragma strict_types

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

public int      list_cmd(string arg);

// Defines
#define AOD_LEFTOVER_HEAD "/d/Emerald/common/guild/aod/obj/head"

nomask void
create_wearable_pack()
{
    set_name("belt");
    add_name(({ "_raspatoon_leftovers_belt", "belt", "pouch" }));
    set_pname("belts");
    set_short("sturdy belt of pouches");
    set_adj( ({ "sturdy", "rough", "hide" }));
    set_long("A number of cloth pouches hang along the length of this "
           + "belt. The belt itself is made of rough hide that is "
           + "showing obvious signs of wear and tear. The cracks in "
           + "the material don't appear to affect the sturdiness of "
           + "its carrying ability. On the inside of the belt, you "
           + "note some markings.\n");

    add_item ( ({ "cloth pouch", "cloth pouches", "cloth", "blood" }),
               "The cloth pouches hang from the belt, each seemingly "
             + "capable of storing something different. There appears "
             + "to be residues of blood seeping through parts of the "
             + "cloth.\n" );
    
    add_item ( ({ "hide", "rough hide", "cracks", "length" }),
               "The belt is made from a very rough hide material. Cracks "
             + "span the surface of the belt. It isn't clear whether this "
             + "is from heavy use, or if that is the intention of the "
             + "maker.\n" );
    
    add_item ( ({ "inside", "marking", "markings" }),
               "You look carefully on the inside lining of the belt, and "
             + "notice that the person who made this belt incribed "
             + "in black ink: Raspatoon, for use with leftovers, "
             + "gem stones, and gem shards.\n" );

    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_CLOSED,     1);

    add_prop(CONT_I_WEIGHT,     50);        /* .5 kg        */
    add_prop(CONT_I_VOLUME,     50);        /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 50000);      /* 50.0 l        */
    add_prop(CONT_I_MAX_WEIGHT, 50000);      /* 50.0 kg       */
    add_prop(CONT_I_REDUCE_VOLUME, 50);
    add_prop(CONT_I_REDUCE_WEIGHT, 50);
    add_prop(OBJ_I_VALUE,       50+random(20));

    set_slots(A_HIPS);
    set_looseness(10);
    set_layers(2);
    set_keep(1); 

    seteuid(getuid());    
}

public int
valid_item_for_container(object obj)
{
    if (!IS_LEFTOVER_OBJECT(obj)
        && !obj->query_gem()
        && !obj->query_gem_shard()
        && !obj->query_scop_spell_component()
        && !obj->query_is_elementalist_component()
        && !(obj->query_short() == "copper coin" || obj->query_short() == "silver coin" 
           || obj->query_short() == "gold coin" || obj->query_short() == "platinum coin"))
    {
        write("The " + obj->short() + " doesn't seem to fit into the "
            + "pouches.\n");
        return 0;
    }
    
    if (MASTER_OB(obj) == AOD_LEFTOVER_HEAD && (!obj->query_race() || !obj->query_organ()))
    {
        string value = obj->query_prop(HEAP_S_UNIQUE_ID);
        obj->leftover_init("head", obj->query_skull_race());
        obj->add_prop(HEAP_S_UNIQUE_ID, value);
    }
    
    return 1;
}

public int
prevent_enter(object obj)
{
    if (!valid_item_for_container(obj))
    {
        return 1;
    }
   
    return ::prevent_enter(obj);
}

void
init()
{
    ::init();
    add_action(list_cmd, "beltlist");    
}

public void
describe_contents(object for_obj, object *obarr)
{
    string name = query_name();
    for_obj->catch_tell("You can use <beltlist> to see the contents of "
                      + "the " + name + " in a list.\nYou can also use "
                      + "<beltlist> to filter "
                      + "the " + name + ". eg. <beltlist intestines>\n\n");
    ::describe_contents(for_obj, obarr);
}

public object *
resolve_arguments(string arg)
{
    mixed * matches;
    object  rack;
        
    // See if the user typed something like "list weapon rack"
    if (parse_command(arg, all_inventory(environment(this_player())),
                      "[the] %i", matches))
    {
        if (matches[0] == 1 && matches[1] == this_object())
        {
            // Simply get the first object in the array
            rack = matches[1];
            return all_inventory(rack);
        }
        else if (matches[0] < 0 
                 && sizeof(matches) > (matches[0] * -1)
                 && matches[(matches[0] * -1)] == this_object())
        {
            // player used something like "first, second, third"
            rack = matches[(matches[0] * -1)];
            return all_inventory(rack);
        }
    }

    // Now see if the user is trying to list something inside the pack
    if (parse_command(arg, all_inventory(this_object()), 
                      "[the] %i", matches))
    {
        if (matches[0] == 0)
        {
            // parse matched multiple objects
            return matches[1..];
        }
        else if (matches[0] == 1)
        {
            // Simply get the first object in the array
            return ({ matches[1] });
        }
        else if (matches[0] < 0 
                 && sizeof(matches) > (matches[0] * -1))
        {
            // player used something like "first, second, third"
            return ({ matches[(matches[0] * -1)] });
        }
    }
    
    return 0;
}

/*
 * Function:    query_object_subtype
 * Description: An object's subtype is what how the specific object
 *              gets sub-divided. For example, for leftovers, we divide
 *              by race.
 */
public string
query_object_subtype(object obj)
{
    if (!valid_item_for_container(obj))
    {
        return "";
    }
    
    if (IS_LEFTOVER_OBJECT(obj))
    {
        return obj->query_race();
    }
    else if (obj->query_gem_shard() || obj->id("shard"))
    {
        return obj->query_gem_name();
    }
    else if (obj->query_gem())
    {
        return obj->query_gem_colour();
    }
    else if (obj->query_scop_spell_component())
    {
        return obj->query_component_type();
    }
    else if (obj->query_is_elementalist_component())
    {
        if (obj->can_id_component(this_player()))
        {
            return obj->query_component_type();
        }
        else
        {
            return implode(obj->query_adjs(), " ");
        } 
    }
    else if (obj->id("coin") || obj->id("coins"))
    {
        return obj->query_coin_type();
    }
    
    return "";
}

/*
 * Function:    query_object_type
 * Description: This returns the object's type. This is the first
 *              level of categorization. When you list out the contents
 *              it will aggregate based on these object types.
 */
public string
query_object_type(object obj)
{
    if (!valid_item_for_container(obj))
    {
        return "";
    }
    
    if (IS_LEFTOVER_OBJECT(obj))
    {
        return obj->query_organ();
    }
    else if (obj->query_gem_shard() || obj->id("shard"))
    {
        return obj->query_gem_colour() + " shard";
    }
    else if (obj->query_gem())
    {
        return obj->query_gem_name();
    }
    else if (obj->query_scop_spell_component() || obj->query_is_elementalist_component())
    {
        return "component";
    }
    else if (obj->id("coin") || obj->id("coins"))
    {
        return "coin";
    }
    
    return "";
}

/*
 * Function:    query_object_plural
 * Description: This constructs the plural name of the object type. It's
 *              mostly necessary because shards don't have the adjective
 *              in the beginning, but uses the construct "of <stone>" after
 *              to designate. To make it plural, we'll need to plural the
 *              main noun.
 */
public string
query_object_plural(string objectType, int nCount = 0)
{
    if (nCount == 1)
    {
        return objectType;
    }
    
    string shardType = "";
    string pluralType = LANG_PWORD(objectType);
    if (parse_command(objectType, environment(), " 'shard' 'of' %s ", shardType))
    {
        pluralType = "shards of " + shardType;
    }

    return pluralType;
}

/*
 * Function:    construct_object_name
 * Description: This construction gets displayed in the Object column of
 *              the listing. We do something special here for shards because
 *              of how they display their name.
 */
public string
construct_object_name(string type, string subtype)
{
    if (wildmatch("* shard*", type))
    {
        return type + " of " + subtype;
    }
    
    return subtype + " " + type;
}

public void
print_list(object for_obj, object *obarr)
{
    mapping     object_data;
    mapping     subtype_data;
    string *    subtype_order;
    string *    type_order;
    int         nAmount;
    string      objectSubType, objectType, contents;
    
    object_data = ([ ]);
    subtype_order = ({ });
    type_order = ({ });
    contents = "";
    foreach (object obj : obarr)
    {
        // Leftovers are heaps. We keep track of the leftover type,
        // leftover race, and leftover quantities
        if (!valid_item_for_container(obj))
        {
            // If it's not a valid object, we continue.
            continue;
        }
        
        // Object Quantity
        nAmount = obj->num_heap();
        // Object Subtype
        objectSubType = query_object_subtype(obj);
        if (!IN_ARRAY(objectSubType, subtype_order))
        {
            subtype_order += ({ objectSubType });
        }
        // Object Type
        objectType = query_object_type(obj);
        if (!IN_ARRAY(objectType, type_order))
        {
            type_order += ({ objectType });
        }
        
        // Add the data point
        if (!IN_ARRAY(objectType, m_indices(object_data)))
        {
            object_data[objectType] = ([ ]);
        }
        
        subtype_data = object_data[objectType];
        if (!IN_ARRAY(objectSubType, m_indices(subtype_data)))
        {
            subtype_data[objectSubType] = 0;
        }
        
        subtype_data[objectSubType] += nAmount;
    }
    
    // We've added up all the leftovers by here. We will print out
    // to the player.
    if (sizeof(m_indices(object_data)) == 1)
    {
        // We only have a single type. In this case, we will
        // print out the subtypes.
        objectType = (m_indices(object_data))[0];
        mapping subtype_data = object_data[objectType];
        foreach (string subtype : subtype_order)
        {            
            contents += sprintf("| %-50s | %5d |\n", 
                                construct_object_name(query_object_plural(objectType, subtype_data[subtype]), subtype), 
                                subtype_data[subtype]); 
        }

        contents = "\nYou make a quick assessment of the pouch containing "
                 + query_object_plural(objectType) + " and find: \n"
                 + sprintf("%-53s-%8s\n"
                   ,"-----------------------------------------------------"
                   ,"--------")
                 + sprintf("| %-50s | %5s |\n", "Object", "Qty") 
                 + sprintf("%-53s-%6s\n"
                   ,"-----------------------------------------------------"
                   ,"--------") + contents
                 + sprintf("%-53s-%8s\n"
                   ,"-----------------------------------------------------"
                   ,"--------");        
    }
    else if (sizeof(m_indices(object_data)) > 1)
    {
        foreach (string type : type_order)
        {
            if (!strlen(type))
            {
                continue;
            }
            mapping subtype_data = object_data[type];
            int nCount = 0;
            foreach (string race : m_indices(subtype_data))
            {
                nCount += subtype_data[race];
            }
            contents += sprintf("| %-50s | %5d |\n", query_object_plural(type, nCount), 
                                nCount);
        }
        contents = "\nYou peruse the various pouches of the " + short()
                 + " and estimate the collection to comprise of: \n"
                 + sprintf("%-53s-%8s\n"
                   ,"-----------------------------------------------------"
                   ,"--------")
                 + sprintf("| %-50s | %5s |\n", "Pouch Content", "Qty") 
                 + sprintf("%-53s-%6s\n"
                   ,"-----------------------------------------------------"
                   ,"--------") + contents
                 + sprintf("%-53s-%8s\n"
                   ,"-----------------------------------------------------"
                   ,"--------");
        contents += "\nYou can examine a particular pouch using "
                  + "\"beltlist <part>\"\n";
    }
    else
    {
        contents = "You peruse the various pouches of the " + short()
                  + ", but you do not find what you are looking for.\n";
    }
        
    for_obj->catch_tell(contents + "\n");
}

public int
list_cmd(string arg)
{
    object * results;
    
    if (query_prop(CONT_I_CLOSED))
    {
        notify_fail("It is rather difficult to peruse the contents of "
                  + "the " + short() + " when it is closed.\n");
        return 0;
    }
    
    if (!arg)
    {
        print_list(this_player(), all_inventory(this_object()));
        return 1;
    }
    
    results = resolve_arguments(arg);
    if (pointerp(results))
    {
        print_list(this_player(), results);
        return 1;
    }
    
    notify_fail("The belt of pouches doesn't contain any " 
              + LANG_PWORD(LANG_SWORD(arg)) + ".\n");
    return 0;
}

string
query_recover()
{
     return MASTER + ":" + query_keep_recover() + 
     query_container_recover();
}

void
init_recover(string arg)
{
     init_keep_recover(arg);
     init_container_recover(arg);
}
