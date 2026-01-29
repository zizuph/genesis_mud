inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
object ob1;
object ob2;

void
create_room()
{
    set_short("Sewers");
    set_long("The sewer leads northward, darkness forming the path. "
        +"The environment seems to be plagued with darkness, a clinging "
        +"darkness which grabs at your clothing, and plots unspeakable "
        +"evils. The walls aid in navigation by leading on into the "
        +"dark, and a strange odor seems to emanate from everything "
        +"in the area. It is not an odor of filth but of evil, "
        +"uninhibited, raw evil. There is a hole here leading "
        +"into a tunnel, which you see nothing but darkness "
        +"within.\n");
    
    add_item("hole", "A dark hole leading down into a tunnel below.  " +
        "It has been covered over by a heavy iron grate.\n");
    add_item("grate", "A sturdy iron grate covering over a dark hole " +
        "which leads down into a tunnel below.  It doesn't look like " +
        "it can be opened.\n");
    add_cmd_item(({ "grate", "iron grate" }), "open", "It won't budge!\n");

    add_item(({"wall","walls"}),"The walls are slick with a shiny fungus "
        +"and condensation from the damp sewer.\n");
    add_item(({"odor"}),"The odor is uncharacteristic of any sewer you "
        +"have ever been in, almost alien to this place. "
        +"But you aren't really an expert on sewers, so "
        +"you can't be sure.\n");
    add_item(({"fungus"}),"This is a shiny, almost luminescent fungus. "
        +"it is shiny, and slightly glowing, but not "
        +"enough for the naked eye to see by.\n");
    add_exit(TRADE(sewers/s3),"south");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_NO_TIME_DESC,1);
    set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
    if (!ob1 || !ob2)
        {
        ob1 = clone_object("/d/Kalad/common/trade/thief.c");
        ob1 ->move_living("xxx", this_object());
        ob2 = clone_object("/d/Kalad/common/trade/thief.c");
        ob2 ->move_living("xxx", this_object());
        ob1->team_join(ob2);
    }
    
}
