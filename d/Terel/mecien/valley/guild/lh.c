/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/valley/guild/"

reset_room(arg){

object obj;

if(present("teacher")) return 0;
obj=clone_object(PATH + "lt");
obj->move(this_object());

}

create_room(){

set_short("Inner Chapel");
set_long(
"This small chamber, is the inner hall of the chapel, its walls\n"
+"are white marble, as is the floor and ceiling. A large table of\n"
+"white stone fills most of the chamber, upon which is a huge candle\n"
+"and a large silvery tome.\n"
);

add_item("candle", "It is a huge silvery candle.\n");
add_item("table", "It is a large round stone table, white and inscribed\n"
+ "with a star and circle.\n");
add_item("tome", "It is an ancient silver coloured tome.\n");
add_cmd_item("tome", "read", "@@read_tome");
add_exit(PATH + "lchapel", "west", 0);

reset_room();

}

read_tome(){
if(this_player()->query_guild_name_occ()!="The Ancient Mystic Order"){
write("The words are obscure and confusing.\n");
return 1;
}
write("Life is the Power that abides through all things, we seek it\n"
+"through Mystery. For through Life shall we call to the Ancients\n"
+"and they shall grant us their Powers. Our healing comes through it,\n"
+"as does our ways to the world beyond. Let only those of Truth know\n"
+"our healing hands, for then shall Justice abide in us.\n"
);
return 1;
}


