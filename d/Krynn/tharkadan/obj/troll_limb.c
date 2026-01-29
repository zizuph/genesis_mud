/* Ashlar, 19 Jul 97
 * a limb of a troll, which will grow into a new troll after
 * a short while, unless it is burnt.
 *
 */
inherit "/std/object";
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

#include "/d/Krynn/common/defs.h"
// #include "/d/Ansalon/taman_busuk/neraka/local.h"

object gWeapon = 0;
int gRegenAlarm = 0;
private object *gFail;
static string regen_ob;

#define TROLL_LIMB_BURNT    "_troll_limb_burnt"

/* prototypes*/
public string query_burn_fail();
void set_limb(string limb);

void
create_object()
{
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET,
        "The troll limb twitches and turns so fiercly, " +
        "that you cannot get a hold of it.\n");
    set_limb("right arm");
    add_name("limb");
}

mixed
find_fire_object(object pl)
{
    object *ol;
    int i,sz;

    ol = all_inventory(pl) + ({ E(pl) });
    ol = filter(ol, &->query_prop(OBJ_I_HAS_FIRE));    
    if (sizeof(ol))
        return ol[0];
    return 0;
}

/*
 * Function name: do_burn
 * Description:   The player tries to burn a limb
 * Arguments:	  str - the string describing what he  wants to burn
 * Returns:	  1/0
 */
public int
do_burn(string str)
{
    object *a,fire;
    string str2, vb;

    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n");
    if (!strlen(str))
        return 0;

    if(!(fire = find_fire_object(TP)))
    {
        NF("There is no fire nearby.\n");
        return 0;
    }

    gFail = ({});
    a = CMDPARSE_ONE_ITEM(str, "burn_one_limb", "burn_limb_access");
    if (sizeof(a) > 0)
    {
        str2 = COMPOSITE_DEAD(a);

        if (fire->query_prop(ROOM_I_IS))
        {
            say(QCTNAME(TP) + " throws " + str2 + " into the " +
                "nearby fire.\n");
            write("You throw " + str2 + " into the nearby fire.\n");
        }
        else
        {
            say(QCTNAME(TP) + " burns " + str2 + " with " + HIS(TP) +
                " " + fire->short() + ".\n");
            write("You burn " + str2 + " with your " + fire->short() + 
                ".\n");
        }
        return 1;
    }

    if (sizeof(gFail))
    {
        notify_fail("The " + COMPOSITE_DEAD(gFail) +
            (sizeof(gFail) > 1 ? " are " : " is ") +
            "already burnt.\n");
    }

    return 0;
}

int
burn_limb_access(object ob)
{
    if (objectp(ob))
        return ob->burn_limb_access();
    return 1;
}

int
burn_one_limb(object ob)
{
    if (!ob->burn_limb())
    {
        gFail += ({ ob });
        return 0;
    }
    
    return 1;
}

/* Burnt limbs disappear */
void
decay_limb()
{
    if (living(environment()) || !environment()->query_prop(ROOM_I_IS))
    {
        return;
    }

    tell_room(environment(), "The " + QSHORT(this_object()) + 
        " decays.\n");
    remove_object();
}

int
burn_limb()
{
    
    if (query_prop(TROLL_LIMB_BURNT))
    {
        return 0;
    }

    remove_alarm(gRegenAlarm);    
     
    add_adj("burnt");
    if (gWeapon)
    {
        gWeapon->move(E(TO));
        gWeapon = 0;
    }
    
    set_short("burnt " + query_adj(0) + " " + query_name() + 
        " of a troll");
    set_long("This is the " + short() + ".\n");
    this_object()->add_prop(TROLL_LIMB_BURNT, 1);
    remove_prop(OBJ_M_NO_GET);

    set_alarm(3600.0 * rnd(), 0.0, &decay_limb());
    
    return 1;
}

public string
query_burn_fail()
{
    if (query_prop(TROLL_LIMB_BURNT))
    {
        return "The " + short() + " is already burnt.\n";
    }
    return "You can't burn that.\n";
}

void
init()
{
    ::init();
    add_action(do_burn, "burn");
}

void
set_limb(string limb)
{
    string *l = explode(limb, " ");

    
    
    remove_name("arm");
    remove_adj(({"right","troll"}));

    set_name(l[1]);
    if (l[1] == "leg")
        set_pname("legs");
    set_adj(l[0]);
    add_adj("troll");

    set_short(limb + " of a troll");
    set_long("This is the " + limb + " of a troll.\n");
}

void
set_weapon(object w)
{
    gWeapon = w;
    set_short(query_short() + ", clutching " + LANG_ADDART(w->short()));
    set_long(query_long() + "It is clutching " + LANG_ADDART(w->short()) +
        " in a tight grip.\n");
}

void
do_regen()
{
    object troll;

    setuid();
    seteuid(getuid());

    troll = clone_object(regen_ob);
    if (!objectp(troll))
    {
        log_file("events", file_name(this_object()) + " unable to " +
            "regenerate " + regen_ob + "\n", 50000);
        return;
    }
    
    tell_room(E(TO),"With a ripping and tearing sound, the " + short() +
        " grows into " + QNAME(troll) + "!\n");
    troll->set_arms(gWeapon);
    if(gWeapon)
        gWeapon->move(troll,1);
    troll->move_living("M",E(TO));
    troll->set_regens(0);
    remove_object();
}       

void
set_regen_object(string ob)
{
    regen_ob = ob;
}

void
set_regen(int time)
{
    if (!objectp(regen_ob))
        regen_ob = MASTER_OB(previous_object());
    
    if (!get_alarm(gRegenAlarm))
        gRegenAlarm = set_alarm(itof(time),0.0,do_regen);
}
