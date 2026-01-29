// file name: d/Avenir/common/outpost/cave2.c
// creator(s):  Kazz    Jan 1995
// purpose:     access to the fort 
//		water quest: see dw_guard.c in MON directory.
// revisions: 
//              May 28 2004 Lilith: updated infidel/enemy check
//              Jun 22 2004 Lilith: gate opens and closes via knocking.
//             April 2022 Lilith: Fort makeover
//
inherit "/d/Avenir/inherit/room";

#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"
#include <macros.h>
#include <stdproperties.h>
// For tomato drop quest
#define NPC_ROOM   ("/d/Avenir/common/outpost/tower_middle2")
// For Plalgus curse/infidels
#define LIST       ("/d/Avenir/union/list")
#define ENEMY(x)   (LIST->query_enemy(x))
#define FRIEND(x)  (LIST->query_friend(x))
// For gate
#define OTHER_SIDE (OUTPOST +"fort2")

static object *guards = allocate(2);

int door_closed;
int query_closed();
int enemy_test(object ob);

int query_closed() {    return door_closed;    }

void open_door();

void
add_guards()
{
    int     i = sizeof(guards);
 
    while(i--)
    {
        if (!objectp(guards[i]))
        {
            guards[i] = clone_object(MON + "dw_guard");
            guards[i]->equip_me();
            guards[i]->add_gate_talk();
            guards[i]->move(this_object());
        }
    }
} // add_guards()



public void
reset_domain_room()
{
    add_guards();        
    door_closed = 1;
}

public void
create_domain_room()
{
    object  npc_room;
    
    set_short("just outside that gate of Fort Sybarus");
	set_long("A large fortress has been built to control passage "+
	    "between this ancient magma tube and the Great Cavern "+
        "of Sybarus. "+		
		"An imposing gateway made of soot-stained stone blocks the "+
        "way to the east. "+
        "It bears a large symbol in flowing gold. "+
        "A path leads southwest to a wide chasm that glows orange-"+
        "red with flowing lava, while another leads northwest to a "+
        "dark opening in the cavern wall. "+
        "On either side of the paths and the gate burn huge, "+
        "scorching pools of liquid that illuminate the fort "+
        "and the surrounding area.\n");
	
    add_exit("cave1","northwest",0);
    add_exit("cave3","southwest",0);
    add_exit("fort2","east", "@@try_east");
    reset_room();


//	FORT
    add_item(({"fort", "tall fort", "black fort", "tall black fort",
	"fortress", "basalt fortress"}),
        "The fortress is built with very black, smooth stones taken "+
        "from the basalt formations in the cavern. It has two towers, "+
        "one of which is quite tall and blends in with the cavern "+
        "ceiling and the southern wall. The second, north tower, "+
        "connects to the gate via parapets.\n" );
//	TOWER
    add_item(({"tower"}), 
        "Two towers rise above you. The taller tower is to the south "+
        "and the short one to the north.\n");
    add_item(({"tall tower", "south tower", "black tower"}), 	
		"The black tower rises high above you, providing whoever "+
        "stands within a view of the cavern and the sea beyond.\n" );
    add_item(({"north tower", "short tower", "squat tower"}),
        "This tower squats in the place, wide and a few stories high. "+
        "Its parapets seem to connect with those above the gate, "+
        "providing good defensive capability against invaders.\n");	
    add_item(({"parapet", "parapets", "tower parapets"}),
        "Each tower seems to have its own parapets, as does the gate.\n");		
//	GATE  
    add_item(({"gate", "fort gate", "stone gate", "door", "sooty gate",
        "soot-stained gate", "soot-stained gateway", "gateway",
        "black door", "black stone door", "black stone gate door"}),
        "The black stone gate door guards the only entrance to the fort. "+
        "An open metal window is noticeable on either side of "+
        "the door, allowing the guards to talk to whoever desires "+
		"passage. There is a stylized lock-and-key symbol engraved "+
		"into the gate and filled with gold that seems to move in "+
        "the light of the flames.\n");
    add_item(({"lock-and-key symbol", "symbol on gate", "stylized symbol",
	    "stylized lock-and-key symbol", "symbol of salilus", 
        "salilus symbol", "golden symbol", "large symbol", "gold symbol"}),
        "This stylized lock-and-key symbol symbol is for the god Salilus, "+
        "He Who Opens The Way.\n");
    add_cmd_item(({"door", "black door", "gate", "gateway", "black gate"}), 
        "open",  "The black stone gate can only be opened by the guards "+
        "Perhaps you could knock or bang on the gate to get their "+
        "attention.\n");
    add_cmd_item(({"door", "black door", "gate", "gates", "black gate",
         "on gate", "on door"}), 
        ({"knock", "bang"}), "@@knock_gate");
    add_item(({"pools", "liquid", "burning liquid"}),
        "The liquid is barely noticeable through the flame. It "+
	    "might be oil, but the flame is too hot to be sure.\n");
    add_item(({"window", "windows", "metal windows", "metal window"}),
	    "The windows allow guards to look out and see who is "+
        "knocking.\n");

    LIGHT
    IN
    FLAME
    CAVERN
    WALL
    PATH
    FLOOR
    ROCKS
    CHASM
	
    // load the tomato_quest room to get the npc's moving in the fort
    npc_room = NPC_ROOM->this_room();
    npc_room->load_me();
    if (!objectp( npc_room )) 
    {
        notify_fail( "The tower_middle2 room cannot be found.\n" );
 	  return 0;
    }
}

