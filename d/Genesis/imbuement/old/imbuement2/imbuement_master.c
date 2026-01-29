/*
 *
 */
#pragma strict_types
#include "imbuement.h"

#include <macros.h>
#include <files.h>

/* Definitions */
#define IMBUEMENT_DIR   "/d/Genesis/imbuement/shadows"
#define IMBUEMENT_LIST      ({ "acid_damage", "resist_cold", "skill_knife",\
    "stat_dis" })

/* Global Variables */
string              imbuement = "extra_hit";
mapping             imbuements = ([]);
int                 max_id = 0;

/* Prototypes */
public void             create();
public int              get_id();
public varargs string   imbue(object obj, string imb1, int lev1, string imb2,
                            int lev2, string imb3, int lev3);
public string           add_imbuement(object ob, string mod, int lvl, int num,
                            int id);
public void             destructed(int id, string caller);
public void             set_recover(int id, string recover);
public string           get_recover(int id);
public void             reimbue(object obj, int id);
public string           list(int mode);


/*
 * Function name:        create
 * Description  :        set up
 */
public void
create()
{
    setuid();
    seteuid(getuid());
} /* create */


/*
 * Function name:        get_id
 * Description  :        get an ID for an imbuement record
 */
public int
get_id()
{
    int id;
    while (imbuements[max_id])
        max_id++;
    return max_id;
}


/*
 * Function name:        imbue
 * Description  :        imbue an object
 */
public varargs string
imbue(object obj,
    string imb1, int lev1, string imb2, int lev2, string imb3, int lev3)
{
    int id;
    int count;
    if (!obj)
        return 0;
    if (obj->query_imbue_info())
        return 0;
    id = get_id();
    if (imb1 == "r")
        imb1 = one_of_list(IMBUEMENT_LIST);
    if (imb1)
        add_imbuement(obj, imb1, lev1, 1, id);
    if (imb2 == "r")
        imb2 = one_of_list(IMBUEMENT_LIST);
    if (imb2)
        add_imbuement(obj, imb2, lev2, 2, id);
    if (imb3 == "r")
        imb3 = one_of_list(IMBUEMENT_LIST);
    if (imb3)
        add_imbuement(obj, imb3, lev3, 3, id);
    imbuements[id] = ({ obj, imb1, lev1, imb2, lev2, imb3, lev3, 1, 0 });
    for (int i = 1; i <= 3; i++)
    {
        if (obj->get_shadow(i))
            count++;
    }
    obj->add_prop(IMBUE_SHORT, POWER_SHORT[count]);
}


/*
 * Function name:        add_imbuement
 * Description  :        add a specific imbuement to a given object.
 * Arguments    :        object ob - the object receiving the imbuements
 *                       string mod - the name of the imbuement
 *                       int lvl - The power rating of the imbuement (1-3)
 *                       int num - The order number of the imbuement (1-3)
 * Returns      :        a string containing the info this specific imbuement
 *                       should show for a magic id spell.
 */
public string
add_imbuement(object ob, string mod, int lvl, int num, int id)
{
    object  shadow;

    shadow = clone_object(SHADOW_DIR + mod + "_shadow");
    shadow->set_id(id);
    shadow->set_num(num);
    shadow->shadow_me(ob);
    ob->init_imbue_shadow(lvl);

    return shadow->query_imbue_info() + "\n";
} /* add_imbuement */

    
public void
set(string new)
{
    imbuement = new;
    TELL_G("Set to " + imbuement);
}


/*
 * Function name:        destructed
 * Description  :        called by a shadow when destructed
 * Arguments    :        int id - ID of object
 *                       string caller - calling function
 */
public void
destructed(int id, string caller)
{
    if (!imbuements[id])
        return;
    if (caller == "quit")
    {
        imbuements[id][7] = 2;
    }
    else
    {
        imbuements[id][7] = -1;
    }
} /* destructed */


/*
 * Function name:        set_recover
 * Description  :        called by a shadow when destructed
 * Arguments    :        object obj - object to reimbue
 *                       int id - ID of object
 */
public void
set_recover(int id, string recover)
{
    if (!imbuements[id])
        return;
    imbuements[id][8] = recover;
} /* set_recover */


/*
 * Function name:        get_recover
 * Description  :        Get recovery info for object
 * Arguments    :        int id - ID of object
 * Returns      :        string - recovery string
 */
public string
get_recover(int id)
{
    if (!imbuements[id])
        return 0;
    return imbuements[id][8];
} /* get_recover */


/*
 * Function name:        reimbue
 * Description  :        Recover imbuements for object
 * Arguments    :        int id - ID of object
 * Returns      :        string - recovery string
 */
public void
reimbue(object obj, int id)
{
    mixed *rec = imbuements[id];
    if (!rec)
        return;
    imbue(obj, rec[1], rec[2], rec[3], rec[4], rec[5], rec[6]);
} /* reimbue */


/*
 * Function name:        list
 * Description  :        List imbued objects
 * Arguments    :        int mode 
 * Returns      :        string - output
 */
public string
list(int mode)
{
    string out = "\n";
    string env;
    object envo;
    foreach (int id, mixed *rec: imbuements)
    {
        envo = environment(rec[0]);
        if (IS_PLAYER_OBJECT(envo))
            env = capitalize(envo->query_real_name());
        else
            env = file_name(envo);
        out += sprintf("%-5d %-20s %d %s\n", id, rec[1], rec[2], env);
    }
    return out;
} /* list */