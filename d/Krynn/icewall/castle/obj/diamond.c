/* a diamond coded for Icewall by Stevenson */

#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
inherit "/std/object";
	inherit PLAINS_O + "icy_objects_base";

create_object() {
   set_name("ice");
   set_short("piece of ice");
   set_long("This is a very dazzling piece of ice. So dazzling in fact that "
      + "you wonder if it isn't something more valuable.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 175);
   add_prop(OBJ_I_VOLUME, 70);
	make_me_meltable();
}

/* The below function is redefined so that wen the ice melts
	off, the diamond is exposed. */
void
melt(object room, object person)
{
    object melter;
    melter = TO;
    if(E(TO) == person){
        person->catch_msg("The piece of ice you were carrying begins " +
	"to melt.......\nThe layer of ice melts away and discover that " +
	"what you thought was a simple chunk of ice is actually a rather " +
	"large diamond!\n");
        tell_room(room, QCTNAME(person) + " suddenly gets a surprised " +
	"look on " + TP->query_possessive() + " face as " + 
	TP->query_pronoun() + " examines something in " +
	TP->query_possessive() + " inventory.\n",({person}));
    }
    else
      if(E(TO) == room)
        tell_room(room, "A layer of ice melts off the piece of ice " +
		"revealing that it is in fact a rather large diamond!.\n");
      else
        {
            person->catch_msg("You see water dripping from your " +
                              E(TO)->query_short() + ".\n");
        }
	set_name("diamond");
	set_short("diamond");
	set_long("This is a very dazzling diamond. It seems to be wet and cold.\n");
	add_prop(OBJ_I_VALUE, 500);
	add_prop(OBJ_I_WEIGHT, 170);
	add_prop(OBJ_I_VOLUME, 65);

}

