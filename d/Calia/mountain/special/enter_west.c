/* Code for the west guard entrance, the one into the boulder at the
   roundabout near Gelan.

   Coded by Amelia.

   History:
         13/5/01       def updated                    Maniac
         14/6/96       typo corrected                 Maniac
          8/3/96       guard presence check           Maniac
          2/10/95      Bug corrected                  Maniac
          30.5.95      Modification                   Maniac
          23.5.95      Correction                     Maniac
          16.5.95      Team pulled in on door open    Maniac
*/


#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#define TP this_player()
#define ENTER_ROOM "/d/Calia/mountain/lower_tunnel/guard_room_W"
#include "check_out.c"


int
enter_door(string str)
{
        object r;

        ENTER_ROOM->load_me();
        r = find_object(ENTER_ROOM);

	if((str=="door") || (str=="on door") || (str == "on the door"))
		{
                if (!present("guard", r)) {
                    write("You knock on the door but nothing happens.\n");
                    say (QCTNAME(TP)+" knocks on the boulder...strange...\n");
                    return 1;
                }
		if(enter_check(TP))
		{
		write("You knock on the door.\n");
		say (QCTNAME(TP)+" knocks on the boulder...strange...\n");
		write ("You see a small slot open in the door.\n");
		write("An eye at the hole examines you closely.\n");
		set_alarmv(1.0, 0.0, "pulls_in", ({TP}));
		return 1;
		}
		else
		if(TP->query_skill(SS_AWARENESS)>45)
		{
		write("You knock on the door.\n");
		say(QCTNAME(TP)+" knocks on the boulder...strange...\n");
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
        QCTNAME(player)+" leaves into the boulder.\n", player);
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

    tell_room(environment(tp), "A door opens in the boulder.\n");
    move_in(tp);
    for (i = 0; i < sizeof(m_team); i++)
        move_in(m_team[i]);
}


string
boulder_desc()
{
	if((TP->query_skill(SS_AWARENESS)>45)||(is_calian(TP)))
	{
		return("This is an immense boulder, made apparently "+
		"of solid granite.  As you examine it closely, however, "+
		"you see that there are symmetric cracks on the west "+
		"side of it...that look like the outline of a "+
		"strange door. You could try to knock on it.\n");
	}
	/* else */
	return("The boulder is massive and immobile.  It has steep "+
		"sides, and you don't think you could climb it.\n");
}

