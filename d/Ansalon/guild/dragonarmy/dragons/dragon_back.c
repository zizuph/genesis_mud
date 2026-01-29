/*
 * This is back of the dragonsteed in dragonarmies
 *
 * Added Palanthas destination. - Mortis 9.2014
 *
 * 2019-11-24 - Carnak:
 *  The 'strike' dragons took a spot on the 'summoned', blocking the pull
 *  command. I changed the query_dragon_occupied to only check for players.
 *
 */
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <config.h>
#include <composite.h>
#include <cmdparse.h>

#define MSG_FREQ itof((20 + random(10)))

int dragon_is_flying = 0;
static object dragon, msg_relay;
string dest_desc = "your destination";
mixed back_dest;
int flying_back = 0;
static string *flight_messages = ({
    "The dragon shrieks cruelly, knowing it is the unchallenged "+
    "master of the skies.\n",
    "The dragon stretches its leathery wings, gliding "+
    "leisurely through the skies.\n",
    "The dragon beats its wings powerfully, gaining altitude.\n",
    "The rush of air chills your skin as the dragon wings "+
    "its way to its destination.\n",
    });

int
query_flying()
{
    return dragon_is_flying;
}

public string
fly_msg()
{
    if(query_flying())
    {
    return "";
    }

    return "To take off, simply 'fly to <destination>' or 'fly back'. " +
    "You may also check <destinations> while you are mounted here. "+
    "You can also 'allow' other people to mount your dragon or "+
    "'pull' them to dragon back if they are too scared to mount "+
    "it by themselves.\n";
}

string
dragon_env()
{
    return file_name(E(dragon));
}

object
query_msg_relay()
{
    return msg_relay;
}

void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("Mounted on the back of a dragon");
    set_long("You sit firmly strapped into a dragonsaddle " +
      "mounted on the back of a mighty wyrm, " +
      "one of the many evil dragons serving the dragonarmies. " +
      "@@fly_msg@@\n");

    add_item(({"dragon","wyrm"}),"A more fearsome creature you will " +
      "not find than a dragon, which is what you find yourself " +
      "perched on.\n");
    add_item(({"surroundings","surrounding","view","views"}), 
    "@@surrounding_desc");

    add_exit(VBFC_ME("dragon_env"), "__not__to__be__used__", 1, 0, 1);

    msg_relay = clone_object(DRAGONARMY_DRAGON+"msg_relay");
    msg_relay->move(TO, 1);

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop("_room_m_no_earthmeld", 1);
    add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_HIDE, -1);
    add_prop(ROOM_M_DA_DRAGONSTEED_NO_LAND,"Summoning dragon on another one? Are you mad???\n");
}

string
surrounding_desc()
{
    object *ob_list, *lv, *dd, env;
    string item;

    if(query_flying())
    {
    write("You find yourself flying through the air on the back "+
        "of a mighty dragon, winging your way "+
        (flying_back ? "from " : "towards ")+C(dest_desc)+".\n");
    if(file_name(E(dragon)) == TEMP_DRAGON_ROOM)
        return "";
    }
    
    env = E(dragon);
    write(env->long());
    ob_list = all_inventory(env) - ({ dragon });
    lv = FILTER_LIVE(ob_list);
    dd = FILTER_SHOWN(ob_list - lv);

    item = COMPOSITE_FILE->desc_dead(dd, 1);
    if (stringp(item))
    {
    write(C(item) + ".\n");
    }
    item = COMPOSITE_FILE->desc_live(lv, 1);
    if (stringp(item))
    {
    write(C(item) + ".\n");
    }

    /* Give a nice description of the combat that is going on. */
    TP->describe_combat(lv);

    return "";
}

int
destinations(string str)
{
    if(str)
    {
    NF("What?\n");
    return 0;
    }

    if(!IS_MEMBER(TP))
    {
    NF("Only Dragonarmy members can check the possible destinations.\n");
    return 0;
    }

    write("   --===Destinations===--\n\n"+
    "          Sanction\n"+
    "          Neraka\n" +
    "          Flotsam\n"+
    "          Palanthas\n"+
    "          Pax Tharkas\n"+
    "          Solace\n"+
    "          Kalaman\n"+
    "          Solamnian plains\n" +
    "          Forest of Icewall\n" +
    "          Clearing in Mithas\n" +
    "          Sparkle\n");
    return 1;
}

public void
dismount_all()
{
    int i;
    object *all = all_inventory(TO);
    all -= ({ msg_relay });
    for (i = 0; i < sizeof(all); i++)
    {
    if (all[i] == dragon->query_summoner() || !living(all[i]))
    {
        continue;
    }

    if (interactive(all[i]) || all[i]->query_npc())
    {
        all[i]->command("dismount dragon");
        continue;
    }

    all[i]->move_living("M", OWN_STATUE, 1);
    OWN_STATUE->set_revive_dest(all[i], file_name(E(dragon)));
    }
}

