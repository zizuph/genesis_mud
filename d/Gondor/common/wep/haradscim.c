/*  /d/Gondor/common/wep/haradscim
 *
 *  Haradrim scimitar  
 * 
 *  2007.02.21, Toby: Balanced weight and coinage
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_weapon()
{
    set_name(({"scimitar","sword","weapon"}));
    set_pname("scimitars");
    add_name("swords");
    set_short("ornate gold scimitar");
    set_pshort("ornate gold scimitars");
    set_long("A sharp, curved haradrim sword, made of ornate gold.\n");
    set_adj( ({"golden", "haradrim", "ornate", "gold", "curved", "sharp" }) );
    set_default_weapon(30,23,W_SWORD,W_SLASH,W_NONE,0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(23, W_SLASH));
    add_prop(OBJ_I_VOLUME,950);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30,23));
}
