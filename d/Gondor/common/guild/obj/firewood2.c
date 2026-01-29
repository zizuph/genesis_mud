/*
 *	/d/Gondor/common/guild/obj/firewood.c
 *
 *	Firewood for rangers who can gather firewood.
 *
 *	Elessar
 *
 *	Modification log:
 *	Gorboth, December 1995: Changes for Amon Din quest.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/quest/din/din_defs.h"

#define INTERVAL	 5
#define COOL_INTERVAL	60
#define FIREWOOD_M_GET_NO_TORCH		"_firewood_m_get_no_torch"

/*
 *	Prototypes
 */
	string  do_search(object tp, string arg);
        int     query_lit();
        void    cool_down();
varargs void    go_out(int i);
        void    light_tick();
        int     put_on_fire(string arg);

/*
 *	Global variables
 */
int     alarm_id = 0,
        burn_time = 60,
        orig_burn_time = 60,
        burnt,
        burnt_down,
        is_stack,
        not_burning,	// If this is set, the wood won't burn.
        waslit,
        cool_ticks,
        cool_alarm;

varargs int
set_is_stack(int stack = 1)
{
    if ((is_stack && stack) || (!is_stack && !stack))
        return 0;
    is_stack = stack;

    if (is_stack)
    {
        remove_name("campfire");
        set_name(({"stack of firewood", "stack", }));
    }
    else
    {
        remove_name(({"stack", "stack of firewood", }));
        set_name("campfire");
    }

    return 1;

}

void
update_fire()
{
    object  room = ENV(TO);

    while (!room->query_prop(ROOM_I_IS))
        room = ENV(room);
    room->update_light(1);
}

void
set_burn_time(int i)
{
    burn_time = i;
    orig_burn_time = burn_time;

    if (alarm_id && sizeof(get_alarm(alarm_id)))
        update_fire();
}

int
test_lit()
{
    if (alarm_id && sizeof(get_alarm(alarm_id)))
        return 1;
    return 0;
}

int
test_light()
{
    if (alarm_id && sizeof(get_alarm(alarm_id)))
        return (burn_time/100 + 1);
    else
        return 0;
}

int
test_weight()
{
    return (burn_time * 50 / 3);
}

int
test_volume()
{
    return (test_weight() * 3);
}

void
create_object()
{
    set_name(({"campfire", "firewood", "wood", }));
    add_name("_firewood");
    set_short("@@short_func");
    set_long("@@long_func");
    set_burn_time(5);
    add_prop(OBJ_I_LIGHT,    "@@test_light");
    add_prop(OBJ_I_NO_GET,   "@@test_lit");
    add_prop(OBJ_I_WEIGHT,   "@@test_weight");
    add_prop(OBJ_I_VOLUME,   "@@test_volume");
    add_prop(OBJ_I_HAS_FIRE, "@@test_lit");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
}

string
determine_size()
{
    if (orig_burn_time > 625) return "very large";
    if (orig_burn_time > 500) return "large";
    if (orig_burn_time > 375) return "ordinary";
    if (orig_burn_time > 250) return "small";
    if (orig_burn_time > 125) return "tiny";
    else return "pathetic";
}

