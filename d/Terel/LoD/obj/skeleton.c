/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * skeleton.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <stdproperties.h>
#include <language.h>

object rope = 0;

public void
create_object()
{
    set_name("skeleton");
    set_adj("old");
    
    set_long("It is an old skeleton. @@my_long@@\n");
    
    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, 0);
    
    add_item("neck", "@@my_neck@@\n");
}

public string
my_long()
{
    if (rope)
        return "Around its neck " + LANG_ADDART(rope->query_name()) +
               "is tied. You doubt that the prisoner himself " +
               "did that.";
    return "This poor prisoner must have starved to death.";
}

public string
my_neck()
{
    if (rope)
        return capitalize(LANG_ADDART(rope->query_name())) +
               " is tied around what is left of it.";
    return "Only the bones are left.";
}

public int
tie_object(object ob, string what)
{
    if (rope || (what != "skeleton" && what != "neck"))
        return 0;
        
    rope = ob;
    return 1;
}

public int
untie_object(object ob)
{
    if (!rope || rope != ob)
        return 0;
        
    rope = 0;
    return 1;
}
