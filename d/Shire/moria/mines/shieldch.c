#include "defs.h"

object shield;

CONSTRUCT_ROOM {
    set_short("Shield chamber.");
    set_long("This is the shield chamber. Some of the finest knight-shields "+
	     "have been placed here. Strangely it is that this place looks "+
	     "exactly like it did many years ago. It surely is an evidence "+
	     "of the power of the King, seeing that the trolls do not enter "+
	     "here, trying to destroy whatever they find breakable.\n");
    add_item("shields","They are placed out of reach.");

    SOUTH("armoury");
    WEST("wardrobe");
    reset();
}

RESET_ROOM {
/*
    if (!shield || !present(shield)) {
	shield = clone_object("/d/Shire/rogon/sdir/obj/shield");
	shield->move(this_object());
    }
*/
}	
    
/*
      shield->set_name("shield of durin");
      shield->set_short("A magnificient circular shield");
      shield->set_long("This shield was made for the knights of Durin, "+
		       "the King under the Mountain.\n");
      shield->set_value(600);
      shield->set_weight(1);
      shield->set_ac(1);
      shield->set_type("shield");
*/
