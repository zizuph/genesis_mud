inherit "/std/armour";
#include "/d/Kalad/defs.h"

/* SaRr */

int down;
string padj1,padj2;

void
create_armour()
{
    set_name("shoufa");
    add_adj("black");
    set_adj("concealing");
    set_short("black concealing shoufa");
    set_long("A black cloth which is wraped around the neck and the head "+
    "with a part that can be raised to cover the mouth and nose, leaving "+
    "only the eyes visable.\n");
    set_at(A_HEAD);
    set_ac(1);
    set_af(TO);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,3700);
    add_prop(OBJ_I_VALUE,300);
}

void
leave_env(object inv, object to)
{
    if(interactive(inv))
    {
        set_this_player(inv);
        TP->remove_adj("black-masked");
        TP->remove_adj("dangerous");
        if(padj1 && padj2)
            TP->set_adj(({padj1,padj2}));
        down = 0;
    }
    ::leave_env(inv,to);
}

void
init()
{
    ::init();
    AA(do_shup,shup);
    AA(do_shlaugh,shlaugh);
    AA(do_shdown,shdown);
}
int
do_shdown()
{
    NF("You don't have the "+short()+".\n");
    if(!present(TO,TP))
        return 0;
    NF("You aren't wearing the "+short()+"!\n");
    if(query_worn() != TP)
        return 0;
    NF("The "+short()+" is already down!\n");
    if(down == 0)
        return 0;
    down = 0;
    write("You pull the "+short()+", revealing your face.\n");
    say(QCTNAME(TP)+" pulls down the "+short()+", revealing "+
    HIS(TP)+" face.\n");
    TP->remove_adj("black-masked");
    TP->remove_adj("dangerous");
    TP->set_adj(({padj1,padj2}));
    return 1;
}

int
do_shup()
{
    NF("You don't have the "+short()+".\n");
    if(!present(TO,TP))
        return 0;
    NF("You aren't wearing the "+short()+"!\n");
    if(query_worn() != TP)
        return 0;
    NF("The "+short()+" is already up!\n");
    if(down == 1)
        return 0;
    down = 1;
    write("You raise the "+short()+" up to cover your mouth and "+
    "nose. Your eyes gleam dangerously from within.\n");
    say(QCTNAME(TP)+" raises the "+short()+" up to cover "+HIS(TP)+
    "mouth and nose. "+C(HIS(TP))+" eyes gleam dangerously from "+
    "within.\n");
    padj1 = TP->query_adj(1)[0];
    padj2 = TP->query_adj(1)[1];
    TP->remove_adj(padj1);
    TP->remove_adj(padj2);
    TP->set_adj(({"dangerous","black-masked"}));
    return 1;
}

int
do_shlaugh()
{
    if(down == 0)
    {
        write("You don't have your shoufa covering your face.\n");
        return 1;
    }
    write("You laugh from within your "+short()+".\n");
    say("A muffled, evil laughter sounds from behind "+QTNAME(TP)+
    "'s "+short()+".\n");
    return 1;
}

