/*
 * Function name: sk_hook_unknown_skill
 * Description:   Player tries to improve or learn an unknown skill
 * Arguments:	  skill - The skill he sought for
 *		  verb  - 'learn' or 'improve'
 * Returns:	  0
 */
int
sk_hook_unknown_skill(string skill, string verb)
{
    notify_fail("I'm afraid there is no skill named '" + skill + "' to " +
	verb + ".\n");
    return 0;
}

/*
 * Function name: sk_hook_improve_unknown
 * Description:	  Player wants to improve a skill he has never learned
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
int
sk_hook_improve_unknown(string skill)
{
    notify_fail("You must learn a skill before you can improve it.\n");
    return 0;
}

/*
 * Function name: sk_hook_learn_known
 * Description:	  Player wants to learn an already known skill
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
int
sk_hook_learn_known(string skill)
{
    notify_fail("You already know that skill, try to improve it.\n");
    return 0;
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 * Returns:	  0
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    notify_fail("You fail to adapt what " +
		process_string(QTNAME(this_object())) +
                " tries to teach you.\n");
    return 0;
}

/*
 * Function name: sk_hook_cant_pay
 * Description:   Player can't pay for session (kill him?)
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 *		  cost   - The price
 * Returns:	  0
 */
int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    notify_fail("You don't have enough money with you.\n");
    return 0;
}

/*
 * Function name: sk_hook_raise_rank
 * Description:   The player trains and pays, write something
 * Arguments:	  snum  - The skill he trained
 *		  to_lev - Wich level he reached
 *		  cost   - How much he payed
 */
void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    write(process_string(QCTNAME(this_object())) +
	" helps you to improve your ability to " +
	sk_tdesc[snum][0] + ".\n");
    write("You achieve the rank of " + rank + ".\n");
    say(QCTNAME(this_object()) + " helps " + QTNAME(this_player()));
    say(break_string("" + 
	" to improve " + this_player()->query_possessive() +
	" ability to " + sk_tdesc[snum][1] + " and " +
	this_player()->query_pronoun() + " receives the rank of " +
	rank + ".\n", 70));
}

/*
 * Function name: sk_hook_write_header
 * Description:   Write the header to the improve or learn list
 * Arguments:	  steps - How many steps we are talking about
 */
void
sk_hook_write_header(int steps)
{
    if (!steps)
	steps = 1;
    write("These are the skills " +
	process_string(QTNAME(this_object())) +
	" may help you to " + query_verb() +
	" " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") +
	".\n");
    write("  Skill:                Cost:      "+
          "Next level:          Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
}

/*
 * Function name: sk_hook_skillisting
 * Description:   Someone is listing the skills
 */
void
sk_hook_skillisting()
{
    write("This is what I can teach you, and your " +
	  "next level in those skills:\n");
    write("  Skill:                Cost:      "+
          "Next level:          Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
}

/*
 * Function name: sk_hook_no_list_learn
 * Description:   No more unknown skills for the player in this guild
 * Returns:	  1
 */
int
sk_hook_no_list_learn()
{
    write(break_string("For you there are no unknown skills. " +
	"You may try to improve some or seek out new teachers " +
	"elsewhere.\n", 70));
    return 1;
}

/*
 * Function name: sk_hook_no_list_improve
 * Description:   No more skills that the player can improve
 * Returns:	  1
 */
int
sk_hook_no_list_improve()
{
    write(break_string("I have taught you all that I can. " +
	"Perhaps you would feel like learning some new skills, " +
	"or try to find another teacher?\n", 70));
    return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:	  skill - The skill player wanted to improve
 * Returns:	  0
 */
int
sk_hook_improved_max(string skill)
{
    notify_fail(break_string(
	"I cannot train you any further here, you have to " +
	"seek knowledge elsewhere.\n", 70));
    return 0;
}

int query_init_master() { return 1;}
