/*
 * 920820 by dust. A mathematical riddle. Description is included... note
 * that the balance behaves following the heisenberg principle ;--)
 * it doesnt choose the solution a priori.
 * 920905: modified by dust: coins instead of balls, quest-exp,
 *         hint for zodiac-quest given, colour green instead of purple
 * 931019: improved for other riddle
 */
inherit "std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define BAL_LEFT	"The balance bends to the left.\n"
#define BAL_EQUI	"The balance remains in equilibrium.\n"
#define BAL_RIGHT	"The balance bends to the right.\n"

#define BSN(s)		break_string(s,70)
#define BSNN(s)		break_string((s)+"\n",70)

int	*possible;	/* All still possible solutions */
int	*left;		/* coins on the left */
int	*right;		/* coins on the right */
int	tries;		/* Number of tries */


/*
 * start_balance: resets number of tries to 0 and puts all
 * possibilities in possible
 */
start_balance()
{
    tries = 0;
    possible = ({0,0,1,0, 0,0,1,1, 0,1,1,0, 0,1,1,1,
		 0,0,2,0, 0,0,2,1, 0,1,2,0, 0,1,2,1,
		 0,0,3,0, 0,0,3,1, 0,1,3,0, 0,1,3,1,
		 0,0,4,0, 0,0,4,1, 0,1,4,0, 0,1,4,1,
		 0,0,5,0, 0,0,5,1, 0,1,5,0, 0,1,5,1,
		 1,0,2,0, 1,0,2,1, 1,1,2,0, 1,1,2,1,
		 1,0,3,0, 1,0,3,1, 1,1,3,0, 1,1,3,1,
		 1,0,4,0, 1,0,4,1, 1,1,4,0, 1,1,4,1,
		 1,0,5,0, 1,0,5,1, 1,1,5,0, 1,1,5,1,
		 2,0,3,0, 2,0,3,1, 2,1,3,0, 2,1,3,1,
		 2,0,4,0, 2,0,4,1, 2,1,4,0, 2,1,4,1,
		 2,0,5,0, 2,0,5,1, 2,1,5,0, 2,1,5,1,
		 3,0,4,0, 3,0,4,1, 3,1,4,0, 3,1,4,1,
		 3,0,5,0, 3,0,5,1, 3,1,5,0, 3,1,5,1,
		 4,0,5,0, 4,0,5,1, 4,1,5,0, 4,1,5,1});
    /* possibilities: each possibility uses 4 entries; the first entry is
     * the index of the first fake coin (0-5), the second is 0 for lighter, 1 for
     * heavier. The third and fourth are the same for the second fake coin.
     * There are 15 ways to choose 2 fakes (one line each) and 4 possibilities
     * to assign light and heavy, so there are 60 solutions (-> 240 entries in table)
     */
}

/*
 * calc_left: returns array of possibilities if balance bends to the left
 */

int *
calc_left()
{
  int *result;
  int i,j,weight_left,weight_right;
  
  result = ({ });
  for (i=0, j=2; i<sizeof(possible); i += 4, j += 4) /* i loops f1rst, j second fake */
    {
      weight_left = weight_right = 0; /* calculate left and right overweight */
      if (member_array(possible[i],left) >= 0)
	weight_left += 2*possible[i+1] - 1; /* +1 for heavy, -1 for light */
      if (member_array(possible[i],right) >= 0)
	weight_right += 2*possible[i+1] - 1;
      if (member_array(possible[j],left) >= 0)
	weight_left += 2*possible[j+1] - 1;
      if (member_array(possible[j],right) >= 0)
	weight_right += 2*possible[j+1] - 1;
      if (weight_left > weight_right) /* add if overweight on left */
	result = result + ({ possible[i], possible[i+1],
			     possible[j], possible[j+1] });
    }
  return result;
}

/*
 * calc_right: returns array of possibilities if balance bends to the right
 */

