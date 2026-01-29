#pragma strict_types

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include <macros.h>


string corpse_type;
string death_type;

void
create_object()
{

    string str;
    string * adjlist1 = ({ "male", "child", "female"});

    string * adjlist2 = ({ "beaten", "choked", "stabbed",""+ 
         "burned","sliced","cut","crushed","poisoned","bled"});

    corpse_type = adjlist1[(random(sizeof(adjlist1)))];

    death_type = adjlist2[(random(sizeof(adjlist2)))];

    set_name("pole");
    set_short("high wooden pole with an ice folk " + 
       corpse_type + " tied to its top");
    set_long("This is a high wooden pole. Someone has " +
      "staked it deep into the earth here. Tied to its top " +
      "hangs a naked corpse of an ice folk " + corpse_type + ". From " +
      "what you can see, the " + corpse_type + " has been " +
      "brutally tortured, and then " + death_type + " to death.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(OBJ_I_VOLUME, 30000);
    add_prop(OBJ_M_NO_GET, "Only a giant could attempt that!\n");
    add_prop(OBJ_M_NO_STEAL, "It is simply too big...\n");
}
       