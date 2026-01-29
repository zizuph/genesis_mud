/*
 *    trainer.c  
 *
 * A skill trainer module, inherit it and use
 * create_trainer() to set the name etc and
 * add skills to train in initiate_training().
 * see trainer_example.c
 *
 * Baldacin@Genesis, Aug 2003.  
 *
 */

#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>

inherit "/std/monster.c";
inherit "/lib/skill_raise";

int talk_skill_list;

/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    command("say to "+this_player()->query_name()+" I have already taught you everything I know.");
    return 1;
}

/*
 * Function name: sk_hook_write_header
 * Description  : Write the header to the improve or learn list.
 * Arguments    : int steps - the number of steps to train.
 */
void
sk_hook_write_header(int steps)
{
    command("say to "+this_player()->query_name()+" You can train the following skills here.");
    ::sk_hook_write_header(steps);
}

/*
 * Function name: sk_hook_allow_train
 * Description:   Function called when player tries to do the improve command
 *                Will determine if a player can train skills here.
 *                ( Default is:  yes )
 * Arguments:     object - The player trying to improve/learn
 *                string - The string from sk_improve
 *                verb   - improve or learn typically
 * Returns:       1 - yes (default) / 0 - no
 */
public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    return 1;
}

/*
 * Function name: sk_hook_unknown_skill
 * Description  : Player tries to improve or learn an unknown skill.
 * Arguments    : string skill - The skill he sought for.
 *                string verb  - 'learn' or 'improve'.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_unknown_skill(string skill, string verb)
{
    command("say to "+this_player()->query_name()+" What '" + skill + "' are you talking about?");
    return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:     skill - The skill player wanted to improve
 * Returns:       0
 */
int
sk_hook_improved_max(string skill)
{
    command("say to "+this_player()->query_name()+" I cannot teach you any further in this" +
      " skill, seek knowledge elsewhere.");
    return 1;
}
/* THIS ONE */
/*
 * Function name : sk_hook_steps_allowed
 * Description   : tests if practicing steps amount is allowed
 * Arguments     : int     - steps specified by player
 * Returns       : int     - 1 if steps amount fits, and 0 if it doesnt
 */
public int
sk_hook_steps_allowed(int steps)
{
    return 1;
}

/*
 * Function name: sk_hook_cant_train
 * Description  : Player can't train that skill that high for some reason.
 * Arguments    : string skill - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    int number = sk_find_skill(skill);

    this_player()->catch_tell(this_object()->query_The_name(this_player())  +
      " tries to teach you to " + sk_tdesc[number][0] + ", but"     +
      " you fail to adopt it.\n");

    say(QCTNAME(this_object()) + " tries to teach " + QTNAME(this_player()) +
      " to " + sk_tdesc[number][1] + ", but "                     +
      this_player()->query_pronoun() + " fails to adopt it.\n");

    return 1;
}

/*
 * Function name: sk_hook_cant_pay
 * Description  : Player cannot pay for session. (Kill him?)
 * Arguments    : string skill  - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 *                int cost - the price that is required, in coppers.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    command("say to "+this_player()->query_name()+" What are you going to pay with?");
    command("frown");
    return 1;
}


/*
 * Function name: sk_hook_raise_rank
 * Description  : The player trains and pays, write something.
 * Arguments    : int snum  - the number of the skill trained.
 *                int to_lev - the level reached.
 *                int cost - the price paid, in coppers.
 */
void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank = sk_rank(to_lev);

    this_player()->catch_tell(this_object()->query_The_name(this_player())   +
      " teaches you to " + sk_tdesc[snum][0] + " to the rank of "   +
      rank + ".\n");

    say(QCTNAME(this_object()) + " taught " + QTNAME(this_player()) + " to "+
      sk_tdesc[snum][1] + " to the rank of " + rank + ".\n");
}

/*
 * Function name : sk_format_money_say
 * Description   : turns price in cc into platinum, gold and silver string
 *               : formated to speak.
 * Arguments     : int     - the price in copper coins
 * Returns       : string  - formated money string
 */
string
sk_format_money_say(int price)
{
    int    *coins, *value, pc, gc, sc, cc;
 
    if (price <= 0)
    {
        return "-----";
    }
 
    coins = MONEY_SPLIT(price);
    value = MONEY_VALUES;
 
    pc = coins[3];
 
    if (pc > 5)
    {
        return (pc+" pc");
    }
 
    gc = coins[2] + (value[3]*coins[3]) / value[2];
 
    if (gc > 5)
    {
        return (gc+" gc");
    }
 
    sc = coins[1] + (value[2]*coins[2] + value[3]*coins[3]) / value[1];
 
    if (sc > 5)
    {
        return (sc+" sc");
    }
 
    return (price+" cc");
}


/*
 * Function name: sk_list
 * Description:   Someone wants a list of skills
 * Arguments:     steps - How many steps the player wants to raise
 * Returns:       1
 */
int
sk_list(int steps)
{
    int     n = -1, size, *number = sk_query_train();
    int levone, levtwo, levmax;
    string  ranext, ranmax, price;     
 
    if (steps <= 0)
    {
        steps = 1;
    }
 
    number = sort_array(filter(number, &sk_filter_improve(, steps)));
 
    if (!(size = sizeof(number)))
    {
        return sk_hook_no_list_improve();
    }
 
    if (!talk_skill_list)
    {
        sk_hook_write_header(steps);
 
        while (++n < size)
        {
            write(sk_fix_cost(number[n], steps));
        } 
    }
    else
    {
         /* Header */
    //    command("say You can train the following skills here.\n");
 
        while (++n < size)
        {
            levone = (this_player()->query_base_skill(number[n]));
            levtwo = (steps ? levone + steps : levone + 1);
            levmax = (sk_query_max(number[n]));
        
            ranext = (levone >= 100 ? "maxed" : sk_rank(levtwo));
            ranmax = (sk_rank(levmax));
            price = (levtwo > levmax ? "-----" :
              sk_format_money_say(sk_cost(number[n], levone, levtwo)));
            
            command("say to "+this_player()->query_name()+" I guess I could teach you to "+
             /* sk_query_name(number[n])+ */
              sk_tdesc[number[n]][0]+
              " like "+LANG_ADDART(ranext)+ " for "+price+". Keep training and one "+
              "day I might be training you as a "+ranmax+"!");
                       
        }
       
          /* Footer */
    //    command("say .");
    }
 
    return 1;
}

/*
 * Function name: set_talk_skill_list
 * Description  : If we want the trainer to 'speak' his
 *                skill list, set this to 1.
 */
void
set_talk_skill_list(int i)
{
    talk_skill_list = i;
}

/*
 * Function name: initiate_training
 * Description  : Initiate the skills with this function
 *                it is called from the create function.
 */
void
initiate_training()
{
}

/*
 * Function name: create_trainer
 * Description  : Creates the trainer. Use this to create the trainer
 *                not the create_monster function.
 */
void
create_trainer()
{	
}

/*
 * Function name: create_monster
 * Description  : Creates the trainer. You can't create the trainer
 *                by using this function since it is declared nomask,
 *                use create_trainer.
 */	
nomask void
create_monster()
{
    create_trainer();
    create_skill_raise();
    initiate_training();
}

void
init_living()
{
    init_skill_raise();
   
}