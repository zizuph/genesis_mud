inherit "/std/container";

#include "/d/Terel/include/Terel.h"


void
create_container()
{

    seteuid(getuid(TO));

        set_name("crate");
        add_name("explorer:crate");
	add_name("chest");
	add_name("box");
        set_short("wooden crate");
        add_adj("wooden");
        add_adj("wood");
        set_long("A large wooden crate. It looks " +
           "like it could hold a lot of stuff. There is a small label " +
           "pasted to the side that says: <sort crate> - to sort unsaving " +
           "items from the crate.\n");

        add_item("slats","Horizontal openings in between the wooden boards that " +
                 "make the crate.\n");
        add_item("boards","the wooden boards are made of pine. Nothing of interest " +
                 "unless you are a woodpecker.\n");

        set_no_show_composite(1);
        add_prop(CONT_I_CLOSED,0);
        add_prop(CONT_I_MAX_WEIGHT, 9000000);
        add_prop(CONT_I_MAX_VOLUME, 9000000);
        add_prop(CONT_I_WEIGHT, 500000);
        add_prop(CONT_I_VOLUME, 500000);

        add_prop(OBJ_I_VALUE, 8549);
        add_prop(CONT_I_RIGID, 1);
        add_prop(OBJ_M_NO_GET, "It is attatched to the wall by thick "
           +"metal and stone brackets.\n");

}




int
reject_object(object ob, object env)
{
    if (ob->move(env) == 0) {

                  tell_room(env,
                  capitalize(LANG_THESHORT(ob)) + " falls through the slats of " +
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
sort_crate()
{

    write("You sort the contents of " + LANG_THESHORT(this_object()) + "\n");
    say(QCTNAME(TP) + " sorts " + LANG_THESHORT(this_object()) + ".\n");

    map(all_inventory(this_object()),
         &recoverable_check(,environment(this_object()), this_player()));
         return 1;

}



init()
{
    ::init();
    add_action(sort_crate, "sort");
}
