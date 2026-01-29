inherit "/std/object";
#include "/d/Kalad/defs.h"

#define KALAD_SHADOW_WIRE   "_kalad_shadow_wire"


/* Sarr */

int hooked,hidden_level;
string type;
float cloud_power;
int fire_str;


int know_it_there(object ob);
int can_see_it(object ob);
void set_hooked(object ob);
mixed query_hooked();
void set_hidden_level(int i);
int query_hidden_level();
void set_off_trap(object ob);
void set_off_bomb_trap(object ob);
void set_off_net_trap(object ob);
void set_off_dust_trap(object ob);

/* Set the type of trap hooked to wire */

void
set_hooked(object ob)
{
    if(MASTER_OB(ob) == "/d/Kalad/common/guilds/shadow_walkers/fire_bomb")
    {
        hooked = 1;
        fire_str = ob->query_fire_str();
        type = "bomb";
    }
    if(MASTER_OB(ob) == "/d/Kalad/common/guilds/shadow_walkers/net")
    {
        hooked = 1;
        type = "net";
    }
    if(MASTER_OB(ob) == "/d/Kalad/common/guilds/shadow_walkers/dust")
    {
        hooked = 1;
        cloud_power = itof(query_hidden_level() / 2);
        type = "dust";
    }
}

/* tells what kind of trap is hooked to the wire */   
mixed
query_hooked()
{
    if(hooked)
        return type;
    return 0;
}

void
create_object()
{
    set_name("wire");
    set_short("wire");
    set_long("@@wire_long@@");
    set_short("carefully hidden wire");
    add_prop(OBJ_M_NO_GET,"@@wire_get@@");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME,1);
    set_no_show_composite(1);
}

void
init()
{
    ::init();
    AA(do_disarm,disarm);
    if(living(TP))
        set_alarm(0.2,0.0,"check_trap",TP);
}

/* try to disarm the trap */

int
do_disarm(string str)
{
    object wire;
    NF("Disarm what?\n");
    if(!parse_command("disarm "+str,E(TP),"'disarm' %o",wire))
        return 0;
    if(!know_it_there(TP))
        if(!can_see_it(TP))
            return 0;
    if(!wire)
        return 0;
    if(wire != TO)
        return 0;
    write("You attempt to disarm the trap....\n");
    say(QCTNAME(TP)+" attempts to disarm the trap...\n");
    set_alarm(3.0,0.0,"disarm_try",TP);
    return 1;
}

void
disarm_try(object ob)
{
    if( ( ob->query_skill(SS_FR_TRAP) + MIN(50,(ob->query_stat(1) / 2)) ) >= hidden_level)
    {
        tell_object(ob,"You sucessfully disarm the trap!\n");
        tell_room(E(ob),QCTNAME(TP)+"bdisarms the trap!\n",ob);
        seteuid(getuid());
        if(type == "bomb")
        {
clone_object("/d/Kalad/common/guilds/shadow_walkers/fire_bomb")->move(E(ob));
clone_object("/d/Kalad/common/guilds/shadow_walkers/wire")->move(E(ob));
        }
        if(type == "net")
        {
clone_object("/d/Kalad/common/guilds/shadow_walkers/net")->move(E(ob));
clone_object("/d/Kalad/common/guilds/shadow_walkers/wire")->move(E(ob));
        }
        if(type == "dust")
        {
clone_object("/d/Kalad/common/guilds/shadow_walkers/wire")->move(E(ob));
clone_object("/d/Kalad/common/guilds/shadow_walkers/dust")->move(E(ob));
        }
        remove_object();
        return;
    }
    tell_object(ob,"Oh shit! You messed up, and sprung it!\n");
    tell_room(E(ob),QCTNAME(ob)+" messed up and sprung the trap!\n",ob);
    set_off_trap(ob);
}

/* called when someone enters the room, and see if they spring it */
void
check_trap(object ob)
{
    if(know_it_there(ob))
    {
        ob->catch_msg("You remember that there is a trap here, and "+
        "carefully avoid it.\n");
        return;
    }
    if(can_see_it(ob))
    {
        ob->catch_msg("You see a strange wire running accross "+
        "the room and carefully avoid it. It could use some "+
        "closer examination though.\n");
        if(ob->query_prop(KALAD_SHADOW_WIRE) == 0)
            ob->add_prop(KALAD_SHADOW_WIRE,({}));
        ob->add_prop(KALAD_SHADOW_WIRE,ob->query_prop(KALAD_SHADOW_WIRE)+
        ({file_name(TO)}));
        return;
    }
    if(hooked)
    {
    ob->catch_msg("You trip over a wire and it springs a trap!\n");
    tell_room(E(ob),QCTNAME(ob)+" trips over a wire and springs "+
    "a trap!\n",ob);
    set_off_trap(ob);
    }
    else
    {
    ob->catch_msg("You trip over a wire and it falls to the ground.\n");
    tell_room(E(ob),QCTNAME(ob)+" trips over a wire.\n",ob);
    seteuid(getuid());
    clone_object("/d/Kalad/common/guilds/shadow_walkers/wire")->move(E(ob));
    remove_object();
    }
}