int *
calc_right()
{
  int *result;
  int i,j,weight_left,weight_right;
  
  result = ({ });
  for (i=0, j=2; i<sizeof(possible); i += 4, j += 4) /* i loops first, j second fake */
    {
      weight_left = weight_right = 0; /* calculate left and right overweight */
      if (member_array(possible[i],left) >= 0)
	weight_left += 2*possible[i+1] - 1; /* +1 for heavy, -1 for light */
      if (member_array(possible[i],right) >= 0)
	weight_right += 2*possible[i+1] - 1;
      if (member_array(possible[j],left) >= 0)
	weight_left += 2*possible[j+1] - 1;
      if (member_array(possible[j],right) >= 0)
	weight_right += 2*possible[j+1] - 1;
      if (weight_left < weight_right) /* add if overweight on right */
	result = result + ({ possible[i], possible[i+1],
			     possible[j], possible[j+1] });
    }
  return result;
}


/*
 * calc_equi: returns array of possibilities if balance remains in equilibrium
 */

int *
calc_equi()
{
  int *result;
  int i,j,weight_left,weight_right;
  
  result = ({ });
  for (i=0, j=2; i<sizeof(possible); i += 4, j += 4) /* i loops first, j second fake */
    {
      weight_left = weight_right = 0; /* calculate left and right overweight */
      if (member_array(possible[i],left) >= 0)
	weight_left += 2*possible[i+1] - 1; /* +1 for heavy, -1 for light */
      if (member_array(possible[i],right) >= 0)
	weight_right += 2*possible[i+1] - 1;
      if (member_array(possible[j],left) >= 0)
	weight_left += 2*possible[j+1] - 1;
      if (member_array(possible[j],right) >= 0)
	weight_right += 2*possible[j+1] - 1;
      if (weight_left == weight_right) /* add if no overweight */
	result = result + ({ possible[i], possible[i+1],
			     possible[j], possible[j+1] });
    }
  return result;
}


/*
 * calc_answer: calculates the most general answer (returns string)
 * the balance tries to behave in a way that it leaves as much
 * "open" possibilities as possible. So it calculates how much
 * solutions remain if teh balance bends to the left, right, or
 * stays in equilibrium. The maximum is teh answer returned. If
 * several behaviours result in the same (maximum) number of
 * still possible solutions, one is chosen by random (they are
 * stored in "int *poss*", 0: bending to the left, 1: equilibrium,
 * 2: bending to the right).
 */
string
calc_answer()
{
    int *result_left;
    int *result_right;
    int *result_equi;
    int le,ri,eq,answer;
    int *poss;	/* all most general answers; 0=left, 1=equi, 2=right */

    poss = ({ }); /* no behaviour chosen yet */
    tries++;
    /* first treat trivial cases, if number of coins isn't the same on
     * both sides (it is assumed the weigh-difference is smaller than
     * the weigh of a single coin)
     */
    if (sizeof(left) > sizeof(right))
    {
	answer = 0; /* more coins on the left: bend to the left */
	result_left = possible; /* no information gained */
    }
    else if (sizeof(left) < sizeof(right))
    {
	answer = 2; /* more coins on the rght: bend to the right */
	result_right = possible; /* no information gained */
    }
    else /* only way to get information: same number of coins */
    {
	/* first calculate remaining possibilities for all 3 baheviours */
	result_left = calc_left();	le = sizeof(result_left);
	result_right = calc_right();	ri = sizeof(result_right);
	result_equi = calc_equi();	eq = sizeof(result_equi);
	/* fill "poss" with the "best" behaviours (worst for teh player) */
	if (le >= ri && le >= eq) poss = poss + ({ 0 }); /* left */
	if (ri >= le && ri >= eq) poss = poss + ({ 2 }); /* right */
	if (eq >= ri && eq >= le) poss = poss + ({ 1 }); /* equilibrium */
	answer = poss[random(sizeof(poss))]; /* choose one by random */
    }
    /* now the answer is chosen, eventually by random. Construct string. */
    if (answer == 0) /* answer is "left" */
    {
	possible = result_left;
	return BAL_LEFT;
    }
    if (answer == 1) /* answer is "equilibrium" */
    {
	possible = result_equi;
	return BAL_EQUI;
    }
    /* answer is "right" (it's ok to leave away else) */
    possible = result_right;
    return BAL_RIGHT;
}


