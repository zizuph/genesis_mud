// file name:        /d/Avenir/common/bazaar/admin/a18.c
// creator(s):       Lilith, Oct 2002
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/bazaar/admin/admin_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/bazaar/admin/admin.h"

//not using smis for this placement. 
static object gate;

/* Now create the room.  */
void
create_admin_room()
{
    set_short("At the First Gate, just outside the Forbidden City");
    set_long("The First Gate rises impossibly high above you, its "+
        "massive granite slabs immovable by any hand but the Idrys. "+
        "A giant trefoil has been carved into the stone and the "+
        "hollow filled with gold that glows in the light of the "+
        "Source. The chalcedony walls of the Forbidden City are "+
        "as glossy as gemstones, as if each one was hand-polished "+
        "to a high sheen before it was carefully placed. "+
        "The Bridge of Sighs stretches west across the sea "+
        "toward the Bazaar, filling the air with its distinctive "+
        "music. Beneath it dark waters seethe and flow, teeming "+
        "with mysterious life just below the surface.\n");
    add_item(({"gate", "gates", "slab", "slabs", "first gate"}), 
        "This imposing structure is known as the First Gate. "+
        "It is comprised of two granite slabs so large that "+
        "part of you wonders how they were moved into place. "+
        "A golden trefoil, the symbol of Sybarus, has been carved "+
        "into the stone.\n");
    add_item(({"trefoil", "golden trefoil", "trefoil carved into "+
        "the stone", "trefoil on gate"}), 
        "A mind-boggling amount of gold has been used to create "+
        "the golden trefoil carved into the stone of the gate. "+
        "The golden trefoil is easily recognized as the symbol "+
        "of Sybarus.\n");
    add_item(({"walls", "wall", "chalcedony", "chalcedony walls",
       "city walls"}),
       "The walls of the Forbidden City are made from blocks of "+
       "stone from the chalcedony family of minerals: agate, "+
       "bloodstone, carnelian, chrysoprase, jasper, onyx, prase, "+
       "and sardonyx. Randomly placed, they are rectangular with "+
       "each one standing the height of a tall elf and thrice that "+
       "in length. The blocks are glossy as gemstones, making them "+
       "both beautiful and deadly difficult to climb.\n");
    add_cmd_item(({"wall", "walls", "block", "blocks"}), "climb",
       "Under the watchful eyes of the guards you casually approach "+
        "the wall. A cursory examination reveals that without the "+
       "proper equipment and considerable help from the inside, "+
       "this wall would be impossible to climb.\n");
    add_cmd_item(({"walls", "walls", "block", "blocks"}), 
       ({"feel", "touch"}),
       "It is cool and smooth to the touch, with nary a crack or "+
       "a chip to mark the flawless finish.\n");
    add_item(({"bridge", "bridge of sighs"}),
       "The Bridge of Sighs extends west from here.  It has a "+
       "distinctly golden appearance, looking more like a "+
       "filigree necklace than anything so mundane as a bridge.\n");     
    add_item(({"sea", "seas", "water", "waters","dark waters",
       "sybarus sea", "sea of sybarus"}),
       "The dark waters below are part of the Sea of Sybarus. "+
       "The light of the Source does not penerate deep enough "+
       "for you to see beneath the slick surface.\n");

    add_exit(BAZ_ADMIN +"a17", "northwest", 0);

    add_prop(ROOM_M_NO_ATTACK, "You feel as though the weight "+
        "of a giant hand presses upon you, stifling your attempt.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "As if the Gods of Sybarus "+
        "would permit your puny magic!\n");

    /* Place the first Gate */
    gate = clone_object(CITY + "obj/door/first_gate.c");
    gate->move(this_object());  
    set_dircmd("south");  

    reset_admin_room();
}

