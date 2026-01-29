/*
 * The steed of the nazgul.
 * 
 * In principle it works like a teleport spell from all outside rooms
 * not protected against magic or teleportation to predefined rooms.
 *
 * Based on the original idea by Olorin
 */

#pragma strict_types

#include <const.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../../morgulmage.h"
#include <cmdparse.h>
#include <filter_funs.h>
#include <options.h>
#include <living_desc.h>
#include <composite.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/d/Gondor/common/lib/time.c";
inherit MORGUL_SPELL_OBJ_DIR + "winged_steed_flight";

#define ATT_BEAK  0
#define ATT_CLAWS 1

#define HIT_HEAD  0
#define HIT_BODY  1
#define HIT_LWING 2
#define HIT_RWING 3
#define HIT_LCLAW 4
#define HIT_RCLAW 5

string owner;
int is_dismissed = 0;

string pinion_desc();
string long_desc();
string view_desc();
string rider_short();

public void create_creature()
{
    set_name("steed");
    add_name(({ "creature", "bird", "beast", "wyrm", "figure" }));
    set_adj(({ "fell", "black", "winged", "dark", "monstrous", "naked",
        "huge" }));

    set_race_name("winged steed");
    set_short(rider_short);
    set_long(long_desc);

    set_gender(G_NEUTER);

    add_item(({ "wing", "wings", "pinions", "pinion", }), pinion_desc);
    add_item(({ "creature", "beast", "bird", "winged creature", "steed",
        "winged steed", "fell beast", "wyrm" }), long_desc);

    add_item(({ "view", "room" }), view_desc);

    set_stats(({ 80, 20, 20,  5,  5, 10, }));

    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_DEFENCE, 10);

    set_whimpy(80);
    set_alignment(-700);

    set_attack_unarmed(ATT_BEAK,  10, 10, W_IMPALE,           30, "beak");
    set_attack_unarmed(ATT_CLAWS, 10, 10, W_IMPALE | W_SLASH, 70, "claws");

    set_hitloc_unarmed(HIT_HEAD,  ({ 10, 10,  5, }), 12, "head");
    set_hitloc_unarmed(HIT_BODY,  ({  5,  5,  5, }), 16, "body");
    set_hitloc_unarmed(HIT_LWING, ({ 15,  5, 10, }), 24, "left pinion");
    set_hitloc_unarmed(HIT_RWING, ({ 15,  5, 10, }), 24, "right pinion");
    set_hitloc_unarmed(HIT_LCLAW, ({ 15,  5,  5, }), 12, "left claw");
    set_hitloc_unarmed(HIT_RCLAW, ({ 15,  5,  5, }), 12, "right claw");

    add_prop(CONT_I_VOLUME,      100* 1000);
    add_prop(CONT_I_MAX_VOLUME, 1000* 1000);
    add_prop(CONT_I_WEIGHT,       89* 1000);
    add_prop(CONT_I_MAX_WEIGHT, 1000* 1000);
    add_prop(CONT_I_LIGHT, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
}

string 
rider_short() {
    object *livings = FILTER_LIVE(all_inventory(this_object()));
    if (sizeof(livings)) {
        return "dark figure mounted on a huge winged beast";
    }

    return "huge winged beast";
}

int targeted_this_steed(string args) {
    if (!args || !strlen(args)) return 0;
    if (is_dismissed) return 0;

    object *obs = PARSE_COMMAND(args, ({ this_object() }), "[the] %l");
    if (obs && (member_array(this_object(), obs) != -1)) return 1;

    obs = PARSE_COMMAND(args, 0, "[the] %l");
    if (obs && (member_array(this_object(), obs) != -1)) return 1;

    return 0;
}

int is_owner(mixed player) {
    if (objectp(player)) player = player->query_real_name();
    return owner == player;
}

void set_owner(mixed player) {
    if (objectp(player)) player = player->query_real_name();
    owner = player;
}

string get_owner() {
    return owner;
}

string describe_environment() {
    string desc = "";

    object env = environment(this_object());
    if (this_player()->query_wiz_level()) {
        if (stringp(env->query_prop(OBJ_S_WIZINFO)))
            desc += "Wizinfo ";

        desc += file_name(env) + "\n";
    }
    
    if (!CAN_SEE_IN_A_ROOM(this_player(), env)) {
        string item = env->query_prop(ROOM_S_DARK_LONG);
        desc += stringp(item) ? item : LD_DARK_LONG;
    } else {
        desc += env->long();

        object *all_objects = all_inventory(environment(this_object()));
        object *visible_obs = FILTER_SHOWN(FILTER_CAN_SEE(all_objects, this_player()));

        object *livings = FILTER_OTHER_LIVE(all_objects);
        object *dead = FILTER_DEAD(all_objects);

        if (sizeof(dead)) {
            desc += capitalize(COMPOSITE_DEAD(dead)) + ".\n";
        }

        if (sizeof(livings)) {
            desc += capitalize(COMPOSITE_LIVE(livings)) + ".\n";
        }
    }

    return desc;
}

