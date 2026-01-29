// file name:    falling.c
// creator(s)    Ilyian (25 August, 1995)
// last update:  Lilith   July 2021   Added some exits in case the
//                                    player doesn't get moved out.
// purpose: This is the place where a player is when he is falling
// revisions: Lilith Apr 2022: fixed typo (duplicate "fills") and
//                added more randomization to exits.

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

void
create_room()
{
    set_short("falling through the ground");

    set_long("You can see nothing in the blackness all around, "
      +"oppressive and deeply distressing. "
      +"The scent of moist earth fills your nose, and you experience "
      +"the sensation of falling"
      +".\n");
    add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
      +"thick to");
    add_prop(ROOM_S_DARK_LONG, "Darkness presses upon you "
      +"from all directions. The scent of moist earth fills "
      +"your nose and you feel like you are falling.\n");

    // Swallowed by earth, the darkness is deep.
    add_prop(ROOM_I_LIGHT, -20);

    // In the event mortal doesn't get moved out of here
    // Lets give them some exits
    add_exit(CRYPT+"crypt"+(25+random(10)),"down", 0, 10, 0);	
    add_exit(CRYPT+"crypt"+(55+random(10)),"up", 0, 10, 1);
    add_exit(CRYPT+"crypt"+(75+random(10)),"out", 0, 10, 1);
    // Detour into cairn 
    add_exit(MARSH+"fell","in", 0, 10, 1);

}

void
move_along(object tp)
{
    if (!present(tp)) return;

    tp->catch_msg("You finally land with a painful "
      +"thud on a cold and damp stone floor somewhere "
      +"deep in the catacombs of Sybarus. OUCH!\n "
      +"Fear wells up from the depths of your being."
      +"\n");
    // just a little damage from the fall
    tp->heal_hp(-(tp->query_max_hp() / 12));
    tp->move_living("M", CRYPT+"crypt"+(1+random(15)));
    // rooms 1-15

}	


// If player is here for too long, move them along.
void 
enter_inv(object ob, object from)
{

    ::enter_inv(ob, from);

    if(!interactive(ob)) return;

    set_alarm(5.0, 0.0, &move_along(ob));

}
