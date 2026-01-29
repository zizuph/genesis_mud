inherit "/std/object";
#include "/d/Kalad/defs.h"

/* Sarr */

int lit;
int f_str;

string
query_auto_load()
{
    return MASTER+":|"+f_str;
}

void
init_arg(string arg)
{
    string foobar;
    sscanf(arg,"%s|%d",foobar,f_str);
}

void
set_fire_str(int i)
{
    f_str = i;
}

int
query_fire_str()
{
    return f_str;
}

void
create_object()
{
    set_name("bottle");
    set_adj("explosive");
    set_short("explosive bottle");
    set_long("This is a bottle filled with explosive liquid. You "+
    "see a cloth rag sticking out of the top.\n");
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_M_NO_DROP,"@@my_drop@@");
}

int
my_drop()
{
    if(lit)
    { 
        write("You can't drop it, you must throw it!\n");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    AA(do_throw,throw);
    AA(do_ignite,ignite);
}

int
do_ignite(string str)
{
    object bot;
    NF("Ignite what?\n");
    if(!parse_command("ignite "+str,TP,"'ignite' %o",bot))
        return 0;
    if(!bot)
        return 0;
    if(bot != TO)
        return 0;
    NF("The "+short()+" is already lit.\n");
    if(lit)
        return 0;
    lit = 1;
    write("You ignite the wick on the bottle, and it starts to burn. "+
    "You have only a few moments to throw it before it explodes in "+
    "your face.\n");
    say(QCTNAME(TP)+" ignites the wick on the "+short()+".\n");
    set_alarm(10.0,0.0,"explode",TP,f_str);
    return 1;
}

void
do_combat_mess(object ob,int f_str2)
{
    string str;
    switch(f_str2)
    {
        case 80..90:
        str = "puny";
        break;
        case 91..100:
        str = "small";
        break;
        case 101..120:
        str = "fair-sized";
        break;
        case 121..129:
        str = "nice-sized";
        break;
        case 130..144:
        str = "medium-sized";
        break;
        case 145..159:
        str = "large";
        break;
        case 160..174:
        str = "powerful";
        break;
        case 175..200:
        str = "lethal";
        break;
    }
    tell_room(E(ob),QCTNAME(ob)+" is hit with a "+str+
    " blast!\n",ob);
    tell_object(ob,"You are hit with a "+str+" blast!\n");
}

void
explode(object ob)
{
    object fire;
    if(E(TO) == ob)
    {
        ob->catch_msg("The "+short()+" explodes in your face!\n");
        tell_room(E(ob),"The "+short()+" explodes in "+QTNAME(ob)+
        "'s face!\n",ob);
        tell_room(E(ob),"B A N G ! ! ! !\n");
        ob->heal_hp(-f_str);
        do_combat_mess(ob,f_str);
        if(ob->query_hp() <= 0)
           ob->do_die(TO);
        remove_object();
    }
}

void
explode_in_room(object room, object *mes)
{
    int i,dam,loc;
    string *dirs,dir,dirdir,*dirdirs;
    object *occs;
    occs = all_inventory(room);
    for(i=0;i<sizeof(occs);i++)
    {
        if(!living(occs[i]))
            occs -= ({occs[i]});
    }
    if(sizeof(mes))
    {
        for(i=0;i<sizeof(mes);i++)
        {
            if(present(mes[i],room))
                occs -= ({mes[i]});
        }
    }
    dirs = room->query_exit_rooms();
    dirdirs = room->query_exit_cmds();
    for(i=0;i<sizeof(occs);i++)
    {
        loc = random(sizeof(dirs));
        dir = dirs[loc];
        dirdir = dirdirs[loc];
        dam = (70 * f_str) / 100;
        occs[i]->heal_hp(-dam);
        if(occs[i]->query_hp() <= 0)
            occs[i]->do_die(TO);
        do_combat_mess(occs[i],dam);
        if(dir)
        {
            tell_object(occs[i],"You are blown away!\n");
            tell_room(E(occs[i]),QCTNAME(occs[i])+" goes flying "+
            dirdir+"!\n",occs[i]);
            occs[i]->move_living("M",dir);
            tell_room(E(occs[i]),QCTNAME(occs[i])+" comes flying "+
            "in and lands with a thud!\n",occs[i]);
            tell_object(occs[i],"You land with a thud!\n");
       }
    }
}
    

void
explode_in_person(object per,object me)
{
    int dam,loc;
    string *dirs,*rooms,dir,room;
    dam = query_fire_str();
    tell_room(E(per),"The "+short()+" explodes everywhere, "+
    "hurting "+QTNAME(per)+" the most!\n",per);
    tell_object(per,"The "+short()+" explodes everywhere, "+
    "hurting you the most!\n");
    do_combat_mess(per,dam);
    explode_in_room(E(per),({me,per}));    
    per->heal_hp(-dam);
    if(per->query_hp() <= 0)
        per->do_die(TO);
    dirs = E(me)->query_exit_cmds();
    rooms = E(me)->query_exit_rooms();
    loc = random(sizeof(dirs));
    if(sizeof(dirs))
    {
        dir = dirs[loc];
        room = rooms[loc];
        tell_room(E(per),QCTNAME(per)+" goes flying "+dir+
        "!\n",per);
        tell_object(per,"You go are blown away!\n");
        per->move_living("M",room);
        tell_room(E(per),QCTNAME(per)+" comes flying in and "+
        "lands with a thud!\n",per);
        tell_object(per,"You land with a thud!\n");
    }
}
int
do_throw(string str)
{
    string dir,*dirs,*rooms,room;
    object bot,fire,target,oroom;
    NF("What?\n");
    if(TP->query_guild_name_lay() != "Shadow Walkers")
        return 0;
    NF("Throw what?\n");
    if(!parse_command("throw "+str,E(TP),"'throw' %o 'at' %o",bot,target))
    {
        if(!parse_command("throw "+str,E(TP),"'throw' %o %s",bot,dir)) 
            return 0;
    }
    if(!bot)
        return 0;
    if(bot != TO)
        return 0;
    NF("The "+short()+" is not lit.\n");
    if(lit == 0)
        return 0;
    if(dir && !target)
    {
        if(dir == "here")
        {
            oroom = E(TP);
            write("You hurl the "+short()+" to the ground!\n");
            say(QCTNAME(TP)+" hurls the "+short()+" to the ground!\n");
            explode_in_room(oroom, ({TP}) );
            remove_object();
            return 1;
        }
        rooms = E(TP)->query_exit_rooms();
        dirs = E(TP)->query_exit_cmds();
        NF("Throw it where?\n");
        if(!dir)
            return 0;
        NF("There is no direction "+dir+".\n");
        if(member_array(dir,dirs) == -1)
            return 0;
        room = rooms[member_array(dir,dirs)];
        oroom = find_object(room);
        write("You hurl the "+short()+" to the "+dir+"!\n");
        tell_room(room,"A "+short()+" comes flying in!\n");
        tell_room(room,"B O O M ! ! ! It explodes!\n");
        if(!oroom)
            tell_room(E(TP),"BUG!\n");
        explode_in_room(oroom, ({TP}) );
        remove_object();
        return 1;               
    }
    if(target)
    {
        NF("You can only throw it at living objects.\n");
        if(!living(target))
            return 0;
        NF("You don't want to throw it at yourself.\n");
        if(target == TP)
            return 0;    
        if(target->query_prop(OBJ_M_NO_ATTACK))
        {
            write(target->query_prop(OBJ_M_NO_ATTACK)+".\n");
            return 1;
        }
        TP->catch_msg("You hurl the "+short()+" at "+QTNAME(target)+
        "!\n");
        tell_object(target,QCTNAME(TP)+" hurls the "+short()+" at "+
        "you!\n");
        tell_room(E(TP),QCTNAME(TP)+" hurls the "+short()+" at "+
        QTNAME(target)+"!\n",({target,TP}));
        explode_in_person(target,TP);
        remove_object();
        return 1;
    }    
} 
