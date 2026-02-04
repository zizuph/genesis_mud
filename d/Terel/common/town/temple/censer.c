/* torch.c A sample torch */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#define TP this_player()

public void
create_object()
{
    set_name("censer");
    set_adj(({"small", "silver"}));
    set_long("A small silver censer on a chain. It is beautiful.\n");
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_WEIGHT, 140);
    add_prop(OBJ_I_VOLUME, 50);
}

public int
do_light(string str)
{
    if (!id(str)) return 0;
    
    write("You light the censer.\n");
    write("Incense begins to rise out of the censer.\n");
    say(QCNAME(TP) + " lights a silver censer.\n");
    return 1;
}

public int
do_reverence(string str)
{
    if (!id(str)) return 0;
    
    write("You reverence this place with holy incense.\n"); 
    say(QCNAME(TP) + " reverences this place with incense.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_light,     "light"); 
    add_action(do_reverence, "reverence");
}
