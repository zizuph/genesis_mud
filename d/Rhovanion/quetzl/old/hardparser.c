#include <cmdparse.h>
 
#define SEQUENCE ({ "Can this emote be seen in the dark?", \
    "What is the default adverb?  (NO for no adverb possible)", \
    "Can this be targeted? (yes, no, or must)", \
    "Can the target see this emote in the dark?", \
    "What should I see when I target?", \
    "What should my target see?", \
    "What should others see when I target?", \
    "Which of the following ways is this emote performed?\n"  + \
    "1) smile (happily) at bob\n" + \
    "2) thank bob (gratefully) - ?", \
    "What should I see when I do not target?", \
    "What should others see when I do not target?", \
    "What should I see when I mistype?" })
 
#define SPECIAL_CHARS ({ "#all2act#", "#all#", "#default#", "#trails#", \
    "#emote#", "#fail#", "#parse#", "#bb#", "#btb#", "#write#", "#actor#" })
 
#define CODER "/d/Cirath/vladimir/hardcoder"
 
static string *e;
static int vis,
           options,
           done;
 
static int
contains_specials(string arg)
{
    int i;
    string s1, s2;
    i = sizeof(SPECIAL_CHARS);
    while(i--)
        if (sscanf(arg, "%s" + SPECIAL_CHARS[i] + "%s", s1, s2) == 2)
            return 1;
}
 
static int
next_step(int last)
{
    switch(last)
    {
        case 0: return 1;
        case 1: return 2;
        case 2: if (options & 6) return 3; return 8;
        case 3: return 4;
        case 4: return 5;
        case 5: return 6;
        case 6: return 7;
        case 7: if (options & 2) return 8; return 10;
        case 8: return 9;
       case 9: return 10;
        case 10: return -1;
    }
}
 
static int
yes(string arg, int which)
{
    if (arg == "yes" || arg == "y")
        vis |= which;
    else
        if (arg != "no" && arg != "n")
            return 0;
    return 1;
}
 
static int
adv_change(string arg)
{
    string *str;
    if (arg == "NO")
    {
        e[2] = "";
        return 1;
    }
    str = COMMAND_DRIVER->parse_adverb(arg, "happily", 0);
    if (strlen(str[0]))
        return 0;
    options |= 1;
    e[2] = arg;
    return 1;
}
 
static int
change_options(string arg)
{
    if (arg == "yes" || arg == "y")
        options |= 2;
    else
        if (arg == "must" || arg == "m")
            options |= 4;
        else
            if (arg != "no" && arg != "n")
                return 0;
    return 1;
}
 
static int
check_for_targ(string arg)
{
    if (sizeof(explode(arg, "#targ#")) != 2)
        return 0;
    return 1;
}
 
public void
hand_set_parse(string arg, int i)
{
    e[4] = arg;
    e[3] = sprintf("%d", i);
}
 
static int
default_parse(string arg)
{
    if (arg == "1")
    {
        e[4] = "[at] / [to] / [toward] [the] %l";
        e[3] = "0";
    }
    else
        if (arg == "2")
        {
            e[4] = "[the] %l";
            e[3] = "1";
        }
        else
            return 0;
    return 1;
}
 
static int
contains_targ(string arg)
{
    return sizeof(explode(arg, "#targ#")) > 1;
}
 
static int
contains_adv(string arg)
{
    return sizeof(explode(arg, "#adv#")) > 1;
}
 
static int
convert_arg(string arg, int i)
{
    if (!strlen(arg))
        return 0;
    if (contains_specials(arg))
        return 0;
    if (i != 4 && i != 6 && contains_targ(arg))
        return 0;
    if (!(options & 1) && contains_adv(arg))
        return 0;
    switch(i)
    {
        case 0: if (!yes(arg, 1)) return 0; return 1;
        case 1: if (!adv_change(arg)) return 0; return 1;
        case 2: if (!change_options(arg)) return 0; return 1;
        case 3: if (!yes(arg, 2)) return 0; return 1;
        case 4: if (!check_for_targ(arg)) return 0; e[5] = arg; return 1;
        case 5: e[7] = arg; return 1;
        case 6: if (!check_for_targ(arg)) return 0; e[6] = arg; return 1;
        case 7: if (!default_parse(arg)) return 0; return 1;
        case 8: e[8] = arg; return 1;
        case 9: e[9] = arg; return 1;
        case 10: e[1] = arg; return 1;
        default: return 1;
    }
}
 
static int
abort()
{
    e = ({});
    vis = 0;
    options = 0;
    done = 0;
    return 1;
}
 
public void
finished_hook()
{
    write("You finish your emote.\nNow name it.\n");
}
 
static void
run_sequence(string arg, int i)
{
    if (arg == "~q")
    {
        abort();
        write("You abort making an emote.\n");
        return;
    }
    if (!convert_arg(arg, i))
    {
        write(SEQUENCE[i] + " ");
        input_to("run_sequence", 0, i);
        return;
    }
    i = next_step(i);
    if (i == -1)
    {
        finished_hook();
        done = 1;
        return;
    }
    write(SEQUENCE[i] + " ");
    input_to("run_sequence", 0, i);
    return;
}
 
public int
begin(string arg)
{
    notify_fail(capitalize(query_verb()) + " what?\n");
    if (strlen(arg))
        return 0;
    e = allocate(10);
    done = 0;
    options = 0;
    write(SEQUENCE[0] + " ");
    input_to("run_sequence", 0, 0);
    return 1;
}
 
public void
change_name_hook(string arg)
{
    write("You change the name to " + arg + ".\n");
}
 
public int
name(string arg)
{
    notify_fail("You must specify a name.\n");
    if (!strlen(arg))
        return 0;
    notify_fail("You can't name it until you make it.\n");
    if (!done)
        return 0;
    e[0] = arg;
    change_name_hook(arg);
    return 1;
}
 
public void
forward_hook()
{
    write("You forward your emote.\n");
}
 
public void
not_done_hook()
{
    notify_fail("The emote must be finished and named before it can " +
        "be forwarded.\n");
}
 
public int
forward(string arg)
{
    string emote;
    notify_fail(capitalize(query_verb()) + " what?\n");
    if (strlen(arg))
        return 0;
    not_done_hook();
    if (!done)
        return 0;
    forward_hook();
    CODER->write_emote(options, e, vis);
    return 1;
}