int
get_torch(string str)
{
    int     get_log;
    object  torch, wood;
    mixed   res;

    if (!strlen(str))
    {
	NFN("Get what?");
        return 0;
    }

    if (is_stack || !parse_command(str, ({ TO }),
        "'torch' / 'branch' 'from' [the] %o", wood) || wood != TO)
    {
        if (is_stack && parse_command(str, ({ TO }),
            "'log' 'from' [the] %o", wood) && wood == TO)
            get_log = 1;
        else
            return 0;
    }

    if (res = query_prop(FIREWOOD_M_GET_NO_TORCH))
    {
	if (stringp(res))
	    NFN(res);
	else
	    NFN("You cannot get a torch from the " + short() + ".\n");
	return 0;
    }
/*
 *  Ok, we assume the player actually wanted to get a burning branch
 *  from the fire. Now let's give it to him if we can.
 */
    if (burn_time > 375) 
    {
        /* We declare this campfire big enough to have a real branch to take. */
        FIX_EUID
        torch = clone_object("/std/torch");
        if (get_log)
        {
            torch->set_name("log");
            torch->set_short(0);
            torch->set_pshort("logs");
            torch->set_adj("dry");
            if (not_burning)
            {
                torch->set_adj("ash-grey");
                if (query_prop(DIN_I_FIREWOOD))
                    torch->add_prop(DIN_I_FIREWOOD, 2);
            }
            torch->set_long("This is a "+torch->short()+" that was chopped "
              + "into timber for burning.\n");
        }
        else
        {
            torch->set_name("branch");
            torch->set_pname("branches");
            torch->set_adj(({"dry", "gnarly", }));
            torch->set_long("This dry branch looks like it has fallen from a tree.");
        }
        torch->set_strength(1);
        if (not_burning)
            torch->set_time(0);
        else
            torch->set_time(200);
        torch->add_prop(OBJ_I_WEIGHT,400);
        torch->add_prop(OBJ_I_VOLUME,600);

        if (test_lit())
            torch->light_me();
        if (torch->move(TP))
        {
            write("You can't carry more!\n");
            say(QCTNAME(TP)+" tries to get a branch from the "
              + query_name()+", but fails.\n",TP);
            torch->remove_object();
        }
        else 
        {
            burn_time -= 200;
            orig_burn_time -= 200;
            update_fire();
            if (test_lit())
            {
                write("You get a burning "+torch->query_name()+" from the "
                  + query_name()+".\n");
                say(QCTNAME(TP)+" takes a burning "+torch->query_name()
                  + " from the "+query_name()+".\n");
            }
            else if (get_log)
            {
                write("You get a log from the stack of firewood.\n");
                say(QCTNAME(TP)+" takes a log from the stack of firewood.\n");
            }
            else
            {
                write("You get a dry branch from the campfire.\n");
                say(QCTNAME(TP)+" takes a dry branch from the campfire.\n");
            }
        }
        return 1;
    }
    if ( id("ashes") )
	write(BSN("There are no "
	  + (get_log ? "logs" : "branches suitable for a torch")
	  + " in the pile of ashes."));
    else if ( !get_log )
	write(BSN("There are no branches large enough; the "+query_name()
          + " consists of only small dry sticks, not suitable for a torch."));
    else
	write(BSN("There are no logs of a suitable size."));
    return 1;
}
      
string
short_func()
{
    string  shortstr = determine_size();

    if (burnt_down)
    {
        if (is_stack)
            return "pile of ashes from a burnt stack of firewood";
        return "pile of ashes from an old, "+shortstr+" campfire";
    }

    if (!(ENV(TO)->query_prop(ROOM_I_IS)) || (is_stack && !query_lit()))
    {
        if (sizeof(query_adjs()))
            shortstr += " stack of "+implode(query_adjs(), ", ")+" firewood";
        else
            shortstr += " stack of firewood";
    }
    else if (query_lit())
        shortstr += ", burning "+query_name();
    else if (waslit)
        shortstr += ", half-burned, extinguished "+query_name();
    else
        shortstr += " "+query_name()+", ready to be set fire to";

    return shortstr;
}

string
long_func()
{
    int     hrs;
    string  longstr,
            size = determine_size();

    if (burnt_down) 
    {
        hrs = cool_ticks/60;
        longstr = "This "+query_name()+" must have been "+size
          + ", judging by the amount of ashes left behind.";
        if (hrs)
            longstr += " By feeling the temperature of the ashes you guess "
              + "that this "+query_name()+" burned down about "+LANG_WNUM(hrs)
              + " hour" + (hrs > 1 ? "s" : "") + " ago.";
        else if (cool_ticks > 45)
            longstr += " By feeling the temperature of the ashes, you estimate "
              + "that this "+query_name()+" burned down less than an hour ago.";
        else if (cool_ticks > 30)
            longstr += " You also find a few live coals left, glowing in the "
              + "ashes. The "+query_name()+" probably burned down about half "
              + "an hour ago.";
        else
            longstr += " The glowing pieces of live coals and firewood left "
              + "amongst the ashes makes you understand that this fire burned "
              + "out quite recently.";
        return BSN(longstr);
    }

    if (waslit)
    {
        hrs = cool_ticks/60;
        longstr = "This "+size+" "+query_name()+" had burned a while when it was "
          + "extinguished again. By feeling the temperature of the ashes, "
          + "you guess that ";
        if (hrs)
            longstr += ("the "+query_name()+" was extinguished about "
              + (hrs > 1 ? (LANG_WNUM(hrs) + " hours") : "an hour") + " ago.");
        else if (cool_ticks > 45)
            longstr += "the "+query_name()+" was extinguished less than an hour ago.";
        else if (cool_ticks > 30)
            longstr += "the "+query_name()+" was extinguished about half an hour ago. "
              + "The few live coals you find glowing amongst the ashes confirm "
              + "this.";
        else
            longstr += "the "+query_name()+" was extinguished quite recently, since "
              + "you see glowing pieces of wood and live coals in the ashes.";

        return BSN(longstr);
    }

    if (alarm_id && sizeof(get_alarm(alarm_id)))
    {
        hrs = burn_time/60;
        longstr = "This "+size+", burning "+query_name()+" gives both light and "
          + "warmth out here in the open. You guess that it will still "
          + "burn for ";
        if (hrs > 1)
            longstr += "about another "+LANG_WNUM(hrs)+" hours before "
              + "it dies out.";
        else if (hrs)
            longstr += "about one more hour before it dies out.";
        else if (burn_time > 45)
            longstr += "less than an hour before it dies out.";
        else if (burn_time > 30)
            longstr += "just about half an hour before it dies out.";
        else
            longstr += "a few more minutes before going out.";
        return BSN(longstr);
    }

    if (sizeof(query_adjs()))
        longstr = "This "+size+" stack of "+implode(query_adjs(), ", ")+" firewood";
    else
        longstr = "This "+size+" stack of firewood";

    if (is_stack)
        return BSN(longstr + " is comprised of numerous logs"
          + " which have been chopped into timber for burning.");
    else
        return longstr + " is ready to be lit.\n";
}

