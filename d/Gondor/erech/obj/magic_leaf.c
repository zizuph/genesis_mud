/* 
 * magic_leaf.c
 * By Skippern Dec 2000
 *
 * Example used: /d/Gondor/pelargir/misc/tournote.c by Elessar
 */

inherit "/std/object";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../erech.h"

int     task_no,
        task_done;
string  task,
        player_name,
       *cnames = ({});

void
create_object()
{
    set_name("leaf");
    add_name("Erech_Task_Item");
    set_short("@@short_desc@@");
    set_pshort("magical leaves");
    set_long("@@long_desc@@");
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_WEIGHT, 2);
}

void
set_task_no(int i)
{
    task_no = i;
}

int
query_task_no()
{
    return task_no;
}

void
set_task_done()
{
    task_done = 1;
}

void
set_player_name(string str)
{
    player_name = str;
}

string
query_player_name()
{
    return player_name;
}

int
query_task_done()
{
    return task_done;
}

void
set_task(string s)
{
    task = s;
}

string
query_task()
{
    return task;
}

string
short_desc()
{
    if (task_done)
        return "a green magical leaf";
    else
      return "a red magical leaf";
}

string
long_desc()
{
    string clr, ld;

    if (task_done)
      clr = "green";
    else
      clr = "red";

    ld = "This is a magical leaf. It looks prety much like " +
      "a normal maple leaf, but when you drow your fingers over it you " +
      "notices a strange pressence. ";

    ld = BSN(ld)
      + "Utmir have given the leaf a magical feeling. ";
    //      + BSN(task);

    ld += "The leaf is " + clr + " telling you ";
    if (task_done)
      ld += "that the task is done.\n";
    else
      ld += "that the task is not done.\n";

    return ld;
}

