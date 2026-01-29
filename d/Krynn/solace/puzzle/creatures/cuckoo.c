/* A cuckoo from a cuckoo-clock. ~solace/puzzle/creatures/cuckoo */

inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../defs.h"
#include "/sys/const.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/language.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

#define ATT_WING1	0
#define ATT_WING2	1
#define ATT_BEAK	4

#define HIT_BODY	0
#define HIT_HEAD	1
#define HIT_WING1	2
#define HIT_WING2	3

string *acts = ({ "pecks at the bird-seed hungrily.",
                  "raises its head thoughtfully.",
                  "opens its beak and to you surprise, begins to speak!" });

void create_creature()
{
    int i;

    set_name("cuckoo");
    set_adj("small");
    add_adj("yellow-plumed");
    set_alignment(200 + random(500));
    set_race_name("cuckoo");
    set_gender(G_NEUTER);
    set_long("A cute little cuckoo. It looks very hungry. It must have been "+
        "stuck in that clock for a very long time.\n");

    for(i = 0; i < 6; i++)
        set_base_stat(i, (2 + random(5))); // Stats are 2 to 6.

    set_hp(10000);

                    /* Att_id     Hit Pen  Dam_type      %  Att_string */
    set_attack_unarmed(ATT_WING1,  12, 10,  W_BLUDGEON, 25, "left wing");
    set_attack_unarmed(ATT_WING2,  12, 10,  W_BLUDGEON, 25, "right wing");
    set_attack_unarmed(ATT_BEAK,   13, 11,  W_IMPALE,   50, "beak");

                    /* Hit_id     Ac   %  Hit_string */
    set_hitloc_unarmed(HIT_BODY,   3, 40, "body");
    set_hitloc_unarmed(HIT_HEAD,   4, 10, "head");
    set_hitloc_unarmed(HIT_WING1,  2, 25, "left wing");
    set_hitloc_unarmed(HIT_WING2,  2, 25, "right wing");

    remove_prop(OBJ_M_NO_GET);
    remove_prop(OBJ_I_NO_GET);

    add_prop(CONT_I_HEIGHT, 25);
    add_prop(CONT_I_WEIGHT, 750);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, C(LANG_THESHORT(TO))+" is far too cute to do "+
        "that!\n");

    change_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_act_time(1 + random(5));
    add_act("emote @@flap@@");
    add_act("emote cheeps merrily.");
    add_act("emote cheeps hungrily.");
    add_act("emote flaps its little wings.");
    add_act("emote pecks @@peck@@ hungrily.");
}

void init_living()
{
    ::init_living();

    add_action("stop_put", "put");
    add_action("feed_cuckoo", "feed");
}

int stop_put(string str) // Stop them putting the cuckoo on a bag/container.
{
    string dummy;

    if(parse_command(str, TP, "[small] [yellow-plumed] 'cuckoo' 'in' 'into' "+
        "[the] %s", dummy))
    {
        write("Suddenly, "+LANG_THESHORT(TO)+" flaps its wings hard and "+
            "flies around the room before landing on the floor.\n");

        TO->move(E(TP));
        return 1;
    }
    return 0;
}

string flap()
{
    if(LIVING(E(TO)))
        TO->move(E(E(TO)));

    return("flaps its wings hard and flies around the room before landing "+
        "on the floor.");
}

string peck()
{
    string *desc = ({ "hand", "shoulder", "ear", "arm", "foot", "leg" });

    if(LIVING(E(TO)))
        return("at your "+desc[random(6)]);
    else
        return("at the floor");
}

int feed_cuckoo(string str)
{
    int i;
    string food;
    object *arr, seed, obj;

    if(!strlen(str))
    {
        notify_fail("Feed who/what?\n");
        return 0;
    }

    if(member_array(TO, FIND_STR_IN_OBJECT(str, TP)) != -1)
    {
        notify_fail("Feed the "+str+" with what?\n");
        return 0;
    }

    if(parse_command(str, E(TP), "%o 'with' %s", obj, food))
    {
        arr = FIND_STR_IN_OBJECT(food, TP);

        if(!sizeof(arr))
        {
            notify_fail("You don't have a "+food+".\n");
            return 0;
        }

        if(!objectp(obj) || obj != TO)
        {
            notify_fail("Feed what with the "+food+"?\n");
            return 0;
        }

        for(i = 0; i < sizeof(arr); i++)
        {
            if(MASTER_OB(arr[i]) == OBJECTS + "bird_seed")
                seed = arr[i];
        }

        if(objectp(seed))
        {
            seed->remove_object();

            set_alarm(1.0, 0.0, "tell_password", 0);

            TP->catch_msg(QCTNAME(TO)+" cheeps happily and begins to peck "+
                "at the seed.\n");

            tell_room(E(TP), QCTNAME(TP)+" offers some seed to "+QTNAME(TO)+
                " who cheeps happily and begins to peck at the seed.\n",
                ({ TO, TP }));
        }
        else
        {
            TP->catch_msg(QCTNAME(TO)+" totally ignores your offering.\n");

            tell_room(E(TP), QCTNAME(TP)+" offers something to "+QTNAME(TO)+" "+
                "who just totally ignores it.\n", ({ TO, TP }));
        }

        return 1;
    }

    notify_fail("Feed what with what?\n");
    return 0;
}

void tell_password(int timer)
{
    mixed *exits;
    string *desc, passwd, direction;

    if(LIVING(E(TO)))
        exits = E(E(TO))->query_exit_cmds();
    else
        exits = E(TO)->query_exit_cmds();

    if(sizeof(acts) != 5)
    {
        passwd = find_object(LOCATIONS + "sargonnas")->query_password();

        acts += ({ "cheeps: The password to the Sargonnas room is '"+
            passwd+"'." });
        acts += ({ "flies away "+exits[random(sizeof(exits))]+"wards." });
    }

    switch(timer)
    {
        case 0..4:
        {
            timer++;

            command("emote "+acts[timer - 1]);

            set_alarm(2.0, 0.0, "tell_password", timer);
            break;
        }

        default:
            TO->remove_object();
    }
}
