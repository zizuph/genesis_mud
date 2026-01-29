/*
 *  On this device people can see the ranking of best Hin Warriors
 *  It probably is in the guildroom: /d/Shire/common/guild/rooms/hguild.c
 *
 *                                                   Tricky, october 1993
 */
inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/secure/std.h"
#include "shire_defs.h"
#include "defs.h"

#undef DEBUG

/* Variables to save */
mixed *top_few;
string last_month;

/* top_few consist of arrays like ({ "name", guildstat, experience }) */
#define THE_NAME    0
#define GSTAT       1
#define TOTEXP      2

/* The number of top players to display */
#define TOPNR   15

/* Prototypes */
void check_reset();

void
create_object()
{
    set_name("device");
    set_adj(({"ranking", "magical"}));
    set_short("magical ranking device");
    set_pshort("magical ranking devices");
    set_long("@@my_long");

    add_item(({"button", "protrusion", "copper button", "copper protrusion"}),
            "To update your position on the list, you should push the "
          + "button.\n"
          + "Don't you just love these button-operated magical devices?\n");

    add_prop(OBJ_M_NO_GET,"@@my_get");

    restore_object(MASTER);

    check_reset();
}

void
init()
{
    ::init();
    add_action("do_push","push");
    add_action("do_push","press");
#ifdef DEBUG
    add_action("do_delete", "delete");
#endif
}

/*
 * Function name:   check_reset
 * Description:     Reset the list of top players every now and then
 *		    to create some competition. "Every now and then"
 *		    means once a month, in this case.
 */
void
check_reset()
{
    string this_month, time_str;

    /*
     * Hrmmm. This is more complicated than I thought; what if a
     * reboot does not occurr on the right day? I will have to
     * do a more thorough check than simply a date-check...
     */

    time_str = ctime(time());
    /*
     * time_str is now something like "Thu Sep 30 20:45:38 1993",
     * let us examine the month.
     */
    this_month = explode(time_str, " ")[1];

    if (this_month != last_month)
    {
	last_month = this_month;
	top_few = ({ });

	/* And keep the record */
	seteuid(getuid());
	save_object(MASTER);
    }
}

int
my_get()
{
    write("You are struck by a lightning bolt when you try to get the "
        + "magical device.\n");
    say(QCTNAME(this_player()) + " is struck by a lightning bolt for trying "
      + "to steal the magical device.\n");
    return 1;
}

string
my_long()
{
    string str, the_name;
    int i;

    str = break_string("The magical ranking device is made out of wood, "
           + "and looks like a cube with a height of three feet. On the "
           + "left side is a copper protrusion, or button which looks "
           + "like it can be pushed. The top of the device shows a list "
           + "of this month's " + TOPNR
           + " most distinguished and honoured Hin Warriors.\n\n", 70);

    if (sizeof(top_few) == 0)
        str += "Noone has pressed the button yet, this month.\n";

    for (i=0; i < sizeof(top_few); i++)
    {
        the_name = top_few[i][THE_NAME];

        /* Cut off long names that do not fit on one line */
        if (strlen(the_name) > 75)
        {
	    /* Make sure the last character is not a space, because
	       that will mess up things (the gamedriver breaks the string!) */
	    if (the_name[70] == ' ')
               the_name = extract(the_name, 0, 69) + "...";
	    else
               the_name = extract(the_name, 0, 70) + "...";
        }

        str += sprintf("%2d: %75-s\n", i+1, the_name);
    }

    return str + "\n";
}

int
do_push(string str)
{
    string verb, name;
    object tp;
    mixed *newp, *top_new;
    int i;

    verb = query_verb();
    tp = this_player();

    if (!str || (str != "button" && str != "protrusion"))
    {
        notify_fail(capitalize(verb) + " what?\n");
        return 0;
    }


    /* Mortals only! */
    if (tp->query_wiz_level())
    {
        write("Only mortals may push the button. After all... they are\n"
            + "no match for you, are they?\n");
        return 1;
    }


    /* Is this a member of our guild? */
    if (!(tp->test_bit("Shire", 0, 0)))
    {
        write("You " + verb + " the " + str + ", but nothing happens.\n");
        say(QCTNAME(tp) + " pushes the button on the magical "
          + "ranking device, but nothing much happens.\n");
        return 1;
    }

    name = tp->query_name();

    /* Is this a testcharacter? */
    if (extract(name, strlen(name)-2, strlen(name)-1) == "jr")
    {
        write("You " + verb + " the " + str + ", but nothing happens.\n"
            + "The device is not considering testcharacters.\n");
        say(QCTNAME(tp) + " pushes the button on the magical "
          + "ranking device, but nothing much happens.\n");
        return 1;
    }

    write("After you " + verb + " the " + str + " of the ranking device, "
        + "you feel that your inner state is being probed by a magical "
        + "force.\n");
    say(QCTNAME(tp) + " pushes the button of the ranking "
      + "device.\n");
    tell_room(environment(), "A light humming can be heard coming from "
            + "the device.\n");

    /* Check if the person is already listed in the top_few */
    for (i = 0; i < sizeof(top_few); i++)
	if (explode(top_few[i][THE_NAME], " ")[0] == tp->query_name())
	    top_few = exclude_array(top_few, i, i);

    /* Make a new ranking */
    newp = ({ tp->query_name() + " " + tp->query_title(),
              tp->query_base_stat(SS_LAYMAN),
              tp->query_exp() });

    if (sizeof(top_few) == 0)
        top_few = ({ newp });
    else
        top_few += ({ newp });

    /* Sort the new ranking */
    top_new = sort_array(top_few, "less_eq_func", this_object());

    /* Only keep the top <TOPNR> */
    if (sizeof(top_few) > TOPNR)
        top_few = top_new[0..(TOPNR-1)];

    /* And keep the record */
    seteuid(getuid());
    save_object(MASTER);
    return 1;
}

int
less_eq_func(mixed *p1, mixed *p2)
{
    /* First compare guild stats */
    if (p1[GSTAT] < p2[GSTAT])
        return 1;

    if (p1[GSTAT] > p2[GSTAT])
        return -1;

    /*
     * p1[GSTAT] == p2[GSTAT]
     * If guildstats tie, look at total experience...
     */
    return p1[TOTEXP] <= p2[TOTEXP];
}

#ifdef DEBUG
int
do_delete(string str)
{
    int i;

    if (!str)
	return 0;

    sscanf(str, "%d", i);
    i--;
    top_few = exclude_array(top_few, i, i);

    /* And keep the record */
    seteuid(getuid());
    save_object(MASTER);

    write("Deleted.\n");
    return 1;
}
#endif
