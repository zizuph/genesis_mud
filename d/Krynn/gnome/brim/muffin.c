/* created by Aridor, 06/15/94 */

inherit "/std/food";
#include "brimsch.h"
#include <macros.h>

int hits = 0;

void
create_food()
{
    set_name("muffin");
    set_pname("muffins");
    set_adj("yummy");
    set_long("It looks very delicious, but by eating it you will never solve this!\n");
    add_prop(HEAP_S_UNIQUE_ID,"Muffin with raisins #" + time());
    set_amount(41);
    seteuid(getuid(TO));
}

void
init()
{
    ::init();
    ADD("smash","squeeze");
    ADD("smash","break");
    ADD("smash","tear");
    ADD("smash","rip");
    ADA("smash");
}


int
smash(string str)
{
    object drop;
    NF(C(query_verb()) + " what?\n");
    if (!str)
      return 0;
    if (str != "muffin")
      return 0;
    NF("The muffin is too smashed already.\n");
    if (query_adj() == "smashed")
      {
	  if (hits >= 1)
	    return 0;
	  write("You " + query_verb() + " the smashed muffin again and some drops of a liquid drop onto the floor.\n");
	  say(QCTNAME(TP) + " hits something in " + POSSESSIVE(TP) + " hands and some drops fall onto the floor.\n");
	  drop = clone_object(DROP);
	  drop->set_person(TP);
	  drop->move(E(TP));
	  hits++;
	  return 1;
      }
    remove_adj("yummy");
    set_adj("smashed");
    set_short(0);
    remove_prop(HEAP_S_UNIQUE_ID);
    set_long("It looks smashed. A shapeless mass, and a drop " +
	     "of something sticky runs down your finger as you " +
	     "hold it.\n");
    set_amount(30);
    write("You " + query_verb() + " the muffin and some drops of a liquid drop onto the floor.\n");
    say(QCTNAME(TP) + " hits something in " + POSSESSIVE(TP) + " hands and some drops fall onto the floor.\n");
    drop = clone_object(DROP);
    drop->set_person(TP);
    drop->move(E(TP));
    hits++;
    return 1;
}


