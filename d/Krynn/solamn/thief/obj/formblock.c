/* created by Aridor 09/94 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <language.h>

mixed produces;
string produced_name = "";
int broken = 0;
int hits = 0;
int max_fill;
int filled = 0;
int solved = 0;
string *the_colors = ({ });

void
create_object()
{
    set_name("block");
    add_name("stone");
    add_name("stoneblock");
    add_name("formblock");
    set_adj("hollow");
    add_adj("stone");
    set_short("@@my_short@@");
    set_pshort("@@my_pshort@@");
    set_long("@@my_long@@");
    add_prop(OBJ_I_VOLUME, 50000);
    add_prop(OBJ_I_WEIGHT, 50000);
    seteuid(getuid(TO));
}

string
my_short()
{
    if (broken)
      return "broken hollow stone block";
    return "hollow stone block";
}

string
my_pshort()
{
    if (broken)
      return "broken hollow stone blocks";
    return "hollow stone blocks";
}

string
my_long()
{
    if (broken)
      return ("The block is broken and useless now. Once, it had a " +
	      "hollow inside and there are still some tiny glimmering " +
	      "pieces of metal noticable there. It seems that the block " +
	      "was used to produce a " + produced_name + ".\n");
    add_item(({"hole","hole on block","hole on formblock"}),"@@check_hole@@");
    return "This is an ordinary looking stoneblock except for the " +
      "hole on top of it.\n";
}

string
check_hole()
{
    if (broken)
      return "You find no hole.\n";
    if (filled == max_fill)
      return "It's a hole leading inside the stone block. It is filled " +
	"with some kind of metal.\n";
    return "It's a hole leading inside the stone block. You cannot see " +
      "anything inside, but you think there can't be much in it.\n";
}

void
init()
{
    remove_item("hole");
    remove_item("hole on block");
    remove_item("hole on formblock");
    ADD("do_break","break");
    ADD("do_break","hit");
}

int
set_produce(string file)
{
    if (broken)
      return 0;
    if (produces)
      return 0;
    produces = file;
    produces->load_me();
    if (!produces)
      return 0;
    else
      max_fill = produces->query_prop(OBJ_I_VOLUME);
    return 1;
}

mixed
query_produce()
{
    return produces;
}

/* returns 0 if unsuccessful, 1 if successfully produced */
static int
do_produce()
{
    string a_color;
    string *my_colors = ({ });

    seteuid(getuid(TO));
    if (!produces || broken)
      return 0;
    if (filled == 0)
      {
	  produces = "Nothing";
	  broken = 1;
	  add_prop(OBJ_I_BROKEN,1);
	  //set_adj("broken");
	  set_short("broken stone block");
	  set_pshort("broken stone blocks");
	  return 1;
      }
    else
      produces = clone_object(produces);
    if (!produces)
      return 0;
    /*figure out what color the produced object has*/
    while(sizeof(the_colors))
      {
	  a_color = the_colors[0];
	  my_colors += ({ a_color });
	  the_colors -= ({ a_color });
      }
    if (sizeof(my_colors) > 1)
      produces->set_adj("multicolored");
    else if (sizeof(my_colors) == 1)
      produces->set_adj(my_colors[0]);

    clone_object(OBJ + "unforged_shadow")->shadow_me(produces);
    if (filled < max_fill)
      {
	  produces->add_prop(OBJ_I_BROKEN,1);
	  produces->remove_adj("broken");
      }
    else
      solved = 1;
    produces->move(E(TP));
    produced_name = produces->short();
    broken = 1;
    add_prop(OBJ_I_BROKEN,1);
    //set_adj("broken");
    set_short("broken stone block");
    set_pshort("broken stone blocks");
    return 1;
}

static int
do_break(string str)
{
    mixed *wep = (all_inventory(TP)->query_dt()) & ({ 4,5,6,7 });
    object thing;
    wep -= ({ 0 });
    NF(C(query_verb()) + " what?\n");
    if (!TO->id(str))
      return 0;
    NF("You cannot hit the stone block when it is not in front of you.\n");
    if (!function_exists("create_room",E(TO)))
      return 0;
    NF("The stone block is still connected to the pipeline.\n");
    if (E(TO)->query_form_block() == TO)
      return 0;
    NF("You don't have a proper tool to break the stone block.\n");
    if (!wep || !sizeof(wep))
      return 0;
    if (broken)
      {
	  NF("The form block is already broken.\n");
	  return 0;
      }
    write("You hit the stone block with a blunt weapon with all your " +
	  "force.\n");
    hits += TP->query_stat(SS_STR);
    if (hits < 150)
      {
	  hits -= (30 + random(hits / 2));
	  if (hits < 0)
	    hits = 0;
	  write("Your force wasn't strong enough to break the stone block.\n");
	  return 1;
      }
    if (!do_produce())
      {
	  write("You come to the conclusion that the formblock cannot be " +
		"broken.\n");
	  return 1;
      }
    write("The stone block shatters and breaks. " +
	  C(stringp(produces) ? produces : LANG_ASHORT(produces)) +
	  " appears from the inside of the block.\n");
    wep->set_reduce_pay(60); /* in percent */
    if (solved == 1)
      {
	  if (!TP->test_bit("Krynn",2,18))
	    {
		seteuid(getuid(TO));
		TP->set_bit(2,18);
		TP->add_exp(3500, 0);/*real exp*/
		write("You feel more experienced!!\n");
		K_QUEST_LOG("quest", "Furnace quest", TP, 3500);
		wep->set_reduce_pay(100); /* in percent */
	    }
	  solved = 2;
      }

    return 1;
}

/* returns how much did fit inside, -1 means broken*/
int
fill_me(int i, string color)
{
    int left;
    if (broken)
      return -1;
    left = max_fill - filled;
    filled += i;
    the_colors += ({ color });
    if (filled > max_fill)
      filled = max_fill;
    if (left > i)
      return i;
    else
      return left;
}

int
query_full()
{
    return filled;
}

int
query_max_fill()
{
    return max_fill;
}

void
set_produced_name(string str)
{
    broken = 1;
    produced_name = str;
}
