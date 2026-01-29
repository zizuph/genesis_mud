// file name: grotto.c
// creator(s): Ilyian (April, 1995)
// last update:
// purpose: This is where the key is hidden for the faerie quest
// to-do:

inherit "/std/room";

#include <stdproperties.h>

#include "park.h"
#include "mon/faerie_quest.h"

private static object key;

public void reset_room(void);

public void
create_room(void)
{
    set_short("Damp grotto");
    set_long("You are in a small, rough cave-like grotto. The air smells "
      +"stale and ancient, and the walls glisten with the water that "
      +"runs down it. The right half of this cavern drops off into "
      +"black water, "
      +"but the rest is a smooth rock floor. Strange, clinging vines "
      +"that have a pale luminescence run down the walls here, which "
      +"light the cavern with an eerie glow. Shadows play in the "
      +"corners of this cave, and it is difficult to make out "
      +"anything in detail.\n");

    AI(({"grotto","cave","cavern"}),"The cavern is fairly big, and seems "
      +"to be naturally formed.\n");
    AI(({"wall","walls"}),"The walls are rough and craggy, glistening with "
      +"trickles of water that run down it and along the floor. Many "
      +"strange looking vines are clinging to the walls here.\n");
    AI(({"vine","vines"}),"They seem to glow with a luminesence, lighting "
      +"the cavern a small bit. The vines cling firmly to the rocks, "
      +"though, leaving you with little possibility of getting them "
      +"off.\n");
    AI(({"floor","rock"}),"The floor beneath your feet is surprisingly "
      +"smooth. It drops off on the east side of the cavern into a "
      +"deep and dark pool of water, and the rest extends below "
      +"small outcroppings of rock that form the base of the walls.\n");
    AI(({"shadow","shadows"}),"The shadows make it difficult to see any "
      +"details of the room.\n");
    AI(({"pool","water","dropoff"}),"The water at the east end of the grotto "
      +"is dark and deathly cold. You cannot tell how deep it is.\n");

    add_prop(ROOM_I_LIGHT, 9);
    IN_IN

    seteuid(getuid(this_object()));

    set_search_places(
	({"wall","walls","grotto","vine","vines","cave","cavern"}));

    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    add_herb_file(HERB+"mittikna");
    add_herb_file(HERB+"mittikna");

    reset_room();
}

public void
reset_room(void)
{
    if (!key || !present(key, TO))
    {
	key = clone_object(PK + "obj/cage_key");
	key->move(this_object(), 1);
	key->add_prop(OBJ_I_HIDE, 40 + random (5));
    }

    set_searched(0);
}

public int
do_dive(string str)
{
    write("You dive back into the dark and freezing pool, and "
      +"quickly drop down into the tunnel.\n");
    this_player()->move_living("into the water",PK + "water/water18");
    return 1;
}

public int
do_breath(string str)
{
    if (str != "breath") return 0;
    write("You take a deep breath of air and hold it in your lungs.\n");
    say(QCTNAME(this_player()) +
      " takes a deep breath of air holds it.\n");
    return 1;
}

public 
init(void)
{
    ::init();
    add_action(   do_dive, "dive" );
    add_action( do_breath, "take" );
}
