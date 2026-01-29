/*
 * What         : An ornate wooden case
 * Used by      : Carried by minotaur captain Corth sailing the Bloodsea.
 *                /d/Ansalon/goodlund/bloodsea/obj
 * Description  : One of two quest items the player has to find when solving 
 *              : the Toron_missing_standard quest.
 * Made by      : Cherek, Feb 2007
 */

inherit "/std/receptacle";

#include "../local.h"
#include <formulas.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_receptacle()
{
    setuid(); 
    seteuid(getuid());

    set_name("case");   
    add_name("_ornate_wooden_case");
    add_pname("cases");
    set_adj( ({"ornate", "wooden" }) );
    set_short("ornate wooden case");
    set_pshort("ornate wooden cases");
    set_long("This is a rectangular shaped wooden case, it is " +
             "about five feet long and only one feet wide. It " +
             "is made of dark well-polished wood and the inside " +
             "is covered with a deep green cloth. \n");

    add_prop(CONT_I_WEIGHT,     5000);
    add_prop(CONT_I_MAX_WEIGHT, 20000);
    add_prop(CONT_I_VOLUME,     10000);
    add_prop(CONT_I_MAX_VOLUME, 20000);
    add_prop(CONT_I_RIGID, 1);   
    add_prop(OBJ_I_VALUE, 100);

}
