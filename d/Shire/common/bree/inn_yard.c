#include "/d/Shire/common/defs.h";

inherit LIB_DIR + "rom";

void make_npcs();

void reset_room()
{
   make_npcs();
}
     object pony;

create_rom()
{
    set_short("Prancing Pony's inn yard");
    set_long(
	"You are standing in the Prancing Pony's inn yard. You see "+
	"now that the building surrounds you in all directions except "+
	"east, where you can see the Bree-Hill steeply rises. To the "+
	"south you have the stables, and to the north you have the "+
	"entrance.\n");

    add_item(({"stables"}),
	"Well, some day the great wizards of the Shire will code a "+
	"place for you to keep your horses, but for now, you'll have "+
	"to place them here.\n");

    add_exit(BREE_DIR + "inn", "north", 0);
    add_exit(BREE_DIR + "crossing", "west", 0);
    make_npcs();

}

void
make_npcs()
{
   if(!pony)
     {
      pony = clone_object(BREE_DIR + "npc/pony");
      pony->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(pony->query_nonmet_name()))+
      " comes trotting out of the stable.\n");
      }
}
init()
{
   ::init();
   add_action("do_ride","ride");
   add_action("do_ride","mount");
}

int
do_ride(string str)
{
  if (str != "pony")
     return 0;
   if (!pony)
     return 0;


   say(QCTNAME(TP)+ " mounts the little starving pony and rides "+
   "around the inn-yard in style, cheering.\n");
   write("You mount the pony and go riding off into the "+
     "sunset, or at least as far as he will take you, which ends "+
     "up being not out of the innyard.\n"+
     "You get off and thank the pony for the ride.\n");
     return 1;

}
