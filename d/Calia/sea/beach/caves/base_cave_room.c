/*  description: Cave room for small water
 *               krougs.  Nasty smelling,
 *               dark, and damp.
 */

#pragma strict_types
inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include KR_HERBSEARCH

void
reset_herb_room()
{
    set_searched(0);
}

void
reset_room()
{
    reset_herb_room();
}


public void
make_tunnel_room()
{
    set_short("Dark tunnel");
    set_long("This is a network of underground caves"+
      " and tunnels descending into the rock cliff."+
      " The walls, ceiling and floor"+
      " are round as if someone had bored a hole down into"+
      " the solid rock. However it was created, there is"+
      " something unnatural about the place. The tunnel is"+
      " about 2 meters in diameter. The floor"+
      " is partially submerged in water, deeper in some"+
      " areas than in others. The walls and ceiling are"+
      " covered in some kind of damp dark mold or slime."+
      " A nasty foetid odour permeates the place, and"+
      " you really wish you could get a breath of"+
      " fresh air.\n");

    add_item(({"odour", "nasty odour", "nasty foetid odour"}), 
      "Whatever is causing this odour, the air"+
      " quality here is really poor.\n");
    add_item("floor", "The floor of the tunnel is"+
      " partially submerged in sea water. You realize that"+
      " you must be at or below sea level.\n");
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERBS+"brownslime");
    add_herb_file(HERBS+"greenslime");


    reset_room();   

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}

public void
make_cave_room()
{
    set_short("Underwater cave.");
    set_long("This is part of a network of caves and tunnels"+
      " that delve down into the solid rock, cutting you"+
      " off from the light. The tunnel"+
      " comes to a deadend in this cave where the murky"+
      " water comes up to the thigh in some places."+
      " There is just enough space to stand. The floor"+
      " is partially submerged in water, deeper in some"+
      " areas than in others. The walls and ceiling are"+
      " covered in some kind of damp dark mold or slime."+
      " A nasty foetid odour permeates the place, and"+
      " you really wish you could get a breath of"+
      " fresh air.\n");

    add_item(({"odour", "nasty odour", "nasty fetid odour"}), 
      "Whatever is causing this odour, the air"+
      " quality here is really poor.\n");
    add_item("floor", "The floor of the tunnel is"+
      " partially submerged in sea water, and you"+
      " find that in some areas you need to wade"+
      " through dark murky water up to your thighs."+
      " You realize that you must be at or below"+
      " sea level.\n");
    add_item(({"water", "sea water"}),
      "The water is murky and carries a nasty"+
      " slick residue of some kind. You wonder"+
      " if your health will be affected if you"+
      " stay here too long.\n");
    set_search_places(({"walls","water", "ceiling", "floor"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERBS+"brownslime");
    add_herb_file(HERBS+"greenslime");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    reset_room();
}

void
hook_smelled(string str)
{
    write("It smells toxic around here.\n");

}

void
make_underwater_tunnel()
{
    set_short("Dark underwater tunnel");
    set_long("The tunnel is completely submerged."+
      " The water is murky, and you find it"+
      " difficult to see far in any direction. While"+
      " the rock below your feet is solid, it is also"+
      " slippery. Every now and then you bump into the"+
      " walls or a low area of the ceiling cracks your"+
      " head.\n");
    add_item(({"walls", "ceiling", "floor", "rock"}),
      "You can barely see the surrounding tunnel walls,"+
      " ceiling and floors, although you sense they are"+
      " made of solid rock like the floors above. They "+
      " are seamed with cracks. The whole tunnel structure"+
      " is covered with some sort of slimy mucuous like"+
      " the inner bowels of some giant organism.\n");
    add_item("water", "The water is dark and murky,"+
      " and it feels contaminated by some very unpleasant"+
      " substances. You wonder how long you can continue"+
      " to stay here without becoming ill.\n");
    add_item("mucous", "It is unpleasant to speculate"+
      " on the source of this anomoly. You only hope that"+
      " it will not infect you.\n");


    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERBS+"brownslime");
    add_herb_file(HERBS+"greenslime");


    reset_room();   

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);

}
void
make_underwater_cave()
{
    set_short("Dark underwater cave");
    set_long("The tunnel widens here and"+
      " comes to a deadend. It is completely submerged"+
      " under dark, murky waters where you cannot see"+
      " very far in any direction. While"+
      " the rock below your feet is solid, it is also"+
      " slippery. You wonder how long you can continue"+
      " to survive here without being overcome by the"+
      " noxious mucuous that floats in the water.\n");

    add_item(({"walls", "ceiling", "floor", "rock"}),
      "You can barely see the surrounding tunnel walls,"+
      " ceiling and floors, although you sense they are"+
      " made of solid rock like the floors above. They "+
      " are seamed with cracks. The whole tunnel structure"+
      " is covered with some sort of slimy mucuous like"+
      " the inner bowels of some giant organism.\n");
    add_item("water", "The water is dark and murky,"+
      " and it feels contaminated by some very unpleasant"+
      " substances. You wonder how long you can continue"+
      " to stay here without becoming ill.\n");
    add_item(({"mucous", "noxious mucous"}),
      "It is unpleasant to speculate"+
      " on the source of this anomoly. You only hope that"+
      " it will not infect you.\n");


    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERBS+"brownslime");
    add_herb_file(HERBS+"greenslime");


    reset_room();   

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);

}
