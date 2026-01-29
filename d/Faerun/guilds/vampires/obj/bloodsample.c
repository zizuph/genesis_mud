/*  /d/Faerun/guilds/vampires/obj/bloodsample.c
 *
 *  Questitem for the vampires entryquest.
 *
 *  Nerull, 2021
 *
 */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>


int
no_drop()
{
}


int
do_destroy(string str)
{
    if (str == "sample")
    {
        write("You destroy the small sample of vampire blood!\n");
        remove_object();
        
        return 1;
    }
    
    return 0;
}


void
create_object()
{
    set_name("_quest_vampire_bloodsample");
    add_name("sample");
    add_name("bloodsample");
    add_name("blood sample");
    add_name("small sample");
    add_name("small sample of blood");
    add_name("sample of blood");
    set_adj("small");
    add_adj("");
    
    set_short("small sample of blood");
    
    set_long("This is a small sample of vampire blood.\nYou may "
    +"<destroy sample> if you wish to rid yourself of this "
    +"object, or <give sample to x> to turn it in.\n");
    
    add_prop(OBJ_I_VALUE, 123);
    // Questitem no-drop properties.
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
}


init()
{
    ::init();
    add_action(do_destroy,"destroy");
}


string
query_recover()
{
    return 0;
}
