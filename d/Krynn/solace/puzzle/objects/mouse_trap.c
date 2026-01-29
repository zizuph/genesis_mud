/* A mouse trap. ~solace/puzzle/objects/mouse_trap */

inherit "/std/object";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

int cheese, set;

int query_ready()
{
    return(cheese & set);
}

void reset_trap()
{
    cheese = 0; set = 0;
}

void create_object()
{
    set_name("mouse-trap");
    add_name("trap");
    set_long("A small wooden mouse-trap with a serrated iron arm."+
        "@@cheese_and_set_desc@@\n");

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 450);
}

void init()
{
    ::init();

    add_action("set_trap", "set");
    add_action("get_cheese", "get");
    add_action("get_cheese", "take");
    add_action("add_cheese", "put");
    add_action("add_cheese", "prepare");
}

string cheese_and_set_desc()
{
    if(cheese)
        return(" It has been prepared with a slice of cheese"+
            (set ? " and has been set ready to trap mice!" : "."));
    else
        return "";
}

int set_trap(string str)
{
    if(!strlen(str))
        return 0;

    if((member_array(TO, FIND_STR_IN_OBJECT(str, TP)) != -1) ||
       (member_array(TO, FIND_STR_IN_OBJECT(str, E(TP))) != -1))
    {
        if(!cheese)
        {
            notify_fail("You can't set the trap without cheese!\n");
            return 0;
        }

        set = 1;

        TP->catch_msg("You pull back the arm of the trap to set it.\n");
        tell_room(E(TP), QCTNAME(TP)+" sets "+(E(TO) == TP ? "a" : "the")+
            " mouse-trap.\n", TP);
    }
    else
        return 0;

    return 1;
}

int get_cheese(string str)
{
    object what;

    if(parse_command(str, TP, "[slice] [of] 'cheese' 'off' / 'from' %o", what))
    {
        if(what == TO)
        {
            write("It seems to be stuck!\n");
            return 1;
        }
    }
    return 0;
}

int add_cheese(string str)
{
    object what, where, ob = E(TP);
    string prs1 = "%o 'on' / 'onto' %o", prs2 = "%o 'with' %o";

    if(!strlen(str))
        return 0;

    if((query_verb() == "put" && parse_command(str, ob, prs1, what, where)) ||
       (query_verb() == "prepare" && parse_command(str, ob, prs2, where, what)))
    {
        if(MASTER_OB(what) != OBJECTS + "cheese_slice")
        {
            notify_fail("You can't put that on!\n");
            return 0;
        }

        if(where != TO)
        {
            notify_fail("You can't put "+LANG_THESHORT(what)+" on there!\n");
            return 0;
        }

        cheese = 1;

        what->remove_object();

        TP->catch_msg("You put the cheese on the mouse-trap.\n");
        tell_room(E(TP), QCTNAME(TP)+" puts some cheese on the trap.\n", TP);
    }
    else
        return 0;

    return 1;
}







