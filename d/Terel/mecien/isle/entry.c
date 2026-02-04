inherit "/std/room";
#include "/d/Terel/mecien/isle/defs.h";
#include <macros.h>


init(){
add_action("make", "make");
}

make(string str){
if(!str) return 0;
if(str == "sign"){
    TP->catch_msg("You trace an ancient symbol in the air.\n");
   TP->catch_msg("The ivy parts and you pass within.\n");
TP->move_living("traces an ancient symbol in the air, suddenly the ivy opens and " +
     TP->query_name() + " passes through.\n", "/d/Terel/mecien/isle/center", 0);
   return 1;
   }
}

create_room(){

set_short("Isle");
set_long(
"Strange and ancient stone monoliths rise up here amidst the trees, " +
"making passage beyond impossible. A huge mass of ivy hangs down from the " +
"stones, mysterious and beautiful.\n"
);

}

