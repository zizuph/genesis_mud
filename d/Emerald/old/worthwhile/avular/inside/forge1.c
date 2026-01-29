/*
 * FORGE1.c
 * This is the Avular Forge
 * Because they make only darkling items, there is no
 * merchant / repair capability here.
 * - Alaron JAN 2000
 */

#include <macros.h>
#include "../defs.h"
#include "/d/Emerald/sys/terrain_types.h"
#include "/d/Emerald/sys/properties.h"
#include <stdproperties.h>

#define CM_FIVE_FEET    153
#define CM_FOUR_FEET    122

inherit AVULAR_ROOM;

object asmith;

void reset_room();

void
create_avular_room()
{
    set_short("A darkling forge");
    set_em_long("The small, dome-shaped room is filled with "+
        "workbenches and shelves. Each bench is covered with various "+
        "smithing tools. In the east wall of the room, "+
        "enclosed in a large, stone semi-circular column is a furnace, where there are "+
        "several rods of iron and more. There appears to be another room on the "+
        "other side of the chimney. A plume of black and gray smoke is "+
        "continually bellowing up from the furnace. The metal of the rods themselves are "+
        "not giving off heat, instead "+
        "it glows a brilliant white. Dozens of armour molds and hundreds of "+
        "smithing tools hang from hooks in the ceiling. @@get_ceiling_rel_height@@. A "+
        "small, open doorway leads east to another room.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_HOUSE );

    add_item( ({"benches", "workbenches", "bench", "workbench"}),
             "The workbenches appear to be made of the white, bark-less wood of the "+
             "trees from the strange forest that borders this city to the east. Iron "+
             "brackets are riveted in place, making the benches able to hold very "+
             "heavy items without buckling. All of them are cluttered with various "+
             "molds and tools.\n");

    add_item( ({"shelves","piles"}),
             "The shelves are made of the white, bark-less wood of the trees "+
             "from the odd forest outside the city gates. Neatly arranged piles "+
             "of cups, chisels, tools, and other items are layed out for easy "+
             "access.\n");

    add_item( ({"chisels", "molds", "cups", "tools", "hammers","armour molds",
                "smithing tools", "items", "tongs"}),
             "The entire room is filled with chisels, molds, cups, tools, and hundreds "+
             "of other objects, small and large. Most of the things hanging from hooks "+
             "in the ceilings are molds for various armour forms, though they appear to be "+
             "small; designed to make darkling-wearable armour only.\n");

    add_item( ({"rods", "iron rods", "rod", "iron rod"}),
             "The rods appear normal to you, yet even though they are giving off no heat, "+
             "their tips are glowing with a brilliant white light, making them usable "+
             "by the smith's hammers and other shapers.\n");

    add_item( ({"chimney", "column"}),
             "The chimney in the center of the room seems to be split exactly in the "+
             "center by a gray, stone wall. It appears as though the two adjacent rooms "+
             "share the same furnace and chimney.\n");

    add_item( ({ "wall", "east wall" }),
              "The east wall separates the two adjacent rooms, with the central "+
              "furnace and chimney being shared between the two rooms.\n");

    add_item( ({"furnace", "other room"}),
             "The furnace is carved into the gray stone chimney in the wall separating "+
             "the two adjacent rooms in this dome-shaped building. Unlike most furnaces "+
             "of this type, there are no coals or wood embers burning a hot, red and orange "+
             "flame. Instead, there is a small pile of glowing blue rocks in the bottom "+
             "of the furnace. They don't seem to be generating any heat, but somehow "+
             "the rods on the rack in the furnace seem to be becoming soft enough to shape.\n");

    add_item( "rack",
             "It is a rack that supports the metal balls and rods while being softened "+
             "for later shaping.\n");

    add_item( ({"floor", "down"}),
             "The floor in this room is made of a combination of the smooth, gray "+
             "stone that is used for the wall and small shards of rock and other "+
             "stone. Somehow the shards of stone have been pressed into the gray "+
             "stone floor, providing a surface easy for boots to grip if something "+
             "were to spill.\n");

    add_item( ({"smoke", "plume", "black smoke", "gray smoke" }),
             "A steady, thick plume of smoke is continually drifting up out of the "+
             "furnace and outside the building through the chimney. It appears very "+
             "strange to you, since you can't actually see anything burning. In fact, "+
             "it doesn't even look as though the smoke is coming from the furnace at all, it "+
             "almost looks like it is coming from somewhere below the rocks in the furnace.\n");

    add_item( "hooks",
             "Hundreds of black iron hooks are imbedded in the ceiling, each holding "+
             "tools or molds of some kind.\n");

    add_item ("ceiling",
              "@@get_ceiling_rel_height@@.\n");

    add_item( ({"doorway", "open doorway", "small doorway", "small open doorway"}),
             "The doorway is small, designed for comfortable passage by a darkling. "+
             "It leads east into the other room that shares the furnace here.\n");


    remove_item("dark");
    remove_item("up");
    remove_item("down");
    remove_item("plants");
    add_door_exit( AV_OBJ+"forge_door1", AVMAIN+"av5", "southwest", 0, 0, 1 );
    add_exit(AVINSIDE+"forge2", "east");

    reset_room();
}

void
reset_room()
{
    if (!asmith)
    {
        asmith = clone_object(AV_NPC+"elmenir");
        asmith->move(this_object());
    }
}

string
get_ceiling_rel_height()
{
    int pHeight;

    pHeight = this_player()->query_prop(CONT_I_HEIGHT);
    if ( (pHeight < CM_FIVE_FEET) &&
         (pHeight > CM_FOUR_FEET) )
    {
        return "The ceiling is quite low, and the only place in the room "+
            "that you can stand comfortable is in the center";
    }
    else if ( pHeight > CM_FIVE_FEET )
    {
        return "The ceiling is very low, and even when standing in the "+
            "center of the room, you have to stoop over to avoid "+
            "bumping your head on the cold stone";
    }
    else
    {
        return "The ceiling is quite low.";
    }
}

public void
enter_inv(object ob, object from)
{
    if ( ob->query_prop(CONT_I_HEIGHT) > CM_FIVE_FEET )
    {
        if (present(asmith, this_object()))
        {
            asmith->command("say to " + OB_NAME(ob) + " Watch your head. A "+
                "tall "+ob->query_race_name()+ " like yourself could get "+
                "hurt around here.");

        }
    }
}
