inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/dark/"
#define TP this_player()

void
init(){
add_action("blow_horn", "blow", 0);
::init();
}

int
blow_horn(){
mixed exits;
int i, fill;
string mess;
object room;

room = environment(TP);
exits = room->query_exit();

if(file_name(room)!="/d/Terel/mecien/dark/chasm")
{
  write("You sound the horn.\n");
   say(QCTNAME(TP) + "sounds a black horn.\n");
  return 1;
}
fill = 0;
for (i = 0; i < sizeof(exits); i += 3)
{
if(exits[i + 1] == "bridge")
  fill = 1;
}

if (fill == 1){
mess = " sounds a black horn and the bridge rises.\n";
write("You sound the black horn and the bridge is raised.\n");
room->remove_exit("bridge");
room->remove_my_desc();
}
else
{
mess = " sounds a black horn, its eerie cry reaches out across\n"
  +"the chasm. A long bridge is lowered from the fortress and\n"
  +"spans the chasm.\n";
write("You sound the horn and it cries out into the darkness.\n");
write("A long bridge is lowered from the fortress.\n");
room->add_exit("/d/Terel/mecien/dark/outpost/gates", "bridge", 0);
room->add_my_desc("A long narrow bridge spans the chasm.\n");
}

say(QCTNAME(TP) + mess);
return 1;
}


create_object(){

set_name("horn");
set_adj("black");
set_short("black horn");
set_long("A long twisted black horn, it appears to have been made\n"
  +"from a large dragons horn. It is carved and inscribed\n"
   +"with runes of silver. The mouthpiece is silver plated.\n");

}
