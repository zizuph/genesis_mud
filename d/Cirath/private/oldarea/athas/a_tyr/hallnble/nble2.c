/*  Nobel Hall Foyer 
    Renovation to the Nobel Tavern has taken place and we are going to 
    enjoy our brand spankin new Nobel Ballroom - a medival country
    club, if you will, for Tyr.
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPCS+"drabakk.c", 1, 7, ATH_PERSON+"rich_eat.c", 1);
}
void    
create_room()
{
   set_short("Nobel Hall Foyer");
   set_long("A small but over stated entry to the Nobel Hall, this room "
   + "has been filled with marble flooring, plush red carpets, gold candle "
   + "holders, golden picture frames and an extraordinary brass chandelier. "
   + "Stairs to the south lead to the second level, which can be seen from "
   + "from this area, seem to carry off into a ball room.\n");

   add_item(({"carpet","carpets","rugs","rugs","plush carpet","red carpet",
   "plush carpets","red carpets","plush red carpet","plush red carpets\n"}),
   "The warm red with plush hairs. It lines the room connecting each exit. "
   + "It seems to have been adhered to the floor lest some poor nobleman or "
   + "noblewoman trip and fall breaking a danty arm or leg.\n");
 

    INSIDE

   add_exit("/d/Cirath/athas/a_tyr/noble/noble/rd_ds_01","north",0,1);
    reset_room();
}
