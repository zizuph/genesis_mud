/*
   rag_doll.c
   ----------

   Coded ........: 95/01/16
   By ...........: Jeremiah

   Latest update : 95/01/16
   By ...........: Jeremiah


  rag doll used in the prisoner quest in Pax Tharkas. The doll is given
  to the player by a gully dwarf. If the dwarf is killed there will be 
  blood stains in the doll, and it will be useless in solving the quest.
  
 
*/

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"


int blood_stains = 0; /* 0 = NO blood stains on doll */

void
create_object()
{
    set_name("doll");
    add_name("pax_quest_doll");
    set_adj(({ "small", "rag" }));
    set_short("@@doll_descr@@");

    set_long("A small doll made of old rags. It is wearing " +
        "a small dress. A small smiling face has been " +
        "drawn on the head of the doll.\n");
    
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,200);
}


string
doll_descr()
{
    if (blood_stains)
        return "small blood-stained rag doll";
    else
        return "small rag doll";
}


void
set_blood_stains()
{
    blood_stains = 1;
    add_adj("blood-stained");
}


int
query_blood_stains()
{
    return blood_stains;
}


