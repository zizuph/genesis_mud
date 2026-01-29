/*
   Wayreth.

   laboratory.c
   ------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 96/11/28
   By ...........: Teth

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;

object    moroth;

void
reset_tower_room()
{
    if (moroth)
      return;
    moroth = clone_object("/d/Krynn/wayreth/npc/walk_black.c");
    moroth->move_living("xx",TO);
    moroth->seq_new("do_thing");
    moroth->seq_addfirst("do_thing","@@start_patrol");
}

void
create_tower_room()
{
   set_short("Laboratory at the top of the Tower");
   set_long("This is the laboratory that is shared by each of " +
      "the three Orders of Magi. Arcane experiments are conducted " +
      "in this lab, and this is obvious by the amount of glassware " +
      "and other materials present on the various tables. A dank " +
      "smell hangs in the air, but it is still possible to breathe " +
      "without harm. Stairs can be seen to the east. This area " +
      "is used by some wizards as a place to discuss alchemy.\n");

   AI("floor","The floor is composed of the same polished obsidian " +
      "as the walls. There is a hole in the floor, possibly a " +
      "drain, near the northwestern edge of the room.\n");
   AI(({"drain","hole","hole in the floor"}),"This drain is " +
      "used to magically teleport away any leakages or spillages " +
      "of fluids from this room. It's small holes ensure that only " +
      "liquids can be moved through.\n");
   AI(({"wall","walls"}),"The walls of this room are composed " +
      "of polished obsidian, with a magical enchantment placed " +
      "on them to prevent damage from any possible explosions " +
      "that may be caused in this room.\n");
   AI("ceiling","The ceiling in this room angles upwards to a " +
      "point, as this is the top level in the tower. There doesn't " +
      "appear to be anything special about it, other than a humming " +
      "noise that is emitted every so often.\n");
   AI(({"various tables","tables"}),"These tables are made of a " +
      "flat grey stone, magically impervious to damage by " +
      "the fact that they are near perfect.\n");
   AI(({"glass","glassware"}),"Glassware of all sorts is scattered " +
      "throughout the room, mostly on the tables. Some of the " +
      "glass containers even contain liquids, labelled 'Do not " +
      "touch'.\n");
   add_item(({"materials","other materials"}),"The other materials " +
      "include tubing, ceramics, burners and the like.\n");
   add_item("tubing","This is rubber tubing, used to connect " +
      "glassware.\n");
   add_item("ceramics","These are used as a shield against the " +
      "fire, allowing a more even distribution of heat.\n");
   add_item("burners","Small flames can be controlled with these, " +
      "and used to heat elixirs.\n");
   AI(({"smell","dank smell"}),"The smell of the area reminds " +
      "you of rotten eggs. It has a sulfurish tinge to it.\n");

   set_tell_time(180);
   add_tell("A faint humming is emitted from the ceiling.\n");
   add_tell("The smell of chemicals hangs in the air.\n");
   add_tell("An open piece of glassware suddenly fizzes!\n");
   add_tell("Faint steps can be heard on the stairwell to the east.\n");
   add_tell("Pop-op-op-op gurgles a piece of glassware with liquid " +
      "inside it.\n");

   add_exit(WTOWER + "stairwell11", "east", 0);
   add_exit(WTOWER + "magicdiscuss", "down", 0);
}

public void
enter_inv (object ob, object from)
{
   ::enter_inv(ob, from);
   if (interactive(ob))
      start_room_tells();
    reset();
}
