#include "defs.h"

object ar;

CONSTRUCT_ROOM {
    set_short("The Armoury");
    set_long("You're in the Armoury. A whole lot of scrap lies scattered "+
	     "around here; most of it is destroyed, however. Unfinished "+
	     "swords, bent iron-plates and other things bear witness to a "+
	     "hasty abandoning of this place.\n");
    add_item(({"scrap","swords"}),
	     "They are useless.");
    add_item(({"iron-plates", "plates", "armours"}), "They are all useless and not worth taking.");
    WEST("knightsh");
    NORTH("shieldch");
//    TO->reset();
}

/*
RESET_ROOM 
{
    if (!ar || (environment(ar) && !present(ar)))
    {
	    ar = clone_object(MORIA_ARM+"dwarf_plate");
        clone and move the armour here.
        room_add_object(MORIA_ARM+"dwarf_plate");
    }
}
*/
string
exa_plates()
{
    if (objectp(ENV(ar)))
	return "They are all useless.";
    else {
	ar->move(TO);
	return "You notice one piece of armour which might be usable.";
    }
}


/*
      ar->set_name("dwarf-plate");
      ar->set_short("A dwarfen platemail");
      ar->set_long("A strong, good-looking platemail made of strong iron.\n");
      ar->add_id("platemail");
      ar->set_value(1200);
      ar->set_weight(3);
      ar->set_ac(3);
      ar->set_type("armour");
*/
