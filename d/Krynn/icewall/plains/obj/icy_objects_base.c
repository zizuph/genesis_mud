/* created by Macker 06/29/94 */
/* Added feature to stop the melt with specific warfare items 
 * Arman 23-Feb-2019 */

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/warfare/warfare.h"

#define SHADOW "/d/Krynn/icewall/plains/obj/wet_shadow.c"
#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"

/* prototype */
void melt(object room, object person);

void
make_me_meltable()
{
    set_alarm(itof(150 + random(250)), 0.0, "do_i_melt");
}

void
do_i_melt()
{
    object room = TO;
    object person = TO;
    while(E(room))
      room = E(room);
    if(E(TO) != room)
      while(person && !(interactive(person)))
	person = E(person);
    if(room && file_name(room))
      if(file_name(room)[0..16] != "/d/Krynn/icewall/")
	melt(room, person);
      else
	set_alarm(itof(150 + random(250)), 0.0, "do_i_melt");
    return;
}

void
add_wet_shadow(object person)
{
    object shadow;
    seteuid(getuid(TO));
    shadow = clone_object(SHADOW);
    shadow->shadow_me(person);
    shadow->destruct_wet_shadow();
}

void
melt(object room, object person)
{
    object melter;
    melter = TO;
    string glove_desc, warfare_gem_id, warfare_gem_short;

    if(E(TO) == person)
    {
        // melt halted if in LD room
        if(person->query_prop(PLAYER_S_LD_IN_ROOM))
        {
            set_alarm(itof(150 + random(250)), 0.0, "do_i_melt");
            return;
        }

        warfare_gem_id = person->query_armour(A_HANDS)->query_crystal_id_one();

	if((warfare_gem_id == "_cold_resistance_crystal") || 
           (warfare_gem_id == "_greater_cold_resistance_crystal"))
	{
            if(TO->query_wielded())
            {
                glove_desc = person->query_armour(A_ARMS)->short();
                warfare_gem_short = MASTERWORK_GEM_PROPS[warfare_gem_id][3];

	        person->catch_msg("The " +warfare_gem_short+ " embedded in your " + 
                    glove_desc + " radiates a sudden, arctic chill, hardening " +
                    "your " +TO->short()+ ".\n");
	        tell_room(room, "The " +warfare_gem_short+ " on " +QCTPNAME(person) + 
                    " " +glove_desc+ " radiates a sudden, arctic chill, hardening " +
                    HIS(person)+ " " +TO->short()+ ".\n", ({person}));

                set_alarm(itof(150 + random(250)), 0.0, "do_i_melt");
                return;
            }
	}

	person->catch_msg("Your " + TO->short() + " melts away, "
	    + "leaving you soaking wet.\n");
	tell_room(room, QCTNAME(person) + " suddenly looks all wet.\n", 
            ({person}));

    }
    else if(E(TO) == room)
    {
	tell_room(room, "The " + TO->short() + " melts away "
		  + "in the heat.\n");
    }
    else
    {
	person->catch_msg("You see water dripping from your " +
			      E(TO)->short() + ".\n");
	if (person)
	   tell_room(room, QCTNAME(person) + " suddenly looks all wet.\n", 
               ({person}));
    }

    if (person)
      add_wet_shadow(person);

    melter->remove_object();
}

