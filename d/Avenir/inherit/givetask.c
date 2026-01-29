/* -*-C++-*-
 * file name:     /d/Avenir/inherit/givetask.c
 * creator(s):    Sirra    Sept 15, 2002
 * purpose:       Inheritable component for NPCs
 *
 * note:
 *               	See below for list of functions/abilities
 *                and instructions for usage.
 * last update:
 * bug(s):
 * to-do:

This file groups quests by area and difficulty.

NPCs who inherit and call the appropriate check_group_* function,
will recommend a quest to the player that he has not done yet.

The quests recommended are prioritized by area and difficulty
	(organized into Groups 1, 2, 3, 4. See below).

The easiest quests in the same area as the NPC are recommended first.

Which quest within a group is recommended first, is random to prevent
player from being stuck on one quest.

Player can, however, get stuck in the easy groups. He must be finish
all easy quests before being recommended a difficult one.

NOTE: If player has done all of the easiest quests in the area BUT ONE,
		only an NPC in a different group (area) will recommend him a different
		quest to do.

		If player has done all the easiest quest in all the areas BUT ONE,
		all NPCS will recommend him to the same quest.
		Player must complete all of the easy quests before being *recommended*
		a difficult one.

NOTE: Bury Bones and the Gelan Toilet Quest are excluded from this file.

To Use this file in an NPC:

1). Decide what area the NPC that is inheriting this file is in.

2). Add the following code to the NPC's file:

	a). If it's in the port/utterdark/outpost area add the following
			code to your give_quest()

			check_group_one(this_player(), ({0,0,0,0}) );

	b). If it's in the bazaar/park/admin/dead/holm area add the following:

			check_group_two(this_player(), ({0,0,0,0}) );

	**NOTE: Never add check_group_three, or check_group_four


To Add a Quest to this File:
1). Determine what group it's in.
	Group 1: Easy -Port, Outpost, Utterdark
	Group 2: Easy -Bazaar, Park, Holm, Dead, Admin
	Group 3: Difficult -Port, Outpost, Utterdark
	Group 4: Difficult -Bazaar, Park, Holm, Dead, Admin

	**Difficult is anything a young player can't do, such as,
		killing, or maxing skills. It's also difficult if
		there is a real possibility of dieing.

2). In this inherited file, Add the global integer variable.
		(see Below for example of global variable)

3). In this inherited file, within check_group_* function,
	  add an new position into the Group_* array.

	  For Example: If you are adding a Group 1 quest.

	  int
	  check_group_one(object player)
	  {
		...

		Group_One = ({0, 0, 0, 0});

		<BECOMES>
		Group_One = ({0, 0, 0, 0, 0});


4). Within the check_group_* function,
		Fill that position in the array
		according to whether or not player has
		done the quest. (see below for example within code)

5). Within give_group_*_task function, add response of NPC.
		(see below for example within code).

*/
#include <macros.h>
#pragma strict_types;

inherit "/d/Avenir/inherit/quest";

#define WRITE_THIS_LOG(file, msg) \
	(write_file(file, ctime(time()) + " " + (msg)))

#define QUEST_FILE   "/d/Avenir/log/quest/givetask"

int check_group_one(object player, int *Completed_Groups);
int check_group_two(object player, int *Completed_Groups);
int check_group_three(object player, int *Completed_Groups);
int check_group_four(object player, int *Completed_Groups);

int give_group_one_task(object player, int *Group_One);
int give_group_two_task(object player, int *Group_Two);
int give_group_three_task(object player, int *Group_Three);
int give_group_four_task(object player, int *Group_Four);

int GROUP_ONE_FULL = 0;
int GROUP_TWO_FULL = 1;
int GROUP_THREE_FULL = 2;
int GROUP_FOUR_FULL = 3;

//Group 1: Easy -Port, Outpost, Utterdark
int HAT_QUEST=0;
int WATER_QUEST=1;
int TOMATO_QUEST=2;
int RAT_HUNT=3;
/*Add new Group 1 quest int here
Ex: int YOUR_VARIABLE = 4;
*/

