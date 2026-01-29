inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "camp.h"
#include "/d/Shire/orcmaker/orcmaker.h" 

object slave, slave1, paper, pen, shire_map;

void add_stuff()
{
  if(!slave)
  {
    slave=clone_object(ORCMAKER_DIR+"orcmaker");
    slave->set_power(20+random(11));
    slave->set_type(SLAVE);
    slave->move(TO);
  }
  if(!slave1)
  {
    slave1=clone_object(ORCMAKER_DIR+"orcmaker");
    slave1->set_power(35+random(16));
    slave1->set_type(SLAVE);
    slave1->set_random_move(23);
    slave1->set_restrain_path(({GREEN_DIR+"camp"}));
    slave1->move(TO);
    slave1->team_join(slave);
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
  set_long("Tents surround you to the north "+
   "mainly, but in all other directions as well. This place "+
   "seems to be a focal point for orc fires and comradeship. "+
   "There are many standards planted in the ground near the charred "+
   "center of this part of the camp, silent testimony to the "+
   "cruel natures of this camp's inhabitants.\n");

   add_item(({"campfire","camp fire","orc fire","charred center", "center"}),
   "The fire which burnt here must have been enormous. From its "+
   "magnitude, it is clear the orcs do not fear being discovered.\n");

  add_exit(GREEN_DIR + "camp/camp12","northwest",0);
  add_exit(GREEN_DIR + "camp/camp13","northeast",0);
  add_exit(GREEN_DIR + "camp/camp08","west",0);
  add_exit(GREEN_DIR + "camp/camp10","east",0);
  add_exit(GREEN_DIR + "camp/camp05","southeast",0);
  set_tent_name("tent09");
  enable_reset();
  add_stuff();
  
  STANDARDS;
}
void
enter_inv(object ob, object from)
{

   ::enter_inv(ob, from);
   //object paper, map;
   if(!interactive(ob)) { return; } /* he's got to be a player to do our quest */
   if(!ob->query_prop("_mapping_quest")) { return; } /* No props for those who
   don't want them */

   if(ob->query_prop("_mapping_quest") != 3) { return; } /* 3 is for camp09 */
   /* This must be the proper room, based on random assignment */

    if(!present("pen",ob)) { return; }
   if(!present("paper",ob)) { return; }
   /* Gotta have a pen to make any map */
   if(ob->query_skill(SS_AWARENESS) < 20 + random(25)) { return; }
   if(ob->query_skill(SS_LOC_SENSE) < 20 + random(25)) { return; }
   /* Need these skills to draw a proper map with the pen */
   if(ob->query_stat(4) < 20 + random(25)) { return; }
   if(ob->query_stat(5) < 20 + random(25)) { return; }
/* Here we require the player to have some int and wis :) */

    ob->catch_msg("You feel you have seen enough to draw a proper map.\n");
    ob->catch_msg("You sketch out a quick map on your piece of paper.\n");
    ob->catch_msg("You start to fear you may be caught if you don't leave soon.\n");
    ob->add_prop("_i_mapped_the_orc_camp",1);

    shire_map = clone_object(GREEN_DIR +"obj/map.c");
    shire_map->move(ob);  /* Give him the map */

    paper = present("paper",ob);
    paper->remove_object();   /* Take away the paper instead */

    return;

}
