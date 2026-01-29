inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

object demon;
int i_demon;

void start_it();

void
create_armour()
{
    ::create_armour();
    if (!IS_CLONE)
        return;
    set_name("light_amulet");
    add_name("amulet");
    set_adj("ancient");
    add_adj("powerfull");
    set_short("powerfull ancient amulet");
    set_long("This is the fabled Amulet of Light. Made of a large "+
    "blue diamond set in the grip of an onyx claw on a mithril chain, "+
    "it's sheer beuty overwhelmes you. You feel a strong aura coming "+
    "from the amulet as power pulses within the diamond's core. The "+
    "Amulet is glowing very brightly. You suddenly feel as if a thousand "+
    "eyes are watching you, some which are very, very dark...\n");
    set_at(A_NECK);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "life" }));
    add_prop(MAGIC_AM_ID_INFO, ({"This is the Amulet of light. It was "+
    "created to drive the undead forces of Raumor away. It's true "+
    "powers will work only in the hands of the current Lord of Raumdor ", 25}));
    add_prop(OBJ_I_LIGHT,3);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
    add_prop(OBJ_I_VALUE,900);
    seteuid(getuid(TO));    
    start_it();
}

void 
call_demon()
{
    object ob;

    ob = environment(this_object());

    if (i_demon) 
        return;

    if(!present("tinytim",TP) || !present("tinytim",E(TP)))
    {
        if (ob->query_prop(ROOM_I_IS))
        {
            i_demon = 1;
            demon = clone_object("/d/Kalad/common/raum/ruins/floor1/npc/demon.c");
            tell_room(ob, "A great black rift tears open before you, the "+
            "screaming souls of those who are damned can be heard echoing "+
            "throughout your mind. The rift seems to widen as a massive "+
            "black-skinned demon steps out, it's demonic red eyes semm to cut into "+
            "your very soul./n");
            demon->move_living("M", ob);
            demon->command("say I have come for the amulet mortal. Back away "+
            "from the foul creation so I may destroy it, try to stop me, and I will "+
            "tear your soul apart.");
            demon->command("get amulet");
            return;
        }        
        else
        { 
            i_demon = 1;
            demon = clone_object("d/Kalad/common/raum/ruins/floor1/npc/demon.c");
            tell_room(E(TP),"A great black rift tears open before you, the "+
            "screaming souls of those who are damned can be heard echoing "+
            "throughout your mind. The rift seems to widen as a massive "+
            "black-skinned demon steps out, it's demonic red eyes cut into "+
            "your very soul.");
            demon->move_living("M", environment(ob));
            if (living(ob))
            demon->set_follow(ob->query_real_name());
            return;
        }
    } 
}

void 
start_it()
{
    int i;
    i = random(400) + 400;
    set_alarm(itof(i), 0.0, call_demon);
}


