inherit "/std/container";
#include "/d/Kalad/defs.h"

/* A dagger sheath by Sarr */

int worn;

void
create_container()
{
    set_name("sheath");
    set_adj("black");
    add_adj("small");
    set_short("small black sheath");
    set_long("This is a small sheath made of hard, black leather. On "+
        "it, you see small red stripes spiraling around its length. The "+
        "scabbard is so small, than only a dagger would fit in it. You "+
        "can try with 'dsheath' <dagger>. There are also straps on it "+
        "to wear around your wrist.\n");
    add_prop(CONT_I_WEIGHT,300);
    add_prop(CONT_I_VOLUME,170);
    add_prop(CONT_I_MAX_WEIGHT,22000);
    add_prop(CONT_I_MAX_VOLUME,11800);
    add_prop(OBJ_M_NO_DROP,"@@my_drop@@");
}

int
my_drop()
{
    if(worn == 1)
        {
        write("You must remove the "+short()+" first!\n");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action("do_dsheath","dsheath");
    add_action("do_put","put");
    add_action("do_put","drop");
    add_action("do_draw","draw");
    add_action("do_wear","wear");
    add_action("do_remove","remove");
}

int
do_wear(string str)
{
    object scab;
    NF("Wear what?\n");
    if(!parse_command("wear "+str,TP,"'wear' %o",scab))
        return 0;
    if(scab != TO)
        return 0;
    NF("You already wear the "+short()+".\n");
    if(worn == 1)
        return 0;
    NF("You can't wear another sheath there.\n");
    if(member_array("dagger_sheath",TP->query_sublocs()) != -1)
        return 0;
    worn = 1;
    write("You wear the "+short()+" around your wrist.\n");
    say(QCTNAME(TP)+" wears the "+short()+" around "+HIS(TP)+
        " wrist.\n");
    TP->add_subloc("dagger_sheath",TO);
    set_no_show_composite(1);
    return 1;
}

int
do_remove(string str)
{
    object scab;
    if(!parse_command("remove "+str,TP,"'remove' %o",scab))
        return 0;
    if(scab != TO)
        return 0;
    NF("You aren't wearing the "+short()+".\n");
    if(worn == 0)
        return 0;
    worn = 0;
    set_no_show_composite(0);
    TP->remove_subloc("dagger_sheath");
    write("You remove your "+short()+" from your wrist.\n");
    say(QCTNAME(TP)+" removes the "+short()+" from "+HIS(TP)+
        " wrist.\n");
    return 1;
}

string
show_subloc(string subloc, object on, object for_ob)
{
    string str,str2;
    if(subloc != "dagger_sheath")
        return "";
    if(on == for_ob)
        {
        str2 = "your";
        str = "You are";
    }
    else
        {
        str2 = HIS(on);
        str = capitalize(HE(on))+" is";
    }
    str = str+" wearing a "+short()+" around "+str2+" wrist.\n";
    return str;
}

int
do_put(string str)
{
    string ver;
    object sca,ob;
    ver = query_verb();
    if(parse_command(ver+" "+str,TP,"'"+ver+"' %o 'in' %o",ob,sca))
        {
        if(sca == TO)
            {
            write("If you want to put a dagger in the sheath, use "+
                "'dsheath' <dagger>.\n");
            return 1;
       }
    }
}


int 
do_dsheath(string arg)
{
    object dag,*che;
    NF("Sheathe what dagger?\n");
    if(!parse_command("dsheath "+arg,TP,"'dsheath' %o",dag))
        return 0;
    if(!dag)
        return 0;
    NF("You must have the "+dag->short()+" first!\n");
    if(!present(dag,TP))
        return 0;
    NF("You can only put daggers in here!\n");
    if(!dag->query_wt(W_KNIFE))
        return 0;
    che = all_inventory(TO);
    NF("There already is a dagger in the sheath!\n");
    if(sizeof(che))
        return 0;
    dag->unwield_wep(dag->short());
    NF("It doesn't fit.\n");
    if(dag->move(TO))
        return 0;
    write("You slide your "+dag->short()+" into your "+short()+".\n");
    say(QCTNAME(TP)+" slides "+HIS(TP)+" "+dag->short()+" into "+HIS(TP)+ 
        " "+short()+".\n");
    return 1;
}

int
do_draw()
{
    object *che,dag;
    che = all_inventory(TO);
    NF("There isn't a dagger in the sheath!\n"); 
    if(!sizeof(che))
        return 0;
    dag = che[0];
    NF("You couldn't draw it for some reason.\n");
    if(dag->move(TP))
        return 0;
    write("You draw your "+dag->short()+"!\n");
    say(QCTNAME(TP)+" draws "+HIS(TP)+" "+dag->short()+"!\n");
    dag->wield_wep(dag->short());
    return 1;
}

