inherit "/std/room.c";

#define PATH "/d/Terel/LoD/monster/"
object monster;
reset_room(){
if(present("knight"))return;

monster=clone_object(PATH + "darkness_knight");
    monster->equip_me();
    monster->equip_actions();
monster->move(this_object());
}
#include "/d/Terel/common/terel_defs.h"
create_room() {
    set_short("Road");
    set_long("This is a simple stony road that leads out across a\n" +
             "great moor. Patches of ice and snow are sprinkled out\n" +
             "upon the rocky grass. The sky is dreary, the wind cold.\n" +
	     "The road leads south and northeast.\n");
    add_exit("/d/Terel/common/road/road2", "northeast",0);
    add_exit("/d/Terel/common/road/road4", "south",0);
reset_room();
}

