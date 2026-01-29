/*    pit.c - re-written by Jaypeg and Alaron
 *    28thJan97
 *    This is a deathtrap and part of the
 *    path to the vamp guild area, the Shrine
 *    of Darkness, surviving this room is part
 *    of an "entrance test" quest.
 */

inherit "/std/room";

#include <filter_funs.h>
#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"

int num_players;
int gag_id;

/*  write("\n\n\nTumbling and bouncing violently against "+
  "the walls, you land with a THUD!\n\n\n");  */

void gag_players();

void create_room()
{

    num_players = 0;

    set_short("In a dark pit");
    set_long( "   You have landed "+
      "in a dark pit. Your meager light source does little to "+
      "illuminate this dismal place of barren walls and floor "+
    "scratched out of black stone\n");


    add_prop( ROOM_I_LIGHT, 0 );
    add_prop( ROOM_I_INSIDE, 1 );

    add_item( ({"walls", "wall", "ceiling", "chimney"}),
      "Black stone walls of this pit surround you, and you can see "+
      "no way to escape. The rock chimney you fell down extends "+
      "far up into the ceiling, way beyond your reach, and the "+
      "walls provide no good hand or footholds for you climb your "+
      "way out.\n" );
    add_item( ({"floor", "ground"}),
      "The dirty floor beneath your feet feels rough and crudely "+
      "carved from the black rock from which it was formed. Taking "+
      "your light source down close to the surface doesn't help at "+
      "all in finding clues on how you might make free from here.\n "+
      "You're going to have to search a little harder to find a way "+
      "out.\n" );



    // this is only a temp. exit until I add the code for the exit. 
    add_exit( VAMP_KR_DIR + "cav1.c", "out", 0 );

}

/*	write( "\n\n\nYou notice the air "+
	"tastes...wrong.\n\nYou feel a great sense of urgency.\n\n ); */

void
enter_inv(object ob, object from)
{
    num_players++;
    if (num_players == 1)
	gag_id = set_alarm(30.0,30.0, gag_players);
    ::enter_inv(ob, from);
}

void
leave_inv(object ob, object to)
{
    num_players--;
    if (num_players == 0)
	remove_alarm(gag_id);
}

int
filter_undeads(object ob)
{
    if (ob->query_prop(LIVE_I_UNDEAD)==1)
	return 0;
    else 
	return 1;
}

void
gag_players()
{
    int i;
    int a;
    object *ppl;

    ppl = filter(FILTER_LIVE(all_inventory(TO)), filter_undeads);

    for (i=0; i<sizeof(ppl); i++)
    {
	ppl[i]->catch_msg("Your chest feels tight and you choke, struggling "+
	  "for air!!\n");
	tell_room(TO, QCTNAME(ppl[i])+" chokes, "+ppl[i]->query_possessive()+
	  " face turning various shades of red and blue.\n", ppl[i]);
	a = ppl[i]->query_base_stat(SS_CON) / 10;
	ppl[i]->set_stat_extra(SS_CON,-a);
	ppl[i]->heal_hp(- (ppl[i]->query_max_hp() / 10));
	ppl[i]->heal_hp(-50);
	ppl[i]->heal_hp(-50);
	if (ppl[i]->query_hp() < 1) ppl[i]->do_die(TO);
    }
}

