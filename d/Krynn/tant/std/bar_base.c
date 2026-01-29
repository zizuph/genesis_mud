/* Bar base file for Tantallon.
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
create_bar()
{
   
}

nomask void
create_tant_room()
{
   set_short("In a bar in Tantallon");
   set_long("You have entered a bar in Tantallon, where they serve many " +
       "different kinds of alcohol. Many stains can be seen on the floor. ");
   
   AI(({"ceiling","walls"}),"The ceiling and walls are both made of an aged " +
       "hardwood.\n");
   AI("wall","It is made of an aged hardwood.\n");
   AI(({"hardwood","aged hardwood"}),"The aged hardwood is probably " +
       "poplar.\n");
   AI("floor","The floor of the bar is covered with peculiar stains.\n");
   AI(({"peculiar stains","stains"}),"Curious, aren't you? They are " +
       "definitely stains caused by becoming sick after imbibing copious " +
       "amounts of alcohol.\n");
   AI("stain","They come in all shapes and odours, and nauseate you so that " +
       "you can't look at a particular one.\n");

   INSIDE;
   
   create_bar();
   reset_room();
   
}

init()
{
    add_action("do_puke", "barf");
    add_action("do_puke", "puke");
    ::init();
}

int do_puke(string str)
{
    if ((str=="on floor")||(str=="floor")||(str=="here"))
    {
        write("You puke on the floor, adding another stain to it.\n");
        say(QCTNAME(TP) + " pukes on the floor, adding yet another " +
            "stain.\n");
        return 1;
    }
}
