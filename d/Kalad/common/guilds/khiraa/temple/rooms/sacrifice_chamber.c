/*     Created by:      Sarr
 *     purpose:		
 *     Location:         
 *     Modified:        Sir Toby, 97-09-18 (fixed a bunch of typos..)
 */

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <cmdparse.h>
#pragma strict_types
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In a magical and macabre room");

    set_long("\n   You are in a small but cold feeling room. Shadows "+
    "lie everywhere. The floor is made of solid black marble, but has "+
    "many markings and signs on it, most noticably a grim skull etched "+
    "within a pentagram. The smell of blood, decay and rotting flesh "+
    "is very strong here.\n"+
    "   There is a large black altar on the north wall, surrounded by "+
    "small skulls with purple flames burning within them.\n\n");
    
    add_item("ceiling","The ceiling here is low, and is made of "+
    "solid black stone blocks.\n");
    add_item("walls","The walls are, like the ceiling, made of "+
    "black stone. They are marked with magical symbols and signs.\n");
    add_item("floor","The floor is made of solid, black marble. There "+
    "are many circles, hexagrams, pentagrams and other symbols on it. "+
    "The largest being a pentagram with a grim skull in its center.\n");
    add_item("pentagram","This large pentagram is located in the "+
    "very center of the room. A large picture of a grim skull lies "+
    "within its very center.\n");
    add_item("altar","The altar is made of solid black marble, and "+
    "is covered with all sorts of magical symbols, runes and wards "+
    "imaginable. There are blood stains on its surface.\n");

    INSIDE;
   
}

int
do_kneel(string str)
{
    NF("Kneel before what?\n");
    if(str != "before altar")
        return 0;
    write("You kneel before the altar and slowly fade away.\n");
    say(QCTNAME(TP)+" kneels before the altar and slowly fades away.\n");
    TP->move_living("M",KHIRAA_DIR(temple/rooms/t16));
    say(QCTNAME(TP)+" slowly fades into view.\n");
    return 1;
}

int 
do_fail(object me)
{
    tell_object(me,"Something has gone wrong.\n");
    return 1;
}

int
rsk6(object me)
{
    object crps,skll;
    set_this_player(me);
    crps = present("corpse",TO);
    if(!objectp(crps))
        return do_fail(me);
    skll = clone_object(KHIRAA_DIR(temple/obj/rat_skull));
    
    write("You speak the burning words of the Necro King, and the "+
    "flame dissapears, leaving a "+skll->short()+" behind.\n");
    say(QCTNAME(TP)+" speaks the burning words of the Necro King, "+
    "and the flame dissapears, leaving a "+skll->short()+" behind.\n");
    skll->move(TO);
    crps->remove_object();
    return 0;
}


int
rsk5(object me)
{
    object crps,vine,hem;
    set_this_player(me);
    crps = present("corpse",TO);
    vine = FIND_STR_IN_OBJECT("black red-pitted vine",TO)[0];
    hem = FIND_STR_IN_OBJECT("handful of green berries",TO)[0];
    if(!objectp(crps) || !objectp(vine) || !objectp(hem))
        return do_fail(me);
    write("You scatter the "+hem->short()+" around the "+crps->short()+
    " while chanting more prayers.\n");
    say(QCTNAME(TP)+" scatters the "+hem->short()+" around the "+
    crps->short()+" while chanting more prayers.\n");
    hem->remove_object();
    write("Then you wrap the "+crps->short()+" up with the "+vine->short()+
    ".\n");
    say("Then "+QTNAME(TP)+" wraps the "+crps->short()+" up with the "+
    vine->short()+".\n");
    vine->remove_object();
    set_alarm(3.0,0.0,&tell_room(TO,"The flesh of the "+crps->short()+
    " begins to burn in a green flame!\n"));
    set_alarm(5.0,0.0,&tell_room(TO,"The "+crps->short()+" starts to "+
    "decay and melt while being consumed by the growing green flame.\n"));
    set_alarm(8.0,0.0,&rsk6(me));
    return 0;
}


int
rsk4(object me)
{
    object crps;
    set_this_player(me);
    crps = present("corpse",TO);
    if(!objectp(crps))
        return do_fail(me);
    write("You chant the unholy words: By Pazuzu, Mistress of "+
    "Plague, by Him, our Lord of All, by Shaadok Y'Sulgash and "+
    "Ke'lets, they who give us the Power of Might, bring forth "+
    "your Powers together, and grant us a piece in this offering "+
    "to you by your humble servants...\n");
    say(QCTNAME(TP)+" chants: By Pazuzu, Mistress of Plague, by "+
    "Him, our Lord of All, by Shaadok Y'Sulgash and Ke'lets, they "+
    "who give us the Power of Might, bring forth your Powers together, "+
    "and grant us a piece in this offering to you by your humble "+
    "servants...\n");
    set_alarm(4.0,0.0,&tell_room(TO,"The "+crps->short()+" begins to "+
    "glow a sickly green color.\n"));
    set_alarm(6.0,0.0,&tell_room(TO,"The "+crps->short()+" glows "+
    "brighter.\n"));
    set_alarm(9.0,0.0,&rsk5(me));
    return 0;
}


