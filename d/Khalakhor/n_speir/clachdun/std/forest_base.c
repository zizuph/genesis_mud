#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h";
#include "local.h"

inherit CLACHDUN;
inherit STDHERBSEARCH;

#define WARNING     "_clachdun_forest_i_was_warned"

// Prototypes
void set_up_cords();

// Varables
static mapping opposite_dir = ([
  "north" : "south",
  "northeast" : "southwest",
  "east" : "west",
  "southeast" : "northwest",
  "south" : "north",
  "southwest" : "northeast",
  "west" : "east",
  "northwest" : "southeast",
]);



void create_forest() {}

nomask void
create_clachdun()
{
    set_up_cords();
    set_short("within a dense forest nearby Clach Dun");

    add_prop(ROOM_I_INSIDE, 0);
    set_terrain(TERRAIN_CONIFEROUS);

    add_item(({"trail", "trails", "path", "paths"}),
      "A number of paths are scattered about the forest. "+
      "Most of them lead no where.  An expert woodsman might be "+
      "able to study these trails and navigate them.\n");

    set_no_exit_msg("all", "The forest growth seems to dense to "+
      "travel that way.");
    create_forest();
    add_std_herbs(5, 7, file_size(file_name(TO)));
}

void
set_up_cords()
{
    sscanf(file_name(this_object()),
      FOREST_DIR + "forest_%d_%d", gX, gY);
}

void
move_random_dir(string dir, object player)
{
    string where = one_of_list(TO->query_exit_rooms());
    object *team = player->query_team();
    int size , i;


    player->move_living(dir, where, 1);
    size = sizeof(team);
    if (size)
    {
	i = -1;
	while(++i < size)
	{
	    if (ENV(team[i]) == player->query_prop(LIVE_O_LAST_ROOM))
	    {
		team[i]->move_living(dir, where, 1);
	    }
	}
    }
}

void
move_everyone(string dir, object player)
{
    string *cmds = TO->query_exit_cmds(), where;
    int i, size;
    object *team = player->query_team();

    i = -1;
    while(++i < sizeof(cmds))
    {
	if (cmds[i] == dir)
	{
	    where = TO->query_exit_rooms()[i];
	}
    }
    player->move_living(dir, where, 1);
    size = sizeof(team);
    i = -1;
    while(++i < size)
    {
	if (ENV(team[i]) == player->query_prop(LIVE_O_LAST_ROOM))
	{
	    team[i]->move_living(dir, where, 1);
	}
    }
}

int
complicate_movement()
{
    int skill;
    object player;

    player = this_player();


    // Don't bother wizards or npcs with this test
    if (player->query_wiz_level() || player->query_npc())
	return 0;

    // We can always go back the way we came
    if (query_verb() == opposite_dir[player->query_prop(LIVE_S_LAST_MOVE)])
    {
	move_everyone(query_verb(), player);
	return 1;
    }



    skill = player->query_skill(SS_LOC_SENSE) +
    (player->query_stat(SS_WIS) / 10);
    if (skill < 0)
	skill = 0;

    if (skill <= 20 && (player->query_prop(WARNING) < 2))
    {
	player->catch_tell("The forest paths look extremely grown "+
	  "over and dense.  You could get lost "+
	  "within the shadowy forest with "+
	  "such a low awareness of your location.\n");
	player->add_prop(WARNING, player->query_prop(WARNING) + 1);
	return 1;
    }

    switch(skill)
    {
    case 0..20:
	/* player might get lucky and go the right way. */
	if (!random(5))
	{
	    move_everyone(query_verb(), player);
	    return 1;
	}

	/* Now pick a direction and move the player around
	 * randomly (grin)
	 */
	move_random_dir(query_verb(), player);
	return 1;
    case 31..60:
	/* player might get unlucky ;) */
	if (random(7))
	{
	    move_everyone(query_verb(), player);
	    return 1;
	}

	/* Now pick a direction and move the player around
	 * randomly (grin)
	 */
	move_random_dir(query_verb(), player);
	return 1;
    default:
	move_everyone(query_verb(), player);
	return 1;
    }

}

void
add_forest_exit(string place, string cmd)
{
    add_exit(place, cmd, complicate_movement, 1, 1);
}


int
study_trail(string str)
{
    int skill;
    string *exit_cmds;

    notify_fail("Study what?  You could study the trails or "+
      "the paths here to try and figure out where "+
      "to go.\n");
    if (str != "path" && str != "paths" && str != "trail" &&
      str != "trails")
	return 0;

    skill = TP->query_skill(SS_LOC_SENSE) +
    (TP->query_stat(SS_WIS) / 10);
    exit_cmds = TO->query_exit_cmds();
    notify_fail("Mmm there are no exits here to study.\n");
    if (!sizeof(exit_cmds))
	return 0;

    // should never happen but I'm paranoid anyways ;)
    if (skill < 0)
	skill = 0;

    switch(skill)
    {
    case 0..20:
	write("With your limited sense of direction "+
	  "you look around the trail trying to find "+
	  "a possible way through this dense forest.  "+
	  "You can only see an opening in the forest "+
	  "which leads you "+
	  opposite_dir[TP->query_prop(LIVE_S_LAST_MOVE)] +
	  ", back towards the way you came.\n");

	break;
    case 21..60:
	// If you have more than 2 exits available you
	// won't find all of them
	while (sizeof(exit_cmds) > 2)
	{
	    exit_cmds -= ({one_of_list(exit_cmds, str2val(OB_NUM(TP)))});
	}
	write("With your sense of direction you take "+
	  "a close look at the trail attempting to "+
	  "figure out where the path leads.  After a short "+
	  "while you figure you can move "+COMPOSITE_WORDS(exit_cmds)+
	  " along the path.\n");
	break;
    default:
	write("With your expert sense of direction you quickly "+
	  "determine that the path leads "+
	  COMPOSITE_WORDS(exit_cmds)+ " from this area.\n");

	break;
    }
    return 1;
}


void
init()
{
    ::init();
    add_action(study_trail, "study");
}


