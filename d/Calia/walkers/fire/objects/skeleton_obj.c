/* Skeleton object. This is cloned to the room if something is killed
   by the Aeras spell for the Firewalkers. 

   Coded by Bishop, June 20th, 1999.
*/

inherit "/std/object";

#include <stdproperties.h>
#include "defs.h"

public void set_race(string str);
public string query_race();

public string race = "human";


create_object()
{
    set_name("skeleton");
    set_adj(({"blackened", "@@query_race@@"}));
    set_short("blackened @@query_race@@ skeleton");

    set_long("This is the remains of an unfortunate @@query_race@@" +
        " who was killed by incredible heat by the looks of it.\n");

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 5000);
    remove_prop(OBJ_I_VALUE);
}

public void
set_race(string str)
{
    race = str;
}

public string
query_race()
{
    return race;
}