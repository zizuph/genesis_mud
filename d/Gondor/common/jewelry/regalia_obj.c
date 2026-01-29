/*
 * /d/Gondor/common/jewelry/regalia_obj.c
 * 
 * This handles the sublocs for any Orders that the player belongs to.
 * Only one is in the inventory at any time.
 *
 * Coded by Gwyneth, 08/02
 */
inherit "/std/object";

#include <composite.h>
#include <macros.h>
#include "jewelry.h"

string *gMember = ({}),
       *gKc = ({}),
       *gKgc = ({}),
       gSubloc1 = "",
       gSubloc2 = "";

public void create_object();
public void add_to_subloc(string desc, int rank);
public void remove_from_subloc(string desc, int rank);
public void set_order_subloc();
public string show_subloc(string subloc, object on, object for_obj);

public void
create_object()
{
    set_name(ORDER_SUBLOC_GROUP);
    add_name("decor");
    set_short("decor");
    set_long("You shouldn't be seeing this. Make a bug report.\n");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    
}

public void
add_to_subloc(string desc, int rank)
{
    switch(rank)
    {
    case 0:
        gMember += ({ desc });
        break;
    case 1:
        gKc += ({ desc });
        break;
    case 2:
        gKgc += ({ desc });
        break;
    default:
        return;
    }

    set_order_subloc();
    environment()->remove_subloc(ORDER_SUBLOC);
    environment()->add_subloc(ORDER_SUBLOC, this_object());
}

public void
remove_from_subloc(string desc, int rank)
{
    switch(rank)
    {
    case 0:
        gMember -= ({ desc });
        break;
    case 1:
        gKc -= ({ desc });
        break;
    case 2:
        gKgc -= ({ desc });
        break;
    default:
        return;
    }

    set_order_subloc();
    environment()->remove_subloc(ORDER_SUBLOC);
    environment()->add_subloc(ORDER_SUBLOC, this_object());
}

public void
set_order_subloc()
{
    string he, me, data, desc;

    he = capitalize(environment()->query_pronoun()) + " is a ";
    me = "You are a ";

    gSubloc1 = (sizeof(gMember) ?  he + "Member of " +
        COMPOSITE_WORDS(gMember) + ".\n" : "");
    gSubloc2 = (sizeof(gMember) ?  me + "Member of " +
        COMPOSITE_WORDS(gMember) + ".\n" : "");

    gSubloc1 += (sizeof(gKc) ? he + "Knight Commander of " +
        COMPOSITE_WORDS(gKc) + ".\n" : "");
    gSubloc2 += (sizeof(gKc) ? me + "Knight Commander of " +
        COMPOSITE_WORDS(gKc) + ".\n" : "");

    gSubloc1 += (sizeof(gKgc) ? he + "Knight Grand Cross of " +
        COMPOSITE_WORDS(gKgc) + ".\n" : "");
    gSubloc2 += (sizeof(gKgc) ? me + "Knight Grand Cross of " +
        COMPOSITE_WORDS(gKgc) + ".\n" : "");
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data, desc, order;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if(subloc == ORDER_SUBLOC)
    {
        if (!strlen(gSubloc1))
            return "";

        if(for_obj != on)
            return gSubloc1;
        else
            return gSubloc2;
    }

    return "";
}
