/*
    A chimney-sweeper "HAPPY NEW YEAR"
*/

     

inherit "/std/monster";

#include <macros.h>

#define BS(x) break_string(x,70)
#define NF(x) notify_fail(x)

/*
 * Function name: create_monster
 * Description:   creates the monster (what else?)
 * Arguments:     none
 * Returns:       nothing
 */

create_monster()
{
#define LONG_DESCRIPTION \
  "This chimney-sweeper really looks like a mascot. If I were you " + \
  "I'd try to get some of his luck by touching him.\n"
  
  set_name("chimney-sweeper");
  set_race_name("chimney-sweeper");
  set_long(BS(LONG_DESCRIPTION));
  set_random_move(10);

}

 

void
init_living()
{
    this_object()->command("say HAPPY NEW YEAR!");
    add_action("touch", "touch");
}

     
int
touch(string what)
{
#define MESSAGE \
"You touch the chimney-sweeper and boy you can be sure that " + \
"you're a lucky person from now on.\n"

  if (!what) {
    NF("Touch what?\n");
    return 0;
  }

  if((what != "chimney-sweeper") && (what != "sweeper"))
 {
   NF("You don't see no " + what + ".\n");
   return 0;
 }

write(BS(MESSAGE));
say(QCTNAME(this_player()) + " touches the chimney-sweeper.\n");
return 1;

}

 


