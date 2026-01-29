inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
int coal_here;
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   DIRTY(2);
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within some mines close to Underhome");
   set_long("This excavation, made in the hard rock by hundreds "+
       "of dwarves for the purpose of extracting mineral substances as "+
       "ore, coal and even precious stones, has just two exits. "+
       "You can walk to the northwest and up a wooden ladder.\n");
   add_item("ladder","Its a normal wooden ladder.\n");
   add_item(({"rock","minerals","stones","ore","coal"}),
       "In the walls here you can see @@coal@@.\n");
   add_exit(CPASS(dwarf/mine/m14),"up",0,3);
   add_exit(CPASS(dwarf/mine/m12),"northwest",0,3);

   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}
reset_room()
{
   coal_here=0;
}
init()
{
   ::init();
   add_action("mine","mine");
}
coal()
{
   if(!coal_here)
     return "nothing except the hard rock";
   return "some layers of coal inside the hard rock";
}
mine(string str)
{
   object stop;
   notify_fail("Mine what?\n");
   if (!str || str!="coal") return 0;
   notify_fail("But there is no coal here!\n");
   if(!coal_here) return 0;
   notify_fail("Mine with what? You can't mine with your hands!\n");
   if((TP->query_weapon(W_BOTH))->query_name() != "pickaxe")
      return 0;
   write("You start to mine for coal.\n");
   say(QCTNAME(TP)+" starts to mine some coal.\n");
   stop=clone_object(CPASS(dwarf/obj/stun_mine));
   stop->set_stop_object(TO);
   return 1;
}
stop_mining()
{
   object coal;
   coal_here=0;
   coal=clone_object(CPASS(dwarf/obj/coal));
   coal->move(TO);
}