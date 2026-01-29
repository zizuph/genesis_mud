
/*

   /d/Calia/gelan/cadet/cadet_notebook.c 

   A notebook and quill that is required for some cadet emotes. 

   Coded by Maniac@Genesis, September 1997

*/ 

inherit "/std/heap"; 

#include <macros.h>
#include <stdproperties.h>
#include "cadet.h"

void
create_heap()
{
    set_heap_size(1); 

    set_name("notebook"); 
    add_name("quill"); 
    add_name(GC_NOTEBOOK_ID); 
    set_adj(({ "cadet" })); 
    set_short("notebook and quill"); 
    set_pshort("notebooks and quills"); 
    set_long("A cadet's notebook and quill. If you want to get rid of " +
            "it you can <tear notebook>.\n"); 

    add_prop(HEAP_I_UNIT_VALUE, 0); 
    add_prop(HEAP_I_UNIT_WEIGHT, 100); 
    add_prop(HEAP_I_UNIT_VOLUME, 100); 
    add_prop(HEAP_S_UNIQUE_ID, GC_NOTEBOOK_ID); 
}


int
tear_notebook(string str)
{
    notify_fail("Tear notebook?\n"); 
    if (str != "notebook")  
        return 0;
    write("You tear up " + LANG_THESHORT(this_object()) + ".\n"); 
    say(QCTNAME(this_player()) + " tears up " + 
                LANG_THESHORT(this_object()) + ".\n"); 
    set_heap_size(0);  
    return 1;
}

void
init()
{
    ::init(); 
    add_action(tear_notebook, "tear");  
}

