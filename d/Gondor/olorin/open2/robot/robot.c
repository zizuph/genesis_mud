/*
 * /d/Gondor/olorin/open/robot.c
 *
 * An attempt to code an intelligent npc
 *
 * Olorin, September 1994
 */

/*
 * ideas: log the npc actions, too
 *        different intro routines
 *        intro trigger
 *        wave trigger
 *        trigger on items given
 *        trigger on enemies killed
 *        trigger on poke
 *        teleport close to players
 *     
 * problems: who
 *           invite
 *           remember
 * fix 'who' and 'remember' using a shadow in the interacting player
 */
inherit "/std/monster";

#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Gondor/olorin/open/robot/scars";
#include "/d/Gondor/olorin/open/robot/r_cmdhooks.h"
#include "/d/Gondor/olorin/open/robot/r_savevars.h"
#include "/d/Gondor/olorin/open/robot/r_triggers.h"

#define CAP(x) capitalize(x)
#define ENV(x) environment(x)
#define TO this_object()
#define TP this_player()

#define DEBUG_MSG(x) find_player("olorin")->catch_msg(x)

/*
 *	Prototypes
 */

/*
 *	Global variables
 */
static int     move_alarm =  0,
               move_speed = 20,
               alarm_f1,
               alarm_c1;
static object *doors;
static string *cmds,
               back_cmd,
               old_dir,
               repeat_text,
              *last_room = allocate(50),
              *left_exits;

/*
 * Function name:   query_log_tell
 * Description:     should tells be logged?
 * Returns:         0 = no, 1 = yes.
 */
int
query_log_tell()
{
    return (sizeof(FILTER_PLAYERS(all_inventory(
            environment(this_object())))));
}

/*
 * Function name: set_race_name
 * Description:   set the race name and set the real race name
 * Arguments:     arg - the name of the race
 */
public void
set_race_name(string arg)
{
    ::set_race_name(arg);
    set_race_real(arg);
}
 
/*
 *  Description: To log monster actions
 */
void
catch_tell(string str)
{
    if (query_log_tell())
        log_file("robot", str, -1);
    ::catch_tell(str);
}

int
set_move_speed(int i)
{
    if (i >= 0)
    {
        move_speed = i;
        return 1;
    }
    return 0;
}

int
query_move_speed()
{
    return move_speed;
}

void
create_robot()
{
//  ::create_monster();
}

nomask void
create_monster()
{
    int    rnd1 = random(21),
           rnd2 = random(11);

    set_living_name("dummy");
    set_name("dummy");
    add_name("robot");
    set_race_name("human");
    set_adj(({"long-legged", "long-armed"}));
    set_long("@@long_desc@@");
    set_alignment(100 - random(201));

    default_config_npc(30 + rnd1);
    set_learn_pref(({1, 1, 1, 1, 1, 1, 0, 0, 0, }));

    set_skill(SS_WEP_SWORD,	10+rnd1);
    set_skill(SS_WEP_POLEARM,	rnd2);
    set_skill(SS_WEP_AXE,	rnd1);
    set_skill(SS_WEP_KNIFE,	rnd1 + rnd2);
    set_skill(SS_WEP_CLUB,	rnd1);
    set_skill(SS_DEFENCE,	0);
    set_skill(SS_PARRY,		0);

    set_skill(SS_SPELLCRAFT,	rnd1);
    set_skill(SS_HERBALISM,	10 + rnd2);

    set_skill(SS_SNEAK,		rnd1);
    set_skill(SS_HIDE,		rnd1);

    set_skill(SS_LANGUAGE,	rnd2/2);

    set_skill(SS_SWIM,		10 + 2*rnd1);
    set_skill(SS_CLIMB,		10 + 2*rnd1);
    set_skill(SS_AWARENESS,	2*rnd2 + rnd1);

    set_scar(2*rnd1 + 3*rnd2);
    set_whimpy(75);

    set_pick_up(75);

    set_act_time(7);
    add_act("ponder dangerous quests.");
    add_act("smile mysteriously");
    add_act("sigh desperately");
    add_act("wear all");
    add_act("wield all");
    add_act("wield all");

    set_cact_time(2);
    add_cact("@@emote_enemy|kick@@");
    add_cact("shout Help! A player killer!");

    set_chat_time(1);
    add_chat("do you now which quests are in this area?");
    add_chat("do you have some spare change for me?");
    add_chat("could you give me a weapon, pleeze?");
    add_chat("I lost everything o those stupid orcs in eodras");
    add_chat("pleeeezzzeeeee!!!");
    add_chat("lllllllaaaaggggggg!!!");
    add_chat("yess!!!");
    add_chat("thanks a lot");
    add_chat("@@repeat_it@@");

    set_cchat_time(2);
    add_cchat("player killer!");

    create_robot();

    set_tell_active(1);
    enable_intro();

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

//  trig_new("%s 'says:' %s", "log_say");
    trig_new("%w 'arrives.' %s", "log_arrive");
    trig_new("'Your legs run away with' %s", "whimpy_restart");

    command("echoon");
}

