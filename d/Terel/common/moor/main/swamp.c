// Lilith Dec 2021: fixed awkward working in long desc and typo in item desc,
//                  converted to Terel std room.

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
#include <ss_types.h>

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


int 
no_go()
{
    write("The swamp sucks at your feet and you start sinking!\n "+
        "You struggle back onto firm ground.\n");
    say(QCTNAME(TP) + " starts to go east but turns back when the "+
        "ground begins sinking underfoot.\n");
    return 1;
}


void
create_room(){
    set_short("Swampy Moor");
    set_long("The desolate and haunting moor, with its megalthic "+
    "stones and stunted trees, transitions into a swamp here, where "+
    "muck pushed has up against the eroded face of the northern "+
	"hills, making a cliff. Brackish water and saturated mossy soil "+
    "extends east, as far as your eye can see.\n");

    add_exit("moor5", "south", 0);
	add_exit("swamp", "east", no_go);
    add_item("cliff", "It is formed by the rocky hills that have "+
        "been eroded by the swamp. It shouldn't take much skill "+
        "to climb it.\n");
    add_cmd_item("cliff", "climb", "@@climb");

    add_item("muck", "It is normal pond muck, filth and putresence.\n");  
    add_item(({"rocks", "megalithic rocks", "megaliths"}), 
        "There are megalithic rocks, some as small as a horse, others as big "+
        "as a house, scattered across the moors as if by a giant's hand.\n");
    add_item(({"heather", "ground", "moss"}),"The ground is covered in heather "+
       "and moss and standing water due to poor drainage.\n");
    add_item(({"trees","tree","small tree","small trees"}),
      "Several small trees dot the moorlands and line the roads.\n");
    add_item(({"hill","hills","moor", "moors"}),"Rolling hills covered in mist.\n");

    add_item(({"bushes","shrubs"}), "Bushes and shrubs " +
       "litter the area.\n");   
    add_item(("hills"),"Rolling hills, rocky crags, stunted trees.\n");
    add_item(({"mist", "mists" }), "They seem malevolent as they glide "+
       "across the moors.\n");
    add_item(({"water", "soil", "ground"}), 
        "The ground is all mucky, covered in shallow, brackish water.\n");
    add_item("moss", "It is lurid and looks foul.\n");	   
    add_item("water", "It is shallow, but cold and brackish.\n");	   
    add_item(({"swamp"}), "It is too foggy to see any details from here.\n");

    set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                  }),
                  ({"muck", "cliff", "hills"}) , 
                     3 );

}

int
climb(){
    int skill = this_player()->query_skill(SS_CLIMB) + random(100);
    if (skill > 60){
        tell_room(environment(this_player()), QCTNAME(this_player()) +
                " scrambles up the cliff.\n", this_player());
        this_player()->catch_msg("You scramble up the cliff.\n");

        set_dircmd("cliff");
        this_player()->move_living("climbing up the cliff", 
            "/d/Terel/common/moor/main/cliff");
        return 1;
    }
    this_player()->catch_msg("You fail to get a sure footing.\n");
    return 1;

}

