/*
 * g_mail.c
 * By Skippern
 * June 2000
 *
 */
inherit "/std/armour";

#include "../erech.h"
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name( ({ "chainmail", "mail" }) );
    set_pname( ({ "chainmails", "mails" }) );
    set_short("rusty chainmail");
    set_pshort("rusty chainmails");
    set_long("It is an old chainmail made of rusty iron rings. Once upon " +
	"time it has been painted white, but most of the paint is worn " +
	"off. Some places a few rings are missing revealing a linen shirt " +
	"to protect the skin from the rings.\n");
    set_adj("chain");

    set_default_armour(14,A_BODY,0,0);
    add_prop(OBJ_I_WEIGHT,5800);
    add_prop(OBJ_I_VOLUME,700);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(14) + random(200) - 200 );
}



