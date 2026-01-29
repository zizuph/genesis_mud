#pragma no_clone

#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

object *magicweps,
       *magicarms,
       *illegalweps,
       *illegalarms;
mapping all_weapons,
        all_armours,
        all_illegal_weapons,
        all_illegal_armours,
        total_wep_map,
        total_arm_map;
int list_alarm;

create_object()
{
    setuid(); seteuid(getuid());
    all_weapons = restore_map("/d/Earthsea/private/magic_hunter/all_weapons");
    all_armours = restore_map("/d/Earthsea/private/magic_hunter/all_armours");
    all_illegal_weapons = restore_map("/d/Earthsea/private/magic_hunter/all_illegal_weapons");
    all_illegal_armours = restore_map("/d/Earthsea/private/magic_hunter/all_illegal_armours");
}

int filter_magic_weapon(object ob)
{
    return ob->query_prop(OBJ_I_IS_MAGIC_WEAPON) && !ob->has_imbue_shadow();
}

int filter_magic_armour(object ob)
{
    return ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR) && !ob->has_imbue_shadow();
}

int filter_illegal_weapon(object ob)
{
    return !ob->query_prop(OBJ_I_IS_MAGIC_WEAPON) && (ob->query_pen() >= 40 || ob->query_hit() >= 40);
}

int filter_illegal_armour(object ob)
{
    return !ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR) && ob->query_ac() >= 40;
}

public void
generate_list()
{
    object *players,
           *weapons,
           *armours;
    object *temp;
    int i, new;

    players = filter(users(), &not() @ &->query_wiz_level());
    players = filter(players, &operator(>)(160) @ &->query_average_stat());
    weapons = ({});
    armours = ({});
    for (i = 0; i < sizeof(players); i++)
    {
        if (pointerp(temp = filter(deep_inventory(players[i]), &->check_weapon())) && sizeof(temp))
            weapons += temp;
        if (pointerp(temp = filter(deep_inventory(players[i]), &->check_armour())) && sizeof(temp))
            armours += temp;
    }
    temp = filter(weapons, filter_magic_weapon);
    magicweps = temp;
    for (i = 0; i < sizeof(temp); i++)
    {
        if (!all_weapons[MASTER_OB(temp[i])])
        {
            all_weapons[MASTER_OB(temp[i])] = temp[i]->short();
            new = 1;
        }
    }
    if (new)
    {
        seteuid(getuid());
        if (find_player("ckrik"))
            find_player("ckrik")->catch_msg("Magic Hunter found new weapons.\n");
        save_map(all_weapons, "/d/Earthsea/private/magic_hunter/all_weapons");
    }
    new = 0;
    temp = filter(armours, filter_magic_armour);
    magicarms = temp;
    for (i = 0; i < sizeof(temp); i++)
    {
        if (!all_armours[MASTER_OB(temp[i])])
        {
            all_armours[MASTER_OB(temp[i])] = temp[i]->short();
            new = 1;
        }
    }
    if (new)
    {
        seteuid(getuid());
        if (find_player("ckrik"))
            find_player("ckrik")->catch_msg("Magic Hunter found new armours.\n");
        save_map(all_armours, "/d/Earthsea/private/magic_hunter/all_armours");
    }
    new = 0;
    temp = filter(weapons, filter_illegal_weapon);
    illegalweps = temp;
    for (i = 0; i < sizeof(temp); i++)
    {
        if (!all_illegal_weapons[MASTER_OB(temp[i])])
        {
            all_illegal_weapons[MASTER_OB(temp[i])] = temp[i]->short();
            new = 1;
        }
    }
    if (new)
    {
        seteuid(getuid());
        if (find_player("ckrik"))
            find_player("ckrik")->catch_msg("Magic Hunter found new illegal weapons.\n");
        save_map(all_illegal_weapons, "/d/Earthsea/private/magic_hunter/all_illegal_weapons");
    }
    new = 0;
    temp = filter(weapons, filter_illegal_armour);
    illegalarms = temp;
    for (i = 0; i < sizeof(temp); i++)
    {
        if (!all_illegal_armours[MASTER_OB(temp[i])])
        {
            all_illegal_armours[MASTER_OB(temp[i])] = temp[i]->short();
            new = 1;
        }
    }
    if (new)
    {
        seteuid(getuid());
        if (find_player("ckrik"))
            find_player("ckrik")->catch_msg("Magic Hunter found new illegal armours.\n");
        save_map(all_illegal_armours, "/d/Earthsea/private/magic_hunter/all_illegal_armours");
    }

    if (!get_alarm(list_alarm))
        list_alarm = set_alarm(3600.0, 0.0, generate_list);
}

