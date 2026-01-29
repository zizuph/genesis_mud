/* MCLUB - Initiation book. This object is found in the cabinet in
**         the sacristry and contains the preparations and instructions
**         for initiating someone into the club
**   CODER         DATE             ACTION
**  ------------ -------- -----------------------------------------------
**   Zima         7/30/95   Created
**
**/
inherit "/std/scroll";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <config.h>
#include <cmdparse.h>
#include "defs.h"
 
void create_scroll()
{
    set_name(({"ancient tome","tome"}));
    set_short("ancient tome");
    set_long(
       "It is an ancient papyrus tome with newly written arcane "+
       "lettering. Perhaps you can read or mread it.\n");
 
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 150);
 
    set_file(OBJ_DIR+"initome.txt");
}
