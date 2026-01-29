/*
 * /d/Gondor/anorien/nimrais/trolls/treasurecave.c
 * Modified by Tigerlily April 22, 2004
 *   for ranger recode--cleanse spell scroll
*/

inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/d/Gondor/defs.h"
#include "/sys/money.h"



#ifndef  NEW_RANGERS_OPEN
#define CSCROLL (RANGER_DIR + "spells/obj/cleanse_scroll")
#endif

#ifdef  NEW_RANGERS_OPEN 
#define CSCROLL "/d/Gondor/guilds/rangers/spells/obj/cleanse_scroll"
#endif

int scroll_found,plat_taken;

create_room()
{
  set_short("A small chamber in a hill-troll lair");
  set_long("You are standing inside a dark little sidechamber in the lair of\n"+
    "the hill-trolls. This little cell seems to be used as a treasure cell.\n"+
    "There is a half-rotted, worthless box here. You do however wonder how\n"+
    "the hill-trolls could get hold of their treasures inside this little\n"+
    "cell, as the little hole you entered through is too narrow at least for\n"+
    "the grownup trolls, maybe they used baby trolls for the job. To the east\n"+
    "is the little hole you entered through.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/anorien/nimrais/trolls/cave2","east",0,0);
  add_item(({"ground","floor","cavefloor"}),"@@exa_floor");
  add_prop(ROOM_I_LIGHT,0);
  add_item("hole","The hole looks dark and mysterious, but only a little person would be\n"+
    "be able to enter it.\n");
  add_item("box","@@exa_box");
  add_scoins();
  scroll_found = 0;
}

exa_box()
{
  object coins;
  if (plat_taken) return "The empty box is just about rotted to pieces, so it is worthless.\n";
  seteuid(getuid(this_object()));
  coins = MONEY_MAKE_PC(2);
  coins->move(this_object());
  plat_taken = 1;
  return "The box has just about rotted to pieces, but you find some coins in it!\n";
}

add_scoins()
{
  object coins;
  coins = MONEY_MAKE_SC(random(20)+5);
  coins->move(this_object());
}

exa_floor()
{
  if (scroll_found) return "The only thing you find left on the cave-floor is a little box.\n";
  scroll_found = 1;
  clone_object(CSCROLL)->move(this_object(), 1);
  return "You find an old scroll lying on the cave floor!\n";
}

init()
{
  ::init();
  add_action("enter_hole","enter");
}

reset_room()
{
  if (!present("coins")) add_scoins();
  scroll_found = 0;
}

enter_hole(str)
{
  if (!str) {
    NF("Enter what?\n");
    return 0;
    }
  if (str == "hole" || str == "little hole") {
    if (!test_size()) {
      write("You squeeze yourself through the little hole!\n");
      this_player()->move_living("through the little hole in the east wall",
        "/d/Gondor/anorien/nimrais/trolls/cave2");
      return 1;
      }
    return 1;
    }
  return 0;
}

test_size()
{
  string race;
  race = this_player()->query_race();
  if (race != "hobbit" && race != "gnome" && race != "dwarf") {
    write("You quickly find out that you are too big for the little hole!\n");
    say(QCTNAME(this_player())+" tries to enter the little hole, but is too big.\n",this_player());
    return 1;
    }
  return 0;
}

