/*  Crozier of a abbot/Ard-Prebytair
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           5/15/98  Recoded to inherit staff.c
**
**/
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"
inherit SR_WEAPON+"staff"; //staff inherits khalakhor_weapon

void create_khalakhor_weapon() 
{
    set_name("crozier");
    set_adj(({"ornate","silver","tall"}));
    set_base_hit(30);
    set_base_pen(10);
    set_sshort("ornate silver crozier");
    set_slong("It is an ornate silver crozier, a tall staff which "+
              "curls at the top like a shepherd's staff.\n");
    update_srstaff();
}
