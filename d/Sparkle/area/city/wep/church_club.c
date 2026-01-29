/*
 *  /d/Sparkle/area/city/wep/church_club.c
 *
 *  The default club given to new players who pray at the church in
 *  Sparkle.
 *
 *  given at: /d/Genesis/start/human/town/church.c
 *
 *  Created May 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/wep/church_weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>


/* prototypes */
public void        create_church_weapon();


/*
 * Function name:        create_church_weapon
 * Description  :        dummy constructor function for inheriting
 *                       objects to redefine
 */
public void
create_church_weapon()
{
    set_name("club");

    set_short("mistform club");
    set_long("This club is light as a feather, yet looks as if it could"
      + " still do quite a bit of damage if anyone wanted to"
      + " <wield> it and try to <kill> something.\n");

    set_default_weapon(10, 10, W_CLUB, W_SLASH, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(10, W_CLUB) / 4);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
} /* create_church_weapon */


/*
 * Function name:        wizinfo
 * Description  :        provide some special info on this weapon
 * Returns      :        string - the info
 */
public string
wizinfo()
{
    return "This weapon can be obtained by any player at the Sparkle"
      + " church who wishes to <pray> and <request> it. It is a way"
      + " to make the game a bit more friendly to new players. As such,"
      + " it is much lighter than normal weapons.\n";
} /* wizinfo */
