/* Solamnic Shop of Vingaard Keep by Morrigan, Jan 97     */
/* Based on the General Shop in Calia by Maniac         */

#pragma save_binary

inherit "/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include "../../guild.h"

inherit IN_BASE;
object keeper;

string
tell_message1()
{
    return "The sound of metal on metal rings from the south.\n";
}

string
tell_message2()
{
    return "A sudden gust of heat from the south swirls through "+
           "the room.\n";
}

string
tell_message3()
{
    if (!keeper || !P(keeper, TO))
    {
	return "A row of swords lined up against the wall falls, creating "+
	       "a loud crash. Unfortunately, there is no one here to pick "+
               "them up.\n";
    }
    return "A row of swords lined up against the wall falls to the ground "+
           "with a loud crash. "+QCTNAME(keeper)+" sighs and begins to clean "+
           "up the mess.\n";
}

string
tell_message4()
{
    if (!keeper || !P(keeper, TO))
    {
	return "";
    }

    return QCTNAME(keeper)+" frantically looks around for something.\n"+
           "Scowling angrily, "+QTNAME(keeper)+" shouts: Chert, that cursed "+
           "kender has stolen my ring again!\n";
}

void
reset_vin_room()
{
    if (!keeper)
    {
	keeper = clone_object(VNPC + "lauren");
	keeper->move(TO);
    }
}

/*
* Function name:   create_room
* Description:     Initialize this room
* Returns:
*/
void
create_room()
{
    config_default_trade();
    set_short("Solamnic Armoury");
    set_long("This small extension of the Smithy is well-heated, "+
      "most likely from the forge in the neighbouring room. " +
      "This room is unadorned, with only a small storeroom to the " +
      "west, and a counter in front of it. Also, a sign hangs from the " +
      "counter. This would be a difficult place to stand in, all day, " +
      "both boring and too warm.\n");
    AI(({"small extension","extension"}),"You are standing in it.\n");
    AI("smithy","The Redhammer Smithy sits to the south.\n");
    AI("counter","The counter is about one meter in height, so still " +
      "useful to a dwarf.\n");
    AI("sign","The sign can be read, for instructions.\n");
    ACI("sign","read","@@do_read");
    AI(({"wall","floor","ceiling"}),"It is made of the same dark stone " +
      "as the rest of Vingaard Keep.\n");
    AI("walls","They are made of the same dark stone as the rest of " +
      "Vingaard Keep.\n");
    AI(({"stone","dark stone"}),"The dark stone is definitely volcanic.\n");
    set_store_room(VROOM + "sol_store2");
    AE(VROOM + "sol_store2", "west", "@@wiz_check", 0, 1);
    AE(VROOM + "forge", "south", 0);
    INSIDE;
    query_store_room()->load_me();
    set_tell_time(150);
    add_tell("@@tell_message1");
    add_tell("@@tell_message2");
    add_tell("@@tell_message3");
    add_tell("@@tell_message4");

    reset_vin_room();
}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
	start_room_tells();
    }
}

/*
* Function name:   init
* Description:     Is called for each living that enters this room
* Returns:
*/
void
init()
{
    ::init();   /* You MUST do this in a room-init */

    init_shop();
}

/*
* Function name:   wiz_check
* Description:     Check if a player is a wizard
    * Returns:         0 if the player is a wizard
    *                  1 otherwise
*/
int
wiz_check()
{
    object tp;

    tp = TP;
    if (tp->query_wiz_level())
    {
	return 0;
    }

    write("Some magic force keeps you from going west.\n");
    say(QCTNAME(tp) + " tries to go west but fails.\n");
    return 1;
}

int
do_read(string str)
{   
    if (str == "sign")
    {
	write("\nSolamnian Knights may buy weapons and armours here.\n\n");
	return 1;
    }
    else
    {
	NF("Read what? The sign?\n");
	return 0;
    }
}

int
do_sell(string str)
{
    NF("You may not sell items here.\n");
    return 0;
}

int
do_buy(string str)
{
    NF("The shopkeeper is not here to buy from.\n");
    if (!P(keeper, TO))
    {
	return 0;
    }

    NF("You are not a Knight, only Knights may purchase armours and weapons from "+
      "this store.\n");

    if (!MEMBER(TP))
    {
  	return 0;
    }
    return ::do_buy(str);
}

