/*
 * /d/Gondor/common/guild/obj/prep_animal.c
 *
 * Coded by Mayhem.
 */
inherit "/std/food.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define FOOD_POISONED   "_poisoned"
#define FOOD_NOT_HOT    "_not_hot_any_more"

public string  query_animal_long();
public void    cooled();
public void    poisoned(object player);

static string  Animal_Type;

public void
create_food()
{
    set_name("animal");
    add_name("meat");
    add_name("_animal_meat");
    set_long(query_animal_long);
}

public void 
set_animal_type(string what)
{
    Animal_Type = what;
}

public string 
query_animal_long()
{
    if (!Animal_Type)
    {
        return "Some kind of cooked meat. You can't tell what animal it " +
            "came from, but it looks delicious.\n";
    }
    else
    {
        return "Some cooked meat from " + LANG_ADDART(Animal_Type) +
            ". It looks delicious.\n";
    }
}

public mixed
command_eat()
{
    mixed flag;
    flag = ::command_eat();

    if (intp(flag) && flag && TO->query_prop(FOOD_POISONED))
        poisoned(TP);

    return flag;
}

private void
poisoned(object player)
{
    object poison;

    seteuid(getuid(TO));

    poison = clone_object(OBJ_DIR + "poison_water_effect");
    poison->move(player);
    poison->start_poison(this_player());

    log_file("curses", TP->query_name() + " was poisoned by " +
        Animal_Type + " cooked in dirty water on " + ctime(time())+".\n");
}

public void
start_cooling()
{
    set_alarm(200.0, 0.0, cooled);
}

public void
cooled()
{
    object room = ENV(TO);
    while (!room->query_prop(ROOM_I_IS)) 
        room = ENV(room);

    /* Have to call short() so that query_short() will be defined. */
    short(); 
    tell_room(room,"The " + query_short() + " is not hot anymore.\n");
    add_prop(FOOD_NOT_HOT, 1);
}

public int
eat_access_from_pot(object ob)
{
    object room = ENV(TO);

    while (!room->query_prop(ROOM_I_IS)) 
        room = ENV(room);

    /* Have to call short() so that query_short() will be defined. */
    short(); 

    if (present(TP, room) && 
      (function_exists("create_heap", ob) == FOOD_OBJECT) &&
      (strlen(ob->query_short())))
        return 1;
    else
        return 0;
}

public void
consume_text_from_pot(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + " from the pot.\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str + " from the pot.\n");
}

public void
tp_remove_temp(object pl)
{
    pl->remove_prop(TEMP_STDFOOD_CHECKED);
}

/*
 * Copied from /std/food.c eat_it(string str)
 * mod: vb = query_verb(); -> vb = "eat";
 *
 * Olorin, 23-jun-1993
 */
public int
eat_from_pot(string str)
{
    object *a;
    int il;
    mixed flag;
    string vb;

    if (TP->query_prop(TEMP_STDFOOD_CHECKED))
        return 0;

    vb = "eat";

    if (eat_access_from_pot(TO)) 
        flag = command_eat();

    if (flag && intp(flag))
    {
        consume_text_from_pot( ({ TO }), vb);
        TO->remove_object();
        return 1;
    }
    else
    {
        set_alarm(1.0, 0.0, &tp_remove_temp(TP));
        TP->add_prop(TEMP_STDFOOD_CHECKED, 1);

        if (stringp(flag))
            NF(flag);
        else
            NF(CAP(vb) + " what?\n");

        return 0;
    }
}

public string
query_recover()
{
    return MASTER + ":heap#" + num_heap() + "#" + food_amount + "#" + Animal_Type;
}

public void
init_recover(string str)
{
    string foobar;
    int    num;

    if (sscanf(str, "%sheap#%d#%d#%s", foobar, num, food_amount, Animal_Type) == 4)
    {
        set_heap_size(num);
	set_short("cooked " + Animal_Type);
	set_amount(food_amount);
	set_name(Animal_Type);
    }
}
