inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("A large, central chamber");
   set_long("This place seems to be a central chamber in this cavern "+
      "system for small tunnels branch off in various directions, heading "+
      "towards smaller side chambers. From the tunnel in the west a thick cloud "+
      "of acrid smoke is pouring into this chamber. In the center of this "+
      "chamber is a ring of stones surrounding one large stone.\n");
   add_item(({"central chamber","chamber","cavern system","cavern"}),
      "A large, roughly oval area within one of the mountains of the Desertrise "+
      "range.\n");
   add_item(({"small tunnels","tunnels","tunnel"}),
      "Dark passages leading to the west, north, east and southeast.\n");
   add_item(({"small side chambers","small chambers","side chambers","chambers"}),
      "They must lie past the small tunnels leading from this central chamber.\n");
   add_item(({"thick cloud","acrid smoke","cloud","smoke"}),
      "It is dark grey in color and looks quite unhealthy, but thankfully "+
      "has risen high up towards the ceiling, where it is a good twenty "+
      "feet over your head.\n");
   add_item(({"ceiling","walls","wall"}),
      "The interior of this chamber is made of the same dark grey stone "+
      "that comprises the Desertrise range of mountains.\n");
   add_item(({"floor","ground"}),
      "The rough stone ground is warm to the touch, almost pleasantly so.\n");
   add_item(({"ring of stones","stones"}),
      "Several stones the size of watermelons, they have been arranged into a "+
      "rough circle around the large stone in the center of this chamber.\n");
   add_item(({"large stone"}),
      "A six foot wide chunk of rock that lies in the center of the chamber, its "+
      "top has been roughly flattened. Upon it lies a great red orb.\n");
   add_item(({"great red orb","great orb","red orb","orb"}),
      "A faintly shimmering sphere of light. The three foot wide sphere "+
      "is casting its red aura all throughout this chamber.\n");
   add_exit(CPASS(desert/mount/g1),"west");
   add_exit(CPASS(desert/mount/g3),"north");
   add_exit(CPASS(desert/mount/g4),"east");
   add_exit(CPASS(desert/mount/g5),"southeast");
}
void
init()
{
   ::init();
   AA(rub,rub);
}
int
rub(string str)
{
   if(!str || str != "orb")
      {
      NF("What ?\n");
      return 0;
   }
   write("You rub the surface of the orb...\n");
   say(QCTNAME(TP) + " rubs the surface of the orb...\n");
   set_alarm(3.0,0.0,"orb_effect");
   return 1;
}
void
orb_effect()
{
   int i;
   i = random(5);
   if (i < 1)
      {
      TP->catch_msg("An image of a snake the color of crystals forms "+
         "before you. The snake then vanishes beneath a ground of salt crystals.\n");
      return;
   }
   else
      if( i < 2)
      {
      TP->catch_msg("A sparkling fountain of water nearly fills your sight "+
         "with its magnificence. You watch as the water trickles through some "+
         "cracks within the ground and disappear into darkness.\n");
      return;
   }
   else
      if(i < 3)
      {
      TP->catch_msg("An old well situated among many luxuriously green "+
         "plants appears in your mind's eye, then disappears.\n");
      return;
   }
   else
      if(i < 4)
      {
      TP->catch_msg("A ruined tower suddenly appears before you, jutting "+
         "from a large sand dune. You watch as the wind lifts sand up the "+
         "side of the dune.\n");
      return;
   }
   else
      TP->catch_msg("A clear and completely still pool of water fills "+
      "your mind's eye, thick vegetation growing along its banks.\n");
   return;
}
