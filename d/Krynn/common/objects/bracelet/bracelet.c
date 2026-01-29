/*
 * A 'braclet of charms' from the Dragonlance Fighter guide
 *
 * Cotillion - 2003-03-17
 *
 * Navarre April 9th 2009: Changed to work with new recovery changes.
 */
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#define MAX_HOLD 5
#define USE_INTERVAL 15
#define EVOLVE_INTERVAL 3600
#define MAX_CONTAINER_TIME 7453 
#define CLASP_PROP "krynn_bracelet_clasp"

/*
 * Globals
 */
string command_word = "evolve";
int last_use, last_evolve, break_alarm;
object prison;

/*
 * Prototypes
 */
string long_generator();
string clasp_generator();
string charm_generator();

void
create_object()
{
    setuid();
    seteuid(getuid());

    set_name("bracelet");
    set_adj(({ "golden" }));
    
    set_long(&long_generator());
    add_item("clasp", &clasp_generator());
    add_item(({ "charm", "charms" }), &charm_generator());
        

    set_slots(A_ANY_ARM);
    set_keep(1);

    add_prop(OBJ_I_VOLUME, 130);
    add_prop(OBJ_I_WEIGHT, 230);
    add_prop(OBJ_I_VALUE, 5420);

    add_prop(MAGIC_AM_ID_INFO, 
        ({ "This bracelet is most assuredly magic.", 10,
               "The bracelet smells strongly of transformation magic.", 30,
               "It is a 'Braclet of Charms'. " + 
               "The magic of the bracelet can transfer items into a " + 
               "magic dimension from which they can be called by the " + 
               "bracelets wearer.", 60,
               }));
    add_prop(MAGIC_AM_MAGIC, ({ 70, "transformation" }));
    
    add_prop(OBJ_S_WIZINFO,
        "This object stores other weapons. Check its inventory " + 
        "if you need to retrive something.\n");
    
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    
    last_evolve = time();
    last_use = time();

    will_not_recover = (random(100) > 30);
    
    set_wf(this_object());
}

public int
add_prop_obj_i_broken(mixed value)
{
    set_adj("broken");
    set_short("broken golden bracelet");
    return 0;
}

public string
query_recover()
{
    return MASTER + ":";
}

string
long_generator()
{
    int size;
    string ret;
    
    ret = "It's a nicely crafted bracelet of sturdy gold links. " + 
        "The clasp is of a delicate elven design. It's wide enough " + 
        "to easily slide around the blade of a broadsword.\n";
    
    if (size = sizeof(all_inventory()))
    {
        ret += "Hanging from the bracelet you see " + 
            LANG_WNUM(size) + " golden charm" + (size > 1 ? "s. " : ". ") + 
            capitalize(COMPOSITE_DEAD(all_inventory())) + ".\n";
    }
    return ret;
}

string
charm_generator()
{
    int size;

    if (!(size = sizeof(all_inventory())))
    {
        return "You find no charms.\n";
    }
    
    if (size == 1)
        return "The golden charm on the " + short(this_player()) + 
            " looks like a perfect miniature replica of a weapon.\n";
    return "The golden charms on the " + short(this_player()) + 
        " looks like miniature replicas of the larger version of " + 
        COMPOSITE_DEAD(all_inventory()) + ".\n";
}

string
clasp_generator()
{
    string str;
    int res;
    str = "The golden clasp is used to close the bracelet around " + 
        "a wrist. " ; 
    
    if (!this_player()->query_prop(CLASP_PROP)) 
    {
        this_player()->add_prop(CLASP_PROP, 
            this_player()->resolve_task(TASK_ROUTINE,
                ({ SS_LANGUAGE, TS_INT })));
    }
    
    res = this_player()->query_prop(CLASP_PROP);
    
    if (res > 0)
    {
        str += "The word '" + command_word + 
            "' has been etched into the clasp.\n";
    } else {
        str += "Something has been written on the clasp in an unknown " + 
            "language.\n";
    }
    
    return str;
}


/*
 * Called from an alarm. 
 *
 * It should break all weapons/armours in this container.
 */
static void
break_inv()
{
    object *inv;

    inv = all_inventory();
    inv->add_prop(OBJ_I_BROKEN, 1);
    add_prop(OBJ_I_BROKEN, 1);
}

public void 
enter_env(object ob, object from)
{
    ::enter_env(ob, from);

    if (living(ob))
    {
        if (get_alarm(break_alarm))
        {
            remove_alarm(break_alarm);
        }
    } 
    else 
    {
        if (!get_alarm(break_alarm))
        {
            break_alarm = 
                set_alarm(itof(MAX_CONTAINER_TIME), 0.0, &break_inv());
        }
    }
}

