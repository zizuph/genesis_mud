// Ziggurat Garden Storeroom (ZIG_RL3 + "store_garden.c")
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Avenir/inherit/storage";

#include "zigg.h"
#include "../garden/flowers.h"

#define NUM_FLOWER	20
#define NUM_POSY	5
#define NUM_BOUQUET	5

private void
make_singles(void)
{
    int num = NUM_FLOWER;

    while(num--)
    {
	mixed flower = one_of_list(m_indices(m_flowers));
	string colour = one_of_list(m_flowers[flower][3]);
	object ob = clone_object(SINGLE);

	ob->set_flower(flower, colour);
	ob->move(TO);
    }
}

private void
make_posies(void)
{
    int num = NUM_POSY;

    while(num--)
    {
	string flower = one_of_list(m_indices(m_flowers));
	string colour = one_of_list(m_flowers[flower][3]);
	object ob = clone_object(POSY);

	ob->make_flowers(flower, colour);
	ob->move(TO);
    }
}

private void
make_bouquets(void)
{
    int num = NUM_BOUQUET;

    while(num--)
    {
	string flower = one_of_list(m_indices(m_flowers));
	string colour = one_of_list(m_flowers[flower][3]);
	object ob = clone_object(BOUQUET);

	ob->make_flowers(flower, colour);
	ob->move(TO);
    }
}

public void
reset_store(void)
{
    all_inventory()->remove_object();

    ::reset_store();

    set_alarm(0.2, 0.0, &make_singles());
    set_alarm(0.5, 0.0, &make_posies());
    set_alarm(1.0, 0.0, &make_bouquets());
}

public void
create_room(void)
{
    set_shop_room(ZIG_RL3 + "garden");

    set_short("The flower shop's store room");
    set_long("This is the store room for the flower shop.\n");

    add_exit("garden", "out");

    add_prop(ROOM_I_INSIDE, 1);

    set_default_stock(
      ({
	ZIG_OBJ + "p_basket", 5,
      })
    );

    max_items = 50;
    enable_reset(200);
    reset_store();
}
