/* Monument to the fallen.
   A monument to all those who have fallen while seeking to preserve
   and protect free civilisation from tyranny.
   The monument is made of weapons donated by (mostly good)
   players. It grows in height as more weapons are donated to 
   it.

   Coded by Maniac.

   History
          28/8/95           Created                   Maniac
*/

inherit "/std/object";

#include <macros.h>
#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "obj.h"

#define ITEMS_PER_FOOT 100
#define MONUMENT_RECORD (MOUNTAIN_TEXTS + "monument")

int swords; 
int polearms;
int axes;
int clubs;
int knives;


string
my_short()
{
    int height;
 
    height = 4 + ((swords + polearms + axes + clubs + knives) /
                  ITEMS_PER_FOOT);

    return ("The " + height + "-foot high monument to the fallen");
}


string
my_long()
{
   string str;

   str = (my_short() + ". ");

   str += ("It is made up entirely of donated weapons, which " +
           "are held together in grand and beautiful arrangement " +
           "by magic. ");
   str += ("At its base is a plaque that reads:\n\n" +
           "             This monument commemorates those who\n" +
           "       have fallen while seeking to preserve and protect\n" +
           "          free civilisation from the claws of tyranny.\n\n\n");
   str += ("The monument is currently made up of:\n" +
           "             " + swords + " swords,\n" +
           "             " + polearms + " polearms,\n" +
           "             " + axes + " axes,\n" +
           "             " + clubs + " clubs,\n" +
           "             " + knives + " knives.\n\n");
   str += ("You may <donate> a weapon to the commemoration yourself if " +
           "you wish.\n");

   return str;
}


void
create_object()
{
    set_short("@@my_short");
    set_long("@@my_long");
    set_name("monument");

    add_prop(OBJ_M_NO_GET, "You want to pick up a whole monument? Gone " +
                           "mad or something?\n");
    add_prop(OBJ_I_WEIGHT, 1000000);
    add_prop(OBJ_I_VOLUME, 1000000);

    seteuid(getuid());
    restore_object(MONUMENT_RECORD);
}



/* Donate item to the monument */
int
donate_item(string str)
{
    object ob;
    object tp = this_player();
    int wt;
    string dummy;

    if (!str) {
        notify_fail("Donate what?\n");
        return 0;
    }

    if (!parse_command(str, all_inventory(tp), "%o", ob)) {
        notify_fail("Donate what?\n");
        return 0;
    }

    if (tp->query_wiz_level()) {
        notify_fail("Wizards may not donate to this monument!\n");
        return 0;
    }

    if (sscanf(tp->query_real_name(), "%sjr", dummy) == 1) {
        notify_fail("Wizard juniors may not donate to this monument!\n");
        return 0;
    }

    if (!function_exists("create_weapon", ob)) {
        notify_fail("That is not a weapon!\n");
        return 0;
    }

    if (ob->query_prop(OBJ_I_BROKEN)) {
        notify_fail("That is broken!\n");
        return 0;
    }

    wt = ob->query_wt();

    if ((wt != W_SWORD) &&
        (wt != W_POLEARM) &&
        (wt != W_AXE) &&
        (wt != W_KNIFE) &&
        (wt != W_CLUB)) {
        notify_fail("That weapon is not of donatable type!\n");
        return 0;
    }


    if (ob->move(environment(this_object())) != 0) {
        notify_fail("You could not donate that weapon for some reason!\n");
        return 0;
    }

    tp->catch_msg("You donate your " + ob->short() + " to the monument.\n");
    tell_room(environment(tp), QCTNAME(tp) + " donates " +
                               tp->query_possessive() + " " + ob->short() +
                               " to the monument.\n", tp);

    ob->remove_object();

    switch (wt) {
        case W_SWORD : swords++;
                       break;
        case W_POLEARM : polearms++;
                         break;
        case W_AXE : axes++;
                     break;
        case W_KNIFE : knives++;
                       break;
        case W_CLUB : clubs++;
                      break;
    }
    save_object(MONUMENT_RECORD);
    return 1;
}


void
init()
{
    ::init();
    add_action("donate_item", "donate");
}

