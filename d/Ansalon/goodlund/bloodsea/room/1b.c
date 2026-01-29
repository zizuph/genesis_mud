#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"

inherit BLOODSEA_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "intertide", }) );

object ship, ship2, ship3;

void
reset_bloodsea_room()
{
     object boat_in, boat_in2, boat_in3;

     if (!objectp(ship)) 
     {
          ship = clone_object(BOBJ +"ship");
          ship->move(this_object());
     }

     if (!objectp(boat_in = ship->query_boat_in())) 
     {
         ship->config_boat_inside();
         boat_in = ship->query_boat_in();
     }

     if (!objectp(ship2)) 
     {
          ship2 = clone_object(BOBJ +"ship");
          ship2->move(this_object());
     }

     if (!objectp(boat_in2 = ship2->query_boat_in())) 
     {
         ship2->config_boat_inside();
         boat_in2 = ship2->query_boat_in();
     }

     if (!objectp(ship3)) 
     {
          ship3 = clone_object(BOBJ +"ship");
          ship3->move(this_object());
     }

     if (!objectp(boat_in3 = ship3->query_boat_in())) 
     {
         ship3->config_boat_inside();
         boat_in3 = ship3->query_boat_in();
     }

    set_searched(0);
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"huge ship", "stormseeker"}), "The "+
            "great ship 'Stormseeker' rises up to your southeast. Its heavy sails "+
            "flutter violently in the wind. On the deck you can see some strong "+
            "minotaurs pulling ropes and shouting at each other. The massive "+
            "hull has been made out of thick wooden planks, that have been "+
            "coated with tar making it very water proof.\n");
    add_item(({"pier","wooden pier","small pier","small wooden pier", "piers"}), 
               "To your east you can wade to a very old and wooden pier.\n");
    add_item(({"bay","horned bay","bloodsea","blood sea"}), "The Horned Bay "+
               "stretches out to the northwest where it meets the Bloodsea.\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");
    add_item(({"mithas", "isle", "village", "nethosak"}), "The great Imperial "+
             "city of Nethosak, home of the minotaurs of Ansalon, lies to the "+
             "east. This great city is the home of the Emperor of the Minotaurs "+
             "and the Great Arena, where minotaurs and other lucky 'volunteers' "+
             "fight against each other, sometimes to the death. This is also the "+
             "place of the Temple of the Stars, where the High Priest of the "+
             "minotaurs performs rituals to their god. A strong smell of "+
             "smoke and sweat fills the air.\n");
    add_item("ladder","A ladder rises out of the water here up to the pier. You could " +
             "probably climb it.\n");

    add_row_exit(BROOM + "1c", "north", 0, 1);
    add_row_exit(BROOM + "2b", "west", 0, 1);
    add_row_exit(BROOM + "2a", "southwest", 0, 1);
    add_wade_exit(BROOM + "1c", "north", "@@swim_off", 1);

    add_cmd_item(({"ladder", "up ladder"}),"climb",
      "@@climb_ladder");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_bloodsea_room();

}

int
swim_off()
{
   write("You swim along the side of the pier.\n");
   return 0;
}

string
climb_ladder()
{
    write("You climb up the ladder to the pier above you.\n");
    say(QCTNAME(this_player()) + " climbs the ladder.\n");
    tell_room("/d/Ansalon/goodlund/nethosak/city/room/pier6",
      QCTNAME(TP) + " climbs up to the pier from the water below.\n");
    TP->move_living("M","/d/Ansalon/goodlund/nethosak/city/room/pier6",1,0);
    return "";
}

/*
void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}
*/

string
short_descr()
{
    return "Horned Bay near the Nethosak piers";
}
 
string
long_descr()
{
    return "You are near the piers of Horned Bay, where the minotaurs " +
    "of Nethosak dock. A ladder rises out of the water up to the pier here. " +
    bloodsea_desc()+ "\n";
}