string
wire_long()
{
    if(know_it_there(TP) || can_see_it(TP) )
    {
       if(hooked)
       {
           if(type == "bomb")
           return "You see a long, thin wire carefully hidden with a "+
           "bottle set to implode on when someone pulls it.\n";
           if(type == "net")
           return "You see a long, thin wire carefully hidden with "+
           "a net concealed overhead to drop on someone who "+
           "pulls it.\n";
           if(type == "dust")
           return "You see a long, thin wire carefully hidden with "+
           "a bag hooked to explode outward into the room.\n";
        }
        else
           return "You see a long, thin wire carefully hidden.\n";
    }
    return "You find no wire.\n";
}

string
wire_get()
{
    set_no_show_composite(0);
    set_alarm(0.1,0.0,"trigger",TP);
    return 0;
}



/* Sets off the trap */
void
trigger(object ob)
{
    if(hooked)
    {
        ob->catch_msg("Oh shit! You just set off the trap!\n");
        tell_room(E(ob),QCTNAME(ob)+" ignorantly sets off "+
        "the trap by pulling on the trip wire.\n",ob);
        seteuid(getuid());
        clone_object("/d/Kalad/common/guilds/shadow_walkers/wire")->move(ob);
        set_off_trap(ob);
        remove_object();
    }
    else
    {
        seteuid(getuid());
        clone_object("/d/Kalad/common/guilds/shadow_walkers/wire")->move(ob);
        remove_object();
    }
}

/* checks to see if you know the trap is there */

int
know_it_there(object ob)
{
    int i;
    string *traps,t_trap;
    traps = ob->query_prop(KALAD_SHADOW_WIRE);
    t_trap = file_name(TO);
    for(i=0;i<sizeof(traps);i++)
    {
        if(t_trap == traps[i])
            return 1;
    }
    return 0;
}

/* sets how well the trap is hidden */

void
set_hidden_level(int i)
{
    hidden_level = i;
}

int
query_hidden_level()
{
    return hidden_level;
}

/* checks to see if ob can see the trap */

int
can_see_it(object ob)
{
    int s_wis,awa,fr,total,intox;
    intox = TP->max_intoxicated();
    if(!intox)
        intox = 1;
    s_wis = MIN(120,ob->query_stat(4));
    awa = ob->query_skill(SS_AWARENESS);
    fr = ob->query_skill(SS_FR_TRAP);
    total = awa+fr+(s_wis/8) - (100*(TP->query_intoxicated()/intox));
    total = total + random(s_wis/8);
    if(total >= hidden_level)
            return 1;
    else
    {
        if(random(100) > 80)
           return 1;
        return 0;
    }
}
/* determine what kind of trap, and set it off */

void
set_off_trap(object ob)
{
    if(type == "bomb")
        set_off_bomb_trap(ob);
    if(type == "net")
        set_off_net_trap(ob);
    if(type == "dust")
        set_off_dust_trap(ob);
}

/* The types of traps to set off: */
void
set_off_dust_trap(object ob)
{
    object cloud;
    tell_room(E(ob),"A bag filled with dust explodes, spraying dust "+
    "everywhere and clouding up the room in darkness!\n");
    seteuid(getuid());
    cloud = clone_object("/d/Kalad/common/guilds/shadow_walkers/cloud");
    cloud->move(E(ob));
    cloud->set_cloud_time(cloud_power);
    remove_object();
}


void
set_off_bomb_trap(object ob)
{
    int dam;
    object fire;
    tell_room(E(ob),"\n\n\n\nB O O M ! ! ! \n\n\n\n");
    tell_object(ob,"You are hit hard by a fire blast in the "+
    "face!\n");
    tell_room(E(ob),QCTNAME(ob)+" is hit hard by a fire blast "+
    "in the face!\n",ob);
    dam = -random(100);
    dam = dam + ob->query_prop(MAGIC_I_RES_FIRE);
    if(dam > 0)
    {
        dam = 0;
        tell_object(ob,"You are not hurt by the fire.\n");
    }
    else
    {
        tell_object(ob,"You are burnt!\n");
        ob->heal_hp(dam);
        if(ob->query_hp() <= 0)
            ob->do_die(TO);
    }
    seteuid(getuid());
    fire = clone_object("/d/Kalad/common/guilds/shadow_walkers/fire");
    fire->set_fire_str(fire_str);
    fire->move(E(ob));
    tell_room(E(ob),"A blazing fire starts.\n");
    remove_object();
}

void
set_off_net_trap(object ob)
{
    int delay;    
    object net,netp;
    tell_object(ob,"A black leather net falls from the ceiling on "+
    "top of you, and you get tangled up!\n");
    tell_room(E(ob),"A black leather net falls from the ceiling "+
    "on top of "+QTNAME(ob)+" and "+HE(ob)+" gets all tangled up!\n",ob);
    netp = clone_object("/d/Kalad/common/guilds/shadow_walkers/netp");
    delay = MAX(10,(100 - ob->query_stat(0)));
    netp->set_remove_time(delay);
    netp->move(ob);
    ob->add_attack_delay(delay);
    remove_object();
}