void
add_burn_time(int i)
{
    burn_time += i;
    if (burn_time > orig_burn_time)
        orig_burn_time = burn_time;
    if (alarm_id && sizeof(get_alarm(alarm_id)))
        update_fire();
}

int
query_burn_time()
{
    return burn_time;
}

int
query_lit()
{
    return (alarm_id && sizeof(get_alarm(alarm_id)));
}

void
blow_away_ashes()
{
    tell_room(ENV(TO),
        "The remaining ashes of the "+query_name()+" blow away with the wind.\n");
    remove_alarm(cool_alarm);
    remove_object();
}

public int
light_fire(string str)
{
    object  room = ENV(TO),
           *objs;

    if (!strlen(str))
        return 0;

    if (!sizeof(objs = FIND_STR_IN_OBJECT(str, room)))
        return 0;

    if (member_array(TO, objs) < 0)
        return 0;
/*
    if (str != "campfire" && str != "firewood" && str != "fire" &&
        str != "wood") 
        return 0;
 */

    if (burnt_down)
        return 0;

    if (not_burning)
    {
        NFN("The ash-grey firewood does not catch fire.");
        return 0;
    }

    if (!(room->query_prop(ROOM_I_IS)))
    {
        if (ENV(TO) == TP)
            NFN("You cannot light the firewood you are carrying!");
        else
            NFN("You cannot light the firewood there!");
        return 0;
    }

    if ((room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
	(room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER))
    {
	NFN("You cannot light the firewood while it is in water!");
	return 0;
    }
    if (alarm_id && sizeof(get_alarm(alarm_id)))
    {
        NFN("But the "+query_name()+" is already burning!");
        return 0;
    }

    if (is_stack)
    {
        write("You light the stack of firewood, and it quickly "
          + "catches fire.\n");
    }
    else
    {
        write(BSN("You light the campfire, and feel the warmth of "
          + "the fire warm you and the light from the fire feels as a "
          + "protection against the wild."));
    }
    say(QCTNAME(TP)+" lights the "+query_name()+".\n", TP);

    alarm_id = set_alarm(itof(INTERVAL), itof(INTERVAL), light_tick);

    if (waslit)
    {
        waslit = 0;
        remove_alarm(cool_alarm);
        cool_alarm = 0;
    }
    add_name("fire");
    /* prop _room_has_fire added to the room, Olorin, 14-apr-93 */
    room->add_prop("_room_has_fire",1);
    room->add_prop(OBJ_I_HAS_FIRE,1);
    room->update_light();
    return 1;
}

void
light_tick()
{
    int     ti,
            i;
    object  room = ENV(TO);
    string *rooms;

    burn_time -= INTERVAL;

    if (burn_time <= 0)
    {
        go_out(1);
        remove_alarm(alarm_id);
        alarm_id = 0;
    }

    if (!is_stack)
    {
        switch (random(16)) 
        {
            case 0:
                tell_room(room,
                    "A loud pop erupts from the burning campfire.\n");
                break;
            case 1:
                tell_room(room,
                    "Flames dance across the burning firewood.\n");
                break;
            case 2:
                tell_room(room, "A wet piece of wood in the campfire "
                  + "spits and hisses as it burns.\n");
                break;
            case 3:
                tell_room(room, "The heat from the burning campfire "
                  + "warms your body comfortably.\n");
                break;
            case 4:
                tell_room(room, "Shadows created by the flames of "
                  + "the campfire dance around the area.\n");
                break;
            case 5:
                tell_room(room, "The burning firewood emits some "
                  + "crackling noises.\n");
                break;
            case 6:
            case 7:
                tell_room(room, "The flames of the campfire flicker "
                  + "in the breeze.\n");
                break;
            case 8:
            case 9:
                for (i = 0; i < sizeof(rooms = room->query_exit_rooms()); i++)
                    tell_room(rooms[i], "You suddenly notice the smell of "
                      + "woodsmoke drifting here from somewhere close by.\n");
                break;
            default:
                break;
        }
    }

    ti = (burn_time/INTERVAL)*INTERVAL;

    if (ti == 60)
        tell_room(room, "The "+query_name()+" slumps down a little as it "
          + "begins to burn down.\n");
    else if (ti == 45)
        tell_room(room, "The "+query_name()+" flickers and the heat grows "
          + "less intense.\n");
    else if (ti == 30)
        tell_room(room, "The "+query_name()+" looks like it will burn out soon.\n");
    else if (ti == 15)
        tell_room(room, "The "+query_name()+" grows "
          + "smaller; it's about to go out.\n");

    update_fire();
}

int
extinguish(string str)
{
    if (!strlen(str))
        return 0;

    if (str != "campfire" && str != "fire")
        return 0;

    if (burnt_down || waslit)
    {
        NFN("But the "+query_name()+" is already extinguished!");
        return 0;
    }
    if (!(alarm_id && sizeof(get_alarm(alarm_id))))
    {
        NFN("But the "+query_name()+" has not even been lit yet!");
        return 0;
    }
    write("You extinguish the "+query_name()+".\n");
    say(QCTNAME(TP)+" extinguishes the "+query_name()+".\n", TP);
    go_out(0);
    remove_alarm(alarm_id);
    alarm_id = 0;
    return 1;
}

int
kick_fire(string str)
{
    object  room = ENV(TO),
           *objs;
 
    if (!strlen(str))
        return 0;

    if (!sizeof(objs = FIND_STR_IN_OBJECT(str, room)))
        return 0;

    if (member_array(TO, objs) < 0)
        return 0;
/*
    if (str != "ashes" && str != "pile" && str != "campfire" &&
        str != "campfire" && str != "firewood")
        return 0;
 */

    if (alarm_id && sizeof(get_alarm(alarm_id)))
    {
        if (orig_burn_time > 500 && burn_time > 200)
        {
            write("The "+query_name()+" is too large to just kick it out.\n"+
                  "You will have to extinguish it the normal way.\n");
            return 1;
        }
        write(BSN("You kick the burning "+query_name()+", spreading sticks and "
          + "branches around, soon to go out by themselves."));
        say(QCTNAME(TP)+" kicks out the "+query_name()+", extinguishing it "
          + "effectively.\n",TP);
        tell_room(room, "Only a sad pile of ashes are left.\n");
        burn_time = 0;
        orig_burn_time = orig_burn_time / 10;
        burnt_down = 1;
        remove_alarm(alarm_id);
        alarm_id = 0;
        waslit = 1;
        room->remove_prop("_room_has_fire");
        room->remove_prop(OBJ_I_HAS_FIRE);
        room->update_light();
        remove_name(({"stack", "stack of firewood", "firewood", "campfire", "wood", }));
        set_name("old campfire");
        add_name("ashes");
        add_name("pile");
        add_adj("pile of");
        if (!(cool_alarm && sizeof(get_alarm(cool_alarm))) &&
            !(room->query_prop(ROOM_I_INSIDE)))
            cool_alarm = set_alarm(itof(COOL_INTERVAL),
                                   itof(COOL_INTERVAL), cool_down);
    }
    else if (burnt_down)
    {
        write("You kick the ashes of the "+query_name()+", and spread them to "
          + "remove the traces.\n");
        say(QCTNAME(TP)+" kicks the ashes of the "+query_name()+", spreading "
          + "them to remove the traces.\n",TP);
        blow_away_ashes();
    }
    else if (!(alarm_id && sizeof(get_alarm(alarm_id))))
    {
        write("You kick at the readied "+query_name()+", and spread the "
          + "firewood all around.\n");
        say(QCTNAME(TP)+" kicks at the readied "+query_name()+", spreading the "
          + "firewood all around.\n");
        remove_object();
    }
    return 1;
}

varargs void
go_out(int i)
{
    object  room = ENV(TO);

    remove_name(({"fire", "stack", "stack of firewood", "firewood", "wood", }));

    if (is_stack)
    {
        set_name("stack of firewood");
        set_adj("burnt");
    }
    else
    {
        set_name("campfire");
        set_adj("old");
    }
    add_name("ashes");
    add_name("pile");
    add_adj("pile of");

    if (i)
    {
        tell_room(room, BSN("The flames of the "+query_name()+" flicker "
          + "briefly. Then it goes out, leaving only a smoking "
          + "pile of ashes."));
        burnt_down = 1;
    }
    else
    {
        tell_room(room, BSN("The flames of the "+query_name()+" silently "
          + "die out, leaving a half-burnt pile of smoking firewood."));
        waslit = 1;
    }
    /* remove prop _room_has_fire from environment, Olorin, 14-apr-93 */
    room->remove_prop("_room_has_fire");
    room->remove_prop(OBJ_I_HAS_FIRE);
    room->update_light();
    if (!(cool_alarm && sizeof(get_alarm(cool_alarm))) &&
        !(room->query_prop(ROOM_I_INSIDE)))
        cool_alarm = set_alarm(itof(COOL_INTERVAL),
                               itof(COOL_INTERVAL), cool_down);
}

void
cool_down()
{
    cool_ticks += COOL_INTERVAL;

    if (cool_ticks > 10*orig_burn_time)
    {
        blow_away_ashes();
        // return here to prevent runtime errors (this_object() == 0)
        return;
    }

 
    if (!random(2))
    {
	if (!objectp(TO))
	    log_file("errors", "\n" +
		     "\tthis_object() not define in firewood.\n\n");
	else
	    tell_room(ENV(TO), "A sudden gust of wind blows away some of "
		+ "the ashes from the "+query_adj()+" "+query_name()+".\n");
    }
}

int
query_burnt_down()
{
    return burnt_down;
}


void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!(cool_alarm && sizeof(get_alarm(cool_alarm))))
        return;

    if (!objectp(dest) || !living(dest))
        return;
    // remove the alarm if someone picks up the ashes
    remove_alarm(cool_alarm);
    cool_alarm = 0;
}

