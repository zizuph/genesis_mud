inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

init(){
add_action("pray", "pray");
}

pray(string str){
   string name;
if(!str){
  TP->catch_msg("You pray for a time in this solemn place.\n");
  say(QCTNAME(TP) + " prays in solemnity.\n");
   name = TP->query_name();
   set_alarm(6.0, 1.0, "spirit", name);
      return 1;
}

}

create_room(){

set_short("Central Sanctuary");
set_long(
"Ancient stone monoliths forming a ring, perhaps in some special" +
" pattern, but now unknown to all. Long ago they were carved with strange " +
"letters and symbols, but now nearly worn away, faded with the passing ages. " +
" Beautiful ivy grows up and over each of the twelve stones, like mysterious " +
"protection, warding them in their living graceful leaves. " +
"In the center of the stones is a white pedestal.\n"
);

add_exit("/d/Terel/mecien/isle/entry", "out", 0, 0);

add_cmd_item("ivy", "pick", "@@pick");
add_item(({"white pedestal", "pedestal"}), "It is made of white stone carved" +
" and patterned with silvery four-pointed stars.\n");
add_item("ring", "The stones are set this way, as to form this ancient circle.\n");
add_item("ivy", "It is very mysterious, a strange reddish hue.\n");
add_item(({"monoliths", "stones"}), "They form a ring. Made of a dark " +
"gray stone, ancient and crumbling. Once carved with letters and symbols " +
"long since faded. A growth of ivy covers them. They are ten feet " +
"tall and half as thick, placed in a tight circle.|n");
}

spirit(string name){

object ob, caller;
 UID;
   caller = find_living(name);
  ob = clone_object("/d/Terel/mecien/isle/spirit");
   ob->add_prop("caller", name);
  ob->move(ENV(name));
tell_room(ENV(ob), "A soft wind rushes through this place.\n");
}

