/* File:          /d/Khalakhor/ship/macdunn/wbeach/bbase.c
 * Creator:       Zima
 * Date:          May 15, 1998
 * Modifications:
 * Purpose:       This is the base room for a line of beach rooms along
 *                the coast of MacDunn, west of the pier. Accessible
 *                only by swimming west from beneath the pier and
 *                climbing onto the rocks (from ../shore0.c)
 * Related Files: /d/Khalakhor/ship/macdunn/
 * Comments:
 */
 
#pragma save_binary
#pragma strict_types
 
inherit "/d/Khalakhor/std/room";
#include "local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#define  RM_MAX 10
inherit HERBSEARCH;
public void washup_corpse();
public void washout_corpse();
 
 
string *herbs=HERBMASTER->query_herbs(({TERRAIN_SALTBEACH,}));
int    loc;
int    rock;
object stone;
int    walarm=0;
int    palarm=0;
 
public int    query_walarm()     { return walarm; }
public int    query_palarm()     { return palarm; }
public int    query_loc()        { return loc;    }
public object query_pointer()    { return TO;     }
 
public void
reset_room()
{
    rock = 0;
    set_searched(0);
}
 
public void do_washup_corpse() {
   tell_room(TO,"A great wave rises over the harbour and crashes into "+
                "the shore!\nThe carcass of a small whale rolls onto "+
                "the beach!\n");
   seteuid(getuid());
   (clone_object(BEACH_DIR+"whcorpse"))->move(TO);
}
 
public void do_washout_corpse() {
   object whale=present(WH_CORPSE,TO);
   if (!objectp(whale)) return;
   tell_room(TO,"A great wave rises over the harbour and crashes into "+
                "the shore!\nThe carcass of the small whale is washed "+
                "out to sea!\n");
   whale->remove_object();
}
 
public int washup_corpse()
{
   object rm;
   loc=random(RM_MAX-1)+2; //pick from b2.c through bRM_MAX.c
   rm=((BEACH_DIR+"b"+loc)->query_pointer());
   if (objectp(rm)) {
      rm->do_washup_corpse();
      walarm=set_alarm(1800.0,0.0,&washout_corpse());
      /*
      log_file("washup","up  b"+loc+".c "+ctime(time())+"\n");
      */
   }
   else
      {
      loc=0;
      /*
      log_file("washup","error b"+loc+".c "+ctime(time())+"\n");
      */
      }
   return loc;
}
 
public void washout_corpse() {
   object rm=((BEACH_DIR+"b"+loc)->query_pointer());
   rm->do_washout_corpse();
   walarm=set_alarm(300.0,0.0,&washup_corpse());
   /*
   log_file("washup","out b"+loc+".c "+ctime(time())+"\n");
   */
}
 
