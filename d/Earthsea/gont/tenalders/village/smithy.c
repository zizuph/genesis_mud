/**
  *  smithy, coded by Amelia for Ten Alders, 8/31/97
  *  NPCS:  Pelle, the smith
  *
  * updated to use lib/smith by Rhyn, nov '02
  */

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/smith";

#pragma no_clone
#pragma strict_types

private object smith;

public void
create_earthsea_room()
{
    set_short("smithy");
    set_long("A blacksmith shop. The walls and " +
         "ceiling are blackened with the soot of the ever-burning " +
         "smith's fire, where you see molds and kettles that " +
         "contain molten metal. A large black bellows " +
         "lies near to it. Many implements of the trade hang upon " +
         "the walls. The room is dominated by a massive immovable " +
         "anvil in the center. There is an old wooden sign " +
         "blackened by age and soot hanging on the wall.\n");
    add_exit("village_path_5", "north");
    add_item((({"molds", "kettles"})), "Molds for shaping " +
        "weapons and armour and kettles filled with molten metal " +
        "lie ready by the smith's fire.\n");
    add_item((({"walls", "ceiling"})), "The stone walls and " +
        "ceiling of this hut are blackened by soot from the ever-" +
        "burning fire.\n");
    add_item((({"implements", "implements of the trade"})),
        "You see metal calipers, hammers and tongs of various sizes, " +
        "as well as ladles and metal molds, which hang on the " +
        "walls in a semi-orderly fashion.\n");
    add_item((({"bellows", "black bellows", "large black bellows"})),
        "A large blackened bellows, constructed of two sleeves of " +
        "goat leather, lies idle on the floor by the fire. It is " +
        "used for feeding the fire with air.\n");
    add_item("sign", "@@sign_long");
    reset_room();
    configure_smith();
}

public void
reset_room()
{
    if(!smith)
    {
        smith = clone_object("/d/Earthsea/gont/tenalders/npc/smith");
        smith->arm_me();
        smith->move(this_object(), 1);
        smith->command("emote swaggers in.");
    }
}

public void
init()
{
    ::init();
    init_smith();
}

public int
check_smith_active()
{
    return (objectp(smith));
}
