inherit "/d/Shire/room";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_room() {
   set_short("Main road.\nThere are two obvious exits: east, west");
   set_long("@@my_view");

   set_noshow_obvious(1);

   add_exit(STAND_DIR + "er2", "east", 0);
   add_exit(STAND_DIR + "er5", "west", 0);
   add_exit(STAND_DIR + "newphouse","north","@@check_enter",1);


}

my_view() {
  int sk1,sk2;
  string str;

  sk1 = this_player()->query_skill(SS_AWARENESS);
  sk2 = this_player()->query_skill(SS_TRACKING);

  
  str = "You are on the great Eastroad. The road is paved and looks\n"
    + "well-kept. If you follow this road to the east, you will\n"
    + "eventually get to Bree. If you go west, you will end up in\n"
    + "Grey Havens. ";

  if((sk1 <= 10) & (sk2 <= 10)) {
    str = str
      + "\nThere are two obvious exits: east, west.\n";
  }
  else {
    str += "To the north you see a small track.\n";
    str = str 
         + "There are three obvious exits: east, west, north.\n";
  }
  return str;
}
    
check_enter() {
int sk1,sk2;
  string str;

  sk1 = this_player()->query_skill(SS_AWARENESS);
  sk2 = this_player()->query_skill(SS_TRACKING);

  if((sk1 <= 10) & (sk2 <= 10)) {
    write("There is no obvious exit north.\n");
    return 1;
  }
  else {
    write("You follow the small track.\n");
    return 0;
  }
}

      

     
