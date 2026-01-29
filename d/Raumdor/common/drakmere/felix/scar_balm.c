/*
 * - scar_balm.c
 *
 * This object will allow a player to remove one of their scars.
 * It's a delayed removal, not instantaneous.
 *
 *    Coded by Lucius@Genesis.
 * Inspired by Maeve@Genesis.
 */
#pragma no_inherit
#pragma no_shadow
#pragma strict_types

inherit "/std/object";

#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#define DELAY 10.0
#define COUNT 6

private int cnt, scar, alarm;
private string loc, *rem_msg = ({
   "Your skin tingles as the balm works its way further into "+
     "your %s.\n",
   "The skin about your %s grows warmer as the balm works its "+
     "healing.\n",
   "A burning and itching sensation flows through the skin around "+
     "the scar on your %s.\n",
   });


public void
setup_extra(string *extra, object who)
{
    if (!sizeof(extra))
	return;

    remove_item("jar");
    add_adj(extra[0]);
    set_short(0);

    add_item("jar", "A glass jar with a glowing "+ extra[0] +
	" substance inside.\n");
    set_long("The jar hosting the balm feels hot to the touch, though "+
        "not hot enough to burn your hands. Inside "+ LANG_ADDART(extra[0]) +
        " substance glows softly. Around the bottle an elegant label has "+
	"been attached with flowing script.\n");
}

public string
command_read(int more)
{
    return "The label reads: \n"+
        "\tThis is a balm used explicitly as a topical solution\n"+
        "\tfor removing scars. Do not ingest! To use this balm,\n"+ 
        "\tsimply 'rub' or 'apply' the balm onto the scar you wish \n"+
        "\tremoved.\n";
}

static void
create_object()
{
    set_name("balm");
    add_name("__scar_removal_balm");

    set_adj(({ "glowing", }));
    set_long("The jar hosting the balm feels hot to the touch, though "+
        "not hot enough to burn your hands. Inside a substance "+
        "glows softly. Around the bottle an elegant label has been attached "+
        "with flowing script.\n");
    add_item("jar", "A glass jar with a glowing substance inside.\n");
    add_item("label", command_read);
    add_cmd_item(({"label"}), ({"read"}), ({ command_read }));
        

    add_prop(OBJ_M_NO_SELL,   1);
    add_prop(OBJ_M_NO_BUY,    1);
    add_prop(OBJ_I_WEIGHT,  500);
    add_prop(OBJ_I_VOLUME,  500);
    add_prop(OBJ_I_VALUE, 50000);
}

private void
remove_scar()
{
    object old_tp;

    if (++cnt < COUNT)
    {
        tell_object(environment(), sprintf(one_of_list(rem_msg), loc));
        return;
    }

    remove_alarm(alarm);
    alarm  = 0;
    old_tp = this_player();
    set_this_player(environment());

    write("The tingling fades away to nothingness and you feel a "+
        "smoothness on your "+ loc +" where once you had a scar.\n");
    say("You suddenly notice a smoothness to "+ QTPNAME(this_player()) +
	" "+ loc +" where once "+ this_player()->query_pronoun() +
	" had a scar.\n");

    environment()->set_scar(this_player()->query_scar() ^ scar);
    set_this_player(old_tp);
    remove_object();
}

public int
f_apply(string str)
{
    int i, idx, scars;
    string verb = query_verb();

    if (alarm)
	return 0;

    if (!strlen(str) || !parse_command(str, ({}), 
	    "[the] 'balm' [onto] / [into] [the] / [my] %s", loc))
    {
        notify_fail(capitalize(verb) +" the balm where?\n");
        return 0;
    }

    if(!(scars = this_player()->query_scar()))
    {
        write("You don't have any scars to "+ verb +" the balm onto.\n");
        return 1;
    }

    if ((idx = member_array(loc, F_SCAR_DESCS)) == -1)
    {
        write("That is no such location for a scar.\n");
        return 1;
    }

    i = -1; scar = 1;
    while(i++ < idx)
    {
        if ((i == idx) && (scars & scar))
        {
            alarm = set_alarm(DELAY, DELAY, remove_scar);
            break;
        }
        scar *= 2;
    }

    if (!alarm)
    {
        write("You don't appear to have any scars in that location.\n");
    }
    else
    {
        write("You "+ verb +" the "+ short() +" onto your "+ loc +".\n");
	say(QCTNAME(this_player()) + " "+ verb +"s the "+ short() +
	    " onto "+ this_player()->query_possessive() +" "+ loc +".\n");
    }

    set_no_show();
    return 1;
}

public void
init()
{
    ::init();
    add_action(f_apply, "apply");
    add_action(f_apply, "rub");
}

public void
remove_object()
{
    if (alarm)
        remove_alarm(alarm);
    ::remove_object();
}