/*
 * Function name: destroy_firewood
 * Description:    A call to this function will destroy the firewood.
 *                 It will turn ash-grey and will not burn anymore.
 * Returns:        0 / 1 - Failure / success
 */
public int
destroy_firewood()
{
    if (query_lit())
        return 0;
    not_burning = 1;
    add_adj("ash-grey");
    return 1;
}

public void
init()
{
    add_action(light_fire, "light");
    add_action(extinguish, "extinguish");
    add_action(get_torch,  "get");
    add_action(get_torch,  "take");
    add_action(get_torch,  "pick");
    add_action(kick_fire,  "kick");
    add_action(put_on_fire, "put");
    add_action(put_on_fire, "place");
}

/*
 * Function name:       do_search
 * Description  :       scorch their fingers if they search a burning fire
 * Arguments    :       object tp       this player
 *              :       string          whatever the player searched
 * Return       :       string describing results of search
 */
public string
do_search(object tp, string arg)
{
    if ( test_lit() )
    {
	tp->reduce_hit_point(2 + random(5));
	tell_object(tp,
	    BSN("Ouch! You burn yourself while searching the campfire."));
    }

    return "";	/* use default msg for you-find-nothing */
}
 
/*
 * Function name:       put_on_fire
 * Description  :       if there's a fire in the env, allow putting
 *                      more wood on it.
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 *
 * since OBJ_I_HAS_FIRE can be set for torches, also check for
 * a "fire" item in the env.
 * since we have no idea whether the fire is in a fireplace or
 * pit or campfire or ..., we can only do very limited parsing:
 *      put [wood/firewood/...] 'on' / 'in' [the] fire
 */
public int
put_on_fire(string arg)
{
    object      ob, env;
 
    if ( !strlen(arg) ||
    !parse_command(LOW(arg), all_inventory(TP),
      "%o 'on' / 'in' [the] 'fire'", ob) ||
    ob != TO )
        return 0;
 
    if ( !stringp((env = ENV(TP))->long("fire", TP)) &&
    !sizeof(FIND_STR_IN_OBJECT("fire", env)) )
        return 0;
 
    WRITE("You put the wood on the fire.");
    SAY(" puts some wood on the fire.");
    remove_object();
    return 1;
}
