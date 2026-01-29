// 2hp7.c 
// uses boriska's random exit generator
// grace

#include "../local.h"

inherit STD2HP;

#define DRAIN 10
// fatigue drain on player
#define SIZE(xx)  ((xx)->query_average_stat() < 65)
//minimum stat average (size) needed to open door

#define PARALYZE (SOBJ + "hold_para")
#define PARALYZE_PROP "_krynn_o_hold_paralyze"
#define CELL_ENT ("/d/Krynn/solamn/hctower/spur/room/cell")

static int door_opened = 0;
static int door_held = 0;
static int close_alarm_id = 0;


void
create_spur_room()
{
    ::create_spur_room();
    SHORT("the end of a dark passage");
    LONG("Here the rough stone walls are dark and dull, "+
        "swallowing the light.  The ceiling is low "+
        "and blackened with soot.\n   The floor slopes "+
        "upward into a wall which blocks further pro"+
        "gress in that direction. Reddish lines pulse "+
        "and glow irregularly, forming a tenuous rect"+
        "angle.\n");


    DARK

        AI(({"floor","dust"}), "Dark powdery dust covers the floor. "+
            "It looks like soot which has fallen from the ceiling.\n");
    AI("ceiling", "It is rough and low, and covered "+
        "with what looks to be hundreds of years of "+
        "soot.\n");
    AI("soot", "Thick and black, it bears witness to "+
        "the thousands of torches consumed within this "+
        "passage.\n");
    AI(({"rectangle", "glow", "red", "lines"}),
   	"It appears to be part of the wall blocking "+
        "the passage. Your searching eyes notice that "+
        "there is no mortar joining the stones of the "+
        "wall along the glowing lines.\n");
    AI(({"wall", "walls", "stone", "stones", "door"}),
      	"Careful examination of the wall indicates "+
        "that it is in fact a well-crafted door made "+
        "of stone that swings on hidden hinges.\n");
    AI(({"hinge", "hinges", "door", "hidden"}),
       	"The door is made of the same thick stone as "+
        "rest of the passage. It seems it should pivot "+
        "on cleverly concealed hinges when enough wei"+
        "ght is thrown against it.\n");
    /*
      ACI(({"hinge", "hinges", "door", "hidden"}), 
      ({"throw weight against", "throw myself against"}),
      "@@do_door");
    */

    set_tell_time(60);
    add_tell("The sound of your heart beating echos loudly "+
        "in your ears.\n"); 
    add_tell("A small current of air stirs near your face.\n");
    add_tell("The glowing lines flicker and flare.\n");
    add_tell("Little puffs of disturbed dust rise from the floor.\n");


    INSIDE;
}

nomask void
init()
{
    ::init();
    ADD("do_door", "throw");
    ADD("do_door", "lean");
    ADD("do_hold", "hold");
    ADD("do_hold", "brace");
    ADD("do_close", "close");
    ADD("do_close", "release");
    
}  

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}

nomask static int
do_door(string str)
{
    object tp = this_player();
    int fatigue_drain;

 
    NF("Throw what against what?\n");
    if (!str)
        return 0;

    NF("The door is already opened.\n");
    if (door_opened || door_held)
	return 0;

    NF("You're not big enough to budge the door.\n");
    if (SIZE(tp))
	return 0;

    NF("You sag against the door, much too fatigued to use enough "+
        "force to swing it open.\n");
    if (tp->query_fatigue() < tp->query_max_fatigue()/DRAIN)
	return 0;   

    if (str == "weight against door" || str == "myself against door")
    {
        tp->catch_msg("You throw your weight against the door and push with "+
            "all your might!\nThe door swings silently open, then "+	
            "begins to swing closed again. You'd better hold the "+
            "door!\n");
        say(QCTNAME(tp) + " manages to swing the door open.\n");
        tell_room (CELL_ENT, "The northern wall seems to move, swinging "+
            "inward!\n");

        door_opened = 1;
        close_alarm_id = set_alarm (10.0, 0.0, "close_for_me", tp);
        return 1;
    }
    return 0;
}

// secures the door when 'hold' command is issued within some time interval
// after throwing wieght against it.
int
do_hold(string str)
{
    object tp = this_player();
    int fatigue_penalty;
    float hold_time;
    object paralyze;
  
    if (!door_opened)
        return 0;
  
    notify_fail ("Hold what, the door?\n");
    if (!str)
        return 0;

    fatigue_penalty = tp->query_max_fatigue()/DRAIN;

    if (tp->query_fatigue() < fatigue_penalty)
    {
        tp->catch_msg ("You are too tired to hold the door open. It "+
            "swings closed despite your efforts.\n");
        return 1;
    }

    if (str == "door" || str == "the door")
    {
        write("You push yourself into the opening and lean against the "+
            "door with your back, bracing your feet against the wall.\n"+
            "Your legs begin to tremble with the strain of the door's "+
            "weight bearing so heavily against you.\n");
  
        say(QCTNAME(tp) + " pushes into the opening and leans "+ 
            tp->query_possessive() +" back against the door, bracing feet "+
            "against the wall to keep it from swinging shut.\n"+
            QCTNAME(tp) + " appears to be under a lot of strain.\n");

        tell_room (CELL_ENT, "You catch a glimpse of "+ QCTNAME(tp) +
            " leaning against the door to keep it open.\n");
  
        door_held = 1;
        add_exit(CELL_ENT, "south", 0);
        call_other(CELL_ENT, "open_pass");
        
        remove_alarm (close_alarm_id);
        hold_time = itof (random(tp->query_base_stat(SS_STR) - 50));

        (paralyze = clone_object(PARALYZE))->move(tp, 1);
        tp->add_prop(PARALYZE_PROP, paralyze); // to store objectpointer
 
        close_alarm_id = set_alarm (hold_time, 0.0, "close_for_me", tp);
        return 1;
    }
    return 0;
}

void
close_for_me(object tp)
{
    int fatigue_penalty = tp->query_max_fatigue()/DRAIN;
    object paralyze;
  
    // close_for_me can be called not only by alarm, but when 
    // releasing door after paralyze is gone.
    if (close_alarm_id)
    {
        remove_alarm (close_alarm_id);
        close_alarm_id = 0;
    }

    write("You leap back into the tunnel and away from the door.\nIt "+
	"closes fairly slowly and silently, disturbing the dust with "+
	"a strong puff of air.\n");
    say(QCTNAME(tp) +" suddenly leaps away from the door.  It closes "+
	"slowly and silently, disturbing the dust with a strong puff "+
	"of air.\n");

    tell_room(CELL_ENT, QCTNAME(tp) + " disappears from view and the "+
	"wall slides back into place.\n");
    
    door_opened = 0;
    door_held = 0;
    remove_exit("south");
    call_other(CELL_ENT, "close_pass");

    set_this_player(tp);
    tp->add_fatigue(-fatigue_penalty);
    // remove paralyze from player.
    if (objectp(paralyze = tp->query_prop(PARALYZE_PROP)))
        paralyze->remove_object();
    tp->remove_prop(PARALYZE_PROP);
}

 
int
do_close(string str)
{
    object tp = this_player();
  
    if (!door_held || !door_opened)
        return 0;

    NF("Close what, the door?\n");
    if (!str)
        return 0;

    if (str == "the door" || str == "door")
    {
        close_for_me(tp);
        return 1;
    }

    return 0;
}



public int
query_door_opened() { return door_opened;}

public int
query_door_held() { return door_held;}



