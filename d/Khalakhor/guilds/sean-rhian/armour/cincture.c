/*  Cincture (rope belt worn with a robe)
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/15/97  Created
** Damaris        02/01    Added wear-remove features
**/

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#define TP        this_player()
#define TO        this_object()
#define CAP(x)    capitalize(x)
#define ENV(x)    environment(x)
#define HIS(x)    x->query_possessive()
#define HE(x)     x->query_pronoun()
#define HIMM(x)    x->query_objective()

void create_armour()
{
    set_name("cincture");
    add_name(({"rope","belt"}));
    set_adj(({"braided", "white"}));
    set_short("braided white cincture");
    set_long( "It is a braided white cincture, a long rope tied around "+
              "the waist as a belt.\n");
    set_ac(2);
    set_at(A_WAIST);
    set_af(this_object());

}

mixed wear()
{
   /* This is what wearer see's when wearinging. */
   write("You wrap the "+short()+" around your waist and tie it firmly.\n");

   /* This what others in room see upon wearing. */
   say(QCTNAME(TP)+" wraps the "+short()+" around "+HIS(TP)+" waist "+
   "and ties it firmly.\n");

   return 1;
}

mixed remove()
{
    /* This is what wearer see's when removing. */
    write("You untie the "+short()+" removing it from your waist.\n");

    /* This is what others in room see when removing. */
    say(QCTNAME(TP)+" unties the "+short()+" removing it "+
      "from "+HIS(TP)+" waist.\n");

    return 1;
}
