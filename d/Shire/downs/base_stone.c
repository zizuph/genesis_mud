/*
 * Base file for the Barrow downs
 * Original concept and area by Dondon, October 1993
 * Expanded and enlarged by Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

#define DELAY (random(3) + 2)
static string pit_exit;

//  Prototypes
void init_msg(object player);
void tell1(object player);
void tell2(object player);
void tell3(object player);
void set_pit_exit(string str){ pit_exit = str; }
void create_stone_room() {}


public void
//create_area_room()
create_room()
{
    set_short("Inside a dark pit of a Barrow");
    set_long("The earth suddenly gives way as you fall into a " +
        "dark pit. The dark, dank earth looks impossible to climb " +
        "out of.\n");
    add_item(({"hole","pit"}),
        "The hole is made of soft dirt, making it impossible to " +
        "climb out of.\n");
   
    add_item(({"wall", "walls"}),
        "The wall consists of moist, black earth, which crumble " +
        "the more you dig\n");
    add_item(({"earth", "dark earth", "black earth", "soft dirt", "dirt"}),
        "The earth is dark and moist. It crumbles under your feet " +
        "and hands, making digging nearly impossible.\n");
//   add_prop(ROOM_I_INSIDE,1);
    create_stone_room();
}

init() {
   ::init();
   set_alarm(itof(DELAY),0.0,&init_msg(this_player()));
   add_action("do_climb", "climb");
}

void
init_msg(object player) {
   if (player && (ENV(player) != TO))
      return;
   player->catch_msg("The dark pit shudders as it settles.\n");
   set_alarm(itof(DELAY),0.0,&tell1(player));
}

void
tell1(object player) {
   if (player && (ENV(player) != TO))
      return;
   player->catch_msg("Suddenly the pit collapses some more, and " +
        "you fall deeper into the pit.\n");
   set_alarm(itof(DELAY),0.0,&tell2(player));
}

void
tell2(object player) {
   if (player && (ENV(player) != TO))
      return;
   player->catch_msg("Mists and dust rise up from the pit as it " +
        "rumbles and settles again.\n");
   set_alarm(itof(DELAY),0.0,&tell3(player));
}

void
tell3(object player) {
   if (player && (ENV(player) != TO))
      return;
   player->catch_msg("A dark, hidden exit appears, leading into " +
        "the depths of the barrow.\n");

   player->move_living("crawling.",pit_exit);
}

do_climb(str) {
   if (str == "wall" || str == "to hole" || str == "walls" || str == "up" || str == "out")
      {
      write("You try to climb the moist wall, but halfway you lose " +
            "your grip and fall back in the pit.\n");
      say(QCTNAME(this_player()) + " make an attempt to climb the walls,\n"
         + "but falls back into the pit...\n");
      return 1;
   }
}
