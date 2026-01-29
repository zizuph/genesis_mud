inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_room()
{
    set_short("The Kabal Museum of Art");
    set_long("You are greeted by a cool breeze as you step into "+
    "this large, vaulted ceiling building. The walls are made of "+
    "white stone, and there are windows along the walls letting "+
    "beams of sun shine down. All around you, you see many tables "+
    "and stands with glass domes on them. Paintings and numerous "+
    "decorations line the walls. This vast museum stretches "+
    "further to the west.\n");
   
    add_item("walls","The walls are clean and made of white stone.\n");
    add_item("ceiling","The ceiling is vaulted and soars high into the "+
    "sky.\n");
    add_item("windows","The windows let light into the building.\n");
    add_item("tables","On the tables you see many strange and "+
    "intresting artifacts.\n");
    add_item("stands","On the stands you see many strange and "+
    "intresting artifacts.\n");
    add_item("domes","Glass domes to protect the artifacts.\n");
    add_item("paintings","Many old and ancient paintings line the "+
    "wall. They range from formless splots of paint, to detailed "+
    "pictures of castles, cities, and the countryside.\n");
    add_item("decorations","Ornate candle holders, tapestries, "+
    "bells and strange charms dot the room.\n");
    add_item("artifacts","There are many strange artifacts and ancient "+
    "looking items in the glass cases. Among the more intresting ones "+
    "are a sword with an emerald blade, two giant ruby rings, a "+
    "brilliant white, platinum necklace with a dark sun on it, a "+
    "orange globe, and a crystal sculpture of an eagle.\n");

    INSIDE;

    clone_object(NOBLE(obj/case1))->move(TO);
    clone_object(NOBLE(obj/case2))->move(TO);
    clone_object(NOBLE(obj/case3))->move(TO);
    clone_object(NOBLE(obj/case4))->move(TO);
    clone_object(NOBLE(obj/case5))->move(TO);

    add_exit(NOBLE(gateway/s11),"north",0,-1,-1);
    add_exit(NOBLE(museum2),"west",0,-1,-1);
    reset_room();
}