void
leave_env(object from, object to)
{                                                                           
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

int
slide(string str)
{
    object *obs, ob;

    if (environment() != this_player())
        return 0;


    notify_fail("Slide what on what?\n");

    if (!stringp(str))
    {
        return 0;
    }
    
    if (!parse_command(str, this_player(), 
        "[golden] 'bracelet' [on] %i", obs)) 
    {
        return 0;
    }
    
    obs = NORMAL_ACCESS(obs, 0, 0);
    
    if (!sizeof(obs))
    {
        return 0;
    }
    
    if (sizeof(obs) > 1)
    {
        notify_fail("You fail to decide what to slide the " + short() + 
            "around.\n");
        return 0;
    }
    
    if (sizeof(all_inventory()) >= MAX_HOLD ||
        !IS_WEAPON_OBJECT(obs[0]))
    {
        notify_fail("You get a feeling nothing would happen.\n");
        return 0;
    }
    
    ob = obs[0];

    this_object()->remove_me();

    write("You slide your " + short() + " around the "
        + ob->short() + 
        " and " + ob->query_objective() + " suddenly disappears.\n");
    say(QCTNAME(this_player()) + " slides " + 
        "a " + QSHORT(this_object()) + 
        " around " + this_player()->query_possessive() + 
        " " + QSHORT(ob) + " which then disappears.\n");
    
    ob->move(this_object());
    return 1;
}

int
volume_left()
{
    return 100000;
}

public void
grow(object ob)
{
    /* You never know */
    if (!objectp(ob) || environment(ob) != this_object() || 
        !living(environment()))
        return;
    
    set_this_player(environment());
    
    write("The " + ob->short() + " appears in your hands.\n");
    
    ob->move(environment());
    ob->wield_me();

}

public int
communicate(string str)
{
    object *obs;
    string *words;

    if (!query_worn() ||
        (query_worn()->query_race_name() == "kender"))
        return 0;
    
    if (!stringp(str))
        return 0;

    words = explode(str, " ");

    if ((sizeof(words) >= 2) &&
        (words[0] == command_word))
    {
        obs = FIND_STR_IN_OBJECT(implode(words[1..], " "), this_object());
        if (!sizeof(obs) || sizeof(obs) > 1) 
            return 0;
        
        if ((time() - last_use) < USE_INTERVAL)
            return 0;
        last_use = time();
        
        set_alarm(1.0, 0.0, &grow(obs[0]));
    }
    
    if ((sizeof(words) > 1) &&
        ((time() - last_evolve) > EVOLVE_INTERVAL))
    {
        command_word = lower_case(words[random(sizeof(words))]);
        last_evolve = time();
    }
    
    return 0;
}

void
init()
{
    ::init();

    add_action(communicate, "'", 2);
    add_action(communicate, "say");
    add_action(communicate, "mhiss");
    add_action(slide, "slide");
}

public int
prevent_enter()
{
    if (previous_object(-1) == this_object())
        return 0;
    write("You can't " + query_verb() + " things there.\n");
    return 1;
}

public int
prevent_leave()
{
    if (previous_object(-1) == this_object())
        return 0;
    write("You can't " + query_verb() + " things there.\n");
    return 1;
}

void
transport_kender(object who, int back)
{
    if (!objectp(who))
        return;

    if (!back)
    {
        if (query_worn() != who)
            return;
        
        if (!objectp(prison))
        {
            prison = clone_object("/std/room");
            prison->set_short("A very dark and boring room");
            prison->set_long("You find yourself in a very dark place. " + 
                "And very boring.\n");
            prison->add_prop(ROOM_M_NO_TELEPORT, "Something stops the " + 
                "teleportation attempt.\n");
        }
        
        who->move_living("X", prison);
        prison->add_prop(OBJ_S_WIZINFO, "This room is created " + 
            " by " + file_name(this_object()) + " as a prison " + 
            "for kender who wear it. It should be returned to " + 
            file_name(who->query_prop(LIVE_O_LAST_ROOM)) +
            " when it removes it.\n");
        return;
    }
    
    who->move_living("X", who->query_prop(LIVE_O_LAST_ROOM));
    prison->remove_object();
}

mixed
wear(object what)
{
    if (this_player()->query_race_name() == "kender")
    {
        if (!this_player()->query_relaxed_from_combat())
        {
            this_player()->command("$drop bracelet");
            return "You slip and drop the " + short() + ".\n";
        }
        set_alarm(0.2, 0.0, &transport_kender(this_player(), 0));
    }    
    return 0;
    
}

int
remove(object what)
{
    if (this_player()->query_race_name() == "kender")
        set_alarm(0.2, 0.0, &transport_kender(query_worn(), 1));
    return 0;
}
