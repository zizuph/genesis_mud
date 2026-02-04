/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* room2.c
   Mort 911004 */

inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define TP this_player()
/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

init(){
add_action("knock","knock");
::init();
}

create_room() {
    object sdoor1;

    set_short("Entry");
    set_long("A gothic monument, a grand shrine built in the midst\n" +
	     "of the mountains. This is a great stone hall, tightly fit\n" +
             "between the mountain rifts. An ancient place, it has stood\n" +
             "here for countless ages, weathered and beaten, but remaining\n" +
             "still. Of strange design, it is tiered by stone rings that\n" +
             "form an immense dome.\n" +
             "This area is the courtyard and entry, which is built from\n" +
             "immense blocks of stone. There are dozens of marble columns\n" +
             "that circle the area, an archway out to the east.\n");

    sdoor1=clone_object("/d/Terel/mecien/valley/guild/sdoor1");
    sdoor1->move(this_object());
    sdoor1->set_key(7777777);

  add_item("dome", "It must be the central hall of the great shrine.\n");
  add_item("columns", "These many columns of marble circle the stone\n"
  + "courtyard like an immense fence.\n");
  add_item("blocks", "The structure had been fashioned of these great stones. It\n"
   + "is a wonder who could have built this place.\n");
  add_item(({"monument", "shrine", "structure"}),
   "It is an ancient and gothic place, it stands here throughout\n"
    + "the ages as a symbol of the triumph of wisdom.\n");
   add_cmd_item("star", "touch", "@@touch");
   add_item("star", "A luminous silver four-pointed star. It has been\n"
    + "placed upon the door like a mystical seal.\n");
    add_exit("/d/Terel/mecien/valley/guild/pool", "south", 0);
    add_exit("/d/Terel/common/road/cornerstone","east",0);
/*
    add_exit("/d/Terel/mecien/valley/guild/stair3", "east", 0);
*/
    add_item( ({ "stone arch" , "arch" }) , 
     "This stone arch stands twenty feet high, runed with ancient letters.\n");

}

touch(){

if(this_player()->query_alignment()<20){
   write("The star burns you with a holy light.\n");
   this_player()->heal_hp(-10);
  return 1;
}
if(this_player()->query_guild_name_occ()!="The Ancient Mystic Order"){
  write("It is smooth and silver. You sense a mystic peace.\n");
  return 1;
}
write("The star emits a pale silver glow.\n");
  say(QCTNAME(this_player()) + " disappears into an eerie mist.\n");
write("You are enveloped in a eerie mist.\n", TP);
this_player()->move("/d/Terel/mecien/valley/guild/chamber");
tell_room(environment(this_player()), "A mist takes shape.\n");
return 1;
  

}

knock(){
   object room, dk;
  if(!present("protector_ring", TP)){
   write("Your knock quietly passes into nothingness.\n");
   say(QCTNAME(TP) + " knocks in vain upon the door.\n");
  return 1;
   }
write("You knock upon the doors to the sacred shrine.\n");
say(QCTNAME(TP) + " knocks upon the doors.\n");

  room = find_object("/d/Terel/mecien/valley/guild/chamber");
   dk = find_living("cirthes");
   if(present(dk, room)){
  set_alarmv(4.0, -1.0, "fetch", ({ TP, dk, room }));
   return 1;
}
   set_alarm(3.0, -1.0, "nobody", TP);
   return 1;
}

nobody(object me){
  me->catch_msg("No one seems to be attending the door.\n");
}

fetch(object me, dk, room){
  me->catch_msg("The door opens quickly and you are ushered in.\n");
   tell_room(environment(me), "The door opens momentarily and " + QCTNAME(me) +
   " disappears within, just before the door closes.\n", me);
me->move_living("M", room);
   tell_room(room, QCTNAME(dk) + " opens the door and ushers someone in, quickly closing it afterwards.\n", me);
dk->command("bow humb");
dk->command("say Greetings protector");
}

/*
 * Function name:
 * Description  :
 */

