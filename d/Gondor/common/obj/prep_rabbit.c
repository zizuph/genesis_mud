inherit "/std/food";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

void    poisoned(object player);

void
create_food()
{
    set_name("rabbit");
    set_pname("rabbits");
    add_pname("meats");
    add_name("meat");
    add_name("_rabbit_meat");
    set_long("Meat from a rabbit. It looks delicious.\n");
}

public mixed
command_eat()
{
    mixed     flag;
    flag = ::command_eat();
    if (intp(flag) && flag && this_object()->query_prop("_poisoned"))
        poisoned(TP);
    return flag;
}

void
poisoned(object player)
{
    object poison;

    seteuid(getuid(TO));

    poison = clone_object(OBJ_DIR + "poison_water_effect");
    poison->move(player);
    log_file("curses", TP->query_name()+" was poisoned by rabbit cooked in dirty water on "+ctime(time())+".\n");
    poison->start_poison();
}

void
start_cooling()
{
    set_alarm(300.0, 0.0, "cooled");
}

void
cooled()
{
    object  room = ENV(TO);

    while (!room->query_prop(ROOM_I_IS))
        room = ENV(room);
    short(); /* Have to call short() so that query_short() will be defined. */
    tell_room(room,"The "+query_short()+" is not hot anymore.\n");
    add_prop("_not_hot_any_more",1);
}

int
eat_access_from_pot(object ob)
{
    object room = ENV(TO);
    while(!room->query_prop(ROOM_I_IS))
       room = ENV(room);
    short(); /* Have to call short() so that query_short() will be defined. */
    if (present(TP, room) && 
        (function_exists("create_heap", ob) == "/std/food") &&
        (ob->query_short()))
        return 1;
    else
        return 0;
}

void
consume_text_from_pot(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + " from the pot.\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str + " from the pot.\n");
}

/*
 * Copied from /std/food.c eat_it(string str)
 * mod: vb = query_verb(); -> vb = "eat";
 *
 * Olorin, 23-jun-1993
 */
int
eat_from_pot(string str)
{
    object *a;
    int     il;
    mixed   flag;
    string vb;

    if (this_player()->query_prop(TEMP_STDFOOD_CHECKED))
        return 0;

    vb = "eat";

    notify_fail(capitalize(vb) + " what?\n");  /* access failure */

    if (eat_access_from_pot(TO))
        flag = command_eat();
    else
        find_player("gnadnar")->catch_msg(file_name(TO)+" No eat_access!\n");

    if (intp(flag) && flag)
    {
        consume_text_from_pot( ({TO}), vb);
        TO->remove_object();
        return 1;
    }
    else
    {
        set_alarm(1.0, 0.0, "tp_remove_temp", this_player());
        this_player()->add_prop(TEMP_STDFOOD_CHECKED, 1);
        if (stringp(flag))
            notify_fail(flag);
        return 0;
    }
}
