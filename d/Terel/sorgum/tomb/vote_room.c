/*
    This room is where the vote puzzle quest takes place. It
	was created by Sorgum sometime around 1993.

    Modified: 13 June 2003, by Bleys
	- Updated to modern includes.
	- Now logging to the correct quest file.

    Modified: Jan 2021, by Lucius
        - Some code reformatting and various fixups.
        - Removed QXP reward limiter, such things are nonsense.
*/

#include "/d/Terel/include/Terel.h"

inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>
#include "tomb.h" 

#include "/d/Terel/include/quest_bits.h"

string *voters, *TerelWiz = ({
  "Cedric", "Mecien", "Vader", "Azireon", "Janus",
  "Redhawk", "Mortricia", "Dust", "Sorgum"
});

mixed *sol = ({
  ({ "nay", "aye", "aye", "aye", "nay" }),
  ({ "nay", "aye", "aye", "aye", "nay" }),
  ({ "aye", "nay", "aye", "aye", "nay" }),
  ({ "nay", "nay", "aye", "aye", "nay" }),
  ({ "nay", "aye", "nay", "aye", "nay" }),
});

mapping sol_done = ([]);
int current, solved = 0;


public int
is_occupied()
{
    int i;
    object *op = deep_inventory();

    for (i = 0; i < sizeof(op); i++) {
	if (interactive(op[i]))
            return 1;
    }
    return 0;
}

public void
init()
{
    ::init();
    add_action("answer_func", "answer");
    add_action("solve_func", "solve");
    add_action("read_func", "read");
}

public int
ransort(string a, string b)     { return random(3) - 1; }

public void
reset_room()
{
    current = 0;
    voters = ({ }) + TerelWiz;
    sol_done = mkmapping(0, allocate(5));

    while(sizeof(voters) > 5) {
        voters -= ({ one_of_list(voters) });
    }
    sort_array(voters, ransort);
    tell_room(TO, "There is a blinding flash of light and the sign is " +
      "magically altered.\n");     
}

public void
create_room()
{
    set_short("Vote room");
    set_long(
      "This is the Terel wizard council chamber.  There is a sign on " +
      "the wall.  There is a column in the center of the room with " +
      "an oracle set into it.  In the corner is a strange statue.\n"
    );

    reset_room();

    add_item(({"sign", "wall"}), "@@desc_sign");
    add_item(({"oracle", "column"}), 
      "The oracle accepts solutions to the puzzle.  Make sure you read " +
      "the sign first though.\n"
    );				   

    add_item("statue", "The statue is amorphous although roughly humanoid.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(TOMBDIR + "path03", "out", 0);    
}

public string
desc_sign()
{
    return(
      "A council of five Terel wizards recently voted on five proposals " +
      "concerning the domain of Terel.  Each of the five council members-- " +
      implode(voters[0..3],", ") + " and " + voters[4] + " --cast an aye or " +
      "a nay vote for each of the five proposals, with no abstentions.  " +
      "You must deduce how each council member voted on each proposal, " +
      "given the following clues:\n" +

      "\n1. Each proposal got a different number of aye votes." +

      "\n2. All in all, there was one more aye vote than nay vote cast." +

      "\n3. At no point in time did " + voters[2] + " vote nay on two " +
      "consecutive proposals." +

      "\n4. " + voters[0] + ", " + voters[1] + ", " + voters[4] +
      " voted the same way on the second proposal." +

      "\n5. " + voters[3] + " voted aye on the fourth proposal." +

      "\n6. " + voters[2] + " and " + voters[4] + " voted differently on " +
      "each of the first three proposals." + 

      "\n7. The third proposal received one more aye vote than the second " +
      "proposal did.\n\n"

      +  "When you think you have solved the puzzle you can use 'solve' " +
      "and the oracle will give you further instructions. " +
      "Be careful!\n\nAnswering incorrectly could prove to be very " +
      "dangerous or even fatal!\n");
}

public int
get_next()
{
    int *next = filter(sol_done, &operator(==)(0));
    return one_of_list(m_indices(next));
}

public int
ask_next()
{
    write("How did " + voters[current] + " vote?\n");
    return 1;
}

public int
solve_func(string str)
{
    write("The oracle bellows: You have awakened the oracle!  Now you " +
      "must solve the puzzle or else incur my wrath!  You must use the " +
      "'answer' command to enter your answers.  For example: 'answer " +
      "aye aye nay aye nay'.\n");

    solved = 0;
    current = get_next();
    return ask_next();
}

public int
answer_func(string str)
{
    int i;
    string *ans;
    object riddler;

    if (!strlen(str))
    {
        notify_fail("You didn't provide an answer.\n");
        return 0;
    }

    ans = explode(str, " ");
    i = sizeof(ans);

    if (i != 5)
    {
	notify_fail("There were 5 proposals, not " + sizeof(ans) + "\n");
	return 0;
    }

    for (i = 0; i < 5; i++)
    {
	if ((ans[i] != "aye") && (ans[i] != "nay"))
        {
	    write("You typed something other than 'aye' or 'nay'\n");
	    return 1;
	}

	if (ans[i] != sol[current][i])
        {
	    write("Your solution is wrong!\n");
	    write("The oracle flashes and you feel an intense pain.\n");
	    reset_room();
	    find_object(TOMBDIR + "dop_room")->remove_exit("out");
	    TP->reduce_hit_point(TP->query_hp() / 4);
	    TP->move_living("X", TOMBDIR + "dop_room");
	    riddler = clone_object(TOMBDIR + "riddler");
	    riddler->move_living("X", TOMBDIR + "dop_room");
	    riddler->global_set_up(TP);
	    return 1;
	}
    }

    write("Your solution for how " + voters[current] +" voted is correct!\n");
    if (++solved == 5)
    {
	reset_room();
	write("You solved the entire puzzle!\n");
	if (TP->test_bit("Terel", QUEST_SS1_GROUP, QUEST_SS1_BIT))
	{
	    tell_object(TP, "You have solved the puzzle on a previous " +
	      "occasion!\n");
	}
	else
	{
            TP->add_exp(QUEST_SS1_EXP);
	    TP->set_bit(QUEST_SS1_GROUP, QUEST_SS1_BIT);
	    tell_object(TP, "You feel more experienced than before.\n");
	    write_file(QUEST_LOG, TP->query_name() + " solved " +
	      "the Terel wizard council vote quest (vote_room) (" +
	      ctime(time()) + ")\n");
	}
	return 1;
    }
    sol_done[current] = 1;
    current = get_next();
    ask_next();
    return 1;
}

public int
read_func(string str)
{
    if (str == "sign")
    {
	write(desc_sign());
	return 1;
    }
    return notify_fail("Read what?\n");
}
