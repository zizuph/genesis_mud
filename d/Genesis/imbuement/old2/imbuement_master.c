/*
 *
 */
#pragma strict_types
#include "imbuement.h"

#include <macros.h>
#include <files.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Global Variables */
mapping             imbuements = ([]);
int                 max_id = 1;
int                 alarm_save;
int                 updated;

/* Prototypes */
public void             create();
public void             remove_object();
public int              get_imbuements();
public int              get_id();
public int              set_updated();
public string           list(int mode);
public void             load();
public void             save(int mode);
public int *            checkmissing(int armageddon);


/*
 * Function name:        create
 * Description  :        set up
 */
public void
create()
{
    setuid();
    seteuid(getuid()); // needed for restore_map?

    load();

    //if ((time() - SECURITY->query_start_time()) <= 60)
    if ((calling_program(0) == "secure/master.c") && (!calling_program(-1)))
        checkmissing(1);

    alarm_save = set_alarm(600.0, 600.0, save);

    IMBUE_GENERATOR->create();
} /* create */


/*
 * Function name:        remove_object
 * Description  :        we are being destructed - save data
 */
public void
remove_object()
{
    save(0);
} /* remove_object */


/*
 * Function name:        get_imbuements
 * Description  :        return imbuement data (by reference!)
 */
public mapping
get_imbuements()
{
    return imbuements;
} /* get_imbuements */


/*
 * Function name:        get_id
 * Description  :        get an ID for an imbuement record
 */
public int
get_id()
{
    while (imbuements[max_id])
        max_id++;
    return max_id;
} /* get_id */


/*
 * Function name:        set_updated
 * Description  :        set flag to show data has been changed
 */
public int
set_updated()
{
    updated = 1;
} /* set_updated */


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
        envo = environment(rec[COL_OBJ]);
        if (IS_PLAYER_OBJECT(envo))
            env = capitalize(envo->query_real_name());
        else
            env = file_name(envo);
        out += sprintf("%-5d %-20s %d %s\n", id, rec[COL_TY1], rec[COL_LV2], env);
    }
    return out;
} /* list */


/*
 * Function name:        load
 * Description  :        load data from file
 */
public void
load()
{
    //imbuements = restore_map(IMBUE_DIR + "imbuement_data");
    restore_object(IMBUE_DIR + "imbuement_data");
    updated = 0;
} /* load */


/*
 * Function name:        save
 * Arguments    :        int mode - false = save only if needed, true = always
 * Description  :        save data to file
 */
public void
save(int mode)
{
    if (updated || mode)
        //save_map(imbuements, IMBUE_DIR + "imbuement_data");
        save_object(IMBUE_DIR + "imbuement_data");
    updated = 0;
} /* save */


/*
 * Function name: checkmissing
 * Description:   Reset "active" state of missing objects (after armageddon)
 */
public int *
checkmissing(int armageddon)
{
    int *ids = ({});
    foreach (int id, mixed *rec: imbuements)
    {
        if ((rec[COL_STA] == 1) && (!rec[COL_OBJ]))
        {
            rec[COL_STA] = (armageddon ? 4 : 3);
            ids += ({ id });
        }
    }
    updated = 1;
    return ids;
} /* checkmissing */