varargs mixed
list_all_weapons(int save = 0)
{
    int i;

    object *temp;
    string *indexes;
    mapping weapons;

    temp = ({});
    weapons = ([]);
    indexes = m_indexes(all_weapons);
    for (i = 0; i < sizeof(indexes); i++)
    {
        if (file_size(indexes[i] + ".c") < 0)
            all_weapons = m_delete(all_weapons, indexes[i]);
        if (objectp(find_object(indexes[i])))
        {
            temp = object_clones(find_object(indexes[i]));
            weapons[indexes[i]] = ({all_weapons[indexes[i]],
                sizeof(temp)});
        }
    }

    if (save)
    {
        setuid(); seteuid(getuid());
        save_map(weapons, 
            "/d/Earthsea/private/magic_hunter/save_maps/all_wep_" + time());
        save_map(weapons, 
            "/d/Earthsea/private/magic_hunter/save_maps/all_wep_last");
    }
    return weapons;
}

varargs mixed
list_all_armours(int save = 0)
{
    int i;

    object *temp;
    string *indexes;
    mapping armours;

    temp = ({});
    armours = ([]);
    indexes = m_indexes(all_armours);
    for (i = 0; i < sizeof(indexes); i++)
    {
        if (file_size(indexes[i] + ".c") < 0)
            all_armours = m_delete(all_armours, indexes[i]);
        if (objectp(find_object(indexes[i])))
        {
            temp = object_clones(find_object(indexes[i]));
            armours[indexes[i]] = ({all_armours[indexes[i]],
                sizeof(temp)});
        }
    }

    if (save)
    {
        setuid(); seteuid(getuid());
        save_map(armours, 
            "/d/Earthsea/private/magic_hunter/save_maps/all_arm_" + time());
        save_map(armours, 
            "/d/Earthsea/private/magic_hunter/save_maps/all_arm_last");
    }
    return armours;
}

varargs mixed
list_carried_weapons(int save = 0)
{
    int i;

    object *temp;
    mapping weapons;
    temp = ({});
    weapons = ([]);
    for (i = 0; i < sizeof(magicweps); i++)
    {
        if (!weapons[MASTER_OB(magicweps[i])])
            weapons[MASTER_OB(magicweps[i])] = ({magicweps[i]->short(), 1});
        else
            weapons[MASTER_OB(magicweps[i])] = ({magicweps[i]->short(),
                weapons[MASTER_OB(magicweps[i])][1] + 1});
            
    }

    if (save)
    {
        setuid(); seteuid(getuid());
        save_map(weapons, 
            "/d/Earthsea/private/magic_hunter/save_maps/carried_wep_" + time());
        save_map(weapons,
            "/d/Earthsea/private/magic_hunter/save_maps/carried_wep_last");
    }

    return weapons;
}

