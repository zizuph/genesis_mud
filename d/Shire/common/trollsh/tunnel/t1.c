#include "../defs.h";
inherit "/d/Shire/room";

create_room()
{
    set_short("A tunnel under the Trollshaws");
    set_long(
    "You can see a bit of light coming through the bushes above "+
    "you, but down below you it gets much darker and you can sniff "+
    "out a dank, aged smell wafting upwards. "+
    "You can go back up to the surface or continue down into "+
    "the unknown.\n");
       
    add_item(({"bushes","bush","light"}),
    "The bushes above you are greyish, they seem to be dying even as  "+
    "light pours over them.\n");
    	
    add_item(({"smell","sniff","below"}),
    "The smell you can discern from below is one of death and "+
    "decay. Your conscience cries out to you to get away "+
    "from this place.\n");

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TROLLSH_DIR + "shaws6", "up", 0, 3);
    add_exit(TROLLSH_DIR + "tunnel/t2", "down", 0, 3);
}
