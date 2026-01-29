#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

object ob,ob2;

void reset_room();

void
create_room()
{
    set_short("In a dark hall");
    
    set_long("\n   You are walking along a short, cold hallway. The "+
    "walls and ceiling are made of smooth black stone, while the "+
    "floor is formed of polished black marble. Small red runes "+
    "decorate the sides of the walls.\n"+
    "   You can smell death and decay in the air. Looking to the "+
    "north, you can see a purple glowing coming from the room there. "+
    "To the east, only darkness can be seen.\n\n");

    add_item(({"runes","symbols"}),"@@query_k_rune@@");
    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, with "+
    "a few runes inscribed on them.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   

    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_exit(KHIRAA_DIR(temple/rooms/temple_portal),"north","@@block@@",-1);
    add_exit(KHIRAA_DIR(temple/rooms/temple_join),"east",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t7),"south",0,-1);
    reset_room();
    clone_object(KHIRAA_DIR(temple/obj/pbasin))->move(TO);
    clone_object(KHIRAA_DIR(temple/obj/bell))->move(TO);
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(KHIRAA_DIR(temple/obj/xantios));
        ob->arm_me();
        ob->move(TO);
    }
    if(!ob2)
    {
        ob2 = clone_object(KHIRAA_DIR(temple/obj/olaus));
        ob2->arm_me();
        ob2->move(TO);
    }
}

string
query_k_rune()
{
    if(IS_LP(TP) || IS_DK(TP))
        return "They are praises to the Nameless one. All hail "+
        "unto Him. Khiraa.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}

int
block()
{
    mapping temp = restore_map(KHIRAA_DIR(log/friend_list));
    if(IS_DK(TP) || IS_LP(TP))
        return 0;
    if(member_array(TP->query_real_name(),m_indexes(temp)) != -1)
        return 0;
    write("You try to go north, but a magical field suddenly appears "+
    "and prevents you from going in.\n");
    say(QCTNAME(TP)+" tries to go north, but a magical field suddenly "+
    "appears and stops "+HIM(TP)+".\n");
    return 1;
}

