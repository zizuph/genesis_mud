/* Castle base file for Tantallon.
* By Teth, Jan 17 , 1996
*/

#include "../local.h"
#include <macros.h>

inherit INROOM; 

public void
reset_tant_room()
{
}

public void
create_castle()
{
   
}

nomask void
create_tant_room()
{
   set_short("In Castle Tantallon");
   set_long("You are in Castle Tantallon. The vandalized walls of the " +
       "castle surround you, and it is readily apparent that this castle " +
       "is only a shadow of its former self. The floor is stained with " +
       "blood. ");
   
   AI(({"ceiling","walls"}),"The ceiling and walls are composed of a grey " +
       "rock.\n");
   AI("wall","It is made of a grey rock.\n");
   AI(({"rock","grey rock"}),"The grey rock is granite.\n");
   AI("floor","The floor is granite, and it is covered with blood stains.\n");
   AI(({"peculiar stains","stains"}),"Curious, aren't you? They are " +
       "definitely stains caused by becoming sick after imbibing copious " +
       "amounts of alcohol.\n");
   AI("stain","They come in all shapes and odours, and nauseate you so that " +
       "you can't look at a particular one.\n");

   INSIDE;
   
   create_castle();
   reset_room();
   
}

