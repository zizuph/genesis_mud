/* Installed by Glykron 

   Updated by Maniac 18.1.96 
*/

#pragma save_binary

inherit "/std/room";

create_room()
{
 set_short("Calia domain entrance");
 set_long("This is the domain entrance to the land of Calia. " +
          "To the north you will find Centre Point Calia, which " +
          "contains many useful gateways. To the south is " +
          "the Tower of Domains.\n");
 add_exit("/d/Genesis/wiz/dom_a2", "south", 0);
 add_exit("/d/Calia/workroom", "north", 0);
}
