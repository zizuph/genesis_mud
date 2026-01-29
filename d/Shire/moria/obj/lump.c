inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void die(object fool);
create_object() {
    set_name(({"sulfur", "lump", "lump of sulfur"}));
    set_short("lump of sulfur");
    set_long(
"This is a green-yellow lump of sulfur, which has a peculiar scent.\n"
    );
    add_item(({"scent of lump","lumps scent", "lump's scent", "sulfur's scent",
	       "scent of sulfur", "scent of lump of sulfur",
	       "lump of sulfur's scent"}), "@@exa_scent@@");
    add_prop(OBJ_I_WEIGHT, 456);
    add_prop(OBJ_I_VALUE,    3);
}

init() {
    ::init();
    add_action("do_eat","eat");
    add_action("do_smell","smell");
    add_action("do_smell","sniff");
    add_action("do_smell","scent");
}


string
exa_scent()
{
    tell_room(ETP,
	QCTNAME(TP)+" sniffs upon a smelly lump of sulfur.\n", TP);
    return
	"It smells horrible. The last thing I would do is eat it, as "+
	"it probably is *very* poisonous.\n";
}

do_smell(str) {
  if(!id(str)) {
    notify_fail("Smell what?\n");
    return 0;
  }
  write(exa_scent());
  return 1;
}

do_eat(str) {
    if(!id(str))
	return 0;
    write("You carefully start to eat the lump of sulfur.\n");
    say(QCTNAME(TP)+" carefully start to eat the lump of sulfur.\n");
    write("I don't think it was such a great idea.\n");
    set_alarm(5.0, 0.0, &die(this_player()));
    TO->remove_object();
    return 1;
}

die(object fool) {
    tell_object(fool,"You feel your stomack burns as if hell is within you!!\n");
    tell_object(fool,"You fall down on the floor, struck by the fact, that "+
	      "sulfur is poisonous!\n");
    tell_room(ENV(fool),
	QCTNAME(TP)+" falls down on the floor in pain, holding "+
	"tight around " + HIS_HER(fool)+ " stomach twisting and "+
	"kicking like a dying pig.\n",fool);

    fool->heal_hp(-100000);
    fool->do_die(TO); /* Sorry, fool! */
    TO->remove_object();
}
