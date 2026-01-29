#include "defs.h"

inherit "/std/room";

//    Prototypes
void tom0(object player);
void tom1(object player);
void tom2(object player);
void tom3(object player);

int busy;

create_room() {
    set_short("Trapped in a willow");
    set_long(break_string(
          "You are trapped inside an old, evil tree, "
        + "around you see the remnants of other victims. You remember that "
        + "a man called Tom Bombadil is rumoured to live in the "
        + "area, he is said to have powers to control this forest. "
        + "Perhaps you should try to call him.\n",70));
}

init() {
    ::init();
    add_action("do_call", "call"); 
    add_action("do_call", "shout"); 
}

do_call(str) {
    if (!str || str == "")
        return 0;

    str = lower_case(str);
    if (str != "tom" && str!="bombadil" && str != "tom bombadil")
        return 0;

    write("You call for Tom Bombadil as loud as you can in your cramped position.\n");
    if (busy) write("Nothing happens. You realize you may not be the only "+
                    "one who needs Tom's help.\n");
    else {
      set_alarm(6.0,0.0,&tom0(this_player()));
      busy = 1;
    }
    return 1;
}

void
tom0(object player)  {
    player->catch_msg("Somewhere, in the distance you hear someone singing.\n");
    set_alarm(6.0,0.0,&tom1(player));
}

void
tom1(object player) {
    player->catch_msg("Tom Bombadil arrives, jumping and dancing.\n");
    set_alarm(6.0,0.0,&tom2(player));
}

void
tom2(object player) {
    player->catch_msg("Tom forces the old grey willow-man to release you.\n");
    set_alarm(6.0,0.0,&tom3(player));
}

void
tom3(object player) {
    player->catch_msg("He carries you to his house.\n");
    player->move_living("with Tom Bombadil", STAND_DIR + "tom");
    busy = 0;
}