varargs mixed
list_carried_armours(int save = 0)
{
    int i;

    object *temp;
    mapping armours;
    temp = ({});
    armours = ([]);
    for (i = 0; i < sizeof(magicarms); i++)
    {
        if (!armours[MASTER_OB(magicarms[i])])
            armours[MASTER_OB(magicarms[i])] = ({magicarms[i]->short(), 1});
        else
            armours[MASTER_OB(magicarms[i])] = ({magicarms[i]->short(),
                armours[MASTER_OB(magicarms[i])][1] + 1});
            
    }

    if (save)
    {
        setuid(); seteuid(getuid());
        save_map(armours, 
            "/d/Earthsea/private/magic_hunter/save_maps/carried_arm_" + time());
        save_map(armours,
            "/d/Earthsea/private/magic_hunter/save_maps/carried_arm_last");
    }

    return armours;
}

public int
sort_me_wep(string arg1, string arg2)
{
    int val1,
        val2;

    val1 = (total_wep_map[arg1][1] +
           total_wep_map[arg1][3] +
           total_wep_map[arg1][5]) / 3;
    val2 = (total_wep_map[arg2][1] +
           total_wep_map[arg2][3] +
           total_wep_map[arg2][5]) / 3;

    total_wep_map[arg1][6] = val1;
    total_wep_map[arg2][6] = val2;

    if (val1 < val2)
        return 1;
    if (val1 == val2)
        return 0;
    if (val1 > val2)
        return -1;
}

public int
sort_me_arm(string arg1, string arg2)
{
    int val1,
        val2;

    val1 = (total_arm_map[arg1][1] +
           total_arm_map[arg1][3] +
           total_arm_map[arg1][5]) / 3;
    val2 = (total_arm_map[arg2][1] +
           total_arm_map[arg2][3] +
           total_arm_map[arg2][5]) / 3;

    total_arm_map[arg1][6] = val1;
    total_arm_map[arg2][6] = val2;

    if (val1 < val2)
        return 1;
    if (val1 == val2)
        return 0;
    if (val1 > val2)
        return -1;
}
                   