int
rsk3(object me)
{
    object crps,finger,drudge;
    set_this_player(me);
    crps = present("corpse",TO);
    finger = FIND_STR_IN_OBJECT("bloody dismembered finger",TO)[0];
    if(!objectp(crps) || !objectp(finger))
        return do_fail(me);
    write("The "+finger->short()+" you hold crumbles to dust.\n");
    say("The "+finger->short()+" held by "+QTNAME(TP)+" crumbles to "+
    "dust.\n");
    finger->remove_object();
    drudge = FIND_STR_IN_OBJECT("slimy black mushroom",TO)[0];
    finger = FIND_STR_IN_OBJECT("bloody dismembered finger",TO)[0];
    if(!objectp(finger) || !objectp(drudge))
        return do_fail(me);
    write("You pick up the other one, along with the "+drudge->short()+
    ".\n");
    say(QCTNAME(TP)+" picks up another one, along with a "+drudge->short()+
    ".\n");
    write("You place the "+finger->short()+" and "+drudge->short()+
    " inside the "+crps->short()+".\n");
    set_alarm(3.0,0.0,&tell_room(TO,"The eyes of the "+crps->short()+
    " begin to glow slightly.\n"));
    finger->remove_object();
    drudge->remove_object();
    set_alarm(8.0,0.0,&rsk4(me));
    return 0;
}


int
rsk2(object me)
{
    object crps,finger;
    set_this_player(me);
    crps = present("corpse",TO);
    finger = FIND_STR_IN_OBJECT("bloody dismembered finger",TO)[0];
    if(!objectp(crps) || !objectp(finger))
        return do_fail(me);
    write("You draw the symbols of Pazuzu along the torso of the "+
    crps->short()+" with the "+finger->short()+".\n");
    say(QCTNAME(TP)+" draws some symbols along the torso of the "+
    crps->short()+" with the "+finger->short()+".\n");
    set_alarm(2.0,0.0,&tell_room(TO,"The "+crps->short()+"'s torso "+
    "suddenly splits open, and its insides begin to rot away in a "+
    "stinking heap.\n"));
    set_alarm(6.0,0.0,&rsk3(me));
    return 0;
}

int
do_create_rat_skull(object me)
{
    int i;
    object *obs;
    string *test,temp;
    set_this_player(me);
    obs = all_inventory(TO);
    test = ({"finger","finger","hemlock","corpse of rat","drudgeworth",
    "vinerot" });
    for(i=0;i<sizeof(obs);i++)
    {
        if(member_array(obs[i]->query_herb_name(),test) != -1)
            test -= ({obs[i]->query_herb_name()});
        if(obs[i]->id("corpse of rat"))
        {
            temp = "corpse of rat";
            if(member_array(temp,test) != -1)
                test -= ({temp});
        }
        if(obs[i]->id("finger"))
        {
            temp = "finger";
            if(member_array(temp,test) != -1)
                test -= ({temp});
        }
    }
    
    if(sizeof(test))
    {
        write("You must put all the proper sacrifices on the ground "+
        "here in order to perform the ceremony of the 'rat skull'.\n");
        return 1;
    }
    if(!present("_khiraa_chain2_",TP))
    {
        write("You are not wearing the proper medallions.\n");
        return 1;
    }
    write("You kneel on the ground and begin to chant the magical "+
    "prayer words.\n");
    say(QCTNAME(TP)+" kneels on the ground and begins to chant the "+
    "magical prayer words.\n");
    set_alarm(5.0,0.0,&rsk2(me));
    return 1;
}


int
pd6(object me)
{
    object doll;
    set_this_player(me);
    doll = present("doll",TO);
    if(!objectp(doll))
        return do_fail(me);
    write("You chant a harsh word, and wave your hands over the "+
    doll->short()+" and it begins to spin.\n");
    say(QCTNAME(TP)+" chants a harsh word, and waves "+HIS(TP)+
    " hands over the "+doll->short()+" and it begins to spin.\n");
    tell_room(TO,"It suddenly stops, and there now lies a plague doll.\n");
    doll->remove_object();
    doll = clone_object(KHIRAA_DIR(temple/obj/plague_doll));
    doll->move(TO);
}

int
pd5(object me)
{
    object doll,vial;
    set_this_player(me);
    vial = present("vial",TO);
    doll = present("doll",TO);
    if(!objectp(doll) || !objectp(vial))
        return do_fail(me);
    write("You pour the blood from the "+vial->short()+" over the "+
    doll->short()+" while chanting praises to Him.\n");
    say(QCTNAME(TP)+" pours the blood from the "+vial->short()+
    " over the "+doll->short()+" while chanting praises to Him.\n");
    vial->set_contents(({0,"none"}));
    set_alarm(5.0,0.0,&tell_room(TO,"The "+doll->short()+" begins "+
    "to shrivel and become horribly mangled!\n"));
    set_alarm(7.0,0.0,&pd6(me));
}

