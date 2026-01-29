inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"

object guard, paper, shire_map, pen;
void add_stuff()
{
  if(!guard)
  {
    guard=clone_object(ORCMAKER_DIR + "orcmaker");
    guard->set_power(85);
    guard->set_type(GUARD);
    guard->add_chat("I'll kill any fool who tries to pass.");
    guard->move(TO);
    tell_room(TO,CAP(LANG_ADDART(guard->query_nonmet_name())) +
      " steps out of the shadows.\n");
  }
}


void reset_room()
{
  add_stuff();
}


create_room()
{
  create_camproom();
  set_short("Within the camp");
  set_long("Tents surround you on all sides, providing shelter "+
    "for the inhabitants of this camp. A black tent is nearby "+
    "but no standard names its owner.\n");

  add_exit(GREEN_DIR + "camp/camp09","northwest",0);
  add_exit(GREEN_DIR + "camp/camp10","northeast",0);
  set_tent_name("tent05");
  
  remove_item("tent");
  add_item(({"tent","black tent"}),
    "This tent is unique amoung the others in that it is "+
    "constructed entirely of a canvas-like material, with no "+
    "visible seams, gaps, or holes.  The flap closes tightly "+
    "with the frame, blocking the view of the interior.\n");
  add_item("flap","Nope, still can't see past it.\n");

  enable_reset();
  add_stuff();
}


void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   

   if(!interactive(ob)) { return; } /* he's got to be a player to do our quest */
   if(!ob->query_prop("_mapping_quest")) { return; } /* No props for those who
   don't want them */

   if(ob->query_prop("_mapping_quest") != 1) { return; } /* 1 is for camp05 */
   /* This must be the proper room, based on random assignment */

    if(!present("pen",ob)) { return; }
   if(!present("paper",ob)) { return; }
   /* Gotta have a pen to make any map */
   if(ob->query_skill(SS_AWARENESS) < 20 + random(15)) { return; }
   if(ob->query_skill(SS_LOC_SENSE) < 20 + random(15)) { return; }
   /* Need these skills to draw a proper map with the pen */
   if(ob->query_stat(4) < 30 + random(15)) { return; }
   if(ob->query_stat(5) < 30 + random(15)) { return; }
/* Here we require the player to have some int and wis :) */

    ob->catch_msg("You feel you have seen enough to draw a proper map.\n");
    ob->catch_msg("You sketch out a quick map on your piece of paper.\n");
    ob->catch_msg("You start to fear you may be caught if you don't leave soon.\n");
    ob->add_prop("_i_mapped_the_orc_camp",1);

    shire_map = clone_object(GREEN_DIR + "obj/map.c");
    shire_map->move(ob);  /* Give him the map */

    paper = present("paper",ob);
    paper->remove_object();   /* Take away the paper instead */

    return;

}