//Group 2: Easy -Bazaar, Park, Holm, Dead, Admin
int JADESTONE_FLOWER_QUEST=0;
int PUSHER_QUEST=1;
int SONG_BOOK_QUEST=2;
int FISHERMAN_QUEST= 3;
int WOLF_QUEST=4;
int JADESTONE_LETTER_QUEST=5;
/*Add new Group 2 quest int here
Ex: int YOUR_VARIABLE = 6;
*/

//Group 3: Difficult -Port, Outpost, Utterdark
int ELVEN_GHOST_QUEST=0;
int MAGIC_SQUARE_QUEST=1;
/*Add new Group 3 quest int here
Ex: int YOUR_VARIABLE = 2;
*/

//Group 4: Difficult -Bazaar, Park, Holm, Dead, Admin
int FALCHION_QUEST=0;
int FAIRY_QUEST=1;
int JADESTONE_PLANS_QUEST=2;
int JADESTONE_NOCHIPA_QUEST=3;
/*Add new Group 4 quest int here
Ex: int YOUR_VARIABLE = 4;
*/

int
check_group_one(object player, int *Completed_Groups)
{
	int *Group_One;
	int sum = 0;
	int num =0;
	int i;

	//I hate that I have to do this.
	//Everytime a quest is added to group
	//Must add zero to this initialization.
	//*Sigh* There must be another way.
	Group_One = ({0, 0, 0, 0});

	if( player->test_bit("Avenir", 1, 0) )
		Group_One[HAT_QUEST] = 1;
	else
		Group_One[HAT_QUEST] = 0;

	if( player->test_bit("Avenir",0, 12) )
	  Group_One[WATER_QUEST] = 1;
	else
		Group_One[WATER_QUEST] = 0;

	if( player->test_bit("Avenir",0, 13) )
	  Group_One[TOMATO_QUEST] = 1;
	else
	  Group_One[TOMATO_QUEST] = 0;

	if( player->test_bit("Avenir",0, 3) )
	  Group_One[RAT_HUNT]=1;
	else
	  Group_One[RAT_HUNT]=0;

	//Example: Add Your Group One Quests Here
	/*if ( player->test_bit("Avenir", YOUR_QUEST_GROUP, YOUR_QUEST_BIT) )
		Group_One[YOUR_VARIABLE] = 1;
	else
		Group_One[YOUR_VARIABLE] = 0;
	*/

	num = sizeof(Group_One);

	//Add up the integers in Group_One
	for(i = 0; i <num; i++)
	{
		sum = sum + Group_One[i];
	}

	//Check to see if all quests in this group are done.
	if(sum == sizeof(Group_One) )
	{
		Completed_Groups[GROUP_ONE_FULL] = 1;

		if(!Completed_Groups[GROUP_TWO_FULL])
		{
			check_group_two(player, Completed_Groups);
			return 1;
		}

		if(!Completed_Groups[GROUP_THREE_FULL])
		{
			check_group_three(player, Completed_Groups);
			return 1;
		}

		if(!Completed_Groups[GROUP_FOUR_FULL])
		{
			check_group_four(player, Completed_Groups);
			return 1;
		}

		//all groups must be full.
		command("No, I have nothing for you.");
		return 1;
	}

	//The player still has quests to do in this group.
	give_group_one_task(player, Group_One);
	return 1;
}

