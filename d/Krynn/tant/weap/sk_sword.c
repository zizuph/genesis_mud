/* Skeleton sword by Teth, April 6, 1996 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "../local.h"

create_weapon()
{
    set_name("shortsword");
    add_name(({"sword","weapon"}));
    set_pname("shortswords");
    add_pname(({"swords","weapons"}));
    set_short("fine shortsword");
    set_adj("fine");
    add_adj("short");
    set_pshort("fine shortswords");
    set_long("This fine shortsword is most likely the sword of a "+
      "nobleperson. It has a sturdy hilt, with a rounded pommel. "+
      "The blade of the weapon is sleek and shiny, and it looks "+
      "like it could do massive damage. You think kissing the "+
      "blade might bring good luck.\n");
    set_wf(TO);
    set_default_weapon(12, 18, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    AI(({"hilt","sturdy hilt"}),"The hilt of sword is made of steel, "+
      "with a fine chain wrapped around to offer better grip.\n");
    AI(({"pommel","rounded pommel"}),"The pommel of the sword is "+
      "rounded, and might help prevent the sword from slipping out "+
      "of your hand.\n");
    AI("blade","The blade of the sword is sleek and shiny, obviously "+
      "well-crafted.\n");
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(12,18));
}

init()
{
    ::init();
    ADA("kiss");
}

int kiss(string str)
{
    if ((str=="blade")||(str=="shortsword"))
    {
        if (TO->query_wielded())
        {
            write("You kiss the blade of the shortsword for good luck.\n"+
              "You somehow feel luckier.\n");
            say(QCTNAME(TP)+ " kisses the blade of the fine shortsword, "+
              "presumably for good luck.\n");
            return 1;
        }
        write("Kiss what?\n");
        return 1;
    }
    NF("Kiss whom [how]?\n");
    return 0;
}

mixed 
wield(object what)
{
    if (TP->query_base_stat(SS_STR) < 61)
    {
        write("The sword shivers in your hand, testing you, but then "+
          "allows you to wield it.\n");
        say(QCTNAME(TP)+ "'s fine shortsword shivers slightly when it is "+
          "wielded.\n");
        return 0;
    }
    return "The sword shivers violently in your hand, not allowing you to "+
    "wield it. A piercing pain enters your head, along with a "+
    "voice that shrieks: You'd destroy me, fool!\n";
}

mixed
unwield(object what)
{
    return 0;
}


