inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

/* Sarr */

/* Valen, 20011015, fixed a typo */

void
create_weapon()
{
    ::create_weapon();

    set_name("battleaxe");
    add_name("axe");
    set_adj("lochaber");
    add_adj("silver");
    set_short("silver lochaber battleaxe");
    set_pshort("silver lochaber battleaxes");

    set_long("This is a very nasty looking axe. The blade is made out "+
      "of some pure silver steel, and it curves back into nasty, sharp "+
      "points. There are barbs along the edges to cause more pain to "+
      "an enemy than damage. The wooden haft looks old, and there "+
      "are black iron bands wrapped around it.\n");

    set_dt(W_SLASH);
    set_wt(W_AXE);
    set_hit(24);
    set_pen(30);
    KVWEP(20);
    KWWEP(30);
    KVOL(silver);
}
