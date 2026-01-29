inherit "/std/monster";
inherit "/std/act/action";

#include "defs.h"

#include <stdproperties.h>
#include <macros.h>

#define LOC_HUT 1
#define LOC_OUTSIDE 2
#define LOC_BOAT 3
#define TIME_OUT 20.0

int loc=LOC_HUT;
int alarm_h=0;

void create_monster()
{
 set_name("fisherman");
 set_race_name("fisherman");
 set_adj("strong");
 set_adj("robust");
 set_stats(({200,200,200,200,200,200}));

 add_prop(OBJ_M_NO_ATTACK,"You don't dare , he's too strong!\n");

 set_act_time(1);
 add_act("say I've seen them!");
 add_act("peer susp");
 add_act("say Their warships are fast , but I can sneak by them...");
 add_act("say They have an outpost on that island...");
 add_act("worry");

 add_ask(({"they","karg","kargs"}),"@@answer_they");
 add_ask(({"warship","warships"}),"@@answer_warships");
 add_ask("island","@@answer_island");
 add_ask("outpost","@@answer_outpost");
}

void init_living()
{
 ::init_living();
 add_action("nod","nod");
}

string answer_they()
{
 if(loc!=LOC_HUT) return 0;
 command("say Kargs... I've seen their warships patroling around "+
   "they island..");
 return "";
}

string answer_warships()
{
 if(loc!=LOC_HUT) return 0;
 command("say I've seen lots of warships patroling around the isnald.");
 command("say But I think i can pass them by without being noticed...");
 return "";
}

string answer_island()
{
 if(loc!=LOC_HUT) return 0;
 TP->add_prop("_live_i_asked_fisheman",1);
 command("say Yes... I've been there... they have an outpost on that "+
   "island...");
 command("say If you wish me to take you there just give me a nod...");
 command("say But remember... it's very dangrous out there... If we "+
   "get noticed by patrol I doubt they will spare our lives!");
 return "";
}

string answer_outpost()
{
 if(loc!=LOC_HUT) return 0;
 command("say Outpost is located at the other side of the forest...");
 command("say I've got as close as I could stay unnoticed...");
 return "";
}

void return_to_hut()
{
 command("shrug");
 command("hut");
 loc=LOC_HUT;
}

int nod()
{
 if(loc!=LOC_HUT) return 0;
 if(!TP->query_prop("_live_i_asked_fisheman")) return 0;

 write("You nod at fisherman.\n");
 command("say Well , as you with , I will wait for you outside...");
 command("out");
 loc=LOC_OUTSIDE;
 alarm_h=set_alarm(TIME_OUT,0.0,&return_to_hut());

 return 1;
}

void go_boat()
{
 remove_alarm(alarm_h);
 tell_room(ENV(TO),QCTNAME(TO)+" boards the boat.\n");
 TO->move_living("M",INSIDE_BOAT);
 ENV(TO)->i_am_the_fisherman(TO);
 tell_room(ENV(TO),QCTNAME(TO)+" arrives.\n");
 (INSIDE_BOAT)->start_moving(1);
}

