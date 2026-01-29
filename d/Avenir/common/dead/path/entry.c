
// file name: Entry
// creator(s): Ilyian (28 August, 1995)
// last update: Lilith Feb 2002: added aglyna summoning
//              Cirion, February 1996
// purpose:
// note:      Algna to the Seawall
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"
#include "/d/Avenir/include/relation.h"

int pass_arch();

create_room()
{

  set_long("Rising ahead to the north is a massive stone "
          +"arch that stands inexplicably before the apex "
          +"of the hill. Through the arch can be made out "
          +"a number of large figures in the mist, standing "
          +"like sentinels. The path leads back to the southwest, "
          +"and the hill drops down steeply to the west, east, and "
          +"south.\n");
  set_short("before the arch");

  AI(({"object", "objects", "figure", "figures", "shape", "shapes"}),
            "You can not make out the shapes from here. All you "
           +"can tell is that they are large.\n");
  AI(({"arch","archway","south"}),"The massive arch of decaying "
         +"stone rises up to the north, like a gate leading "
         +"to the top of the hill.\n");
  AI(({"mist","fog"}),"The mist is not so thick up here "
         +"as it is down below, but it still makes a light "
         +"covering over everything.\n");
  

  ahdown(HILL+"hill4","west");
  ahdown(HILL+"hill10","east");
  ahdown(HILL+"hill11","south");
  AE(HILL+"cairn", "north", "@@pass_arch", 1);
  AE(PATH+"path10", "southwest", 0, 1);

}

int pass_arch()
{
  write("You pass beneath the massive arch.\n");
  say(QCTNAME(TP)+ " passes beneath the massive arch.\n");
  return 0;
}

void
summon()
{
    int num_players, num_steeds, how_many, i;
    object *steeds = ({});

    num_players = sizeof(FILTER_PLAYERS(all_inventory(TO)));
    num_steeds = sizeof(filter(all_inventory(TO), &->id("aglyna")));

    how_many = num_players - num_steeds;

    if(how_many <= 0)
    {
         return;
    }

    for(i = 0; i < how_many; i++)
        steeds += ({ clone_object("/d/Avenir/common/outpost/mon/aglyna") });

    steeds->move_living("M", TO);

    tell_room(TO, "Flying down from great heights, "
        + COMPOSITE_LIVE(steeds) + " descend" + (sizeof(steeds) == 1 ? "s" : "")
        + ".\n");

}

void populate_island()
{
   UMAKER->create_room();
   UMAKER->start_cooking();
}

void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if (interactive(to))
        populate_island();

    if(IS_SYBARITE(to))
       set_alarm(30.0, 0.0, summon);
}
