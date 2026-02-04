/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 *  Grey Helmet for the House4_Captain
 *  Tomas, 11/19/1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("helmet");
    set_short("grey helmet");
    set_adj("grey");
   set_pshort("grey helmets");
    set_long("A grey helmet is conical shaped with a nose guard. \n");
    
   set_pname(({"helmets","grey helmets"}));
    set_default_armour(30, A_HEAD, 0, 0);
}
