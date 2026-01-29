/* Ashlar, 1 Jul 97
   The incredible gnomish dyeing machine */

inherit "/std/object";

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <ss_types.h>
#include <files.h>

#define CAN_ID_MACHINE(x)   ( (x)->query_guild_member("Inventors") || \
    (((x)->query_stat(SS_WIS) + (x)->query_stat(SS_INT)) > 200) )

#define ONE_OF(x)   ((x)[random(sizeof(x))])

#define P_BEGIN     1
#define P_FINISHED  100

#define NO_OPERATE  (stringp(no_operate) && !(TP->query_npc()))

string *colours =
    ({ "white",
       "red",
       "blue",
       "brown",
       "yellow",
       "green",
       "black",
       "purple",
       "violet",
       "grey",
       "orange",
       "silver",
       "golden",
       });

string *types =
    ({ "stripes",
       "dots",
       "wavy lines",
       "stars",
       "dragons"
       });

mapping type_valve =
    ([ "" : 4,
       "stripes" : 2,
       "dots" : 3,
       "wavy lines" : 2,
       "squiggles" : 1
    ]);

string *lever_states = ({ "up", "down" });
string *valve_states = ({ "fully closed", "almost closed",
    "halfway open", "almost open", "fully open" });

string *rows = ({ ONE_OF(colours), ONE_OF(colours)});
string type = ONE_OF(types);

int lever_state;
int heat_state;
int valve_state;
int in_production;
object scarf;

mixed no_operate;

void
create_object()
{
    set_name("machine");
    set_adj("strange");
    add_adj("gnomish");
    add_adj("dyeing");

    set_short("@@my_short@@");
    set_long("@@my_long@@");
    
    lever_state     = 0;
    heat_state      = 0;
    valve_state     = 0;
    in_production   = 0;

    no_operate      = "You are not allowed to operate the machine";

    add_prop(OBJ_I_WEIGHT, 450000);
    add_prop(OBJ_I_VOLUME, 60000);
    add_prop(OBJ_M_NO_GET, "The machine is bolted to the floor.\n");

    add_item(({"containers","cylindrical containers","container",
        "cylindrical container"}),
        "@@exa_containers@@");
    add_item(({"pipes","copper pipes","pipe","copper pipe"}),
        "The copper pipes lead from the containers into the interior " +
        "of the machine. Beneath the pipes are two rows of buttons.\n");
    add_item(({"rows","rows of buttons","buttons"}),
        "@@exa_buttons@@");
    add_item(({"knob","large knob"}),"@@exa_knob@@");
    add_item(({"lever"}),"@@exa_lever@@");
    add_cmd_item(({"lever"}),
        ({"push","pull"}),
        ({"@@do_push_lever@@", "@@do_pull_lever@@"}));
    add_item(({"slit","wide slit"}),"The slit is labelled 'INPUT'.\n");
    add_item(({"large pipe"}),"The large pipe on the side of the machine " +
        "opens up at the end, and there is a valve placed halfway up the " +
        "pipe.\n");
    add_item(({"valve","valve on pipe","valve on large pipe"}),
        "@@exa_valve@@");
    add_cmd_item(({"valve","valve on pipe","valve on large pipe"}),
        ({"open","close"}),
        ({"@@do_open_valve@@", "@@do_close_valve@@"}));
    add_item(({"hatch"}),"@@exa_hatch@@");
    add_item(({"handles","bellows"}),"The handles control a bellows built " +
        "into the machine.\n");
    add_cmd_item(({"handles","bellows"}),({"pump"}),
        ({"@@do_pump@@"}));

}

string
exa_hatch()
{
    string s;

    s = "The hatch is labelled 'OUTPUT'. ";

    if (objectp(scarf) && (in_production == P_FINISHED))
        s += "\nThe hatch contains " + LANG_ADDART(scarf->short()) + ", " +
            "which you can retrieve. ";
    else
        s += "\nThe hatch is empty. ";

    return s + "\n";
}

string
exa_valve()
{
    string s;

    s = "The valve seems to be some sort of outlet for steam. It can " +
        "be opened and closed in small steps. ";

    s += "\nCurrently, the valve is " + valve_states[valve_state] + ".";

    return s + "\n";
}

string
exa_lever()
{
    string s;

    s = "The lever can be pushed up and pulled down, and is " +
        "denoted 'MAIN LEVER'. ";

    if (lever_state)
        s += "\nThe lever is pulled down. ";
    else
        s += "\nThe lever is pushed up. ";

    return s + "\n";
}

string
exa_knob()
{
    string s;

    s = "The large knob can be turned to point at " + LANG_WNUM(sizeof(types)) +
        " symbols, and also to the far left, the text 'OFF'. The " +
        "symbols are " + COMPOSITE_WORDS(types) + ".";

    if (type == "")
        s += "\nAt the moment, the knob is in the 'OFF' position.";
    else
        s += "\nThe knob is turned to point at the " + type + ".";

    return s + "\n";
}

string
exa_buttons()
{
    string s;

    s = "There are two rows of buttons, each containing " +
        LANG_WNUM(sizeof(colours)) + " buttons. Each button in a row " +
        "is painted in an unique colour. The colours are " +
        COMPOSITE_WORDS(colours) + ". ";
    s += "\nIn the first row the " + rows[0] + " button is pressed.";
    s += "\nIn the second row the " + rows[1] + " button is pressed.";

    return s + "\n";
}
        

string
exa_containers()
{
    return "There are " + LANG_WNUM(sizeof(colours)) + " containers, " +
        "each connected to the machine via a copper pipe.\n";
}

