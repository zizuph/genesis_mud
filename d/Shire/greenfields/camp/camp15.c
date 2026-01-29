inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "camp.h"

object paper, shire_map, pen;

create_room()
{
  create_camproom();
  set_short("Within the camp");
   set_long("You seem to have come as far north as you can get in "+
   "this camp. "+
   "There is a large black tent to the north, and beyond it, the "+
   "trees take over. You can go back to the center of "+
   "the camp which lies to the south, or you can enter the tent.\n");
   add_item(({"trees","cliff","north tent"}),
   "The camp in which you are standing ends just on "+
   "the other side of the strange looking black tent you see to "+
   "the north.\n");

  add_exit(GREEN_DIR + "camp/camp13","south",0);
  set_tent_name("tent15");
}

void
enter_inv(object ob, object from)
{

   ::enter_inv(ob, from);
   //object paper, shire_map, pen;
   if(!interactive(ob)) { return; } /* he's got to be a player to do our quest */
   if(!ob->query_prop("_mapping_quest")) { return; } /* No props for those who
   don't want them */

   if(ob->query_prop("_mapping_quest") != 2) { return; } /* 2 is for camp15 */
   /* This must be the proper room, based on random assignment */

    if(!present("pen",ob)) { return; }
   if(!present("paper",ob)) { return; }
   /* Gotta have a pen to make any map */
   if(ob->query_skill(SS_AWARENESS) < 20 + random(5)) { return; }
   if(ob->query_skill(SS_LOC_SENSE) < 20 + random(5)) { return; }
   /* Need these skills to draw a proper map with the pen */
   if(ob->query_stat(4) < 20 + random(5)) { return; }
   if(ob->query_stat(5) < 20 + random(5)) { return; }
/* Here we require the player to have some int and wis :) */

    ob->catch_msg("You feel you have seen enough to draw a proper map.\n");
    ob->catch_msg("You sketch out a quick map on your piece of paper.\n");
    ob->catch_msg("You start to fear you may be caught if you don't leave soon.\n");
    ob->add_prop("_i_mapped_the_orc_camp",1);

    shire_map = clone_object(GREEN_DIR + "obj/map");
    shire_map->move(ob);  /* Give him the map */

    paper = present("paper",ob);
    paper->remove_object();   /* Take away the paper instead */

    return;

}
