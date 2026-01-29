/*
 * This is back of the dragonsteed in dragonarmies
 * Modified: Louie 2005 to be a wyvern back for soldiers.  I mostly
 *    just changed all the words "dragon" to "wyvern" because
 *    I like efficiency and irony.
 *
 * Added Palanthas destination. - Mortis 9.2014
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

int wyvern_is_flying = 0;
static object msg_relay;
private object wyvern;
string dest_desc = "your destination";
mixed back_dest;
int flying_back = 0;
static string *flight_messages = ({
    "The wyvern gives a high pitched shriek.\n",
    "The wyvern stretches its leathery wings, gliding "+
    "leisurely through the skies.\n",
    "The wyvern beats its wings powerfully, gaining altitude.\n",
    "The rush of air chills your skin as the wyvern wings "+
    "its way to its destination.\n",
    });

/*proto*/
public object * query_wyvern_occupied();

int
query_flying()
{
    return wyvern_is_flying;
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
    "You can also 'allow' other people to mount your wyvern or "+
    "'pull' them to wyvern back, if your wyvern is large enough.\n";
}

string
wyvern_env()
{
    return file_name(E(wyvern));
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

    set_short("Mounted on the back of a wyvern");
    set_long("You are sitting bareback on a wyvern "+
        "trained to transport Dragonarmy soldiers.  " +
      "@@fly_msg@@\n");

    add_item(({"wyvern","steed"}),"This is a wyvern, "+
        "one of the more bad tempered creatures of the realms.  "+
        "\n");
    add_item(({"surroundings","surrounding","view","views"}), 
    "@@surrounding_desc");

    add_exit(VBFC_ME("wyvern_env"), "__not__to__be__used__", 1, 0, 1);

    msg_relay = clone_object(DRAGONARMY_DRAGON+"msg_relay");
    msg_relay->move(TO, 1);

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop("_room_m_no_earthmeld", 1);
    add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_HIDE, -1);
    add_prop(ROOM_M_DA_DRAGONSTEED_NO_LAND,"Summoning a dragon on a wyvern? Are you mad?\n");
}

string
surrounding_desc()
{
    object *ob_list, *lv, *dd, env;
    string item;

    if(query_flying())
    {
    write("You are flying through the air on the back "+
        "of "+LANG_ADDART(wyvern->short())+", on your way "+
        (flying_back ? "from " : "towards ")+C(dest_desc)+".\n");
    if(file_name(E(wyvern)) == TEMP_DRAGON_ROOM)
        return "";
    }
    
    env = E(wyvern);
    write(env->long());
    ob_list = all_inventory(env) - ({ wyvern });
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

    if(!IS_MEMBER(TP) && !TP->query_wiz_level())
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
    "          Solamnian plains\n" +
    "          Forest of Icewall\n" +
    "          Clearing in Mithas\n" +
        "          Sparkle\n\n");
    return 1;
}

public void
dismount_all()
{
    int i;
    object *all = all_inventory(TO);
    for (i = 0; i < sizeof(all); i++)
    {
    if (all[i] == wyvern->query_summoner() || !living(all[i]))
    {
        continue;
    }

    if (interactive(all[i]) || all[i]->query_npc())
    {
        all[i]->command("$dismount wyvern");
        continue;
    }

    all[i]->move_living("M", OWN_STATUE, 1);
    OWN_STATUE->set_revive_dest(all[i], file_name(E(wyvern)));
    }
}

public void
arrive(mixed dest)
{
    int i;
    string *dnames;

    wyvern_is_flying = 0;

    /* move() returns 0 if success */
    if(wyvern->move(dest, 1))
    {
    if(flying_back)
    {
        dest = DRAGON_MANAGER->query_destination_file(lower_case(dest_desc));
    }
    else
    {
        dest = back_dest;
    }
    if(wyvern->move(dest, 1))
    {
        dnames = DRAGON_MANAGER->query_destinations();
        for(i=0; i<sizeof(dnames); i++)
        {
        dest = DRAGON_MANAGER->query_destination_file(dnames[i]);
        if(!wyvern->move(dest, 1))
        {
            i = sizeof(dnames)+1;
        }
        }
        if(i == sizeof(dnames))
        {
        tell_room(TO, "*** BUG ***\n"+
            "Wyvern could not land at any destination.\n"+
            "Please call a wizard for help.\n"+
            "*** ENDBUG ***\n");
        return;
        }
    }
    }

    tell_room(TO, "The wyvern suddenly dives, then extends " +
      "its mighty wings as it lands at your destination.\n");
    tell_room(dest, "With a loud shriek, " +
        LANG_ADDART(wyvern->short())+ " lands here.\n", 
        query_wyvern_occupied(),TO);
    (wyvern->query_summoner())->command("exa view");
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
    int time;

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
    if(TP != wyvern->query_summoner() && !TP->query_wiz_level())
    {
    NF("The wyvern refuses to obey.\n");
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

    if(file == file_name(E(wyvern)))
    {
        write("You are already there!\n");
        return 1;
    }

    dest_desc = str;
    back_dest = E(wyvern);
    file_name(back_dest)->load();
    if(back_dest == find_object(file_name(back_dest)))
    {
        back_dest = file_name(back_dest);
    }
    }

    time = 120 - random(20);
    if (!wildmatch("/d/Ansalon*", file) && !wildmatch("/d/Krynn*", file))
    {
    time *= 2;
    }
    set_alarm(itof(time), 0.0, &arrive(file));
    set_alarm(MSG_FREQ, 0.0, give_flight_messages);

    tell_room(E(wyvern), "The "+wyvern->short()+
    " beats its leathery wings, and launches into the sky!\n");
    wyvern->move(TEMP_DRAGON_ROOM, 1);

    tell_room(TO, "The wyvern takes off!\n"+
      "You find yourself airborne, the ground swiftly dropping below you.\n");

    wyvern_is_flying = 1;
    return 1;
}

