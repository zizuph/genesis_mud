/*  -*- LPC -*-  */
#include "defs.h"
#include <macros.h>
#include <wa_types.h>

string *ldesc;
int pos;

void fall_cont(object ob);

mixed
query_where()
{
    return ({ 0, 300 + (pos < 4 ? 0 : pos < 7 ? (pos-3) * 25 : 100 ),
              -100-pos*100, "hide" });
}

object rope()
{
    return (THIS_DIR+"shaft1")->query_rope();
}

int length()
{
    return (THIS_DIR+"shaft1")->query_rope_length();
}

CONSTRUCT_ROOM
{
}

setup_pos(int p)
{
    string str;
    pos = p;
    str =
	"You are climbing on a "+rope()->short()+" in a deep shaft "+
	"in the Mines of Moria. ";
    switch(pos) {
	case 1: str +=
	    "You are now quite high up in the mountain, and a little bit "+
	    "further up you can see the hook and the "+rope()->short()+
	    ". ";
	    break;
	case 2: str +=
	    "You begin to realize that this shaft is increadibly deep. In fact "+
	    "you wonder if the rope you tied was long enough. ";
	    break;
	case 3: str +=
	    "At this spot the shaft widens and you dingle in the free air. How "+
	    "far down this is in the Mines you can just imagine, but by the "+
	    "feeling of the air, you reckon it must be quite deep. ";
	    break;
	case 4: str +=
	    "This is a particulary narrow spot, and from here you notice that "+
	    "the shaft bends somewhat in the eastern direction. ";
	    break;
	case 5: str +=
	    "The air definitely gets hotter here! Surely you must now be "+
	    "over sixty meters below the hook, but looking down you see that "+
	    "the shaft continues even further! ";
	    break;
	case 6: str +=
	    "In a foul damp atmosphere you begin to breathe heavily. You wonder "+
	    "if you will ever be able to climb upwards again... ";
	    break;
	case 7: str +=
	    "Here the shaft descends steeply down, while it turns upwards steeply "+
	    "to the west. ";
	    break;
	case 8: str +=
	    "This is a particularly dark spot in the shaft. The heat is overwhelming "+
	    "now, and you can hardly breath. ";
	    break;
	case 9: str +=
	    "It is a great luck that the rope is this long. You must now be Over a "+
	    "hundred meters deep in the mountain! "+CAP(rope()->short())+" rises up into cooler "+
	    "air further up, while the damp air gets thicker and thicker downwards. ";
	    break;
	case 10: str +=
	    "You are now only meters above what seems to be the bottom of the shaft! "+
	    "The air is quite humid and hot here, and you can just barely breathe. "+
	    "The shaft continues steeply upwards into the darkness. ";
	    break;
    }
    if(length()<pos*20+20)
	str +=
	    "You notice that the rope does not continue any further down! "+
	    "The "+rope()->short()+" is simply not long enough for this "+
	    "deep shaft. You have no alternative but to climb up again. ";

    set_long(str+"\n");
    set_short("Climbing in a shaft");
}


init()
{
    ::init();
    add_action("do_up", "up");
    add_action("do_down", "down");
    add_action("do_jump", "jump");
    add_action("do_fall", "fall");
}

#define QUERY_COUNT(tp)   tp->query_prop("_temp_fall_count")
#define SET_COUNT(tp,v)   tp->add_prop("_temp_fall_count", v)
#define ADD_COUNT(tp)	  SET_COUNT(tp, QUERY_COUNT(tp)*2)

#define QUERY_POS(tp)	  tp->query_prop("_temp_fall_pos")
#define SET_POS(tp,v)	  tp->add_prop("_temp_fall_pos", v)
#define ADD_POS(tp)	  SET_POS(tp, QUERY_POS(tp)+1)

fall_cont(object tp)
{
    int dam;

    ADD_COUNT(tp);
    ADD_POS(tp);

    if(QUERY_POS(tp) < 11) {
	tp->catch_msg("The speed increases in your way down!!\n");
	if(random(2)) {
	    tp->catch_msg("You hit the wall!\n");
	    dam = (QUERY_COUNT(tp)*5)-random(QUERY_COUNT(tp)*(tp->query_prop(SS_ACROBAT)+DEX(tp))/50);
	    if(dam<QUERY_COUNT(tp)) dam = QUERY_COUNT(tp);
	    tp->hit_me(QUERY_COUNT(tp)*5, W_BLUDGEON, TO, -1);
	    if(HP(tp)<=0) {
		tp->do_die(TO);
		return;
	    }
	}
	tp->command("down");
    set_alarm(2.0, 0.0, &fall_cont(TP));
	return;
    }
    tp->catch_msg("You schmack into the floor with a bonecrushing sound!\n");
    tell_room(THIS_DIR+"bottom",
	QCTNAME(tp)+" schmaks into the floor with a bonecrushing sound!\n", tp);
    tp->move(THIS_DIR+"bottom");
    tp->hit_me(QUERY_COUNT(tp)*20, W_BLUDGEON, TO, -1);
    if(HP(tp)<=0)
	tp->do_die(TO);
    return 1;
}

do_fall_down(object tp)
{
    tp->catch_msg("You start accelerating downwards!\n");
    (THIS_DIR+"shaft1")->remove_climber(tp);
    SET_COUNT(tp, 1);
    SET_POS(tp, pos);
    set_alarm(2.0, 0.0, &fall_cont(TP));
    return 1;
}

fall_down()
{
    TP->catch_msg("You let your grip on the "+rope()->short()+" go!\n");
    tell_room(ETP,
	QCTNAME(TP)+" lets "+HIS_HER(TP)+" grip on the "+rope()->short()+" go!\n");
    do_fall_down(TP);
}

do_jump(string str)
{
    if(str!="down") {
	write("You can not jump here. If you want to fall down, you might.\n");
	return 1;
    }
    fall_down();
    return 1;
}

do_fall(string str)
{
    if(str!="down")
	return notify_fail("What do you mean? Fall down? That will hurt!\n");
    fall_down();
    return 1;
}


do_up()
{
    int f = 500/(random(4*TP->query_prop(SS_CLIMB)+2*DEX(TP)+CON(TP))+10)+pos;
    string how;
    if(TP->query_fatigue()<f) {
	write("You are too tired to climb upwards.\n");
	return 1;
    }
    switch(f) {
	case 1..9:   how = "very easy"; break;
	case 10..15: how = "rather easy"; break;
	case 16..20: how = "tiring"; break;
	case 21..30: how = "very tiring"; break;
	case 31..40: how = "extremely tiring"; break;
	default:     how = "very demanding and tiring"; break;
    }
    write("You feel that climbing upwards is "+how+" for you.\n");
    TP->add_fatigue(-f);
    if(pos==1)
	(THIS_DIR+"shaft1")->remove_climber(TP);
    return 0;
}

do_down()
{
    if(length()<pos*20+20) {
	write("You can't climb any further down!\n");
	write("The "+rope()->short()+" is too short for this deep shaft.\n");
	write("If you *really* want to get down, you could always "+
	      "'jump down' from here, but that might hurt, and perhaps kill "+
	      "you instantly.\n");
	return 1;
    }
    TP->add_fatigue(-3-pos);
    if(pos==10)
	(THIS_DIR+"shaft1")->remove_climber(TP);
    return 0;
}

enter_inv(object ob, object from)
{
    if(!living(ob) && ob->query_prop(OBJ_I_WEIGHT)>0)
    {
	tell_room(TO, "The " + QSHORT(ob) + " drops down into the shaft.\n");
	ob->move(THIS_DIR+"bottom");
	return;
    }
    ::enter_inv(ob, from);
}
