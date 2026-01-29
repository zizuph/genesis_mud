/* 
   Workroom.c 
   ----------

   Coded ........: 94/12/19
   By ...........: Jeremiah

   Latest update : 95/09/25
   By ...........: Jeremiah

*/


#include "/d/Krynn/common/defs.h"

#include <stdproperties.h>
#include <macros.h>

inherit "/std/workroom";
inherit "/std/act/trigaction";

int staff, fire, light_intens;


void load_poly()
{
   if(!P("poly",TO))
      clone_object("/d/Krynn/jeremiah/polyphant")->move(TO);
}


void
create_workroom()
{
    staff = 0;        /* 0 = no light from staff, 1 = light from staff */
    fire = 0;         /* 0 = fire is out,         1 = fire is on       */
    light_intens = 1; /* light intensity from rooms light sources */

    set_short("Jeremiah's workroom");
    set_long("You are standing in the south end of a large vaguely lit room. " +
             "The floor, the walls and the ceiling are made of huge dark grey " +
             "pieces of rock. The rocks are perfectly fitted together and only " +
             "the vague rounding of the stones and an occasional crack reveals " +
             "that the room is not carved out of one piece of solid rock. The " +
             "walls and the ceiling have been given a coat of whitewash, " +
             "removing the otherwise gloomy appearance of this room. A fire, " +
             "burning inside a large fireplace built into the eastern wall, " + 
             "throws eerie shadows across the room. Through a window built " +
             "into the northern wall, an almost unnatural light flows onto the " + 
             "ceiling as if the light source from which it comes is somewhere " +
             "below the location of this place.\n");

 
    add_prop(ROOM_I_LIGHT,light_intens);

    load_poly();
}
