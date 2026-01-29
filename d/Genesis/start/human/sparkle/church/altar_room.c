/*
 * /d/Genesis/treacher/rooms/altar_room.c
 * Created by: Treacher
 * Started: 1999-09-13
 */

/* inherit "/d/Genesis/treacher/default_room";*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define PLAYER_HAS_BLOWN_CANDLES   "_player_i_has_blown_candles"

int candles_are_lit = 1;

void
create_room()
{   
    set_short("altar room");
    set_long("As you slyly walks over the floor, the sound "+
      "of your footsteps echo below the high ceiling. "+
      "Slightly at your side a smooth marble altar erupts "+
      "from the floor. Placed on two sides of the altar, "+
      "two high candelabras stands tall.\n");

    add_item("ceiling",
      "High above you the ceiling spreds out.\n");
    add_item(({ "floor", "marble floor" }),
      "The floor is entirely made of marble, and it reflects "+
      "the surroundings easily.\n");
    add_item(({ "candle", "candles" }),
      "The candles are placed in a circle around the altar to "+
      "shed light apon it.\n");
    add_item(({ "candelabra", "candelabras" }),
      "Standing on long legs, the candelabras reaches high above "+
      "the altar. Still the candles sheds strong light apon the it.\n"+
      "The candles are placed on the candelabra in a cricle, with one "+
      "candle in the center.\n");

    room_add_object("/d/Genesis/start/human/sparkle/church/altar.c", 1, "test");

    add_prop(ROOM_I_INSIDE, 1);

}


int
query_candle_status()
{
    return candles_are_lit;
}

int
set_candle_status(int i)
{
    candles_are_lit = i;
    return 1;
}

int
do_blow_candles(string str)
{
    int i;

    if(!str || (member_array("candles", explode(str," ")) == -1))
	return notify_fail("Blow out what?");

    write("You blow out the candles.\n");
    say(QCTNAME(this_player()) + " blows out the candles.\n");
    this_player()->add_prop(PLAYER_HAS_BLOWN_CANDLES, 1);
    set_candle_status(0);
    return 1;

}


void
init()
{
    add_action(&set_candle_status(1), "light");
    add_action(&set_candle_status(0), "ext");

    add_action(do_blow_candles, "blow");
}






