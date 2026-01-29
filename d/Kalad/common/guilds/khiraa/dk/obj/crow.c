/*
 * Post rat by Milan. 9.3.94.
 * Time of delivery depends slightly on distance (domains check)
 * It is of course longer than pigeon times...
 * But rats have advantage that they go indoor, can swim well and
 * generally there is almost NO place that rat cant get in.
 *  
 * All this is modification of Gondor pigeon.
 */
/*
 *  Carrier pigeon.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 *  added 'return' from /d/Genesis/obj/pigeon.c, Olorin, July 1993
 */

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/cmd/std/command_driver"; /* For emotes */

#include "/d/Kalad/defs.h"

#define TEMP_ROOM "/d/Kalad/common/wild/pass/drow/spider_room"
#define MESSAGE "/d/Kalad/common/wild/pass/drow/obj/message"

string  gWho, gSender, gMessage = "";
object  owner;

void 
create_creature()
{
    set_name("crow");
    set_race_name("crow");
    set_adj(({"black","eerie"}));
    set_short("eerie black crow");
    set_long("This is a large crow with strange red eyes and a sharp "+
    "black beak. It ruffles its feathers and caws with an eerie voice.\n"+
    "  You can 'send <name>' to send a message to a person with it.\n"+
    "  You can 'send home' to send it away.\n"+
    "  You can 'send reply' to send back to the person who sent it.\n"+
    "  You can do 'crow emotes' also.\n");
    add_prop(CONT_I_WEIGHT,550);
    add_prop(CONT_I_VOLUME,550);
    remove_prop(OBJ_I_NO_GET);
    remove_prop(OBJ_I_NO_DROP);
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_attack_unarmed(0, 5, 5, W_IMPALE, 30, "beak");
    set_attack_unarmed(1, 5, 5, W_IMPALE, 35, "left talon");
    set_attack_unarmed(2, 5, 5, W_IMPALE, 35, "right talon");
    set_hitloc_unarmed(0, ({ 5, 7, 3}), 30, "head");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 60, "body");
    set_hitloc_unarmed(2, ({ 5, 7, 3}), 10, "legs");
}

void 
init_living()
{
    ::init_living();
    add_action("do_send","send",0);
    add_action("do_crow","crow");
    add_action("do_crowcaw","crowcaw");
    add_action("do_crowflap","crowflap");
    add_action("do_crowpeer","crowpeer");
    add_action("do_crowblaze","crowblaze");
    add_action("do_crowlaugh","crowlaugh");
}

int
do_crowlaugh()
{
    write("The "+short()+" on your shoulder begins to caw out a "+
    "sinister, horrible laugh.\n");
    say("The "+short()+" on "+QTNAME(TP)+"'s shoulder begins to "+
    "caw out a sinister, horrible laugh.\n");
    return 1;
}


int
do_crowblaze()
{
    write("The eyes of the "+short()+" on your shoulder suddenly glow bright "+
    "red.\n");
    say("The eyes of the "+short()+" on "+QTNAME(TP)+"'s shoulder "+
    "suddenly glow bright red.\n");
    return 1;
}

int
do_crowpeer(string str)
{
    object *obs;
    NF("Crowpeer at whom?\n");
    obs = parse_this(str,"[the] %l");
    if(!sizeof(obs))
        return 0;
    TP->catch_msg("The "+short()+" on your shoulder cocks its head to the "+
    "side and peers at "+QTNAME(obs[0])+".\n");
    obs[0]->catch_msg("The "+short()+" on "+QTNAME(TP)+"'s shoulder cocks "+
    "its head to the side and peers at you.\n");
    tell_room(E(TP),"The "+short()+" on "+QTNAME(TP)+"'s shoulder cocks "+
    "its head to the side and peers at "+QTNAME(obs[0])+".\n", ({obs[0],TP}));
    return 1;
}

int
do_crowflap(string str)
{
    string adv;
    adv = parse_adverb(str,"noisily",1)[1];
    write("The "+short()+" on your shoulder flaps its wings "+adv+".\n");
    say("The "+short()+" on "+QTNAME(TP)+"'s shoulder flaps its wings "+
    adv+".\n");
    return 1;
}

int
do_crowcaw(string str)
{
    string adv;
    adv = parse_adverb(str,"loudly",1)[1];
    write("The "+short()+" on your shoulder caws "+adv+".\n");
    say("The "+short()+" on "+QTNAME(TP)+"'s shoulder caws "+adv+".\n");
    return 1;
}


int
do_crow(string str)
{
    NF("Crow what?\n");
    if( str != "emotes")
        return 0;
    write("Crow emotes available: \n"+
    "crowcaw  [adverb]  -  Make your crow caw.\n"+
    "crowflap [adverb]  -  Make your crow flap its wings.\n"+
    "crowpeer [target]  -  Make your crow peer at a target.\n"+
    "crowblaze          -  Make your crow's eye's glow.\n"+
    "crowlaugh          -  Make your crow laugh.\n");
    return 1;
}