public void
arrive(mixed dest)
{
    int i;
    string *dnames;

    dragon_is_flying = 0;

    /* move() returns 0 if success */
    if(dragon->move(dest, 1))
    {
    if(flying_back)
    {
        dest = DRAGON_MANAGER->query_destination_file(lower_case(dest_desc));
    }
    else
    {
        dest = back_dest;
    }
    if(dragon->move(dest, 1))
    {
        dnames = DRAGON_MANAGER->query_destinations();
        for(i=0; i<sizeof(dnames); i++)
        {
        dest = DRAGON_MANAGER->query_destination_file(dnames[i]);
        if(!dragon->move(dest, 1))
        {
            i = sizeof(dnames)+1;
        }
        }
        if(i == sizeof(dnames))
        {
        tell_room(TO, "*** BUG ***\n"+
            "Dragon could not land at any destination.\n"+
            "Please call wizard for help.\n"+
            "*** ENDBUG ***\n");
        return;
        }
    }
    }

    tell_room(TO, "The dragon suddenly dives, then extends " +
      "its mighty wings as it lands at your destination.\n");
    tell_room(dest, "With a powerful beat of its wings, " +
    LANG_ADDART(dragon->short())+ " lands here.\n");
    (dragon->query_summoner())->command("exa view");
    dismount_all();
}

public void
give_flight_messages()
{
    if(!query_flying())
    {
    return;
    }
    tell_room(TO, flight_messages[random(4)]);
    set_alarm(MSG_FREQ, 0.0, give_flight_messages);
}

public int
fly(string instr)
{
    string str;
    mixed file;
    int time, size = dragon->query_dragon_size();

    if(!instr || (instr != "back" && !sscanf(instr, "to %s", str)))
    {
    NF(C(query_verb()) + " to where?\n");
    return 0;
    }
    if(query_flying())
    {
    NF("You are already flying to a destination.\n");
    return 0;
    }
    if(TP != dragon->query_summoner() && !TP->query_wiz_level())
    {
    NF("The dragon refuses to obey.\n");
    return 0;
    }

    if (instr == "back")
    {
    if(!back_dest)
    {
        NF("You cannot fly back now. First you have to fly to a destination.\n");
        return 0;
    }
    file = back_dest;
    back_dest = 0;
    flying_back = 1;
    }
    else
    {
    flying_back = 0;

    setuid();
    seteuid(getuid());

    str = lower_case(str);

    if(!(file = DRAGON_MANAGER->query_destination_file(str)))
    {
        NF(C(str)+" is not valid destination.\n");
        return 0;
    }

    if(!DRAGON_MANAGER->query_open_destination(str))
    {
        write("Sorry, "+C(str)+" is out of order now.\n");
        return 1;
    }

    if(file == file_name(E(dragon)))
    {
        write("You are already there!\n");
        return 1;
    }

    dest_desc = str;
    back_dest = E(dragon);
    file_name(back_dest)->load();
    if(back_dest == find_object(file_name(back_dest)))
    {
        back_dest = file_name(back_dest);
    }
    }

    time = 80 - (size*13) + random(40 - (size*7));
    if (!wildmatch("/d/Ansalon*", file) && !wildmatch("/d/Krynn*", file))
    {
    time *= 2;
    }
    set_alarm(itof(time), 0.0, &arrive(file));
    set_alarm(MSG_FREQ, 0.0, give_flight_messages);

    tell_room(E(dragon), "The "+dragon->short()+
    " beats its massive wings, and takes off into the sky!\n");
    dragon->move(TEMP_DRAGON_ROOM, 1);

    tell_room(TO, "The dragon takes off!\n"+
      "You find yourself airborne, the ground swiftly dropping below you.\n");

    dragon_is_flying = 1;
    return 1;
}

public object
query_dragon()
{
    return dragon;
}

public void
set_dragon(object ob)
{
    dragon = ob;
}

