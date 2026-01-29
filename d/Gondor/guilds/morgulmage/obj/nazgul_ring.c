#include <wa_types.h>
#include "../morgulmage.h"
#include <language.h>
#include <stdproperties.h>

inherit "/std/object";

mixed ring_information;

void create_object() 
{
    set_name(MORGUL_MORGUL_RING);
    add_name("ring");
    set_adj(({"heavy", "gold"}));
    set_short("heavy gold ring");
    set_long("Imbued with a weightiness beyond its size, this thick band of perfect curves of gold is unadorned.\n");
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}

private string remove_str(string needle, string haystack) 
{
    return implode(explode(haystack, needle), "");
}

string get_armour_underneath_ring() 
{
    object env = environment(this_object());
    object armour = env->query_armour(TS_RHAND);
    if (!objectp(armour)) return "";
    
    string armour_short = armour->short();
    armour_short = remove_str("pair of ", armour_short);
    if (armour_short[-2..] == "es") return armour_short[0..-3] + "e";
    if (armour_short[-1..] == "s") return armour_short[0..-2];
    return armour_short;
}

void clear_ring_information()
{
    ring_information = ([
        "name" : 0,
        "short" : "heavy gold",
        "long" : "Imbued with a weightiness beyond its size, this thick "
          + "band of perfect curves of gold is unadorned."
    ]);
}

void setup_ring(object ob = environment(this_object()))
{
    ring_information = MORGUL_MASTER->query_ring_information(ob);
    if (!ring_information) clear_ring_information();
    
    set_adj(explode(ring_information["short"], " "));
    set_short(ring_information["short"] + " ring");
    set_long(ring_information["long"] + "\n");
    
    if(ring_information["name"]) {
        add_name(lower_case(ring_information["name"]));
        set_long(ring_information["long"] + "\n"
            + "The ring is named " + ring_information["name"] + ".\n");
    }
}

void enter_env(object ob, object from)
{
    setup_ring(ob);
    ::enter_inv(ob, from);
}

void save_ring_information()
{
    object mage = environment(this_object());
    if (!objectp(mage) || !IS_MEMBER(mage)) return;    
    MORGUL_MASTER->set_ring_information(mage, ring_information);
}

int ringwipe_cmd(string args)
{
    if(args && args != "")
    {
        notify_fail("Ringwipe does not take arguments.\n");
        return 0;
    }
    
    if (!this_player()->query_prop("_confirmed_ringwipe"))
    {
        write("Execute this command again to change the appearance " 
          + "of your ring to the original.\n");
        this_player()->add_prop("_confirmed_ringwipe", 1);
        return 1;
    }
    
    this_player()->remove_prop("_confirmed_ringwipe");
    clear_ring_information();
    save_ring_information();
    setup_ring();
    
    write("Suddenly your ring turns into a " + short() + "\n");
    return 1;
}

int ringname_cmd(string args)
{
    if(!args || args == "") 
    {
        notify_fail("Name your ring how?\n");
        return 0;
    }
    
    ring_information["name"] = args;
    save_ring_information();
    setup_ring();
    
    write("You name your ring " + args + ".\n");
    return 1;
}

int ringshort_cmd(string args)
{
    if(!args || args == "") 
    {
        notify_fail("Change the short description of your ring to?\n");
        return 0;
    }
    
    ring_information["short"] = args;
    save_ring_information();
    setup_ring();
    
    write("You ring now looks like " + LANG_ADDART(short()) + ".\n");
    return 1;
}

int ringlong_cmd(string args)
{
    if(!args || args == "") 
    {
        notify_fail("Change the long description of your ring to?\n");
        return 0;
    }
    
    ring_information["long"] = args;
    save_ring_information();
    setup_ring();
    
    write("You ring now looks like:\n" + long());
    return 1;
}

void init()
{
    ::init();
    add_action(ringwipe_cmd, "ringwipe");
    add_action(ringname_cmd, "ringname");
    add_action(ringshort_cmd, "ringshort");
    add_action(ringlong_cmd, "ringlong");
    
}
