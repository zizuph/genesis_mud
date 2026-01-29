#define UP_ROOM 	EDORAS_DIR + "in_well5"

#define CREATEADD \
    add_exit(EDORAS_DIR + "in_well5","up","@@try_up"); \
    add_exit(EDORAS_DIR + "in_well5","down","@@fail_down"); \
    add_item(({"mud","ground","bottom"}),break_string("The bottom of the well is covered with mud, anything " + \
      "could be hidden there.\n",70)); \
    add_prop("_obj_s_search_fun","do_search");

#include "well.h"

object wellring;

do_search(object searcher, string str)
{
  int pldex;
  pldex = TP->query_stat(SS_DEX)/10;
  if(pldex > 8) pldex = 8;
  if(pldex < 1) pldex = 1;
  if(str != "ground" && str != "mud" && str != "bottom") return 0;
  if(TP->test_bit("Gondor",1,4) || (wellring && present(wellring, TP)))
  {
    return BS("Eeek! You feel around in the mud with your hands, but you do not find anything.\n");
  }
  if (!wellring || !present(wellring, TO))
  {
    if(random(10-pldex))
    {
      return BS("Eeek! You feel around in the mud with your hands, but you do not find anything. But "
        + "there's a lot of mud on the ground here. Whole treasure hoards could be "
        + "hidden here and still you would not find anything at the first try. \n");
    }
    wellring = clone_object(EDORAS_DIR + "obj/questring");
    wellring->move(TO);
    wellring->add_prop(OBJ_I_INVIS,1);
    return BS("Eeek! You feel around in the mud with your hands. Suddenly you "
      + "notice something small and hard. But probably it is just a stone. It "
      + "slips through your hands and is gone again. \n");
  }
  if(random(12-pldex))
  {
    return BS("Again you feel around in the mud, trying to find the small object "
      + "that slipped through your fingers. Perhaps it is valuable.\n");
  }
  wellring->move(TP);
  TP->add_prop("_found_ring_in_edoras_well",1);
  wellring->remove_prop(OBJ_I_INVIS);
  return BS("Again you feel around in the mud, and suddenly you find the small "
    + "object again. This time you quickly close your hand around it, so that "
    + "you do not lose it again.\n");
}  

fail_down()
{
  write(BS("You try to dive further down, but you are stopped by the bottom of "
    + "the well. You sink into the mud at the bottom, whirling it up and making "
    + "the water even darker and mustier.\n"));
  return 1;
}

