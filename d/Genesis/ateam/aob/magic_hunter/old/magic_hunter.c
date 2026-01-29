#pragma no_clone

#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

#define PATH "/d/Khalakhor/khail/open/magic_hunter/"

object *magicweps;
mapping all_weapons,
        total_map;
int list_alarm;

create_object()
{
    setuid(); seteuid(getuid());
    all_weapons = restore_map(PATH + "all_weapons");
}

public void
generate_list()
{
    object *players,
           *weapons;
    object *temp;
    int i,
        new;

    players = filter(users(), &not() @ &->query_wiz_level());
    players = filter(players, &operator(>)(200) @ &->query_average_stat());
    weapons = ({});
    for (i = 0; i < sizeof(players); i++)
    {
        if (pointerp(temp = filter(deep_inventory(players[i]), &->check_weapon())) && sizeof(temp))
            weapons += temp;
    }
    temp = filter(weapons, &->query_prop(OBJ_I_IS_MAGIC_WEAPON));
    magicweps = temp;
    for (i = 0; i < sizeof(temp); i++)
    {
        if (!all_weapons[MASTER_OB(temp[i])])
        {
            all_weapons[MASTER_OB(temp[i])] = temp[i]->short();
            log_file("new_magic_weapons", MASTER_OB(temp[i]) + " on " + ctime(time()) + ".\n");
            new = 1;
        }
    }
    if (new)
    {
        seteuid(getuid());
        if (find_player("khail"))
            find_player("khail")->catch_msg("Magic Hunter found new weapons.\n");
        save_map(all_weapons, "/d/Khalakhor/khail/open/magic_hunter/all_weapons");
    }

    if (!get_alarm(list_alarm))
        list_alarm = set_alarm(900.0, 0.0, generate_list);
}

/*
 * Function name: list_all_weapons
 * Description  : Generates a mapping of all the known magic weapons
 *                of which clones currently exist.
 * Arguments    : save - Optional, if true, output is saved to a .o
 *                       file.
 * Returns      : Mapping described above.
 */
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
            "/d/Khalakhor/khail/open/magic_hunter/save_maps/all_" + time());
        save_map(weapons, 
            "/d/Khalakhor/khail/open/magic_hunter/save_maps/all_last");
    }
    return weapons;
}

/*
 * Function name: list_carried_weapons
 * Description  : Same as list_all_weapons, but only reports back
 *                weapons carried by players.
 * Arguments    : Same as list_all_weapons
 * Returns      : As above.
 */
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
            "/d/Khalakhor/khail/open/magic_hunter/save_maps/carried_" + time());
        save_map(weapons,
            "/d/Khalakhor/khail/open/magic_hunter/save_maps/carried_last");
    }

    return weapons;
}


public int
sort_me(string arg1, string arg2)
{
    int val1,
        val2;

    val1 = (total_map[arg1][1] +
           total_map[arg1][3] +
           total_map[arg1][5]) / 3;
    val2 = (total_map[arg2][1] +
           total_map[arg2][3] +
           total_map[arg2][5]) / 3;

    total_map[arg1][6] = val1;
    total_map[arg2][6] = val2;

    if (val1 < val2)
        return 1;
    if (val1 == val2)
        return 0;
    if (val1 > val2)
        return -1;
}

/*
 * Function name: dump_statistics
 * Description  : Outputs a general list of information on all the
 *                known magic weapons, including how many are from
 *                each domain, how many are carried, and how many
 *                total clones exist. It also 'ranks' the domain on
 *                the highest average percentage incidences for each
 *                of these three columns.
 * Arguments    : n/a
 * Returns      : n/a
 */                   
