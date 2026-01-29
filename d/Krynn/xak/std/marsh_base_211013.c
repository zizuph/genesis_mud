/* Xak Tsorath coded by Percy */

/* marsh_base by Aridor, 09/14/94 to be inherited in the marsh rooms
 * all basic stuff is already in here.
 *
 * Herbs added by Teth 11/11/96
 *
 * Marsh beetle grub fishing bait added.
 * Arman 01/10/21
 */

#include "../xlocal.h"

inherit  XAKOUTROOM
/*inherit  ROOM_TELLS*/
inherit  HERBSEARCHNEW

#include RND_MEET
#include <ss_types.h>
#include <macros.h>

#define BURREED             (KRHERB + "bur_reed")
#define HAS_SEARCHED_GRUBS   "_has_searched_marsh"
#define HOW_MANY_GRUBS       5
#define GRUB_OBJECT          "/d/Krynn/xak/obj/marsh_grub"

string *herbs = HERB_MASTER->query_herbs( ({ "swamp", }) );
object monster;
int times_searched = 0;

void
reset_xak_room()
{
    set_searched(random(2));

    times_searched = 0;

    if (random(5))
        return;

    if (monster)
        return;
    monster = RANDOM_MEET("/d/Krynn/common/rndtables/tblcursedlands");
    if (monster->query_prop(OBJ_I_COLORABLE))
        monster->set_color("black");
    monster->move(TO);
}

public int
query_grub_time_searched()
{
    return times_searched;
}

mixed
search_marsh(object searcher, string what)
{
  int find_grub = this_player()->query_skill(SS_HUNTING);
  if (CAN_SEE_IN_ROOM(this_player()))
    {
        times_searched += 1;
        // 20% chance with superior layman hunting skill
        if(random(150) > find_grub)
	    return ("You fruitlessly search through the water here, " +
                "but find nothing.\n");
	if (times_searched >= HOW_MANY_GRUBS)
	  {
	      return ("Your search of the water here reveals nothing special. " +
                  "You don't think you'll find any larvae in this location.\n"); 
	  }
	else
	  {
              say(QCTNAME(this_player())+ " pulls a marsh beetle larva from " +
                  "out of the slimy waters of the marsh!\n");
              setuid();
              seteuid(getuid());
              object grub = clone_object(GRUB_OBJECT);
              grub->move(this_player(), 1);
	      return "You pull a marsh beetle larva from out of the slimy " +
                  "waters of the marsh!\n";
	  }
    }
  return 0;
}

void
create_marsh()
{

}

nomask void
create_xak_room() 
{
    set_short("The cursed lands");
    set_long("You are in the cursed lands, a truly dismal place in"
      + " every sense of the word. All around you is a seemingly"
      + " endless marsh swamp. Danger seems to ooze from its nauseous"
      + " surface, and its slimy waters seem a breeding ground for "
      + "marsh beetle larvae.\n");

    add_search(({"water", "slimy water", "water for larva", 
       "waters", "slimy waters", "waters for larva",
       "waters for marsh beetle larvae", "waters for marsh beetle larva" }), 
       6, "search_marsh", 1);

    add_item(({"water", "slimy water", "slimy waters", "waters",
        "marsh beetle larvae", "marsh beetle", "larvae", "larva"}),
        "The slimy waters of the marsh are teeming with larvae " +
        "of the local marsh beetle. If you were so inclined you could " +
        "probably search the waters for some.\n");

    OUTSIDE;
    LIGHT;

    set_tell_time(45);
    add_tell("A small breeze has blown up helping you, at"
      + " least a little bit, to stand the awful swamp stench.\n");
    add_tell("A small pit of ooze erupts around you"
      + " covering you with filthy disgusting mud.\n");
    add_tell("Strange... you could swear you heard what sounded "
      + "like a cry for help.. nah must just be this damn swamp.\n");
    add_tell("A horde of mosquitoes surround you and start feeding on you"
      + ", after a few moments they move on leaving you covered"
      + " in ugly red splotches.\n");
    add_tell("A slimy fish rises briefly to the surface of the waters " +
       "of the marsh to gulp down the larva of a beetle before vanishing " +
       "quickly beneath the surface.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        BURREED, ONE_OF(herbs) }), ({ "marsh", "swamp" }), 7);

    create_marsh();
    reset_room();

}

int
cross()
{
    if (!random(3))
    {
        write("You trudge onwards through this horrible stinking"
          + " swamp. Crossing this swamp saps the energy from your body"
          + " and you have to concentrate on just putting one foot in "
          + "front of the other.\n");
        return 0;
    }
    write("You trudge endlessly onwards...\n");
    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}
