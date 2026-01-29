/*
 * File         : /d/Genesis/start/hobbit/obj/egg.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/21/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This orb is a wizard tool and should NOT be used instead of the
 *        'typo' or 'bug' commands after the code is released. We just
 *        want to enable a more structured way of quality check the code
 *        before release.
 * 
 * TODO         :
 * - logging of bugs/errors with comment
 * - listing of bug/errors
 * - mark bug/errors as done with comment
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types
/* inherits */
inherit "/std/object";
inherit "/lib/wearable_item";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <wa_types.h>
#include "../hobbit.h"
/* defines */
#define EGG_S_PATH "_orb_s_path"
#define EDITOR_OBJECT "/obj/edit"

/* prototypes */
string list_all();
string log_typo();

/* globals */


/*
 * Function name:       create_object
 * Description  :       set up the object
 */
void
create_object()
{
    set_name("egg");
    
    set_long(
      "This is the golden egg of truth. It is used by wizards to manage " +
      "a local set of log files. Typical usages are prerelase bug and " +
      "typo notes.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/21/99.\n");
    
    set_short("egg");
    add_prop(EGG_S_PATH,
        "/d/Genesis/seaweed/log/local/");
    add_cmd_item("all", "list", list_all);
    add_cmd_item("typo","log",  log_typo);
    
    
}
public void
leave_env(object env, object to)
{
    /*
     * override leave_env to detect when object is dropped
     */
    ::leave_env(env, to);
}

string
list_all()
{
    string *dir_contents;
    string ret;
    int i, sz;
    
    ret = "Directory of " + query_prop(EGG_S_PATH) + "\n";
    setuid();
    seteuid(getuid());
    dir_contents = get_dir(query_prop(EGG_S_PATH));
    for (i = 0, sz = sizeof(dir_contents) ; i < sz ; i++)
    {
        ret += (dir_contents[i] + "\n");
    }
    return(ret);
}

void
done_log_typo(string str)
{
    string fn;
    fn = "typo" + time() + ".log";
    setuid();
    seteuid(getuid());
    write_file(query_prop(EGG_S_PATH) + fn, str);
    write("The typo is logged in " + query_prop(EGG_S_PATH) + fn +". Thank you! \n");
}

string
log_typo()
{
    clone_object(EDITOR_OBJECT)->edit(done_log_typo, "", 1);
    return"";
}

