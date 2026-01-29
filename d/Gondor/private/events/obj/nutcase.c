inherit "/std/receptacle.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* Global variables */
object gWho;
string gDescriptor = "empty";

/* Prototypes */
public string short_desc();
public string long_desc();

public void
create_container()
{
    set_name("nutcase");
    add_name("case");
    set_adj("wooden");
    set_short(&short_desc());
    set_long(&long_desc());

    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(CONT_I_IN,             1);
    add_prop(CONT_I_TRANSP,         0);
    add_prop(CONT_I_CLOSED,         0);
    add_prop(CONT_I_WEIGHT,       300);
    add_prop(CONT_I_VOLUME,       300);
    add_prop(CONT_I_MAX_WEIGHT, 18000);
    add_prop(CONT_I_MAX_VOLUME,  9000);
    add_prop(OBJ_I_VALUE,          345);
}

public void
set_descriptor(string str)
{
    gDescriptor = str;
}

public string
query_descriptor()
{
    return gDescriptor;
}

public string
short_desc()
{
    return (query_descriptor() + " wooden nutcase");
}

public string
long_desc()
{
    string text;
    switch(query_descriptor())
    {
        case "empty":
            text = "This wooden nutcase smells vaguely of " +
                "nuts and dried fruit. It appears to be made " +
                "for holding trailmix!\n";
            break;
        default:
            text = "This wooden nutcase is " + gDescriptor + 
                ". It appears to grow with its contents!\n";
            break;
    }

    return (text + "Please aid in our quest to make the vengeful " + 
        "wraith, Stern Urya-Yare, into a vegetarian and save the " +
        "elves of Gondor! Fill this nutcase with at LEAST one " +
        "of each ten different gondorian trailmix ingredients, " +
        "and after the span " +
        "of one hour, the biggest nutcase wins!\n");
}

public int
prevent_enter(object ob)
{
    ::prevent_enter();

    if (ob->id("_gondor_trail_mix_"))
    {
        return 0;
    }
    else
    {
        write("Only trail mix should go in here!\n");
        return 1;
    }
}

public void
reset_mix()
{
    gWho = this_object();
}

public void
recalculate_size(object ob, int grow)
{
    int size = (query_prop(OBJ_I_VOLUME) - query_prop(CONT_I_VOLUME));
    string old_desc = short();

    switch(size)
    {
        case 0:
            gDescriptor = "empty";
            break;
        case 1..3:
            gDescriptor = "miniscule";
            break;
        case 4..6:
            gDescriptor = "tiny";
            break;
        case 7..9:
            gDescriptor = "small";
            break;
        case 10..12:
            gDescriptor = "medium";
            break;
        case 13..15:
            gDescriptor = "large";
            break;
        case 16..18:
            gDescriptor = "huge";
            break;
        case 19..21:
            gDescriptor = "jumbo";
            break;
        case 22..24:
            gDescriptor = "bulging";
        case 25..27:
            gDescriptor = "gigantic";
            break;
        default:
            gDescriptor = "close-to-exploding";
            break;
    }

    if (objectp(ob))
    {
        tell_object(ob, "The " + old_desc + " seems to grow a bit " +
            (grow ? "larger" : "smaller") + " into a " + 
            short() + " as you " +
            (grow ? "drop" : "take") + " some trailmix " +
            (grow ? "into" : "from") + " it.\n");
    }

    if (objectp(environment(ob)))
    {
        tell_room(environment(ob), QCTPNAME(ob) + " " + old_desc +
            " seems to " + (grow ? "grow" : "shrink") + " into a " +
            short() + ".\n", ob);
    }

    setuid();
    seteuid(getuid());
    write_file("/d/Gondor/private/events/logs/trailmix", 
        ob->query_name() + ": " + size + ".\n");

}

public void
leave_inv(object ob, object to)
{
    int *alarms = query_alarms();

    ::leave_inv(ob, to);

    if (gWho == to)
    {
        return;
    }


    set_alarm(0.1, 0.0, &recalculate_size(to, 0));

    if (!sizeof(alarms))
    {
        gWho = to;
        set_alarm(0.3, 0.0, reset_mix);
        return;
    }

    gWho = to;
    return;
}
public void
enter_inv(object ob, object from)
{
    int *alarms = query_alarms();

    ::enter_inv(ob, from);

    if (gWho == from)
    {
        return;
    }

    set_alarm(0.1, 0.0, &recalculate_size(from, 1));

    if (!sizeof(alarms))
    {
        gWho = from;
        set_alarm(0.3, 0.0, reset_mix);
        return;
    }

    gWho = from;
    return;
}