public void
dump_statistics()
{
    mapping temp,
            cloned_weps;

    string *indexes,
           *sorted_domains;
    string dom,
           foo;
    int i,
        total_files,
        total_cloned,
        total_carried,
        sub_total;

    total_map = ([]);
    generate_list();

    temp = ([]);
    indexes = m_indexes(all_weapons);
    total_files = sizeof(indexes);
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, foo);
        if (!temp[dom])
            temp[dom] = ({1, 0, 0});
        else
            temp[dom][0] += 1;
    }

    indexes = m_indexes(cloned_weps = list_carried_weapons(1));
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, foo);
        temp[dom][1] += cloned_weps[indexes[i]][1];
        total_carried += cloned_weps[indexes[i]][1];
    }

    indexes = m_indexes(cloned_weps = list_all_weapons(1));
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, foo);
        temp[dom][2] += cloned_weps[indexes[i]][1];
        total_cloned += cloned_weps[indexes[i]][1];
    }
    
    foo = sprintf("%-15@s\n", ({"Domain name", "Ranking", "Weapon Files",
        "Carried Weapons", "All Clones"}));
    foo += sprintf("%-15@s\n", ({"(Totals)", "", total_files + "",
        total_carried + "", total_cloned + ""})) + "\n";

    for (i = 0; i < m_sizeof(temp); i++)
    {
        dom = m_indexes(temp)[i];
        total_map[dom] = ({
            temp[dom][0],
            ftoi(itof(temp[dom][0]) / itof(total_files) * 100.0),
            temp[dom][1],
            ftoi(itof(temp[dom][1]) / itof(total_carried) * 100.0),
            temp[dom][2],
            ftoi(itof(temp[dom][2]) / itof(total_cloned) * 100.0),
            0});
    }

    sorted_domains = sort_array(m_indexes(total_map), sort_me);
    for (i = 0; i < sizeof(sorted_domains); i++)
    {
        dom = sorted_domains[i];
        foo += sprintf("%-15@s\n", ({
            dom,
            total_map[dom][6] + "%",
            total_map[dom][0] + " (" + total_map[dom][1] + "%)",
            total_map[dom][2] + " (" + total_map[dom][3] + "%)",
            total_map[dom][4] + " (" + total_map[dom][5] + "%)",
            }));
    }
    write(foo + "\n");
}

public void
dump_domain_statistics(string domain)
{
    mapping temp,
            cloned_weps;

    string *indexes,
           *sorted_domains,
           *temparr;
    object wep,
           *weparr;

    string dom,
           foo;
    int i,
        j,
        total_files,
        total_cloned,
        total_carried,
        sub_total;

    temparr = ({});
    weparr = ({});
    total_map = ([]);
    generate_list();
    temp = ([]);
    domain = capitalize(domain);

  /* First we get an array containing the filepaths of all the */
  /* known weapons. */
    indexes = m_indexes(all_weapons);

  /* Next, we sort out only the ones for the specified domain. */
    for (i = 0; i < sizeof(indexes); i++)
    {
        sscanf(indexes[i], "/d/%s/%s", dom, foo);
        if (dom == capitalize(domain))
            temparr += ({indexes[i]});         
    }

    indexes = temparr;

    total_files = sizeof(indexes);

  /* Ok, now we've got 'indexes' as an array identifying all */
  /* known magic weapons in the specified domain. The next */
  /* thing to do is find all the clones of each weapon. */

    for (i = 0; i < sizeof(indexes); i++)
    {
        if (!temp[indexes[i]])
            temp[indexes[i]] = allocate(2);
        if (!(wep = find_object(indexes[i])))
            temp[indexes[i]][0] = ({});
        else
            temp[indexes[i]][0] = object_clones(wep);
    }

    write("Known weapons from the domain " + domain + ":\n");
    dump_array(indexes);

  /* Now, we have the mapping 'temp', which has the filepaths */
  /* of known weapons as indexes, with an array for values. */
  /* The first element of this array is an array containing */
  /* all the weapon clones. The next thing to do is generate */
  /* a list of the environments for each clone. */

    for (i = 0; i < sizeof(indexes); i++)
    {
        for (j = 0; j < sizeof(temp[indexes[i]][0]); j++)
        {
            if (!temp[indexes[i]][1])
                temp[indexes[i]][1] = ({});

            if (!(wep = environment(temp[indexes[i]][0][j])))
                temp[indexes[i]][1] += ({"Void"});        
            else if (interactive(wep))
                temp[indexes[i]][1] += ({wep->query_name()});
            else
                temp[indexes[i]][1] += ({file_name(wep)});
        }
    }
    
  /* Now, we've got a mapping resembling this:                         */
  /* (["/d/Domain/weapon1" : ({ ({"wepclone1","wepclone2"}),           */
  /*                            ({"wepclone1env", "wepclone2env"}) }), */
  /*   "/d/Domain/weapon2" : etc.])                                    */
   
    write("Clones and locations of known magic weapons in " +
        domain + ".\n");
    for (i = 0; i < m_sizeof(temp); i++)
    {
        dom = m_indexes(temp)[i];
        for (j = 0; j < sizeof(temp[dom][0]); j++)
        {
            write(file_name(temp[dom][0][j]) + " in " +
                temp[dom][1][j] + "\n");
        }
    }
}               
