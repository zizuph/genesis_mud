inherit "/std/room";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

void
create_room()
{
    set_short("In another realm");
    INSIDE;
    set_long("\n"+
    "   You have entered a strange place. You stand on a dry, reddish "+
    "sand that stretches as far as you can see in all directions. The "+
    "sky is black, except at the horizon, where you see a dark-reddish "+
    "haze. But what is more eerie about this place is the source of "+
    "light. Just before you is a narrow river of reddish liquid that "+
    "glows like lava. Only you feel no heat. And the liquid is clear but "+
    "sluggish, like blood.\n\n");
    add_item("sky","The sky is black, and star-less. Only a dim, reddish "+
    "haze at the horizon marks any variation.\n");
    add_item("river","The river of blood, so it is called. It glows with "+
    "a fiery glow, casting reddish haze over the landscape. The river "+
    "stretches forever in both north and south directions.\n");
}

int
do_depart(string str)
{
    int i;
    object *us;
    NF("Depart where? Home?\n");
    if(str != "home")
        return 0;
    us = FILTER_LIVE(all_inventory(TO));
    write("You call upon the magic to take you back home.\n");
    for(i=0;i<sizeof(us);i++)
    {
        tell_object(us[i],"You feel transported!\n");
        us[i]->move_living("X",
             KHIRAA_DIR(temple/rooms/sacrifice_chamber));
    }
    return 1;
}

int
do_wash(string str)
{
    object ob;
    NF("Wash what?\n");
    if(str != "key")
        return 0;
    ob = present("_kmaster_key_",TP);
    if(!objectp(ob))
        return 0;
    write("You kneel down by the river and dip the "+ob->short()+" into "+
    "it, letting the blood soak it totally.\n");
    say(QCTNAME(TP)+" kneels down by the river and dips the "+ob->short()+
    " into it, letting the blood soak it totally.\n");
    tell_room(TO,"The "+ob->short()+" flashes violently!\n");
    ob->add_prop(CER_WASHED_IN_BLOOD,1);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_depart,"depart");
    add_action(do_wash,"wash");
}

