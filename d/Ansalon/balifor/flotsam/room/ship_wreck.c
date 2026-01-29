#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;

#define PLAYER_I_FOUND_WRECK  "_player_i_found_flotsam_wreck"
#define POTION "/d/Ansalon/goodlund/bloodsea/obj/swim_potion"

object chest,treasure;
int sand_searched = 0;

void
reset_flotsam_room()
{
    if(!objectp(chest))
    {
        chest = clone_object(FOBJ + "chest");
        chest->move(TO);
    }

    if(!P(treasure, chest))
    {
        treasure = clone_object(FOBJ + "webnet");
        treasure->move(chest,1);
        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }
    sand_searched = 0;
}

void
create_flotsam_room()
{
    setuid();
    seteuid(getuid());
    
   set_short("Within the shipwreck");
   set_long("@@long_descr");
   
   add_item("shelf","The wooden shelf is empty, with what it " +
      "once held long ago being washed away. \n");
   add_item("door","The shattered wooden door lies at your feet " +
      "in pieces, probably broken by the great rock during a storm.\n");
   add_item("rock","A great rock rises through the opening of " +
      "what was once the cabins entrance, completely blocking it. " +
      "Its tip breaks through the cabins ceiling. \n");
   add_item("ceiling","The low wooden ceiling has been pierced " +
      "by the rock, leaving a hole in the ceiling large enough to " +
      "allow light in, but too small to crawl through. \n");
   add_item("sand","Sand covers much of the cabins wooden floor.\n");
   add_item("hole","A hole in the side of the cabin leads back to " +
      "the rough waters of the Blood Bay. Occasionally a wave crashes " +
      "against the side of the vessel, filling the cabin with water. \n");
   add_item("second hole","About the size of your fist, this hole " +
      "allows light into the wreck. \n");
   
   add_cmd_item("hole","enter","@@enter_hole");
   
   set_tell_time(45);
   add_tell("The shipwreck creaks " +
      "ominously at the extra weight inside the cabin. You " +
      "are not sure, but you think the vessel tilted slightly...\n"); 
   
   add_search(({"sand"}), 2, "search_sand", 1);

   reset_flotsam_room();
}

string search_sand()
{
  string find_string = "";

  if(sand_searched)
  {
    find_string = "You search through the sand but find nothing of interest.\n";
  }
  else 
  {
    find_string = "You find a couple of potions probably fallen off the shelf.\n";
    clone_object(POTION)->move(this_player(), 1);
    clone_object(POTION)->move(this_player(), 1);
    sand_searched = 1;
  }
  return find_string;
}

string
long_descr()
{
   return "You stand within the cabin of the shipwrecked " +
   "fishing vessel. As you enter through the hole in its " +
   "side you notice the whole vessel shift... not a good " +
   "sign if you plan to remain here for any period. Much " +
   "of the cabin lies in ruins, or buried under wet sand. " +
   "A makeshift shelf still holds precariously to the wall " +
   "of the cabin. " +
   "The door to the cabin lies shattered at your feet, " +
   "and in its place the side of a rock passes through its " +
   "opening and through the ceiling. " +
   "\n";
}

string
enter_hole()
{
   write("You dive back into the rough waters of the " +
      "Blood Bay.\n");
   TP->move_living("through the hole",
      FROOM + "bay2",1,0);
   return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob))
        return;

    if (interactive(ob))
        start_room_tells();

    if (ob->query_prop(PLAYER_I_FOUND_WRECK))
        return;

    ob->add_prop(PLAYER_I_FOUND_WRECK, 1);

}