int
check_group_two(object player, int *Completed_Groups)
{
	int *Group_Two;
	int sum = 0;
	int num =0;
	int i;

	//I hate that I have to do this.
	//Everytime a quest is added to group
	//Must add zero to this initialization.
	//*Sigh* There must be another way.
	Group_Two = ({ 0, 0, 0, 0, 0, 0 });

	if(  player->test_bit("Avenir", 0, 15) )
		Group_Two[JADESTONE_FLOWER_QUEST] = 1;
	else
		Group_Two[JADESTONE_FLOWER_QUEST] = 0;

	if(  player->test_bit("Avenir",0, 8) )
		Group_Two[PUSHER_QUEST] = 1;
	else
		Group_Two[PUSHER_QUEST] = 0;

	if(  player->test_bit("Avenir",0, 5) )
		Group_Two[SONG_BOOK_QUEST] = 1;
	else
		Group_Two[SONG_BOOK_QUEST] = 0;

	if(  player->test_bit("Avenir",0, 6) )
		Group_Two[FISHERMAN_QUEST] = 1;
	else
		Group_Two[FISHERMAN_QUEST] = 0;

	if(  player->test_bit("Avenir",0, 18) )
		Group_Two[WOLF_QUEST] = 1;
	else
		Group_Two[WOLF_QUEST] = 0;

	if( player->test_bit("Avenir",0, 7) )
	  Group_Two[JADESTONE_LETTER_QUEST]=1;
	else
	  Group_Two[JADESTONE_LETTER_QUEST]=0;

	//Example: Add Your Group Two Quests Here
	/*if ( player->test_bit("Avenir", YOUR_QUEST_GROUP, YOUR_QUEST_BIT) )
		Group_Two[YOUR_VARIABLE] = 1;
	else
		Group_Two[YOUR_VARIABLE] = 0;
	*/

	num = sizeof(Group_Two);

	//Add up the integers in Group_One
	for(i = 0; i <num; i++)
	{
		sum = sum + Group_Two[i];
	}

	//Check to see if all quests in this group are done.
	if(sum == sizeof(Group_Two))
	{
		Completed_Groups[GROUP_TWO_FULL] = 1;

		if(!Completed_Groups[GROUP_ONE_FULL])
		{
			check_group_one(player, Completed_Groups);
			return 1;
		}

		//The player is probably in the bazaar when asking
		//for another task. If the player has done all the
		//easy quests, give him a difficult one in the area
		//he is already in (most likely bazaar).
		if(!Completed_Groups[GROUP_FOUR_FULL])
		{
			check_group_four(player, Completed_Groups);
			return 1;
		}

		if(!Completed_Groups[GROUP_THREE_FULL])
		{
			check_group_three(player, Completed_Groups);
			return 1;
		}

		//all groups must be full.
		command("No, I have nothing for you.");
		return 1;
	}

	//The player still has quests to do in this group.
	give_group_two_task(player, Group_Two);
	return 1;
}

int
check_group_three(object player, int *Completed_Groups)
{
	int *Group_Three;
	int sum = 0;
	int num =0;
	int i;

	//I hate that I have to do this.
	//Everytime a quest is added to group
	//Must add zero to this initialization.
	//*Sigh* There must be another way.
	Group_Three = ({0, 0});

	if( player->test_bit("Avenir",0, 0) )
		Group_Three[ELVEN_GHOST_QUEST] = 1;
	else
		Group_Three[ELVEN_GHOST_QUEST] = 0;

	if( player->test_bit("Avenir",0, 2) )
		Group_Three[MAGIC_SQUARE_QUEST] = 1;
	else
		Group_Three[MAGIC_SQUARE_QUEST] = 0;

	//Example: Add Your Group Three Quests Here
	/*if ( player->test_bit("Avenir", YOUR_QUEST_GROUP, YOUR_QUEST_BIT) )
		Group_Three[YOUR_VARIABLE] = 1;
	else
		Group_Three[YOUR_VARIABLE] = 0;
	*/

	num = sizeof(Group_Three);

	//Add up the integers in Group_One
	for(i = 0; i <num; i++)
	{
		sum = sum + Group_Three[i];
	}

	//Check to see if all quests in this group are done.
	if(sum == sizeof(Group_Three))
	{
		Completed_Groups[GROUP_THREE_FULL] = 1;

		if(!Completed_Groups[GROUP_ONE_FULL])
		{
			check_group_one(player, Completed_Groups);
			return 1;
		}

		if(!Completed_Groups[GROUP_TWO_FULL])
		{
			check_group_two(player, Completed_Groups);
			return 1;
		}

		if(!Completed_Groups[GROUP_FOUR_FULL])
		{
			check_group_four(player, Completed_Groups);
			return 1;
		}

		//all groups must be full.
		command("No, I have nothing for you.");
		return 1;
	}

	//The player still has quests to do in this group.
	give_group_three_task(player, Group_Three);
	return 1;
}