public object
query_wyvern()
{
    return wyvern;
}

public void
set_wyvern(object ob)
{
    wyvern = ob;
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

    obj = filter(all_inventory(TO), &->query_prop("_drop_from_wyvern"));

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
    obj->move(E(wyvern), 1);
        obj->remove_prop("_drop_from_wyvern");
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if ((!living(ob) && !ob->query_no_show()) || interactive(from))
    {
    ob->add_prop("_drop_from_wyvern", 1);
    set_alarm(0.0, 0.0, &drop(ob));
    }
}

public object *
query_wyvern_occupied()
{
    return FILTER_LIVE(all_inventory(TO)) - ({ msg_relay });
}

public int
dismount(string str)
{
    if(strlen(str) && (str != "wyvern"))
    {
    NF(C(query_verb()) + " what?\n");
    return 0;
    }

    if(query_flying())
    {
    write("Dismounting now would be suicide!\n");
    return 1;
    }

    TP->move_living("M", environment(wyvern), 1);
    say(({METNAME+ " dismounts the wyvern.\n",
    NONMETNAME+ " dismounts the wyvern.\n",
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
    parse_command(str, all_inventory(E(wyvern)), "[the] %l [to] [mount]", oblist);
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
    if (TP != wyvern->query_summoner())
    {
    NF("You cannot allow anyone to mount this wyvern.\n");
    return 0;
    }

    oblist->catch_msg(QCTNAME(TP)+" allows you to mount "+HIS(TP)+" "+
            wyvern->short()+".\n");
    TP->catch_tell("You allow "+COMPOSITE_LIVE(oblist)+" to mount your wyvern.\n");
    oblist->add_prop("_da_can_mount_wyvern", wyvern);
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
    NF(C(query_verb()) + " whom to wyvern back?\n");
    return 0;
    }
    parse_command(str, all_inventory(E(wyvern)), "[the] %l [to] [wyvern] [back]", oblist);
    if (sizeof(oblist))
    oblist -= ({ oblist[0] });
    if (!sizeof(oblist))
    {
    NF(C(query_verb()) + " whom to wyvern back?\n");
    return 0;
    }
    if (TP != wyvern->query_summoner())
    {
    //NF("You cannot pull anyone to this wyvern back.\n"); 
        // changed by Torqual
    NF("The wyvern eyes you up intently, daring you to make "+
       "that mistake. As you straighten up, the wyvern turn its "+
       "attention to somewhere else.\n");
    return 0;
    }
    if (wyvern->query_wyvern_size() == "small" ||
        sizeof(query_wyvern_occupied()) > 1)
    {
    NF("There is no room for more riders.\n");
    return 0;
    }
    if (sizeof(oblist) > 1)
    {
    write("You can pull only one person up on the wyvern's back.\n");
    return 1;
    }
    if (member_array(oblist[0], TP->query_team_others()) < 0)
    {
    write(oblist[0]->query_The_name(TP)+" is not in your team. "+
        "You can pull only your team members.\n");
    return 1;
    }
    if (oblist[0]->query_prop("_wolf_i_riding"))
    {
    write(oblist[0]->query_The_name(TP)+" is riding a wolf.\n");
        return 1;
    }

    oblist[0]->catch_tell(TP->query_The_name(oblist[0])+" pulls you up to "+
            "the " + wyvern->short()+"'s back.\n");
    TP->catch_tell("You pull "+oblist[0]->query_the_name(TP)+
           " up to your wyvern's back.\n");
    tell_room(E(wyvern), QCTNAME(TP)+" pulls "+QTNAME(oblist[0])+
        " up to the "+wyvern->short()+"'s back.\n", oblist, TP);
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
