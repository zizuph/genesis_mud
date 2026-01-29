
/* 	
    Helm with long straight horns, for the tough krougs 

    coder(s):   Maniac

    22/3/96        plural corrected        Maniac
    20/2/96         Created                Maniac
    05/8/96         Emotes added           Khail
    10/6/11         Bad inherit removed    Lavellan

*/

#pragma save_binary

inherit "/std/armour";
//inherit "/cmd/std/command_driver";
inherit "/lib/commands";
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>

string *colours = ({ "blue", "red", "green", "black", "purple",
                     "white", "silver", "golden", "orange" });
string my_colour;
string horn_short;

void
set_up_desc(string c) 
{
    if (stringp(my_colour))
        remove_adj(my_colour);

    my_colour = c;
    add_adj(my_colour);

    horn_short = "long, straight " + my_colour + " horns";

    set_short("helm with two long straight " + my_colour + " horns");
    set_pshort("helms with two long straight " + my_colour + " horns");

    set_long("A steel helm with two long, straight " + my_colour + 
          " horns sticking out " +   
         "of the top. It looks just the right thing to match " + 
         "a big ego. Hmm, for that matter, those horns give you some " +
         "ideas. You could probably 'hornpoke [who]', 'hornturn <who>', " +
         "'hornnod' and 'hornshake' for a laugh or two.\n" +
         "(Reference: horned, long-horned, straight-horned.)\n");
}

void
create_armour()
{
    string c;

    set_name("helmet");
    add_name("helm");
    set_adj(({"horned", "long-horned", "straight-horned"}));

    c = colours[random(sizeof(colours))];

    set_up_desc(c);

    set_ac(27);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
}


string
query_recover()
{
  string rec;
  rec = MASTER + ":";
  rec += "#a#";
  rec += my_colour;
  rec += "#myend";
  rec += query_arm_recover();
  return rec;
}


void
init_recover(string arg)
{
  string foobar, c;

  sscanf(arg, "%s#a#%s#myend%s",
                foobar, c, foobar);
  set_up_desc(c);
  init_arm_recover(arg);
}


public int
hornnod(string str)
{
    string *how;
    object tp;

    if (!query_worn() || query_worn() != this_player())
        return 0;

    tp = this_player();
    how = parse_adverb(str, "wildly", 0);

    write("You nod " + how[1] + ", the " + horn_short + " of your helm " +
        "bobbing wildly, pulling it somewhat lop-sided on your head. " +
        "Blushing a bit, you hastily rearrange it.\n");
    say(QCTNAME(tp) + " nods " + how[1] + ", the " + horn_short + " of " +
        tp->query_possessive() + " helm bobbing wildly, " +
        "pulling it somewhat lop-sided on " + tp->query_possessive() +
        " head. Blushing a bit, " + QTNAME(tp) + " hastily rearranges " +
        "it back into its proper place.\n");
    return 1;
}

public int
hornshake(string str)
{
    string *how;
    object tp;

    if (!query_worn() || query_worn() != this_player())
        return 0;

    tp = this_player();
    how = parse_adverb(str, "wildly", 0);

    write("You shake your head " + how[1] + ", and suddenly everything " +
        "turns black!\n");
    say(QCTNAME(tp) + " shakes " + tp->query_possessive() + " head " +
        how[1] + ", and much to your amusement, the " + horn_short + " of " +
        tp->query_possessive() + " helm makes it spin around " +
        "sideways, with " + tp->query_possessive() + " ear sticking out " +
        "where " + tp->query_possessive() + " face should be!\n");
    tp->command("shout Gads! I've been struck blind!");
    write("Suddenly, you realize your helm has turned itself sideways " +
        "from your motion, which explains the sudden darkness. Sheepishly, "+
        "you tug it back around so you can see out of it again.\n");
    say(QCTNAME(tp) + " seems to realize what's happened, and sheepishly " +
        "repositions it so " + tp->query_pronoun() + " can see again.\n");
    return 1;
}

