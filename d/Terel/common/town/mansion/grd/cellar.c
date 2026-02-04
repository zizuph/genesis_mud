/* cellar.c */
/* janus 921029 */

inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include </sys/money.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

int NOOFTOOLS;
int RND;
reset_room()
{
    RND=4;
    NOOFTOOLS=2;
}
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    set_short("earthen cellar");
    set_long(BS("You are in a dark, dank earthen cellar. Cold water slowly "+
        "drops from the ceiling. The floor is just stamped earth and is "+
       "covered with debris. The only light comes from the opening. There is "+
       "also a dark tunnel that will take you under the mansion. \n"));
    add_exit(MANSION + "grd/ogrd2", "up",0,0);
    add_exit(MANSION + "grd/tunnel1","south",0,0);
    add_item(({"area","ground","floor","cellar"}),
               BS("There is a lot of debris and "+
               "pieces of this and that lying around.\n"));
    reset_room();    
  }
do_search()
{
     object ob4;
     object cash;
     int iii;
     int i1;
     int i2;
     i1 = TP -> query_skill(SS_AWARENESS);
     i2 = i1- random(8);
     if (NOOFTOOLS > 0 && i2 > 0 ){
     iii=random(RND);
     seteuid(getuid(this_object()));
     if (iii==2){
     clone_object("/d/Terel/common/town/mansion/garden/rope")->move(environment(TP));
     write(BS("Hidden beneath some snow you find a rope.\n"));
/*     say(BS(QCTNAME(TP)+"searches the area and finds something.\n")); */
     RND--;
     NOOFTOOLS--;
     if (NOOFTOOLS > 0 ){
        write(BS("You see something glint beneath some debris, maybe there "+
                 "is something more here ?\n"));
     return;
      }
   }
     if (iii==3){
     clone_object("/d/Terel/common/town/mansion/garden/bag")->move(environment(TP));
     write(BS("Hidden beneath some vines you find a bag.\n"));
/*     say(BS(QCTNAME(TP)+"searches the area and finds something.\n")); */
     NOOFTOOLS--;
     RND--;
     if (NOOFTOOLS > 0 ){
        write(BS("You see something glint beneath some debris, maybe there "+
                 "is something more here ?\n"));
      }
     return;
   }
     if (iii==1){
     clone_object("/d/Terel/common/town/mansion/garden/torch")->move(environment(TP));
     write(BS("Hidden beneath some vines you find a a stick that can be "+
              "used as a torch.\n"));
/*     say(BS(QCTNAME(TP)+"searches the area and finds something.\n")); */
     RND--;
     NOOFTOOLS--;
     if (NOOFTOOLS > 0 ){
        write(BS("You see something glint beneath some debris, maybe there "+
                 "is something more here ?\n"));
      }
     return;
   }
     if (iii==0){
     cash = MONEY_MAKE_SC(random(6));
     cash -> move(environment(TP));
     write(BS("Hidden under some debris you find some money.\n"));
/*     say(BS(QCTNAME(TP)+"searches the area and finds some money.\n")); */
     RND--;
     NOOFTOOLS--;
     if (NOOFTOOLS > 0 ){
        write(BS("You see something glint beneath some debris, maybe there "+
                 "is something more here ?\n"));
      }
     return;
   }
   }
     if (i2 < 0){
       write(BS("Maybe you should train your observational skills. \n"));
     }
     return;
   }
