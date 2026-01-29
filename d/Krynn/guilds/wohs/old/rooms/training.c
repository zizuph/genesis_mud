/*
   Wayreth.

   training.c
   ----------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : July 1997
   By ...........: Kentari

*/

#include "../guild.h"

inherit TOWERROOM;

void
create_tower_room()
{
   set_short("Training Lobby");
   set_long("This room is the lobby of the Wizards of High Sorcery training " +
            "area. South lies a room that radiates magic, and " +
            "is obviously where magic training takes place. West is " +
            "a room where Magi may find peace, and deliberate upon " +
            "their existence. A stairwell lies to the east.\n");


   add_exit("norm_skills", "north", 0);
   add_exit("stairwell06", "east", 0);
   add_exit("mage_skills", "south", 0);
   add_exit("meditation", "west", 0);

   AI(({"walls","wall"}),"The walls are made of magicked obsidian.\n");
   AI(({"floor","ceiling"}),"It is made of magicked obsidian.\n");
   AI("stairwell","The stairwall leads both up and down the tower.\n");
   AI(({"area","training area"}),"The southern training area seems to " +
      "radiate powerful magic.\n");

   clone_object(OBJ + "normal_board")->move(this_object());
}