int
pd4(object me)
{
    object doll,vial;
    set_this_player(me);
    vial = present("vial",TO);
    doll = present("doll",TO);
    if(!objectp(doll) || !objectp(vial))
        return do_fail(me);
    write("With the poison in your body, you chant in ecstacy: "+
    "By Pazuzu and the Death King, grant me a shred of your soul, "+
    "that I may further your will of evil in this world....\n");
    say(QCTNAME(TP)+" chants in ecstacy: By Pazuzu and the Death "+
    "King, grant me a shred of your soul, that I may further your will "+
    "of evil in this world....\n");
    set_alarm(7.0,0.0,&pd5(me));
}

int
pd3(object me)
{
    object dajla,ml,doll;
    set_this_player(me);
    dajla = present("mushroom",TO);
    ml = present("berry",TO);
    doll = present("doll",TO);
    if(!objectp(doll) || !objectp(ml) || !objectp(dajla))
        return do_fail(me);
    write("You then smash the "+ml->short()+" over the "+doll->short()+
    " and let its juices spread over its head.\n");
    say(QCTNAME(TP)+" then smashes the "+ml->short()+" over the "+
    doll->short()+" and lets its juices spread over its head.\n");
    write("You pick up the "+dajla->short()+" and eat it, feeling "+
    "its poison course through your body...\n");
    say(QCTNAME(TP)+" picks up the "+dajla->short()+" and eats it, "+
     "shivering slightly.\n");
    dajla->remove_object();
    ml->remove_object();
    set_alarm(6.0,0.0,&pd4(me));
}


int
pd2(object me)
{
    object doll,fennel;
    set_this_player(me);
    doll = present("doll",TO);
    fennel = present("leaves",TO);
    if(!objectp(doll) || !objectp(fennel))
        return do_fail(me);
    write("You crush the "+fennel->short()+" in your hands and "+
    "sprinkle its crumbs over the "+doll->short()+" while chanting "+
    "the magic prayer words.\n");
    say(QCTNAME(TP)+" crushes the "+fennel->short()+" in "+HIS(TP)+
    " hands and sprinkles its crumbs over the "+doll->short()+" "+
    "while chanting magic prayer words.\n");
    fennel->remove_object();
    set_alarm(6.0,0.0,&pd3(me));
    return 0;
}


int
do_create_plague_doll(object me)
{
    int i;
    object *obs;
    string *test,temp;
    set_this_player(me);
    obs = all_inventory(TO);
    test = ({"doll","dajla","vial","fennel","mindleech" });
    for(i=0;i<sizeof(obs);i++)
    {
        if(member_array(obs[i]->query_herb_name(),test) != -1)
            test -= ({obs[i]->query_herb_name()});
        if(obs[i]->id("vial"))
        {
            temp = "vial";
            if(obs[i]->query_contents()[0] == 1 &&
               obs[i]->query_contents()[1] == "human")
                test -= ({temp});
        }
        if(obs[i]->id("doll"))
        {
            temp = "doll";
            if(member_array(temp,test) != -1)
                test -= ({temp});
        }
    }
    
    if(sizeof(test))
    {
        write("You must put all the proper sacrifices on the ground "+
        "here in order to perform the ceremony of the 'plague doll'.\n");
        return 1;
    }
    if(!present("_khiraa_chain2_",TP))
    {
        write("You are not wearing the proper medallions.\n");
        return 1;
    }
    write("You kneel on the ground and begin to chant the magical "+
    "prayer words.\n");
    say(QCTNAME(TP)+" kneels on the ground and begins to chant the "+
    "magical prayer words.\n");
    set_alarm(5.0,0.0,&pd2(me));
    return 1;
}


int
do_create(string str)
{
    NF("Create what?\n");
    switch(str)
    {
        case "rat skull":
            return do_create_rat_skull(TP);
        break;
        case "plague doll":
            return do_create_plague_doll(TP);
        default:
            return 0;
    }
    return 0;
}


void
init()
{
    ::init();
    AA(do_kneel,kneel);
    AA(do_create,create);
    AA(do_depart,depart);
}

int
do_depart(string str)
{
    int i;
    object *us;
    NF("Depart where?\n");
    if(str != "blood")
        return 0;
    NF("You can't do that.\n");
    if(!present("_kmaster_key_",TP))
        return 0;
    write("You enter the room of Blood.\n");
    us = FILTER_LIVE(all_inventory(TO));
    for(i=0;i<sizeof(us);i++)
    {
        tell_object(us[i],"You feel transported to another realm!\n");
        us[i]->move_living("X",KHIRAA_DIR(temple/rooms/blood_realm));
    }
    return 1;
}

