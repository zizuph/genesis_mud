/*
 * This change shows output of training areas with P/G/S/C instead of total 
 * copper coins.
 *
These are the skills you are able to improve one step here.
                        Cost:
  Skill:                P  G  S  C  Next level:           Max level:
-----------------------------------------------------------------------------
  conjuration spells    1  3  6  0  novice acolyte        superior journeyman 
  sneak                 0  6  1  6  novice layman         superior journeyman 
  hide                  0  6  1  6  novice layman         superior journeyman 
  trading               1  5 11  4  junior journeyman     superior journeyman 

 *-- Finwe, October 2005
 *-- Disabled by Eowul, Januari 2013 as a similar function is now implemented 
 *   in the mudlib.
*/

#include <language.h>
inherit "/lib/skill_raise";

/*
 * Function name: sk_fix_cost
 * Description:   Fix each line in the improve/learn list
 * Arguments:     snum  - The skill to check
 *                steps - How many steps player wants to raise
 * Returns:       A formatted string
 *
varargs string
sk_fix_cost(int snum, int steps)
{
    int this_level, next_level, max, cost_brkdn;
    string next_rank, max_rank, cost;

    this_level = this_player()->query_base_skill(snum);
    next_level = steps ? this_level + steps : this_level + 1;

    if (next_level > (max = sk_query_max(snum)))
    {
        cost = "---";
    }
    else
    {
        cost = sk_cost(snum, this_level, next_level) + "";
        cost_brkdn = atoi(cost);
    }

    next_rank = ((this_level >= 100) ? "maxed" : sk_rank(next_level));
    max_rank = sk_rank(max);

    if (!sk_hook_allow_train_skill(this_player(), sk_trains[snum][0], 
            next_level))
    {
        return "";
    }

    return sprintf(" %-=21s %2d %2d %2d %2d  %-21s %-20s\n", sk_trains[snum][0], 
        cost_brkdn / 1728, (cost_brkdn % 1728) / 144, (cost_brkdn % 144) / 12, cost_brkdn % 12, next_rank, max_rank);
}


/*
 * Function name: sk_hook_write_header
 * Description  : Write the header to the improve or learn list.
 * Arguments    : int steps - the number of steps to train.
 *
void
sk_hook_write_header(int steps)
{
    if (!steps)
    {
        steps = 1;
    }
    write("\nThese are the skills you are able to " + query_verb() + " " +
        LANG_WNUM(steps) + ((steps == 1) ? " step" : " steps") + " here.\n");
    write("                        Cost:\n"+
          " Skill:                 P  G  S  C  Next level:           " +
          "Max level:\n"+
          "------------------------------------------------------------" +
          "------------------\n");
}

/*
 * Function name: sk_hook_skillisting
 * Description  : Display the header when someone is listing the skills
 *                to see which training he can receive.
 *
void
sk_hook_skillisting()
{
    write("Here follows all skills we teach, and your next level in " +
          "those skills:\n\n");
    write("                        Cost:\n"+
          "  Skill:                P  G  S  C  Next level:           " +
          "Max level:\n"+
          "------------------------------------------------------------" +
          "-----------------\n");
}
*/