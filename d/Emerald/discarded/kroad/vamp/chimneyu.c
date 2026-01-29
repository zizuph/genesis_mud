/*    chimneyu.c
 *    This is where the vampires move from one end of the
 *    rock chimney to another.
 */

inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


int flush_id;
int num_players;

void flush_players();

void create_room()
{

    num_players = 0;

    set_short("Floating through the rock chimney");
    set_long( "   Although not really able to see, you are aware of "+
      "of your surroundings as your non-corpreal form glides its way "+
      "between the narrow walls of the natural chimney. From the top "+
      "you sense the sting of the Emerald sun, and below, a darkness "+
      "of the deepest kind.\n\n" ); 

    add_prop( ROOM_I_LIGHT, 0 );
    add_prop(ROOM_I_INSIDE,1);

}

void
enter_inv(object ob, object from)
{
	flush_id = set_alarm(20.0, 0.0, flush_players);
    ::enter_inv(ob, from);
}

void
flush_players()
{
    int i;
    int sz;
    object *ppl;
    object ob;

    ppl = all_inventory(TO);
    sz = sizeof(ppl);

    for (i=0; i<sz; i++)
    {

        while (ob = present("vamp_paralysis_ob", ppl[i]))
            ob->remove_object();

	ppl[i]->catch_msg("Focusing carefully through the distraction "+
	  "of the encroaching sunlight as your body rises out of the "+
	  "chimney, you cause your mist form to coalesce its typical "+
	  "humanoid body.\n\n");
	ppl[i]->move_living("sliding slowly through the chimney",
	  "/d/Emerald/kroad/eroad5", 1, 0);
    }

}