public void
create_beach_room()
{
    set_short("on a rocky shore");
    set_long("   You are on a rocky beach which is the narrow shore of "+
       "Cala Fasgadh near Port MacDunn. The pounding surf beats at "+
       "the shoreline to the south as the waves crash continuously "+
       "upon the sharp rocks which portrude all around. Cliffs rise "+
       "high to the north, leaving only a narrow strip of beach on "+
       "which you can walk.\n");
 
    add_item(({"cliff","cliffs"}), "Forged by the pounding seas "+
       "with razor sharp edges, the cliffs rise straight up "+
       "from the shore to the north, dashing any hope of climbing "+
       "them or going anywhere except along the narrow beach.\n");
    add_item("pier","You can see it far to the east, but the rocks "+
       "prevent you from walking there.\n");
    add_item("boats","There are a few boats in the tumultuous harbor "+
      "to the south.\n");
    add_item("boat","Each boat is different.\n");
    add_item(({"water","salt water","salty water"}),"The water, which " +
      "is the essential element of the harbour, is salty. It is " +
      "rather clean, however.\n");
    add_cmd_item(({"water","salt water","salty water","clean water",
        "the water","the salt water","the salty water",
        "the clean water","from the harbour"}), ({"drink","taste",
        "gulp","swallow"}),"You can not reach it from on the beach.\n");
    add_item(({"harbour","oceanic harbour","cala","cala fasgadh"}),
      "The harbour extends to the southwest, where it meets Lear " +
      "Min, the sea, which cannot be seen from here.\n");
    add_item(({"shore","rocky shore","beach"}),"The rocks on the shore "+
      "are sharp and dangerous, though a narrow strip of beach lies "+
      "between them and the pounding surf.\n");
    add_item("rocks","The rocks have razor-sharp edges and might " +
      "cut anyone attempting to pass through them.\n");
    add_item(({"surf","waves"}),"The waves are unusually high for a "+
       "peaceful harbour. They pound violently against the shore.\n");
    add_item("sky","The semi-cloudy sky above you is a typical " +
      "coastal sky.\n");
    add_item("clouds","The clouds above are grey and streaky.\n");
    add_item("cloud","Each cloud looks about the same, although " +
      "location and size differ.\n");
    add_cmd_item(({"water","sea","harbor","into water","into sea",
        "into harbor","off rocks","off beach","off shore"}),
        ({"enter","swim","dive"}),
        "The pounding surf is too dangerous to enter the water here.\n");
    add_cmd_item(({"cliff","cliffs","rocks","up","up rocks","up cliff",
       "up cliffs"}),"climb","@@go_rocks");
    add_cmd_item(({"rocks","sharp rocks","rock","sharp rock"}),
      ({"chip","break","crack","smash"}),"@@get_rock");
 
 
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SALTBEACH);
/* SET_UP_HERBS is causing a load error!!???
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
      ONE_OF(herbs)}),({"water","here"}),2);
*/
 
    reset_room();
 
    seteuid(getuid());
}
 
public void create_khalakhor_room()
{
   create_beach_room();
   washup_corpse();
}
 
public string
go_rocks()
{
    write("You ignorantly try to climb up the rocks of the cliff, but "+
          "slip and crash down onto the beach. You are injured on the "+
          "edges of the rocks.\n");
    say(QCTNAME(TP) + " attempts to climb up the rocks of the cliff but "+
          "slips and falls back onto the beach.\n");
    TP->heal_hp(-50);
    if (TP->query_hp() <= 0)
        TP->do_die();
    return "";
}
 
public int
get_rock()
{
    if (this_player()->query_weapon(-1) == ({}))
    {
        write("You are unable to break the rocks without a tool!\n");
        say(QCTNAME(TP) + " attempts to break the rocks lining the shore " +
          "without a tool, and fails.\n");
        return 1;
    }
 
    if (rock > 4)
    {
        write("Try as you might, you are unable to break any of the " +
          "rocks.\n");
        say(QCTNAME(TP) + " attempts to break the rocks lining the shore, " +
          "but " + HE + " finds that the rocks will not yield to " +
          HIS + " effort.\n");
        return 1;
    }
 
    write("You break a piece of stone from the rocks lining the " +
      "shore!\n");
    say(QCTNAME(TP) + " breaks a piece of stone from the rocks lining " +
      "the shore!\n");
    stone = clone_object(COM_OBJ + "stone");
    stone->move(this_object(), 1);
    rock = rock + 1;
    return 1;
}
 
public int filter_beach(object ob)
{
   return ((environment(ob)) &&
           (wildmatch(BEACH_DIR+"*", file_name(environment(ob)))));
}
 
public void do_pound_surf()
{
   object *bplayers = filter(users(), filter_beach);
   if (sizeof(bplayers)>0)
      {
      bplayers->catch_tell(
         "A great wave rises over the harbour and crashes into the shore!\n");
      palarm=set_alarm(20.0,0.0,&do_pound_surf());
      }
   else
      palarm=0;
}

public void start_pound_surf()
{
   if (palarm) return;
   palarm=set_alarm(10.0,0.0,&do_pound_surf());
}
