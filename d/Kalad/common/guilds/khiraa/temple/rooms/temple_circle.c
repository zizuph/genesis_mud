#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In the Circle Chamber");
    
    set_long("\n   You have entered a large chamber filled with "+
    "eerie green light. The walls are made of black stone, and the "+
    "ceiling vaults up high here. The green light seems to be "+
    "coming from the walls, but you are not sure.\n"+
    "   In the center of a room stands a circle of stone chairs. At "+
    "the north end of the circle, a large and ornate master chair "+
    "stands, while a dozen or so wooden benches are lined up against "+
    "the sides of the walls.\n\n");
    add_item("chairs","The stone chairs are where the circle members "+
    "sit to discuss issues of the Khiraa.\n");
    add_item(({"chair","master chair","ornate chair"}),"This is "+
    "where the head of the circle sits.\n");
    add_item("benches","The benches are made of old wood, and are "+
    "there for those who wish to watch the circle speak.\n");

    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, and "+
    "they seem to glow with a magical eerie green light.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    clone_object(KHIRAA_DIR(temple/doors/circledoor2))->move(TO); 
    clone_object(KHIRAA_DIR(temple/obj/kboard))->move(TO);
    add_exit(KHIRAA_DIR(temple/rooms/circle_private),"north","@@check@@",-1);

}

int
check()
{
    if(TP->query_circle() < 1)
    {
        write("Only members of the Circle may enter the private chambers.\n");
        return 1;
    }
    return 0;
}

