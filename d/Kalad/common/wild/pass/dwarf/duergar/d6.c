inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

object ob1;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("You are within an old ruin. Large blocks of granite that once "+
      "held up the stone-roof lies scattered around in a random order, "+
      "making it hard to walk in here. Still, you notice signs of life in "+
      "here. The odd gnawed bone, scraps of refuse and dry crumbles lies "+
      "next to broken weapons and torn-up clothes. Three large blocks has "+
      "been used to create some sort of a chair here with a large cloth "+
      "covering it. "+
      "You can only walk south from here, since the "+
      "other ways are closed off by the ruins.\n");
   add_item(({"chair","cloth"}),
      "The chair consists of one huge block of stone that function as a seat "+
      "and two put on the sides for the user to rest the arms. A dirty "+
      "cloth has been plased on it as a 'decoration'.\n");
   add_item(({"crumbles","refuse","bone","bones","rubble"}),
      "They lie scattered around in here along with the rubble of stone "+
      "that once was part of an impressive building.\n");
   add_item(({"block","blocks","stone blocks","roof","walls"}),
      "Most of the building has decayed into a rubble of broken stones, "+
      "but some of the walls still stand tall and seems to even hold up "+
      "a roof further east.\n");
   add_item(({"weapons","clothes","torn-up","broken weapons"}),
      "The weapons and clothes seems to have been fairly newly dropped, "+
      "but all look very useless.\n");
   add_item(({"building","buildings"}),
      "You are not really sure what this building once housed, but you "+
      "guess it once was some kind of temple.\n");

   add_exit(CPASS(dwarf/duergar/d5),"south");

   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ob1))
   {
      ob1 = clone_object(CPASS(dwarf/npc/duergar_chief));
      ob1 -> arm_me();
      ob1->move_living("M",TO);
      tell_room(TO,"An impressive duergar turns and stares at you from his "+
         "place in the stone-chair.\n");
      ob1->command("emote chuckles evilly.");
      ob1->command("emote grins: Welcom tah my Kingdom surface-dweller.");
   }
}
