inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>

#define GUILD "The Ancient Mystic Order"
#define PATH "/d/Terel/mecien/valley/guild/"

create_armour(){

set_name("talisman");
add_adj("silver");
set_long("It is a mysterious talisman, shaped like a serpent\n"
+ "coiled about a crystal of deep purple.\n");
}

init(){
add_action("speech", "speech");
::init();
}

speech(string msg){
   object *userlist, sec, inv;
   int i, n;
   string dom;
   
   if(this_player()->query_guild_name_occ()!=GUILD){
   write("Nothing happens.\n");
      return 1;
   }
   userlist = users();
   for (i = 0; i< sizeof(userlist); i++)
   tell_object(userlist[i], 
"Santa Claus tells you: MERRY CHRISTMAS!!!\n");
   return 1;
}