public void
drop(object ob)
{
    object *all, *obj;
    int i;

    if (!objectp(ob) || environment(ob) != TO)
    {
    return;
    }

    obj = filter(all_inventory(TO), &->query_prop("_drop_from_dragon"));

    if(query_flying())
    {
    all = all_inventory(TO);
    for (i = 0; i < sizeof(all); i++)
    {
        if (!interactive(all[i]) || !CAN_SEE_IN_ROOM(all[i]))
        {
        continue;
        }
        all[i]->catch_tell(C(FO_COMPOSITE_DEAD(obj, all[i])) + 
        " fall" + (sizeof(obj) == 1 ? "s" : "")+
        " to the ground deep below.\n");
    }
    obj->remove_object();
    }
    else
    {
    obj->move(E(dragon), 1);
        obj->remove_prop("_drop_from_dragon");
/*
    all = all_inventory(E(dragon));
    for (i = 0; i < sizeof(all); i++)
    {
        if (!interactive(all[i]) || !CAN_SEE_IN_ROOM(all[i]))
        {
        continue;
        }
        all[i]->catch_msg(QCTNAME(TP)+" drops "+
        FO_COMPOSITE_DEAD(obj, all[i])+" to the ground.\n");
    }
*/
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if ((!living(ob) && !ob->query_no_show()) || interactive(from))
    {
    ob->add_prop("_drop_from_dragon", 1);
    set_alarm(0.0, 0.0, &drop(ob));
    }
}

public object *
query_dragon_occupied()
{
    return FILTER_PLAYERS(all_inventory(TO));
}

public int
dismount(string str)
{
    if(strlen(str) && (str != "dragon"))
    {
    NF(C(query_verb()) + " what?\n");
    return 0;
    }

    if(query_flying())
    {
    write("Dismounting now would be suicide!\n");
    return 1;
    }

/*
    say(({ METNAME+ " dismounts the dragon.\n",
    NONMETNAME+ " dismounts the dragon.\n",
    "", }));
*/
    TP->move_living("M", environment(dragon), 1);
    say(({METNAME+ " dismounts the dragon.\n",
    NONMETNAME+ " dismounts the dragon.\n",
    "", }));

    return 1;
}

public int
prevent_leave(object ob)
{
    int i;

    /* Don't allow linkdead players to leave */
    if (living(ob) && !ob->query_npc() && !interactive(ob))
    {
    while ((ob = calling_object(-i++)) && (file_name(ob) != OWN_STATUE));
    return !!ob;
    }

    return 0;
}

public int
allow(string str)
{
    object *oblist;

    if (!strlen(str))
    {
    NF(C(query_verb()) + " who to mount?\n");
    return 0;
    }
    parse_command(str, all_inventory(E(dragon)), "[the] %l [to] [mount]", oblist);
    if (!sizeof(oblist))
    {
    NF(C(query_verb()) + " who to mount?\n");
    return 0;
    }
    oblist -= ({ oblist[0] });
    if (!sizeof(oblist))
    {
    NF(C(query_verb()) + " who to mount?\n");
    return 0;
    }
    if (TP != dragon->query_summoner())
    {
    NF("You cannot allow anyone to mount this dragon.\n");
    return 0;
    }

    oblist->catch_msg(QCTNAME(TP)+" allows you to mount "+HIS(TP)+" "+
            dragon->short()+".\n");
    TP->catch_tell("You allow "+COMPOSITE_LIVE(oblist)+" to mount your dragon.\n");
    oblist->add_prop("_da_can_mount_dragon", dragon);
    return 1;
}
/* I did not change command itself - only messages it returns
 * and those were just minor changes. It would be good to rephrase whole command
 * though
 *       Torqual 3.10.2001
 */
public int
pull(string str)
{
    object *oblist;

    if (!strlen(str))
    {
    NF(C(query_verb()) + " who to dragon back?\n");
    return 0;
    }
    parse_command(str, all_inventory(E(dragon)), "[the] %l [to] [dragon] [back]", oblist);
    if (sizeof(oblist))
    oblist -= ({ oblist[0] });
    if (!sizeof(oblist))
    {
    NF(C(query_verb()) + " who to dragon back?\n");
    return 0;
    }
    if (TP != dragon->query_summoner())
    {
    //NF("You cannot pull anyone to this dragon back.\n"); 
        // changed by Torqual
    NF("The dragon eyes you up intently, daring you to make "+
       "that mistake. As you straighten up, the dragon turn its "+
       "attention to somewhere else.\n");
    return 0;
    }
    if (sizeof(query_dragon_occupied()) > 1)
    {
    NF("There is no more place left up here.\n");
    return 0;
    }
    if (sizeof(oblist) > 1)
    {
    write("You can pull only one person up on the dragon's back.\n");
    return 1;
    }
    if (member_array(oblist[0], TP->query_team_others()) < 0)
    {
    write(oblist[0]->query_The_name(TP)+" is not in your team. "+
        "You can pull only your teammembers.\n");
    return 1;
    }
    if (oblist[0]->query_prop("_wolf_i_riding"))
    {
    write(oblist[0]->query_The_name(TP)+" is riding a wolf.\n");
        return 1;
    }

    oblist[0]->catch_tell(TP->query_The_name(oblist[0])+" pulls you up to "+
            "the " + dragon->short()+"'s back.\n");
    TP->catch_tell("You pull "+oblist[0]->query_the_name(TP)+
           " up to your dragon's back.\n");
    tell_room(E(dragon), QCTNAME(TP)+" pulls "+QTNAME(oblist[0])+
        " up to the "+dragon->short()+"'s back.\n", oblist, TP);
    oblist[0]->move_living("M", TO, 1);
    return 1;
}

public void
init()
{
    ::init();
    add_action(fly, "fly");
    add_action(dismount, "dismount");
    add_action(destinations, "destinations");
    add_action(allow, "allow");
    add_action(pull, "pull");
}