string
my_short()
{
    if (CAN_ID_MACHINE(TP))
        return "gnomish dyeing machine";
    else
        return "strange machine";
}

string
my_long()
{
    string s;

    s = "The machine is quite large";
    if (CAN_ID_MACHINE(TP))
        s += ", quite obviously used to dye cloths in different colours. ";
    else
        s += ", and you cannot immediately fathom its purpose. ";
    s += "A number of cylindrical containers rest on the top of the machine, " +
        "and copper pipes lead into the machine. Beneath the pipes are two " +
        "rows of coloured buttons. A large knob is beneath the buttons, and " +
        "a lever is to the side of the knob, while to other side of the " +
        "buttons there is a wide slit. On the right side of the machine " +
        "is a large pipe with a valve, and beneath it is a hatch. Near the " +
        "floor are the handles to a bellows which is built into the machine. ";

    if (in_production)
        s += "The machine is creaking and groaning. ";
    else if (heat_state)
        s += "The machine is shivering slightly. ";

    return s + "\n";
}

string
do_open_valve()
{
    if (NO_OPERATE)
    {
        write(no_operate + "\n");
        return "";
    }
    
    if (valve_state == 4)
        return "The valve will not open further.\n";
    write("You open the valve a bit and it is now " +
        valve_states[++valve_state] + ".\n");
    COMMAND_DRIVER->allbb(" opens a valve a bit on the machine.");
    return "";
}

string
do_close_valve()
{
    if (NO_OPERATE)
    {
        write(no_operate + "\n");
        return "";
    }
    
    if (valve_state == 0)
        return "The valve will not close further.\n";
    write("You close the valve a bit and it is now " +
        valve_states[--valve_state] + ".\n");
    COMMAND_DRIVER->allbb(" close a valve a bit on the machine.");
    return "";
}

string
do_pump()
{
    if (NO_OPERATE)
    {
        write(no_operate + "\n");
        return "";
    }
    
    write("You pump the bellows and you hear a fire roar within the " +
        "machine.\n");
    COMMAND_DRIVER->allbb(" pumps the bellows.");
    heat_state = 1;
    return "";
}

string
do_push_lever()
{
    if (NO_OPERATE)
    {
        write(no_operate + "\n");
        return "";
    }
    /* push the lever up (state 0) */
    if (!lever_state)
        return "The lever is already pushed all the way up.\n";
    write("You push the lever up.\n");
    COMMAND_DRIVER->allbb(" pushes a lever on the machine.");
    lever_state = 0;
    return "";
}

string
do_pull_lever()
{
    if (NO_OPERATE)
    {
        write(no_operate + "\n");
        return "";
    }
    /* pull the lever down (state 1) */
    if (lever_state)
        return "The lever is already pulled all the way down.\n";
    write("You pull the lever down.\n");
    COMMAND_DRIVER->allbb(" pulls a lever on the machine.");
    lever_state = 1;
    return "";
}

/* press <a button> */
int
do_press(string str)
{
    int row;
    string col;
    string rd;
    string vb = query_verb();

    NF(C(vb) + " what?\n");
    if (!stringp(str) || (str == ""))
        return 0;

    if (sscanf(str,"first %s button",col))
        row = 0;
    else if(sscanf(str,"second %s button",col))
        row = 1;
    else if(sscanf(str,"%s button",col))
        row = 0;
    else
        return 0;

    if (member_array(col,colours) == -1)
    {
        NF("There is no " + col + " button to " + vb + ".\n");
        return 0;
    }

    rd = ({ "first", "second" })[row];

    if (NO_OPERATE)
    {
        write(no_operate + "\n");
        return 1;
    }
    if (rows[row] == col)
    {
        write("You " + vb + " the " + col + " button in the " + rd + " row, " +
            "but nothing happens since the button was already pressed.\n");
        COMMAND_DRIVER->allbb(" " + vb + "es a button on the machine.");
        return 1;
    }
    else
    {
        write("You " + vb + " the " + col + " button in the " + rd + " row, " +
            "and the " + rows[row] + " button pops out with a click.\n");
        COMMAND_DRIVER->allbb(" " + vb + "es a button on the machine.");
        rows[row] = col;
        return 1;
    }
}

int
do_turn(string str)
{
    string l;
    int i = 0;

    NF("Turn what?\n");
    if (!stringp(str) || (str == ""))
        return 0;

    if (sscanf(str,"knob to %s",l))
        i = 1;
    else if(sscanf(str,"large knob to %s",l))
        i = 2;
    else if(sscanf(str,"knob %s",l))
        i = 3;
    else if(sscanf(str,"large knob %s",l))
        i = 4;
    else
        return 0;

    l = lower_case(l);
    if ((l == "off") || (member_array(l,types) != -1))
    {
        if (NO_OPERATE)
        {
            write(no_operate + "\n");
            return 1;
        }
    
        write("You turn the large knob to '" + l + "'.\n");
        COMMAND_DRIVER->allbb(" turns a knob on the machine.");
        if (l == "off")
            type = "";
        else
            type = l;
        return 1;
    }
    else
    {
        NF("There is no such possible setting for the knob.\n");
        return 0;
    }
}
    
void
init()
{
    ::init();

    add_action(do_press,"press");
    add_action(do_press,"push");
    add_action(do_turn,"turn");
    //add_action(do_insert,"insert");
}

void
set_no_operate(mixed operate)
{
    no_operate = operate;
}

mixed
query_no_operate()
{
    return no_operate;
}

string *
query_colours()
{
    return colours;
}

string *
query_types()
{
    return types;
}
