/* 
   Code for the south guard entrance, the one in the rock of the mountain
   next to the foothills. 

   Originally coded by Amelia, adapted by Maniac 8/3/96

*/
    

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define TP this_player()
#define ENTER_ROOM "/d/Calia/mountain/lower_tunnel/guard_room_S"
#include "check_out.c"


int
enter_door(string str)
{
        object r;

        ENTER_ROOM->load_me();
        r = find_object(ENTER_ROOM);

	if((str=="door")||(str=="on door") || (str == "on the door"))
		{
                if (!present("guard", r)) {
                  write("You knock on the door but nothing happens.\n");
                  say (QCTNAME(TP)+" knocks on the rock face...strange...\n");
                  return 1;
                }

		if(enter_check(TP))
		{
		write("You knock on the door.\n");
		write ("You see a small slot open in the door.\n");
		write("An eye at the hole examines you closely.\n");
                say (QCTNAME(TP)+" knocks on the rock face...strange...\n");
		set_alarmv(1.0, 0.0, "pulls_in", ({TP}));
		return 1;
		}
		else
		if(TP->query_skill(SS_AWARENESS)>45)
		{
		write("You knock on the door.\n");
		write("An eye appears at a peephole in the door.\n");
		write("It glares at you, and you feel uncomfortable.\n");
		write("The peephole closes with a snap!\n");
		return 1;
		}
		
		}
	/* else */
		notify_fail("Knock on what?\n");
		return 0;
}

void
move_in(object player)
{
    tell_room(this_object(),
        QCTNAME(player)+" leaves into the rock face.\n", player);
    player->catch_msg("A guard pulls you in.\n"); 
    player->move_living("M", ENTER_ROOM, 1);
    tell_room(environment(player), QCTNAME(player)+" arrives.\n", player);
}


void
pulls_in(object tp)
{
    int i;
    object *team, *m_team;

    if (environment(tp) != this_object())
        return;

    team = tp->query_team();

    m_team = ({ });
    for (i = 0; i < sizeof(team); i++)
        if ((environment(tp) == environment(team[i])) &&
            enter_check(team[i]))
            m_team += ({team[i]});

    tell_room(environment(tp), "A door opens in the rock face.\n");
    move_in(tp);
    for (i = 0; i < sizeof(m_team); i++)
        move_in(m_team[i]);
}


string
rock_face_desc()
{
	if((TP->query_skill(SS_AWARENESS)>45)||(is_calian(TP)))
		{
            return("As you look more closely, you see that part "+
		"of the rock face appears to be smoother than the " +
                "rest. Your perceptive gaze discerns the camouflaged "+
                "outline of a door, which you could try knocking on.\n");  
		}
	/* else */
       return("As you look more closely, you see that part "+
              "of the rock face appears to be smoother than the " +
              "rest.\n");
}


string
door_desc()
{
	if((TP->query_skill(SS_AWARENESS)>45)||(is_calian(TP)))
		{
         return ("Your perceptive gaze discerns the camouflaged "+
                "outline of a door in the rock face, which you could " +
                "try knocking on.\n");  
		}
	/* else */
       return("You find no door.\n");
}

