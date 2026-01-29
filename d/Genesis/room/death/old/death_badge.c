/* death_badge.c */
/* Mrpr 910117 */
/* Tintin 911031 */

#include <stdproperties.h>

#define FRONT "I'm reincarnated"
#define BACK ", so hands off Death!!"

#define DESCR ""

inherit "/std/object";

string descr;
int dnr;

/*
 * Prototypes
 */
void set_dnr(int n);

/*
 * Function name: reset
 * Description:   Reset the badge.
 */
void
create_object()
{
    set_name("death_badge");
    set_name("deathbadge");
    set_name("badge");
    set_dnr(1);
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 0); /* 0 copper */
    add_prop(OBJ_I_NO_DROP, 1); /* Call drop when property tested */

    set_short("jet black badge");
    set_adj("jet");
    add_adj("black");
}

/*
 * Function name: query_dnr
 * Description:   Return the number of times dead this session.
 */
int
query_dnr()
{
    return dnr;
}

/*
 * Function name: set_dnr
 * Description:   set the number of times dead this session.
 */
void
set_dnr(int n)
{
    dnr = n;
    descr = FRONT;
    if (dnr == 1)
	descr += BACK;
    else if (dnr == 2)
	descr += " twice" + BACK;
    else
	if (dnr != 1)
	    descr += " " + n + " times" + BACK;
    set_long("A jet black badge, made in some hard stone. Inset in the hard surface is\n" +
	     "a glowing inscription: " + descr + "\n");
}

void
start_reincarnate(object ob)
{
    call_out("do_reincarnate", 1, ob);
}

void
do_reincarnate(object ob)
{
    if (ob)
	ob->reincarnate();
}