public void
dump_statistics()
{
    mapping temp,
            cloned_weps,
            cloned_arms;

    string *indexes,
           *sorted_domains;
    string dom,
           foo,
           item;
    int i,
        total_wep_files,
        total_wep_cloned,
        total_wep_carried,
        total_arm_files,
        total_arm_cloned,
        total_arm_carried,
        sub_total;

    total_wep_map = ([]);
    total_arm_map = ([]);
    generate_list();

    temp = ([]);
    indexes = m_indexes(all_weapons);
    total_wep_files = sizeof(indexes);
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, item);
        if (!temp[dom])
            temp[dom] = ({1, 0, 0});
        else
            temp[dom][0] += 1;
    }

    indexes = m_indexes(cloned_weps = list_carried_weapons(1));
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, item);
        temp[dom][1] += cloned_weps[indexes[i]][1];
        total_wep_carried += cloned_weps[indexes[i]][1];
    }

    indexes = m_indexes(cloned_weps = list_all_weapons(1));
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, item);
        temp[dom][2] += cloned_weps[indexes[i]][1];
        total_wep_cloned += cloned_weps[indexes[i]][1];
    }
    
    foo = sprintf("%-15@s\n", ({"Domain name", "Ranking", "Weapon Files",
        "Carried Weapons", "All Clones"}));
    foo += sprintf("%-15@s\n", ({"(Totals)", "", total_wep_files + "",
        total_wep_carried + "", total_wep_cloned + ""})) + "\n";

    for (i = 0; i < m_sizeof(temp); i++)
    {
        dom = m_indexes(temp)[i];
        total_wep_map[dom] = ({
            temp[dom][0],
            ftoi(itof(temp[dom][0]) / itof(total_wep_files) * 100.0),
            temp[dom][1],
            ftoi(itof(temp[dom][1]) / itof(total_wep_carried) * 100.0),
            temp[dom][2],
            ftoi(itof(temp[dom][2]) / itof(total_wep_cloned) * 100.0),
            0});
    }

    sorted_domains = sort_array(m_indexes(total_wep_map), sort_me_wep);
    for (i = 0; i < sizeof(sorted_domains); i++)
    {
        dom = sorted_domains[i];
        foo += sprintf("%-15@s\n", ({
            dom,
            total_wep_map[dom][6] + "%",
            total_wep_map[dom][0] + " (" + total_wep_map[dom][1] + "%)",
            total_wep_map[dom][2] + " (" + total_wep_map[dom][3] + "%)",
            total_wep_map[dom][4] + " (" + total_wep_map[dom][5] + "%)",
            }));
    }

    temp = ([]);
    indexes = m_indexes(all_armours);
    total_arm_files = sizeof(indexes);
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, item);
        if (!temp[dom])
            temp[dom] = ({1, 0, 0});
        else
            temp[dom][0] += 1;
    }

    indexes = m_indexes(cloned_arms = list_carried_armours(1));
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, item);
        temp[dom][1] += cloned_arms[indexes[i]][1];
        total_arm_carried += cloned_arms[indexes[i]][1];
    }

    indexes = m_indexes(cloned_arms = list_all_armours(1));
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, item);
        temp[dom][2] += cloned_arms[indexes[i]][1];
        total_arm_cloned += cloned_arms[indexes[i]][1];
    }

    foo += "\n\n";

    foo += sprintf("%-15@s\n", ({"Domain name", "Ranking", "Armour Files",
        "Carried Armours", "All Clones"}));
    foo += sprintf("%-15@s\n", ({"(Totals)", "", total_arm_files + "",
        total_arm_carried + "", total_arm_cloned + ""})) + "\n";

    for (i = 0; i < m_sizeof(temp); i++)
    {
        dom = m_indexes(temp)[i];
        total_arm_map[dom] = ({
            temp[dom][0],
            ftoi(itof(temp[dom][0]) / itof(total_arm_files) * 100.0),
            temp[dom][1],
            ftoi(itof(temp[dom][1]) / itof(total_arm_carried) * 100.0),
            temp[dom][2],
            ftoi(itof(temp[dom][2]) / itof(total_arm_cloned) * 100.0),
            0});
    }

    sorted_domains = sort_array(m_indexes(total_arm_map), sort_me_arm);
    for (i = 0; i < sizeof(sorted_domains); i++)
    {
        dom = sorted_domains[i];
        foo += sprintf("%-15@s\n", ({
            dom,
            total_arm_map[dom][6] + "%",
            total_arm_map[dom][0] + " (" + total_arm_map[dom][1] + "%)",
            total_arm_map[dom][2] + " (" + total_arm_map[dom][3] + "%)",
            total_arm_map[dom][4] + " (" + total_arm_map[dom][5] + "%)",
            }));
    }

    write(foo + "\n");
} 

public void
dump_weapons()
{
    object obj;
    string *indexes;
    string output, dom, item;
    int i;

    indexes = m_indexes(all_weapons);

    output = sprintf("%-50s|%-3s|%-3s|%-15s\n", "Weapon", "Hit", "Pen", "Domain");
    for (i = 0; i < sizeof(indexes); i++)
    {
        obj = find_object(indexes[i]);
        if (objectp(obj))
        {
            sscanf(indexes[i], "/d/%s/%s", dom, item);
            output += sprintf("%-50s|%-3d|%-3d|%-15s\n",
                obj->short(),
                obj->query_hit(),
                obj->query_pen(),
                dom
            );
        }
    }
    write(output + "\n");
} 

public void
dump_armours()
{
    object obj;
    string *indexes;
    string output, dom, item;
    int i;

    indexes = m_indexes(all_armours);

    output = sprintf("%-50s|%-3s|%-15s\n", "Armour", "AC", "Domain");
    for (i = 0; i < sizeof(indexes); i++)
    {
        obj = find_object(indexes[i]);
        if (objectp(obj))
        {
            sscanf(indexes[i], "/d/%s/%s", dom, item);
            output += sprintf("%-50s|%-3d|%-15s\n",
                obj->short(),
                obj->query_ac(),
                dom
            );
        }
    }
    write(output + "\n");
}                
