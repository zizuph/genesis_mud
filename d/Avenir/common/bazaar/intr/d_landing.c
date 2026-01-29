// file name:    d_landing
// creator:      Ilyian, Sept 24, 1995
// last update:  Lilith, Sept 2021: Updated cks for ferry ride.
//               Lilith, Apr 2022: added prop for fishing.               
// purpose: This is where the barge to the 
//          Isle of the Dead lands.
// note:
// bug(s):
// to_do:

inherit "/std/room";
#include "/d/Avenir/common/ships/dead/deadship.h"

object ship;

void
create_room()
{
   set_short("landing");
   set_long("A long sturdy landing extends "
           +"out over the black water here. There "
           +"is a large post where a boat can tie "
           +"up, and to the south you can see "
           +"a quiet street.\n");
   AI(({"dock","landing","pier","ground","floor"}),
            "The pier is "
           +"made of sturdy wood, and seems to "
           +"be quite old.\n");
   AI(({"post","pole"}),"The pole is made of a "
           +"thick log, and marks around it show "
           +"that it is used to tie up a boat of "
           +"some sort.\n");
   AI(({"mark","marks"}),"They appear to have been "
           +"made by large ropes.\n");
   AI(({"water","sea","dark sea","ocean"}),"The vast "
           +"dark sea stretches out to the north into "
           +"blackness. It is calm and still, its "
           +"murky black surface undisturbed.\n");
   AI(({"street","road"}),"The quiet street runs to the "
           +"south.\n");
   AI(({"source","ceiling","cavern","cave"}),"The "
           +"great ceiling of Sybarus cavern "
           +"is high above. From it, you can make "
           +"out the dim gloaming of the Source.\n");

   add_prop("_live_i_can_fish", "brackish");
   HAS_WATER
   IN;       // Avenir is an undergound domain.
 
 
//   AE(BAZAAR + "extr/k_landing", "west", "@@block");
   AE(BAZAAR + "intr/d_str3", "south",0,1);
        ship = clone_object("/d/Avenir/common/ships/dead/ship");
        ship->move(TO,1);
        ship->start_ship();
        reset_room();

    add_prop(ROOM_I_NO_CLEANUP, 1);

}

reset_room()
{
}

mixed block()
{
  if(TP->query_wiz_level())
   {
    write("Ok, since you are a wiz.\n");
    return 0;
   }

  write("It is not yet open.\n");
   return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    //  If you're undead or you're wearing death mask you
    //  can board the ferry to the Necronisi. No coffin ride.	
    if (ob->query_prop(LIVE_I_UNDEAD))
        ob->add_prop(DEAD_ENABLE, 1);
    if (ob->query_prop("_Avenir_death_mask_wearer"))
        ob->add_prop(DEAD_ENABLE, 1);
	
}