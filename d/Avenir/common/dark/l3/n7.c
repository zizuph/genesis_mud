inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"
create_room()   {

        set_short("Natural tunnel");
        set_long(
"You are in a naturally formed tunnel running to the northeast. "+
"The tunnel ends to the southwest, where it seems to break through "+
"into some kind of hallway. From the northeast comes a damp "+
"breeze, which making the uneven floor slippery and even more "+
"difficult to walk on.\n");

    add_item(({"wall","walls"}),
"The walls of this tunnel are simply the natural rock formation. "+
"They glisten with moisture and create strange shadows all around.\n");


        add_exit("/d/Avenir/common/dark/l3/n8","northeast",0);
        add_exit("/d/Avenir/common/dark/l3/n6","southwest",0);


        add_prop(ROOM_I_LIGHT,0);
        add_prop(ROOM_I_INSIDE,1);

}