create_object()
{
    set_name("balance");
    add_adj(({"green","old"}));
    set_short("green, old balance");
    set_long(break_string("This is dusts IMPROVED and NEW green, old balance. At the front you " +
	"see 6 coins numbered from 1 to 6. Behind the coins, you " +
	"find instructions on how to use the balance.\n",70));
    add_prop(OBJ_I_NO_GET,1);
    start_balance();
    enable_reset();
}

reset_object()
{
    say("The coins in front of the balance are shuffeled.\n");
    start_balance();
}

init()
{
    ::init();
    add_action("do_weigh","weigh");
    add_action("do_solve","solution");
    add_action("do_shuffle","shuffle");
    add_action("instructions","read");
}

int
instructions(string str)
{
    if (str != "instructions" && str != "instruction") return 0;
    write(break_string("There are six coins in front of this balance. " +
	"Four of them are real coins, made of silver. Two coins are " +
        "faked coins, they can be made of aluminium or of lead and so are " +
        "heavier or lighter than the other four. It is assumed that an " +
        "aluminium and a lead coin together weigh just as much as two " +
        "silver coins. " +
        "Of course you don't know if the two faked coins are made of " +
        "lead or aluminium, it is also possible that one is of lead and one of " +
        "aluminium. You can't distinguish the coins by their appearance, the " +
        "only way to find out which is is made out of what is by comparing " +
        "their weight on this balance... But beware, you are only allowed " +
        "four tries! If you think you know the solution, tell it to me " +
        "using the command 'solution 1 heavy 2 light' (assuming you think that " +
        "coin 1 is a lead and coin 2 an aluminium coin). You can always " +
        "start from scratch by shuffling the coins.\n",70));
    return 1;
}

int
do_shuffle(string str)
{
    write(break_string("You put the coins back. You are so nervous that you " +
	"drop them, so you don't know the order they have been on before " +
	"anymore.\n",70));
    say(QCTNAME(this_player()) + " shuffles the coins.\n");
    start_balance();
    return 1;
}

/*
 * do_weigh: command parser for weight
 */
int
do_weigh(string str)
{
    string *cmd,player;
    int i,side,n;
    string reply;

    notify_fail("weigh what?? Please read the instructions...\n");
    cmd = explode(str," ");
    left = ({ }); right = ({ }); /* representing the sides of the balance */
    side = 0; /* 0 means: we fill teh left side of the balance, 1 the right */
    for (i=0; i<sizeof(cmd); i++) /* scan all tokens */
    {
	sscanf(cmd[i],"%d",n); /* try to represent token as number */
	/* "and" or "against" change the side (left to right) */
	if (cmd[i] == "and" || cmd[i] == "against")
	{
	    if (side) /* if we are already on the right side */
	    {
		notify_fail("You can use 'and' or 'against' only once.\n");
		return 0;
	    }
	    else side = 1;
	}
	else if (n > 0 && n < 7) /* only numbers 1-6 allowed */
	{
	    n--; /* Adjust for array index 0-5 */
	    if (member_array(n,right) >= 0 || member_array(n,left) >= 0)
	    {
		notify_fail("You can't use any coin twice.\n");
		return 0;
	    }
	    if (side) right = right + ({ n });
	    else left = left + ({ n });
	}
	else return 0;
    }
    if (sizeof(left) == 0 || sizeof(right) == 0) /* probably a syntax error */
    {
	notify_fail("I don't count this as a try... you should put coins " +
	    "on BOTH sides.\n");
	return 0;
    }
    /* construct answer string to "reply" */
    reply = " ";
    for (i=0; i<sizeof(left); i++)
    {
	n = left[i]; n++;
	reply = reply + n + " ";
    }
    reply = reply + "on the left side and coins ";
    for (i=0; i<sizeof(right); i++)
    {
	n = right[i]; n++;
	reply = reply + n + " ";
    }
    reply = reply + "on the right side of the balance. " +
	calc_answer(); 
    say(break_string(QCTNAME(this_player()) + " puts coins" + reply,70));
    write(break_string("You put coins " + reply,70));
    return 1;
}

