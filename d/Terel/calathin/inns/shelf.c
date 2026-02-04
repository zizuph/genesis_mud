inherit "/std/container";

#include "/d/Terel/include/Terel.h"


void
create_container()
{

    seteuid(getuid(TO));

        set_name("shelf");
        add_name("explorer:shelf");
        set_short("wooden shelf");
	set_no_show_composite(1);
        add_adj("wooden");
        add_adj("wood");
        set_long("A common wooden shelf to put things on. It looks like you can " +
	         "<clean shelf> if you wish.\n ");


        add_prop(CONT_I_CLOSED,0);
        add_prop(CONT_I_MAX_WEIGHT, 5000000);
        add_prop(CONT_I_MAX_VOLUME, 5000000);
        add_prop(CONT_I_WEIGHT, 300000);
        add_prop(CONT_I_VOLUME, 300000);
        add_prop (CONT_I_ATTACH, 1);

        add_prop(OBJ_I_VALUE, 8549);
        add_prop(CONT_I_RIGID, 1);
        add_prop(OBJ_M_NO_GET, "It is attached to the wall you cant take it.\n");

}




int
reject_object(object ob, object env)
{
    if (ob->move(env) == 0) {

                  tell_room(env,
                  capitalize(LANG_THESHORT(ob)) + " falls from " +
                  LANG_THESHORT(this_object()) + ".\n");

        return 1;
    }
    return 0;
}


void
recoverable_check(object ob, object env)
{
    if (ob->check_recoverable())
        return;

    if (reject_object(ob, env));

}


int
sort_shelf()
{

    write("You clean " + LANG_THESHORT(this_object()) + "\n");
    say(QCTNAME(TP) + " cleans " + LANG_THESHORT(this_object()) + ".\n");

    map(all_inventory(this_object()),
         &recoverable_check(,environment(this_object()), this_player()));
         return 1;

}



init()
{
    ::init();
    add_action(sort_shelf, "clean");
}
