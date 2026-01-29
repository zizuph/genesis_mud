inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define DELAY (random(20) + 10)

//  Prototypes
void init_msg(object player);
void tell1(object player);
void tell2(object player);
void tell3(object player);

create_room() {
   set_short("Dark pit in the downs");
   set_long(break_string(
         "You have fallen into a dark pit. The walls of the pit are "
         + "bending towards the hole you fell through, far above. "
         + "You cannot get a hold of them and cannot climb up.\n",70));

   add_item("hole", "The hole is out of reach for you.\n");

   add_item("wall", break_string(
         "The wall consists of moist, black earth, virtually "
         + "unclimbable.\n",70));
   add_prop(ROOM_I_INSIDE,1);
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
   player->catch_msg("You look around and wonder if there are any exits here at all.\n");
   set_alarm(itof(DELAY),0.0,&tell1(player));
}

void
tell1(object player) {
   if (player && (ENV(player) != TO))
      return;
   player->catch_msg("Hmmm... Maybe it's possible to climb after all...\n");
   set_alarm(itof(DELAY),0.0,&tell2(player));
}

void
tell2(object player) {
   if (player && (ENV(player) != TO))
      return;
   player->catch_msg("The walls of the pit are caving in...\n");
   set_alarm(itof(DELAY),0.0,&tell3(player));
}

void
tell3(object player) {
   if (player && (ENV(player) != TO))
      return;
   player->catch_msg("You spot a hidden exit and crawl away from this creepy place.\n");
   player->move_living("crawling", DOWNS_DIR + "pit");
}

do_climb(str) {
   if (str == "wall" || str == "to hole" || str == "walls")
      {
      write(break_string(
            "You try to climb the moist wall, but halfway you lose your "
            + "grip and fall back in the pit.\n",70));
      say(QCTNAME(this_player()) + " make an attempt to climb the walls,\n"
         + "but falls back into the pit...\n");
      return 1;
   }
}
