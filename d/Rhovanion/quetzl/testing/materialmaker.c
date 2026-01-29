#pragma strict_types
#pragma no_inherit

#include "/d/Immortal/std/domain.h"

inherit STDOBJECT;

#define MATERIALS_DIR "/d/Rhovanion/quetzl/testing/"
#define DAMTYPES MATERIALS_DIR + "damtypes"
#define MATTYPES MATERIALS_DIR + "mattypes"
#define CHECK_ME if (environment() != this_player()) return 0;

static mapping tempdam;

/*
 * Function name: query_prevent_shadow
 * Description:   ensure that nobody shadows this object
 * Returns:       always 1
 */

public nomask int
query_prevent_shadow()
{
    return 1;
}

/*
 * Function name: create_object  
 * Description:   make the object (constructor)
 */

public void
create_object()
{
    set_name("definer");
    set_adj("materials");
    set_long("This is a tool for making walls.  Valid commands are: \n\n" +
             "    material - define properties for a new material\n\n" +
             "    unmaterial - remove the given material\n" +
             "    edmaterial - edit the properties for a given material\n" +
             "    newdam - define properties for a new damage type\n" +
             "    redefdam - redefine properties for an old damage type\n" +
             "    undam - remove a damage type entirely\n" +
             "    listmat - list all valid materials, and creator\n" +
             "    listdam - list all valid damage types, and creator\n" +
             "    matvals - list the resistance values for a materials\n" +
             "    damvals - list the resistance values vs. a damage type\n");
}

/*
 * Function name: init
 * Description:   add the necessary commands to the user
 */

public void
init()
{
    ::init();
    add_action("define_new_material", "material");
    add_action("define_new_material", "edmaterial");
    add_action("remove_old_material", "unmaterial");
    add_action("add_new_damtype", "newdam");
    add_action("remove_old_damtype", "redefdam");
    add_action("remove_old_damtype", "undam");
    add_action("list_valid_materials", "listmat");
    add_action("list_valid_damages", "listdam");
    add_action("list_material_vals", "matvals");
    add_action("list_damage_vals", "damvals");
}

/*
 * Function name: add_resist
 * Description:   add a resistance type to the global mapping
 * Arguments:     num - string of the number to be used
 *                type - string describing damtype to resist
 */

public void
add_resist(string num, string type)
{
    int val;

    val = atoi(num);
    if ((val < 1) || (val > 1000))
    {
        write("That is not a valid number, try again: ");
        return input_to("add_resist", 0, type);
    }
    tempdam += ([ type:val ]);
    return;
}

/*
 * Function name: do_begin_material
 * Description:   ensures all known damage types are added, and adds
 *                the material to the known list, with the adder's name
 * Arguments:     type - the name of the material
 */

public int
do_begin_material(string type)
{
    int i;
    mixed *alltypes = m_indexes(restore_map(DAMTYPES));
    tempdam = ([]);
    CHECK_ME;

    for (i = 0; i < sizeof(alltypes); i++)
    {
        write("How well does " + type + " resist damage from " + alltypes[i] +
            "? (number from 1 to 1000): ");
        input_to("add_resist", 0, alltypes[i]);
    }
    save_map(restore_map(MATTYPES)+([type:this_player()->query_real_name()]),
        MATTYPES);
    save_map(tempdam, MATERIALS_DIR + type);
}
        
/*
 * Function name: define_new_material
 * Description:   the action function, insures correct command is used
 * Arguments:     type - the name of the new material
 * Returns:       1 if successful, 0 if not
 */

public int
define_new_material(string type)
{
    int newdef; 
    mapping damtypes;
    mapping materials;
    materials = restore_map(MATTYPES);
    damtypes = restore_map(DAMTYPES);
    
    newdef = (query_verb() == "material") ? 1 : 0;

    reset_euid();

    notify_fail("That is a damage type, you can't make a material out of " +
        "it.\n");
    if (damtypes[type])
        return 0;

    notify_fail("That material is already defined, please use edmaterial.\n");
    if ((newdef) && (materials[type]))
        return 0;

    notify_fail("That material is not defined, please use material.\n");
    if ((!newdef) && (!materials[type]))
        return 0;

    do_begin_material(type);

    write ("Material type " + type + " successfully added.\n");

    return 1;
}

/*
 * Function name: enter_env
 * Description:   ensure only those authorized use this object
 * Arguments:     to - the object this one is moving into.
 *                from - the object this one is moving from
 */

public void
enter_env(object to, object from)
{
    reset_euid();

    if ((to->query_domain() != "Immortal") &&
        (!call_other("/d/Immortal/workroom", "is_trusted",
        to->query_real_name())))
        {
            remove_object();
            write("You are not allowed to use that item.\n");
        }
    else
        ::enter_env(to, from);
}

/*
 * Function name: remove_old_material
 * Description:   remove a material that is faulty or no longer in use
 * Arguments:     type - the name of the material
 * Returns:       1 if successful, else 0
 */

public int
remove_old_material(string type)
{
    mapping mattypes = restore_map(MATTYPES);

    reset_euid();

    CHECK_ME;
    notify_fail("Remove which type?");
    if (!strlen(type))
        return 0;

    notify_fail("That isn't a type.\n");
    if (!mattypes[type])
        return 0;

    write("Removing " + type + " from types list.\n");
    rm (MATERIALS_DIR + type + ".o");
    mattypes = m_delete(mattypes, type);
    save_map(mattypes, MATTYPES);

    write("Material type " + type + " successfully removed.\n");
    return 1;
}