int
check_group_four(object player, int *Completed_Groups)
{
	int *Group_Four;
	int sum = 0;
	int num =0;
	int i;

	//I hate that I have to do this.
	//Everytime a quest is added to group
	//Must add zero to this initialization.
	//*Sigh* There must be another way.
	Group_Four = ({0, 0, 0, 0});

	if( player->test_bit("Avenir",0, 19) )
		Group_Four[FALCHION_QUEST] = 1;
	else
		Group_Four[FALCHION_QUEST] = 0;

	if( player->test_bit("Avenir",0, 14) )
		Group_Four[FAIRY_QUEST] = 1;
	else
		Group_Four[FAIRY_QUEST] = 0;

	if( player->test_bit("Avenir",0, 9) )
		Group_Four[JADESTONE_PLANS_QUEST] = 1;
	else
		Group_Four[JADESTONE_PLANS_QUEST] = 0;

	if( player->test_bit("Avenir",0, 10) )
		Group_Four[JADESTONE_NOCHIPA_QUEST] = 1;
	else
		Group_Four[JADESTONE_NOCHIPA_QUEST] = 0;

	//Example: Add Your Group Four Quests Here
	/*if ( player->test_bit("Avenir", YOUR_QUEST_GROUP, YOUR_QUEST_BIT) )
		Group_Four[YOUR_VARIABLE] = 1;
	else
		Group_Four[YOUR_VARIABLE] = 0;
	*/

	num = sizeof(Group_Four);

	//Add up the integers in Group_One
	for(i = 0; i <num; i++)
	{
		sum = sum + Group_Four[i];
	}

	//Check to see if all quests in this group are done.
	if(sum == sizeof(Group_Four))
	{
		Completed_Groups[GROUP_FOUR_FULL] = 1;

		//The player is probably in the bazaar when asking
		//for another task. Give player easy task in the area
		//he is already in (most likely bazaar).
		if(!Completed_Groups[GROUP_TWO_FULL])
		{
			check_group_two(player, Completed_Groups);
			return 1;
		}

		if(!Completed_Groups[GROUP_ONE_FULL])
		{
			check_group_one(player, Completed_Groups);
			return 1;
		}

		if(!Completed_Groups[GROUP_THREE_FULL])
		{
			check_group_three(player, Completed_Groups);
			return 1;
		}

		//all groups must be full.
		command("No, I have nothing for you.");
		return 1;
	}

	//The player still has quests to do in this group.
	give_group_four_task(player, Group_Four);
	return 1;
}

