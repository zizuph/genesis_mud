inherit "/d/Shire/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

#define ADDED_TIME 75
int ok_to_soak = 2;

create_room()
{
  set_short("A small storage room");
  set_long("This is where the smith stores all the wastes from "+
    "his daily workings. There are a few barrels stacked in the "+
    "far corner, and some piles of filings and other bits of "+
    "useless metals. This part of the building is constructed of "+
    "heavy timber beams and thick wooden planks. A single doorway "+
    "leads back into the smithy proper.\n");

  add_exit(HOBBIT_DIR + "forge","northeast");
  add_prop(ROOM_I_INSIDE,1);

  add_item(({"waste oil","oil"}),"The oil is very thick and black, "+
    "obviously left over from some sort of process the "+
    "smith uses.\n");
  add_item(({"plank","planks","beam","beams"}),"All the wood forming "+
    "this room looks as if it was recently involved in a fire, "+
    "and is still covered in soot and burn marks.\n");
  add_item(({"barrel","barrels","barrels of oil","barrel of oil"}),
    "@@barrels_long_desc@@");
  add_item(({"piles","pile","metals","useless metals","bits","filings"}),
    "These piles are really just the dumpings of scraps leftover "+
    "from the workings of the forge. Most of the bits are rusted "+
    "or are in the process of rusting.\n");
}


string barrels_long_desc()
{
  switch(ok_to_soak)
  {
    case 0:
      return "The barrels are coated on the inside with a thin "+
      "residue leftover from the waste oil that is no longer being "+
      "stored in them.\n";
      break;
    case 1:
      return "The barrels contain a small amount of waste oil "+
      "left over from the forge's operation.\n";
      break;
    case 2:
      return "Quite a bit of waste oil fills the barrels, the "+
      "forge must be in high demand these days.\n";
      break;
  }
}
 

init()
{
  add_action("do_soak","soak");
  ::init();
}


int torch_filter(object torch)
{
  if(torch->id("torch")) return 1;
  return 0;
}


int do_soak(string str)
{
  object torch, *arr;
  arr = all_inventory(TP);
  arr = filter(arr,"torch_filter",TO);
  if(!str) NFN0("Soak what, your head?");
  if(!parse_command(str,TP, " %o [in] 'barrel' / 'oil' ", torch))
  {
    NFN0("Soak what in where?");
  }

  if(torch->query_prop(OBJ_I_HAS_FIRE))
  {
    WRITEN("You stick the burning torch into the barrel of "+
      "oil, catching it, and yourself, on fire briefly.");
    SAY(" catches the barrel of oil on fire when "+HE_SHE(TP)+  
      "sticks a burning torch into it.");
    TP->add_hp(-(TP->query_max_hp()/10));
    ok_to_soak = 0;
    return 1;
  }

  torch->set_burn_time(torch->query_time_left() + ADDED_TIME +
    random(16));
  --ok_to_soak;
  WRITEN("You soak the torch in the oil for a while, then retrieve it.");
  SAY(" soaks a torch in the barrel of oil.");
  set_alarm(itof(ADDED_TIME * 2),0.0,"get_soaked_again");
}


get_soaked_again()
{
  if(ok_to_soak < 2)
  {
    say("The smith bustles into the room, pours a bucket of "+
      "excess oil into a barrel, and quickly returns to his forge.\n");
    ++ok_to_soak;
  }
}