string view_desc() {
    if (environment(this_player()) != this_object()) {
        return "You find no view.\n";
    }

    if (in_flight()) {
        if (is_circling()) {
            return "Your winged steed is slowly circling " 
                + query_destination_name() + ".\n";
        } else {
            return "Your winged steed is flying through the air high "
                + "above the ground. All you can see are clouds below you "
                + "while you are hurtling towards " + query_destination_name()
                + ".\n";
        }
    }

    return describe_environment();
}

string long_desc() {
    if (environment(this_player()) == this_object()) {
        if (in_flight()) {
            return "You are mounted on the monstrous winged creature, "
                + "sitting on the naked body between the featherless "
                + "leathery pinions and the long naked neck. The creature "
                + "is high in the air, flying at an incredible speed, and "
                + "an icy wind is blowing into your face.\n";
        } else {
            return "You are mounted on the monstrous winged creature, "
                + "sitting on the naked body between the featherless "
                + "leathery pinions and the long naked neck. The creature "
                + "is standing on the ground, so you can leave it by "
                + "dismounting.\n";
        }
    }

    string desc = "A winged creature: if bird, then greater than all other "
        + "birds, and it is naked, bearing neither quill nor feather, and "
        + "its vast pinions are as webs of hide between horned fingers. A "
        + "creature of an older world maybe it is, whose kind, lingering "
        + "in forgotten mountains cold beneath the Moon, outstayed their "
        + "day, and in hideous eyrie bred this last untimely brood, apt to "
        + "evil."; 

    object *livings = FILTER_LIVE(all_inventory(this_object()));
    if (sizeof(livings)) {
        desc += " " + livings[0]->query_The_name(this_player()) + " is "
            + "mounted on " + query_objective() + ".";
    }

    if (is_owner(this_player())) {
        desc += " It is waiting for you to mount it.";
    }

    return desc + "\n";
}

public void show_visible_contents(object for_obj)
{
    if (environment(for_obj) == this_object()) {
        return;
    } else {
        ::show_visible_contents( for_obj );
    }
}

public string exits_description() {
    return "The only obvious exit is to dismount your winged steed.\n";
}

varargs string long(mixed for_obj) {
    if (stringp(for_obj)) return ::long(for_obj);
    if (!objectp(for_obj)) for_obj = this_player();
    if (!for_obj) return ::long(for_obj);
    if (environment(for_obj) != this_object()) return ::long(for_obj);

    string desc = this_player()->query_option(OPT_BRIEF) ?
        "You are astride your " + query_race_name() + ". " : long_desc() + "\n";

    if(in_flight()) {
        if (is_circling()) {
            desc += "Your winged steed is slowly circling " 
                + query_destination_name() + ".\n";
        } else {
            desc += "Your winged steed is flying through the air high "
                + "above the ground. All you can see are clouds below you "
                + "while you are hurtling towards " + query_destination_name()
                + ".\n";
        }
        return desc;
    } 

    desc += "From here you can see:\n";
    desc += describe_environment();
    return desc;
}

string pinion_desc() {
    if (in_flight()) {
        return "The vast pinions are as webs of hide between horned "
            + "fingers, and the mighty beast is beating them restlessly.\n";
    } else {
        return "The vast pinions are as webs of hide between horned "
            + "fingers. Their span must be twenty feet or more.\n";
    }
}

void catch_msg(mixed str, object player) {
    if (!player) {
        player = this_player();
    }

    ::catch_msg(str, player);
    if (player == this_object()) {
        return;
    }

    if (file_name(environment(this_object())) == MORGUL_WINGED_STEED_ROOM) {
        return;
    }

    if (player && environment(player) == this_object()) {
        tell_room(environment(), str, this_object(), player);
    } else {
        tell_room(this_object(), str, this_object(), player);
    }
}

void throw_off_rider() {
    if (in_flight()) return;

    object *obs = FILTER_LIVE(all_inventory(this_object()));
    foreach(object rider : obs) {
        tell_room(environment(this_object()), ({
            rider->query_name() + " is thrown off " + rider->query_possessive()
            + " " + query_race_name() + ".\n",
            "The " + rider->query_nonmet_name() + " is thrown off "
            + rider->query_possessive() + " " + query_race_name() + ".\n",
            "" }), ({ this_object(), rider }));
        rider->catch_msg("You are thrown off your " + query_race_name() + ".\n");
        rider->move_living("M", environment(this_object()), 1, 0);
    }
}

public void run_away()
{
    set_alarm(0.0, 0.0, throw_off_rider);
    set_alarm(0.1, 0.0, take_off_and_remove);
}

public void attacked_by( object ob )
{
    tell_room(this_object(), QCTNAME(ob) + " attacks your " 
        + query_race_name() + ".\n");
    
    ::attacked_by( ob );
    set_alarm(0.0, 0.0, throw_off_rider);
    set_alarm(0.1, 0.0, take_off_and_remove);
}

