/* created by Aridor 12/20/93 */

#include "../local.h"
#define HOW_FAR    ({ "almost all the way", "about three-quarters", \
		      "about two-thirds", "about halfway", \
		      "close to halfway", "a little"})

inherit OUTSIDE_BASE;

#include <ss_types.h>
#include <macros.h>

void
create_splains_room()
{
    set_short("At the foot of the mountains");
    set_long("@@my_long");
/*    set_long("Impressive mountains rise up right to your west and " +
	     "northwest. The plains stretch out to your east as far as you " +
	     "can see. You are still on the plains, and the grass is just " +
	     "as dry as everywhere else. You notice a small trickle of " +
	     "water coming down the mountainside though.\n");
*/
    add_item(({"mountain","mountains","cliff","mountainside"}),
	     "The mountains you see rise up direct in front of you to your " +
	     "west. The mountain range runs in a southwest - northeastern " +
	     "direction. The cliff looks almost impossible to climb.\n");
    add_item(({"valley"}),
	     "The valley is so narrow that there is only room for the river " +
	     "and it is impossible to go in on foot.\n");
    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think the " +
	     "ground might just be a little damper here near the river.\n");
    add_item(({"trickle","water"}),
	     "This is not much water coming down here and all of it is " +
	     "soaked into the ground immediately. This makes the ground " +
	     "maybe just a little wetter than on the rest of the plains.\n");
    add_cmd_item(({"mountain","cliff","mountains","up","mountainside"}),"climb",
		 "@@do_climb");

    set_noshow_obvious(1);
    add_exit(ROOM + "road1","southwest",0,3);
    add_exit(ROOM + "plain1","south",0,3);
    add_exit(ROOM + "mount2","northeast",0,3);
    add_exit(ROOM + "plain19","east",0,3);
    
    (DWARFGATE)->load_me();
}

string
my_long()
{
    string str;
    str = ("Impressive mountains rise up right to your west and " +
	   "northwest. The plains stretch out to your east as far as you " +
	   "can see. You are still on the plains, and the grass is just " +
	   "as dry as everywhere else. You notice a small trickle of " +
	   "water coming down the mountainside though.\n");
    if ((DWARFGATE)->gate_is_open())
      str += ("High up on the cliff you notice an opening into the " +
	      "mountain, but it looks almost unaccessable from down here.\n");
    return str;
}

int
do_climb()
{
    int sk = TP->query_skill(SS_CLIMB) - 37 - random(15, time() / 1000);

    sk -= 8;
    sk /= (-8);
    sk--;
    if (sk < 0)
      {
	  if (!(DWARFGATE)->query_gate_state())
	    write("You pick your foot- and handholds carefully and climb up " +
		  "the mountainside. You reach a narrow path and you are " +
		  "able to walk the last part and right in front of you a " +
		  "great opening leads into the mountainside.\n");
	  else
	    write("You pick your foot- and handholds carefully and climb up " +
		  "the mountainside. You reach a narrow path and you are " +
		  "able to walk a bit but suddenly the path ends in front " +
		  "of naked rock.\n");
	  TP->move_living("climbing up the cliff", DWARFGATE_OUTSIDE);
	  say(QCTNAME(TP) + " arrives climbing up the cliff.\n");
	  find_player("aridor")->catch_msg(TP->query_name() + " enters THIEFAREA.\n");
      }
    else
      {
	  sk = random(sk);
	  write("You pick your foot- and handholds carefully and climb up " +
		"the mountainside. As you are " + HOW_FAR[sk] + " up, " +
		"you miss a grip and fall back down. OUCH!!\n");
	  say(QCTNAME(TP) + " climbs up the mountainside. Being " + 
	      HOW_FAR[sk] + " up, " + PRONOUN(TP) + " misses a grip and " +
	      "falls back down!\n");
	  TP->heal_hp(-150 - sk*25);
	  TP->do_die(TO);
      }
    return 1;
}
