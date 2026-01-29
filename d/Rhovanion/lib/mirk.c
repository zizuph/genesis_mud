#pragma save_binary

inherit "/std/room"; 
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
 
 /* This is the generic Mirkwood room file.
  * Coded by Randor in June '93
  */
 

 /* Protos */
void create_mirk() {}
 
string long_desc, roomtype, rivername;
 

void
create_room()
{
    rivername == "";
    set_short("@@my_short@@");
    ::set_long("@@my_long@@");
    add_item(({ "tree", "trees" }), BS("There are gloomy trees all around "
     + "you. Their trunks are black and the branches are covered by "
     + "green slime...\n"));
    add_item(({ "web", "webs", "spiderwebs", "spiderweb", "spider web",
        "spider webs" }), BS("Here and there you see big spider webs. " +
        "You wonder how big spider can weave such webs.\n"));
    set_noshow_obvious(1);
    create_mirk();
}
 
string
my_long()
{
    object server;
    string text;
    server = find_object("/d/Rhovanion/lib/mirkserver");
    if (!server) return BS(process_string(long_desc));
        /* The room will work even if the server is broken... */
    text = server->get_long(roomtype);
    return BS(process_string(text + long_desc));
}
 
 /* Notice that this is the default short function, but you can
  * define your own if you want to.
  */
 
string
my_short()
{
    switch(roomtype) {
        case "forest": return "Lost in the Mirkwood";
        case "clearing": return "On a clearing in the Mirkwood";
        case "river": return "By the river";
    }
}
 
void
init()
{
    ::init();
    add_action("check_time", "time");
}
 
mixed
add_monster(string monstertype)
{
    if (!monstertype || monstertype == "") return 0;
    return "/d/Rhovanion/lib/mirkserver"->add_monster(monstertype);
}
 
int
check_time()
{
    object server;
    server = find_object("/d/Rhovanion/lib/mirkserver");
    if (!server) {
        write(BS("You try to determine the time with no success. In fact "+
            "you realize that it's a bug and you should report it.\n"));
        return 1;
    }
    return server->check_time(roomtype);
}
 
void
set_long(string desc)
{
    long_desc = desc;
}
 
void
set_roomtype(string str)
{
    switch(str) {
        case "clearing":
        case "river":
            roomtype = str; break;
        default:
            roomtype = "forest"; break;
    }
}
 
string
query_roomtype() { return roomtype; }
 
void
set_rivername(string str)
{
    rivername = str;
}
 
string
query_rivername() { return rivername; }
 
 /* This function returns the time of the day. */
 
string
tod()
{
    object clock;
    clock = find_object("/d/Gondor/elessar/lib/clock");
    if (!clock) return "noon";
    return clock->query_time_of_day();
}
 