//-*-C++-*-
// file name:      cloud.c
// creator(s):     Sirra May 2003
// Purpose:			 Cloud follows player targetted with cloudsp.c and rains
//						  on them.
// last update:
// bug(s):         Has not been tested.
//
// to-do:          What happens when targetted player gets transported
//							somewhere. Will the cloud follow then?
//						 Time out the cloud (it wears away eventually)
//							Remember to remove LIVE_S_SOULEXTRA also.
//
// Notes:          Coded as object rather than creature, monster, npc.
//							Necessary to avoid a hansome cloud that is feeling
//							very well.

# pragma strict_types
# include <macros.h>
# include <stdproperties.h>
#include "/d/Krynn/guilds/wohs/guild.h";
#include "/d/Krynn/common/defs.h"

inherit "/std/object.c";
inherit "/std/act/domove.c";  //Test to see if set_follow command works.

int do_rain(int count);
int do_zap();
//int do_trans();

object TARGET;



//This function called from cloudsp.c
void
set_target(object tar)
{
	int count = 0;
	tar = TARGET;

	set_alarm(1.0, 200.0, do_rain(count));
	count++;

	return;
}


void
create_object()
{
	int count = 0;

	set_name("thundercloud");
	add_name("cloud");
	set_adj("black");
	set_long("This is a small black thundercloud. It looks like "
		 +"it's on a mission.\n");

	/*
	set_name("thundercloud");
	add_name("cloud");
	set_race_name("thundercloud");
	set_adj("black");
	set_gender(G_NEUTER);
	set_long("Nothing here.");
	//set_short("black thundercloud.");
	*/

	add_prop(OBJ_M_NO_ATTACK,
		"You try to kill a cloud. The world laughs at you.\n");
	add_prop(OBJ_M_NO_GET, 1);

	/*
	B O O M ! A thundercloud bursts overhead!

It begins to rain on you. Just on you.
	  */

	//set_mm_in(" booms overhead!");


}

//Arguements: count is set in create function.
//					count == 0 if this is first time raining on target.
int
do_rain(int count)
{
	int i;
	string name;

	name = TARGET->query_name();

	set_follow(name, 1);

	//It cannot rain if the target is not in the room with the cloud.
	if(environment(this_object()) != environment(TARGET))
			return 0;

	//First time player gets rained on.
	if(count == 0)
	{
		tell_room("Rain bursts from the thundercloud directly above "
			+QCTNAME(TARGET) +", drenching "+HIM(TARGET)+".\n", TARGET);

		TARGET->catch_msg("Rain bursts from the cloud directly "
			+"above your head, drenching you. Only you.\n");

		TARGET->add_prop(LIVE_S_SOULEXTRA, "soaked");

		return 1;
	}

	if(count > 0)
	{
		i = random(5);

		if(i<3)
		{
			tell_room("The thundercloud rains on "
				+QCTNAME(TARGET)+ ".\n", TARGET);

			TARGET->catch_msg("The thundercloud rains on you. Only you.\n");

			return 1;
		}
		return 1;
	}

}


/*
 * Masked:        No good times with a thundercloud over head. ;)
 * Function name: emote_hook
 * Description  : Whenever an emotion is performed on this NPC, or when it
 *                is performed on in the room in general, this function is
 *                called to let the NPC know about the emotion. This way we
 *                can avoid the usage of all those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverbs - the adverb used with the emotion, if there
 *                    was one. When an adverb is possible with the emotion,
 *                    this argument is either "" or it will contain the used
 *                    emotion, preceded by a " " (space). This way you can
 *                    use the adverb in your reaction if you please without
 *                    having to parse it further.
 */
public varargs void
emote_hook(string emote, object actor, string adverb = 0)
{

	string *offensive = ({"laugh", "giggle",
		"smile", "cheer", "sing", "hum", "dance" });

	if(actor != TARGET)
		return;

	if(member_array(emote, offensive) == -1)
		return;

	if(!interactive(actor))
		return;

	set_alarm(1.0, 0.0, &do_zap());

}

int
do_zap()
{
	int i;

	if(environment(this_object()) != environment(TARGET))
		return 0;

	i= random(3);

	if(i>0)
	{
		tell_room("A lightening bolt from the thundercloud "
			+"zaps "+QCTNAME(TARGET)+ "on the bottom!\n", TARGET);

		TARGET->catch_msg("A lightening bolt from the thundercloud "
			+"zaps you on the bottom!\n");
		return 1;
	}

	return 1;
}


/*
int
do_trans()
{
	if(environment(this_object()) != environment(TARGET))
	{
		this_object()->move_living(environment(TARGET));
		remove_alarm(trans_id);
		return 1;
	}

	return 0;
}
*/

void
init()
{
	 ::init();

	 write("say Hi and Goodbye?\n");

}

