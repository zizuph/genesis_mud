/* Gully dwarf for the city of Nethosak. 
 * Made from a gully dwarf in Kendermore by Gwyneth. * - Elmore.
 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
string face();

void
create_krynn_monster()
{
    add_name("dwarf"); 
    set_race_name("gully dwarf");
    set_adj(face());
    add_adj("dirty");
    add_adj("gully");
    set_long("This is one of the dirtiest creatures you've ever seen! "+
        "His clothes are rags, and his hair looks as if the only time "+
        "it gets washed is when it rains. This gully dwarf is not very "+
        "bright, but he's rather friendly, and helps the minotaurs here "+
        "the keep the city clean.\n"+
        "He is holding a large dirty sack in his right hand.\n");
    set_alignment(50); 
    set_gender(0);
    set_knight_prestige(-5);
    set_random_move(random(20)+35); 
    set_act_time(random(30));
    add_act("emote spots some garbage lying by the side of the road, "+
            "he quickly hurries over there to get it."); 
    add_act("get all");
    add_act("emote gets some dry leaves.");
    add_act("emote lashes out after the flies buzzing over him."); 
    add_act("emote looks admiringly at one of the minotaurs.");
    add_act("emote peers curiously at you."); 
    add_act("emote closes his large dirty bag.");
    add_act("emote opens his large dirty bag."); 
    add_act("get all");
    add_act("emote falls asleep in the gutter."); 
    add_act("says: Me collect garbage."); 
    add_act("emote gathers some garbage, and puts in into the large "+
            "dirty bag."); 

    
}

string
face()
{
    // Set description.
    string *faces;
    faces = ({"very", "thin", "slim", "confused", "tiny",              "tired", "unkempt"});
    return faces[random(sizeof(faces))];
}