int
give_group_one_task(object player, int *Group_One)
{
	int size = 0;
	int task = 0;

	size = sizeof(Group_One);

	//This Keeps NPC from giving out
	//the same quest over and over.
	//That would be frustrating
	//if player got stuck on one particular quest.
	task = random(size);

	//To DO: Check if Group_One is full.

	while(Group_One[task] != 0)
	{
		//start loop over again.
		if( (task+1) == sizeof(Group_One) )
			task = 0;
		else
			task++;
	}

	if(task == HAT_QUEST)
	{
	  //Hat Quest. Directs player from port to bazaar.
	  //GIVE THE RETURN HAT QUEST (Reward = 200, port)
	  command("say Someone told me Barkona at the Stormy Haven Pub "
			+"was having a bad day.");

	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Hat Quest.\n");

	  return 1;
	}

	if(task == WATER_QUEST)
	{
		//GIVE THE WATER QUEST (Reward = 150, Outpost)
		command("say The guards at the fort are brave. See if you can "
			+"help them out.");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Water Quest.\n");

		return 1;
	}

	if(task == TOMATO_QUEST)
	{
		//GIVE THE Tomato QUEST HERE (Reward = 1500, Outpost)
		command("say I saw Gritor around the fort earlier today. "
			+"He looked like he was up to something.");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Tomato Quest.\n");

		return 1;
	}

	if(task == RAT_HUNT)
	{
		//GIVE THE Rat Hunt QUEST HERE (Reward = 3750, Und)
		command("say I have heard rumours about ogre moms deep "
			+"in the Utterdark");
		command("shrug .");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Rat Hunt.\n");

		return 1;
	}

	//Example: Add Your Group 1 Response Here
	/*if(task == YOUR_VARIABLE)
	{
		//GIVE your QUEST HERE (Reward = ??, Area?)
		command("say Something witty.");
		return 1;
	} */

	//This should not happen.
	  WRITE_THIS_LOG(QUEST_FILE, "Failure to give_group_one_task.\n");
	write("Failed. Please Make a Bug Report about this NPC.\n");
	return 0;
}

int
give_group_two_task(object player, int *Group_Two)
{
	int size = 0;
	int task = 0;

	size = sizeof(Group_Two);

	//This Keeps all NPCS from giving out
	//the same quest. That would be frustrating
	//if player got stuck on one particular quest.
	task = random(size);

	//To DO: Check if Group_Two is full.

	while(Group_Two[task] != 0)
	{
		//start loop over again.
		if( (task+1) == sizeof(Group_Two) )
			task = 0;
		else
			task++;
	}

	if(task == JADESTONE_FLOWER_QUEST ||
			task == JADESTONE_LETTER_QUEST)
	{
		//GIVE THE FLOWER QUEST HERE (Reward = 500, bazaar)
		//Need "a little" herbalism skill.

		//Give the Jadestone Letter Quest here (Reward = 1500, bazaar & holm)
		//Kind of borderline difficult. Holm is dangerous. And noble hard to
		//find. But, no killing mandated.
		command("say Go find Jadestone doll.");
		command("say Now, stop bothering me.");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Jadestone Group two Quest.\n");

		return 1;
	}

	if(task == PUSHER_QUEST)
	{
		//GIVE THE ITCH QUEST HERE (reward 500, bazaar)
		command("say Maybe someone at Icky Bod's pub could use some help.");
      command("shrug .");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Itch Quest.\n");

		return 1;
	}

	if(task == SONG_BOOK_QUEST)
	{
		//GIVE THE  SONG OF SEER Book QUEST HERE (Reward = 1500, Bazaar)
		command("say I think the librarian was looking for someone earlier.");
		command("shrug unknown");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Song Book Quest.\n");
		return 1;
	}

	if(task == FISHERMAN_QUEST)
	{
		//GIVE THE FISH FOR FISHERMAN QUEST HERE (Reward = 1000, Bazaar)
		command("say Go patronize the fisherman in the bazaar!");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Fisherman Quest.\n");
		return 1;
	}

	if(task == WOLF_QUEST)
	{
		//GIVE THE WOLF QUEST HERE (reward = 1500, holm)
		command("I saw Prumwil with a strange bone today. "
			+"Ask him about it.");
		command("shrug");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Wolf Quest.\n");

		return 1;
	}

	//Example: Add Your Group 2 Response Here
	/*if(task == YOUR_VARIABLE)
	{
		//GIVE your QUEST HERE (Reward = ??, Area?)
		command("say Something witty.");
		return 1;
	} */

	//This should not happen.
	  WRITE_THIS_LOG(QUEST_FILE, "Give_Group_Two_Task Failed.\n");

	write("Failed. Please Make a Bug Report about this NPC.\n");
	return 0;
}

