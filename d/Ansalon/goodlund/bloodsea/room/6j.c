#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_OUT;

object mino_warship, corth, mino1, mino2, mino3, mino4;

object cabin_room = BOBJ + "mino_warship_cabin";
object down_room = BOBJ + "mino_warship_down";

void
reset_bloodsea_room()
{

     object boat_in;

     if (!objectp(mino_warship)) 
     {
          mino_warship = clone_object(BOBJ +"mino_warship");
          mino_warship->move(this_object());
     }

     if (!objectp(boat_in = mino_warship->query_boat_in())) 
     {
         mino_warship->config_boat_inside();
         boat_in = mino_warship->query_boat_in();
     }

     if (!objectp(corth)) 
     {
         corth = clone_object(BNPC + "minotaur_corth");
         corth->move_living("into his warship", boat_in);
         boat_in->set_owner(corth); 
         corth->command("cabin");
         cabin_room->clean_loot();
         
     }

     if (!objectp(mino1)) 
     {
         mino1 = clone_object(BNPC + "minotaur_sailor");
         mino1->move_living("into his warship", boat_in);
         mino1->command("down");
         cabin_room->clean_loot();
     }   
     
     if (!objectp(mino2)) 
     {
         mino2 = clone_object(BNPC + "minotaur_sailor");
         mino2->move_living("into his warship", boat_in);
         mino2->command("down");
         cabin_room->clean_loot();
     }

     if (!objectp(mino3)) 
     {
         mino3 = clone_object(BNPC + "minotaur_sailor");
         mino3->move_living("into his warship", boat_in);
     }

     if (!objectp(mino4)) 
     {
         mino4 = clone_object(BNPC + "minotaur_sailor");
         mino4->move_living("into his warship", boat_in);
     }       
     
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"cliff", "steep cliffs", "cliffs"}),
               "Steep cliffs rise high above you out of the waters of Horned Bay. " +
               "Dark and menacing, the cliffs seem unscalable from here.\n");
    add_item(({"bay","horned bay","bloodsea","blood sea"}), "The Horned Bay "+
               "opens out to the southeast, while to the west is the Bloodsea " +
               "of Istar.\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");

    add_row_exit(BROOM + "5k", "northeast", 0, 1);
    add_row_exit(BROOM + "7j", "west", 0, 1);
    add_row_exit(BROOM + "6k", "north", 0, 1);
    add_row_exit(BROOM + "6i", "south", 0, 1);
    add_row_exit(BROOM + "5i", "southeast", 0, 1);


    add_cmd_item(({"cliff","cliffs","steep cliffs"}),
      ({"climb", "scale"}),"@@climb_cliff");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_bloodsea_room();

}

string
climb_cliff()
{
    write("The cliffs are too steep to climb here.\n");
    say(QCTNAME(TP) + " tries to climb the cliffs here, but they are too steep.\n");
    return "";
}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return "near the entrance to Horned Bay of the isle of Mithas";
}
 
string
long_descr()
{
    return "You are at the edge of the cliffs that form the entry " +
       "to Horned Bay of the isle of Mithas. " +bloodsea_desc()+
    "\n";
}