public int
hornturn(string str)
{
    object *others;
    object tp;
    object target;
    if (!query_worn() || query_worn() != this_player())
        return 0;

    tp = this_player();
    if (!str || !strlen(str))
    {
        notify_fail("You whip your head around, but luckily nobody's " +
            "around to be hurt by the flailing horns. Darn!\n");
        others = FILTER_OTHER_LIVE(all_inventory(environment(tp)));
        if (!sizeof(others))
            return 0;
        others = FILTER_CAN_SEE(others, tp);
        if (!sizeof(others))
            return 0;

        target = others[random(sizeof(others))];
    }
    else
    {
        others = parse_this(str, "%l");
        if (!sizeof(others))
        {
            notify_fail("Turn into who with your horns?\n");
            return 0;
        }
        if (sizeof(others) > 1)
        {
            notify_fail("You'd never get that many people with the horns " +
                "at once! Get serious.\n");
            return 0;
        }
        target = others[0];
    }

    if ((target->query_stat(SS_DEX) + random(30)) > 
        (tp->query_stat(SS_DEX) + random(30)))
    {
        write("You quickly jerk your head around, the " + horn_short + 
            " of your helm swinging " +
            "wildly towards " + target->query_the_name(tp) + ", but " +
            target->query_pronoun() + "'s faster than you, and dodges " +
            "nimbly out of the way.\n");
        tell_room(environment(tp), QCTNAME(tp) + " quickly jerks " +
            tp->query_possessive() + " " +
            "head around, swinging the " + horn_short + " on " +
            tp->query_possessive() + " helm " +
            "dangerously close to " + QTNAME(target) + "'s head, but " +
            target->query_pronoun() + " dodges nimbly out of the way " +
            "at the last moment.\n", ({tp, target}));
        tell_object(target, tp->query_The_name(target) + " quickly jerks " +
            tp->query_possessive() + " head around, the " + horn_short +
            " on " + tp->query_possessive() + " helm swinging straight " +
            "at you, but you nimbly step aside and avoid them at the last " +
            "moment.\n");
        return 1;
    }
    write("You quickly jerk your head around, whacking " +
        target->query_the_name(tp) +
        " rudely with the " + horn_short + " on your helm.\n");
    tell_room(environment(tp), QCTNAME(tp) + " quickly jerks " +
        tp->query_possessive() + " " +
        "head around, whacking " + QTNAME(target) + " rudely with the " +
        horn_short + " on " + tp->query_possessive() + " helm.\n",
        ({tp, target}));
    tell_object(target, tp->query_The_name(target) + " quickly jerks " +
        tp->query_possessive() + " head around, whacking you rudely " +
        "with the " + horn_short + " on " + tp->query_possessive() +
        " helm.\n");
    tp->command("oops");
    return 1;
}

public int
hornpoke(string str)
{
    string *how;
    object *arr,
           tp,
           target;

    if (!query_worn() || query_worn() != this_player())
        return 0;

    how = parse_adverb_with_space(str, "annoyingly", 0);
    str = how[0];
    notify_fail("Hornpoke who?\n");
    if (!str || !strlen(str))
        return 0;
    arr = parse_this(str, "%l");
    if (!sizeof(arr))
        return 0;

    if (sizeof(arr) > 1)
    {
        notify_fail("You can't poke more than one person, the horns " +
            "aren't _that_ impressive.\n");
        return 0;
    }

    tp = this_player();
    write("You lower your head and" + how[1] + " give " +
        arr[0]->query_the_name(tp) +
        " a poke with the " + horn_short + " of your helm. Now " +
        "_that's_ entertainment!\n");
    tell_object(arr[0], tp->query_The_name(arr[0]) + " lowers " +
        tp->query_possessive() + " head and" + how[1] + " gives you a poke " +
        "with the " + horn_short + " of " + tp->query_possessive() + 
        " helm. Ow! Are you gonna let " + tp->query_objective() + " " +
        "get away with that?\n");
    tell_room(environment(tp), QCTNAME(tp) + " lowers " +
        tp->query_possessive() + " head and" + how[1] + " gives " +
        QTNAME(arr[0]) + " " +
       "a poke with the " + horn_short + " of " + tp->query_possessive() +
        " helm.\n", ({tp, arr[0]}));
    return 1;
}


public void
init()
{
    ::init();
    add_action(hornturn, "hornturn");
    add_action(hornpoke, "hornpoke");
    add_action(hornnod, "hornnod");
    add_action(hornshake, "hornshake");
}