void
whimpy_restart(string you)
{
    if (move_alarm == 0)
        move_alarm = set_alarm(itof(1+random(TO->query_move_speed())),
            0.0, "random_move");
}

void
log_say(string who, string text)
{
    string  pl = TP->query_name();

    if (!interactive(TP))
        return;

    log_file("robot", pl+" says: "+text, -1);
}

void
log_arrive(string who, string xxx)
{
    string  pl = TP->query_name();

    if (!interactive(TP))
        return;

    if (pl != who)
        return;

    log_file("robot_all", who+" in "+file_name(ENV(TO))+", "
      + ctime(time())+".\n", -1);
}

#if 0
void
log_all(string who, string what)
{
    int     s;
    string  pl = TP->query_name(),
           *rtxt;

    if (!interactive(TP))
        return;

    if (pl != who)
        return;

    rtxt = explode(what, " ");

    if (what == "arrives. \n")
        log_file("robot_all", who+" arrives in "+file_name(ENV(TO))
          + " at "+ctime(time())+".\n", -1);
    else if ( (rtxt[0] == "leaves") && 
        (move_alarm == 0) )
        move_alarm = set_alarm(itof(1+random(TO->query_move_speed())),
            0.0, "random_move");
    else
    {
        log_file("robot_all", who+" "+what, -1);
    }

    if (rtxt[0] == "says:")
    {
        if (!random(4))
        {
            s = sizeof(rtxt)/2;
            repeat_text = implode(rtxt[2..(random(s)+s)], " ");
        }
        else if (implode(rtxt[1..3], " ") == "how much money")
        {
            alarm_c1 = 0;
            if (alarm_f1)
                remove_alarm(alarm_f1);
            alarm_f1 = set_alarm(4.0, 1.5, "react_how_much", TP);
        }
        else if ( (member_array("money", rtxt) > -1) ||
                  (member_array("money?", rtxt) > -1) )
            set_alarm(2.0, 0.0, "react_money", TP);
    }
}
#endif

void
react_how_much(object pl)
{
    switch(alarm_c1++)
    {
        case 0: command("hmm");
                break;
        case 1: command("say actually, as much as you can spare, of course");
                break;
        case 2: command("thank "+pl->query_real_name());
                break;
        case 3: command("say a few gold coins would be enough, thou");
                break;
        default: remove_alarm(alarm_f1);
                 alarm_f1 = 0;
                 alarm_c1 = 0;
                 break;
    }
}

void
react_money(object pl)
{
    if (random(2))
    {
        command("say Yes, I need lots of it. I lost everything when I died!");
        command("thank "+pl->query_real_name());
    }
    else
    {
        command("say money, money, money");
        command("say lira, yen, dollar, deutsch mark, I take everything!");
    }
}

void
init_living()
{
    if (!(TP->query_met(query_real_name())) && (random(3)))
        set_alarm(0.0, 0.0, "introduce_me", TP);

    if (!random(4))
        set_follow(TP->query_real_name());
}

string
long_desc()
{
    string  desc;

    desc = "He is "+LANG_ADDART(implode(query_adjs(), " "))+" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        desc = CAP(query_real_name()) + " is " 
          + LANG_ADDART(implode(query_adjs(), " ")) + " "+query_race_name()
          + ", presenting himself as:\n" + CAP(query_real_name());
        if (strlen(query_title()))
            desc += " "+query_title()+",";
        desc += " "+query_exp_title() + ", male "+query_race_name()+".\n";
    }

    desc += "He is tall and lean for "+LANG_ADDART(query_race_name())+".\n";

    return desc;
}

#if 0
void
arm_me()
{
    object  robe;

    ::arm_me();

    robe = clone_object(MAGES_DIR + "npc/npc_robe");
    robe->move(TO);
    robe->check_spell_object(TO);
    add_cmdsoul(MORGUL_SOUL_FILE);
    update_hooks();
    set_title("the "+query_morgul_title());

    command("wear all");

    weapon_name = query_weapon(-1)[0]->query_name();
}
#endif