int 
do_send(string who)
{
    object target;

    if (!who || who == "")
        return 0;
    if (TP != environment())
        return 0;
    if ( who == "home")
    {
        tell_room(E(TP),"The "+short()+" flies back to Raumdor.\n");
        remove_object();
        return 1;
    }
    if (who == "reply")
    {
        if(!owner)
        {
            NF("You are the first sender of a message. You cannot reply.\n");
            return 0;
        }
        who = gSender;
    }
    gSender = lower_case(TP->query_real_name());
    gWho = lower_case(who);
    target = find_player(gWho);

 /* It is useless to write a message to someone who isn't in the game. */
    if (!objectp(target))
    {
        NF("There is no '"+who+"' logged in!\n");
        return 0;
    }
    if(!owner) 
        owner = TP;
    say(QCTNAME(TP)+" starts to write a message.\n");
    write("Enter your message.\n"
       + "On any line you can give ** to end, or ~q to abort the message.\n");
    gMessage = "";
    write("-->");
    input_to("write_more");
    return 1;
}

float 
deliv_time(object ob1, object ob2)
{
    if(environment(ob1) == environment(ob2)) 
        return itof(random(10));
    if(explode(MASTER_OB(environment(ob1)),"/")[2] == 
    explode(MASTER_OB(environment(ob2)),"/")[2])
        return itof(60+random(30));
    return itof(120+random(60));
} 

int 
send_mail()
{
    if (gMessage == "")
    {
        NF("Message aborted.\n");
        return 0;
    }
    write("You give the message to the "+query_short()+".\n");
    say(QCTNAME(TP)+" gives a message to "+
    TP->query_possessive()+" "+query_short()+".\n");
    tell_room(environment(TP),"The "+query_short()+" caws loudly, "+
    "then flaps its wings and flies away.\n");
    /* Move the object to a temporary room */
    move(TEMP_ROOM);
    set_alarm( deliv_time(find_player(gWho),find_player(gSender)),
    0.0,"deliver");   
    return 1;
}

int 
write_more(string str)
{
    if (str == "**")
    {
        send_mail();
        return 1;
    }
    if (str == "~q")
    {
        write("Message aborted.\n");
        gMessage = "";
        return 1;
    }
    gMessage += (str + "\n");
    write("-->");
    input_to("write_more");
    return 1;
}

void 
return_home()
{
    object room;
    if (living(room = environment()))
        room = environment(room);
    tell_room(room,"The "+short()+" flies back to its master.\n");
    if(objectp(owner) && find_player(lower_case(owner->query_name())))
    {
            move(owner);
            tell_object(owner,"You're "+short()+" flies out of the "+
            "sky and returns to your shoulder.\n");
            tell_room(E(owner),"A "+short()+" flies out of the sky and "+
            "lands on "+QTNAME(owner)+"'s shoulder.\n",owner);
    }
    else
        remove_object();
}

int 
deliver()
{
    object target, message;

    /* Does our initial target still exist? */
    target = find_player(gWho);
    if (!target)
    {
        /* Does our sender still exist? */
        target = find_player(gSender);
        if (!target)
        {
            remove_object();
            return 1;
        }
    }

    /* Go to the target */
    move(target);
    if (target == find_player(gSender))
        tell_object(target, "Your "+short()+" returns, "+
        "unable to find "+capitalize(gWho)+". It gives you " +
        "back your message.\n");
    else
        tell_object(target,"A "+short()+" flies down and lands on your "+
        "shoulder and gives you a message from "+capitalize(gSender)+".\n");

    tell_room(E(target),"A "+short()+" flies down to "+QTNAME(target)+", "+
    "lands on "+HIS(target)+" shoulder and gives "+HIM(target)+" a message.\n",
    target);
    seteuid(getuid());
    message = clone_object(MESSAGE);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
    if (target != owner)
        set_alarm(60.0,0.0,"return_home"); 
    else 
        gMessage = "";
}

void 
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if(living(dest))
    {
        if(!objectp(owner))
            owner = dest;
        if(!objectp(dest->query_subloc_obj("dk_crow_subloc")))
            dest->add_subloc("dk_crow_subloc",TO);
    }
    if((gMessage == "") && (dest->query_prop(ROOM_I_IS)))
        set_alarm(itof(random(10)),0.0,"return_home"); 
}     

void
leave_env(object from, object to)
{
    object *obs;
    ::leave_env(from,to);
    if(living(from))
    {
        from->remove_subloc("dk_crow_subloc");
    }
}


string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if(subloc != "dk_crow_subloc")
        return "";
    if (for_obj == carrier)
        str = "your";
    else
        str = HIS(carrier);  
   return "An "+short()+" is perched on "+str+" shoulder.\n";
}