int
knock_gate()
{
    if (!query_closed())
    {
        notify_fail("The black stone door is already open.\n");
        return 0;
    }

    write("You knock on the black stone door.\n");
    say(QCTNAME(TP)+ " knocks on the black stone door.\n");

    if (TP->query_prop(OBJ_I_INVIS) || TP->query_prop(OBJ_I_HIDE))
    {
        write("The dwarven guards look around as though getting ready to "+
            "open the door but don't see who knocked.\n");
        return 1;
    }

    if (TP->query_hooded())
    {
	write("The dwarven guards look at you quizzically.\n");
	say("The dwards guards look at "+ QTNAME(TP) +" quizzically.\n");
	return 1;
    }

    if (enemy_test(TP))
    {
        write("The dwarven guards make a hand-signal to someone "+
            "on the other side of the door.\n");
        write("A booming dwarven voice shouts: I'd sooner eat "+
            "phynos meat than let you pass, you filth! Begone.\n");
        say("The dwarven guards look "+QCTNAME(TP)+" up and down, "+
            "then make a hand-signal towards someone on the "+
            "other side of the door.\n");
        say("A booming dwarven voice shouts: I'd sooner eat "+
            "phynos meat than let you pass, you filth! Begone.\n");
        return 1;
    }

    write("The dwarven guards on both sides of the gate peer at you.\n");
    say("The dwarven guards on both sides of the gate peer at "+ QCTNAME(TP) +".\n");

    open_door();
    set_alarm(8.0, -1.0, "close_door");
    return 1;
}

int
enemy_test(object ob)
{
    if (IS_INFIDEL(ob) || ENEMY(ob))
        return 1;
    else
        return 0;
}

void
open_door()
{
    tell_room(TO,"The black stone door opens just wide enough "+
        "to admit the knocker.\n");
    tell_room(OTHER_SIDE,"The black stone door slowly opens.\n");
    door_closed = 0;
    return;
}
    
void
close_door()
{
    if (query_closed())
        return;

    tell_room(TO,"The black stone door swings closed.\n");
    tell_room(OTHER_SIDE, "The black stone door swings closed.\n");
    door_closed = 1;
    return;
}
    
int
try_east()
{   
    if (!interactive(TP))
        return 0;

    if (query_closed())
    {
        write("The black stone door is closed.\n");
        return 1;
    }

    if (enemy_test(TP))
    {
        close_door();
        return 1;
    }
    write("You walk past the open door and into the fortress.\n");
    return 0;
}
       
/* 
 * I've been bad and I shouldn't have come back.
 */
void
do_curse(object ob)
{
    // I have entered as an infidel or an enemy of the Union.
    WRATHOBJ->load_me();         
    WRATHOBJ->mark_enemy(ob);
    // if infidel but not union enemy, add to Union enemy
    // list. Its their job to clean up enemies of Sybarus.
    if (!ENEMY(ob))
        LIST->add_enemy(ob->query_real_name());
    STATSERV_LOG_EVENT("plalgus", "Entered as an enemy and was cursed");
    return;
}

void
enter_inv(object ob, object from)
{
    object curse; 
    string str;

    ::enter_inv(ob, from);
    
    if (!interactive(ob))
        return;

    if (curse = present(WRATHNAME, ob))
    {
        STATSERV_LOG_EVENT("plalgus", "Entered Sybarus as accursed");
        if(FRIEND(ob))
        {  
            ob->remove_skill(SS_INFIDEL);
            curse->lift_judgement(100);
        }
        if (!IS_INFIDEL(ob))
        {
            curse->lift_judgement(100);
        }
        return;
    }

    if (IS_INFIDEL(ob))
    {
        if(FRIEND(ob))
        {
            ob->remove_skill(SS_INFIDEL);
            return;
        }
        else
            do_curse(ob);     
        return;
    }

    if (ENEMY(ob))
    {
        if(FRIEND(ob))
        {
            ob->remove_skill(SS_INFIDEL);
            return;
        }
        else
            do_curse(ob);     
        return;
    }

 
    // It would be nice if this would work, but it won't
    //    str = ob->query_all_major_guilds());
    // So we will use three checks instead of one.
    // We will mark individuals as Union enemy but not call Plalgus. 

    str = ob->query_guild_name_race();
    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
        LIST->add_enemy(ob->query_real_name());
        return;
    }
    str = ob->query_guild_name_occ();          
    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
        LIST->add_enemy(ob->query_real_name());
        return;
    }
    str = ob->query_guild_name_lay();
    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
        LIST->add_enemy(ob->query_real_name());
        return;
    }

}