int do_mount(string args) {
    if (environment(this_player()) == this_object()) return 0;

    if (!targeted_this_steed(args)) {
        notify_fail("Mount what?\n");
        return 0;   
    }

    if (!is_owner(this_player())) {
        notify_fail("The fell beast does not accept you as its rider.\n");
        return 0;
    }

    if (environment(this_player())->query_prop(ROOM_I_INSIDE) 
        && (environment(this_object())->query_domain() != "Avenir")) {
        notify_fail("There is not enough room to mount your "
            + query_race_name() + " here.\n");
        return 0;
    }

    if (this_player()->query_attack()) {
        notify_fail("You are too busy fighting to do that.\n");
        return 0;
    }

    if (this_object()->query_attack()) {
        notify_fail("The " + this_object()->short() + " is fighting, you "
            + "cannot mount it now.\n");
        return 0;
    }

    if (this_player()->query_skill(SS_ANI_HANDL) < 20) {
        write("Trying to mount this fell beast would be your certain "
            + "doom, since you cannot control it properly!\n");
        return 1;
    }

    if (this_player()->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_RIDING, 
        SS_ANI_HANDL })) <= 0) {
        write("Your clumsy attempt to mount the fell beast fails and you "
            + "are thrown off.\n");
        say(QCTPNAME(this_player()) + " clumsy attempt to mount the fell "
            + "beast fails and "+ this_player()->query_pronoun() 
            + " is thrown off.\n");
        return 1;
    }

    tell_room(environment(this_object()), QCTNAME(this_player()) + " mounts " 
        + this_player()->query_possessive() + " winged steed.\n", 
        ({ this_object(), this_player() }) );

    add_prop(ROOM_I_IS, 1);
    this_player()->remove_prop(OBJ_M_NO_GET);

    if (this_player()->move_living("M", this_object(), 1, 1)) {
        write("Your " + query_race_name() + " is unable to carry you.\n");
    } else {
        write("You mount your " + query_race_name() + ".\n");
    }

    this_player()->add_prop(OBJ_M_NO_GET, 1);
    remove_prop(ROOM_I_IS);
    return 1;
}

int do_dismount(string args) {
    if (environment(this_player()) != this_object()) return 0;

    if (strlen(args) && !id(args)) {
        notify_fail("Dismount what?\n");
        return 0;
    }

    if (in_flight()) {
        notify_fail("The fell beast is flying through the air! "
            + "Dismounting now would be your doom!\n");
        return 0;        
    }

    tell_room(environment(this_object()), QCTNAME(this_player())
        + " dismounts " + this_player()->query_possessive()
        + " " + query_race_name()+ ".\n", ({ this_object(), 
            this_player() }));
    write("You dismount your "+ query_race_name()+ ".\n");

    this_player()->move_living( "M", environment(this_object()), 1, 0);
    return 1;
}

int do_time(string args) {
    if (environment(this_player()) != this_object())
    {
        return 0;
    }

    // Checking time while circling
    if(is_circling()) return check_time(args);

    return environment(this_object())->check_time();
}

string query_domain() {
    return "Gondor";
}

int do_shriek(string args) {
    // This will only work when we are circling
    if(!is_circling()) return 0;

    // We cannot give adverbs
    if(strlen(args)) {
        write("You cannot specify an adverb when mounted on your steed.\n");
        return 1;
    }

    string *msg = ({ "The figure atop the winged beast rasps at his steed. "
        + "The winged beast shrieks terribly. Blind fear mixed with unheard "
        + "of terror and deadly cold descend upon you.\n",

        "The fell wraith atop the winged shape shrieks shrilly. You " 
        + "struggle with fright and madness for mastery of your actions.\n" });
    players_in_circle_region()->catch_msg(one_of_list(msg));

    if(query_verb() != "shriek") {
        tell_room(this_object(),
            "You shriek shrilly, blanketing the land below with the dread " 
            + "of the Nine.\n");
        return 1;
    } else {
        // Let the original shriek command take over
        return 0;
    }
}

int do_dismiss(string args) {
    if (!targeted_this_steed(args)) {
        notify_fail("Dismiss what?\n");
        return 0;   
    }

    if (!is_owner(this_player())) {
        notify_fail("The fell beast does not accept you as its rider.\n");
        return 0;
    }

    if (environment(this_player()) == this_object()) {
        notify_fail("You cannot dismiss your steed while mounted.\n");
        return 0;
    }

    write("You dismiss " + this_object()->query_the_name(this_player()) + ".\n");
    is_dismissed = 1;
    set_alarm(2.0, 0.0, take_off_and_remove);
    return 1;
}

public void init_living()
{
    ::init_living();
    add_action(do_mount,    "mount");
    add_action(do_dismount, "dismount");
    add_action(do_command,  "command");
    add_action(do_time,     "time");
    add_action(do_shriek,   "mwail");
    add_action(do_shriek,   "shriek");
    add_action(do_dismiss,  "dismiss");
}

public void enter_inv( object ob, object from )
{
    ::enter_inv( ob, from );

    if (!objectp( ob ) || !objectp( from ) || living( ob ))
    {
        return;
    }
    ob->move( environment( this_object() ), 1 );
}
