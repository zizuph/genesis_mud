/* Tantallon coded by Nick */

#include "local.h"

inherit TANTALLON_OUTSIDE;

object draco, human, baaz1, baaz2;

#include RND_MEET

boy_arrive()
{
    if (!present("boy", TO))
    clone_object(MON + "ne_child")->move_living("xxx", TO);
}

reset_tantallon_room()
{
    if (baaz1)
    	return;
    baaz1 = clone_object("/d/Krynn/std/baaz");
    if (baaz1->query_prop(OBJ_I_COLORABLE))
	baaz1->set_color("red");
    BAAZ_COIN1->move(baaz1);
    BAAZ_COIN2->move(baaz1);
    baaz1->move_living("xx", TO);

    if (baaz2)
    	return;
    baaz2 = clone_object("/d/Krynn/std/baaz");
    if (baaz2->query_prop(OBJ_I_COLORABLE))
	baaz2->set_color("red");
    BAAZ_COIN1->move(baaz2);
    BAAZ_COIN2->move(baaz2);
    baaz2->move_living("xx", TO);

    set_alarm(3.0,0.0,"boy_arrive");
    if (draco)
        return;
    draco = RANDOM_MEET(DRACOS);/*clone_object(MON + "draconian");*/
    if (draco->query_prop(OBJ_I_COLORABLE))
    draco->set_color("red");
    draco->set_random_move(30);
    draco->move_living("xx", TO);

    if (!human)
      set_alarm(6.0,0.0,"load_human");
}

load_human()
{
    int i;

    human = clone_object(MON + "ne_hum_g");
    human->move_living("xxx", TO);

    if (random(3))
        human->set_random_move(random(100));

}

create_tantallon_room()
{
    object door;
    set_short("By river");
    set_long(BS(
        "You are in a tight location between the river east from here and a " +
        "tent to the west. There is another tent south. Southwest it looks " +
        "rather dirty, perhaps it's better to follow the river north.", SL));

    add_item("tent",
           "Which tent do you mean, the south tent or the west tent?\n");
    add_item("west tent", BS(
        "It's grey and rather big. Ten people could at least stand up in it. " +
        "There is a lot of noise coming from it. You see no entrance though." +
    "", SL));
    add_item("south tent", BS(
        "It's a small black tent. You see no entrance nor do you hear any " +
        "sounds from it but it radiates evil.", SL));
    add_item("river",
        "It runs from north to south.\n");
    add_item("fish", "The fish disappears as you look only to reappear elsewhere in the river.\n");

    add_exit(TDIR + "city23", "southwest", 0);
    add_exit(TDIR + "city17", "north", "@@follow");

    set_alarm(1.0,0.0,"reset_room");

    door = clone_object(OBJ + "d_city20_a");
    door->move(TO);
    door->set_key(K_CITY20);
}

follow()
{
    write("You follow the river north.\n");
    return 0;
}
