inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
 
#include "/d/Emerald/defs.h"
 
void reset_room();
 
void
create_room()
{
    reset_room();
    set_short("The Plaza");
    set_long("   The Plaza is the general meeting area for " +
        "many elves. It is an open area in the city and serves " +
        "as a meeting place. Often times, you can find friends " +
        "and families reuniting here. South of here takes " +
        "you to the center of the city.\n");
 
    add_item("tree",
        "The tree reaches towards the sky. You can't see its top.\n");
    add_item("plaza",
        "The Plaza is large. All around here you see various " +
        "plantings, which add peace and quiet to the bustling " +
        "noises outside the Plaza.\n");
    add_item("ground",
        "The ground is constructed of many large white marble " +
        "stones. Inset into the stones is a mosaic made of " + 
        "various gemstones, including many large emeralds.\n");
    add_item("sky",
        "The sky is clear and blue. A large tree dominates the " +
        "southern horizon.\n");                                
    add_item(({"gemstone", "gemstones", "jewels"}),
        "You see many precious and semi-precious stones. They all " +
        "twinkle in the light, creating a kaleidoscope of color " +
        "and breathtaking beauty.\n");
    add_item("emeralds",
        "The emeralds are from the famous mines. They are of the " +
        "deepest green you've ever seen. Though they are large, " +
        "the gems don't detract from the overall patterns in the " +
        "mosaic.\n");    
 
    set_tell_time(1);
    add_tell("Some elves whisper quietly in the distance.\n");
    add_tell("A dove takes wing and flys away.\n");
    add_tell("A royal courier passes by you.\n");
    add_tell("Some children laugh in the distance.\n");
    add_tell("You see some children playing in the Plaza.\n");
    add_tell("A gentle breeze blows through the trees.\n");
    add_tell("A gentle floral frangrance fills the air.\n");
 
                                          
    add_exit(TOWNSHIP_DIR + "rd05", "north");
    add_exit(TOWNSHIP_DIR + "pk03", "south");
    add_exit(TOWNSHIP_DIR + "rd11", "east");
    add_exit(TOWNSHIP_DIR + "board", "west");
}                    
 
void
reset_room()
{
}
 
 
void
enter_inv(object ob, object from)
{
   start_room_tells();
   ::enter_inv(ob, from);
}