int
give_group_three_task(object player, int *Group_Three)
{
	int size = 0;
	int task = 0;

	size = sizeof(Group_Three);

	//This Keeps all NPCS from giving out
	//the same quest. That would be frustrating
	//if player got stuck on one particular quest.
	task = random(size);

	//To DO: Check if Group_One is full.

	while(Group_Three[task] != 0)
	{
		//start loop over again.
		if( (task+1) == sizeof(Group_Three) )
			task = 0;
		else
			task++;
	}

	if(task == ELVEN_GHOST_QUEST)
	{
		//GIVE THE Elven Ghost QUEST HERE (Reward = 20000, Und)
		//Must Kill stuff for this quest.
		command("whisper to "+player->query_real_name()+" Strange "
			+"things happen to those who haunt the ghosts in the Utterdark");
		command("shiver");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Elven Ghost Quest.\n");
		return 1;
	}

	if(task == MAGIC_SQUARE_QUEST)
	{
		//GIVE THE Magic Square QUEST HERE (Reward = 5000-30000, Und)
		//Need awareness and language skills. Chance to die.
		if( player->query_alignment() > -1)
		{
			command("say I am told there is an archaelogist "
				+"in the Utterdark. Perhaps he could "
				+"use your help.");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Evil Magic Square Quest.\n");

			return 1;
		}

		if( player->query_alignment() < 0)
		{
			command("say I have heard there is a gnome seeking "
				+"treasure in the Utterdark.");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Good Magic Square Quest.\n");

			return 1;
		}

	}

	//Example: Add Your Group 3 Response Here
	/*if(task == YOUR_VARIABLE)
	{
		//GIVE your QUEST HERE (Reward = ??, Area?)
		command("say Something witty.");
		return 1;
	} */

	//This should not happen.
	  WRITE_THIS_LOG(QUEST_FILE, "give_group_three_task Failed.\n");
	write("Failed. Please Make a Bug Report about this NPC.\n");
	return 0;
}

int
give_group_four_task(object player, int *Group_Four)
{
	int size = 0;
	int task = 0;

	size = sizeof(Group_Four);

	//This Keeps all NPCS from giving out
	//the same quest. That would be frustrating
	//if player got stuck on one particular quest.
	task = random(size);

	//To DO: Check if Group_One is full.

	while(Group_Four[task] != 0)
	{
		//start loop over again.
		if( (task+1) == sizeof(Group_Four) )
			task = 0;
		else
			task++;
	}

	if(task == FALCHION_QUEST)
	{
		//GIVE THE Runed Falchion QUEST HERE (Reward = 1500, holm)
		//impossible for an individual to obtain solo, as
		//the npcs are a good challenge even for a small team.
		command("say I've heard mysterious stories about the runed "
			+"falchions the shadow-elves carry.");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Falchion Quest.\n");

		return 1;
	}

	if(task == FAIRY_QUEST)
	{
		//GIVE THE Faerie QUEST HERE (Reward = 25000, Park)
		command("say I have heard wild tales about fairies in a glade.");
		command("shrug .");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Fairy Quest.\n");
		return 1;
	}

	if(task == JADESTONE_PLANS_QUEST || task == JADESTONE_NOCHIPA_QUEST)
	{
		//The Jadestone Letter Quest (Reward = 3000, bazaar)
		//Lots of infindel killing.

		//The Jadestone Nochipa Quest (Reward = 5000, bazaar)
		//Violent as all get out.
		command("say Go find Jadestone doll. Now, stop bothering me.");
	  WRITE_THIS_LOG(QUEST_FILE, player->query_name()
			+ " is recommended Jadestone Group Four Quest.\n");

		return 1;
	}

	//Example: Add Your Group 4 Response Here
	/*if(task == YOUR_VARIABLE)
	{
		//GIVE your QUEST HERE (Reward = ??, Area?)
		command("say Something witty.");
		return 1;
	} */

	//This should not happen.
	  WRITE_THIS_LOG(QUEST_FILE, "give_group_four_task Failed.\n");
	write("Failed. Please Make a Bug Report about this NPC.\n");
	return 0;
}

