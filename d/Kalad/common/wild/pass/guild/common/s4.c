inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"
#define DROW_GUILD_BIT 1
#define FOURTH_GROUP 4
object guard;
object guard2;
object insignia;

void
create_room()
{
set_short("Entrance to Tier Breche");
set_long("You have reached the top of the stairs, and in doing so, "
	+"reached the mouth of Tier Breche. Before you sprawls an "
	+"immense cavern filled with drow students and their schools. "
	+"To get their though you must first pass the guards of the "
	+"school. If you aren't of the school, you shouldn't try to "
	+"pass. It could be fatal, not that Lloth would mind feasting "
	+"on the blood of intruding non-believers.\n");
add_item(({"student","students"}),"They seem to be students at the school "
	+"and don't want to be bothered.\n");
add_item(({"wall","walls"}),"The walls are carved from black marble "
        +"and are highly polished and carved with spider webs.\n");
add_item(({"floor"}),"The floor is made of a highly polished black "
        +"marble which is highly reflective.\n");
add_item(({"cavern"}),"The cavern is carved out of a stone resembling "
        +"black marble, and is incredibly large. It contains the whole "
	+"Drow Academy and its students.\n");
add_item(({"flame","fire","faerie fire"}),"This is the strange blue "
        +"flame that covers most of the city in an eerie glow. The "
        +"flames are blue, and seem to be alive.\n");
add_item(({"entrance"}),"The entrance of the Tier Breche lies to "
        +"your north.\n");
add_item(({"stairs","stair","step","steps"}),"They are carved from the "
        +"same black marble as the rest of the cavern and are broad "
        +"enough for many people to walk down.\n");
add_exit(DGUILD + "common/s3", "south", 0, 2);
add_exit(DGUILD + "common/s5", "north", "@@is_member", 1);
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
add_prop(ROOM_I_LIGHT,0);
add_prop(ROOM_M_NO_TELEPORT,1);
set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
if(!guard)
        {
guard = clone_object(DGUILD + "npc/guard_spider");
guard->move_living("xxx", TO);
}
if(!guard2)
{
guard2 = clone_object(DGUILD + "npc/guard_spider");
guard2->move_living("xxx", TO);
guard -> team_join(guard2);
        }
}

is_member()
{
    object *ob;

    int pres,i;
if(IS_MEMBER){
return 0;
    }
    if (this_player()->query_guild_name_lay()==GUILD_NAME)
        return 0;

   if (insignia = present("_backflip_", TP)){
        return 0;
    }

    ob = FILTER_LIVE(all_inventory(this_room()));
    pres = 0;
    for (i = 0; i < sizeof(ob); i++){
   if (ob[i]->query_name() == "Spider"){
            pres = 1;
        }
    }
    if (pres == 1){
write("The spider animates and blocks your way!\n");
say(QCTNAME(TP) + " tries to go north but is brutally stopped by the guardian spider!\n");
    }

    return pres;
}
init()
{
::init();
}
