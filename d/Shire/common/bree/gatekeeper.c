#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"

inherit "/d/Shire/room";
void add_stuff();
void reset_room()
{
   add_stuff();
}

create_room() {
    set_short("Gatekeeper's lodge");
   set_long("The gatekeeper's lodge is stationed here at the borders "+
   "of the Shire in order to keep peace within "+
   "that happy land. Inside, is the lodgings for "+
   "the gatekeeper as well as a place for posting "+
   "of traveller's advisories. A large river "+
   "is just to the west.\n");

    add_item("lodge", break_string(
   "The lodge is big enough to house the gatekeepers "+
   "and overnight guests in case of emergency. Perhaps "+
   "you should go in and read all about the traveller's "+
   "advisories posted inside?\n",70));


    add_exit(BREE_DIR + "bridge1", "east");
    add_exit(BREE_DIR + "bridge", "west");
   add_exit(BREE_DIR + "in_gatekeeper","in","@@check_npc@@");
   reset_room();
}

int
check_npc()
{
   if(TP->query_npc())
   return 1;

  return 0;
}
void
add_stuff()
{
   object bessie, farmer;

   if(!find_living("_bessie_the_shire_cow"))
   {
   bessie = clone_object("/d/Shire/common/eastroad/npc/cow");
   }

   if(!find_living("_bibble_"))
   {
   farmer = clone_object("/d/Shire/common/eastroad/npc/oldfarm");
   farmer->move(TO);
   bessie->move(TO);
   farmer->team_join(bessie);

   }


}
