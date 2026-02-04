/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#define PATH "/d/Terel/mecien/valley/guild"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define START "/d/Terel/mecien/valley/guild/entry"

init()
{
    add_action("enter", "enter");
    add_action("read", "read");
    ::init();
}

id(str) {
    return str == "arch";
}

enter(str)
{
 if (!id(str))
     {
	 write("Enter what?\n");
	 return 1;
     }
   write("The arch will not let you pass.\n");
  return 1;
 write("As you pass under the arch you see its runes glow softly blue.\n");
 say(QCTNAME(this_player()) + " passes through the ancient arch.\n");
 say("The runes on the arch emanate a blue light.\n");
 this_player()->move(START);
 this_player()->command("look");
 return 1;
}
read(string str){
 if (str!="arch" && str!="inscription") return 0;
 if (this_player()->query_skill(SS_LANGUAGE) < 15)
 {
  write("You cannot understand the runes.\n");
  say(QCTNAME(this_player()) + " looks up at the arch.\n");
  return 1;
 }
 write("The runed arch reads:\n\n" +
       "GLORY BE UNTO THE ANCIENTS\n" +
       "Those who seek Wisdom and Truth shall find life\n" +
       "in the Ancients, for the Mystery of Eternity resides\n" +
       "with them. Enter ye in and be lifed up.\n");
 say(QCTNAME(this_player()) + " looks up at the arch.\n");
 return 1;
}


create_room(){
    
    set_short("Arch of The Shrine");
    set_long(
	     "Towering twenty feet high stands a monumental arch, a stone\n"
	     +"guardian that leads into a misty stone courtyard. This place,\n"
	     +"like darkned ruins, stands at the edge of the world to haunt\n"
	     +"the unbelieving, to beckon them into the arms of mystery, to\n"
             +"shroud them in doubt and fear.\n" 
             +"Here, in front of the arch, a long stair descend into the mist\n"
             +"and clouds to the east. Far below a valley.\n");
    
    add_exit("/d/Terel/mecien/valley/guild/stair2", "east", 0);
    
    add_item(({"archway","arch"}),
	     "This ancient arch is inscribed with mystic writings.\n");
}

int guarded(){
    object rat;
    rat=present("rat");
    if(rat && rat->query_name()!="corpse"){
	write("The nasty rat guards the way.\n");
	say("The rat keeps "+QCNAME(this_player())+" from going any further.\n");
	return 1;
    }
    return 0;
}  
