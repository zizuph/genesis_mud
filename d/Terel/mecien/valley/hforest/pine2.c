inherit "/std/room";
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/hforest/"

create_room(){
set_short("Dark Pine Forest");
set_long(
"All about great dark pines rise up, like shadowy enemies prepared to\n"
+"do battle with any who oppose them. They sway in the winds, frosted\n"
+"with a glaze of snow and ice.\n"
+"A large black stone sits under the pines.\n"
);

add_item("stone", "It is a large black stone with red lettering.\n");
add_cmd_item("stone", "read", "@@read");
add_item("trees", "They are dark pines, frosted with snow and ice.\n");
add_item("pines", "They are great dark trees, conifers of many ages.\n");

add_exit(PATH + "forest4", "south", 0);

}

read(){
if(this_player()->query_guild_member_occ("The Ancient Mystic Order")){
  write("You are struck with horrifying pain!\n");
   write("Evil powers surge through your being.\n");
   write("You feel weak.\n");
   say(QCTNAME(this_player()) + " looks upon the stone and collapses.\n");
this_player()->set_mana(1);
this_player()->heal_hp(-10);
return 1;
}

write("May the Ancients be cursed forever. The Shadow of the Beast preside over them.\n");
  write("In the Beast is Truth, Life and Hope.\n");
return 1;
}

