inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";


create_room()
{
    set_short("At the ruined gates");
    set_long("You stand outside the blackened and charred remains" +
    " of what once were the great gates of this building. The wood" +
    " in the gates has long since rotted away, and the only thing" +
    " that remains are the twisted remnants of the great iron hinges upon" +
    " which the mighty doors once swung. The hole were they sat is like a" +
    " gaping black wound in the towering walls.It must have been a" +
    " very long time since  anyone lived here. From the west the sea" +
    " breeze carries the cries of seagulls, and to the north the" +
    " road lies. Looking south through the portal you can see into" +
    " a dark courtyard.\n");
   
    add_exit(RHUN_DIR + "newruins/to_road", "north");
    add_exit(RHUN_DIR + "newruins/court_n", "south");
    add_exit(RHUN_DIR + "newruins/seapath", "west");

   add_item(({"gates","hinges","remains"}),"Nothing remains of the" +
    " gates. The rusty hinges are twisted like the gates were ripped" +
    " from their seat. They must have been huge though to fill this portal.\n"); 

    add_item(({"wall","walls"}),"The walls look ancient." +
    " They are roughly hewn from granite and towers over these plains" +
    " like a sentinel. Battlements crown the walls, and you can see crude" +
    " carvings decorating them.\n");
  
   add_item (({"carvings","battlements","carving"}),"The battlements"+
    " are cut into the walls, and the defenders could pour boiling oil on"+
    " would be attackers. They are covered with carvings which, although cut" +
    " in granite, have almost been worn smooth by time.It is very hard" +
    " to make any sense of them, but one recurring motif seem to be an" +
    " eye looking out across the plains. Somehow, you almost feel like" +
    " it's watching you!\n");

}                                          