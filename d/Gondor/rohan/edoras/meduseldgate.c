inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>

#include "/d/Gondor/defs.h"

object hama, *mguard;

public int	gate();

create_room()
{
  set_short("You are at the crown of the hill, in front of the golden "
    + "hall Meduseld");
  set_long(BS("You are standing on a paved platform at the crown of the "+
	"hill in front of the golden hall Meduseld. " +
    	"From here you can see beyond the stream Snowbourn the green "+
	"fields of Rohan fading into distant grey. " +
    	"To the south and the west, you can see the White Mountains, "+
	"with the snow-toothed peak of the Irensaga, the black mass of "+
	"the Dwimorberg, and the Starkhorn to the south towering all "+
	"other peaks. \n"));
  add_exit(EDORAS_DIR + "meduseldstair","north",0,1);
  add_exit(EDORAS_DIR + "meduseldentry","south",gate,1);
  mguard = ({ });

  reset_room();
}

make_guard(int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    mguard+=({clone_object(EDORAS_DIR + "npc/mguard")});
    mguard[i]->arm_me();
    mguard[i]->move(TO);
    hama->team_join(mguard[i]);
    tell_room(TO,capitalize(LANG_ADDART(mguard[i]->query_nonmet_name())) 
	+ " arrives.\n");
  }
}

reset_room()
{
  if(!objectp(hama))
  {
    hama=clone_object(EDORAS_DIR + "npc/hama");
    hama->arm_me();
    hama->move(TO);
    set_alarm(2.0, 0.0, &make_guard(3));
  }
}

gate()
{
  int i;
  object *inv_list;
/*
  if(TP->query_wiz_level()) return 0;
*/
  inv_list = all_inventory(TP);
  for (i = 0; i < sizeof(inv_list); i++)
  {
    if(function_exists("create_weapon",inv_list[i]))
    {
      write("The great gates are closed.\n");
      return 1;
    }
  }
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx an 76-char line xxxxxxxxxxxxxxxxxxxxxxxxx*/
  write(BS("The guards lift the heavy bars of the doors and swing them "+
	"inwards grumbling on their great hinges. You enter.\n"));
  return 0;
}
