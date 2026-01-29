/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object human, kapak1, kapak2, bozak;

reset_tantallon_room()
{
    if (!human)
      set_alarm(6.0,0.0,"load_human");

    if(!objectp(kapak1))
        {
         kapak1 = clone_object("/d/Krynn/std/kapak");
         kapak1->set_color("red");
         KAPAK_COIN1->move(kapak1);
         KAPAK_COIN2->move(kapak1);
         kapak1->move(TO);
    }

    if(!objectp(kapak2))
        {
         kapak2 = clone_object("/d/Krynn/std/kapak");
         kapak2->set_color("red");
         KAPAK_COIN1->move(kapak2);
         KAPAK_COIN2->move(kapak2);
         kapak2->move(TO);
    }

    if(!objectp(bozak))
        {
         bozak = clone_object("/d/Krynn/std/bozak");
         bozak->set_color("red");
         BOZAK_COIN1->move(bozak);
         bozak->move(TO);
    }

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
    set_short("Center of Tantallon");
    set_long(BS(
        "You are in the middle of Tantallon. You stand in the northwest corner " +
        "of an opening. A lot of people are running around in what appears " +
    "to be circles. The evil in the air is very strong now. One tent is " +
    "north from you and west is a very big building.", SL));

    add_item(({"tent", "north tent"}), BS(
        "It looks like if this tent is the biggest one in Tantallon. It's " +
    "coloured in deep black and you feel something evil present in " +
    "it.", SL));
    add_item("people", BS(
        "At a closer look you see that some are talking to each other and " +
    "others are walking quickly cross this place.", SL));
    add_item(({"building", "big building"}), BS(
        "This is the biggest, and also the only, building in Tantallon. It " +
    "appears to be some kind of a temple. You understand that this is " +
    "the center of all evil in this city.", SL));

    add_exit(TDIR + "city8", "northwest", 0);
    add_exit(TDIR + "city15", "south", 0);
    add_exit(TDIR + "city12", "east", 0);
    add_exit(TDIR + "temple1", "west", "@@construction");
    add_exit(TDIR + "tent6", "north", 0);
    seteuid(getuid(TO));
    clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());

    reset_tantallon_room();
}

construction()
{
    write("This temple is still under construction.\n");
    return 1;
}

