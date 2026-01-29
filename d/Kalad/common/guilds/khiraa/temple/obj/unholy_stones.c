inherit "/std/object";
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/unholy_stones.c
 * Purpose    : Can form symbols on the ground with them.
 * Located    : Bought from Werners
 * Created By : Sarr 11.Jun.97
 * Modified By: 
 */

int portal_opened;
int scattered;
string symbol;

void scatter_stones(string style, object ob);
int  create_symbol(string str);
int  summon_demon(string str);

void
create_object()
{
    set_name("stones");
    add_name("_babi_unholy_stones_");
    set_adj("unholy");
    set_short("@@stones_short@@");
    set_pshort("@@stones_pshort@@");
    set_long("@@stones_long@@");

    add_prop(MAGIC_AM_ID_INFO,({"These are magical stones blessed by "+
    "the powers of the Underworld Demon known as Babi. The are used for "+
    "obtaining a connection to this Underworld, as well as other "+
    "planes of existance. If the conjurer is bold enough, or foolhardy, "+
    "they may even try to summon other creatures to do their bidding.\n",20}));

    add_item(({"red portal","portal"}),"@@my_portal@@");
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_GET,"@@get_stones@@");
    setuid();
    seteuid(getuid());
}

string
my_portal()
{
    if(portal_opened == 1)
        return "A blazing red portal floats above the center of "+
    "these stones. You might try to enter it.\n";
    return "What portal?\n";
}

string
stones_pshort()
{
    if(scattered == 1)
        return symbol+"s on the ground formed by a handful of "+
    "unholy stones";
    return "handfulls of unholy stones of Babi";
}

string
stones_short()
{
    if(portal_opened == 1)
        return symbol+" on the ground with a red portal in its "+
    "center";
    if(scattered == 1)
        return symbol+" on the ground formed by a handful of "+
    "unholy stones";
    "center";
    return "handful of unholy stones of Babi";
}



string
stones_long()
{
    if(scattered == 1)
        return "These are a bunch of shiny, purple stones that glow "+
    "with a soft light. They are arranged in a "+symbol+" on the "+
    "ground here.\n";
    if(portal_opened == 1)
        return "These are a bunch of shiny, purple stones that glow "+
    "with a soft light. They are arranged in a "+symbol+" on the "+
    "ground here, and a red portal floats above its center.\n";
    if(IS_LP(TP) || IS_DK(TP))
        return "These are a handful of shiny, purple stones that "+
    "glow with a soft light. With them, you can create symbols on "+
    "the ground with 'create <symbol>'. The symbols available are: "+
    "pentagram, hexagram, circle, triangle, octagon and square. "+
    "When they are scattered, you can try to 'summon shadow'.\n";

    return "These are strange shiny stones that are deep purple "+
    "in color and glow with a soft light. You wonder what they do.\n";
}

int
do_enter(string str)
{
    if(portal_opened == 0)
        return 0;
    if(str != "portal")
        return 0;
    if(!IS_LP(TP) && !IS_DK(TP))
    {
        write("You feel that only death awaits you in there, so you do not "+
        "not dare to enter the portal.\n");
        return 1;
    }
    write("You enter the red portal.\n");
    say(QCTNAME(TP)+" enters the red portal in the center of the "+symbol+
    " and vanishes.\n");
    TP->move_living("M",KHIRAA+"temple/rooms/gateway_room");
    say(QCTNAME(TP)+" emerges from the green portal.\n");
    return 1;
}


void
init()
{
    ::init();
    add_action(create_symbol,"create");
    add_action(summon_demon,"summon");
    add_action(do_enter,"enter");
}

void
summon_shadow(object ob)
{
    object demon;
    demon = clone_object(KHIRAA+"temple/obj/shadow_demon");
    demon->move_living("M",E(ob));
    tell_room(E(ob),"From the center of the "+short()+", a "+
    demon->short()+" arises screaming in fury!\n");
    demon->set_master(ob);
}