void
do_attack(object victim)
{
    if(query_attack())
        return;
    if(victim->query_npc())
        return;
    if (!present(victim,ENV(TO)) || !CAN_SEE(TO,victim))
        return;
    add_prop(LIVE_O_ENEMY_CLING, victim);
    command("kill "+victim->query_real_name());
}

void
escape_to_home()
{
//    remove_object();
}

int filter_door(object x)
{
    return (function_exists("create_object", x) == "/std/door");
}

int
random_move()
{
    int     i,
            bn,
            delay = 5;
    object  env = ENV(TO),
           *pl;
    mixed  *exits,
            door_name;
    string  dir,
            this_room,
           *exit_rooms;

    move_alarm = 0;

    if (!TO->query_move_speed())
        return -1;

    if (objectp(query_attack()))
        return -2;

    if (sizeof(pl = FILTER_PLAYERS(all_inventory(env))))
    {
        delay = 60;
        set_move_speed(120);
    }

    if ( !(env->query_prop(ROOM_I_IS)) )
    {
        set_alarm(1.0, 0.0, "escape_to_home");
        return -4;
    }

    if ((this_room = file_name(env)) != last_room[0])
    {
        cmds = env->query_exit_cmds();
        back_cmd = 0;
        exit_rooms = env->query_exit_rooms();
        if ((bn = member_array(last_room[0], exit_rooms)) > -1)
        {
            back_cmd = cmds[bn];
            cmds -= ({ back_cmd });
        }
//      DEBUG_MSG(this_room+": back_cmd = "+back_cmd+"\n");
        doors = filter(all_inventory(env), "filter_door", TO);
    }
    else
        old_dir = 0;

//  DEBUG_MSG(this_room+": cmds = "+sizeof(cmds)+", doors = "+sizeof(doors)+"\n");
    if (sizeof(cmds))
    {
        if ( (stringp(old_dir)) && (member_array(old_dir, cmds) > -1) &&
             (random(4)) )
        {
            if ( (member_array(this_room, last_room) == -1) )
            {
                dir = old_dir;
                delay = 1;
                set_move_speed(10);
            }
            else
            {
                set_move_speed(20);
                cmds -= ({ old_dir, 0 });
                if (sizeof(cmds))
                    dir = cmds[random(sizeof(cmds))];
                else
                    dir = back_cmd;
            }
        }
        else
        {
            set_move_speed(30);
            dir = cmds[random(sizeof(cmds))];
//          DEBUG_MSG("\t Random selection! Dir = "+dir+"\n");
        }
        cmds -= ({ dir, 0 });
    }
    else if (sizeof(doors))
    {
//  DEBUG_MSG("Trying to walk through a door now!\n");
        // pick one door at random
        i = random(sizeof(doors));
//  DEBUG_MSG("Door \# "+i+"\n");
        if (!(doors[i]->query_open()))
        {
//  DEBUG_MSG("\t Door closed! Name = ");
            door_name = doors[i]->query_door_name();
//  DEBUG_MSG(door_name);
            if (pointerp(door_name))
                door_name = door_name[0];
            command("unlock "+door_name);
            command("open "+door_name);
//  DEBUG_MSG(". Tried to unlock and open it!\n");
        }
        // try to walk through that door
        dir = doors[i]->query_pass_command()[0];
        doors -= ({ doors[i], 0 });
//  DEBUG_MSG("End of door loop!\n");
    }
    else if (stringp(back_cmd))
    {
        dir = back_cmd;
        back_cmd = 0;
    }
    else
    {
        set_alarm(1.0, 0.0, "escape_to_home");
//      DEBUG_MSG(this_room+": dead end! Removing robot!\n");
        return -6;
    }

    if (this_room != last_room[0])
        last_room = ({ this_room }) + last_room[0..(sizeof(last_room)-2)];
    old_dir = dir;
    set_alarm(0.0, 0.0, "command", dir);

    move_alarm = set_alarm(itof(delay+random(TO->query_move_speed())),
        0.0, "random_move");
    return 0;
}

string
repeat_it()
{
    int     i;
    string *ll;

    if (!stringp(repeat_text))
        return "pardon?";

    ll = explode(repeat_text, "");
    for (i = 0; i < sizeof(ll); i++)
        if (ll[i] == "\n")
            ll[i] = "";
    repeat_text = implode(ll, "");
    
    return "What do you mean by \""+repeat_text+"\"?";
}