/*
 * quest_solved: called if a player solved the quest. Increases exp etc.
 */
string
quest_solved()
{
    int	exp_to_give;

/*
    seteuid(getuid());
    if (this_player()->test_bit("Terel",QUEST_BAL_GROUP,QUEST_BAL_BIT))
	return(" ");
    this_player()->set_bit(QUEST_BAL_GROUP,QUEST_BAL_BIT);
    exp_to_give = this_player()->query_exp();
    if (exp_to_give > QUEST_BAL_EXP)
	exp_to_give = QUEST_BAL_EXP;
    this_player()->add_exp(exp_to_give,0);
    write_file(QUEST_LOG,this_player()->query_name() +
	" solved balance-quest (" + ctime(time()) + ")\n");
    return(" Suddenly you feel much more experienced and " +
	"enlightened than before...");
*/
}


/*
 * do_solve: player thinks he/she knows the solution
 */
int
do_solve(string str)
{
    string *cmd;
    int i,j,n,nn,m,mm;
    int *remain;
    object doorroom;
    int hint;

    notify_fail("I didn't understand your solution...\n");
    cmd = explode(str," ");
    if (sizeof(cmd) < 4) return 0;
    sscanf(cmd[0],"%d",n);
    if (n<1 || n>6) return 0;
    n--;
    if (cmd[1] == "light" || cmd[1] == "aluminium") nn = 0;
    else if (cmd[1] == "heavy" || cmd[1] == "lead") nn = 1;
    else return 0;
    sscanf(cmd[2],"%d",m);
    if (m<1 || m>6) return 0;
    m--;
    if (cmd[3] == "light" || cmd[3] == "aluminium") mm = 0;
    else if (cmd[3] == "heavy" || cmd[3] == "lead") mm = 1;
    else return 0;
    say(QCTNAME(this_player()) + " thinks that coin " +
	cmd[0] + " is a " + cmd[1] + " one and coin " +
        cmd[2] + " a " + cmd[3] + " one.\n");
    remain = ({ });
    /* "remain" gets the still possible solutions WITHOUT the one
     * suggested by the player. The loop calculates this (n,nn is the
     * player-suggested one)
     */
    for (i=0; i<sizeof(possible); i += 4)
    {
	if (possible[i] != n || possible[i+1] != nn ||
	    possible[i+2] != m || possible[i+3] != mm)
	    remain = remain + ({ possible[i], possible[i+1],
                                 possible[i+2], possible[i+3] });
    }
    /* The balance is mean... if a possibility remains, this one is
     * "chosen" (a posteriori) as right solution, so teh player is
     * ALWAYS wrong, if he didn't restrict the search-space by weighing.
     * so guessing is no option.
     */
    if (sizeof(remain) > 0)
    {
	i = random(sizeof(remain)/4); i *= 4; /* choose an answer by random */
	n = remain[i]; n++; i++;
	write("Sorry, that was the wrong solution.\n");
	write("The right solution is that coin " +
	    n + " is made of " +
	    (remain[i] ? "lead" : "aluminium") +
            " and coin " + (remain[i+1]+1) + " is made of " +
	    (remain[i+2] ? "lead" : "aluminium") + ".\n");
	say("Unfortunately that's the wrong solution.\n");
	say("The right solution is that coin " +
	    n + " is made of " +
	    (remain[i] ? "lead" : "aluminium") +
            " and coin " + (remain[i+1]+1) + " is made of " +
	    (remain[i+2] ? "lead" : "aluminium") + ".\n");
	do_shuffle("");
	return 1;
    }
    say("That's exactly the right solution!\n");
    write("That's right... you needed " + tries + " tries.\n");
    if (tries <= 4)
    {
	say("It was even solved with not more than four tries!!\n");
	write(BSNN("Congratulations, you didn't use more than four tries!! " +
	    "You turn the coin you just detected and see the picture of " +
	    "<hint>. " + quest_solved()));
    }
    else
    {
	say("Unfortunately " + tries + " tries were needed... too much.\n");
	write("Unfortunately you used more than four tries...\n");
    }
    do_shuffle("");
    return 1;
}