int 
summon_demon(string str)
{
    object deamon;
    if(!IS_DK(TP) && !IS_LP(TP))
        return 0;
    if(scattered == 0)
        return 0;
    NF("There already is a demon summoned here.\n");
    if(present("baalzebub",E(TP)))
        return 0;
    NF("Summon what kind of demon forth?\n");
    if(!str)
        return 0;
    if(str == "shadow")
    {
        write("You chant magical words and spin your hands in "+
        "two directions, then point at the "+short()+".\n");
        say(QCTNAME(TP)+" chants magical words and spins "+HIS(TP)+
        " hands in two directions, then points at the "+short()+".\n");
        set_alarm(4.0,0.0,&summon_shadow(TP));
        tell_room(E(TP),"The "+short()+" begin to glow.\n");
        return 1;
    }
    return 0;
}


int
create_symbol(string str)
{
    if(!IS_LP(TP) && !IS_DK(TP))
        return 0;
    NF("Create what with the "+short()+"?\n");
    if(!stringp(str))
        return 0;
    if(member_array(str,({"pentagram","hexagram","circle","triangle",
        "octagon","square"})) == -1)
        return 0;
    scatter_stones(str,TP);
    return 1;
}
    
void
scatter_stones(string s,object ob)
{
    set_this_player(ob);
    symbol = s;
    write("You carefully set the "+short()+" around the ground to "+
    "form a "+symbol+".\n");
    say(QCTNAME(TP)+" carefully sets the "+short()+" around the "+
    "ground to form a "+symbol+".\n");
    scattered = 1;
    move(E(TP));
    add_name(s);
}

mixed
get_stones()
{
    if(objectp(E(TO)) && present("baalzebub",E(TO)))
    {
        return "You dare not disturb the symbol, else you might "+
         "end up dead.\n";
    }
    if(portal_opened == 1)
    {
        return "You dare not disturb the symbol with the portal "+
        "there.\n";
    }
    if(scattered == 1)
    {
        write("You mess up the symbol on the ground.\n");
        scattered = 0;
        remove_name(symbol);
        symbol = "none";
    }
    return 0;
}

int
test_create_portal()
{
    if(scattered == 0)
        return 0;
    if(present("baalzebub",E(TO)))
        return 0;
    if(portal_opened == 1)
        return 0;
    return 1;
}

void
shut_portal()
{
    object groom;
    tell_room(E(TO),"The red portal in the center of the "+symbol+
    " of stones disappears.\n");
    /* Should be loaded now that it was opened */
    groom = find_object(KHIRAA+"(temple/rooms/gateway_room");
    groom->shut_portal();
    portal_opened = 0;
}

void
create_portal(int time, object mms)
{
    object groom,pgate;
    tell_room(E(TO),"From the center of the "+short()+", a "+
    "red portal opens!\n");
    portal_opened = 1;

    groom = find_object(KHIRAA+"temple/rooms/gateway_room");
    if(!objectp(groom))
        call_other(KHIRAA+"temple/rooms/gateway_room","??");
    groom = find_object(KHIRAA+"temple/rooms/gateway_room");
    if(!objectp(groom))
    {
        tell_room(E(TO),"Error!\n");
        return;
    }
    pgate = clone_object(KHIRAA+"temple/obj/gateway");
    if(!objectp(pgate))
        tell_object(find_player("sarr"),"Error cloning gateway.\n");
    if(!objectp(find_object(KHIRAA+"temple/rooms/t7")))
        tell_object(find_player("sarr"),"t7 no exists, moving gateway.\n");
    if(pgate->move(KHIRAA+"temple/rooms/t7"))
        tell_object(find_player("sarr"),"Move failed.\n");

    if(!objectp(find_object(KHIRAA+"temple/rooms/t7")))
        tell_object(find_player("sarr"),"t7 load fail.\n");
    pgate->set_master(mms);
    tell_room(E(pgate),"A "+pgate->short()+" slowly fades into "+
    "view.\n");
    groom->set_gateway(file_name( E(TO) ) );
    set_alarm(itof(time),0.0,&shut_portal());
}

