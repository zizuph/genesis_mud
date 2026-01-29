/*
 *  /d/Gondor/morgul/city/mm_stables/obj/rider_object.c
 *
 *  This file contains actions/emotes for the rider of a steed
 *  from the Stables of Minas Morgul.
 *
 *  Deagol, October 2002
 */

inherit "/d/Genesis/steed/new/rider_object";
inherit "/lib/commands";

#include <macros.h>
#include <filter_funs.h>

#include "/d/Gondor/defs.h"
#include "../mm_stables.h"

int hhalt();
int hsnort();
int hhelp(string str);
int Hgallop;
int hscrape(string str);
int hneigh(string str);
int hrear(string str);
int heyes(string str);
int hgallop(string str);

/*
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!living(to))
    {
        return;
    }
    add_action(hhalt, "hhalt");
    add_action(hsnort, "hsnort");
    add_action(hhelp, "hhelp");
    add_action(hscrape, "hscrape");
    add_action(hneigh, "hneigh");
    add_action(hrear, "hrear");
    add_action(heyes, "heyes");
    add_action(hgallop, "hgallop");
}
*/

int 
hhalt()
{
    write("You bring your steed to a halt.\n");
    say(QCTNAME(TP) + " brings " + POSSESSIVE(TP) + " steed to a halt.\n");
    return 1;
}

int
hsnort()
{
    tell_room(ENV(TP), "The large black horse snorts violently.\n");
    return 1;
}

int
hhelp(string str)
{
//    if (str == "saddlebag")
//    {
//        write(HHELP_BAG_MESSAGE);	/* defined in mm_stables.h */
//        return 1;
//    }
    write(HHELP_RIDER_MESSAGE);		/* defined in mm_stables.h */
    return 1;
}

int
hscrape(string str)
{
    string *how;

    how = parse_adverb_with_space(str, "impatiently", 0);
    
    tell_room(ENV(TP), "The large black horse" + how[1] + " scrapes its " +
              "iron-fitted hooves deep through the ground.\n");
    return 1;
}

int
hneigh(string str)
{
    int i;
    object *people;
    object *oblist;
    string *how;
    
    how = parse_adverb_with_space(str, "chillingly", 0);
    
    if (!stringp(how[0]))
    {
        tell_room(ENV(TP), "Raising its head, the large black horse neighs" +
                  how[1] + ".\n");

        people = FILTER_PLAYERS(all_inventory(ENV(TP)));
        for (i = sizeof(people) - 1; i >= 0; i--)
        {
            if (!IS_MORGUL_MAGE(people[i]))
            {
                people[i]->catch_tell("The blood freezes in your veins.\n");
            }
        }
        return 1;
    }
    oblist = parse_this(how[0], "[at] %l");
    if (!sizeof(oblist))
    {
        notify_fail("hneigh [how] at whom?\n");
        return 0;
    }
    if (sizeof(oblist) > 1)
    {
        notify_fail("You can only do this at one person at a time.\n");
        return 0;
    }
    if (IS_MORGUL_MAGE(oblist[0]))
    {
        notify_fail("The large black horse refuses do that.\n");
        return 0;
    }
    oblist[0]->catch_tell("Raising its head towards you, the large black " +
                          "horse tosses its head" + how[1] + ".\n");
    oblist[0]->catch_tell("The blood freezes in your veins.\n");
    tell_room(ENV(TO), "Raising its head towards " + QTNAME(oblist[0]) +
                       ", the large black horse neighs" + how[1] + ".\n");
    return 1;
}

int
hrear(string str)
{
    string *how;

    how = parse_adverb_with_space(str, "belligerently", 0);
    
    write("With a sharp pull on the reins, you force your steed" +
          how[1] + " to rear itself up.\n");
    say("With a sharp pull on the reins, " + QTNAME(TP) + "" + how[1] +
        " rears up " + POSSESSIVE(TP) + " steed.\n");
    return 1;
}

int
heyes(string str)
{
    string *how;
    object *oblist;
    
    how = parse_adverb_with_space(str, "belligerently", 0);

    if (!stringp(how[0]))
    {
        notify_fail("heyes [how] at whom?\n");
        return 0;
    }
    oblist = parse_this(how[0], "[at] %l");
    if (!sizeof(oblist))
    {
        notify_fail("heyes [how] at whom?\n");
        return 0;
    }
    if (sizeof(oblist) > 1)
    {
        notify_fail("You can only do this at one person at a time.\n");
        return 0;
    }
    oblist[0]->catch_tell("Fixing its dilated eyes upon you, the large " +
                          "black horse tosses its head" + how[1] + ".\n");
    tell_room(ENV(TO), "Fixing its dilated eyes upon " + QTNAME(oblist[0]) +
                       ", the large black horse tosses its head" + how[1] +
                       ".\n");
    return 1;
}

int
hgallop(string str)
{
    return query_steed()->hgallop(str);
}

void
init()
{
    ::init();
    
    add_action(hhalt, "hhalt");
    add_action(hsnort, "hsnort");
    add_action(hhelp, "hhelp");
    add_action(hscrape, "hscrape");
    add_action(hneigh, "hneigh");
    add_action(hrear, "hrear");
    add_action(heyes, "heyes");
    add_action(hgallop, "hgallop");
}