/*
 * Function name: add_dam_to_mat
 * Description:   adds resistance to a damage form to a material
 * Arguments:     num - string of number damage
 *                types - array of ({ material type, damtype })
 */

public void
add_dam_to_mat(string num, mixed *types)
{
    int val;
    mapping damtype;

    CHECK_ME;

    val = atoi(num);
    if ((val < 1) || (val > 1000))
    {
        write("That isn't a valid value, please try again.\n");
        return input_to("add_dam_to_mat", 0, types);
    }
    damtype = restore_map(MATERIALS_DIR + types[0]);
    damtype += ([ types[1]:val ]);
    save_map(damtype, MATERIALS_DIR + types[0]);
    return;
}

/*
 * Function name: add_new_damtype
 * Description:   add a new damagetype to the acceptable list
 * Arguments:     type - the name of the damage type, this should not be the
 *                same as a material type.
 * Returns:       1 if succesful, 0 if not
 */

public int
add_new_damtype(string type)
{
    mapping damtypes = restore_map(DAMTYPES);
    mixed *mattypes = m_indexes(restore_map(MATTYPES));
    int i;

    CHECK_ME;

    notify_fail("You must specify a type.\n");

    if (!strlen(type))
        return 0;

    reset_euid();

    notify_fail("That damage type is already defined, please use " +
        "redefdam to redefine it if you want.\n");
    if (damtypes[type])
        return 0;

    for (i = 0; i < sizeof(mattypes); i++)
    {
        write("How well should " + mattypes[i] + " resist " + type +
            "? (number from 1 to 1000): ");
        input_to("add_dam_to_mat", 0, ({ mattypes[i], type }));
    }
    damtypes += ([ type:this_player()->query_real_name() ]);
    restore_map(DAMTYPES);
    write("Damage type " + type + " successfully added.\n");
    return 1;
}

/*
 * Function name: remove_old_damtype
 * Description:   delete all resistances from materials for a damagetype
 * Arguments:     type - the damage type to delete
 * Returns:       1 if successful, 0 if not
 */

public int
remove_old_damtype(string type)
{
    int i;
    mapping tempme = ([]);
    mapping damtypes = restore_map(DAMTYPES);
    mixed *mattypes = m_indexes(restore_map(MATTYPES));

    CHECK_ME;

    notify_fail("You must specify a type to remove.\n");
    if (!strlen(type))
        return 0;

    notify_fail("That isn't a defined damage type.\n");
    if (!damtypes[type])
        return 0;

    for (i = 0; i < sizeof(mattypes); i++)
    {
        write("Removing " + type + " resistance from " + mattypes[i] +
            ".\n");
        tempme = restore_map(MATERIALS_DIR + mattypes[i]);
        tempme = m_delete(tempme, type);
        save_map(tempme, MATERIALS_DIR + mattypes[i]);
    }

    if (query_verb() == "redefdam")
        return add_new_damtype(type);

    write ("Damage type " + type + " successfully removed.\n");
    return 1;
}

/*
 * Function name:  list_valid_materials
 * Description:    dump the mapping of defined materials and creators
 * Arguments:      str - should not be
 * Returns:        1 if successful, otherwise 0
 */

public int
list_valid_materials(string str)
{
    mapping mattypes = restore_map(MATTYPES);
    CHECK_ME;

    notify_fail("Listmat what?\n");
    if (strlen(str))
        return 0;

    write("The following materials are defined.  type:creator \n");
    dump_mapping(mattypes, "    ");
    write("\n");
    return 1;
}

/*
 * Function name: list_valid_damages
 * Description:   dump the mapping of defined damages and creators
 * Arguments:     str - should not be
 * Returns:       1 if successful, otherwise 0
 */

public int
list_valid_damages(string str)
{
    mapping damtypes = restore_map(DAMTYPES);
    CHECK_ME;

    notify_fail("Listdam what?\n");
    if (strlen(str))
        return 0;

    write("The following damages are defined.  type:creator \n");
    dump_mapping(damtypes, "    ");
    write("\n");
    return 1;
}

/*
 * Function name: list_material_vals
 * Description:   dump the mapping of resistance values for a given material
 * Arguments:     type - the material
 * Returns:       1 if successful, otherwise 0
 */

public int
list_material_vals(string type)
{
    mapping matvals = ([]);
    int there = member_array(type, m_indexes(restore_map(MATTYPES)));
    CHECK_ME;

    notify_fail("That doesn't seem to be a valid type.\n");
    if (there == -1)
        return 0;

    matvals = restore_map(MATERIALS_DIR + type);

    write("The material " + type + " has the following resistances: \n");
    dump_mapping(matvals, "    ");
    write("\n");

    return 1;
}

/*
 * Function name: list_damage_vals
 * Description:   dump a mapping of all material resistances for a damagetype
 * Argument:      type - the damage type
 * Returns:       1 if successful, otherwise 0
 */

public int
list_damage_vals(string type)
{
    mapping tempme;
    mapping damvals = ([]);
    int i;
    mixed *mattypes = m_indexes(restore_map(MATTYPES));
    int there = member_array(type, m_indexes(restore_map(DAMTYPES)));

    CHECK_ME;

    notify_fail("That doesn't seem to be a defined damage type.\n");
    if (there == -1)
        return 0;

    for (i = 0; i < sizeof(mattypes); i++)
    {
        tempme = restore_map(MATERIALS_DIR + mattypes[i]);
        damvals += ([ mattypes[i]:tempme[type] ]);
    }
    write ("The resistance values versus " + type + " are: \n\n");
    dump_mapping(tempme, "    ");
    write("\n");

    return 1;
}
